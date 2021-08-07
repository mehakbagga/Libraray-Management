#ifndef LIBRARYASSIGNMENT_ISSUERECORD_H
#define LIBRARYASSIGNMENT_ISSUERECORD_H

#include <iostream>

using namespace std;

/**
 * Book Issue data model, with some helper methods.
 */
struct IssueRecord {
public:
    //fields
    int recordId{};
    int studentId{};
    int bookIssuedId{};
    unsigned long long dueDateMs; //what precision do we need? maybe just store days since epoch?
    bool wasReturned{};
public:
    //constructors
    IssueRecord();

    explicit IssueRecord(int days);

    //Methods
    /**
     * Extends Due Date by certain number of days.
     */
    void ExtendDueDate(int days);

    /**
     * Marks the issued book as being returned.
     */
    void MarkReturned();

    /**
     * Whether the due date on the book has passed.
     */
    bool IsPastDueDate() const;

    /**
     * How many days from now till the due date of the book.
     */
    int DaysUntilDueDate() const;

    //derived
    //ostream is any output stream like cout
    void WriteToFile(ostream &stream) const;

    //istream is any input stream like cin
    void ReadFromFile(istream &stream);

    void PrettyPrint(ostream &stream) const;

    //operators
    friend bool operator==(const IssueRecord &a, const IssueRecord &b) {
        return a.recordId == b.recordId;
    }

private:
    //time helpers
    static const int defaultDueDateDays = 7; //one week
    static const unsigned long long millisecondsInADay = 24 * 60 * 60 * 1000;
    static unsigned long long MillisecondsNow();
};

#endif //LIBRARYASSIGNMENT_ISSUERECORD_H
