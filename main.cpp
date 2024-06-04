#include "login_register.cpp"
#include "delivery_locations.cpp"
#include "order_delivery.cpp"
#include "book_cart.cpp"


//Login and Register sections helping functions
void printHeader(const string &title)
{
    std::cout << "\033[31m";
    cout << "\n===========================================\n";
    cout << setw(25) << title << endl; // set width
    cout << "===========================================\n";
    std::cout << "\033[0m";
}

void printLibraryInteraction()
{
    std::cout << "\033[1;34m" // blue

              << R"(
       O
      /|\
      / \
    )" << "\033[0m"           // Reset color
              << "\033[1;32m" // green
              << R"(
       __
      /    \
     | BOOK |
      \____/
    )" << "\033[0m"           // Reset color
              << "\033[1;31m" // red
              << R"(
          O
         /|\
         / \
    )" << "\033[0m";          // Reset color
}

void printSuccessfulLogin()
{
    std::cout << "\033[1;32m"; // green
    std::cout << R"(
          O
         \|/
          |
         / \
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[1;34m"; // blue
    std::cout << R"(
      *     *
         *
  *     *     *
         *
      *     *
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[0m"; // Reset color
}

void printFailedLogin()
{
    std::cout << "\033[1;31m"; // red
    std::cout << R"(
        ___
       /     \
      |       |
      |  O O  |
      |   ^   |
      |  '-'  |
       \_____/
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[1;33m"; // yellow
    std::cout << "\nLogin Failed. Please try again.\n";
    std::cout << "\033[0m"; // Reset color
}

bool authenticateAdmin(string username, string password)
{
    return (username == "ADMIN" && password == "ADMIN");
}

void printAdminMenu()
{
    printHeader("Admin Menu");
    cout << "Choose an option:\n";
    cout << "1. View All Users\n";
    cout << "2. Delivey Page \n";
    cout << "3. Modify Delivery Locations : " << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void viewAllUsers(const unordered_map<string, string> &userCredentials)
{
    printHeader("All Registered Users");
    for (const auto &pair : userCredentials)
    {
        cout << "Username: " << pair.first << endl;
    }
    cout << "Press any key to return to the main menu...";
    cin.ignore();
    cin.get();
}

string login(string &type)
{
    system("clear") ;
    string filename = "user_credentials.txt";

    // Initialize the library with existing user credentials
    Library library(filename);

    std::cout << "\033[1;33m";
    cout << "Welcome to the Library Management System!\n";
    std::cout << "\033[0m"; // Reset color

    int choice;
    string username, password;
    bool exit = false; // Control variable to exit the loop

    while (!exit)
    {
        system("clear") ;
        printLibraryInteraction();
        printHeader("Main Menu");
        cout << "Choose an option:\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Admin Login\n";
        cout << "Enter your choice (or any other key to exit): ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Login
            printHeader("Login");
            cout << "Please log in.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (library.authenticateUser(username, password))
            {
                type = "user";
                std::cout << "\033[1;33m";
                cout << "\nLogin successful. Welcome, " << username << "!\n";
                printSuccessfulLogin();
                exit = true; // Set exit to true to exit the loop
            }
            else
            {
                std::cout << "\033[1;33m";
                cout << "\nInvalid username or password. Please try again.\n";
                printFailedLogin();
            }
            break;

        case 2: // Registration
            printHeader("Registration");
            cout << "Please register.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            type = "user";
            library.registerUser(username, password);
            break;
        case 3: // Admin Login
            printHeader("Admin Login");
            cout << "Please log in as admin.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (authenticateAdmin(username, password))
            {
                cout << "Admin login successfull" << endl;
                type = "admin";
                exit = true;
                break;
            }
            else
            {
                std::cout << "\033[1;33m";
                cout << "\nInvalid admin credentials. Please try again.\n";
                printFailedLogin();
            }
            break;

        default:
            std::cout << "\033[1;33m";
            cout << "\nThank you for using the Library Management System. Goodbye!\n";
            exit = true; // Set exit to true to exit the loop
            break;
        }
    }

    return username;
}

//Functions part of Showing Book list

// Assuming other parts of the code are the same

void showTheBookList(Stack &cart, int &price)
{
    Bookshop shop;
    // Display available books
    shop.displayBooks();

    // Let the user select books from the shop
    if (!cart.sizeIs())
        cout << "\nEnter the number beside the book you want to add to the cart (1 to " << shop.getNumBooks() << "), or \"b\" to go back to home page: ";
    else
        cout << "\nEnter the number beside the book you want to add to the cart (1 to " << shop.getNumBooks() << "), or 0 if done adding books to the cart: ";

    int choice = -1;
    while (true)
    {
        cin >> choice;
        // Take input and clear any errors in the input stream
        if (choice == 0)
            break;

        if (choice < 1 || choice > shop.getNumBooks())
        {
            cout << "Invalid book index! Enter a valid number: ";
            continue;
        }

        Book selectedBook = shop.getBook(choice - 1);
        if (selectedBook.title != "")
        {
            cart.push(selectedBook);
            price += selectedBook.price;
            cout << "\n-> Book \"" << selectedBook.title << "\" added to cart.\n"
                 << endl;
        }
        cout << "Enter the number beside the next book you want to add, or 0 if done adding books to the cart: ";
    }

    cout <<YELLOW<<GREEN_BG<<"Total Books price is : " << price << endl;
    cout<<RESET<<RESET_BG<<endl;

    if (cart.sizeIs() == 0)
    {
        return;
    }

    cout << endl;

    // Display books in the cart
    cart.displayCart();

    // Ask the user if they want to delete the entire cart
    char deleteChoice;
    cout << "Do you want to delete the entire cart? (y/n): ";
    cin >> deleteChoice;

    if (deleteChoice == 'y' || deleteChoice == 'Y')
    {
        // Delete the entire cart
        cart.deleteCart();
        cout << "\nAll books are deleted from the cart." << endl;
    }
    else
    {
        cout << "\nCart deletion canceled. Continuing with the cart." << endl;
        cout << "Enter \"y\" to go to the Delivery page or \"m\" to go back: ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            system("clear");
            return;
        }
        else
        {
            cout << "Do you want to keep the list unchanged \"y\" to yes: ";
            char c;
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
                showTheBookList(cart, price);
            }
            else
            {
                price = 0;
                cart.deleteCart();
                showTheBookList(cart, price);
            }
        }
        system("clear");
    }
}





//Functions part of order delivery

void readfromFile(QueueLinked<delivery> &queuelist)
{
    ifstream readFile;
    string line;
again:
    readFile.open(fileName);

    if (!readFile)
    {
        cout << "File could not be opened!" << endl;
        ofstream writeFile(fileName);
        writeFile.close();
        cout << "File created successfully" << endl;
        goto again;
    }
    while (getline(readFile, line))
    {
        if (line == " ")
        {
            break;
        }
        string Name = line;
        string Address;
        string Amount;

        getline(readFile, Address);
        getline(readFile, Amount);
        delivery del(Name, Address, Amount);
        int a = 0;
        while (getline(readFile, line))
        {
            if (line == "--------------------------------------------------------")
            {
                break;
            }
            del.booklist[a] = line;
            a++;
        }
        queuelist.Enqueue(del);
    }

    readFile.close();

    // cout << "Data read from the file successfully." << endl;
}

void addToFile(delivery del)
{
    ofstream appendFile;
    appendFile.open(fileName, ios::app);

    if (!appendFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }

    appendFile << del.getName() << endl;
    appendFile << del.getAddress() << endl;
    appendFile << del.getMoneyAmount() << endl;
    string book;
    for (int i = 0; i < 10; i++)
    {
        string book = del.booklist[i];
        if (book == "Empty")
        {
            break;
        }
        else
        {
            appendFile << book << endl;
        }
    }
    appendFile << "--------------------------------------------------------" << endl;

    appendFile.close();

    // cout << "Data written to the file successfully." << endl;
}

void printDeliveries()
{
    QueueLinked<delivery> deliveries;
    readfromFile(deliveries);
    cout << "\tPending Deliveries :\n"
         << endl;
    while (!deliveries.IsEmpty())
    {
        delivery del;
        deliveries.Dequeue(del);
        if (del.getName() == " ")
        {
            cout << "\n\t--------- No Deliveries ---------" << endl;
        }
        else
        {
            cout << endl;
            cout << "Name: " << del.getName() << endl;
            cout << "Address: " << del.getAddress() << endl;
            cout << "Money Amount: " << del.getMoneyAmount() << endl;
            cout << "Book List:" << endl;
            for (int i = 0; i < 10; i++)
            {
                string book = del.booklist[i];
                if (book == "Empty")
                {
                    break;
                }
                cout << (i + 1) << ". " << book << endl;
            }
            cout << endl;
        }
    }

    char c;
    cin >> c;
}

void clearAllDeliveries()
{
    ofstream writeFile;
    writeFile.open(fileName);
    if (!writeFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }
    writeFile << "";
    writeFile.close();
}

void writeToFile(QueueLinked<delivery> &deliveries)
{
    ofstream writeFile;
    writeFile.open(fileName);

    if (!writeFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }

    while (!deliveries.IsEmpty())
    {
        delivery del;
        deliveries.Dequeue(del);
        writeFile << del.getName() << endl;
        writeFile << del.getAddress() << endl;
        writeFile << del.getMoneyAmount() << endl;
        string book;
        for (int i = 0; i < 10; i++)
        {
            string book = del.booklist[i];
            if (book == "Empty")
            {
                break;
            }
            else
            {
                writeFile << book << endl;
            }
        }
        writeFile << "--------------------------------------------------------" << endl;
    }

    writeFile.close();

    // cout << "Data written to the file successfully." << endl;
}

void completeDelivery()
{
    system("clear");
    QueueLinked<delivery> deliveryqueue;
    readfromFile(deliveryqueue);
    delivery del;
    deliveryqueue.Dequeue(del);
    if (del.getName() == " ")
    {
        cout << "\n\t--------- No Deliveries ---------" << endl;
    }
    else
    {
        // cout<<"\nDequeued : \n";
        // cout<<del.getName()<<endl;
        // cout<<del.getAddress()<<endl;
        // cout<<del.getMoneyAmount()<<endl;
        writeToFile(deliveryqueue);
        cout << "\n\t--------- First Delivery Completed ---------" << endl;
        char c ;
        getchar() ;
        getchar() ;
    }
}

void adminMenu()
{
    while (true)
    {
        system("clear");
        cout << "\tChoose from below :" << endl;
        cout << "\t1. View Delivery List" << endl;
        cout << "\t2. Complete the latest delivery" << endl;
        cout << "\t3. Clear Delivery List" << endl;
        cout << "\t4. Go Back" << endl;
        cout << "Choose -> ";
        bool shesh = false;
        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:
        {
            system("clear");
            printDeliveries();
            system("pause");
            break;
        }
        case 2:
        {
            completeDelivery();
            system("pause");
            break;
        }
        case 3:
        {
            system("clear");
            clearAllDeliveries();
            cout << "\n\t--------- All Deliveries Cleared ---------" << endl;
            system("pause");
            break;
        }
        case 4:
        {
            shesh = true;
            break;
        }
        default:
        {
            cout << "\n\t--------- Invalid Input ---------" << endl;
            break;
        }
        }

        if (shesh)
        {
            break;
        }
    }
}

