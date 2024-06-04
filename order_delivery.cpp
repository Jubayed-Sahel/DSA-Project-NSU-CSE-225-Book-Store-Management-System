#include <iostream>
#include "queuelinked.cpp"
#include <fstream>
#include <string>


using namespace std;
const string fileName = "delivery.txt";

class delivery
{
private:
    string name;
    string address;
    string money_amount;

public:
    string booklist[10];
    delivery()
    {
        name = " ";
        address = " ";
        money_amount = "0.0";
        for (int i = 0; i < 10; i++)
        {
            booklist[i] = "Empty";
        }
    }

    delivery(string Name, string Address, string Money_amount)
    {
        name = Name;
        address = Address;
        money_amount = Money_amount;
        for (int i = 0; i < 10; i++)
        {
            booklist[i] = "Empty";
        }
    }

    string getName()
    {
        return name;
    }

    string getAddress()
    {
        return address;
    }

    string getMoneyAmount()
    {
        return money_amount;
    }

    void setName(string Name)
    {
        name = Name;
    }

    void setAddress(string Address)
    {
        address = Address;
    }
};
