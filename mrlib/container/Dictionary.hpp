//
// Dictionary.hpp
// Archimedes
//
// Created by Matthew Remmel on 11/21/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.
//

/*
 * The purpose of this class was to add a full featured and generic
 * dictionary to C++.
 */


#ifndef MRLIB_DICTIONARY_HPP
#define MRLIB_DICTIONARY_HPP

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>


namespace mrlib {

    template <typename K, typename V>
    class Dictionary {
    private:
        bool _default_flag;
        V _default_value;

    public:
        // Internal Data
        std::map<K, V> _data;

        // Constructors
        Dictionary();
        Dictionary(const V& default_value);
        Dictionary(std::initializer_list<std::pair<const K, V>> i_list);
        Dictionary(const std::map<K, V>& map);
        Dictionary(const std::unordered_map<K, V>& map);
        Dictionary(const Dictionary<K, V>& dictionary);

        // Operator Overloading
        V&                      operator[](const K& key);
        Dictionary<K, V>&       operator=(const Dictionary<K, V>& dictionary);
        const Dictionary<K, V>  operator+(const Dictionary<K, V>& dictionary) const;
        Dictionary<K, V>&       operator+=(const Dictionary<K, V>& dictionary);
        bool                    operator==(const Dictionary<K, V>& dictionary) const;
        bool                    operator!=(const Dictionary<K, V>& dictionary) const;

        // Querying Dictionary
        V               objectForKey(const K& key);
        bool            containsKey(const K& key) const;
        size_t          size() const;
        bool            isEmpty() const;
        bool            hasDefaultValue() const;
        V               getDefaultValue() const;
        std::vector<K>  getKeys() const;
        std::vector<V>  getValues() const;

        // Adding Objects
        Dictionary<K, V>&  addObject(const K& key, const V& value);

        // Removing Objects
        Dictionary<K, V>&  remove(const K& key);
        Dictionary<K, V>&  removeObjects(const std::vector<K>& keys);
        Dictionary<K, V>&  removeAll();

        // Replace Objects
        Dictionary<K, V>&  replace(const K& key, const V& new_value);
        Dictionary<K, V>&  swap(const K& first_key, const K& second_key);

        // Comparing Dictionary
        bool  isEqualTo(const Dictionary<K, V>& dictionary) const;

        // Getting Standard Containers
        std::map<K, V>            std_map() const;
        std::unordered_map<K, V>  std_unordered_map() const;

        // String Representation
        std::string  description() const;
        std::string  inspect() const;

        // Dictionary Copy
        Dictionary<K, V>  copy() const;
    };
}


/////////////////////////////
// TEMPLATE IMPLEMENTATION //
/////////////////////////////

using namespace mrlib;

// Constructors
template <typename K, typename V>
Dictionary<K, V>::Dictionary() {
    this->_data = std::map<K, V>();
    this->_default_flag = false;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const V& default_value) {
    this->_data = std::map<K, V>();
    this->_default_flag = true;
    this->_default_value = default_value;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const std::map<K, V>& map) {
    this->_data = map;
    this->_default_flag = false;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const std::unordered_map<K, V>& map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        this->_data[it->first] = it->second;
    }
    this->_default_flag = false;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary<K, V>& dictionary) {
    this->_data = dictionary._data;
    this->_default_flag = dictionary._default_flag;
    this->_default_value = dictionary._default_value;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(std::initializer_list<std::pair<const K, V>> i_list) {
    this->_data = i_list;
    this->_default_flag = false;
}


// Operator Overloading
template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key) {
    if (_default_flag && !this->containsKey(key)) {
        this->_data[key] = this->_default_value;
        return this->_data[key];
    }
    else {
        return this->_data[key];
    }
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary<K, V>& dictionary) {
    // Check self assignment
    if (this == &dictionary) return *this;

    this->_data = dictionary._data;
    return *this;
}

