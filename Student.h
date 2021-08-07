#ifndef LIBRARYASSIGNMENT_STUDENT_H
#define LIBRARYASSIGNMENT_STUDENT_H

#include <iostream>

using namespace std;
/**
 * Student data model.
 */
struct Student{
    //fields
    //could easily add more like contact no, admission no, etc.
    /**
     * Unique ID of the student.
     */
    int studentId{};
    string studentName{};

    //ostream is any stream like cout
    //istream is any input stream like cin
    void WriteToFile(ostream &stream) const;
    void ReadFromFile(istream &stream);
    void PrettyPrint(ostream &stream)  const;

    //operators
    friend bool operator == (const Student& a, const Student& b) {
        return a.studentId == b.studentId;
    }
};


#endif //LIBRARYASSIGNMENT_STUDENT_H
