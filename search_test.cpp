
#include <iostream>
#include "Student.h"
#include "Sorting.h"
#include "Searching.h"
#include <type_traits>
#include <utility>  
using namespace std;

int main() {
    Student students[] = {
        {105, "David", 73.0},
        {101, "John", 78.5},
        {104, "Sarah", 91.0},
        {102, "Mary", 85.0},
        {103, "Peter", 69.5}
    };

    constexpr size_t n = 5;

    // Sort records by student ID first
    auto byID = [](const Student& a, const Student& b) {
        return a.studentID < b.studentID;
    };

    insertionSort(students, n, byID);

    cout << "STUDENTS SORTED BY ID\n";

    for (const Student& s : students) {
        cout << s.studentID << " - " << s.name << "\n";
    }

    // Compare Student objects and integer IDs
    auto compareID = [](const auto& a, const auto& b) {
        auto getID = [](const auto& value) {
            if constexpr (
                std::is_same_v<std::decay_t<decltype(value)>, Student>
            ) {
                return value.studentID;
            } else {
                return value;
            }
        };

        return getID(a) < getID(b);
    };

    int found = binarySearch(students, n, 103, compareID);

    if (found != -1) {
        cout << "\nStudent found: "
             << students[found].name << "\n";
    } else {
        cout << "\nStudent not found.\n";
    }

    int missing = binarySearch(students, n, 999, compareID);

    cout << "Search for ID 999: "
         << (missing == -1 ? "Not found" : "Found")
         << "\n";

    return 0;
}