int main()
{
    LocationDetails locations;
    Stack cart;
    system("clear");
    string type;
    string username = login(type);
    if (type == "user")
    {
        int price = 0;
        cout << "Here user name is : " << username << endl;
        showTheBookList(cart, price);
        cart.displayCart();
        if (cart.sizeIs() != 0)
        {
            cout << RESET << endl;
            string location = locations.getDeliveryPrice(price);
            cout << location << endl;
            ofstream fout("delivery.txt", ios_base::out | ios_base::app);
            Stack cart2;
            while (cart.sizeIs())
            {
                Book b = cart.top();
                cart2.push(b);
                cart.pop();
            }
            fout << username << "\n"
                 << location << "\n"
                 << price << endl;
            fout.close();
            cart2.displayCart();
            while (cart2.sizeIs())
            {
                ofstream foout("delivery.txt", ios_base::out | ios_base::app);
                Book b = cart2.top();
                cart2.pop();
                foout << b.title << " " << b.author << " " << b.price << endl;
                foout.close();
            }
            ofstream ffout("delivery.txt", ios_base::out | ios_base::app);
            ffout << "--------------------------------------------------------" << endl;
            ffout.close();
            cout << WHITE << endl;
        }
    }
    else if (type == "admin")
    {
        string filename = "user_credentials.txt";
        LocationDetails l;

        // Initialize the library with existing user credentials
        Library library(filename);
        int choice;
        std::cout << "\033[1;33m";
        cout << "\nAdmin login successful. Welcome, " << username << "!\n";
        printSuccessfulLogin();

        bool adminExit = false;
        while (!adminExit)
        {
            printAdminMenu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                viewAllUsers(library.getUserCredentials());
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                l.areaInput();
                break;
            case 4:
                adminExit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    return 0;
}
