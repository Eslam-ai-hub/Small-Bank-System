# Bank Management System – Bank Extension

A console-based Bank Management System developed using C++. The project provides basic banking operations, client management, user management, and permission-based access control.

It focuses on applying core C++ programming concepts, file handling, and problem-solving through a practical banking application.

## Features

### 1. Client Management
- View all registered clients.
- Add new clients with unique account numbers.
- Update existing client information.
- Delete client records.
- Search for clients using their account numbers.
- Store client information in text files.

### 2. Transactions
- Deposit money into client accounts.
- Withdraw money from client accounts.
- Prevent withdrawals that exceed the available balance.
- Display individual account balances.
- Calculate and display total bank balances.

### 3. User Management
- Add new system users.
- View all registered users.
- Update user information.
- Delete existing users.
- Search for users by username.
- Protect the default Admin account from deletion.

### 4. Permissions & Access Control
- Assign permissions to each user.
- Support full access or specific permissions.
- Use Bitwise Operators to manage user permissions.
- Restrict access to unauthorized operations.

### 5. Authentication
- Login using username and password.
- Maintain the currently logged-in user.
- Log out and return to the login screen.

## Technologies & Concepts

- **Language:** C++
- **File Handling:** `fstream`, reading and writing text files.
- **Data Structures:** `struct`, `vector`, and `enum`.
- **Programming Concepts:** Functions, loops, conditions, and `switch` statements.
- **Bitwise Operations:** Managing user permissions using Bitwise AND (`&`) and OR (`|`).
- **Data Processing:** Converting records between strings and structures.
- **Code Organization:** Breaking the application into separate functions.

## Data Storage

The application uses text files to store its data:

- `Clients.txt` – Stores client account information.
- `Users.txt` – Stores system users and their permissions.

Records are stored using a custom separator (`#//#`) to make reading and writing data easier.

## Getting Started

### Prerequisites
- A C++ compiler.
- Visual Studio or any C++ IDE.

### Running the Project
1. Clone or download the repository.
2. Open the project in your preferred C++ IDE.
3. Build and run the application.
4. Log in using an existing user account.

## Project Purpose

This project was developed as a practical application of C++ programming fundamentals, with a focus on file handling, data management, and implementing a permission-based system.

---

**Language:** C++  
**Project Type:** Console Application
