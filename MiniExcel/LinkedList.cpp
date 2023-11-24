#include "LinkedList.h"
#include "Node.h"
#include<string>
#include <sstream>
#include<vector>

using namespace std;

bool LinkedList::IsEmpty()
{
	if (TopLeft == nullptr && TopRight == nullptr && BottomLeft == nullptr && BottomRight == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsTopRight(Node* current)
{
	if (current->next == nullptr && current->top == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsTopLeft(Node* current)
{
	if (current->top == nullptr && current->previous == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsBottomRight(Node* current)
{
	if (current->next == nullptr && current->bottom == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::IsBottomLeft(Node* current)
{
	if (current->bottom == nullptr && current->previous == nullptr)
	{
		return true;
	}
	return false;
}
bool LinkedList::OnlyOneCell()
{

	if (TopLeft == TopRight && BottomLeft == BottomRight && TopLeft == BottomLeft && TopRight == BottomRight)
	{
		return true;
	}
	return false;
}
Node* LinkedList::GetRightEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->next;
	}
	return required;
}
Node* LinkedList::GetLeftEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->previous;
	}
	return required;
}
Node* LinkedList::GetTopEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->top;
	}
	return required;
}
Node* LinkedList::GetBottomEnd(Node* current)
{
	Node* required = nullptr;
	Node* temp = current;
	while (temp != nullptr)
	{
		required = temp;
		temp = temp->bottom;
	}
	return required;
}
Node* LinkedList::GetNodeByPosition(string position)
{
	size_t cPos = position.find('C');
	size_t rPos = position.find('R');

	// Extract column and row substrings
	string colStr = position.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = position.substr(rPos + 1);

	// Convert strings to integers
	int col, row;
	istringstream(colStr) >> col;
	istringstream(rowStr) >> row;

	// Check if the linked list has enough rows and columns
	if (row <= 0 || col <= 0) {
		// Handle error or return nullptr, depending on your requirements
		return nullptr;
	}

	Node* temp = TopLeft;

	// Traverse columns
	for (int idx = 1; idx < col; idx++)
	{
		if (temp == nullptr) {
			// Handle error or return nullptr
			return nullptr;
		}
		temp = temp->next;
	}

	// Traverse rows
	for (int idx = 1; idx < row; idx++)
	{
		if (temp == nullptr || temp->bottom == nullptr) {
			// Handle error or return nullptr
			return nullptr;
		}
		temp = temp->bottom;
	}

	return temp;
}
void  LinkedList::SetValue(Node* current, string value)
{
	current->data = value;
}

void LinkedList::InsertAfter(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->next = newNode;
		newNode->previous = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->bottom = emptyNode01;
		emptyNode01->top = current;
		emptyNode01->next = emptyNode02;
		emptyNode02->previous = emptyNode01;
		newNode->bottom = emptyNode02;
		emptyNode02->top = newNode;

		TopRight = newNode;
		BottomRight = emptyNode02;
		BottomLeft = emptyNode01;
	}
	else if (IsTopRight(current))
	{
		current->next = newNode;
		newNode->previous = current;

		Node* temp01 = newNode;
		Node* temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = newNode;
		BottomRight = GetBottomEnd(newNode);
	}
	else if (IsBottomRight(current))
	{
		current->next = newNode;
		newNode->previous = current;

		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}
		BottomRight = newNode;
		TopRight = GetTopEnd(newNode);
	}
	else if (current->next == nullptr)
	{
		newNode->previous = current;
		current->next = newNode;


		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode;
		temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = GetTopEnd(newNode);
		BottomRight = GetBottomEnd(newNode);
	}
	else if (IsTopLeft(current) || current->top == nullptr)
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->bottom = current->bottom->next;
		current->bottom->next->top = newNode;
		current->next->previous = newNode;
		current->next = newNode;

		TopRight = GetRightEnd(newNode);

		Node* temp01 = TopRight;
		Node* temp = TopRight->bottom;
		while (temp != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		temp01 = newNode->bottom->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->top = temp;
			temp->bottom = temp01;

			temp01 = temp01->next;
			temp = temp->next;
		}

		BottomRight = GetBottomEnd(TopRight);
	}
	else if (IsBottomLeft(current) || current->bottom == nullptr)
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->top = current->top->next;
		current->top->next->bottom = newNode;
		current->next->previous = newNode;
		current->next = newNode;

		BottomRight = GetRightEnd(newNode);

		Node* temp01 = BottomRight;
		Node* temp = BottomRight->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode->top->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopRight = GetTopEnd(BottomRight);

	}
	else
	{
		newNode->previous = current;
		newNode->next = current->next;
		newNode->top = current->top->next;
		newNode->bottom = current->bottom->next;
		current->top->next->bottom = newNode;
		current->next->previous = newNode;
		current->bottom->next->top = newNode;
		current->next = newNode;

		Node* RightEnd = GetRightEnd(current);

		Node* temp01 = RightEnd;
		Node* temp = RightEnd->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->next = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = RightEnd;
		temp = RightEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		Node* temp02 = newNode->bottom->next;
		temp01 = newNode->top->next;
		temp = newNode->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp02->top = temp;
			temp->bottom = temp02;
			temp02 = temp02->next;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopRight = GetTopEnd(RightEnd);
		BottomRight = GetBottomEnd(RightEnd);
	}
}
void LinkedList::InsertBefore(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->previous = newNode;
		newNode->next = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->bottom = emptyNode01;
		emptyNode01->top = current;
		emptyNode01->previous = emptyNode02;
		emptyNode02->next = emptyNode01;
		newNode->bottom = emptyNode02;
		emptyNode02->top = newNode;

		TopLeft = newNode;
		BottomRight = emptyNode01;
		BottomLeft = emptyNode02;
	}
	else if (IsTopLeft(current))
	{
		current->previous = newNode;
		newNode->next = current;

		Node* temp01 = newNode;
		Node* temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopLeft = newNode;
		BottomLeft = GetBottomEnd(newNode);
	}
	else if (IsBottomLeft(current))
	{
		current->previous = newNode;
		newNode->next = current;

		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}
		BottomLeft = newNode;
		TopLeft = GetTopEnd(newNode);
	}
	else if (current->previous == nullptr)
	{
		newNode->next = current;
		current->previous = newNode;


		Node* temp01 = newNode;
		Node* temp = current->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode;
		temp = current->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}


		TopLeft = GetTopEnd(newNode);
		BottomLeft = GetBottomEnd(newNode);
	}
	else if (IsTopRight(current) || current->top == nullptr)
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->bottom = current->bottom->previous;
		current->bottom->previous->top = newNode;
		current->previous->next = newNode;
		current->previous = newNode;

		TopLeft = GetLeftEnd(newNode);

		Node* temp01 = TopLeft;
		Node* temp = TopLeft->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		temp01 = newNode->bottom->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->top = temp;
			temp->bottom = temp01;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		BottomLeft = GetBottomEnd(TopLeft);
	}
	else if (IsBottomRight(current) || current->bottom == nullptr)
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->top = current->top->previous;
		current->top->previous->bottom = newNode;
		current->previous->next = newNode;
		current->previous = newNode;

		BottomLeft = GetLeftEnd(newNode);

		Node* temp01 = BottomLeft;
		Node* temp = BottomLeft->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = newNode->top->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		TopLeft = GetTopEnd(BottomLeft);
	}
	else
	{
		newNode->next = current;
		newNode->previous = current->previous;
		newNode->top = current->top->previous;
		newNode->bottom = current->bottom->previous;
		current->top->previous->bottom = newNode;
		current->previous->next = newNode;
		current->bottom->previous->top = newNode;
		current->previous = newNode;

		Node* LeftEnd = GetLeftEnd(current);

		Node* temp01 = LeftEnd;
		Node* temp = LeftEnd->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->top = emptyNode;
			temp->previous = emptyNode;
			emptyNode->bottom = temp01;
			emptyNode->next = temp;
			temp01 = temp01->top;
			temp = temp->top;
		}

		temp01 = LeftEnd;
		temp = LeftEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		Node* temp02 = newNode->bottom->previous;
		temp01 = newNode->top->previous;
		temp = newNode->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->bottom = temp;
			temp->top = temp01;
			temp02->top = temp;
			temp->bottom = temp02;
			temp02 = temp02->previous;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		TopLeft = GetTopEnd(LeftEnd);
		BottomLeft = GetBottomEnd(LeftEnd);
	}
}
void LinkedList::InsertAbove(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->next = emptyNode01;
		emptyNode01->previous = current;
		emptyNode01->top = emptyNode02;
		emptyNode02->bottom = emptyNode01;
		newNode->next = emptyNode02;
		emptyNode02->previous = newNode;

		TopLeft = newNode;
		TopRight = emptyNode02;
		BottomRight = emptyNode01;

	}
	else if (IsTopRight(current))
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}
		TopRight = newNode;
		TopLeft = GetLeftEnd(newNode);
	}
	else if (IsTopLeft(current))
	{
		current->top = newNode;
		newNode->bottom = current;

		Node* temp01 = newNode;
		Node* temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}
		TopLeft = newNode;
		TopRight = GetRightEnd(newNode);
	}
	else if (current->top == nullptr)
	{
		newNode->bottom = current;
		current->top = newNode;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode;
		temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}


		TopRight = GetRightEnd(newNode);
		TopLeft = GetLeftEnd(newNode);

	}
	else if (IsBottomRight(current) || current->next == nullptr)
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->previous = current->previous->top;
		current->previous->top->next = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		TopRight = GetTopEnd(newNode);

		Node* temp01 = TopRight;
		Node* temp = TopRight->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode->previous->top;
		temp = newNode->top;
		while (temp != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp01 = temp01->top;
			temp = temp->top;
		}


		TopLeft = GetLeftEnd(TopRight);
	}
	else if (IsBottomLeft(current) || current->previous == nullptr)
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->next = current->next->top;
		current->next->top->previous = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		TopLeft = GetTopEnd(newNode);

		Node* temp01 = TopLeft;
		Node* temp = TopLeft->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		temp01 = newNode->next->top;
		temp = newNode->top;
		while (temp != nullptr)
		{
			temp01->previous = temp;
			temp->next = temp01;
			temp01 = temp01->top;
			temp = temp->top;
		}

		TopRight = GetRightEnd(TopLeft);
	}
	else
	{
		newNode->bottom = current;
		newNode->top = current->top;
		newNode->next = current->next->top;
		newNode->previous = current->previous->top;
		current->previous->top->next = newNode;
		current->next->top->previous = newNode;
		current->top->bottom = newNode;
		current->top = newNode;

		Node* TopEnd = GetTopEnd(current);

		Node* temp01 = TopEnd;
		Node* temp = TopEnd->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->top = emptyNode;
			emptyNode->next = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = TopEnd;
		temp = TopEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		Node* temp02 = newNode->next->top;
		temp01 = newNode->previous->top;
		temp = newNode->top;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp02->previous = temp;
			temp->next = temp02;
			temp02 = temp02->top;
			temp01 = temp01->top;
			temp = temp->top;
		}

		TopRight = GetRightEnd(TopEnd);
		TopLeft = GetLeftEnd(TopEnd);
	}
}
void LinkedList::InsertBelow(Node* current, string value)
{
	Node* newNode = new Node(value);
	if (IsEmpty())
	{
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (OnlyOneCell())
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* emptyNode01 = new Node();
		Node* emptyNode02 = new Node();

		current->next = emptyNode01;
		emptyNode01->previous = current;
		emptyNode01->bottom = emptyNode02;
		emptyNode02->top = emptyNode01;
		newNode->next = emptyNode02;
		emptyNode02->previous = newNode;

		TopRight = emptyNode01;
		BottomRight = emptyNode02;
		BottomLeft = newNode;
	}
	else if (IsBottomRight(current))
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}
		BottomRight = newNode;
		BottomLeft = GetLeftEnd(newNode);
	}
	else if (IsBottomLeft(current))
	{
		current->bottom = newNode;
		newNode->top = current;

		Node* temp01 = newNode;
		Node* temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}
		BottomLeft = newNode;
		BottomRight = GetRightEnd(newNode);
	}
	else if (current->bottom == nullptr)
	{
		newNode->top = current;
		current->bottom = newNode;


		Node* temp01 = newNode;
		Node* temp = current->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;

			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode;
		temp = current->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}

		BottomRight = GetRightEnd(newNode);
		BottomLeft = GetLeftEnd(newNode);

	}
	else if (IsTopRight(current) || current->next == nullptr)
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->previous = current->previous->bottom;
		current->previous->top->next = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;

		BottomRight = GetBottomEnd(newNode);

		Node* temp01 = BottomRight;
		Node* temp = BottomRight->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;
			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = newNode->previous->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomLeft = GetLeftEnd(BottomRight);
	}
	else if (IsTopLeft(current) || current->previous == nullptr)
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->next = current->next->bottom;
		current->next->bottom->previous = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;


		BottomLeft = GetBottomEnd(newNode);

		Node* temp01 = BottomLeft;
		Node* temp = BottomLeft->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;
			temp01 = temp01->next;
			temp = temp->next;
		}

		temp01 = newNode->next->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->previous = temp;
			temp->next = temp01;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomRight = GetRightEnd(BottomLeft);
	}
	else
	{
		newNode->top = current;
		newNode->bottom = current->bottom;
		newNode->next = current->next->bottom;
		newNode->previous = current->previous->bottom;
		current->previous->bottom->next = newNode;
		current->next->bottom->previous = newNode;
		current->bottom->top = newNode;
		current->bottom = newNode;

		Node* BottomEnd = GetBottomEnd(current);

		Node* temp01 = BottomEnd;
		Node* temp = BottomEnd->previous;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->previous = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->next = temp01;
			emptyNode->top = temp;

			temp01 = temp01->previous;
			temp = temp->previous;
		}

		temp01 = BottomEnd;
		temp = BottomEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{

			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}

		Node* temp02 = newNode->next->bottom;
		temp01 = newNode->previous->bottom;
		temp = newNode->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			temp01->next = temp;
			temp->previous = temp01;
			temp02->previous = temp;
			temp->next = temp02;
			temp02 = temp02->bottom;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}

		BottomRight = GetRightEnd(BottomEnd);
		BottomLeft = GetLeftEnd(BottomEnd);
	}
}

