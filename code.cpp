#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
 
// Author class
class Author {
private:
    string name;
 
public:
    Author(const string& name)
        : name(name) {}
 
    string getName() const { return name; }
};
 
// Book class
class Book {
private:
    string title;
    Author author; // Use value instead of const reference
    int publicationYear;
 
public:
    Book(const string& title, const Author& author, int publicationYear)
        : title(title), author(author), publicationYear(publicationYear) {}
 
    // Copy constructor
    Book(const Book& other)
        : title(other.title), author(other.author), publicationYear(other.publicationYear) {}
 
    // Copy assignment operator
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            publicationYear = other.publicationYear;
        }
        return *this;
    }
 
    string getTitle() const { return title; }
    Author getAuthor() const { return author; }
    int getPublicationYear() const { return publicationYear; }
};
 
// Library class
class Library {
private:
    vector<Book> books;
 
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
 
    void removeBook(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.getTitle() == title;
            });
 
        if (it != books.end()) {
            books.erase(it);
        }
    }
 
    void listBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        }
        else {
            for (const auto& book : books) {
                cout << "Title: " << book.getTitle() << endl;
                cout << "Author: " << book.getAuthor().getName() << endl;
                cout << "Publication Year: " << book.getPublicationYear() << endl;
                cout << "-------------------" << endl;
            }
        }
    }
};
 
int main() {
    Library myLibrary;
    int choice;
 
    do {
        cout << "1. List Books" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch (choice) {
        case 1:
            myLibrary.listBooks();
            break;
        case 2:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << endl;
    } while (choice != 2);
 
    return 0;
}
