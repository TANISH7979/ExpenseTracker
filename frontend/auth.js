let isRegister = false;

const form = document.getElementById("loginForm");
const formTitle = document.getElementById("formTitle");
const submitBtn = document.getElementById("submitBtn");
const toggleBtn = document.getElementById("toggleBtn");
const nameField = document.getElementById("nameField");
const message = document.getElementById("message");

toggleBtn.addEventListener("click", () =>
{
    isRegister = !isRegister;

    if (isRegister)
    {
        formTitle.innerText = "Register";
        submitBtn.innerText = "Register";
        toggleBtn.innerText = "Back to Login";
        nameField.style.display = "block";
    }
    else
    {
        formTitle.innerText = "Login";
        submitBtn.innerText = "Login";
        toggleBtn.innerText = "Create New Account";
        nameField.style.display = "none";
    }

    message.innerText = "";
});

form.addEventListener("submit", async (e) =>
{
    e.preventDefault();

    const username = document.getElementById("username").value;
    const email = document.getElementById("email").value;
    const password = document.getElementById("password").value;

    const url = isRegister
        ? "http://localhost:8080/register"
        : "http://localhost:8080/login";

    const body = isRegister
        ? {
              username: username,
              email: email,
              password: password
          }
        : {
              email: email,
              password: password
          };

    try
    {
        const response = await fetch(url,
        {
            method: "POST",
            headers:
            {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(body)
        });

        const data = await response.json();

        if (isRegister)
        {
            if (data.success)
            {
                alert("Registration Successful!");

                isRegister = false;

                formTitle.innerText = "Login";
                submitBtn.innerText = "Login";
                toggleBtn.innerText = "Create New Account";
                nameField.style.display = "none";

                message.innerText = "";
                form.reset();
            }
            else
            {
                message.innerText = data.message;
            }
        }
        else
        {
            if (data.success)
            {
                localStorage.setItem("loggedIn", "true");
                localStorage.setItem("email", email);
                localStorage.setItem("userId", data.userId);

                window.location.href = "index.html";
            }
            else
            {
                message.innerText = data.message;
            }
        }
    }
    catch(error)
{
    console.error(error);

    alert(error);

    message.innerText = error;
}
});