void LinkedList::InsertRowAbove(Node* current)
{
	Node* LeftEnd = GetLeftEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopLeft(LeftEnd))
	{
		Node* firstNode = new Node();

		firstNode->bottom = LeftEnd;
		LeftEnd->top = firstNode;

		Node* temp01 = firstNode;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->top = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->bottom = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}
		TopLeft = firstNode;
		TopRight = GetRightEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->bottom = LeftEnd;
		firstNode->top = LeftEnd->top;
		LeftEnd->top->bottom = firstNode;
		LeftEnd->top = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->top->next;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->previous = temp02;
			emptyNode->bottom = temp;
			emptyNode->top = temp01;
			temp02->next = emptyNode;
			temp->top = emptyNode;
			temp01->bottom = emptyNode;

			temp = temp->next;
			temp01 = temp01->next;
			temp02 = emptyNode;
		}
		TopLeft = GetTopEnd(LeftEnd);
		TopRight = GetRightEnd(TopLeft);
	}

}
void LinkedList::InsertRowBelow(Node* current)
{
	Node* LeftEnd = GetLeftEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsBottomLeft(LeftEnd))
	{
		Node* firstNode = new Node();

		firstNode->top = LeftEnd;
		LeftEnd->bottom = firstNode;

		Node* temp01 = firstNode;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->next = emptyNode;
			temp->bottom = emptyNode;
			emptyNode->previous = temp01;
			emptyNode->top = temp;

			temp01 = temp01->next;
			temp = temp->next;
		}
		BottomRight = firstNode;
		BottomLeft = GetLeftEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->top = LeftEnd;
		firstNode->bottom = LeftEnd->bottom;
		LeftEnd->bottom->top = firstNode;
		LeftEnd->bottom = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->bottom->next;
		Node* temp = LeftEnd->next;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->previous = temp02;
			emptyNode->top = temp;
			emptyNode->bottom = temp01;
			temp02->next = emptyNode;
			temp->bottom = emptyNode;
			temp01->top = emptyNode;

			temp = temp->next;
			temp01 = temp01->next;
			temp02 = emptyNode;
		}

		BottomLeft = GetBottomEnd(LeftEnd);
		BottomRight = GetRightEnd(BottomLeft);
	}
}

