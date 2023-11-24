#pragma once
#include <string>
using namespace std;
class Node
{
public:
	Node* previous;
	Node* next;
	Node* top;
	Node* bottom;
	string data;

	Node()
	{
		previous = nullptr;
		next = nullptr;
		top = nullptr;
		bottom = nullptr;
		data = "0";
	}
	Node(string value)
	{
		previous = nullptr;
		next = nullptr;
		top = nullptr;
		bottom = nullptr;
		data = value;
	}
};

