#include <iostream>
#include <fstream> // File
#include <string>
#include <unordered_map> // HashMap
#include <iomanip>       // For setw() -- setwidth (25)



using namespace std;

class Library
{
private:
    unordered_map<string, string> userCredentials; // Declaring Hash map
    string filename;

public:
    // Constructor
    Library(string filename) : filename(filename)
    {
        loadCredentials(); // Load existing user credentials from file
    }

    void registerUser(string username, string password)
    {
        if (userCredentials.find(username) == userCredentials.end()) // CHECK: USERNAME EXIST KORE NAKI NA
        {
            userCredentials[username] = password;
            std::cout << "\033[1;33m";
            cout << "\nUser registered successfully!\n";
            saveCredentials(); // Save updated user credentials to file
        }
        else
        {
            std::cout << "\033[1;33m";
            cout << "\nUsername already exists! Please choose a different username.\n";
        }
    }

    bool authenticateUser(string username, string password)
    {
        auto it = userCredentials.find(username); // auto: as 'it' will return an iterator type / we don't know the exact datatype
        if (it != userCredentials.end() && it->second == password)
        {
            return true;
        }
        return false;
    }

    const unordered_map<string, string> &getUserCredentials() const
    {
        return userCredentials;
    }

private:
    // This function ensures that when the program starts, it has the existing user credentials loaded into memory from the file, allowing for authentication and registration functionalities to work properly
    void loadCredentials()
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string username, password;
            while (file >> username >> password) // Reading Username & password from file.
            {
                userCredentials[username] = password; // If username(key) already exists in the map, its corresponding value (password) is updated.
            }
            file.close();
        }
        else
        {
            cout << "----"; // cout << "Unable to open file. Creating a new file.\n";
        }
    }

    void saveCredentials()
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &pair : userCredentials)
            {
                file << pair.first << " " << pair.second << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file for writing.\n";
        }
    }
};


