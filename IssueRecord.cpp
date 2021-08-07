#include "IssueRecord.h"
#include <chrono>

using namespace std;

void IssueRecord::WriteToFile(ostream &stream) const {
    const char d = ' ';
    stream << recordId << d << studentId << d << bookIssuedId << d << dueDateMs << d << wasReturned << '\n';
}

void IssueRecord::ReadFromFile(istream &stream) {
    stream >> recordId >> studentId >> bookIssuedId >> dueDateMs >> wasReturned;
}

void IssueRecord::ExtendDueDate(int days) {
    this->dueDateMs = this->dueDateMs + days * millisecondsInADay;
}

void IssueRecord::MarkReturned() {
    wasReturned = true;
}

void IssueRecord::PrettyPrint(ostream &stream) const  {
    stream << "Issue Record: [ID:" << recordId << ", Book ID:" << bookIssuedId << ", Student ID:" << studentId
           << (wasReturned ? ", RETURNED" : (IsPastDueDate() ? ", PAST DUE" : ", DUE IN " + to_string(DaysUntilDueDate()) + " DAYS")) << "]\n";
}

IssueRecord::IssueRecord() : IssueRecord(defaultDueDateDays) {
}

IssueRecord::IssueRecord(int days) {
    bookIssuedId = -1;
    recordId = -1;
    studentId = -1;
    wasReturned = false;
    dueDateMs = MillisecondsNow() + days * millisecondsInADay;
}

bool IssueRecord::IsPastDueDate() const {
    return MillisecondsNow() > dueDateMs;
}

unsigned long long IssueRecord::MillisecondsNow() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

int IssueRecord::DaysUntilDueDate() const {
    return (int) ((dueDateMs - MillisecondsNow()) / millisecondsInADay);
}

