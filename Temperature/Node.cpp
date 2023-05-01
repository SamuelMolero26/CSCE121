# include <string>
# include "Node.h"

using std::string;

Node::Node(): next{nullptr}, data{TemperatureData{}}{
	// TODO: implement this function
}

Node::Node(string id, int year, int month, double temperature): next{nullptr}, data{TemperatureData(id,year, month, temperature)}{
	// TODO: implement this function
}

bool Node::operator<(const Node& b) /* TODO */ {
	// TODO: implement this function
	
	return this->data < b.data;
}
