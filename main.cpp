/*
    INF311 DATA STRUCTURES - SEMESTER PROJECT 2026/2027
    PROJECT 15: SOCIAL NETWORK CONNECTION SYSTEM
    Group: GRP23

    Data structure:
    Undirected graph implemented with an adjacency list.
    Both the user list and each user's friend list are built manually
    with linked nodes. No STL containers are used.

    Compile:
        g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o social_network

    Run:
        ./social_network          (Linux / macOS)
        social_network.exe        (Windows)
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct FriendNode {
    string friendName;
    FriendNode* next;

    FriendNode(const string& name) {
        friendName = name;
        next = NULL;
    }
};

struct UserNode {
    string name;
    FriendNode* friends;
    UserNode* next;
    bool visited;

    UserNode(const string& userName) {
        name = userName;
        friends = NULL;
        next = NULL;
        visited = false;
    }
};

class SocialNetwork {
private:
    UserNode* head;
    int userCount;

    UserNode* findUser(const string& name) const {
        UserNode* current = head;

        while (current != NULL) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    bool hasFriend(UserNode* user, const string& friendName) const {
        if (user == NULL) {
            return false;
        }

        FriendNode* current = user->friends;
        while (current != NULL) {
            if (current->friendName == friendName) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addFriendNode(UserNode* user, const string& friendName) {
        FriendNode* newNode = new FriendNode(friendName);
        newNode->next = user->friends;
        user->friends = newNode;
    }

    void removeFriendNode(UserNode* user, const string& friendName) {
        if (user == NULL) {
            return;
        }

        FriendNode* current = user->friends;
        FriendNode* previous = NULL;

        while (current != NULL) {
            if (current->friendName == friendName) {
                if (previous == NULL) {
                    user->friends = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    void deleteAllFriends(UserNode* user) {
        FriendNode* current = user->friends;

        while (current != NULL) {
            FriendNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        user->friends = NULL;
    }

    void resetVisited() {
        UserNode* current = head;
        while (current != NULL) {
            current->visited = false;
            current = current->next;
        }
    }

public:
    SocialNetwork() {
        head = NULL;
        userCount = 0;
    }

    ~SocialNetwork() {
        UserNode* current = head;

        while (current != NULL) {
            UserNode* nextUser = current->next;
            deleteAllFriends(current);
            delete current;
            current = nextUser;
        }
    }

    bool isEmpty() const {
        return head == NULL;
    }

    int getUserCount() const {
        return userCount;
    }

    int getFriendshipCount() const {
        int totalLinks = 0;
        UserNode* current = head;

        while (current != NULL) {
            FriendNode* friendNode = current->friends;
            while (friendNode != NULL) {
                totalLinks++;
                friendNode = friendNode->next;
            }
            current = current->next;
        }

        // Every friendship is stored twice because the graph is undirected.
        return totalLinks / 2;
    }

    bool addUser(const string& name) {
        if (name.empty()) {
            cout << "A user name cannot be empty.\n";
            return false;
        }

        if (findUser(name) != NULL) {
            cout << "That user already exists.\n";
            return false;
        }

        UserNode* newUser = new UserNode(name);
        newUser->next = head;
        head = newUser;
        userCount++;

        cout << name << " has been added successfully.\n";
        return true;
    }

    bool searchUser(const string& name) const {
        return findUser(name) != NULL;
    }

    bool removeUser(const string& name) {
        UserNode* current = head;
        UserNode* previous = NULL;

        while (current != NULL && current->name != name) {
            previous = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << "User not found. Nothing was removed.\n";
            return false;
        }

        // Remove this user from every other user's friend list.
        UserNode* otherUser = head;
        while (otherUser != NULL) {
            if (otherUser != current) {
                removeFriendNode(otherUser, name);
            }
            otherUser = otherUser->next;
        }

        if (previous == NULL) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        deleteAllFriends(current);
        delete current;
        userCount--;

        cout << name << " and all of their friendships have been removed.\n";
        return true;
    }

    bool addFriendship(const string& firstName, const string& secondName) {
        if (firstName == secondName) {
            cout << "A user cannot be friends with themselves.\n";
            return false;
        }

        UserNode* first = findUser(firstName);
        UserNode* second = findUser(secondName);

        if (first == NULL || second == NULL) {
            cout << "Both users must exist before adding a friendship.\n";
            return false;
        }

        if (hasFriend(first, secondName)) {
            cout << "These users are already friends.\n";
            return false;
        }

        // Add both directions because friendship is mutual.
        addFriendNode(first, secondName);
        addFriendNode(second, firstName);

        cout << "Friendship added between " << firstName
             << " and " << secondName << ".\n";
        return true;
    }

    bool removeFriendship(const string& firstName, const string& secondName) {
        UserNode* first = findUser(firstName);
        UserNode* second = findUser(secondName);

        if (first == NULL || second == NULL) {
            cout << "Both users must exist before removing a friendship.\n";
            return false;
        }

        if (!hasFriend(first, secondName)) {
            cout << "These users are not friends.\n";
            return false;
        }

        removeFriendNode(first, secondName);
        removeFriendNode(second, firstName);

        cout << "Friendship removed between " << firstName
             << " and " << secondName << ".\n";
        return true;
    }

    void displayUsers() const {
        if (isEmpty()) {
            cout << "The social network is empty.\n";
            return;
        }

        cout << "\n--- USERS AND THEIR FRIENDS ---\n";
        UserNode* current = head;

        while (current != NULL) {
            cout << current->name << " : ";

            FriendNode* friendNode = current->friends;
            if (friendNode == NULL) {
                cout << "No friends";
            } else {
                while (friendNode != NULL) {
                    cout << friendNode->friendName;
                    if (friendNode->next != NULL) {
                        cout << ", ";
                    }
                    friendNode = friendNode->next;
                }
            }

            cout << '\n';
            current = current->next;
        }
    }

    void displayFriends(const string& name) const {
        UserNode* user = findUser(name);

        if (user == NULL) {
            cout << "User not found.\n";
            return;
        }

        cout << "\nFriends of " << name << ": ";
        FriendNode* current = user->friends;

        if (current == NULL) {
            cout << "No friends";
        } else {
            while (current != NULL) {
                cout << current->friendName;
                if (current->next != NULL) {
                    cout << ", ";
                }
                current = current->next;
            }
        }
        cout << '\n';
    }

    void findMutualFriends(const string& firstName,
                           const string& secondName) const {
        UserNode* first = findUser(firstName);
        UserNode* second = findUser(secondName);

        if (first == NULL || second == NULL) {
            cout << "Both users must exist to find mutual friends.\n";
            return;
        }

        bool found = false;
        FriendNode* current = first->friends;

        cout << "\nMutual friends of " << firstName
             << " and " << secondName << ": ";

        while (current != NULL) {
            if (hasFriend(second, current->friendName)) {
                if (found) {
                    cout << ", ";
                }
                cout << current->friendName;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No mutual friends";
        }
        cout << '\n';
    }

    // Returns true only if both users exist and are direct friends.
    // (The caller in main() checks that the users exist first.)
    bool areDirectlyConnected(const string& firstName,
                              const string& secondName) const {
        UserNode* first = findUser(firstName);
        UserNode* second = findUser(secondName);

        if (first == NULL || second == NULL) {
            return false;
        }

        return hasFriend(first, secondName);
    }

    // Returns true if a path of friendships exists between the two users.
    // (The caller in main() checks that the users exist first.)
    bool areConnectedThroughNetwork(const string& firstName,
                                    const string& secondName) {
        UserNode* start = findUser(firstName);
        UserNode* destination = findUser(secondName);

        if (start == NULL || destination == NULL) {
            return false;
        }

        if (start == destination) {
            return true;
        }

        // Breadth-first search using a manually created array as a queue.
        resetVisited();

        UserNode** queue = new UserNode*[userCount];
        int front = 0;
        int rear = 0;

        start->visited = true;
        queue[rear++] = start;

        bool connected = false;

        while (front < rear && !connected) {
            UserNode* currentUser = queue[front++];
            FriendNode* friendNode = currentUser->friends;

            while (friendNode != NULL) {
                UserNode* nextUser = findUser(friendNode->friendName);

                if (nextUser != NULL && !nextUser->visited) {
                    nextUser->visited = true;

                    if (nextUser == destination) {
                        connected = true;
                        break;
                    }

                    queue[rear++] = nextUser;
                }

                friendNode = friendNode->next;
            }
        }

        delete[] queue;
        resetVisited();
        return connected;
    }

    void displayStatistics() const {
        cout << "\n--- NETWORK STATISTICS ---\n";
        cout << "Total users: " << userCount << '\n';
        cout << "Total friendships: " << getFriendshipCount() << '\n';
    }
};

string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);

    // Remove spaces at the start and end so "Ama " and "Ama" are the same name,
    // and a name made only of spaces becomes empty.
    size_t first = value.find_first_not_of(" \t");
    if (first == string::npos) {
        return "";
    }
    size_t last = value.find_last_not_of(" \t");
    return value.substr(first, last - first + 1);
}

int readMenuChoice() {
    string line;
    int choice = -1;
    cout << "\nEnter your choice: ";

    // If the input has ended (Ctrl+Z / Ctrl+D) there is nothing left to read, so exit.
    if (!getline(cin, line)) {
        return 0;
    }

    stringstream input(line);
    if (!(input >> choice) || !(input >> ws).eof()) {
        return -1;
    }
    return choice;
}

void showMenu() {
    cout << "\n========================================\n";
    cout << "       SOCIAL NETWORK CONNECTION SYSTEM\n";
    cout << "========================================\n";
    cout << "1.  Add user\n";
    cout << "2.  Remove user\n";
    cout << "3.  Search for user\n";
    cout << "4.  Add friendship\n";
    cout << "5.  Remove friendship\n";
    cout << "6.  Display all users and friends\n";
    cout << "7.  Display friends of a user\n";
    cout << "8.  Find mutual friends\n";
    cout << "9.  Check direct friendship\n";
    cout << "10. Check connection through the network\n";
    cout << "11. Display network statistics\n";
    cout << "0.  Exit\n";
}

int main() {
    SocialNetwork network;
    bool running = true;

    cout << "Welcome to the Social Network Connection System!\n";
    cout << "GRP23: Project 15\n";

    while (running) {
        showMenu();
        int choice = readMenuChoice();

        switch (choice) {
            case 1: {
                string name = readText("Enter the user's name: ");
                network.addUser(name);
                break;
            }

            case 2: {
                string name = readText("Enter the name of the user to remove: ");
                network.removeUser(name);
                break;
            }

            case 3: {
                string name = readText("Enter the name to search for: ");
                if (network.searchUser(name)) {
                    cout << name << " is registered in the network.\n";
                } else {
                    cout << name << " was not found.\n";
                }
                break;
            }

            case 4: {
                string first = readText("Enter the first user's name: ");
                string second = readText("Enter the second user's name: ");
                network.addFriendship(first, second);
                break;
            }

            case 5: {
                string first = readText("Enter the first user's name: ");
                string second = readText("Enter the second user's name: ");
                network.removeFriendship(first, second);
                break;
            }

            case 6:
                network.displayUsers();
                break;

            case 7: {
                string name = readText("Enter the user's name: ");
                network.displayFriends(name);
                break;
            }

            case 8: {
                string first = readText("Enter the first user's name: ");
                string second = readText("Enter the second user's name: ");
                network.findMutualFriends(first, second);
                break;
            }

            case 9: {
                string first = readText("Enter the first user's name: ");
                string second = readText("Enter the second user's name: ");

                if (!network.searchUser(first) || !network.searchUser(second)) {
                    cout << "One or both users do not exist.\n";
                } else if (network.areDirectlyConnected(first, second)) {
                    cout << first << " and " << second
                         << " are direct friends.\n";
                } else {
                    cout << first << " and " << second
                         << " are not direct friends.\n";
                }
                break;
            }

            case 10: {
                string first = readText("Enter the starting user's name: ");
                string second = readText("Enter the destination user's name: ");

                if (!network.searchUser(first) || !network.searchUser(second)) {
                    cout << "One or both users do not exist.\n";
                } else if (network.areConnectedThroughNetwork(first, second)) {
                    cout << "A connection path exists between "
                         << first << " and " << second << ".\n";
                } else {
                    cout << "No connection path exists between "
                         << first << " and " << second << ".\n";
                }
                break;
            }

            case 11:
                network.displayStatistics();
                break;

            case 0:
                running = false;
                cout << "Thank you for using the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 0 to 11.\n";
        }
    }

    return 0;
}
