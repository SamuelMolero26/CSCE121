#include <stdexcept>
#include <iostream>

using namespace std; 

int Largest(int a, int b, int c) {
  int d = INT32_MIN;
  if (a > d) {
    d = a;
  } 
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}//DONE 


bool SumIsEven(int a, int b) {
  if(((a + b) % 2) != 0){
    return false;
  }
  else{
    return true;
  }
} // DONE

int BoxesNeeded(int apples) {
  if(apples < 1){
    return 0; 
  }
  else if(apples % 20 == 0){
    return (apples / 20);
  }cout << "Sum overflowed" << endl;
   cout << "Sum overflowed" << endl;
    return ((apples / 20) + 1);
}
//DONE

bool SmarterSection(int A_correct, int A_total, int B_corect, int B_total) {
  if(A_correct < 0 || B_corect < 0){
    throw invalid_argument("Values must be no-negative");
  }
  if(A_correct > A_total){
    throw invalid_argument("A correct must be less than or equal to A total");

  }
  if(B_corect > B_total){
    throw invalid_argument("B correct must be less than or equal to B total");
  }
  if(A_total < 1 || B_total < 1){
    throw invalid_argument("Total values must be positive");
  }

  return static_cast<double>(A_correct)/A_total > static_cast<double>(B_corect)/B_total;
}
//DONE

bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 &&  pizzas <= 20) {
    return true;
  }
  if(pizzas < 10)
  {
    return false;
  }
  else{
    return is_weekend;
  }
}

int SumBetween(int low, int high) {

  if(low > high){
    throw invalid_argument("Out of order");
  }

  if(low == high ){
   return low;
  }  

  if(low == high * -1){
    return 0;
  }

  if(low + high == -1){
    return low;
  }

  if(low < 0 && high > 0){
    low = low * -1;
    if(low > high){
      int val = low; 
      low = high;
      high = val;
    }
    low++;
  }
  if(low == INT32_MIN && high == INT32_MAX){
    throw overflow_error("Sum underflowed");
  }

  if(low == high ){
    return low;
  }  

  int value1 = 0;
  for (int n = low; n <= high; n++) {
    if(value1 > INT32_MAX - n && n > 0 ){
      throw overflow_error("Sum overflowed");
    }

    else if(value1 < INT32_MIN - n && n < 0){
      throw overflow_error("Sum underflowed");
    }
    else {
      value1 += n; 
    }
  }
  //cout << value1 << endl;
  //cout << high << endl;
  //cout << low << endl;
  return value1;


}

int Product(int a, int b) {
  if((a == INT32_MIN && b == -1)||(a == -1 && b == INT32_MIN))
  {
    throw overflow_error("Overflow");
  }
  if(a < 0 && b > 0){
     a *= -1;
     b *= -1;
   }


  if(b > 0) {
    if (a > INT32_MAX/ b )
      throw overflow_error("Overflow");

    if(a < INT32_MIN / b)
      throw overflow_error("Underflow");
  }

  else if(b <  0){
    if (a < INT32_MAX / b)
      throw overflow_error("Overflow");

     if(a > INT32_MIN / b)
       throw overflow_error("Underflow");
  }
  return (a * b);
}
  
  
  
  
  
  

  
  
  
  
  


  
  
  
  
  
  