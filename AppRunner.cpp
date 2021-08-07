#include "AppRunner.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>


using namespace std;

const string save_file_name = "persistent.txt";

int main() {
    AppRunner runner{};
    runner.Run();
    return 0;
}

bool ReadStringOrInt(string &str, int &i);

void AppRunner::Run() {
    HandleCommand("help");
    while (true) {
        //read command
        string command;
        cin >> command;
        //first if-condition helps maintain good input for infinite input loops
        if (cin.fail()) {
            cin.clear();
        } else {
            if (!HandleCommand(command)) return;
        }
    }
}

bool AppRunner::HandleCommand(const string &inputCommand) {
    string command;
    //string_to_lowercase
    for (char i : inputCommand) {
       command.push_back(tolower(i)); 
    }
    if (command == "help") Help();
    else if (command == "import") ImportFile();
    else if (command == "export") ExportFile();
    else if (command == "add_book") AddBook();
    else if (command == "issue_book") IssueBook();
    else if (command == "return_book") ReturnBook();
    else if (command == "extend_book") ExtendBook();
    else if (command == "add_student") AddStudent();
    else if (command == "view_books") ViewAllBooks();
    else if (command == "view_students") ViewAllStudents();
    else if (command == "delete_book") DeleteBook();
    else if (command == "edit_book") EditBook();
    else if (command == "stats") Stats();
    else if (command == "request_book") RequestBook();
    else if (command == "exit") return false;
    else cout << "Command not found!\n";
    cout.flush();
    return true;
}


void AppRunner::EvaluateSuccess(bool success) {
    if (!success) cout << "Error: " << m_library.GetErrorMessage() << '\n';
}

void AppRunner::Help() {
    cout << "Library Commands:\n"<<
            "\texport : Exports library to file.\n"<<
            "\timport : Imports file and loads it as library db.\n"<<
            "\tadd_book : <title author copies> Add book to the library.\n"<<
            "\tissue_book : <bookId studentId days> Issue a book to a student for a specific number of days.\n"<<
            "\treturn_book : <issueid> Returns an issued book.\n"<<
            "\textend_book : <issueid days> Extends loan of book by days.\n"<<
            "\tadd_student : <studentname> Adds a student to the registry.\n"<<
            "\tview_books : Views all books in library.\n"<<
            "\tview_students : Views all students in library records.\n"<<
            "\tdelete_book : <bookIdOrName> Deletes book from the library records.\n"<<
            "\tedit_book : <bookIdOrName title author copies> Edits the book information.\n"<<
            "\tstats : Prints certain useful stats.\n"<<
            "\trequest_book : <authorname> Shows a random book by the author.\n"<<
            "\thelp : Prints all commands defined in application.\n"<<
            "\texit : Closes application (does not save).\n" << endl; 
    
}

void AppRunner::ImportFile() {
    fstream file;
    file.open(save_file_name, fstream::in);
    m_library.ReadFromFile(file);
    file.close();
}

void AppRunner::ExportFile() {
    fstream file;
    file.open(save_file_name, fstream::out | fstream::trunc);
    m_library.WriteToFile(file);
    file.flush();
    file.close();
}

void AppRunner::AddBook() {
    string title, author;
    int copies;
    cin >> title >> author >> copies;
    EvaluateSuccess(m_library.AddBook(title, author, copies));
}

void AppRunner::IssueBook() {
    int bookId, studentId, days;
    string bookName;
    bool isString = ReadStringOrInt(bookName, bookId);
    cin >> studentId >> days;
    bool success = isString ? m_library.IssueBook(bookName, studentId, days) : m_library.IssueBook(bookId, studentId, days);
    EvaluateSuccess(success);
}

void AppRunner::ReturnBook() {
    int issueId;
    cin >> issueId;
    bool success = m_library.ReturnBook(issueId);
    EvaluateSuccess(success);
    if (success) {
        //check if returned book was past issue date. notify student of late fees if it was.
        IssueRecord rec = m_library.GetIssue(issueId);
        if (rec == m_library.IssueRecordNotFound)
            return; //shouldn't be possible, but if replaced with an assertion will be handy to let know of any breaking changes
        if (rec.IsPastDueDate()) {
            cout
                << "Returned book was past due date. You'll be required to pay a Late Fees of 1.99$ before issuing any further books." << endl ;
        }
    }
}

void AppRunner::ExtendBook() {
    int issueId, days;
    cin >> issueId >> days;
    EvaluateSuccess(m_library.ExtendDueDate(issueId, days));
}

void AppRunner::AddStudent() {
    string studentName;
    cin >> studentName;
    EvaluateSuccess(m_library.AddStudent(studentName));
}

void AppRunner::ViewAllBooks() {
    auto books = m_library.Books();
    for (const auto &b : books) b.PrettyPrint(cout);
}

void AppRunner::ViewAllStudents() {
    auto students = m_library.Students();
    for (const auto &s : students) s.PrettyPrint(cout);
}


void AppRunner::DeleteBook() {
    string bookName;
    int bookId;
    bool isName = ReadStringOrInt(bookName, bookId);
    EvaluateSuccess(isName ? m_library.RemoveBook(bookName) : m_library.RemoveBook(bookId));
}

bool isPairSecondGreatertThan(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
}

void AppRunner::Stats() {
    //most issued books
    //use map for constant time access
    cout << "Most Books Issued: " << endl;
    unordered_map<int, int> booksIssuedCount;
    auto issues = m_library.Issues();
    for (const auto &i : issues) {
        booksIssuedCount[i.bookIssuedId]++;
    }
    //move to vector for sorting
    vector<pair<int, int>> booksIssuedCountVec;
    for (const auto &item : booksIssuedCount) {
        booksIssuedCountVec.push_back(item);
    }

    Utils::HeapSort(booksIssuedCountVec, isPairSecondGreatertThan);

    const int maxToPrint = 5;
    for (int i = 0; i < maxToPrint; i++) {
        int index = ((int) booksIssuedCountVec.size()) - i - 1;
        if (index < 0) break;
        auto item = booksIssuedCountVec[index];
        Book &b = m_library.GetBook(item.first);
        if (!(b == m_library.BookNotFound)) {
            b.PrettyPrint(cout);
        }
    }
}

void AppRunner::RequestBook() {
    string authorName;
    cin >> authorName;
    auto books = m_library.BooksByAuthor(authorName);
    if (books.empty()) {
        cout << "No books found by author." << endl;
    } else {
        int bookIndex = rand() % books.size(); //get a random book
        books[bookIndex].PrettyPrint(cout);
    }
    
}

void AppRunner::EditBook() {
    string oldBookName, newTitle, newAuthor;
    int oldBookId, newCopies;
    bool isName = ReadStringOrInt(oldBookName, oldBookId);
    cin >> newTitle >> newAuthor >> newCopies;
    Book &toEdit = isName ? m_library.GetBook(oldBookName) : m_library.GetBook(oldBookId);
    if (toEdit == m_library.BookNotFound)  cout << "Error: " << m_library.GetErrorMessage() << endl;
    else {
        toEdit.title = newTitle;
        toEdit.author = newAuthor;
        toEdit.copies = newCopies;
    }
}

/*
 * Returns true if string. False if int.
 */
bool ReadStringOrInt(string &str, int &i) {
    cin >> str;
    istringstream check(str);
    if (check >> i) {
        return false;
    } else {
        return true;
    }
}