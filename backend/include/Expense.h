#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

class Expense
{
private:
    int id;
    double amount;
    std::string category;
    std::string date;
    std::string description;
    std::string paymentMethod;

public:
    // Constructors
    Expense();
    Expense(int id, double amount, const std::string& category,
            const std::string& date, const std::string& description,
            const std::string& paymentMethod);
    std::string toFileString() const;
    static Expense fromFileString(const std::string& line);

    // Getters
    int getId() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    std::string getDescription() const;
    std::string getPaymentMethod() const;


    std::string toJson() const;

    // Setters
    void setId(int id);
    void setAmount(double amount);
    void setCategory(const std::string& category);
    void setDate(const std::string& date);
    void setDescription(const std::string& description);
    void setPaymentMethod(const std::string& paymentMethod);

    // Utility Functions
    void input();
    void display() const;
    
};

#endif