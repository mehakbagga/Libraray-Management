#include "Library.h"
#include "Utils.h"

using namespace std;

void Library::WriteToFile(ostream &stream) const {
    
    stream << m_nextStudentId << ' ' << m_nextIssueRecordId << ' ' << m_nextBookId << '\n';

    stream << m_books.size() << '\n';
    for(int i = 0; i < m_books.size(); i++) {
        m_books[i].WriteToFile(stream);
    }
    stream << m_issues.size() << '\n';
    for(int i = 0; i < m_issues.size(); i++) {
        m_issues[i].WriteToFile(stream);
    }
    stream << m_students.size() << '\n';
    for(int i = 0; i < m_students.size(); i++) {
        m_students[i].WriteToFile(stream);
    }
}

void Library::ReadFromFile(istream &stream) {
    stream >> this->m_nextStudentId >> this->m_nextIssueRecordId >> this->m_nextBookId;
    int size;
    m_issues.clear();
    stream >> size;
    for (int i = 0; i < size; i++) {
        Book item{};
        item.ReadFromFile(stream);
        m_books.push_back(item);
    }
    stream >> size;
    for (int i = 0; i < size; i++) {
        IssueRecord item{};
        item.ReadFromFile(stream);
        m_issues.push_back(item);
    }
    stream >> size;
    for (int i = 0; i < size; i++) {
        Student item{};
        item.ReadFromFile(stream);
        m_students.push_back(item);
    }
}

bool Library::AddBook(const string &title, const string &authorName, int copies) {
    const Book &prexisting = GetBook(title);
    if (!(prexisting == BookNotFound)) {
        AddErrorMessage("Book with this Title already exists with ID '" + to_string(prexisting.id) + "'.");
        return false;
    }
    Book b{};
    b.author = authorName;
    b.copies = copies;
    b.title = title;
    b.id = m_nextBookId++;
    m_books.push_back(b);
    return true;
}

bool Library::AddStudent(const string &studentName) {
    Student s{};
    s.studentId = m_nextStudentId++;
    s.studentName = studentName;
    m_students.push_back(s);
    return true;
}

bool Library::IssueBook(int bookId, int studentId, int days) {
    Book &b = GetBook(bookId);
    if (b.id == BookNotFound.id) {
        return false;
    }
    if (IssuedCopies(b) >= b.copies) {
        AddErrorMessage("All copies of this book have been issued.");
        return false;
    }

    Student &s = GetStudent(studentId);
    if (s == StudentNotFound) {
        return false;
    }
    IssueRecord issue{days};
    issue.studentId = studentId;
    issue.bookIssuedId = bookId;
    issue.recordId = m_nextIssueRecordId++;
    issue.wasReturned = false;
    m_issues.push_back(issue);
    return true;
}

bool Library::IssueBook(const string &title, int studentId, int days) {
    Book &b = GetBook(title);
    if (b == BookNotFound) return false;
    return IssueBook(b.id, studentId, days);
}

IssueRecord &Library::GetIssue(int issueId) {
    for (auto &i : m_issues) if (i.recordId == issueId) return i;
    AddErrorMessage("Issue Record Not Found.");
    return IssueRecordNotFound;
}

Book &Library::GetBook(int bookId) {
    //because of incrementing unique ID and ordered saving/loading, we can be sure books is always sorted
    int index = Utils::BinarySearch(m_books, Book(bookId));
    if(index != -1) {
        return m_books[index];
    }
    //for (auto &b : m_books) if (b.id == bookId) return b;

    //not found
    AddErrorMessage("Book Not Found.");
    return BookNotFound;
}

Student &Library::GetStudent(int studentId) {
    for (auto &s : m_students) if (s.studentId == studentId) return s;
    AddErrorMessage("Student Not Found.");
    return StudentNotFound;
}


Book &Library::GetBook(const std::string &title) {
    for (auto &b : m_books) if (b.title == title) return b;
    AddErrorMessage("Book Not Found.");
    return BookNotFound;
}



vector<Book> Library::BooksByAuthor(const string &authorName) {
    vector<Book> books;
    for(int i = 0; i < m_books.size(); i++) {
        if(m_books[i].author == authorName) {
            books.push_back(m_books[i]);
        }
    }
    return books;
}

bool Library::ReturnBook(int issueId) {
    IssueRecord &issue = GetIssue(issueId);
    if (issue == IssueRecordNotFound) {
        return false;
    }
    issue.MarkReturned();
    return true;
}

bool Library::ExtendDueDate(int issueId, int days) {
    IssueRecord &issue = GetIssue(issueId);
    if (issue == IssueRecordNotFound) {
        return false;
    }
    if (!issue.wasReturned) {
        issue.ExtendDueDate(days);
    }
    return true;
}

bool Library::RemoveBook(int bookId) {
    Book &b = GetBook(bookId);
    if (b == BookNotFound) return false;
    return RemoveBook(b);
}

bool Library::RemoveBook(const Book &b) {
    //erase-remove_if pattern
    for(int i = m_books.size() - 1; i >= 0; i--) {
        Book book = m_books[i];
        if(b.id == book.id) {
            m_books.erase(m_books.begin() + i);
        }
    }
    return true;
}

bool Library::RemoveBook(const string &title) {
    Book &b = GetBook(title);
    if (b == BookNotFound) return false;
    return RemoveBook(b);
}

const vector<Book> &Library::Books() const {
    return m_books;
}

const vector<IssueRecord> &Library::Issues() const {
    return m_issues;
}

const vector<Student> &Library::Students() const {
    return m_students;
}

string Library::GetErrorMessage() {
    return m_errorMessages.IsEmpty() ? "" : m_errorMessages.RemoveLast();
}

int Library::IssuedCopies(int bookId) {
    return IssuedCopies(GetBook(bookId));
}

int Library::IssuedCopies(const Book &b) {
    if (b == BookNotFound) return 0;
    int count = 0;
    for(int i = 0; i< m_issues.size(); i++) {
        if(m_issues[i].bookIssuedId == b.id && !m_issues[i].wasReturned) count++;
    }
    return count;
}

//bool method()

vector<IssueRecord> Library::PastDueDate() {
    std::vector<IssueRecord> past;

    for(int i = 0; i < m_issues.size(); i++) {
        if(m_issues[i].IsPastDueDate()) {
            past.push_back(m_issues[i]);
        }
    }
    return past;
}

void Library::AddErrorMessage(const string& msg) {
    m_errorMessages.AddLast(msg);
}

bool Library::HasErrorMessages() const {
    return !m_errorMessages.IsEmpty();
}
