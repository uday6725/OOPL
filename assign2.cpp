#include <iostream>
#include <cstring>
using namespace std;

class Book {
    char *author;
    char *title;
    char *publisher;
    float price;
    int stock;

public:
    // Constructor
    Book(const char *auth, const char *tit, const char *pub, float pr, int copies) {
        author = new char[strlen(auth) + 1];
        title = new char[strlen(tit) + 1];
        publisher = new char[strlen(pub) + 1];

        strcpy(author, auth);
        strcpy(title, tit);
        strcpy(publisher, pub);

        price = pr;
        stock = copies;
    }

    // Destructor
    ~Book() {
        delete[] author;
        delete[] title;
        delete[] publisher;
    }

    // Display book information
    void display() {
        cout << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPublisher: " << publisher
             << "\nPrice: $" << price
             << "\nStock: " << stock << "\n";
    }

    // Search for a book
    bool search(const char *searchTitle, const char *searchAuthor) {
        return (strcmp(title, searchTitle) == 0 && strcmp(author, searchAuthor) == 0);
    }

    // Buy a book
    void buy(int quantity) {
        if (quantity <= stock) {
            cout << "Total cost: $" << quantity * price << "\n";
            stock -= quantity;
        } else {
            cout << "Sorry, not enough stock.\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of books to add: ";
    cin >> n;

    // Dynamically allocate an array of Book pointers
    Book **books = new Book*[n];

    for (int i = 0; i < n; i++) {
        char title[50], author[50], publisher[200];
        float price;
        int copies;

        cout << "Enter the name of the author: ";
        cin >> author;
        cout << "Enter the title: ";
        cin >> title;
        cout << "Enter the name of the publisher: ";
        cin >> publisher;
        cout << "Enter the price: ";
        cin >> price;
        cout << "Enter the number of copies: ";
        cin >> copies;

        // Create a new Book object and store it in the array
        books[i] = new Book(author, title, publisher, price, copies);
    }

    char searchTitle[50], searchAuthor[50];
    cout << "Enter book title to search: ";
    cin >> searchTitle;
    cout << "Enter book author to search: ";
    cin >> searchAuthor;

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (books[i]->search(searchTitle, searchAuthor)) {
            books[i]->display();
            found = true;

            int numCopies;
            cout << "Enter number of copies to buy: ";
            cin >> numCopies;
            books[i]->buy(numCopies);
            break; // Exit the loop after finding the book
        }
    }

    if (!found) {
        cout << "Book not available.\n";
    }

    // Clean up
    for (int i = 0; i < n; i++) {
        delete books[i];
    }
    delete[] books;

    return 0;
}
