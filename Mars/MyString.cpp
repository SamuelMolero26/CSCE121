// TODO: Implement this source file

#include <iostream>

#include "MyString.h"

using std::ostream; 

using namespace std;


MyString::~MyString(){

    delete [] this-> str1;
}

MyString::MyString(): str1{new char[15]}, n{0}, capacity1{15} 
{ //construct an empty string

   for(size_t i = 0; i < n; i++)
   {
        this->str1[i] = '\0';
   }
}

MyString::MyString(const MyString& str): n{str.n}, str1{nullptr}, capacity1{str.capacity1}
{

    this->str1= new char[this->capacity1];

    for(size_t i = 0; i < this->capacity1; i++)
    {
        this-> str1[i] = str.str1[i]; 
    }

}

MyString::MyString(const char* str): n(0), str1(nullptr), capacity1(15){

    if(str == nullptr)
    {
        throw invalid_argument("its nullptr");
    }

    while(str[n] != '\0') // update size of imput string
    {
        n++;
    }

    str1 = new char[capacity1];
    for(size_t j = 0; j < capacity1; j++)
    {
        str1[j] = str[j];
        if(str[j] == '\0')
        {
            break; 
        }
    }

}



void MyString::clear() noexcept{

    for(size_t i = 0; i < n; i++)
    {
        this->str1[i] = '\0';
    }
    
    this->capacity1 = 1;
    this->n = 0; 
}

const char* MyString::data() const noexcept {
    return this->str1;
}

size_t MyString::size() const{
    return this->n;
}
void MyString::resize(size_t temp_size )
{
     if( temp_size < this->n)
    {
        this->n = temp_size;
    }

    if(temp_size  > this-> n)
    {
        size_t cap2 = temp_size - this->n; 
        this->capacity1 = cap2; 
        char* temp_arr = new char[capacity1];
        delete [] this->str1; 
        this->str1 = temp_arr;
    }

    this->str1[temp_size] = '\0';


}

size_t MyString::capacity() const{
    return this->capacity1;
}

size_t MyString::length() const noexcept{
    return this->n; 
}

bool MyString::empty() const noexcept{

    return this->n == 0;
}

const char& MyString::front() const{
    return this->str1[0]; // returns referece to the first value 
}

const char& MyString::at (size_t pos) const{
    if(pos >= this->n) // if greater
    {
        throw out_of_range("Fuera de rango"); // out of range
    }

    return this->str1[pos]; // clear to return at pos position
}

MyString& MyString:: operator+=(const MyString& str)
{
   size_t size1 = this->n;
   size_t size2 = this-> n + str.n;
   size_t new_cap = 15;

   while((size2) > new_cap)
   {
        new_cap *= 2;
   }

   this-> capacity1 = new_cap;
   this-> n += str.size();

    char* temp_arr = new char[new_cap];
   for(size_t i = 0; i < new_cap;  ++i)
   {
        if(i < size1)
        {
            temp_arr[i] = this->str1[i];
        }
        else if(i < size2)
        {
            temp_arr[i] = str.at(i - size1);
        }

        else{
            temp_arr[i] = '\0'; 
        }
        
   }

   delete[] this -> str1;
   this-> str1 = temp_arr; 

   return *this;

}

ostream& operator<<(ostream& os, const MyString& str)
{
    for(size_t t = 0; t < str.size(); t++)
    {
        os << str.at(t); 
    }

    return os; 

}


MyString& MyString:: operator=(const MyString& str)
{
    if(this != &str){//check got self assigment
        delete [] this->str1; // delocate dynamic memory


        this->n = str.n;
        this-> capacity1 = str.capacity1;
        this->str1 = new char[this-> capacity1];


        for(size_t i = 0; i < this->capacity1; i++)
        {
            this->str1[i] = str.str1[i];
        }

    }

    return *this; 

}



size_t MyString::find(const MyString& str, size_t pos) const noexcept{

   size_t size_of_string = str.size();

   for(size_t i = pos; i < (this->n - size_of_string + 1); i++)
   {
    bool found = true;
    for(size_t j = 0; j < size_of_string; ++j)
    {
        if(this->str1[i + j] != str.at(j))
        {
            found = false;
            break;
        }
    }
    if(found == true)
    {
        return i;
    }
   }
   return -1;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    return MyString(lhs) += MyString(rhs);
}




//Check list

//resize ---- done
//capacity --- done
//size ---- done
//length --- done
//data --- done
//empty --- done
// front --- done 
//clear --- done
//find 
//operator<< -- done
//operator+= --- done
//operator= -- done
//opeartor== -- done