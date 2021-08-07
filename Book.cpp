#include "Book.h"
#include <iomanip>

using namespace std;

void Book::WriteToFile(ostream &stream) const {
    const char d = ' ';
    stream << id << d << title << d << author << d << copies << '\n';
}

void Book::ReadFromFile(istream &stream) {
    stream >> id >> title >> author >> copies;
}

void Book::PrettyPrint(ostream &stream) const  {
    stream << "Book [ID:" << id << ", Title:'" << title << "', Author:'" << author << "', Copies:" << copies << "]\n";
}
