//
// String.hpp
// Archimedes
//
// Created by Matthew Remmel on 7/29/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.
//

/*
 * The purpose of this class was to add a full featured string
 * class to C++.
 */


#ifndef MRLIB_STRING_HPP
#define MRLIB_STRING_HPP

#include <string>
#include <fstream>
#include <vector>
#include <sstream>


// Index Constants
#ifndef NO_INDEX
#define NO_INDEX -1ull
#endif

// String Constants
static const std::string ASCII_UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string ASCII_LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
static const std::string ASCII_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const std::string ASCII_WHITESPACE = " \t\r\n\v\f";
static const std::string ASCII_PUNCTUATION = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
static const std::string ASCII_DIGITS = "0123456789";
static const std::string ASCII_HEX_DIGITS = "0123456789abcdefABCDEF";
static const std::string ASCII_OCT_DIGITS = "01234567";
static const std::string ASCII_PRINTABLE = ASCII_LETTERS + ASCII_DIGITS + ASCII_PUNCTUATION + ASCII_WHITESPACE;


namespace mrlib {

    class String {
    public:
        // Internal Data
        std::string _data;

        // Constructors
        String();
        String(char character);
        String(const char* string);
//        String(const std::basic_string& string);
        String(const std::string& string);
        String(const String& string);

        // Numeric Constructors
        String(int value);
        String(long value);
        String(long long value);
        String(unsigned value);
        String(unsigned long value);
        String(unsigned long long value);
        String(float value);
        String(double value);
        String(long double value);

        // Operator Overloading
        char&         operator[](size_t index);
        String&       operator=(const String& string);
        const String  operator+(const String& string) const;
        String&       operator+=(const String& string);
        bool          operator==(const String& string) const;
        bool          operator!=(const String& string) const;
        // TODO: < and > overload <= >=

        // User Defined Conversions
        //operator std::string() const;

        // Creating and Initializing Strings
        static String  StringWithContentsOfFile(const String& path);

        // Writing to a File
        void  writeToFile(const String& path);
        void  appendToFile(const String& path);

        // String Length
        size_t  length() const;

        // Getting / Setting Characters
        char     characterAtIndex(size_t i) const;
        void     setCharacterAtIndex(const char c, size_t index);
        String&  setValue(const String& string);

        // Changing Case
        String&  toLowerCase();
        String&  toUpperCase();
        String&  toCapitalCase();
        String&  swapCase();

        // Combining Strings
        String&  append(const String& string);

        // Dividing Strings
        String               substring(size_t from_index, size_t to_index) const;
        String               substringFromIndex(size_t index) const;
        String               substringToIndex(size_t index) const;
        std::vector<String>  split(const String& delimiter) const;

        // Inserting String
        String&  insert(const String& string, size_t index);

        // Trimming String
        String&  trim(const String& characters = ASCII_WHITESPACE);
        String&  trimLeading(const String& characters = ASCII_WHITESPACE);
        String&  trimTrailing(const String& characters = ASCII_WHITESPACE);
        // TODO: remove extra spaces / whitespace in string

        // Reversing String
        String&  reverse();

        // Padding String
        String&  pad(const String& string, size_t count);
        String&  padLeft(const String& string, size_t count);
        String&  padRight(const String& string, size_t count);
        // TODO: Pad to length. Pad if length is smaller than some parameter. Can use std::resize
        // TODO: Can be used for creating pretty printed tables and such

        // Replacing String
        String&  replace(const String& old_string, const String& new_string);
        String&  replaceLast(const String& old_string, const String& new_string);
        String&  replaceAll(const String& old_string, const String& new_string);
        // TODO: Parameter as regex

        // Removing String
        String&  remove(const String& string);
        String&  removeLast(const String& string);
        String&  removeRange(size_t from_index, size_t to_index);
        String&  removeCharacters(const String& string);
        String&  removeAll(const String& string);

        // Searching String
        bool    contains(const String& string) const;
        size_t  indexOf(const String& string) const;
        size_t  indexOf(const String& string, size_t min_index) const;
        size_t  indexOfLast(const String& string) const;
        size_t  indexOfLast(const String& string, size_t max_index) const;

