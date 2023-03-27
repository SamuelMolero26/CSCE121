#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range 
	if(10 <= a && a <= b && b < 10000){
		return true;
	}
	else{
		return false;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	char pattern = 'N';
	int d1 = number % 10;
	number /= 10;

	while(number != 0){
		int d2 = number % 10;
		if (d1 == d2){
			return 'N';
			break;
		}
		else if (d1 > d2) {
			if(pattern == 'M')
			{
				pattern = 'N';
				break;
			}
			else{
				pattern = 'M';
			}
		}else{
			if(pattern == 'V'){
				pattern = 'N';
				break;
			}
			else{
				pattern = 'V';
			}
		}
		d1 = d2;
		number /= 10;

	}
	 return pattern; 
	

}
		


void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int total_M = 0;
	int total_V = 0;
	int i;
	for(i = a; i <= b; ++i){
		if(classify_mv_range_type(i) == 'M'){
			total_M++;
		}
		else if(classify_mv_range_type(i) == 'V')
		{
			total_V++;
		}

	}
	cout <<"There are "<< total_M <<" mountain ranges and "<< total_V <<" valley ranges between "<< a <<" and "<<b<< "." << endl;

}