void LinkedList::InsertColumnAfter(Node* current)
{
	Node* TopEnd = GetTopEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopRight(TopEnd))
	{
		Node* firstNode = new Node();

		firstNode->previous = TopEnd;
		TopEnd->next = firstNode;

		Node* temp01 = firstNode;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->next = emptyNode;
			emptyNode->top = temp01;
			emptyNode->previous = temp;
			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopRight = firstNode;
		BottomRight = GetBottomEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->previous = TopEnd;
		firstNode->next = TopEnd->next;
		TopEnd->next->previous = firstNode;
		TopEnd->next = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->next->bottom;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->top = temp02;
			emptyNode->previous = temp;
			emptyNode->next = temp01;
			temp02->bottom = emptyNode;
			temp->next = emptyNode;
			temp01->previous = emptyNode;

			temp = temp->bottom;
			temp01 = temp01->bottom;
			temp02 = emptyNode;
		}

		TopRight = GetRightEnd(firstNode);
		BottomRight = GetBottomEnd(TopRight);

	}
}
void LinkedList::InsertColumnBefore(Node* current)
{
	Node* TopEnd = GetTopEnd(current);

	if (IsEmpty())
	{
		Node* newNode = new Node();
		TopLeft = newNode;
		TopRight = newNode;
		BottomLeft = newNode;
		BottomRight = newNode;
	}
	else if (IsTopLeft(TopEnd))
	{
		Node* firstNode = new Node();

		firstNode->next = TopEnd;
		TopEnd->previous = firstNode;

		Node* temp01 = firstNode;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			temp01->bottom = emptyNode;
			temp->previous = emptyNode;
			emptyNode->top = temp01;
			emptyNode->next = temp;

			temp01 = temp01->bottom;
			temp = temp->bottom;
		}
		TopLeft = firstNode;
		BottomLeft = GetBottomEnd(firstNode);
	}
	else
	{
		Node* firstNode = new Node();

		firstNode->next = TopEnd;
		firstNode->previous = TopEnd->previous;
		TopEnd->previous->next = firstNode;
		TopEnd->previous = firstNode;

		Node* temp02 = firstNode;
		Node* temp01 = firstNode->previous->bottom;
		Node* temp = TopEnd->bottom;
		while (temp != nullptr && temp01 != nullptr)
		{
			Node* emptyNode = new Node();
			emptyNode->top = temp02;
			emptyNode->next = temp;
			emptyNode->previous = temp01;
			temp02->bottom = emptyNode;
			temp->previous = emptyNode;
			temp01->next = emptyNode;

			temp = temp->bottom;
			temp01 = temp01->bottom;
			temp02 = emptyNode;
		}

		TopLeft = GetLeftEnd(firstNode);
		BottomLeft = GetBottomEnd(TopRight);
	}
}

