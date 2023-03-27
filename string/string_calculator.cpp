#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std ::invalid_argument;
using std::string;
using std::min;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement

    int value = digit - '0';
     
    if(value  > -1 && value < 10)
        return value;
    else
        throw invalid_argument("Invalid argument");
}


char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    char value = '0' + decimal;
    if(decimal <= 9)
        return value;
    else
        throw invalid_argument("Invalid argument");
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    long unsigned int count = 0;
    string str = num;

    if(num.at(0) == '-' && num == "0"){
        str = "0";
        return str;
    }

    if(num == "0"){
        return str;
    }
    else{
        // if(num.at(0) == '-'){
            // str.erase(0);
        // }
        for(long unsigned int i = 0; i < num.length(); i++){
            if(num[i] == '0')
                count += 1;
        } 
        if(count == num.length()){
            str = "0";
        }
        else if(count == num.length()){
            str = "0";
            return str;
        } 
        // if (num.at(0) == '-'){
        //   str.erase(0,1);
        //   str.erase(0,min(str.find_first_not_of('0'),num.size()-1));
        //   str.insert(0,"-");
        //   return str;
        // }              
        else{
            str.erase(0,min(str.find_first_not_of('0'),str.size()-1));
        }
        return str; 
    }
}

string add(string lhs, string rhs) { //positives only
    // TODO(student): implement
    string result = "";
    string sum = "";

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs); // accout  for leading zeros
    if(lhs == "0" && rhs == "0"){
        sum = "0";
        return sum;
    }

       // lhs + rhs
    int first = lhs.size() - 1;
    int second = rhs.size() - 1;
    int carry = 0; // carry the hoe

    while(first >= 0 || second >= 0 || carry)
    {
        if(first >= 0){
            carry += lhs[first] - '0';
            first -= 1; // loop throught 
        }
        if(second >= 0){
            carry += rhs[second] - '0';
            second -= 1; // loop through 
        }
        result += char(carry % 10 + '0');
        carry /= 10;
    }
    for(int i = result.size() - 1; i >= 0; --i){
        sum += result[i];
    }
    return sum;
} 



string multiply(string lhs, string rhs) {
    // TODO(student): implement
    if(lhs == "0" || rhs == "0")
        return "0";
    
    
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    // for(int i = lhs.size() - 1; i >= 0; --i){
        // reversed_lhs += lhs[i];
    // }
    // for(int i = rhs.size()- 1; i >= 0; --i){
        // reversed_rhs += rhs[i];
    // }
    int n_size = lhs.size() + rhs.size();
    string result(n_size, '0');
    for(int j = rhs.size() - 1;  j >= 0; --j){ // loop through the digits
        int carry = 0;
        for (int i = lhs.size() - 1; i >= 0; --i){
             int partial = (digit_to_decimal(rhs[j])) * (digit_to_decimal(lhs[i])) + digit_to_decimal(result[i+j+1]) + carry; // add carry from any prvious digit
             carry = partial / 10;
             result[j+i+1] = decimal_to_digit(partial % 10);
             
             
        }
        result[j] += carry;
    }
    if(result.at(0) == '0'){
        result.erase(0,1);
    }

    return result;
}
