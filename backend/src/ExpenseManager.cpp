#include "../include/ExpenseManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

ExpenseManager::ExpenseManager(int userId)
{
    this->userId = userId;

    expenses = FileManager::loadExpenses(userId);
}


void ExpenseManager::addExpense()
{
    Expense expense;

    expense.input();

    expenses.push_back(expense);

    FileManager::saveExpenses(expenses, userId);

    cout << "\nExpense Added Successfully!\n";
}


void ExpenseManager::addExpense(const Expense& expense)
{
    expenses.push_back(expense);

    FileManager::saveExpenses(expenses, userId);
}


void ExpenseManager::viewExpenses() const
{
    if(expenses.empty())
    {
        cout<<"\nNo Expenses Found!\n";
        return;
    }

    cout<<"\n=====================================================================================\n";

    cout<<left
        <<setw(8)<<"ID"
        <<setw(15)<<"Date"
        <<setw(15)<<"Category"
        <<setw(12)<<"Amount"
        <<setw(15)<<"Payment"
        <<setw(25)<<"Description"
        <<endl;

    cout<<"=====================================================================================\n";

    for(const auto &expense : expenses)
    {
        expense.display();
    }

    cout<<"=====================================================================================\n";
}


void ExpenseManager::editExpense()
{
    int id;

    cout << "\nEnter Expense ID to Edit: ";
    cin >> id;

    bool found = false;

    for (auto &expense : expenses)
    {
        if (expense.getId() == id)
        {
            found = true;

            cout << "\nExpense Found!\n";

            double amount;
            string category;
            string date;
            string description;
            string paymentMethod;

            cout << "Enter New Amount: ";
            cin >> amount;
            cin.ignore();

            cout << "Enter New Category: ";
            getline(cin, category);

            cout << "Enter New Date (YYYY-MM-DD): ";
            getline(cin, date);

            cout << "Enter New Description: ";
            getline(cin, description);

            cout << "Enter New Payment Method: ";
            getline(cin, paymentMethod);

            expense.setAmount(amount);
            expense.setCategory(category);
            expense.setDate(date);
            expense.setDescription(description);
            expense.setPaymentMethod(paymentMethod);

            FileManager::saveExpenses(expenses, userId);

            cout << "\nExpense Updated Successfully!\n";

            break;
        }
    }

    if (!found)
    {
        cout << "\nExpense Not Found!\n";
    }
}

void ExpenseManager::deleteExpense()
{
    int id;

    cout << "\nEnter Expense ID to Delete: ";
    cin >> id;

    bool found = false;

    for (auto it = expenses.begin(); it != expenses.end(); it++)
    {
        if (it->getId() == id)
        {
            expenses.erase(it);

            FileManager::saveExpenses(expenses, userId);

            cout << "\nExpense Deleted Successfully!\n";

            found = true;

            break;
        }
    }

    if (!found)
    {
        cout << "\nExpense Not Found!\n";
    }
}


bool ExpenseManager::deleteExpense(int id)
{
    for (auto it = expenses.begin(); it != expenses.end(); it++)
    {
        if (it->getId() == id)
        {
            expenses.erase(it);

            FileManager::saveExpenses(expenses, userId);

            return true;
        }
    }

    return false;
}


bool ExpenseManager::updateExpense(const Expense& expense)
{
    for (auto &e : expenses)
    {
        if (e.getId() == expense.getId())
        {
            e = expense;

            FileManager::saveExpenses(expenses, userId);

            return true;
        }
    }

    return false;
}


