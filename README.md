# Social Network Connection System

**Course:** INF311 – Data Structures
**Institution:** University of Cape Coast (UCC)
**Academic Year:** 2026/2027
**Assignment:** Semester Project
**Project Number:** 15
**Project Name:** Social Network Connection System
**Group:** GRP23

---

## 1. Project Description

This is a console application written in C++ that models a simple social network. It stores users and the friendships between them, and lets the person using the program manage the network from a text menu.

The program was developed in Code::Blocks. It has no graphical interface, because the project instructions do not require one.

## 2. Data Structure Used

**An undirected graph, stored as an adjacency list.**

- Every **user** is a vertex (a node in a linked list of users).
- Every **friendship** is an edge. Because friendship goes both ways, it is stored twice: once in each user's friend list.
- Each user has their own linked list of friends.
- All linked lists, nodes, and the queue used for searching are written by hand with pointers. **No STL containers** (such as `vector`, `list`, `map` or `queue`) are used.

### Why this data structure?

- A social network is naturally a graph: people are connected to other people.
- An adjacency list only stores friendships that actually exist, so it uses less memory than an adjacency matrix when most users are not friends with each other.
- Listing a user's friends is fast, because they are already in one list.
- Users can be added and removed at any time without a fixed size limit.

## 3. Features and Operations

The seven operations required by the project:

| # | Required operation | Menu option |
|---|--------------------|-------------|
| 1 | Add user | 1 |
| 2 | Remove user (also removes all of that user's friendships) | 2 |
| 3 | Add friendship | 4 |
| 4 | Remove friendship | 5 |
| 5 | Display friends | 7 |
| 6 | Find mutual friends | 8 |
| 7 | Determine whether two users are connected | 9 (direct friends) and 10 (connected through the network) |

Extra options:

| Menu option | Purpose |
|-------------|---------|
| 3 | Search for a user |
| 6 | Display all users and their friends |
| 11 | Display network statistics (total users and total friendships) |
| 0 | Exit |

### Connection check

Option 9 tells you if two users are **direct friends**.
Option 10 tells you if two users are **connected through any chain of friends** (for example, Ama → Kojo → Kofi). It uses a **breadth-first search** with a manually created array as the queue.

### Error handling

The program handles:

- An empty network (for example, displaying users when nobody has been added)
- Empty names, or names made only of spaces
- Names with extra spaces at the start or end (they are trimmed)
- Duplicate users
- Duplicate friendships
- A user trying to befriend themselves
- Users that do not exist
- Removing a friendship that does not exist
- Invalid menu input (letters, decimals, empty lines, numbers outside 0–11)
- Input ending unexpectedly (Ctrl+Z / Ctrl+D), which exits safely

All memory allocated with `new` is released with `delete` when users are removed and when the program exits.

> **Note:** User names are case-sensitive. `Ama` and `ama` are treated as two different users.

## 4. Technologies Used

- **Language:** C++ (C++11)
- **IDE:** Code::Blocks
- **Compiler:** GCC / MinGW (`g++`)
- **Libraries:** C++ standard library for input and output only (`iostream`, `string`, `sstream`)

## 5. How to Compile and Run

### Option A: Code::Blocks

1. Download or clone this repository.
2. Open Code::Blocks.
3. Go to **File → New → Empty file**, or create a **Console application** project in C++.
4. Add `main.cpp` to the project (if you used a project, remove the default `main.cpp` first, then add this one).
5. Press **F9** (Build and Run).

### Option B: Command line with g++

Open a terminal in the folder that contains `main.cpp`, then run:

```
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o social_network
```

Then run the program:

- Windows: `social_network.exe`
- Linux / macOS: `./social_network`

## 6. Example

The example from the project brief:

```
      Ama
     /   \
  Kojo    Yaa
     \   /
      Kofi
```

To build it, add the four users (option 1), then add these friendships (option 4): Ama–Kojo, Ama–Yaa, Kojo–Kofi, Yaa–Kofi.

- Option 8 on **Ama** and **Kofi** shows their mutual friends: Yaa and Kojo.
- Option 10 on **Ama** and **Kofi** says a connection path exists.

## 7. Testing

The program was tested with these kinds of cases:

- **Normal operations:** adding users and friendships, displaying, finding mutual friends, removing friendships and users.
- **Empty network:** displaying, searching, removing and checking connections with no users.
- **Duplicate data:** adding the same user or friendship twice.
- **Invalid input:** empty names, spaces only, letters or decimals as menu choices, numbers outside the menu range, non-existent users.
- **Large input:** 3,000 users linked in a chain, then a connection check between the first and last user, then removing all users.

Test cases, results and screenshots are in **Reflection.pdf**.

## 8. Repository Files

| File | Description |
|------|-------------|
| `main.cpp` | Full C++ source code of the program |
| `README.md` | This file |
| `Reflection.pdf` | Group project reflection, including screenshots of the running application |

## 9. Group Information (GRP23)

| SN | Name | Index Number |
|----|------|--------------|
| 111 | Reuben Ndede | ET/ICT/24/0049 |
| 112 | Richard Ato Quansah | ET/ICT/24/0002 |
| 113 | Richard Kwasi Appau | ET/ICT/24/0079 |
| 114 | Sally Odai-Davis Afoley | ET/ICT/24/0117 |
| 115 | Sam Leah | ET/ICT/24/0144 |

*Group list taken from the lecturer's project group allocation sheet.*
