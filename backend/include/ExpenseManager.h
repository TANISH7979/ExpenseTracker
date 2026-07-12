#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <vector>
#include "Expense.h"
#include "FileManager.h"
#include "ReportGenerator.h"

class ExpenseManager
{
private:
    std::vector<Expense> expenses;
    int userId;

public:
    ExpenseManager(int userId);

    void addExpense();
    void addExpense(const Expense& expense);
    void viewExpenses() const;
    void editExpense();
    bool updateExpense(const Expense& expense);
    void deleteExpense();
    bool deleteExpense(int id);
    void searchById();
    void searchByCategory();
    void sortExpenses();
    void binarySearchById();

    void generateReport();
    void monthlyReport();

    const std::vector<Expense>& getExpenses() const;

    double getTotalExpense() const;
    double getMonthlyExpense() const;
    double getHighestExpense() const;
    double getLowestExpense() const;
    double getAverageExpense() const;
    void loadUserExpenses(int userId);
};

#endif