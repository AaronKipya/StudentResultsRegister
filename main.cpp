
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <memory>
#include <cmath>

#include "Student.h"
#include "DynamicArray.h"
#include "FileManager.h"
#include "Sorting.h"
#include "Searching.h"

using namespace std;

// Find student by ID using linear search
int findStudent(const DynamicArray<Student>& students, int id) {
    for (size_t i = 0; i < students.getSize(); ++i) {
        if (students.get(i).studentID == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Display all student records
void displayStudents(const DynamicArray<Student>& students) {
    if (students.isEmpty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n"
         << left << setw(12) << "ID"
         << setw(22) << "NAME"
         << setw(10) << "SCORE" << "\n";

    cout << string(44, '-') << "\n";

    for (size_t i = 0; i < students.getSize(); ++i) {
        const Student& s = students.get(i);

        cout << left << setw(12) << s.studentID
             << setw(22) << s.name
             << fixed << setprecision(1)
             << setw(10) << s.score << "\n";
    }

    cout << "\nTotal students: "
         << students.getSize() << "\n";
}

// Read an integer safely
int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            return value;
        }

        if (cin.eof()) {
            throw runtime_error("Input stream closed");
        }

        cout << "Invalid input. Enter a whole number.\n";
        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );
    }
}

// Read a valid score
double readScore() {
    double score;

    while (true) {
        cout << "Enter score (0-100): ";

        if (cin >> score &&
            isfinite(score) &&
            score >= 0 &&
            score <= 100) {

            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            return score;
        }

        if (cin.eof()) {
            throw runtime_error("Input stream closed");
        }

        cout << "Invalid score. Enter 0 to 100.\n";
        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );
    }
}

// Add a new student
void addStudent(DynamicArray<Student>& students) {
    int id = readInt("Enter student ID: ");

    if (id <= 0 || findStudent(students, id) != -1) {
        cout << "Invalid or duplicate student ID.\n";
        return;
    }

    string name;
    cout << "Enter student name: ";
    getline(cin, name);

    if (name.empty() ||
        name.find('|') != string::npos) {
        cout << "Invalid student name.\n";
        return;
    }

    double score = readScore();

    students.add({id, name, score});

    cout << "\nStudent added successfully!\n";
}

// Update an existing student's score
void updateStudent(DynamicArray<Student>& students) {
    int id = readInt("Enter student ID to update: ");
    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    Student updated = students.get(index);

    cout << "Current name: " << updated.name << "\n";
    cout << "Current score: " << updated.score << "\n";

    updated.score = readScore();

    if (students.update(index, updated)) {
        cout << "Student score updated successfully!\n";
    }
}

// Delete a student
void deleteStudent(DynamicArray<Student>& students) {
    int id = readInt("Enter student ID to delete: ");
    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    if (students.remove(index)) {
        cout << "Student deleted successfully!\n";
    }
}