void LinkedList::DeleteCellOfRow(Node* current)
{
	Node* temp = current;
	while (temp->next != nullptr)
	{
		temp->data = temp->next->data;

		temp = temp->next;
	}
	Node* RightEnd = GetRightEnd(current);
	RightEnd->data = "0";
}
void LinkedList::DeleteCellOfColumn(Node* current)
{
	Node* temp = current;
	while (temp->bottom != nullptr)
	{
		temp->data = temp->bottom->data;

		temp = temp->bottom;
	}
	Node* BottomEnd = GetBottomEnd(current);
	BottomEnd->data = "0";
}

void LinkedList::DeleteRow(Node* current)
{
	if (current->top == nullptr)
	{
		
		TopLeft = TopLeft->bottom;
		TopRight = TopRight->bottom;
		Node* temp = TopLeft;
		while (temp != nullptr)
		{
			temp->top = nullptr;
			temp = temp->next;
		}

	}
	else if (current->bottom == nullptr)
	{
		BottomLeft = BottomLeft->top;
		BottomRight = BottomRight->top;
		Node* temp = BottomLeft;
		while (temp != nullptr)
		{
			temp->bottom = nullptr;
			temp = temp->next;
		}
	}
	else
	{
		Node* temp = GetLeftEnd(current);
		while (temp != nullptr)
		{
			temp->top->bottom = temp->bottom;
			temp->bottom->top = temp->top;
			temp = temp->next;
		}

	}

}
void LinkedList::DeleteColumn(Node* current)
{
	if (current->next == nullptr)
	{
		TopRight = TopRight->previous;
		BottomRight = BottomRight->previous;
		Node* temp = TopRight;
		while (temp != nullptr)
		{
			temp->next = nullptr;
			temp = temp->bottom;
		}

	}
	else if (current->previous == nullptr)
	{
		TopLeft = TopLeft->next;
		BottomLeft = BottomLeft->next;
		Node* temp = TopLeft;
		while (temp != nullptr)
		{
			temp->previous = nullptr;
			temp = temp->bottom;
		}

	}
	else
	{
		Node* temp = GetTopEnd(current);
		while (temp != nullptr)
		{
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			temp = temp->bottom;
		}
	}
}
void LinkedList::ClearRow(Node* current)
{
	Node* temp = GetLeftEnd(current);
	while (temp != nullptr)
	{
		temp->data = "0";
		temp = temp->next;
	}
}
void LinkedList::ClearColumn(Node* current)
{
	Node* temp = GetTopEnd(current);
	while (temp != nullptr)
	{
		temp->data = "0";
		temp = temp->bottom;
	}
}

