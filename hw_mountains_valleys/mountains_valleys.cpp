#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a1;
	int b1;

	// TODO(student): print prompt for input
	cout << "Enter numbers 10 <= a <= b < 10000: ";
	// TODO(student): read the numbers from standard input
	cin >> a1 >> b1;
	// TODO(student): validate input (and reprompt on invalid input)
	bool check_range = is_valid_range(a1,b1);
	
	while(check_range == false){
		cout << "Invalid Input" << endl;
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		cin >> a1 >> b1;
		check_range = is_valid_range(a1,b1);
	}
	
	// TODO(student): compute and display solution
	count_valid_mv_numbers(a1,b1);



	
	return 0;
}