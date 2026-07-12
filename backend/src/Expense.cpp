#include "../include/Expense.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include<string>
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

// Default Constructor
Expense::Expense()
{
    id = 0;
    amount = 0.0;
    category = "";
    date = "";
    description = "";
    paymentMethod = "";
}

// Parameterized Constructor
Expense::Expense(int id, double amount, const string& category,
                 const string& date, const string& description,
                 const string& paymentMethod)
{
    this->id = id;
    this->amount = amount;
    this->category = category;
    this->date = date;
    this->description = description;
    this->paymentMethod = paymentMethod;
}

// Getters
int Expense::getId() const
{
    return id;
}


double Expense::getAmount() const
{
    return amount;
}

string Expense::getCategory() const
{
    return category;
}

string Expense::getDate() const
{
    return date;
}

string Expense::getDescription() const
{
    return description;
}

string Expense::getPaymentMethod() const
{
    return paymentMethod;
}

// Setters
void Expense::setId(int id)
{
    this->id = id;
}

void Expense::setAmount(double amount)
{
    this->amount = amount;
}

void Expense::setCategory(const string& category)
{
    this->category = category;
}

void Expense::setDate(const string& date)
{
    this->date = date;
}

void Expense::setDescription(const string& description)
{
    this->description = description;
}

void Expense::setPaymentMethod(const string& paymentMethod)
{
    this->paymentMethod = paymentMethod;
}

// Input Function
void Expense::input()
{
    cout << "\nEnter Expense ID: ";
    cin >> id;

    cout << "Enter Amount: ";
    cin >> amount;
    cin.ignore();

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter Description: ";
    getline(cin, description);

    cout << "Enter Payment Method: ";
    getline(cin, paymentMethod);
}

// Display Function
void Expense::display() const
{
    cout << left
         << setw(8) << id
         << setw(15) << date
         << setw(15) << category
         << setw(12) << amount
         << setw(15) << paymentMethod
         << setw(25) << description
         << endl;
}


string Expense::toFileString() const
{
    stringstream ss;

    ss << id << "|"
       << amount << "|"
       << category << "|"
       << date << "|"
       << description << "|"
       << paymentMethod;

    return ss.str();
}

Expense Expense::fromFileString(const string& line)
{
    stringstream ss(line);

    string idStr;
    string amountStr;
    string category;
    string date;
    string description;
    string paymentMethod;

    getline(ss, idStr, '|');
    getline(ss, amountStr, '|');
    getline(ss, category, '|');
    getline(ss, date, '|');
    getline(ss, description, '|');
    getline(ss, paymentMethod);

    return Expense(
        stoi(idStr),
        stod(amountStr),
        category,
        date,
        description,
        paymentMethod
    );
}

string Expense::toJson() const
{
    json j;

    j["id"] = id;
    j["amount"] = amount;
    j["category"] = category;
    j["date"] = date;
    j["description"] = description;
    j["paymentMethod"] = paymentMethod;

    return j.dump();
}