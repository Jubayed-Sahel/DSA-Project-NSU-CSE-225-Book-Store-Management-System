#include <iostream>
#include <string>
#include <vector>


using namespace std;

// Structure for a book
struct Book
{
    string title;
    string author;
    int price;
    // Constructor
    Book(string t, string a, int p) : title(t), author(a), price(p) {}
};

// Class for a bookshop
class Bookshop
{
private:
    vector<Book> books;

public:
    // Constructor
    Bookshop()
    {
        // Initialize with some books
        books.push_back(Book("Pride and Prejudice", "      by--> Jane Austen", 110));
        books.push_back(Book("Great Expectations", "       by--> Charles Dickens ", 130));
        books.push_back(Book("The Shining", "              by--> Stephen King", 200));
        books.push_back(Book("To the Lighthouse", "        by--> Virginia Woolf ", 250));
        books.push_back(Book("War and Peace", "            by--> Leo Tolstoy", 220));
        books.push_back(Book("Crime and Punishment", "     by--> Fyodor Dostoevsky ", 205));
        books.push_back(Book("Norwegian Wood", "           by--> Haruki Murakami ", 215));
        books.push_back(Book("The Unproposed Guy", "       by--> Bhavik Sarkhedi ", 320));
        books.push_back(Book("Gitanjali", "                by--> Rabindranath Tagore", 180));
    }

    // Function to display all books in the shop
    void displayBooks()
    {
        cout << "\t\t\t\tBOOK LIST" << endl;
        cout << "\t\t------------------------------------------------\n";
        cout << endl;
        int index = 1;
        for (const Book &book : books)
        {
            cout << index << ". Title: " << book.title << " " << book.author << ", Price: " << book.price << endl;
            index++;
        }
    }

    // Function to get a book by index
    Book getBook(int index)
    {
        if (index >= 0 && index < books.size())
            return books[index];
        else
        {
            cerr << "\n-> Invalid book index!\n"
                 << endl;
            return Book("", "", 0.0); // Return an empty book if index is invalid
        }
    }

    // Function to get the total number of books in the shop
    int getNumBooks()
    {
        return books.size();
    }
};

// Structure for a node in the doubly linked list
struct Node
{
    Book book;
    Node *next;
    Node *prev;
    // Constructor
    Node(Book b) : book(b), next(nullptr), prev(nullptr) {}
};

// Class for doubly linked list
class DoublyLinkedList
{
private:
    Node *head;
    Node *tail;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Function to add a book to the end of the list
    void addToEnd(Book book)
    {
        Node *newNode = new Node(book);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to remove the last book from the list
    void removeFromEnd()
    {
        if (!tail)
        {
            cerr << "\n-> Cart is empty! Cannot remove.\n"
                 << endl;
            return;
        }
        Node *temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
    }

    // Function to display all books in the list
    void displayBooks()
    {
        cout << endl;
        Node *current = head;
        while (current)
        {
            cout << "Title: " << current->book.title << " " << current->book.author << ", Price: " << current->book.price << endl;
            cout << endl;
            current = current->next;
        }
    }

    // Function to get the last book from the list
    Book getLastBook()
    {
        if (tail)
            return tail->book;
        else
        {
            cerr << "\n-> Cart is empty!\n"
                 << endl;
            return Book("", "", 0.0);
        }
    }

    // Function to delete all books from the list
    void deleteAll()
    {
        Node *current = head;
        while (current)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    // Destructor
    ~DoublyLinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Class for stack using Doubly Linked List
class Stack
{
private:
    int size = 0;
    DoublyLinkedList list;

public:
    void push(Book book)
    {
        list.addToEnd(book);
        size++;
    }

    void pop()
    {
        list.removeFromEnd();
        size--;
    }

    int sizeIs()
    {
        return size;
    }

    bool isEmpty()
    {
        return list.isEmpty();
    }

    void displayCart()
    {
        cout << "\t\t\t------>  Books in the cart: <-------" << endl;
        list.displayBooks();
    }

    Book top()
    {
        return list.getLastBook();
    }

    void deleteCart()
    {
        list.deleteAll();
    }
};
