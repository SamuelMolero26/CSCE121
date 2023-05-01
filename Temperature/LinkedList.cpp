# include <iostream>
# include <string>
# include <limits>
# include <cstdlib>
#include <sstream>
#include <sstream>
# include "LinkedList.h"
# include "Node.h"

using std::string, std::ostream;
using namespace std; 

LinkedList::LinkedList(): head{nullptr},tail{nullptr}{}
	// TODO: implement this function

LinkedList::~LinkedList() { //Deconstrructor
	// TODO: implement this function
	this->clear();
}

LinkedList::LinkedList(const LinkedList& source): head{nullptr}, tail{nullptr} {
	// TODO: implement this function
	//ask about it 
	Node* current = source.head;
	while(current != nullptr) //iterate through each node in the source list, 
	//create a new node with the same data value and link it to the end of the list
	{
		Node*  temp_Node = new Node;
		temp_Node->data = current->data; 
		temp_Node->next = nullptr;

		if(head == nullptr)
		{
			head = temp_Node;
			tail = temp_Node;
		}
		else{
			tail->next = temp_Node;
			tail = temp_Node;
		}
		current = current->next; 
	}
	
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// TODO: implement this function

	if(&source == this) //check self-assigment 
	{
		return *this; 
	}

	this->clear();

	Node* temp = source.getHead();
	TemperatureData temp_data = temp->data;

	this->head = new Node(temp_data.id,temp_data.year,temp_data.month,temp_data.temperature); 
	
	this->head->next = nullptr; //dereference


	Node* node1 = this->head;
	Node* node2 = temp->next; 

	//iterate throught the remaining nodes of the source
	while(node2 != nullptr)
	{
		//new node with source data
		Node* newNode = new Node(node2->data.id,node2->data.year,node2->data.month,node2->data.temperature); 
		cout << node2->data.year << endl;
		node1->next  = newNode; // links to new 
		node1 = newNode; //move to new added node
		node2 = node2->next;
	}
	this->tail = node1; //updates tail

	return *this;


}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// TODO: implement this function
	Node* curr_temp = this->getHead();
	Node* new_temp = new Node(location,year,month,temperature);
	
	//if empty
	if(this->head == nullptr)
	{
		this->head = new_temp;
		this->tail = new_temp; 
		return; 
	}

	//insert before -- principio
	if(*new_temp < *this->head)
	{
		new_temp->next = this->head; // flip 
		this->head = new_temp; 
		return; 
	}

	//insert at the end -- final 
	if(*this->tail < *new_temp)
	{
		this->tail->next = new_temp;
		this->tail = new_temp; 
		return; 
	}

	//middle --- en el medio 
	while(curr_temp->next != nullptr && *(curr_temp->next) < *(new_temp))
	{
		curr_temp = curr_temp->next;
	}
	new_temp->next = curr_temp->next;
	curr_temp->next = new_temp; 
}

void LinkedList::clear() {
	// TODO: implement this function
	
	Node* temp_value = this->head; 
	Node* current_next; 
	while(temp_value != nullptr)
	{
		current_next = temp_value->next;
		delete temp_value;
		temp_value = current_next; 
	}
	this->head = nullptr;
	this->tail = nullptr; 
}

Node* LinkedList::getHead() const {
	// TODO: implement this function, it will be used to help grade other functions
	return this->head;
}

string LinkedList::print() const {
	string outputString = string(); 

	// TODO: implement this function

	Node* temp = this->head; 
	while(temp != nullptr)
	{
		outputString += temp->data.id + " ";
		outputString += to_string(temp->data.year) + " "; 
		outputString += to_string(temp->data.month) + " ";
		string str = to_string(temp->data.temperature); // gives 00000
    	if(str.find('.')) // to trim zeros
    	{
			str = str.substr(0,str.find_last_not_of('0') + 1);
			if(str.find('.') == str.size()-1)
			{
				str = str.substr(0, str.size()-1);
			}
   	    }
		outputString += str + "\n";
		temp = temp->next;
	}

	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	os << ll.print();
	return os;
}
