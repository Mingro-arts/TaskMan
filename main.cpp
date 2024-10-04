#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <limits>
#include <algorithm>  // For sort function

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

    // Function to generate auto-incrementing task ID
    int generateTaskID() {
        static int currentID = 1;
        if (!taskList.empty()) {
            currentID = taskList.back()->getTaskID() + 1;
        }
        return currentID++;
    }

    // Function to add a task
    void addTask(const string& title, const string& description, int priority, const string& dueDate) {
        int id = generateTaskID();
        unique_ptr<Task> newTask = make_unique<Task>(id, title, description, priority, dueDate);
        taskList.push_back(move(newTask));
        cout << "Task added successfully with ID " << id << ".\n";
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
    void saveTasksToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "This is your list of tasks to do:\n";
            outFile << "==============================\n";
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
    void loadTasksFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            taskList.clear();  // Clear any existing tasks before loading new ones

            while (!inFile.eof()) {
                int id, priority;
                string title, description, dueDate;
                bool isCompleted;
                string line, completedStatus;

                getline(inFile, line); // Read "Task ID:"
                if (line.empty()) break;

                inFile >> id;  // Read task ID
                inFile.ignore();

                getline(inFile, line); // Read "Title:"
                getline(inFile, title);

                getline(inFile, line); // Read "Description:"
                getline(inFile, description);

                getline(inFile, line); // Read "Priority:"
                inFile >> priority;
                inFile.ignore();

                getline(inFile, line); // Read "Due Date:"
                getline(inFile, dueDate);

                getline(inFile, line); // Read "Completed:"
                getline(inFile, completedStatus);
                isCompleted = (completedStatus == "Yes");

                getline(inFile, line);  // Skip the separator line

                auto task = make_unique<Task>(id, title, description, priority, dueDate);
                if (isCompleted) {
                    task->markAsCompleted();
                }
                taskList.push_back(move(task));
            }
            inFile.close();
            cout << "Tasks loaded from file.\n";
        } else {
            cerr << "Error: Unable to open file for reading.\n";
        }
    }

    // Function to get a valid priority from the user
    int getPriority() {
        int priority;
        while (true) {
            cout << "Enter Priority (1-5): ";
            cin >> priority;
            if (!cin.fail() && priority >= 1 && priority <= 5) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean input buffer
                return priority;
            } else {
                cin.clear(); // Reset failbit
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter a number between 1 and 5.\n";
            }
        }
    }

    // Function to display tasks sorted by priority
    void displayTasksSortedByPriority() {
        vector<Task*> sortedTasks;
        for (const auto& task : taskList) {
            sortedTasks.push_back(task.get());
        }
        sort(sortedTasks.begin(), sortedTasks.end(), [](Task* a, Task* b) {
            return a->getPriority() > b->getPriority(); // Sort by descending priority
        });
        for (const auto& task : sortedTasks) {
            task->displayTask();
        }
    }

    // Function to display only completed tasks
    void displayCompletedTasks() {
        for (const auto& task : taskList) {
            if (task->isTaskCompleted()) {
                task->displayTask();
            }
        }
    }

    // Function to display only incomplete tasks
    void displayIncompleteTasks() {
        for (const auto& task : taskList) {
            if (!task->isTaskCompleted()) {
                task->displayTask();
            }
        }
    }

    // Function to display the menu
    void displayMenu() {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Display All Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Save Tasks to File\n";
        cout << "6. Load Tasks from File\n";
        cout << "7. Display Tasks Sorted by Priority\n";
        cout << "8. Display Completed Tasks\n";
        cout << "9. Display Incomplete Tasks\n";
        cout << "10. Exit\n";
    }

    // Function to handle user choices securely
    void handleUserChoice() {
        int choice = 0;
        while (choice != 10) {
            displayMenu();
            cin >> choice;

            // Input validation
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please try again.\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    string title, description, dueDate;
                    cout << "Enter Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Description: ";
                    getline(cin, description);
                    int priority = getPriority();
                    cout << "Enter Due Date: ";
                    getline(cin, dueDate);
                    addTask(title, description, priority, dueDate);
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
                case 5: {
                    string filename;
                    cout << "Enter filename to save tasks: ";
                    cin >> filename;
                    saveTasksToFile(filename);
                    break;
                }
                case 6: {
                    string filename;
                    cout << "Enter filename to load tasks: ";
                    cin >> filename;
                    loadTasksFromFile(filename);
                    break;
                }
                case 7:
                    displayTasksSortedByPriority();
                    break;
                case 8:
                    displayCompletedTasks();
                    break;
                case 9:
                    displayIncompleteTasks();
                    break;
                case 10:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        }
    }

}  // namespace TaskManagerApp

int main() {
    TaskManagerApp::handleUserChoice();
    return 0;
}
