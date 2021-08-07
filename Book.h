#ifndef LIBRARYASSIGNMENT_BOOK_H
#define LIBRARYASSIGNMENT_BOOK_H

#include <string>
#include <iostream>

using namespace std;

/**
 * Book data model.
 */
struct Book {
    /**
     * Unique ID of the book.
     */
    int id{};
    /**
     * Unique title of the book.
     */
    string title;
    /**
     * Name of the book's author.
     */
    string author;

    /**
     * Number of copies in the library.
     */
    int copies{};

    
    void WriteToFile(ostream& stream) const ;
    void ReadFromFile(istream& stream) ;
    void PrettyPrint(ostream &stream) const  ;

    Book()= default;

    //id-only constructor
    Book(int ID) {
        id = ID;
    }

    /**
     * Copy constructor required for certain std::algorithms.
     * @param other
     */
    Book(const Book& other) {
        (*this) = other;
    }

    //operators for help with binary search
    bool operator == (const Book& other) const {
        return id == other.id;
    }

     bool operator>(const Book& other) const {
        return id > other.id;
    }

    Book& operator=(const Book& other) {
        id = other.id;
        title = other.title;
        author = other.author;
        copies = other.copies;
        return (*this);
    }
};


#endif //LIBRARYASSIGNMENT_BOOK_H
