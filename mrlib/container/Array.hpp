//
// Array.hpp
// Archimedes
//
// Created by Matthew Remmel on 1/5/16.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.
//

/*
 * The purpose of this class was to add a full featured and generic
 * array class to C++.
 */


#ifndef MRLIB_ARRAY_HPP
#define MRLIB_ARRAY_HPP

#include <vector>
#include <string>
#include <sstream>

// Index Constants
#ifndef NO_INDEX
#define NO_INDEX -1ull
#endif

// Index out of bounds exception
#define ARRAY_OUT_BOUNDS std::invalid_argument("Array: Out of bounds exception")
#define ARRAY_INV_FROM_TO std::invalid_argument("Array: from_index must be less than to_index")

namespace mrlib {

    template <typename T>
    class Array {
    public:
        // Internal Data
        std::vector<T> _data;

        // Constructors
        Array<T>();
        Array<T>(size_t size);
        Array<T>(std::initializer_list<T> i_list);
        Array<T>(const std::vector<T>& vector);
        Array<T>(const Array<T>& array);
        Array<T>(Array<T>&& array);

        // Operator Overloading
        T&              operator[](const size_t index);
        Array<T>&       operator=(const Array<T>& array);
        Array<T>&       operator=(Array<T>&& array);
        const Array<T>  operator+(const Array<T>& array) const;
        Array<T>&       operator+=(const Array<T>& array);
        bool            operator==(const Array<T>& array) const;
        bool            operator!=(const Array<T>& array) const;

        // Querying Array
        T       peak() const;
        T       objectAtIndex(size_t index) const;
        T       firstObject() const;
        T       lastObject() const;
        bool    contains(const T& object) const;
        bool    containsAll(const Array<T>& objects) const;
        size_t  size() const;
        bool    isEmpty() const;

        // Adding Objects
        Array<T>&  add(const T& object);
        Array<T>&  addAll(const Array<T>& objects);
        Array<T>&  insert(const T& object, size_t index);

        // Removing Objects
        T          pop();
        Array<T>&  remove(const T& object);
        Array<T>&  removeIndex(size_t index);
        Array<T>&  removeRange(size_t from_index, size_t to_index);
        Array<T>&  removeAll(const T& object);
        Array<T>&  removeAll(const Array<T>& objects);
        Array<T>&  removeAll();
        Array<T>&  retainAll(const Array<T>& objects);

        // Replace Object
        Array<T>&  replace(const T& old_object, const T& new_object);
        Array<T>&  replaceLast(const T& old_object, const T& new_object);
        Array<T>&  replaceIndex(size_t index, const T& new_object);
        Array<T>&  replaceAll(const T& old_object, const T& new_object);
        Array<T>&  swap(size_t first_index, size_t second_index);

        // Dividing Array
        Array<T>  subarray(size_t from_index, size_t to_index) const;
        Array<T>  subarrayFromIndex(size_t index) const;
        Array<T>  subarrayToIndex(size_t index) const;

        // Finding Objects
        size_t  indexOf(const T& object, size_t min_index = 0) const;
        size_t  indexOfLast(const T& object) const;
        size_t  indexOfLast(const T& object, size_t max_index) const;
        size_t  indexOfObjectInRange(const T& object, size_t from_index, size_t to_index) const;

        // Sorting Array
        Array<T>&  sort();

        // Reversing Array
        Array<T>&  reverse();

        // Comparing Array
        bool  isEqualTo(const Array<T>& array) const;

        // Array Copy
        Array<T>  copy() const;

        // Getting Standard Containers
        std::vector<T>  std_vector() const;

        // String Representation
        std::string  description() const;
        std::string  inspect() const;
    };


    /////////////////////////////
    // TEMPLATE IMPLEMENTATION //
    /////////////////////////////

    // Constructors
    template <typename T>
    Array<T>::Array() {
        this->_data = std::vector<T>();
    }

    template <typename T>
    Array<T>::Array(size_t size) {
        this->_data = std::vector<T>(size);
    }

    template <typename T>
    Array<T>::Array(std::initializer_list<T> i_list) {
        this->_data = std::vector<T>(i_list);
    }

    template <typename T>
    Array<T>::Array(const std::vector<T>& vector) {
        this->_data = vector;
    }

    template <typename T>
    Array<T>::Array(const Array<T>& array) {
        this->_data = array._data;
    }

    template <typename T>
    Array<T>::Array(Array<T>&& array) {
        this->_data = array._data;
    }


