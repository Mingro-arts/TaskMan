# TaskMan
The app for managing tasks , its named TaskMan the Task Manager App

Task Manager App

A simple C++ command-line application for managing tasks. This program allows users to add, remove, view, and mark tasks as completed, with an option to save and load tasks to/from a file. Each task has an ID, title, description, priority, due date, and status (completed or pending).

Features

Add Tasks: Create new tasks with a unique ID, title, description, priority (1-5), and due date.
Remove Tasks: Delete a task by specifying its ID.
View All Tasks: Display all the tasks with their details.
Mark Tasks as Completed: Mark a task as completed by specifying its ID.
Save Tasks: Save the current task list to a text file for future use.
Load Tasks: Load tasks from a previously saved text file.

Getting Started

Prerequisites

To run this application, you need to have a C++ compiler installed on your system. You can use GCC, Clang, or any C++ compiler of your choice.

Running the Program
git clone https://github.com/your-username/task-manager.git

Navigate to the project directory:
cd task-manager

Compile the program:
g++ -o task_manager main.cpp

Run the executable:
./task_manager

File Operations

The tasks can be saved to a file named tasks.txt using the "Save Tasks" feature.
You can load tasks from an existing file (tasks.txt) using the "Load Tasks" feature.
Note: If the file doesn't exist, you will see an error when trying to load tasks.

Example Usage

Task Manager Menu:

1. Add Task
2. Remove Task
3. Display All Tasks
4. Mark Task as Completed
5. Save Tasks to File
6. Load Tasks from File
7. Exit
8. 
Project Structure

task-manager/
│
├── main.cpp            # Main source file containing the task manager logic
├── tasks.txt           # Sample tasks file (optional)
├── README.md           # This README file

Future Improvements

Add task sorting by priority or due date.
Enhance file handling to support JSON or CSV formats.
Implement a graphical user interface (GUI).
Contributing
Fork the repository.
Create a new branch for your feature or bug fix.
Submit a pull request detailing your changes.

This project is licensed under the MIT License.


