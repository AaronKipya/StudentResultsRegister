
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
private:
    T* data;
    std::size_t currentSize;
    std::size_t capacity;

    // Double capacity when the array becomes full
    void resize() {
        std::size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        try {
            for (std::size_t i = 0; i < currentSize; ++i) {
                newData[i] = data[i];
            }
        } catch (...) {
            delete[] newData;
            throw;
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor
    DynamicArray()
        : data(new T[2]), currentSize(0), capacity(2) {}

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Deep-copy constructor
    DynamicArray(const DynamicArray& other)
        : data(new T[other.capacity]),
          currentSize(0),
          capacity(other.capacity) {

        try {
            for (std::size_t i = 0; i < other.currentSize; ++i) {
                data[i] = other.data[i];
                ++currentSize;
            }
        } catch (...) {
            delete[] data;
            throw;
        }
    }

    // Copy assignment
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            DynamicArray temp(other);
            swap(temp);
        }
        return *this;
    }

    // Swap two arrays safely
    void swap(DynamicArray& other) noexcept {
        using std::swap;
        swap(data, other.data);
        swap(currentSize, other.currentSize);
        swap(capacity, other.capacity);
    }

    // Add a record
    void add(const T& value) {
        if (currentSize == capacity) {
            resize();
        }

        data[currentSize] = value;
        ++currentSize;
    }

    // Retrieve a record
    const T& get(std::size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Invalid array index");
        }

        return data[index];
    }

    // Update an existing record
    bool update(std::size_t index, const T& value) {
        if (index >= currentSize) {
            return false;
        }

        data[index] = value;
        return true;
    }

    // Remove a record by index
    bool remove(std::size_t index) {
        if (index >= currentSize) {
            return false;
        }

        for (std::size_t i = index; i + 1 < currentSize; ++i) {
            data[i] = data[i + 1];
        }

        --currentSize;
        return true;
    }

    // Remove all records
    void clear() {
        currentSize = 0;
    }

    // Number of stored records
    std::size_t getSize() const {
        return currentSize;
    }

    // Total allocated slots
    std::size_t getCapacity() const {
        return capacity;
    }

    // Check whether the array is empty
    bool isEmpty() const {
        return currentSize == 0;
    }
};

#endif
