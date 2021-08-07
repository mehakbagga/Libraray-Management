#ifndef LIBRARYASSIGNMENT_LIBRARY_H
#define LIBRARYASSIGNMENT_LIBRARY_H

#include <vector>
#include "IssueRecord.h"
#include "Book.h"
#include "Student.h"
#include "LinkedList.h"

using namespace std;

/**
 * Main class that manipulates simpler models: Issued Books, Books, Students.
 */
class Library {
private:
    int m_nextStudentId{};
    int m_nextIssueRecordId{};
    int m_nextBookId{};
    vector<Book> m_books;
    vector<IssueRecord> m_issues;
    vector<Student> m_students;
    LinkedList<string> m_errorMessages{};
public:
    //Objects that can be used to see if a method on similar object failed.
    //todo -- could be better as static const
    Book BookNotFound{};
    IssueRecord IssueRecordNotFound{};
    Student StudentNotFound{};

public:
    Library() {
        BookNotFound.id = -1;
        IssueRecordNotFound.recordId = -1;
        StudentNotFound.studentId = -1;
    }

    void WriteToFile(ostream &stream) const;

    void ReadFromFile(istream &stream);

    //Class Methods
    /**
     * Adds a book structure to the library. Next unique ID is automatically assigned.
     * @param title Title of the book. May contain spaces.
     * @param authorName Name of the book's author.
     * @param copies Number of copies added to the library.
     * @return True if a book with same title doesn't already exist. False otherwise.
     */
    bool AddBook(const string &title, const string & authorName, int copies);

    /**
     * Adds a student structure to the library.
     * @param studentName
     * @return
     */
    bool AddStudent(const string &studentName);

    /**
     * Adds an issue record for a certain number of days against given book and student pair.
     * @param bookId Unique ID of the book.
     * @param studentId Unique ID of the student.
     * @param days Number of days from now until due date.
     * @return True if book and student found, and book still has some copies that aren't currently issued.
     */
    bool IssueBook(int bookId, int studentId, int days);

    /**
     * Adds an issue record using book name instead of ID.
     */
    bool IssueBook(const string &title, int studentId, int days);

    //Getters
    IssueRecord &GetIssue(int issueId);

    //Uses Binary Search
    Book &GetBook(int bookId);

    Student &GetStudent(int studentId);

    Book &GetBook(const string &title);

    /**
     * Returns all issue records that are past their due date and not fulfilled.
     */
    vector<IssueRecord> PastDueDate();

    /**
     * Returns all books by a certain author.
     */
    vector<Book> BooksByAuthor(const string &authorName);

    /**
     * Counts the number of copies of a book that are currently issued and not returned.
     * @param b Book to count copies of.
     * @return Number of copies currently lent.
     */
    int IssuedCopies(const Book &b);

    /**
     * Counts the number of copies of a book that are currently issued and not returned.
     */
    int IssuedCopies(int bookId);

    //Mutators
    /**
     * Returns an issued book, while notifying student of any pending late fees.
     * @param issueId Unique ID of the issue record against this book and student.
     * @return True if successfully returned (issue record existed).
     */
    bool ReturnBook(int issueId);

    /**
     * Extends the due date on an issued book.
     * @param issueId Unique ID of the issue record.
     * @param days Number of days to extend by.
     * @return
     */
    bool ExtendDueDate(int issueId, int days);

    /**
     * Removes a book from the library records. Does not remove issue records against this book.
     * @param bookId Unique ID of the book.
     * @return True if successful.
     */
    bool RemoveBook(int bookId);

    /**
     * Removes a book from the library records. Does not remove issue records against this book.
     * @param bookId Title of the book.
     * @return True if successful.
     */
    bool RemoveBook(const string &title);

    /**
     * Removes a book from the library records. Does not remove issue records against this book.
     * @param bookId Book structure.
     * @return True if successful.
     */
    bool RemoveBook(const Book &b);

    /**
     * Books registered to the library.
     */
    const vector<Book> &Books() const;

    /**
     * Issue Records in the library.
     */
    const vector<IssueRecord> &Issues() const;

    /**
     * Students in the library.
     */
    const vector<Student> &Students() const;

    /**
     * Get latest error message set by library internals.
     */
    string GetErrorMessage();

    bool HasErrorMessages() const;

private:
    void AddErrorMessage(const string& msg);
};


#endif //LIBRARYASSIGNMENT_LIBRARY_H