        // String Comparison
        bool  isEqualTo(const String& string) const;
        bool  isEqualToIgnoreCase(const String& string) const;
        int   compare(const String& string) const;
        int   compareIgnoreCase(const String& string) const;
        //int compareOverRange(const String& string, size_t from_index, size_t to_index);

        // Numeric Values
        int                 intValue() const;
        long                longValue() const;
        long long           longLongValue() const;
        unsigned            unsignedValue() const;
        unsigned long       unsignedLongValue() const;
        unsigned long long  unsignedLongLongValue() const;
        float               floatValue() const;
        double              doubleValue() const;
        long double         longDoubleValue() const;
        bool                boolValue() const;


        // String Copy
        String  copy() const;

        // Getting Standard Containers
        const char*  c_string() const;
        std::string  std_string() const;

        // String Representation
        std::string  description() const;
        std::string  inspect() const;

        // TODO: matches regex / index of regex pattern
    };


    /////////////////////////////
    // TEMPLATE IMPLEMENTATION //
    /////////////////////////////

    // Constructors
    inline
    String::String() {
        this->_data = "";
    }

    inline
    String::String(char character) {
        this->_data = character;
    }

    inline
    String::String(const char* string) {
        this->_data = string;
    }

    inline
    String::String(const std::string& string) {
        this->_data = string;
    }

    inline
    String::String(const String& string) {
        this->_data = string._data;
    }

