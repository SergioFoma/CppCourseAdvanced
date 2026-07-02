#ifndef STRING_HPP
#define STRING_HPP

#include <optional>
#include <ostream>
#include <istream>

class String{
private:
    char* chars = nullptr;
    size_t sz = 0;
    size_t cap = 0;

    explicit String(size_t n);
public:

    String();
    String(const char* str);
    String(size_t n, char symbol);
    String(const String& other);                        // copy constructor
    String(const char* str, size_t n);
    String(const char* str, size_t start, size_t n);
    String(const String& other, size_t n);
    String(const String& other, size_t start, size_t n);


    String& operator=(const char* str) &;                   // & - only lvalue
    String& operator=(String other) &;                      // & - only lvalue
    String& operator+=(const char* str);
    String& operator+=(const String& other);
    char& operator[](size_t n);
    const char& operator[](size_t n) const;
    size_t size() const;
    size_t max_size() const;
    size_t length() const;
    size_t capacity() const;
    const char* get_chars() const;
    bool empty() const;
    void resize(size_t n);
    void resize(size_t n, char symbol);
    void reserve(size_t n);
    void shrink_to_fit();
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    void push_back(char symbol);
    void insert(size_t pos, const char* str);
    void insert(size_t pos, const String& other);
    void erase(size_t pos);
    void erase(size_t pos, size_t count);
    void clear();
    void replace(size_t pos, size_t count, const char* str);
    void replace(size_t pos, size_t count, const String& other);
    void replace(size_t start, size_t end, char old_symb, char new_symb);
    void swap(String& other);
    void pop_back();
    std::optional<size_t> find_first(char symbol) const;
    std::optional<size_t> find_last(char symbol) const;
    String substr(size_t pos, size_t count);
    int compare(const String& other) const;

    ~String();
};

String operator+(const String& left, const String& right);
String operator+(const String& left, const char* right);
String operator+(const char* left, const String& right);

std::ostream& operator<<(std::ostream& out, const String& str);


#endif