void ExpenseManager::searchById()
{
    int id;

    cout << "\nEnter Expense ID to Search: ";
    cin >> id;

    bool found = false;

    for (const auto &expense : expenses)
    {
        if (expense.getId() == id)
        {
            cout << "\nExpense Found!\n";

            cout << "\n=====================================================================================\n";

            cout << left
                 << setw(8)  << "ID"
                 << setw(15) << "Date"
                 << setw(15) << "Category"
                 << setw(12) << "Amount"
                 << setw(15) << "Payment"
                 << setw(25) << "Description"
                 << endl;

            cout << "=====================================================================================\n";

            expense.display();

            cout << "=====================================================================================\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nExpense Not Found!\n";
    }
}

void ExpenseManager::searchByCategory()
{
    string category;
    bool found = false;

    cout << "\nEnter Category: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, category);

    cout << "\n=====================================================================================\n";

    cout << left
         << setw(8)  << "ID"
         << setw(15) << "Date"
         << setw(15) << "Category"
         << setw(12) << "Amount"
         << setw(15) << "Payment"
         << setw(25) << "Description"
         << endl;

    cout << "=====================================================================================\n";

    for (const auto &expense : expenses)
    {
        if (expense.getCategory() == category)
        {
            expense.display();
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo Expense Found in this Category.\n";
    }

    cout << "=====================================================================================\n";
}


void ExpenseManager::binarySearchById()
{
    int id;

    cout << "\nEnter Expense ID to Search: ";
    cin >> id;

    vector<Expense> temp = expenses;

    sort(temp.begin(), temp.end(),
        [](const Expense &a, const Expense &b)
        {
            return a.getId() < b.getId();
        });

    int left = 0;
    int right = temp.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (temp[mid].getId() == id)
        {
            cout << "\nExpense Found!\n";

            cout << "\n=====================================================================================\n";

            cout << left
                 << setw(8) << "ID"
                 << setw(15) << "Date"
                 << setw(15) << "Category"
                 << setw(12) << "Amount"
                 << setw(15) << "Payment"
                 << setw(25) << "Description"
                 << endl;

            cout << "=====================================================================================\n";

            temp[mid].display();

            cout << "=====================================================================================\n";

            return;
        }

        else if (temp[mid].getId() < id)
        {
            left = mid + 1;
        }

        else
        {
            right = mid - 1;
        }
    }

    cout << "\nExpense Not Found!\n";
}


void ExpenseManager::sortExpenses()
{
    sort(expenses.begin(), expenses.end(),
        [](const Expense &a, const Expense &b)
        {
            return a.getAmount() < b.getAmount();
        });

    FileManager::saveExpenses(expenses, userId);

    cout << "\nExpenses Sorted Successfully (Amount - Ascending).\n";

    viewExpenses();
}


void ExpenseManager::generateReport()
{
    ReportGenerator::generateReport(expenses);
}

void ExpenseManager::monthlyReport()
{
    ReportGenerator::monthlyReport(expenses);
}


const std::vector<Expense>& ExpenseManager::getExpenses() const
{
    return expenses;
}


double ExpenseManager::getTotalExpense() const
{
    double total = 0;

    for (const auto &expense : expenses)
    {
        total += expense.getAmount();
    }

    return total;
}


double ExpenseManager::getHighestExpense() const
{
    if (expenses.empty())
        return 0;

    double highest = expenses[0].getAmount();

    for (const auto &expense : expenses)
    {
        if (expense.getAmount() > highest)
            highest = expense.getAmount();
    }

    return highest;
}


double ExpenseManager::getLowestExpense() const
{
    if (expenses.empty())
        return 0;

    double lowest = expenses[0].getAmount();

    for (const auto &expense : expenses)
    {
        if (expense.getAmount() < lowest)
            lowest = expense.getAmount();
    }

    return lowest;
}


double ExpenseManager::getMonthlyExpense() const
{
    double total = 0;

    time_t now = time(nullptr);
    tm *current = localtime(&now);

    int currentMonth = current->tm_mon + 1;
    int currentYear = current->tm_year + 1900;

    for (const auto &expense : expenses)
    {
        string date = expense.getDate();

        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));

        if (year == currentYear && month == currentMonth)
        {
            total += expense.getAmount();
        }
    }

    return total;
}


double ExpenseManager::getAverageExpense() const
{
    if (expenses.empty())
        return 0;

    return getTotalExpense() / expenses.size();
}

void ExpenseManager::loadUserExpenses(int userId)
{
    this->userId = userId;

    expenses = FileManager::loadExpenses(userId);
}