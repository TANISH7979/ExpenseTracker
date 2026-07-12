let editingId = null;
let allExpenses = [];

let currentSearch = "";
let currentSort = "";


function loadDashboard()
{
    fetch("http://localhost:8080/dashboard")
    .then(response => response.json())
    .then(data => {

        document.getElementById("totalExpense").innerText =
            "₹" + data.totalExpense;

        document.getElementById("monthlyExpense").innerText =
            "₹" + data.monthlyExpense;

        document.getElementById("heroMonthlyExpense").innerText =
        "₹" + data.monthlyExpense;

        document.getElementById("heroMonthlyText").innerText =
            data.totalRecords + " Expenses Added This Month";

        document.getElementById("totalRecords").innerText =
            data.totalRecords;

        document.getElementById("budgetLeft").innerText =
            "₹0";

        document.getElementById("highestExpense").innerText =
            "₹" + data.highestExpense;

        document.getElementById("lowestExpense").innerText =
            "₹" + data.lowestExpense;

        document.getElementById("averageExpense").innerText =
            "₹" + Number(data.averageExpense).toFixed(2);

    })
    .catch(error => console.log(error));
}

function loadExpenses()
{
    fetch("http://localhost:8080/expenses")
    .then(response => response.json())
    .then(data => {

        allExpenses = data;

        applyFilters();

    })
    .catch(error => console.log(error));
}


loadExpenses();
loadDashboard();

document.getElementById("addExpenseBtn").addEventListener("click", () => {

    const expense = {

        amount: document.getElementById("amount").value,
        category: document.getElementById("category").value,
        date: document.getElementById("date").value,
        paymentMethod: document.getElementById("paymentMethod").value,
        description: document.getElementById("description").value

    };

    if (editingId !== null)
{
    fetch(`http://localhost:8080/expenses/${editingId}`, {

        method: "PUT",

        headers: {
            "Content-Type": "application/json"
        },

        body: JSON.stringify(expense)

    })
    .then(response => response.text())
    .then(data => {

        console.log(data);

        editingId = null;

        loadExpenses();
        loadDashboard();

        document.getElementById("formTitle").innerText = "Add New Expense";
        document.getElementById("buttonText").innerText = "Add Expense";

        document.getElementById("amount").value = "";
        document.getElementById("category").selectedIndex = 0;
        document.getElementById("date").value = "";
        document.getElementById("paymentMethod").selectedIndex = 0;
        document.getElementById("description").value = "";

    })
    .catch(error => console.log(error));

    return;
}

    fetch("http://localhost:8080/expenses", {

        method: "POST",

        headers: {
            "Content-Type": "application/json"
        },

        body: JSON.stringify(expense)

    })
    .then(response => response.text())
    .then(data => {

        console.log(data);

        loadExpenses();
        loadDashboard();

        document.getElementById("amount").value = "";
        document.getElementById("category").selectedIndex = 0;
        document.getElementById("date").value = "";
        document.getElementById("paymentMethod").selectedIndex = 0;
        document.getElementById("description").value = "";
        document.getElementById("formTitle").innerText = "Add New Expense";
        document.getElementById("buttonText").innerText = "Add Expense";

    })
    .catch(error => console.log(error));

});


function deleteExpense(id)
{
    if (!confirm("Are you sure you want to delete this expense?"))
    return;

    fetch(`http://localhost:8080/expenses/${id}`, {

        method: "DELETE"

    })
    .then(response => response.text())
    .then(data => {

        console.log(data);

        loadExpenses();
        loadDashboard();

    })
    .catch(error => console.log(error));
}

function editExpense(id)
{
    fetch("http://localhost:8080/expenses")
    .then(response => response.json())
    .then(data => {

        const expense = data.find(e => e.id == id);
        editingId = id;

        if (!expense)
            return;

        document.getElementById("amount").value = expense.amount;
        document.getElementById("category").value = expense.category;
        document.getElementById("date").value = expense.date;
        document.getElementById("paymentMethod").value = expense.paymentMethod;
        document.getElementById("description").value = expense.description;

        console.log("Editing Expense:", expense);
        document.getElementById("formTitle").innerText = "Edit Expense";
document.getElementById("buttonText").innerText = "Update Expense";

document.querySelector(".expense-section")
    .scrollIntoView({ behavior: "smooth" });

    })
    .catch(error => console.log(error));
}

