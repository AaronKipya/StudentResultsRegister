# STUDENT RESULTS REGISTER
## Data Structures and Algorithms Coursework

**Institution:** Victoria University, Kampala  
**Programme:** Bachelor of Computer Science  
**Student Name:** Aaron Kipya  
**Registration Number:** VU-BCS-2507-1211-EVE  
**Programming Language:** C++17  
**Project Repository:** https://github.com/AaronKipya/StudentResultsRegister

---

## 1. PROJECT OVERVIEW

The Student Results Register is a console-based C++ application developed to demonstrate fundamental concepts in Data Structures and Algorithms.

The application allows a user to maintain student academic records by adding, viewing, updating, deleting, searching, and sorting student information.

Instead of relying on the standard C++ vector container for storing the main student records, the project implements a custom dynamic array using templates and manual memory management.

The project demonstrates how data structures and algorithms work internally and how their performance can be measured and compared.

## 2. PROJECT OBJECTIVES

The objectives of this project are to:

1. Implement a custom templated dynamic array.
2. Store and manage student academic records.
3. Demonstrate dynamic memory allocation and automatic capacity expansion.
4. Implement insertion sort and randomized-pivot quicksort.
5. Implement linear search and iterative binary search.
6. Apply exception handling and index validation.
7. Read student records from a text file and save updates.
8. Test the correctness of the implemented operations.
9. Compare algorithm performance using execution-time measurements.
10. Apply Big-O notation to explain time complexity.

## 3. STUDENT RECORD STRUCTURE

Each student is represented by a `Student` structure defined in `Student.h`.

The structure contains three fields:

| Field | Data type | Description |
|---|---|---|
| studentID | int | Unique identifier intended for each student |
| name | string | Student's name |
| score | double | Student's academic score |

Example student record:

`101|John|78.5`

This represents a student with ID 101, name John, and academic score 78.5.

The application uses the pipe character (`|`) to separate fields in the data file.

## 4. CUSTOM DYNAMIC ARRAY

The project implements a templated dynamic array in `DynamicArray.h`.

A dynamic array is a data structure that stores elements in contiguous memory and can increase its storage capacity when additional elements are added.

Unlike a fixed-size array, the dynamic array does not require the final number of elements to be known in advance.

### 4.1 Initial capacity

The array begins with a capacity of two elements.

When this capacity becomes full, the array allocates a larger memory block and copies the existing elements into it.

### 4.2 Capacity doubling

The array doubles its capacity whenever more storage is required.

Example:

- Initial capacity: 2
- First expansion: 4
- Second expansion: 8
- Third expansion: 16
- Fourth expansion: 32

Capacity doubling reduces the frequency of memory reallocations.

Although an individual expansion requires O(n) time to copy existing elements, adding an element at the end has O(1) amortized time complexity.

### 4.3 Supported operations

The custom dynamic array supports:

- `add()` — Adds an element.
- `get()` — Retrieves an element using its index.
- `update()` — Replaces an existing element.
- `remove()` — Deletes an element and shifts subsequent elements.
- `clear()` — Removes all logical elements.
- `getSize()` — Returns the number of stored elements.
- `getCapacity()` — Returns the allocated capacity.
- `isEmpty()` — Checks whether the array contains any elements.

### 4.4 Memory management

The dynamic array manages its own dynamically allocated storage.

It includes a destructor to release allocated memory when an array object is destroyed.

A deep-copy constructor and copy-assignment operator allow arrays to be copied without sharing the same underlying memory.

This helps prevent unintended changes between independent array objects.

Invalid index access is handled through bounds checking.

## 5. APPLICATION FEATURES

The application provides an interactive menu through `main.cpp`.

### 5.1 Display student records

Displays the currently stored student records, including their IDs, names, and scores.

### 5.2 Add a student

Allows the user to enter a new student record.

### 5.3 Update a student

Allows an existing student record to be modified.

### 5.4 Delete a student

Removes a selected student record from the register.

### 5.5 Linear search

Searches through records sequentially to locate a matching student.

### 5.6 Save records

Writes the current student records to a text file.

### 5.7 Display statistics

Provides summary information about the stored student records.

### 5.8 Insertion sort

Arranges student records according to their academic scores using insertion sort.

### 5.9 Randomized quicksort

Arranges student records according to their academic scores using randomized-pivot quicksort.

### 5.10 Binary search

Searches for a student ID using iterative binary search.

The application first creates a sorted copy of the student records by ID, because binary search requires sorted input.

The sorting preparation and binary search are separate operations with different time complexities.

## 6. SORTING ALGORITHMS

The sorting algorithms are implemented as reusable comparator-based templates in `Sorting.h`.

### 6.1 Insertion sort

Insertion sort builds a sorted section of the array by inserting each new element into its correct position.

It is relatively simple to understand and performs well on small or nearly sorted datasets.