    // Numeric Constructors
    inline
    String::String(int value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(long value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(long long value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(unsigned value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(unsigned long value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(unsigned long long value) {
        this->_data = std::to_string(value);
    }

    inline
    String::String(float value) {
        this->_data = std::to_string(value);
        this->trimTrailing("0");
    }

    inline
    String::String(double value) {
        this->_data = std::to_string(value);
        this->trimTrailing("0");
    }

    inline
    String::String(long double value) {
        this->_data = std::to_string(value);
        this->trimTrailing("0");
    }


    // Operator Overloading
    inline
    char& String::operator[](size_t index) {
        if(index < this->_data.length()) {
            return this->_data[index];
        }
        else {
            throw std::invalid_argument("Out of bounds exception");
        }
    }

    inline
    String& String::operator=(const String& string) {
        // Check for self assignment
        if (this == &string) return *this;

        this->_data = string._data;
        return *this;
    }

    inline
    const String String::operator+(const String& string) const {
        return String(this->_data + string._data);
    }

    inline
    String& String::operator+=(const String& string) {
        this->_data += string._data;
        return *this;
    }

    inline
    bool String::operator==(const String& string) const {
        if (this == &string) return true;
        return this->_data == string._data;
    }

    inline
    bool String::operator!=(const String& string) const {
        if (this == &string) return false;
        return this->_data != string._data;
    }


    // Creating and Initializing Strings
    inline
    String String::StringWithContentsOfFile(const String& path) {
        try {
            std::ifstream ifs;
            ifs.open(path._data.c_str());

            if (ifs.is_open()) {
                std::string _data((std::istreambuf_iterator<char>(ifs)),
                                  (std::istreambuf_iterator<char>()));
                ifs.close();
                return String(_data);
            }
            else {
                throw std::invalid_argument("Error opening file at path: " + path.std_string());
            }
        }
        catch(int e) {
            throw std::invalid_argument("Exception opening file at: " + path.std_string() + " error: " + std::to_string(e));
        }
    }


    // Writing to a File
    inline
    void String::writeToFile(const String& path) {
        try {
            std::ofstream ofs;
            ofs.open(path._data.c_str());

            if (ofs.is_open()) {
                ofs << this->_data;
                ofs.close();
            }
            else {
                throw std::invalid_argument("Error opening file at path: " + path.std_string());
            }
        }
        catch (int e) {
            throw std::invalid_argument("Exception opening file at: " + path.std_string() + " error: " + std::to_string(e));
        }
    }

    inline
    void String::appendToFile(const String& path) {
        try {
            std::ofstream ofs;
            ofs.open(path._data.c_str(), std::ios::app);

            if (ofs.is_open()) {
                ofs << this->_data;
                ofs.close();
            }
            else {
                throw std::invalid_argument("Error opening file at path: " + path.std_string());
            }
        }
        catch (int e) {
            throw std::invalid_argument("Exception opening file at: " + path.std_string() + " error: " + std::to_string(e));
        }
    }


    // String Length
    inline
    size_t String::length() const {
        return this->_data.length();
    }


    // Getting / Setting Characters
    inline
    char String::characterAtIndex(size_t i) const {
        if (i < this->_data.length()) {
            return this->_data[i];
        }
        else {
            throw std::invalid_argument("Out of bounds exception");
        }
    }

    inline
    void String::setCharacterAtIndex(char c, size_t index) {
        if (index < this->_data.length()) {
            this->_data[index] = c;
        }
        else {
            throw std::invalid_argument("Out of bounds exception");
        }
    }

    inline
    String& String::setValue(const String& string) {
        this->_data = string._data;
        return *this;
    }


    // Changing Case
    inline
    String& String::toLowerCase() {
        for (size_t i = 0; i < this->_data.length(); ++i) {
            this->_data[i] = (char)tolower(this->_data[i]);
        }

        return *this;
    }

    inline
    String& String::toUpperCase() {
        for (size_t i = 0; i < this->_data.length(); ++i) {
            this->_data[i] = (char)toupper(this->_data[i]);
        }

        return *this;
    }

    inline
    String& String::toCapitalCase() {
        this->_data[0] = (char)toupper(this->_data[0]);
        for (size_t i = 1; i < this->_data.length(); ++i) {
            if (this->_data[i - 1] == ' ') {
                this->_data[i] = (char)toupper(this->_data[i]);
            }
        }

        return *this;
    }

    inline
    String& String::swapCase() {
        size_t length = this->_data.length();

        for (size_t i = 0; i < length; ++i) {
            if (islower(this->_data[i])) {
                this->_data[i] = (char)toupper(this->_data[i]);
            }
            else if (isupper(this->_data[i])) {
                this->_data[i] = (char)tolower(this->_data[i]);
            }
        }

        return *this;
    }


    // Combining Strings
    inline
    String& String::append(const String& string) {
        this->_data.append(string._data);
        return *this;
    }


    // Dividing Strings
    inline
    String String::substring(size_t from_index, size_t to_index) const {
        if (from_index > to_index) throw std::invalid_argument("from_index must be less than to_index");
        if (to_index < this->_data.length()) {
            return this->_data.substr(from_index, to_index - from_index);
        }
        else {
            throw std::invalid_argument("Out of range exception");
        }
    }

    inline
    String String::substringFromIndex(size_t index) const {
        if (index < this->_data.length()) {
            return this->_data.substr(index);
        }
        else {
            throw std::invalid_argument("Out of range exception");
        }
    }

    inline
    String String::substringToIndex(size_t index) const {
        if (index < this->_data.length()) {
            return this->_data.substr(0, index);
        }
        else {
            throw std::invalid_argument("Out of range exception");
        }
    }

    inline
    std::vector<String> String::split(const String& delimiter) const {
        std::vector<String> output;
        size_t delim_length = delimiter._data.length();

        if (delim_length == 0) {
            for (size_t i = 0; i < this->_data.length(); ++i) {
                output.push_back(this->_data[i]);
            }

            return output;
        }

        size_t element_begin = 0;
        size_t element_end = 0;

        while ((element_end = this->_data.find(delimiter.std_string(), element_end)) != NO_INDEX) {
            output.push_back(this->_data.substr(element_begin, element_end - element_begin));
            element_end += delim_length;
            element_begin = element_end;
        }

        output.push_back(this->_data.substr(element_begin, this->_data.length() - element_begin));

        return output;
    }


    // Inserting String
    inline
    String& String::insert(const String& string, size_t index) {
        if (index < this->_data.length()) {
            this->_data.insert(index, string.std_string());
            return *this;
        }
        else {
            throw std::invalid_argument("Out of bounds exception");
        }
    }


    // Trimming String
    inline
    String& String::trim(const String& characters) {
        this->trimLeading(characters);
        this->trimTrailing(characters);
        return *this;
    }

    inline
    String& String::trimLeading(const String& characters) {
        this->_data.erase(0, this->_data.find_first_not_of(characters.c_string()));
        return *this;
    }

    inline
    String& String::trimTrailing(const String& characters) {
        size_t last_not_of = this->_data.find_last_not_of(characters.c_string()) + 1;
        this->_data.erase(last_not_of, this->_data.length() - last_not_of);
        return *this;
    }


    // Reversing String
    inline
    String& String::reverse() {
        std::string buffer = "";

        for (size_t i = this->_data.length(); i > 0; --i) {
            buffer += this->_data[i - 1];
        }

        this->_data = buffer;

        return *this;
    }


    // Padding
    inline
    String& String::pad(const String& string, size_t count) {
        this->padLeft(string, count);
        this->padRight(string, count);
        return *this;
    }

    inline
    String& String::padLeft(const String& string, size_t count) {
        std::string pad_string = "";

        for (size_t i = 0; i < count; ++i) {
            pad_string += string._data;
        }

        this->_data.insert(0, pad_string);

        return *this;
    }

    inline
    String& String::padRight(const String& string, size_t count) {
        std::string pad_string = "";

        for (size_t i = 0; i < count; ++i) {
            pad_string += string._data;
        }

        this->_data.insert(this->_data.length(), pad_string);

        return *this;
    }


    // Replacing String
    inline
    String& String::replace(const String& old_string, const String& new_string) {
        size_t target_length = old_string._data.length();
        size_t target_index = this->_data.find(old_string._data);

        if (target_index != NO_INDEX) {
            this->_data.replace(target_index, target_length, new_string._data);
        }

        return *this;
    }

    inline
    String& String::replaceLast(const String& old_string, const String& new_string) {
        size_t target_length = old_string._data.length();
        size_t target_index = this->_data.rfind(old_string._data);

        if (target_index != NO_INDEX) {
            this->_data.replace(target_index, target_length, new_string._data);
        }

        return *this;
    }

    inline
    String& String::replaceAll(const String& old_string, const String& new_string) {
        size_t target_length = old_string._data.length();
        size_t target_index = 0;

        while ((target_index = this->_data.find(old_string._data, target_index)) != NO_INDEX) {
            this->_data.replace(target_index, target_length, new_string._data);
        }

        return *this;
    }


    // Removing String
    inline
    String& String::remove(const String& string) {
        size_t target_length = string._data.length();
        size_t target_index = this->_data.find(string._data);

        if (target_index != NO_INDEX) {
            this->_data.erase(target_index, target_length);
        }

        return *this;
    }

    inline
    String& String::removeLast(const String& string) {
        size_t target_length = string._data.length();
        size_t target_index = this->_data.rfind(string._data);

        if (target_index != NO_INDEX) {
            this->_data.erase(target_index, target_length);
        }

        return *this;
    }

    inline
    String& String::removeRange(size_t from_index, size_t to_index) {
        if (from_index > to_index) throw std::invalid_argument("from_index must be less than to_index");
        if (from_index < this->_data.length() && to_index < this->_data.length()) {
            this->_data.erase(from_index, to_index - from_index);
            return *this;
        }
        else {
            throw std::invalid_argument("Out of bounds exception");
        }
    }

    inline
    String& String::removeCharacters(const String& string) {
        std::string buffer = "";

        for (size_t i = 0; i < this->_data.length(); ++i) {
            if (!string.contains(this->_data[i])) {
                buffer += this->_data[i];
            }
        }

        this->_data = buffer;

        return *this;
    }

    inline
    String& String::removeAll(const String& string) {
        size_t target_length = string._data.length();
        size_t target_index = 0;

        while ((target_index = this->_data.find(string._data, target_index)) != NO_INDEX) {
            this->_data.erase(target_index, target_length);
        }

        return *this;
    }


    // Searching String
    inline
    bool String::contains(const String& string) const {
        size_t index = this->_data.find(string.std_string());
        return index != NO_INDEX;
    }

    inline
    size_t String::indexOf(const String& string) const {
        return this->_data.find(string._data);
    }

    inline
    size_t String::indexOf(const String& string, size_t min_index) const {
        return this->_data.find(string._data, min_index);
    }

    inline
    size_t String::indexOfLast(const String& string) const {
        return this->_data.rfind(string._data);
    }

    inline
    size_t String::indexOfLast(const String& string, size_t max_index) const {
        return this->_data.rfind(string._data, max_index);
    }


    // String Comparison
    inline
    bool String::isEqualTo(const String& string) const {
        return this->_data == string._data;
    }

    inline
    bool String::isEqualToIgnoreCase(const String& string) const {
        size_t length = this->_data.length();

        if (string._data.length() != length) {
            return false;
        }

        for (size_t i = 0; i < length; ++i) {
            if (tolower(this->_data[i]) != tolower(string._data[i])) {
                return false;
            }
        }

        return true;
    }

    inline
    int String::compare(const String& string) const {
        return this->_data.compare(string.std_string());
    }

    inline
    int String::compareIgnoreCase(const String& string) const {
        return this->copy().toLowerCase()._data.compare(string.copy().toLowerCase()._data);
    }
/*
int String::compareOverRange(const String& string, size_t from_index, size_t to_index) {
    if (from_index > to_index) throw std::invalid_argument("from_index must be less than to_index");
    if (from_index < this->_data.size() && to_index < this->_data.size() &&
            from_index < string._data.size() && to_index < string._data.size()) {
        return this->_data.compare(from_index, to_index - from_index, string._data, from_index, to_index - from_index);
    }
    else {
        throw std::invalid_argument("Out of bounds exception");
    }
}
*/


    // Numeric Values
    inline
    int String::intValue() const {
        return std::stoi(this->_data.c_str());
    }

    inline
    long String::longValue() const {
        return std::stol(this->_data.c_str());
    }

    inline
    long long String::longLongValue() const {
        return std::stoll(this->_data.c_str());
    }

    inline
    unsigned String::unsignedValue() const {
        return std::stoul(this->_data.c_str());
    }

    inline
    unsigned long String::unsignedLongValue() const {
        return std::stoul(this->_data.c_str());
    }

    inline
    unsigned long long String::unsignedLongLongValue() const {
        return std::stoull(this->_data.c_str());
    }

    inline
    float String::floatValue() const {
        return std::stof(this->_data.c_str());
    }

    inline
    double String::doubleValue() const {
        return std::stod(this->_data.c_str());

    }

    inline
    long double String::longDoubleValue() const {
        return std::stold(this->_data.c_str());
    }

    inline
    bool String::boolValue() const {
        String string = this->copy().toLowerCase();

        if (string == "false") return false;
        if (string == "true")  return true;
        if (string == "no")    return false;
        if (string == "yes")   return true;
        if (string == "n")     return false;
        if (string == "y")     return true;
        if (string == "0")     return false;
        if (string == "1")     return true;

        throw std::invalid_argument("Invalid bool value: " + this->_data);
    }


    // String Copy
    inline
    String String::copy() const {
        return String(this->_data);
    }


    // Getting Standard Containers
    inline
    const char* String::c_string() const {
        return this->_data.c_str();
    }

    inline
    std::string String::std_string() const {
        return this->_data;
    }


    // String Representation
    inline
    std::string String::description() const {
        return this->_data;
    }

    inline
    std::string String::inspect() const {
        std::ostringstream oss;

        // Array Address
        oss << "Address: " << this << " ";

        // Array Size
        oss << "Size: " << this->_data.size() << " ";

        // Array Contents
        oss << "\"" << this->_data << "\"";

        return oss.str();
    }
}


#endif //MRLIB_STRING_HPP