function renderExpenses(expenses)
{
    const table = document.getElementById("expenseTable");

    table.innerHTML = "";

    expenses.forEach(expense => {

        table.innerHTML += `
            <tr>
                <td>${expense.id}</td>
                <td>${expense.date}</td>
                <td>${expense.category}</td>
                <td>₹${expense.amount}</td>
                <td>${expense.paymentMethod}</td>
                <td>${expense.description}</td>
                <td>
                    <button class="edit-btn"
                        onclick="editExpense(${expense.id})">
                        Edit
                    </button>

                    <button class="delete-btn"
                        onclick="deleteExpense(${expense.id})">
                        Delete
                    </button>
                </td>
            </tr>
        `;
    });
}


function applyFilters()
{
    let expenses = [...allExpenses];

    if (currentSearch !== "")
    {
        expenses = expenses.filter(expense =>

            expense.category.toLowerCase().includes(currentSearch) ||

            expense.description.toLowerCase().includes(currentSearch)

        );
    }

    switch (currentSort)
    {
        case "amount":

            expenses.sort((a, b) => a.amount - b.amount);
            break;

        case "category":

            expenses.sort((a, b) => a.category.localeCompare(b.category));
            break;

        case "date":

            expenses.sort((a, b) => new Date(a.date) - new Date(b.date));
            break;
    }

    renderExpenses(expenses);
}


document.getElementById("searchBox").addEventListener("input", function ()
{
    currentSearch = this.value.toLowerCase();

    applyFilters();
});


document.getElementById("sortSelect").addEventListener("change", function ()
{
    currentSort = this.value;

    applyFilters();
});


document.getElementById("exportBtn").addEventListener("click", () => {

    let csv = "ID,Date,Category,Amount,Payment Method,Description\n";

    allExpenses.forEach(expense => {

        csv += `${expense.id},${expense.date},${expense.category},${expense.amount},${expense.paymentMethod},"${expense.description}"\n`;

    });

    const blob = new Blob([csv], { type: "text/csv" });

    const url = window.URL.createObjectURL(blob);

    const a = document.createElement("a");

    a.href = url;

    a.download = "Expense_Report.csv";

    a.click();

    window.URL.revokeObjectURL(url);

});


function scrollToSection(id)
{
    document.getElementById(id).scrollIntoView({

        behavior: "smooth"

    });
}

document.getElementById("dashboardBtn").addEventListener("click", () => {

    setActiveMenu("dashboardBtn");

    scrollToSection("dashboard");

});

document.getElementById("addExpenseBtnNav").addEventListener("click", () => {

    setActiveMenu("addExpenseBtnNav");

    scrollToSection("addExpense");

});

document.getElementById("historyBtn").addEventListener("click", () => {

    setActiveMenu("historyBtn");

    scrollToSection("expenseHistory");

});




document.getElementById("getStartedBtn").addEventListener("click", () => {

    scrollToSection("addExpense");

});


// ================= Statistics Modal =================

const statsModal = document.getElementById("statsModal");

document.getElementById("statisticsBtn").addEventListener("click", () => {

    setActiveMenu("statisticsBtn");

    document.getElementById("modalHighest").innerText =
        document.getElementById("highestExpense").innerText;

    document.getElementById("modalLowest").innerText =
        document.getElementById("lowestExpense").innerText;

    document.getElementById("modalAverage").innerText =
        document.getElementById("averageExpense").innerText;

    document.getElementById("modalRecords").innerText =
        document.getElementById("totalRecords").innerText;

    // Progress Bars
    const highest = parseFloat(
        document.getElementById("modalHighest").innerText.replace("₹", "")
    );

    const lowest = parseFloat(
        document.getElementById("modalLowest").innerText.replace("₹", "")
    );

    const average = parseFloat(
        document.getElementById("modalAverage").innerText.replace("₹", "")
    );

    animateValue("modalHighest", highest);
animateValue("modalLowest", lowest);
animateValue("modalAverage", average);

document.getElementById("highestBar").style.width = "0%";
document.getElementById("lowestBar").style.width = "0%";
document.getElementById("averageBar").style.width = "0%";
document.getElementById("recordBar").style.width = "0%";

setTimeout(() => {

    document.getElementById("highestBar").style.width = "100%";

    document.getElementById("lowestBar").style.width =
        (lowest / highest * 100) + "%";

    document.getElementById("averageBar").style.width =
        (average / highest * 100) + "%";

    document.getElementById("recordBar").style.width = "100%";

}, 100);

    statsModal.style.display = "flex";

});