string LinkedList::Sum(string start, string end)
{
	string answer;
	int ans = 0;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			ans += stoi(temp->data);
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			ans += stoi(temp->data);
			temp = temp->next;
		}
	}
	else
	{
		ans = stoi(starting->data) + stoi(ending->data);
	}
	answer = to_string(ans);
	return answer;
}
string LinkedList::Average(string start, string end)
{

	string answer;
	int ans = 0;
	int count = 0;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{

		Node* temp = starting;
		while (temp != ending->bottom)
		{
			ans += stoi(temp->data);
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->bottom;

		}
		ans = ans / count;

	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			ans += stoi(temp->data);
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->next;
		}
		ans = ans / count;
	}
	else
	{
		ans = stoi(starting->data) + stoi(ending->data);
		ans = ans / 2;
	}
	answer = to_string(ans);
	return answer;

}
string LinkedList::Count(string start, string end)
{
	int count = 0;
	string answer;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;


	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (temp->data != "0")
			{
				count++;
			}
			temp = temp->next;
		}
	}
	else
	{
		count = -1;
	}
	answer = to_string(count);
	return answer;
}
string LinkedList::Min(string start, string end)
{
	string answer;
	int min = 100000;
	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (min > stoi(temp->data))
			{
				min = stoi(temp->data);
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (min > stoi(temp->data))
			{
				min = stoi(temp->data);
			}
			temp = temp->next;
		}
	}
	else
	{
		min = -1;
	}
	answer = to_string(min);
	return answer;
}
string LinkedList::Max(string start, string end)
{
	string answer;
	int max = -999;

	int Scol, Srow;
	int Ecol, Erow;

	size_t cPos = start.find('C');
	size_t rPos = start.find('R');

	// Extract column and row substrings
	string colStr = start.substr(cPos + 1, rPos - cPos - 1);
	string rowStr = start.substr(rPos + 1);

	// Convert strings to integers
	istringstream(colStr) >> Scol;
	istringstream(rowStr) >> Srow;

	size_t EcPos = end.find('C');
	size_t ErPos = end.find('R');

	// Extract column and row substrings
	string EcolStr = end.substr(EcPos + 1, ErPos - EcPos - 1);
	string ErowStr = end.substr(ErPos + 1);

	// Convert strings to integers
	istringstream(EcolStr) >> Ecol;
	istringstream(ErowStr) >> Erow;

	Node* starting = GetNodeByPosition(start);
	Node* ending = GetNodeByPosition(end);
	if (Scol == Ecol)
	{
		Node* temp = starting;
		while (temp != ending->bottom)
		{
			if (max < stoi(temp->data))
			{
				max = stoi(temp->data);
			}
			temp = temp->bottom;
		}
	}
	else if (Srow == Erow)
	{
		Node* temp = starting;
		while (temp != ending->next)
		{
			if (max < stoi(temp->data))
			{
				max = stoi(temp->data);
			}
			temp = temp->next;
		}
	}
	else
	{
		max = -1;
	}
	answer = to_string(max);
	return answer;
}

