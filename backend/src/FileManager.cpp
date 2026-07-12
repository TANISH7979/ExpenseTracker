#include "../include/FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void FileManager::saveExpenses(const vector<Expense>& expenses, int userId)
{
    string filename = "backend/data/expenses_" + to_string(userId) + ".txt";

    ofstream file(filename);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    for (const auto& expense : expenses)
    {
        file << expense.toFileString() << endl;
    }

    file.close();
}

vector<Expense> FileManager::loadExpenses(int userId)
{
    vector<Expense> expenses;

    string filename = "backend/data/expenses_" + to_string(userId) + ".txt";

    ifstream file(filename);

    if (!file)
    {
        return expenses;
    }

    string line;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            expenses.push_back(Expense::fromFileString(line));
        }
    }

    file.close();

    return expenses;
}