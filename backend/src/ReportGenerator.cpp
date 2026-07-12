#include "../include/ReportGenerator.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ReportGenerator::generateReport(const vector<Expense>& expenses)
{
    if (expenses.empty())
    {
        cout << "\nNo Expenses Found!\n";
        return;
    }

    double total = 0;

    for (const auto &expense : expenses)
    {
        total += expense.getAmount();
    }

    cout << "\n========================================\n";
    cout << "          EXPENSE REPORT\n";
    cout << "========================================\n";

    cout << "Total Expenses : " << expenses.size() << endl;
    cout << "Total Amount   : " << total << endl;
    cout << "Average Amount : " << total / expenses.size() << endl;

    cout << "========================================\n";
}


void ReportGenerator::monthlyReport(const vector<Expense>& expenses)
{
    if (expenses.empty())
    {
        cout << "\nNo Expenses Found!\n";
        return;
    }

    string month;

    cout << "\nEnter Month (YYYY-MM): ";
    cin >> month;

    double total = 0;
    int count = 0;

    for (const auto &expense : expenses)
    {
        if (expense.getDate().substr(0, 7) == month)
        {
            total += expense.getAmount();
            count++;
        }
    }

    cout << "\n========================================\n";
    cout << "         MONTHLY REPORT\n";
    cout << "========================================\n";
    cout << "Month          : " << month << endl;
    cout << "Total Expenses : " << count << endl;
    cout << "Total Amount   : " << total << endl;

    if (count > 0)
        cout << "Average Amount : " << total / count << endl;
    else
        cout << "Average Amount : 0\n";

    cout << "========================================\n";
}