vector<string> LinkedList::CutRow(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp->data = "0";
		temp = temp->next;
	}
	return data;
}
vector<string> LinkedList::CutColumn(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp->data = "0";
		temp = temp->bottom;
	}
	return data;
}
vector<string> LinkedList::CopyRow(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp = temp->next;
	}
	return data;
}
vector<string> LinkedList::CopyColumn(string address)
{
	vector<string> data;
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		data.push_back(temp->data);
		temp = temp->bottom;
	}
	return data;
}
void LinkedList::PasteRow(string address, vector<string> data)
{
	Node* temp = GetNodeByPosition(address);
	Node* LeftEnd = GetLeftEnd(temp);
	while (temp != nullptr)
	{
		temp->data = data.front();
		data.erase(data.begin());
		temp = temp->next;
	}
}
void LinkedList::PasteColumn(string address, vector<string> data)
{
	Node* temp = GetNodeByPosition(address);
	Node* TopEnd = GetTopEnd(temp);
	while (temp != nullptr)
	{
		temp->data = data.front();
		data.erase(data.begin());
		temp = temp->bottom;
	}
}

void LinkedList::LoadFromFile(const string& filename)
{
	ifstream file(filename);
	/*if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}*/

	string line;
	vector<vector<Node*>> nodes;

	// Read data from the file into nodes
	while (getline(file, line))
	{
		istringstream iss(line);
		vector<Node*> row;

		string value;
		while (getline(iss, value, ','))
		{
			row.push_back(new Node(value));
		}

		nodes.push_back(row);
	}

	// Make links between nodes
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		for (size_t j = 0; j < nodes[i].size(); ++j)
		{
			if (i > 0)
				nodes[i][j]->top = nodes[i - 1][j];
			if (i < nodes.size() - 1)
				nodes[i][j]->bottom = nodes[i + 1][j];
			if (j > 0)
				nodes[i][j]->previous = nodes[i][j - 1];
			if (j < nodes[i].size() - 1)
				nodes[i][j]->next = nodes[i][j + 1];
		}
	}

	// Set the corners
	TopLeft = nodes[0][0];
	TopRight = nodes[0][nodes[0].size() - 1];
	BottomLeft = nodes[nodes.size() - 1][0];
	BottomRight = nodes[nodes.size() - 1][nodes[nodes.size() - 1].size() - 1];

	file.close();
}
void LinkedList::StoreToFile(const string& filename)
{
	ofstream file(filename);
	/*if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}*/

	Node* current = TopLeft;

	while (current)
	{
		Node* rowStart = current;
		while (current)
		{
			file << current->data;
			if (current->next)
				file << ",";
			current = current->next;
		}

		file << "\n";
		current = rowStart->bottom;
	}

	file.close();
}