**Time complexity:**

- Best case: O(n)
- Average case: O(n²)
- Worst case: O(n²)

**Auxiliary space complexity:** O(1)

### 6.2 Randomized-pivot quicksort

Quicksort uses a divide-and-conquer approach.

The algorithm selects a pivot, partitions the elements around it, and sorts the resulting partitions.

This implementation selects pivots randomly to reduce dependence on particular input arrangements.

**Time complexity:**

- Expected: O(n log n)
- Worst case: O(n²)

The recursive implementation uses additional stack space. Its smaller-partition-first recursion strategy helps limit stack depth.

### 6.3 Comparator-based templates

Both sorting algorithms accept a comparison function.

This makes the algorithms reusable for different data types and ordering requirements.

For example, a comparator can order students by academic score or student ID.

## 7. SEARCHING ALGORITHMS

Searching functionality is provided by the application and the reusable algorithm in `Searching.h`.

### 7.1 Linear search

Linear search checks elements one after another until the required record is found or the search reaches the end.

**Time complexity:**

- Best case: O(1)
- Worst case: O(n)

Linear search does not require sorted input.

### 7.2 Iterative binary search

Binary search repeatedly reduces the search interval by comparing the target with an element near the middle.

If the target is smaller, the search continues in the lower section. If it is larger, the search continues in the upper section.

**Time complexity:**

- Best case: O(1)
- Worst case: O(log n)

**Auxiliary space complexity:** O(1)

Binary search requires the records to be sorted according to the same ordering used by the search comparator.

## 8. FILE HANDLING

File-handling functionality is implemented in `FileManager.h`.

The application loads student records from `students.txt`.

Example:

101|John|78.5  
102|Mary|85.0  
103|Peter|69.5  
104|Sarah|91.0  
105|David|73.0

Each line contains a student ID, student name, and academic score.

The file-loading logic validates important record fields, including positive student IDs and scores within the expected range of 0 to 100.

The application can also save updated records to a text file.

## 9. PROJECT FILE STRUCTURE

| File | Purpose |
|---|---|
| Student.h | Defines the Student structure |
| DynamicArray.h | Implements the custom templated dynamic array |
| FileManager.h | Provides student record file operations |
| Sorting.h | Implements insertion sort and randomized quicksort |
| Searching.h | Implements iterative binary search |
| main.cpp | Contains the interactive application |
| students.txt | Original sample student records |
| students_updated.txt | Saved student record output |
| tests.cpp | Automated test suite |
| sorting_test.cpp | Additional sorting tests |
| search_test.cpp | Additional searching tests |
| benchmark.cpp | Algorithm performance benchmark |
| benchmark_results.csv | Recorded benchmark measurements |
| README.txt | Project documentation |
| .gitignore | Excludes generated files from Git tracking |

## 10. SYSTEM REQUIREMENTS

The application requires:

- A C++17-compatible compiler.
- A terminal or command-line environment.
- A text editor or IDE, such as Visual Studio Code.

**Development environment used:**

- Windows
- Visual Studio Code
- MSYS2 UCRT64
- GCC/G++ 16.2.0
- Git for Windows

No external C++ libraries are required.

## 11. HOW TO COMPILE AND RUN

### Step 1: Download the project

Clone the GitHub repository:

`git clone https://github.com/AaronKipya/StudentResultsRegister.git`

Open the project folder:

`cd StudentResultsRegister`

### Step 2: Compile the main application

Run:

`g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe`

### Step 3: Run the application

On Windows PowerShell:

`.\main.exe`

The application loads the sample student records and displays its interactive menu.

Follow the displayed instructions to select operations.

## 12. HOW TO RUN THE AUTOMATED TESTS

Compile the test suite:

`g++ -std=c++17 -Wall -Wextra tests.cpp -o tests.exe`

Run:

`.\tests.exe`

The automated tests cover:

- Empty array initialization.
- Initial capacity.
- Invalid index handling.
- Updating an empty array.
- Removing from an empty array.
- Adding records.
- Capacity doubling.
- Updating records.
- Removing records and shifting elements.
- Deep-copy independence.
- Copy-assignment independence.
- Clearing records.
- Insertion sort correctness.
- Randomized quicksort correctness.
- Binary search with existing values.
- Binary search with missing values.
- Binary search on empty input.

**Recorded automated test results:**

Passed: 21  
Failed: 0

### Additional debug-mode testing

The project was also compiled with additional GCC assertions:

`g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 -D_GLIBCXX_ASSERTIONS tests.cpp -o tests_debug.exe`

Running this executable produced:

Passed: 21  
Failed: 0

This provides additional debugging evidence but is not equivalent to a dedicated memory-sanitizer test.

### Memory sanitizer availability

AddressSanitizer and UndefinedBehaviorSanitizer were attempted using the installed MSYS2 UCRT64 GCC toolchain.

