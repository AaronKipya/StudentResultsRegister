
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "FileManager.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(bool condition, const string& name) {
    if (condition) {
        cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        cout << "[FAIL] " << name << "\n";
        failed++;
    }
}

void writeTestFile(const string& filename,
                   const string& contents) {
    ofstream file(filename);
    file << contents;
}

int main() {
    cout << "FILE MANAGER - VALIDATION TESTS\n";
    cout << "================================\n";

    const string filename = "test_students_temp.txt";

    DynamicArray<Student> students;

    // Test 1: Valid records
    writeTestFile(filename,
                  "101|John|78.5\n"
                  "102|Mary|85.0\n");

    check(FileManager::loadStudents(filename, students)
          && students.getSize() == 2,
          "Valid records load successfully");

    // Test 2: Duplicate IDs
    writeTestFile(filename,
                  "101|John|78.5\n"
                  "101|Mary|85.0\n");

    check(!FileManager::loadStudents(filename, students),
          "Duplicate student IDs rejected");

    // Test 3: Existing data preserved
    check(students.getSize() == 2 &&
          students.get(0).studentID == 101 &&
          students.get(1).studentID == 102,
          "Failed load preserves existing records");

    // Test 4: Negative score
    writeTestFile(filename, "103|Peter|-5\n");

    check(!FileManager::loadStudents(filename, students),
          "Negative scores rejected");

    // Test 5: Score above 100
    writeTestFile(filename, "103|Peter|105\n");

    check(!FileManager::loadStudents(filename, students),
          "Scores above 100 rejected");

    // Test 6: NaN score
    writeTestFile(filename, "103|Peter|nan\n");

    check(!FileManager::loadStudents(filename, students),
          "NaN scores rejected");

    // Test 7: Missing field
    writeTestFile(filename, "103|Peter\n");

    check(!FileManager::loadStudents(filename, students),
          "Missing fields rejected");

    // Test 8: Invalid ID
    writeTestFile(filename, "0|Peter|75\n");

    check(!FileManager::loadStudents(filename, students),
          "Non-positive IDs rejected");

    // Test 9: Save records
    const string output = "test_students_saved.txt";

    check(FileManager::saveStudents(output, students),
          "Student records saved successfully");

    // Test 10: Load saved records
    DynamicArray<Student> reloaded;

    check(FileManager::loadStudents(output, reloaded) &&
          reloaded.getSize() == 2 &&
          reloaded.get(0).studentID == 101 &&
          reloaded.get(1).studentID == 102,
          "Saved records load correctly");

    // Remove temporary test files
    std::remove(filename.c_str());
    std::remove(output.c_str());

    cout << "\n================================\n";
    cout << "TEST SUMMARY\n";
    cout << "Passed: " << passed << "\n";
    cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
