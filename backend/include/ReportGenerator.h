#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include "Expense.h"

class ReportGenerator
{
public:
    static void generateReport(const std::vector<Expense>& expenses);
    static void monthlyReport(const std::vector<Expense>& expenses);
};

#endif