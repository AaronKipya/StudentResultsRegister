
#include <iostream>
#include "Student.h"
#include "Sorting.h"

using namespace std;

void display(const Student students[], size_t n) {
    for (size_t i = 0; i < n; ++i) {
        cout << students[i].studentID << " - "
             << students[i].name << " - "
             << students[i].score << "\n";
    }
}

int main() {
    Student students[] = {
        {101, "John", 78.5},
        {102, "Mary", 85.0},
        {103, "Peter", 69.5},
        {104, "Sarah", 91.0},
        {105, "David", 73.0}
    };

    constexpr size_t n = 5;

    Student insertionData[n];
    Student quickData[n];

    for (size_t i = 0; i < n; ++i) {
        insertionData[i] = students[i];
        quickData[i] = students[i];
    }

    auto byScore = [](const Student& a, const Student& b) {
        return a.score < b.score;
    };

    insertionSort(insertionData, n, byScore);
    quickSort(quickData, n, byScore);

    cout << "INSERTION SORT - BY SCORE\n";
    display(insertionData, n);

    cout << "\nQUICKSORT - BY SCORE\n";
    display(quickData, n);

    return 0;
}
