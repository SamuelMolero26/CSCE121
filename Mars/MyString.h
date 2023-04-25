// TODO: Implement this header file
#ifndef _MYSTRING_H
#define _MYSTRING_H


#include <iostream>

using namespace std;

using std::ostream; 


class MyString {

private:

    
    size_t n; 

    size_t capacity1;

    char* str1;


    
public:

    static  const size_t npos = -1; 

    //Rule of Three
    MyString();
    MyString(const MyString& str);
    MyString(const char* str);
    ~MyString();

   

    //functions
    void resize(size_t temp_size);

    size_t capacity() const; 

    size_t size() const;

    size_t length() const noexcept; 

    const char* data() const noexcept; 

    bool empty() const noexcept; 

    const char& front() const;     

    const char& at (size_t pos) const; 

    void clear() noexcept; 

    friend ostream& operator<< (ostream& os, const MyString& str); 

    MyString& operator= (const MyString& str); 

    MyString& operator+= (const MyString& str); 

    size_t find(const MyString& str, size_t pos = 0) const noexcept; 

    friend bool operator==(const MyString& lhs, const MyString& rhs);

    friend MyString operator+(const MyString& lhs, const MyString& rhs); 
    //friend allows other functions tor class to access to 
    //private or protected members of the class

};

#endif