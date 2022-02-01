#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#pragma once

using namespace std;

class Stack 
{
private:
	vector <int> terminal;
	int size;
	int count;
public:
	Stack()
	{
		count = -1;
		size = 0;
	}
	void pushin(int num)
	{
		terminal.push_back(num);
		count++;
		size++;
	}
	int popout()
	{
		int n = terminal[count--];
		terminal.pop_back();
		return n;
	}
	int Top() {

		return terminal[count];
	}

};