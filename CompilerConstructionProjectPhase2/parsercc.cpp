#include "stackp.h"
#pragma once




struct Parsetree_index
{
	string type;
	int index;
	int noassigned;
};
struct Tokken {
	string name;
	string type;
};

vector <vector<int>> grammerMatrix;
vector <vector<int>> parseTable;
vector <Parsetree_index> ptCol;
vector <Tokken>token;
vector <int>grammer;
Stack st;


void grammer_matrix();
void parse_table();
void Pt_Col_No();
void Tokens();
void parsing();
Parsetree_index indexcol_search(string type);
bool tokencheck(int top);
void push_grammermatrix_Row(int i);
void Write_grammer(vector <int> gr);

ofstream fout("GrmmerProduction.txt");
ofstream terror("errors.txt");

int main()
{
	grammer_matrix();
	parse_table();
	Pt_Col_No();
	Tokens();
	parsing();

	return 0;
}



void parsing()
{
	int ptRow = 0;
	st.pushin(-4);
	st.pushin(0);
	                                           //grammer.push_back(0);
	Parsetree_index tokenInfo;
	                                             //pushGrammerMatrixRow(0);
	for (int i = 0; i < token.size(); i++)
	{
		int top = st.Top();
		tokenInfo = indexcol_search(token[i].type);
		                                                    //cout << tokenInfo.index << endl;
		while (top != tokenInfo.noassigned)
		{
			grammer.push_back(top);
			Parsetree_index infodollar = indexcol_search("$");
			if (tokencheck(top) == true && top != infodollar.noassigned)
			{
				st.popout();
				terror << token[i].name << " " << token[i].type << endl;
				//grammer.pop_back();
				break;
			}
			if (top == -4)
			{
				//grammer.push_back(0);
				//terror << token[i].name << " " << token[i].type << endl;
				st.pushin(0);
				break;
			}
			if (top == -3)
			{
				//grammer.pop_back();
				st.popout();
			}
			if (tokenInfo.index < 0)
			{
				break;
			}
			if (tokenInfo.index >= 0 && top >= 0)
			{
				int lineNo = parseTable[top][tokenInfo.index];
				if (lineNo == -1 || lineNo == -2)
				{
					st.popout();
					terror << token[i].name << " " << token[i].type << endl;
				}
				if (lineNo >= 0)
				{
					//grammer.push_back(top);
					st.popout();
					push_grammermatrix_Row(lineNo);
					Write_grammer(grammer);
					grammer.clear();
				}
			}

			top = st.Top();
		}
		if (top == tokenInfo.noassigned)
		{

			st.popout();
			//grammer.pop_back();
			//grammer.clear();
			//grammer.push_back(0);
		}
	}
}

void Write_grammer(vector <int> gr)
{
	fout << gr[0];
	fout << " -> ";
	for (int i = 1; i < gr.size(); i++)
	{
		cout << gr[i];
		cout << " ";
		fout << gr[i];
		fout << " ";
	}
	cout << endl;
	fout << endl;
}

void push_grammermatrix_Row(int i)
{

	for (int m = grammerMatrix[i].size() - 1; m >= 0; m--)
	{
		st.pushin(grammerMatrix[i][m]);
		//grammer.push_back(grammerMatrix[i][m]);
	}
	for (int m = 0; m < grammerMatrix[i].size(); m++)
	{
		grammer.push_back(grammerMatrix[i][m]);
	}
}

void Tokens()
{

	ifstream fin("Tokens.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}

	while (!fin.eof())
	{
		Tokken t;
		fin >> t.name;
		fin >> t.type;
		token.push_back(t);
	}
	fin.close();
}

Parsetree_index indexcol_search(string type)
{
	int size = ptCol.size();
	for (int i = 0; i < size; i++)
	{

		if (ptCol[i].type.compare(type) == 0)
		{
			//cout << ptCol[i].type << endl;
			return ptCol[i];

		}
	}
	Parsetree_index temp;
	temp.index = -1;
	return temp;
}

bool tokencheck(int top)
{
	int size = ptCol.size();
	for (int i = 0; i < size; i++)
	{
		if (top == ptCol[i].noassigned)
		{
			return true;
		}
	}
	return false;
}

void grammer_matrix()
{
	int row = 0, col = 0; char line[1024];
	ifstream fin("grammerMatrix.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}

	while (!fin.eof())
	{
		vector <int> num;
		fin.getline(line, 1024);
		char* next;
		char* token = strtok_s(line, " ", &next);

		// Keep printing Tokens while one of the 
		// delimiters present in str[]. 
		while (token != NULL)
		{
			num.push_back(stoi(token));
			token = strtok_s(NULL, " ", &next);
		}
		grammerMatrix.push_back(num);
	}
	fin.close();
}

void parse_table()
{
	int row = 0, col = 0;
	ifstream fin("parseTable.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}
	int i = 0, num = 0;
	fin >> row; fin >> col;
	while (i < row)
	{
		int k;
		vector<int>num1;
		for (k = 0; k < col; k++)
		{
			fin >> num;
			num1.push_back(num);
		}
		parseTable.push_back(num1);
		i++;
	}
	fin.close();
}

void Pt_Col_No()
{
	int row = 0, col = 0; Parsetree_index ind;
	ifstream fin("PT_columns.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}

	while (!fin.eof())
	{

		fin >> ind.type;
		fin >> ind.index;
		fin >> ind.noassigned;
		ptCol.push_back(ind);
	}
	fin.close();
}

