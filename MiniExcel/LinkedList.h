#pragma once
#include "Node.h"
#include<vector>
#include <fstream>

class LinkedList
{
public:
	Node* TopLeft;
	Node* TopRight;
	Node* BottomLeft;
	Node* BottomRight;

	LinkedList()
	{
		TopLeft = nullptr;
		TopRight = nullptr;
		BottomLeft = nullptr;
		BottomRight = nullptr;
	}
	bool IsEmpty();
	bool OnlyOneCell();
	bool IsTopRight(Node* current);
	bool IsTopLeft(Node* current);
	bool IsBottomRight(Node* current);
	bool IsBottomLeft(Node* current);
	Node* GetRightEnd(Node* current);
	Node* GetLeftEnd(Node* current);
	Node* GetTopEnd(Node* current);
	Node* GetBottomEnd(Node* current);
	Node* GetNodeByPosition(string position);
	void SetValue(Node* current, string value);
	void InsertAfter(Node* current, string value);
	void InsertBefore(Node* current, string value);
	void InsertAbove(Node* current, string value);
	void InsertBelow(Node* current, string value);
	void InsertRowAbove(Node* current);
	void InsertRowBelow(Node* current);
	void InsertColumnAfter(Node* current);
	void InsertColumnBefore(Node* current);
	void DeleteCellOfRow(Node* current);
	void DeleteCellOfColumn(Node* current);
	void DeleteColumn(Node* current);
	void DeleteRow(Node* current);
	void ClearColumn(Node* current);
	void ClearRow(Node* current);
	string Sum(string start, string end);
	string Average(string start, string end);
	string Count(string start, string end);
	string Min(string start, string end);
	string Max(string start, string end);
	vector<string> CutRow(string address);
	vector<string> CopyRow(string address);
	void PasteRow(string address, vector<string> data);
	vector<string> CutColumn(string address);
	vector<string> CopyColumn(string address);
	void PasteColumn(string address, vector<string> data);
	void LoadFromFile(const string& filename);
	void StoreToFile(const string& filename);
};

