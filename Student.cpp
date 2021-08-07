#include "Student.h"
#include <iomanip>

using namespace std;

void Student::WriteToFile(ostream &stream) const {
    const char d = ' ';
    stream << studentId << d <<studentName << '\n';
}

void Student::ReadFromFile(istream &stream) {
    stream >> studentId >> studentName;
}

void Student::PrettyPrint(ostream &stream) const  {
    stream << "Student: [ID:" << studentId << ", Name:'" << studentName <<  "']\n";
}
