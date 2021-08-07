#ifndef LIBRARYASSIGNMENT_APPRUNNER_H
#define LIBRARYASSIGNMENT_APPRUNNER_H

#include <string>
#include <unordered_map>
#include "Library.h"

class AppRunner;

/**
 *
 * Acts as intermediary between Library class and the user interface.
 */
class AppRunner {
public:
    /**
     * Lifetime method of the class. Never returns unless exceptions interrupt.
     */
    void Run();

    /**
     * Handles a single word received from input, trying to match it to a command method.
     * @param command Single world string (can contain underscores) taken from some input.
     */
    bool HandleCommand(const string &command);

private:
    /**
     * Instance of Library contained in this AppRunner.
     */
    Library m_library;

    /**
     * Method that takes common actions for each command in case of success or failure.
     * (Currently, prints the library error if failed.)
     * @param success Whether the command considers its execution a success.
     */
    void EvaluateSuccess(bool success);

    //All methods below correspond to a command.
    /**
     * Prints helpful information about the application, mostly all of the commands the user can use.
     */
    void Help();

    /**
     * Restores the library state from a file.
     */
    void ImportFile();

    /**
     * Exports the library state to a file that can be restored later.
     */
    void ExportFile();

    /**
     * Add a book to the library records.
     */
    void AddBook();

    /**
     * Issues a book against a specific student and book.
     */
    void IssueBook();

    /**
     * Tries to return an issued book.
     */
    void ReturnBook();

    /**
     * Extends due date on an issued book.
     */
    void ExtendBook();

    /**
     * Adds a student to the library records.
     */
    void AddStudent();

    /**
     * View all books in the system.
     */
    void ViewAllBooks();

    /**
     * View all students in the system.
     */
    void ViewAllStudents();

    /**
     * Deletes a book's information from the system.
     */
    void DeleteBook();

    /**
     * Edit a book's information.
     */
    void EditBook();

    /**
     * Displays useful stats about the system.
     */
    void Stats();

    /**
     * Requests a random book by an author.
     */
    void RequestBook();

};


#endif //LIBRARYASSIGNMENT_APPRUNNER_H
