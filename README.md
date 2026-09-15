# Element Database

**A periodic element manager built in C++ using a Binary Search Tree**

**North South University, Dhaka, Bangladesh**

_Data Structures project — interactive console application for storing, searching, and managing chemical elements keyed by atomic number._

---

## Overview

This repository contains a **console-based element database** written in C++. Elements are stored in a **Binary Search Tree (BST)** sorted by atomic number, with support for add, view, search, and delete operations through an interactive menu.

The project was developed as an academic assignment at **North South University, Dhaka, Bangladesh** for **CSE 225.11**.

| Field          | Type     | Description                        |
| -------------- | -------- | ---------------------------------- |
| `atomicNumber` | `int`    | Unique identifier and BST sort key |
| `symbol`       | `string` | Chemical symbol (e.g. `Li`, `He`)  |
| `name`         | `string` | Full element name (e.g. `Lithium`) |

---

## Features

### Core Operations

| Operation             | Description                                  |
| --------------------- | -------------------------------------------- |
| **Add an element**    | Insert by atomic number, symbol, and name    |
| **View elements**     | In-order traversal — sorted by atomic number |
| **Search by symbol**  | Case-insensitive lookup by chemical symbol   |
| **Search by name**    | Case-insensitive lookup by element name      |
| **Delete an element** | Confirm before removal by atomic number      |
| **Exit**              | Clean program termination                    |

### Data Structure

```
        (3, Li)
       /       \
   (2, He)   (36, Kr)
```

- **Insert / search by atomic number** — O(log n) average on a balanced tree; O(n) worst case if skewed
- **Search by symbol or name** — full tree traversal, O(n)

---

## Project Structure

```
Element-database-Project/
│
├── CSE225_11-SayadulHoque-ElementDatabase.cpp   # Main source code
├── Project Structure.txt                        # Sample run / expected I/O
└── README.md
```

### Source Components

| Component               | Role                                                        |
| ----------------------- | ----------------------------------------------------------- |
| `struct Element`        | BST node (atomic number, symbol, name, left/right pointers) |
| `class ElementDatabase` | Encapsulates the tree and all CRUD operations               |
| `printmenu()`           | Displays the interactive menu                               |
| `main()`                | Menu loop and user input handling                           |

---

## How to Run

**1. Clone the repository:**

```bash
git clone https://github.com/Saidul00005/Element-database-Project.git
cd Element-database-Project
```

**2. Install a C++ compiler (if you don't have one):**

**Windows (recommended — via winget):**

```powershell
winget install -e --id BrechtSanders.WinLibs.POSIX.UCRT
```

Restart your terminal or Cursor after installation so `g++` is recognized.

**3. Compile and run:**

**Windows (PowerShell):**

```powershell
g++ -std=c++17 CSE225_11-SayadulHoque-ElementDatabase.cpp -o CSE225_11-SayadulHoque-ElementDatabase.exe
.\CSE225_11-SayadulHoque-ElementDatabase.exe
```

**Linux / macOS:**

```bash
g++ -std=c++17 -o CSE225_11-SayadulHoque-ElementDatabase CSE225_11-SayadulHoque-ElementDatabase.cpp
./CSE225_11-SayadulHoque-ElementDatabase
```

**Visual Studio (Developer Command Prompt):**

```bash
cl /EHsc CSE225_11-SayadulHoque-ElementDatabase.cpp
```

---

### Run in Cursor / VS Code (Code Runner)

1. Install the **C/C++** extension and **Code Runner**.
2. Install **g++** (see above).
3. Open `CSE225_11-SayadulHoque-ElementDatabase.cpp` and click **Run** (▶) or press `Ctrl+Alt+N`.

The program runs in the **terminal panel** at the bottom — type menu options (`1`–`6`) there. No extra `settings.json` changes are needed with the current filename.

### Source filename rules

The source file is named so Code Runner and `g++` work out of the box on Windows:

```
CSE225_11-SayadulHoque-ElementDatabase.cpp
```

| Rule                                      | Why                                                                   |
| ----------------------------------------- | --------------------------------------------------------------------- |
| **No spaces**                             | Spaces break compile/run commands                                     |
| **No dots in the name** (use `_` instead) | Names like `CSE225.11-...` can stop `g++` from creating a `.exe` file |
| **Hyphens are fine**                      | `SayadulHoque-ElementDatabase` is okay                                |

**Good:** `CSE225_11-SayadulHoque-ElementDatabase.cpp`  
**Avoid:** `CSE225.11-Md. Sayadul Hoque-ElementDatabase.cpp`

---

### Usage

When the program starts, you will see:

```
1. Add an element
2. View elements
3. Search elements by chemical symbol
4. Search elements by element name
5. Delete an element
6. Exit program

Enter your choice:
```

Use the number keys **1–6** to interact with the menu. The program keeps running until you choose **Exit program**.

**Example session:**

```
** Add an element **
Enter atomic number: 3
Enter chemical symbol: Li
Enter element name: Lithium

Element added successfully.

** View Elements **
2, He, Helium
3, Li, Lithium
36, Kr, Krypton

** Search Elements by Chemical Symbol **

Enter chemical symbol: Li

Search result:
3, Li, Lithium
```

See `Project Structure.txt` for a full walkthrough of all menu options.

---

## Design Highlights

- **BST keyed by atomic number** — natural ordering for periodic elements
- **Object-oriented design** — `ElementDatabase` class encapsulates tree logic
- **Case-insensitive search** — symbol and name lookups ignore letter case
- **Proper BST deletion** — handles leaf, one-child, and two-child nodes
- **Interactive menu loop** — runs until the user chooses Exit

---

## Author

**Md. Sayadul Hoque**  
**North South University, Dhaka, Bangladesh**  
Course: **CSE 225.11**

---

## Acknowledgments

This project was developed as part of the CSE 225.11 curriculum at **North South University, Dhaka, Bangladesh**.

---

_If this project helped you understand BSTs and data structures, consider giving it a star._
