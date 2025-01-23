#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Struct Definitions
struct Book {
    int id;
    char title[100];
    char author[50];
    char isbn[20];
    bool isAvailable;
};

struct User {
    int id;
    char name[50];
    char contact[50];
};

struct Loan {
    int loanId;
    int userId;
    int bookId;
    char issueDate[20];
    char dueDate[20];
    bool isReturned;
};

// Function Prototypes
void addBook();
void viewBooks();
void addUser();
void viewUsers();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                addUser();
                break;
            case 4:
                viewUsers();
                break;
            case 0:
                cout << "Exiting the Library Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// Function Definitions

void displayMenu() {
    cout << "\n--- Library Management System ---\n";
    cout << "1. Add Book\n";
    cout << "2. View All Books\n";
    cout << "3. Add User\n";
    cout << "4. View All Users\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void addBook() {
    Book book;
    cout << "\nEnter Book ID: ";
    cin >> book.id;
    cin.ignore(); // To handle newline after cin
    cout << "Enter Book Title: ";
    cin.getline(book.title, 100);
    cout << "Enter Author Name: ";
    cin.getline(book.author, 50);
    cout << "Enter ISBN: ";
    cin.getline(book.isbn, 20);
    book.isAvailable = true;

    ofstream outFile("data/books.dat", ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&book), sizeof(Book));
    outFile.close();
    cout << "Book added successfully.\n";
}

void viewBooks() {
    ifstream inFile("data/books.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    Book book;
    cout << "\n--- Book Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        cout << "ID: " << book.id << "\n"
             << "Title: " << book.title << "\n"
             << "Author: " << book.author << "\n"
             << "ISBN: " << book.isbn << "\n"
             << "Status: " << (book.isAvailable ? "Available" : "Issued") << "\n\n";
    }
    inFile.close();
}

void addUser() {
    User user;
    cout << "\nEnter User ID: ";
    cin >> user.id;
    cin.ignore(); // To handle newline after cin
    cout << "Enter User Name: ";
    cin.getline(user.name, 50);
    cout << "Enter Contact Information: ";
    cin.getline(user.contact, 50);

    ofstream outFile("data/users.dat", ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&user), sizeof(User));
    outFile.close();
    cout << "User added successfully.\n";
}

void viewUsers() {
    ifstream inFile("data/users.dat", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    User user;
    cout << "\n--- User Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        cout << "ID: " << user.id << "\n"
             << "Name: " << user.name << "\n"
             << "Contact: " << user.contact << "\n\n";
    }
    inFile.close();
}