// Linear search by student ID
void searchStudent(const DynamicArray<Student>& students) {
    int id = readInt("Enter student ID to search: ");
    int index = findStudent(students, id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    const Student& s = students.get(index);

    cout << "\nStudent found!\n";
    cout << "ID: " << s.studentID << "\n";
    cout << "Name: " << s.name << "\n";
    cout << "Score: " << s.score << "\n";
}

// Display register statistics
void showStatistics(const DynamicArray<Student>& students) {
    cout << "\nREGISTER STATISTICS\n";
    cout << "-------------------\n";
    cout << "Students: " << students.getSize() << "\n";
    cout << "Capacity: " << students.getCapacity() << "\n";

    if (students.isEmpty()) {
        cout << "No scores available.\n";
        return;
    }

    double total = 0;
    double highest = students.get(0).score;
    double lowest = students.get(0).score;

    for (size_t i = 0; i < students.getSize(); ++i) {
        double score = students.get(i).score;

        total += score;

        if (score > highest) highest = score;
        if (score < lowest) lowest = score;
    }

    cout << fixed << setprecision(2);
    cout << "Average: "
         << total / students.getSize() << "\n";
    cout << "Highest: " << highest << "\n";
    cout << "Lowest: " << lowest << "\n";
}

// Sort students by score
// false = insertion sort
// true = randomized quicksort
void sortByScore(
    const DynamicArray<Student>& students,
    bool useQuickSort
) {
    size_t n = students.getSize();

    if (n == 0) {
        cout << "No students to sort.\n";
        return;
    }

    unique_ptr<Student[]> records(new Student[n]);

    for (size_t i = 0; i < n; ++i) {
        records[i] = students.get(i);
    }

    auto byScore = [](const Student& a, const Student& b) {
        if (a.score != b.score) {
            return a.score < b.score;
        }
        return a.studentID < b.studentID;
    };

    if (useQuickSort) {
        quickSort(records.get(), n, byScore);
        cout << "\nRANDOMIZED QUICKSORT RESULTS\n";
    } else {
        insertionSort(records.get(), n, byScore);
        cout << "\nINSERTION SORT RESULTS\n";
    }

    cout << "---------------------------------\n";

    for (size_t i = 0; i < n; ++i) {
        cout << records[i].studentID << " - "
             << records[i].name << " - "
             << fixed << setprecision(1)
             << records[i].score << "\n";
    }

    cout << "\nTotal sorted records: " << n << "\n";
}

// Iterative binary search by student ID
void binarySearchStudent(
    const DynamicArray<Student>& students
) {
    size_t n = students.getSize();

    if (n == 0) {
        cout << "No students available.\n";
        return;
    }

    int target = readInt("Enter student ID to search: ");

    unique_ptr<Student[]> records(new Student[n]);

    for (size_t i = 0; i < n; ++i) {
        records[i] = students.get(i);
    }

    // Binary search requires sorted records
    auto byID = [](const Student& a, const Student& b) {
        return a.studentID < b.studentID;
    };

    insertionSort(records.get(), n, byID);

    auto compareID = [](const auto& a, const auto& b) {
        auto getID = [](const auto& value) {
            using ValueType =
                decay_t<decltype(value)>;

            if constexpr (is_same_v<ValueType, Student>) {
                return value.studentID;
            } else {
                return value;
            }
        };

        return getID(a) < getID(b);
    };

    int index = binarySearch(
        records.get(), n, target, compareID
    );

    if (index != -1) {
        cout << "\nStudent found using Binary Search!\n";
        cout << "ID: " << records[index].studentID << "\n";
        cout << "Name: " << records[index].name << "\n";
        cout << "Score: " << records[index].score << "\n";
    } else {
        cout << "\nStudent not found.\n";
    }
}

// Display the main menu
void showMenu() {
    cout << "\n=====================================\n";
    cout << "       STUDENT RESULTS REGISTER\n";
    cout << "           VICTORIA UNIVERSITY\n";
    cout << "=====================================\n";

    cout << "1. Display All Students\n";
    cout << "2. Add New Student\n";
    cout << "3. Update Student Results\n";
    cout << "4. Delete Student Record\n";
    cout << "5. Search Student by ID (Linear)\n";
    cout << "6. Save Student Records\n";
    cout << "7. View Register Statistics\n";
    cout << "8. Sort Students (Insertion Sort)\n";
    cout << "9. Sort Students (Randomized Quicksort)\n";
    cout << "10. Binary Search Student by ID\n";
    cout << "0. Exit\n";
}

// Main program
int main() {
    DynamicArray<Student> students;
    const string filename = "students.txt";

    try {
        if (!FileManager::loadStudents(filename, students)) {
            cout << "Unable to load records. Program stopped.\n";
            return 1;
        }

        cout << "Loaded " << students.getSize()
             << " student records successfully!\n";

        bool running = true;

        while (running) {
            showMenu();

            int choice = readInt("\nEnter your choice: ");

            switch (choice) {
                case 1:
                    displayStudents(students);
                    break;

                case 2:
                    addStudent(students);
                    break;

                case 3:
                    updateStudent(students);
                    break;

                case 4:
                    deleteStudent(students);
                    break;

                case 5:
                    searchStudent(students);
                    break;

                case 6:
                    if (FileManager::saveStudents(
                            filename, students)) {
                        cout << "Records saved successfully!\n";
                    } else {
                        cout << "Error saving records.\n";
                    }
                    break;

                case 7:
                    showStatistics(students);
                    break;

                case 8:
                    sortByScore(students, false);
                    break;

                case 9:
                    sortByScore(students, true);
                    break;

                case 10:
                    binarySearchStudent(students);
                    break;

                case 0:
                    running = false;
                    cout << "Exiting program.\n";
                    break;

                default:
                    cout << "Invalid menu choice.\n";
                    break;
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
