#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;
using std::stringstream;

const char plus = '+';
const char mult = '*';

int main()
{
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    //cout<< trim_leading_zeros("-0000") << endl;

    // TODO(student): implement the UI
    // cout << digit_to_decimal('7') << endl;
    // cout << decimal_to_digit(7)<< endl;
    // cout << trim_leading_zeros("000013") << endl;
    // cout << add("23456","2345") << endl;
    // cout << add("19","2") << endl;
    // cout << multiply("2","3") << endl;

    string user_input = "\0";
    string lhs,rhs,sign;
    bool ask = true;

    while(ask)
    {
        cout << ">> " <<  endl;
        getline(cin, user_input);

        if (cin.eof() || cin.fail())
        {
            cout << "farvel!" << endl;
            ask = false;
            break;
        }

        if (user_input == "q" || user_input == "quit")
        {
            cout << "farvel!" << endl;
            ask = false;
            break;
        }

        stringstream stream(user_input); 
        stream >> lhs >> sign >> rhs; 

        const char operation = sign.at(0); 

        if(operation == plus)
        {
            cout << "ans =" << "\n";
            cout <<"\n    "<< add(lhs,rhs) << "\n";
             cout <<"\n";
        }

        if(operation == mult){
          cout << "ans =" << "\n";
          cout << "\n    " << multiply(lhs,rhs) << "\n";
          cout << "\n";
            
        } 
    } 
}