// ================= Reports Modal =================

document.getElementById("reportsBtn").addEventListener("click", () => {

    setActiveMenu("reportsBtn");

    document.getElementById("reportTotal").innerText =
        document.getElementById("totalExpense").innerText;

    document.getElementById("reportMonth").innerText =
        document.getElementById("monthlyExpense").innerText;

    reportModal.style.display = "flex";

});


// ================= Close Buttons =================

document.getElementById("closeStats").onclick = () => {

    statsModal.style.display = "none";

    const scrollY = window.scrollY;

    if (scrollY < document.getElementById("addExpense").offsetTop - 120)
    {
        setActiveMenu("dashboardBtn");
    }
    else if (scrollY < document.getElementById("expenseHistory").offsetTop - 120)
    {
        setActiveMenu("addExpenseBtnNav");
    }
    else
    {
        setActiveMenu("historyBtn");
    }

};

document.getElementById("closeReport").onclick = () => {

    reportModal.style.display = "none";

    const scrollY = window.scrollY;

    if (scrollY < document.getElementById("addExpense").offsetTop - 120)
    {
        setActiveMenu("dashboardBtn");
    }
    else if (scrollY < document.getElementById("expenseHistory").offsetTop - 120)
    {
        setActiveMenu("addExpenseBtnNav");
    }
    else
    {
        setActiveMenu("historyBtn");
    }

};


// ================= Click Outside =================

window.addEventListener("click", (e) => {

    if (e.target === statsModal)
        statsModal.style.display = "none";

    if (e.target === reportModal)
        reportModal.style.display = "none";

});


// ================= Export From Modal =================

document.getElementById("reportExportBtn").addEventListener("click", () => {

    document.getElementById("exportBtn").click();

});

function animateValue(id, end)
{
    let start = 0;

    let duration = 800;

    let step = end / (duration / 16);

    let value = 0;

    let timer = setInterval(() => {

        value += step;

        if(value >= end)
        {
            value = end;

            clearInterval(timer);
        }

        document.getElementById(id).innerText =
            "₹" + Math.round(value);

    },16);
}


// ================= Dark Mode =================

const themeToggle = document.getElementById("themeToggle");

if (localStorage.getItem("theme") === "dark")
{
    document.body.classList.add("dark");
    themeToggle.innerHTML = "☀️";
}

themeToggle.addEventListener("click", () => {

    document.body.classList.toggle("dark");

    if (document.body.classList.contains("dark"))
    {
        localStorage.setItem("theme", "dark");
        themeToggle.innerHTML = "☀️";
    }
    else
    {
        localStorage.setItem("theme", "light");
        themeToggle.innerHTML = "🌙";
    }

});


function setActiveMenu(activeId)
{
    document.querySelectorAll(".sidebar li").forEach(item => {

        item.classList.remove("active");

    });

    document.getElementById(activeId).classList.add("active");
}



// ================= Auto Active Menu On Scroll =================

window.addEventListener("scroll", () => {

    const scrollY = window.scrollY;

    const dashboard = document.getElementById("dashboard");
    const addExpense = document.getElementById("addExpense");
    const expenseHistory = document.getElementById("expenseHistory");

    if (scrollY < addExpense.offsetTop - 120)
    {
        setActiveMenu("dashboardBtn");
    }
    else if (scrollY < expenseHistory.offsetTop - 120)
    {
        setActiveMenu("addExpenseBtnNav");
    }
    else
    {
        setActiveMenu("historyBtn");
    }

});


// ================= Logout =================

const logoutBtn = document.getElementById("logoutBtn");

logoutBtn.addEventListener("click", () =>
{
    if(confirm("Do you want to logout?"))
    {
        localStorage.removeItem("loggedIn");
        localStorage.removeItem("email");

        window.location.href = "login.html";
    }
});

const profileBtn = document.getElementById("profileBtn");

const email = localStorage.getItem("email");

if(email)
{
    profileBtn.innerHTML = "👤 " + email.split("@")[0];
}