# include "TemperatureDatabase.h"
# include <fstream>
#include <sstream>

using std::cout, std::endl, std::string, std::ofstream;
using namespace std;

TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// TODO: implement this function
	ifstream file(filename); 


	// values to collect
	string id = " ";
	int year = 0;
	int month = 0; 
	double temp = 0.0;


	if(!file.is_open())
	{
		cout << "Couldn't open file :(" << endl;
		return; 
	}

	stringstream ss; 
	string data = string();

	while(getline(file, data))
	{
		if(file.eof() && data.empty())
		{
			break;
		}

		ss.clear(); 
		ss.str(data); 


		ss >> id;
		if(ss.fail())
		{
			cout << " Error: Other invalid input" << endl;
			continue;
		}

		ss>> year;
		if(ss.fail())
		{
			cout << "Error: Other invalid input" << endl;
			continue;
		}
		if(year < 1800 || year > 2023)
		{
			cout << "Error: Invalid year " << year << endl; 
			continue;
		}

		
		ss>>month;
		if(ss.fail())
		{
			cout << "Error: Other invalid input" << endl;
			continue;
		}

		if(month > 12 || month < 1)
		{
			cout << "Error: Invalid month " << month << endl;
			continue; 
		}

		ss >> temp;
		if(ss.fail())
		{
			cout << "Error: Other invalid input"<< endl;
			continue; 
		}

		if(temp == -99 ||  temp < -50.0 || temp > 50.0)
		{
			cout << "Error: Invalid temperature " << temp << endl;
			continue;
		}
		this->records.insert(id,year,month,temp);


	}
	file.close(); 
}

void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}

	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// TODO: implement this function
}
