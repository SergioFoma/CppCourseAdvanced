#include <algorithm>
#include <cstring>

#include "string.hpp"

// Constructors

// Delegatin constructors
String::String(size_t n): chars(new char[n + 1]), sz(n), cap(n + 1) {
    chars[sz] = '\0';
}

String::String(): chars(new char[1]), sz(0), cap(1) {
    chars[sz] = '\0';
};

String::String(const char* str): String(strlen(str)) {
    std::copy(str, str + sz, chars);
}

String::String(size_t n, char symbol): String(n) {
    memset(chars, symbol, n);
}

String::String(const String& other): String(other.sz) {
    std::copy(other.chars, other.chars + sz, chars);
}

String::String(const char* str, size_t n): String(n) {
    std::copy(str, str + n, chars);
}

String::String(const char* str, size_t start, size_t n): String(n) {
    std::copy(str + start, str + start + n, chars);
}

String::String(const String& other, size_t n): String(n) {
    char* other_str = other.chars;
    std::copy(other_str, other_str + n, chars);
}

String::String(const String& other, size_t start, size_t n): String(n) {
    char* other_str = other.chars;
    std::copy(other_str + start, other_str + start + n, chars);
}

// Swap and copy
String& String::operator=(const char* str) & {
    String other(str);
    this->swap(other);

    return *this;
}
String& String::operator=(String other) & {           // we can assign constant structures
    this->swap(other);

    return *this;
}

// Getters

size_t String::size() const {
    return this->sz;
}

size_t String::length() const {
    return this->sz;
}

size_t String::capacity() const {
    return this->cap;
}

const char* String::get_chars() const {
    return this->chars;
}

// Function

String operator+(const String& left, const String& right) {
   String copy = left;
   copy += right;
   return copy;
}

String operator+(const String& left, const char* right) {
    return left + String(right);
}

String operator+(const char* left, const String& right) {
    return String(left) + right;
}

String& String::operator+=(const char* str) {
    
    size_t str_size = strlen(str);
    size_t str_cap = str_size + 1;
    char* new_chars = chars;
    bool flag = false;
    if (cap < sz + str_cap) {
        new_chars = new char[sz + str_cap];
        std::copy(chars, chars + sz, new_chars);
        flag = true;
    }
    
    std::copy(str, str + str_cap, new_chars + sz);

    if (flag) {
        delete[] chars;
        chars = new_chars;
        cap = sz + str_cap;
    }
    sz = sz + str_size;
    return *this;
}

String& String::operator+=(const String& other) {
    return String::operator+=(other.chars);
}

bool String::empty() const {
    return sz == 0;
}

size_t String::max_size() const {
    if (cap > 0) {
        return cap - 1;
    }

    return 0;
}

void String::resize(size_t n) {
    if (n == sz) {
        return ;
    }
    char* new_chars = new char[n + 1];
    size_t min_sz = std::min(sz, n);
    std::copy(chars, chars + min_sz, new_chars);
    new_chars[n] = '\0';
    delete[] chars;
    
    chars = new_chars;
    sz = n;
    cap = n + 1;
}

void String::resize(size_t n, char symbol) {
    size_t old_sz = sz;
    this->resize(n);

    if (n > old_sz) {
        memset(chars + old_sz, symbol, n - old_sz);
    }
}

void String::reserve(size_t n) {
    if (n < cap) {
        return ;
    }
    
    size_t old_sz = sz;
    this->resize(n);                // reserve doesn't change size
    sz = old_sz;
}

void String::shrink_to_fit() {
    char* new_chars = new char[sz + 1];
    std::copy(chars, chars + sz, new_chars);
    delete[] chars;
    cap = sz + 1;
    chars = new_chars;
    chars[sz] = '\0';
}

char& String::operator[](size_t n) {
    return chars[n];
}

const char& String::operator[](size_t n) const {
    return chars[n];
}

char& String::front() {
    return chars[0];
}

const char& String::front() const {
    return chars[0];
}

char& String::back() {
    return chars[sz - 1];
}

const char& String::back() const {
    return chars[sz - 1];
}

void String::push_back(char symbol) {
    if (sz == cap - 1) {
        this->reserve(cap * 2);
    }
    
    chars[sz++] = symbol;
    chars[sz] = '\0';
}

void String::insert(size_t pos, const char* str) {
    size_t count = strlen(str);
    size_t new_sz = sz + count;
    
    if (new_sz >= cap) {
        char* new_chars = new char[new_sz + 1];
        std::copy(chars, chars + pos, new_chars);
        std::copy(str, str + count, new_chars + pos);
        std::copy(chars + pos, chars + sz, new_chars + pos + count);
        new_chars[new_sz] = '\0';
        delete[] chars;
        chars = new_chars;
        sz = new_sz;
        cap = sz + 1;
        return ;
    }

    memmove(chars + pos + count, chars + pos, sz - pos);
    memmove(chars + pos, str, count);
    sz = new_sz;
    chars[sz] = '\0';
}

void String::insert(size_t pos, const String& other) {
    insert(pos, other.chars);
}

void String::erase(size_t pos) {
    this->erase(pos, 1);
}
void String::erase(size_t pos, size_t count) {
    if (pos >= sz) {
        return; 
    }
    if (pos + count > sz) {
        count = sz - pos;
    }
    memset(chars + pos, '\0', count);
    memmove(chars + pos, chars + pos + count, cap - pos - count);
    sz -= count;
    chars[sz] = '\0';
}

void String::clear() {
    memset(chars, '\0', sz);
    sz = 0;
}

void String::replace(size_t pos, size_t count, const char* str) {
    this->erase(pos, count);
    this->insert(pos, str);
}

void String::replace(size_t pos, size_t count, const String& other) {
    this->replace(pos, count, other.chars);
}

void String::replace(size_t start, size_t end, char old_symb, char new_symb) {
    for (size_t index = start; index < end; ++index) {
        if (chars[index] == old_symb) {
            chars[index] = new_symb;
        }
    }
}

void String::swap(String& other) {
    std::swap(chars, other.chars);
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);
}

void String::pop_back() {
    chars[sz - 1] = '\0';
    --sz;
}

std::optional<size_t> String::find_first(char symbol) const {
    for (size_t index = 0; index < sz; ++index) {
        if (chars[index] == symbol) {
            return index;
        }
    }

    return std::nullopt; 
}

std::optional<size_t> String::find_last(char symbol) const {
    size_t last_find = sz;

    for (size_t index = 0; index < sz; ++index) {
        if (chars[index] == symbol) {
            last_find = index;
        }
    }
    
    if (last_find == sz) {
        return std::nullopt;
    }
    return last_find;
}

String String::substr(size_t pos, size_t count) {
    String other(count);

    std::copy(chars + pos, chars + pos + count, other.chars);

    return other;
}

int String::compare(const String& other) const {
    return strcmp(chars, other.chars);
}

// Destructor

String::~String() {
    delete[] chars;
}
