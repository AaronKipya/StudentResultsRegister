
#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <cstddef>
#include <random>
#include <utility>

// Insertion sort
template <typename T, typename Compare>
void insertionSort(T arr[], std::size_t n, Compare comp) {
    for (std::size_t i = 1; i < n; ++i) {
        T key = arr[i];
        std::size_t j = i;

        while (j > 0 && comp(key, arr[j - 1])) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = key;
    }
}

// Quicksort partition using a random pivot
template <typename T, typename Compare, typename RNG>
std::size_t partitionRandom(
    T arr[],
    std::size_t low,
    std::size_t high,
    Compare comp,
    RNG& rng
) {
    std::uniform_int_distribution<std::size_t>
        distribution(low, high);

    std::size_t pivotIndex = distribution(rng);
    std::swap(arr[pivotIndex], arr[high]);

    T pivot = arr[high];
    std::size_t i = low;

    for (std::size_t j = low; j < high; ++j) {
        if (comp(arr[j], pivot)) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    std::swap(arr[i], arr[high]);
    return i;
}

// Internal recursive quicksort
template <typename T, typename Compare, typename RNG>
void quickSortRecursive(
    T arr[],
    std::size_t low,
    std::size_t high,
    Compare comp,
    RNG& rng
) {
    while (low < high) {
        std::size_t pivot = partitionRandom(
            arr, low, high, comp, rng
        );

        // Recurse into the smaller partition first
        // to limit recursion depth.
        if (pivot - low < high - pivot) {
            if (pivot > low) {
                quickSortRecursive(
                    arr, low, pivot - 1, comp, rng
                );
            }
            low = pivot + 1;
        } else {
            if (pivot < high) {
                quickSortRecursive(
                    arr, pivot + 1, high, comp, rng
                );
            }
            if (pivot == 0) break;
            high = pivot - 1;
        }
    }
}

// Public randomized quicksort
template <typename T, typename Compare>
void quickSort(T arr[], std::size_t n, Compare comp) {
    if (n < 2) return;

    std::mt19937 rng(std::random_device{}());

    quickSortRecursive(arr, 0, n - 1, comp, rng);
}

#endif
