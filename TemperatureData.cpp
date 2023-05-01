# include "TemperatureData.h"
#include <string>
using std::string;
using namespace std;
TemperatureData::TemperatureData(): id{string()},year{0}, month{0}, temperature{0}{
	// TODO: implement this function
}

TemperatureData::TemperatureData(string id, int year, int month, double temperature): id{id}, year{year}, month{month}, temperature{temperature}{
	// TODO: implement this function
}

TemperatureData::~TemperatureData() {}

bool TemperatureData::operator<(const TemperatureData& b) {
	// TODO: implement this function
	if(this->id != b.id)
	{
		return this->id < b.id; 
	}
	if(this->id > b.id)
	{
		return false;
	}

	if(this->year < b.year)
	{
		return true;
	}
	
	if(this->year > b.year)
	{
		return false;
	}

	if(this->month < b.month)
	{
		return true;
	}

	if(this->month > b.month){
		return false;
	}

	// if(this->temperature < b.temperature)
	// {
	// 	return true;

	// }
	// if(this->temperature > b.temperature)
	// {
	// 	return false;
	// }

	return false; 
}