template <typename K, typename V>
const Dictionary<K, V> Dictionary<K, V>::operator+(const Dictionary<K, V>& dictionary) const {
    Dictionary<K, V> buffer = this->_data;
    for (auto it : dictionary._data) {
        buffer[it.first] = it.second;
    }

    return buffer;
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator+=(const Dictionary<K, V>& dictionary) {
    for (auto it : dictionary._data) {
        this->_data[it.first] = it.second;
    }

    return *this;
}

template <typename K, typename V>
bool Dictionary<K, V>::operator==(const Dictionary<K, V>& dictionary) const {
    return this->_data == dictionary._data;
}

template <typename K, typename V>
bool Dictionary<K, V>::operator!=(const Dictionary<K, V>& dictionary) const {
    return this->_data != dictionary._data;
}


// Querying Dictionary
template <typename K, typename V>
V Dictionary<K, V>::objectForKey(const K& key) {
    if (this->_data.count(key) == 1) {
        return this->_data[key];
    }
    else {
        throw std::invalid_argument("Dictionary: Key does not exist in dictionary");
    }
}

template <typename K, typename V>
bool Dictionary<K, V>::containsKey(const K& key) const {
    return this->_data.count(key) == 1;
}

template <typename K, typename V>
size_t Dictionary<K, V>::size() const {
    return this->_data.size();
}

template <typename K, typename V>
bool Dictionary<K, V>::isEmpty() const {
    return this->_data.size() == 0;
}

template <typename K, typename V>
bool Dictionary<K, V>::hasDefaultValue() const {
    return this->_default_flag;
}

template <typename K, typename V>
V Dictionary<K, V>::getDefaultValue() const {
    if (this->_default_flag)
        return this->_default_value;
    else
        return V();
}

template <typename K, typename V>
std::vector<K> Dictionary<K, V>::getKeys() const {
    std::vector<K> keys = std::vector<K>(this->_data.size());
    size_t index = 0;
    for (auto it = this->_data.begin(); it != this->_data.end(); ++it) {
        keys[index] = it->first;
        ++index;
    }

    return keys;
}

template <typename K, typename V>
std::vector<V> Dictionary<K, V>::getValues() const {
    std::vector<V> values = std::vector<V>(this->_data.size());
    size_t index = 0;
    for (auto it = this->_data.begin(); it != this->_data.end(); ++it) {
        values[index] = it->second;
        ++index;
    }

    return values;
}


// Adding Objects
template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::addObject(const K& key, const V& value) {
    if (this->_data.count(key) == 0) {
        this->_data[key] = value;
        return *this;
    }
    else {
        throw std::invalid_argument("Dictionary: Cannot add key that already exists");
    }
}


// Removing Objects
template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::remove(const K& key) {
    this->_data.erase(key);
    return *this;
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::removeObjects(const std::vector<K>& keys) {
    for (const K& key : keys) {
        this->_data.erase(key);
    }

    return *this;
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::removeAll() {
    this->_data.clear();
    return *this;
}


// Replace Objects
template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::replace(const K& key, const V& new_value) {
    if (this->_data.count(key) == 1) {
        this->_data[key] = new_value;
        return *this;
    }
    else {
        throw std::invalid_argument("Dictionary: Cannot replace key that doesn't exist");
    }
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::swap(const K& first_key, const K& second_key) {
    if (this->_data.count(first_key) == 1 && this->_data.count(second_key) == 1) {
        V first = this->_data[first_key];
        this->_data[first_key] = this->_data[second_key];
        this->_data[second_key] = first;
        return *this;
    }
    else {
        throw std::invalid_argument("Dictionary: Cannot swap keys if one or both do not exist");
    }
}


// Comparing Dictionary
template <typename K, typename V>
bool Dictionary<K, V>::isEqualTo(const Dictionary<K, V>& dictionary) const {
    return this->_data == dictionary._data;
}


// Getting Standard Containers
template <typename K, typename V>
std::map<K, V> Dictionary<K, V>::std_map() const {
    return this->_data;
}

template <typename K, typename V>
std::unordered_map<K, V> Dictionary<K, V>::std_unordered_map() const {
    std::unordered_map<K, V> hash_map = std::unordered_map<K, V>();
    for (auto it : this->_data) {
        hash_map[it.first] = it.second;
    }

    return hash_map;
}


// String Representation
template <typename K, typename V>
std::string Dictionary<K, V>::description() const {
    std::ostringstream oss;
    oss << "{";

    size_t last = this->_data.size() - 1;
    size_t i = 0;

    for (auto it = this->_data.begin(); it != this->_data.end(); ++it) {
        oss << it->first << " => " << it->second;

        if (i != last) {
            oss << ", ";
            ++i;
        }
    }

    oss << "}";
    return oss.str();
}

template <typename K, typename V>
std::string Dictionary<K, V>::inspect() const {
    std::ostringstream oss;

    // Dictionary Address
    oss << "Address: " << this << " ";

    // Dictionary Size
    oss << "Size: " << this->_data.size() << " ";

    // Dictionary Contents
    oss << this->description();

    return oss.str();
}


// Dictionary Copy
template <typename K, typename V>
Dictionary<K, V> Dictionary<K, V>::copy() const {
    return Dictionary<K, V>(this->_data);
}

#endif // MRLIB_DICTIONARY_HPP