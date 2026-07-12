#include <iostream>
#include "../include/ExpenseManager.h"
#include "../include/httplib.h"
#include "../include/UserManager.h"
#include "../include/json.hpp"
#include <algorithm>

using namespace std;
using json = nlohmann::json;

int main()
{
    ExpenseManager manager(0);
    UserManager userManager;

    httplib::Server server;

    // Home Route
    server.Get("/", [](const httplib::Request&, httplib::Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");

        res.set_content(
            R"({
                "status":"success",
                "message":"Backend Connected"
            })",
            "application/json"
        );
    });

    // Get All Expenses
    server.Get("/expenses", [&](const httplib::Request&, httplib::Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");

        auto expenses = manager.getExpenses();

        string json = "[";

        for (size_t i = 0; i < expenses.size(); i++)
        {
            json += expenses[i].toJson();

            if (i != expenses.size() - 1)
                json += ",";
        }

        json += "]";

        res.set_content(json, "application/json");
    });


    server.Get("/dashboard", [&](const httplib::Request&, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");

    json data;

    data["totalExpense"] = manager.getTotalExpense();
    data["monthlyExpense"] = manager.getMonthlyExpense();
    data["highestExpense"] = manager.getHighestExpense();
    data["lowestExpense"] = manager.getLowestExpense();
    data["averageExpense"] = manager.getAverageExpense();
    data["totalRecords"] = manager.getExpenses().size();

    res.set_content(data.dump(), "application/json");
});

    // CORS Preflight
    server.Options("/expenses", [](const httplib::Request&, httplib::Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 200;
    });

server.Options("/login", [](const httplib::Request&, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.status = 200;
});



server.Options("/register", [](const httplib::Request&, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.status = 200;
});



    server.Options(R"(/expenses/(\d+))", [](const httplib::Request&, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.status = 200;
});



// ================= LOGIN =================

server.Post("/login", [&](const httplib::Request& req, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");

    json data = json::parse(req.body);

    string email = data["email"].get<string>();
    string password = data["password"].get<string>();

    if (userManager.login(email, password))
    {
        json response;

        response["success"] = true;
        response["message"] = "Login Successful";
        response["userId"] = userManager.getUserId(email);
        manager.loadUserExpenses(response["userId"]);

        res.set_content(response.dump(), "application/json");
    }
    else
    {
        json response;

        response["success"] = false;
        response["message"] = "Invalid Email or Password";

        res.set_content(response.dump(), "application/json");
    }
});



// ================= REGISTER =================

server.Post("/register", [&](const httplib::Request& req, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");

    json data = json::parse(req.body);

    string username = data["username"].get<string>();
    string email = data["email"].get<string>();
    string password = data["password"].get<string>();

    // Check duplicate email
    for (const auto& u : userManager.getUsers())
    {
        if (u.getEmail() == email)
        {
            json response;
            response["success"] = false;
            response["message"] = "Email already exists";

            res.set_content(response.dump(), "application/json");
            return;
        }
    }

    User user(
        userManager.getUsers().size() + 1,
        username,
        email,
        password
    );

    userManager.registerUser(user);

    json response;
    response["success"] = true;
    response["message"] = "Registration Successful";

    res.set_content(response.dump(), "application/json");
});



    // POST Expense
    server.Post("/expenses", [&](const httplib::Request& req, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");

    json data = json::parse(req.body);

    Expense expense;

    int nextId = manager.getExpenses().size() + 1;

    expense.setId(nextId);
    expense.setAmount(stod(data["amount"].get<string>()));
    expense.setCategory(data["category"].get<string>());
    expense.setDate(data["date"].get<string>());
    string desc = data["description"].get<string>();

    desc.erase(remove(desc.begin(), desc.end(), '\n'), desc.end());
    desc.erase(remove(desc.begin(), desc.end(), '\r'), desc.end());

    expense.setDescription(desc);
    
    expense.setPaymentMethod(data["paymentMethod"].get<string>());

    manager.addExpense(expense);

    res.set_content("Saved", "text/plain");
});


server.Delete(R"(/expenses/(\d+))", [&](const httplib::Request& req, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");

    int id = stoi(req.matches[1]);

    if (manager.deleteExpense(id))
    {
        res.set_content("Deleted", "text/plain");
    }
    else
    {
        res.status = 404;
        res.set_content("Expense Not Found", "text/plain");
    }
});


server.Put(R"(/expenses/(\d+))", [&](const httplib::Request& req, httplib::Response& res)
{
    res.set_header("Access-Control-Allow-Origin", "*");

    json data = json::parse(req.body);

    Expense expense;

    expense.setId(stoi(req.matches[1]));
    expense.setAmount(stod(data["amount"].get<string>()));
    expense.setCategory(data["category"].get<string>());
    expense.setDate(data["date"].get<string>());
    expense.setDescription(data["description"].get<string>());
    expense.setPaymentMethod(data["paymentMethod"].get<string>());

    if (manager.updateExpense(expense))
    {
        res.set_content("Updated", "text/plain");
    }
    else
    {
        res.status = 404;
        res.set_content("Expense Not Found", "text/plain");
    }
});


cout << "Server running at http://localhost:8080" << endl;

server.listen("0.0.0.0", 8080);

return 0;
}