    // Operator Overloading
    template <typename T>
    T& Array<T>::operator[](const size_t index) {
        if (index < this->_data.size()) {
            return this->_data[index];
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T>& Array<T>::operator=(const Array<T>& array) {
        this->_data = array._data;
        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::operator=(Array<T>&& array) {
        this->_data = array._data;
        return *this;
    }

    template <typename T>
    const Array<T> Array<T>::operator+(const Array<T>& array) const {
        Array<T> buffer = Array();
        buffer._data.insert(buffer._data.begin(), this->_data.begin(), this->_data.end());
        buffer._data.insert(buffer._data.end(), array._data.begin(), array._data.end());
        return buffer;
    }

    template <typename T>
    Array<T>& Array<T>::operator+=(const Array<T>& array) {
        if (this == &array) return *this;
        this->_data.insert(this->_data.end(), array._data.begin(), array._data.end());
        return *this;
    }

    template <typename T>
    bool Array<T>::operator==(const Array<T>& array) const {
        return this->_data == array._data;
    }

    template <typename T>
    bool Array<T>::operator!=(const Array<T>& array) const {
        return this->_data != array._data;
    }


    // Querying Array
    template <typename T>
    T Array<T>::peak() const {
        if (this->_data.size() > 0) {
            return this->_data[this->_data.size() - 1];
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    T Array<T>::objectAtIndex(size_t index) const {
        if (index < this->_data.size()) {
            return this->_data[index];
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    T Array<T>::firstObject() const {
        if (this->_data.size() > 0) {
            return this->_data[0];
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    T Array<T>::lastObject() const {
        if (this->_data.size() > 0) {
            return this->_data[this->_data.size() - 1];
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    bool Array<T>::contains(const T& object) const {
        return this->indexOf(object) != NO_INDEX;
    }

    template <typename T>
    bool Array<T>::containsAll(const Array<T>& objects) const {
        for (const T& object : objects._data) {
            if (this->indexOf(object) == NO_INDEX) return false;
        }

        return true;
    }

    template <typename T>
    size_t Array<T>::size() const {
        return this->_data.size();
    }

    template <typename T>
    bool Array<T>::isEmpty() const {
        return this->_data.empty();
    }


    // Adding Objects
    template <typename T>
    Array<T>& Array<T>::add(const T& object) {
        this->_data.push_back(object);
        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::addAll(const Array<T>& objects) {
        for (const T& object : objects._data) {
            this->_data.push_back(object);
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::insert(const T& object, size_t index) {
        if (index < this->_data.size()) {
            this->_data.insert(this->_data.begin() + index, object);
            return *this;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }


    // Removing Objects
    template <typename T>
    T Array<T>::pop() {
        if (this->_data.size() > 0) {
            T object = this->_data.back();
            this->_data.pop_back();
            return object;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T>& Array<T>::remove(const T& object) {
        size_t index = this->indexOf(object);

        if (index != NO_INDEX) {
            this->_data.erase(this->_data.begin() + index);
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::removeIndex(size_t index) {
        if (index < this->_data.size()) {
            this->_data.erase(this->_data.begin() + index);
            return *this;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T>& Array<T>::removeRange(size_t from_index, size_t to_index) {
        if (from_index > to_index) {
            throw ARRAY_INV_FROM_TO;
        }

        if (from_index < this->_data.size() && to_index < this->_data.size()) {
            this->_data.erase(this->_data.begin() + from_index, this->_data.begin() + to_index);
            return *this;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T>& Array<T>::removeAll(const T& object) {
        this->_data.erase(std::remove(this->_data.begin(), this->_data.end(), object), this->_data.end());
        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::removeAll(const Array<T>& objects) {
        for (const T& object : objects._data) {
            this->removeAll(object);
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::removeAll() {
        this->_data.clear();
        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::retainAll(const Array<T>& objects) {
        std::vector<T> new_array = std::vector<T>();

        for (const T& object : this->_data) {
            if (objects.contains(object)) {
                new_array.push_back(object);
            }
        }

        this->_data = new_array;
        return *this;
    }


    // Replace Object
    template <typename T>
    Array<T>& Array<T>::replace(const T& old_object, const T& new_object) {
        size_t index = this->indexOf(old_object);
        if (index != NO_INDEX) {
            this->_data[index] = new_object;
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::replaceLast(const T& old_object, const T& new_object) {
        size_t index = this->indexOfLast(old_object);
        if (index != NO_INDEX) {
            this->_data[index] = new_object;
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::replaceIndex(size_t index, const T& new_object) {
        if (index < this->_data.size()) {
            this->_data[index] = new_object;
            return *this;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T>& Array<T>::replaceAll(const T& old_object, const T& new_object) {
        for (size_t i = 0; i < this->_data.size(); ++i) {
            if (this->_data[i] == old_object) {
                this->_data[i] = new_object;
            }
        }

        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::swap(size_t first_index, size_t second_index) {
        if (first_index < this->_data.size() && second_index < this->_data.size()) {
            T temp = this->_data[first_index];
            this->_data[first_index] = this->_data[second_index];
            this->_data[second_index] = temp;
            return *this;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }


    // Dividing Array
    template <typename T>
    Array<T> Array<T>::subarray(size_t from_index, size_t to_index) const {
        if (from_index > to_index) {
            throw ARRAY_INV_FROM_TO;
        }

        if (from_index < this->_data.size() && to_index < this->_data.size()) {
            Array<T> subarray = Array<T>();
            std::copy(this->_data.begin() + from_index, this->_data.begin() + to_index + 1, std::back_inserter(subarray._data));
            return subarray;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T> Array<T>::subarrayFromIndex(size_t index) const {
        if (index < this->_data.size()) {
            Array<T> subarray = Array<T>();
            std::copy(this->_data.begin() + index, this->_data.end(), std::back_inserter(subarray._data));
            return subarray;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    Array<T> Array<T>::subarrayToIndex(size_t index) const {
        if (index < this->_data.size()) {
            Array<T> subarray = Array<T>();
            std::copy(this->_data.begin(), this->_data.begin() + index, std::back_inserter(subarray._data));
            return subarray;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }


    // Finding Objects
    template <typename T>
    size_t Array<T>::indexOf(const T& object, size_t min_index) const {
        if (min_index < this->_data.size()) {
            for (size_t i = min_index; i < this->_data.size(); ++i) {
                if (this->_data[i] == object) {
                    return i;
                }
            }

            return NO_INDEX;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    size_t Array<T>::indexOfLast(const T& object) const {
        return this->indexOfLast(object, this->_data.size() -1);
    }

    template <typename T>
    size_t Array<T>::indexOfLast(const T &object, size_t max_index) const {
        if (max_index < this->_data.size()) {
            for (size_t i = max_index; i < this->_data.size(); --i) {
                if (this->_data[i] == object) {
                    return i;
                }
            }

            return NO_INDEX;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }

    template <typename T>
    size_t Array<T>::indexOfObjectInRange(const T& object, size_t from_index, size_t to_index) const {
        if (from_index > to_index) {
            throw ARRAY_INV_FROM_TO;
        }

        if (from_index < this->_data.size() && to_index < this->_data.size()) {
            for (size_t i = from_index; i < to_index; ++i) {
                if (object == this->_data[i]) {
                    return i;
                }
            }

            return NO_INDEX;
        }
        else {
            throw ARRAY_OUT_BOUNDS;
        }
    }


    // Sorting Array
    template <typename T>
    Array<T>& Array<T>::sort() {
        std::sort(this->_data.begin(), this->_data.end());
        return *this;
    }


    // Reversing Array
    template <typename T>
    Array<T>& Array<T>::reverse() {
        std::reverse(this->_data.begin(), this->_data.end());
        return *this;
    }


    // Comparing Array
    template <typename T>
    bool Array<T>::isEqualTo(const Array<T>& array) const {
        size_t size = this->_data.size();
        if (size != array._data.size()) return false;

        for (size_t i = 0; i < size; ++i) {
            if (this->_data[i] != array._data[i]) return false;
        }

        return true;
    }


    // Array Copy
    template <typename T>
    Array<T> Array<T>::copy() const {
        return Array<T>(this->_data);
    }


    // Getting Standard Containers
    template <typename T>
    std::vector<T> Array<T>::std_vector() const {
        return this->_data;
    }


    // String Representation
    template <typename T>
    std::string Array<T>::description() const {
        std::ostringstream oss;
        oss << "[";

        size_t last = this->_data.size() - 1;
        for (size_t i = 0; i < this->_data.size(); ++i) {
            oss << this->_data[i];

            if (i != last) {
                oss << ", ";
            }
        }

        oss << "]";
        return oss.str();
    }

    template <typename T>
    std::string Array<T>::inspect() const {
        std::ostringstream oss;

        // Array Address
        oss << "Address: " << this << " ";

        // Array Size
        oss << "Size: " << this->_data.size() << " ";

        // Array Contents
        oss << this->description();

        return oss.str();
    }
}

#endif // MRLIB_ARRAY_HPP
