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
    string title, authorName, publicationYearStr;
    int publicationYear;
 
    do {
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. List Books" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author name: ";
            getline(cin, authorName);
            cout << "Enter publication year: ";
            cin >> publicationYearStr;
            try {
                publicationYear = stoi(publicationYearStr);
                if (publicationYear <= 0) {
                    throw invalid_argument("Publication year must be a positive integer.");
                }
                Author author(authorName);
                Book book(title, author, publicationYear);
                myLibrary.addBook(book);
            }
            catch (const invalid_argument& e) {
                cout << "Invalid input: " << e.what() << endl;
            }
            break;
        case 2:
            cout << "Enter book title to remove: ";
            cin.ignore();
            getline(cin, title);
            if (!title.empty()) {
                myLibrary.removeBook(title);
            }
            else {
                cout << "Empty book title entered. Please try again." << endl;
            }
            break;
        case 3:
            myLibrary.listBooks();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << endl;
    } while (choice != 4);
 
    return 0;
}