Both attempts failed during linking because the corresponding sanitizer runtime libraries were unavailable (`-lasan` and `-lubsan`).

Therefore, successful sanitizer-based memory verification has not yet been established.

## 13. PERFORMANCE BENCHMARKING

Performance benchmarking is implemented in `benchmark.cpp`.

The program compares insertion sort with randomized quicksort using randomly generated integer datasets.

Each algorithm is executed three times for each input size.

The program calculates the average execution time in milliseconds and the ratio between consecutive input sizes.

Compile the benchmark:

`g++ -std=c++17 -O2 -Wall -Wextra benchmark.cpp -o benchmark.exe`

Run:

`.\benchmark.exe`

The program saves its measurements to `benchmark_results.csv`.

### Recorded results

| Input size | Insertion sort (ms) | Quicksort (ms) |
|---|---:|---:|
| 1,000 | 0.127 | 0.052 |
| 2,000 | 0.436 | 0.096 |
| 4,000 | 3.509 | 0.328 |
| 8,000 | 7.935 | 0.430 |
| 16,000 | 28.020 | 0.974 |
| 32,000 | 103.858 | 1.775 |
| 64,000 | 440.460 | 4.018 |

These measurements were obtained from the development computer using the optimized build.

At 64,000 elements, randomized quicksort was approximately 110 times faster than insertion sort.

The results illustrate the practical performance difference between algorithms with quadratic and expected O(n log n) time complexity.

Actual execution times may vary depending on hardware, compiler settings, and system activity.

## 14. TIME COMPLEXITY SUMMARY

| Operation | Time complexity |
|---|---|
| Add element at end | O(1) amortized |
| Access element by index | O(1) |
| Update element by index | O(1) |
| Remove element by index | O(n) |
| Linear search | O(n) |
| Insertion sort, average | O(n²) |
| Randomized quicksort, expected | O(n log n) |
| Binary search on sorted data | O(log n) |

If binary search is preceded by sorting, the overall cost must also include the sorting operation.

## 15. INSERTION SORT LOOP INVARIANT

A loop invariant is a statement that remains true before and after each iteration of a loop.

For insertion sort, the loop invariant is:

**At the beginning of each outer-loop iteration, the portion of the array before the current element is already sorted.**

### Initialization

Before the first outer-loop iteration, the first element forms a sorted section of length one.

A section containing only one element is already sorted.

### Maintenance

During each iteration, insertion sort takes the next element and inserts it into the correct position within the sorted section.

This preserves the sorted ordering and increases the sorted section by one element.

### Termination

When the outer loop finishes, every element has been inserted into the sorted section.

Therefore, the entire array is sorted.

This explains why insertion sort produces a correctly ordered result.

## 16. KEY LEARNING OUTCOMES

Through this project, the following concepts have been practiced:

- Designing a data structure using C++ templates.
- Managing dynamically allocated memory.
- Understanding pointers and array capacity.
- Applying deep-copy semantics.
- Implementing sorting and searching algorithms.
- Using comparison functions.
- Handling invalid array operations.
- Reading and writing structured text files.
- Designing and executing automated tests.
- Measuring algorithm performance.
- Comparing time complexity using Big-O notation.
- Using Git and GitHub for version control.

## 17. LIMITATIONS AND FUTURE IMPROVEMENTS

The application is a coursework demonstration rather than a production-ready student management system.

Potential improvements include:

1. Stronger validation of malformed file records.
2. Explicit prevention of duplicate student IDs.
3. More comprehensive input validation.
4. Additional file error handling.
5. More automated boundary and integration tests.
6. Dedicated memory-safety verification using a supported sanitizer environment.
7. A graphical user interface.
8. Database storage for larger student datasets.

## 18. VERSION CONTROL

The project uses Git for local version control and GitHub for public source-code hosting.

Repository:

https://github.com/AaronKipya/StudentResultsRegister

The repository contains the implementation, sample records, tests, benchmark program, and recorded benchmark results.

## 19. AI-ASSISTED DEVELOPMENT DECLARATION

AI assistance was used during the development of this coursework for explanations of C++ concepts, guidance on implementation, code drafting, debugging support, testing guidance, documentation, and interpretation of benchmark results.

The project was compiled and executed in the student's local development environment. The student participated in the implementation workflow and ran the recorded tests and benchmarks.

AI-generated suggestions and explanations should be reviewed against the actual implementation and coursework requirements before final submission.

## 20. CONCLUSION

The Student Results Register demonstrates the practical application of fundamental data structures and algorithms using C++.

The project implements a custom dynamic array, supports student record management, and includes sorting, searching, file handling, and automated testing.

Performance measurements show that randomized quicksort scales substantially better than insertion sort on the tested random datasets.

The project provides a practical foundation for understanding memory management, algorithm correctness, time complexity, software testing, and version control.

---

**End of README**