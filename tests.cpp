
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

#include "Student.h"
#include "DynamicArray.h"
#include "Sorting.h"
#include "Searching.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(bool condition, const string& testName) {
    if (condition) {
        cout << "[PASS] " << testName << "\n";
        ++passed;
    } else {
        cout << "[FAIL] " << testName << "\n";
        ++failed;
    }
}

int main() {
    cout << "STUDENT RESULTS REGISTER - TEST SUITE\n";
    cout << "=====================================\n\n";

    // TEST 1: Empty array
    DynamicArray<Student> students;

    check(students.isEmpty(), "New array is empty");
    check(students.getSize() == 0, "Initial size is zero");
    check(students.getCapacity() == 2, "Initial capacity is two");

    // TEST 2: Invalid access
    bool exceptionCaught = false;

    try {
        students.get(0);
    } catch (const out_of_range&) {
        exceptionCaught = true;
    }

    check(exceptionCaught, "Invalid index throws exception");

    // TEST 3: Invalid update and removal
    check(!students.update(0, {101, "John", 78.5}),
          "Cannot update empty array");

    check(!students.remove(0),
          "Cannot remove from empty array");

    // TEST 4: Add students
    students.add({101, "John", 78.5});
    students.add({102, "Mary", 85.0});

    check(students.getSize() == 2,
          "Two records added");

    check(students.getCapacity() == 2,
          "Capacity remains two");

    // TEST 5: Capacity doubling
    students.add({103, "Peter", 69.5});

    check(students.getSize() == 3,
          "Third record added");

    check(students.getCapacity() == 4,
          "Capacity doubled from 2 to 4");

    students.add({104, "Sarah", 91.0});
    students.add({105, "David", 73.0});

    check(students.getCapacity() == 8,
          "Capacity doubled from 4 to 8");

    // TEST 6: Update
    bool updated = students.update(
        2, {103, "Peter", 75.0}
    );

    check(updated &&
          students.get(2).score == 75.0,
          "Student score updated");

    // TEST 7: Removal
    bool removed = students.remove(1);

    check(removed &&
          students.getSize() == 4 &&
          students.get(1).studentID == 103,
          "Removal shifts records correctly");

    // TEST 8: Deep copy
    DynamicArray<Student> copied(students);

    copied.update(0, {101, "Changed", 50.0});

    check(students.get(0).name == "John",
          "Deep copy is independent");

    // TEST 9: Copy assignment
    DynamicArray<Student> assigned;
    assigned = students;

    assigned.remove(0);

    check(students.getSize() == 4 &&
          assigned.getSize() == 3,
          "Copy assignment is independent");

    // TEST 10: Clear
    DynamicArray<Student> cleared(students);
    cleared.clear();

    check(cleared.isEmpty(),
          "Clear removes all logical records");

    // TEST 11: Insertion sort
    int numbers1[] = {5, 2, 8, 1, 3};

    insertionSort(numbers1, 5,
        [](int a, int b) { return a < b; });

    check(numbers1[0] == 1 &&
          numbers1[4] == 8,
          "Insertion sort orders integers");

    // TEST 12: Randomized quicksort
    int numbers2[] = {9, 4, 7, 2, 6};

    quickSort(numbers2, 5,
        [](int a, int b) { return a < b; });

    check(numbers2[0] == 2 &&
          numbers2[4] == 9,
          "Randomized quicksort orders integers");

    // TEST 13: Binary search - found
    int sorted[] = {10, 20, 30, 40, 50};

    auto lessThan = [](int a, int b) {
        return a < b;
    };

    int found = binarySearch(sorted, 5, 30, lessThan);

    check(found == 2,
          "Binary search finds existing value");

    // TEST 14: Binary search - not found
    int missing = binarySearch(sorted, 5, 99, lessThan);

    check(missing == -1,
          "Binary search rejects missing value");

    // TEST 15: Binary search - empty array
    int emptySearch = binarySearch(sorted, 0, 30, lessThan);

    check(emptySearch == -1,
          "Binary search handles empty input");

    cout << "\n=====================================\n";
    cout << "TEST SUMMARY\n";
    cout << "Passed: " << passed << "\n";
    cout << "Failed: " << failed << "\n";
    cout << "=====================================\n";

    return failed == 0 ? 0 : 1;
}
