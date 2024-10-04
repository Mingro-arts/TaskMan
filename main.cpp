#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <limits>

using namespace std;

namespace TaskManagerApp {

    // Task Class
    class Task {
    private:
        int taskID;
        string title;
        string description;
        int priority;  // Priority from 1 (low) to 5 (high)
        string dueDate;
        bool isCompleted;

    public:
        // Constructor
        Task(int id, const string& t, const string& desc, int prio, const string& date)
            : taskID(id), title(t), description(desc), priority(prio), dueDate(date), isCompleted(false) {}

        // Mark task as completed
        void markAsCompleted() {
            isCompleted = true;
        }

        // Getters
        int getTaskID() const { return taskID; }
        string getTitle() const { return title; }
        string getDescription() const { return description; }
        int getPriority() const { return priority; }
        string getDueDate() const { return dueDate; }
        bool isTaskCompleted() const { return isCompleted; }

        // Display task details
        void displayTask() const {
            cout << "Task ID: " << taskID << "\n"
                 << "Title: " << title << "\n"
                 << "Description: " << description << "\n"
                 << "Priority: " << priority << "\n"
                 << "Due Date: " << dueDate << "\n"
                 << "Status: " << (isCompleted ? "Completed" : "Pending") << "\n\n";
        }
    };

    // Global vector of unique pointers to manage tasks
    vector<unique_ptr<Task>> taskList;

    // Function to add a task
    void addTask(int id, const string& title, const string& description, int priority, const string& dueDate) {
        unique_ptr<Task> newTask = make_unique<Task>(id, title, description, priority, dueDate);
        taskList.push_back(move(newTask));
        cout << "Task added successfully.\n";
    }

    // Function to remove a task by ID
    void removeTask(int id) {
        bool found = false;
        for (auto it = taskList.begin(); it != taskList.end(); ++it) {
            if ((*it)->getTaskID() == id) {
                taskList.erase(it);
                cout << "Task removed successfully.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Task not found.\n";
        }
    }

    // Function to display all tasks
    void displayAllTasks() {
        if (taskList.empty()) {
            cout << "No tasks to display.\n";
        } else {
            for (const auto& task : taskList) {
                task->displayTask();
            }
        }
    }

    // Function to mark a task as completed
    void markTaskCompleted(int id) {
        bool found = false;
        for (const auto& task : taskList) {
            if (task->getTaskID() == id) {
                task->markAsCompleted();
                cout << "Task marked as completed.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Task not found.\n";
        }
    }

    // Function to save tasks to a file
    void saveTasksToFile() {
    ofstream outFile("tasks.txt");
    if (outFile.is_open()) {
        outFile << "This Your List Of Tasks To Do "<< endl;
        outFile << "==============================" <<endl;
        for (const auto& task : taskList) {

            outFile << "Task ID: " << task->getTaskID() << "\n"
                    << "Title: " << task->getTitle() << "\n"
                    << "Description: " << task->getDescription() << "\n"
                    << "Priority: " << task->getPriority() << "\n"
                    << "Due Date: " << task->getDueDate() << "\n"
                    << "Completed: " << (task->isTaskCompleted() ? "Yes" : "No") << "\n"
                    << "---------------------------\n";  // Separate tasks with a line
        }
        outFile.close();
        cout << "Tasks saved to file.\n";
    } else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}


    // Function to load tasks from a file
    void loadTasksFromFile() {
    ifstream inFile("tasks2.txt");
    if (inFile.is_open()) {
        taskList.clear();  // Clear any existing tasks before loading new ones

        while (!inFile.eof()) {
            int id, priority;
            string title, description, dueDate;
            bool isCompleted;
            string line, completedStatus;

            // Read labeled lines, skipping the labels
            getline(inFile, line); // Read "Task ID:"
            if (line.empty()) break; // Break if there's an empty line (EOF or file structure ends)

            inFile >> id;  // Read task ID
            inFile.ignore();  // Ignore the newline character

            getline(inFile, line); // Read "Title:"
            getline(inFile, title); // Read actual title

            getline(inFile, line); // Read "Description:"
            getline(inFile, description); // Read actual description

            getline(inFile, line); // Read "Priority:"
            inFile >> priority;  // Read actual priority
            inFile.ignore();  // Ignore the newline character

            getline(inFile, line); // Read "Due Date:"
            getline(inFile, dueDate); // Read actual due date

            getline(inFile, line); // Read "Completed:"
            getline(inFile, completedStatus);  // Read if completed ("Yes" or "No")

            // Check completion status
            isCompleted = (completedStatus == "Yes");

            // Skip the separator line
            getline(inFile, line);

            // Create a new Task object with the loaded data
            auto task = make_unique<Task>(id, title, description, priority, dueDate);
            if (isCompleted) {
                task->markAsCompleted();
            }

            taskList.push_back(move(task));  // Add the task to the list
        }

        inFile.close();
        cout << "Tasks loaded from file.\n";
    } else {
        cerr << "Error: Unable to open file for reading.\n";
    }
}


    // Function to display the menu
    void displayMenu() {
        cout <<endl;
        cout << "Task Manager Menu:\n";
        cout <<endl;
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Display All Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Save Tasks to File\n";
        cout << "6. Load Tasks from File\n";
        cout << "7. Exit\n";
        cout <<endl;
    }

    // Function to handle user choices securely
    void handleUserChoice() {
        int choice = 0;
        while (choice != 7) {
            displayMenu();
            cin >> choice;

            // Input validation
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please enter a number between 1 and 7.\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    int id, priority;
                    string title, description, dueDate;
                    cout << "Enter Task ID: ";
                    cin >> id;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cerr << "Invalid Task ID. Please enter a valid number.\n";
                        break;
                    }
                    cin.ignore();
                    cout << "Enter Title: ";
                    getline(cin, title);
                    cout << "Enter Description: ";
                    getline(cin, description);
                    cout << "Enter Priority (1-5): ";
                    cin >> priority;
                    cin.ignore();
                    cout << "Enter Due Date: ";
                    getline(cin, dueDate);
                    addTask(id, title, description, priority, dueDate);
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter Task ID to remove: ";
                    cin >> id;
                    removeTask(id);
                    break;
                }
                case 3:
                    displayAllTasks();
                    break;
                case 4: {
                    int id;
                    cout << "Enter Task ID to mark as completed: ";
                    cin >> id;
                    markTaskCompleted(id);
                    break;
                }
                case 5:
                    saveTasksToFile();
                    break;
                case 6:
                    loadTasksFromFile();
                    break;
                case 7:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please choose between 1 and 7.\n";
                    break;
            }
        }
    }
}

int main() {
    TaskManagerApp::handleUserChoice();
    return 0;
}
