#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Expense.h"

class FileManager
{
public:
    static void saveExpenses(const std::vector<Expense>& expenses,
                             int userId);

    static std::vector<Expense> loadExpenses(int userId);
};

#endif