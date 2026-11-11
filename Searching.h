
#ifndef SEARCHING_H
#define SEARCHING_H

#include <cstddef>

// Iterative binary search on a sorted array
template <typename T, typename Key, typename Compare>
int binarySearch(
    const T arr[],
    std::size_t n,
    const Key& target,
    Compare comp
) {
    std::size_t left = 0;
    std::size_t right = n;

    while (left < right) {
        std::size_t mid = left + (right - left) / 2;

        if (comp(arr[mid], target)) {
            left = mid + 1;
        }
        else if (comp(target, arr[mid])) {
            right = mid;
        }
        else {
            return static_cast<int>(mid);
        }
    }

    return -1;
}

#endif
