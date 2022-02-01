#include<iostream>
#include<stack>
#include<fstream>
#include<string>
#include<stdio.h>
#define YES 50
#define NO 51
#define SCAN -1
#define POP -2



using namespace std;



string* PUNCTUATIONS = new string[]{ "[","{","<",">","}","]","\0" };
string* VARIABLES = new string[]{ "Function","ArgList","ArgList1","Arg","Declaration","Type","IdentList","IdentList1","Stmt","ForStmt","OptExpr","WhileStmt","IfStmt","ElsePart","CompoundStmt","StmtList","StmtList1","Expr","Rvalue","Rvalue1","Compare","Mag","Mag1","Term","Term1","Factor","\0" };
string* TERMINALS = new string[]{ "identifier","<",">",",",";","int","float","for","while","if","else","{","}","==","<=",">=","!=","<>","+","�","*","/","number","$","\0" };
string* OPERATORS = new string[]{ "!=","<>","=:=","==","*","+","/","-",">>","<<","++","=+","&&","||","=>","=<","%",":","::","--","\0" };
string* SYMBOLS = new string[]{ "L","D","_","E","*","/","!","=","%","|","+","-","&",":","{","[","<",">","]","}",".","\0" };
string* KEYWORDS = new string[]{ "loop","agar","magar","asm","else","new","this","auto","enum","operator","throw","bool","explicit","private","true","break","export","protected","try","case","extern","public","typedef","catch","false","register","typeid","char","float","typename","class","for","return","union","const","friend","short","unsigned goto","signed","using","continue","if","sizeof","virtual","default","inline","static","void","delete","int","volatile","do","long","struct","double","mutable","switch","while","namespace","\0" };



string* EXTRACTED_IDENTIFIER = new string[]{ "\0" };
string* EXTRACTED_OPERATORS = new string[]{ "\0" };
string* EXTRACTED_PUNCTUATIONS = new string[]{ "\0" };
string* EXTRACTED_KEYWORDS = new string[]{ "\0" };
string* EXTRACTED_NUMBER = new string[]{ "\0" };
string* SOURCE_CODE = new string[]{ "\0" };
string* MATCHED = new string[]{ "\0" };



int TransitionTable[40][22];
int ParseGrammer[51][20];
int updatedParseTable[26][24];



int dummydata = 0;
int State = 0;
int lineNumber = 0;
char readingCharacter;
char prevCharacter;
string readingAlphabet;
string readingWord;
int Action;
string StackTail;
int SOURCE_CODE_Pointer = 0;
bool parsed = false;
bool err = false;



int searchWord(string* array, const string word);
void readfile(ifstream& fin, int type);
bool checkfinalstate();
int checkTransition(char x);
void makeToken();
void makeError();
int SizeOf(string* x);
string* reGrow(string* x, string xWord);
void PrintStringArray(string* x);
void Parse();
void printParse();
void parseTransition();
void PrintInput();
void checkMatch();



struct MyStruct
{
	MyStruct* back;
	string value;
	MyStruct* front;



	MyStruct() {
		this->back = NULL;
		this->value = "";
		this->front = NULL;
	}
	MyStruct(string x) :MyStruct() {
		this->value = x;
	}
	MyStruct* addFront(string x) {
		this->front = new MyStruct(x);
		this->front->back = this;
		return this->front;
	}
	MyStruct* pop() {
		StackTail = this->value;
		this->value = "";
		if (this->back != NULL)
		{
			this->back->front = NULL;
			return this->back;
		}
		return NULL;
	}
	void printStruct() {
		if (this->back == NULL)
		{
			cout << this->value;
		}
		else
		{
			this->back->printStruct();
			cout << this->value;
		}
	}
};
MyStruct* HEAD = new MyStruct("$");
MyStruct* Tail = HEAD;



int main()
{
	Tail = Tail->addFront("1");



	ifstream finSC, finTT, finPT, finPG;
	finSC.open("Sourcecode.txt");
	finPG.open("ParseGrammerReversed.txt");
	finTT.open("TransitionTable.txt");
	finPT.open("updatedParseTable.txt");



	readfile(finTT, 2);
	finTT.close();
	readfile(finSC, 1);
	finSC.close();
	readfile(finPG, 3);
	finPG.close();
	readfile(finPT, 4);
	finPT.close();
	cout << "\t\tStack\n";
	cout << "-------------------------------------------------------------------------------------\n";

	Parse();



	/*
	abc.pop_back();
	abc.erase();
	*/
	return 0;
}



void Parse() {



	while (true)
	{
		printParse();
		parseTransition();

		if (parsed)
		{
			break;
		}
		if (Tail->value == "$" && (SizeOf(SOURCE_CODE) <= SOURCE_CODE_Pointer))
		{
			Tail->addFront("1");
			SOURCE_CODE_Pointer++;
		}
		if (parsed)
		{
			break;
		}

		/**/
	}
	if (err)
	{
		cout << "\n\nString parsed but contains error \n\n";
	}
	else
	{
		cout << "\n\nSuccessful parsing\n\n";
	}



	/*
	*/
}
void parseTransition() {
	Tail = Tail->pop();
	if (Tail == NULL)
	{
		parsed = true;
		Action = 0;
	}
	int i, j;
	if (StackTail != "$")
	{
		i = stoi(StackTail);
		if (i == 500)
		{
			Action = -500;
		}
	}
	else if (SizeOf(SOURCE_CODE) > SOURCE_CODE_Pointer)
	{
		i = 1;
	}
	else
	{
		parsed = true;
	}
	if (!parsed)
	{
		//check type
		string valueTobeChecked = SOURCE_CODE[SOURCE_CODE_Pointer];
		if (valueTobeChecked == "") { Action = -2; }
		else
		{
			if (valueTobeChecked == ":")
			{
				valueTobeChecked = ";";
			}
			int choice = searchWord(TERMINALS, valueTobeChecked);
			if (choice == -1) {
				choice = searchWord(EXTRACTED_IDENTIFIER, valueTobeChecked);
				if (choice != -1)
				{
					choice = 0;
				}
				if (choice == -1)
				{
					choice = searchWord(EXTRACTED_NUMBER, valueTobeChecked);

					if (choice == 1)
					{
						choice = 23;
					}
				}
			}
			if (i > 26)
			{
				i -= 26;
				if (i - 1 == choice)
				{
					SOURCE_CODE_Pointer++;
					Action = -20;
					MATCHED = reGrow(MATCHED, valueTobeChecked);
				}
				if (i - 1 < choice)
				{
					Action = -2;
				}
			}
			else {



				j = choice;
				int transition = updatedParseTable[i - 1][j];



				if (transition == POP)
				{
					//Tail = Tail->pop();
					Action = -2;
				}
				else if (transition == SCAN)
				{
					SOURCE_CODE_Pointer++;
					Action = -1;
					Tail = Tail->addFront(StackTail);
				}
				else
				{
					Action = transition;
					j = 0;
					while (ParseGrammer[transition - 1][j] != 0)
					{
						Tail = Tail->addFront(to_string(ParseGrammer[transition - 1][j]));
						j++;
					}
				}
			}



		}
	}
	if (Action == -1 || Action == -2)
	{
		err = true;
	}
}
void printParse() {



	PrintStringArray(MATCHED);
	cout << "\t-\t";
	Tail->printStruct();
	cout << "\t-\t";
	PrintInput();
	cout << "\t-\t";
	if (Action != 0)
	{
		if (Action == -500)
		{
			cout << "NULL";
		}
		else if (Action == SCAN)
		{
			cout << "SCAN";
		}
		else if (Action == POP)
		{
			cout << "POP";
		}
		else if (Action == -20)
		{
			cout << "Match";
		}
		else
		{
			cout << Action;
		}
	}
	cout << endl;
}
void PrintInput() {
	for (int i = SOURCE_CODE_Pointer; i <= SizeOf(SOURCE_CODE); i++)
	{
		cout << SOURCE_CODE[i];
	}
}
string* reGrow(string* x, string xWord) {



	int size = SizeOf(x);
	size++;



	string* newX = new string[size + 1];



	for (int i = 0; i < size - 1; i++)
	{
		newX[i] = x[i];
	}
	newX[size - 1] = xWord;
	newX[size] = "\0";

	return newX;
}
void PrintStringArray(string* x) {
	for (int i = 0; x[i] != "\0"; i++)
	{
		cout << x[i];
	}
}
void readfile(ifstream& fin, int type) {
	switch (type)
	{
	case 1: {
		while (fin.get(readingCharacter))
		{
		ReCheckTransition:



			int newState = checkTransition(readingCharacter); //check transition
			if (newState == 0)//no transition
			{
				if (checkfinalstate() == true)
				{ //make a token
					makeToken();
					SOURCE_CODE = reGrow(SOURCE_CODE, readingWord);
				}
				else if (readingWord != "") //on transition
				{
					makeError(); //send word to error txt
				}
				else
				{
					goto EscapeSpace;
				}
				readingWord.erase(); // word Reset
				State = 0; //state = 0
				goto ReCheckTransition; //recheck transition on last character from start state
			}
			else
			{
				State = newState;
				readingWord += readingCharacter;
			}
		EscapeSpace:
			dummydata = 0;
		}



		if (checkfinalstate() == true)
		{ //make a token
			makeToken();
		}
		else if (readingWord != "") //on transition
		{
			makeError(); //send word to error txt
		}
		readingWord.erase(); // word Reset
		State = 0;



		break;
	}
	case 2: {
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 22; j++) {
				fin >> TransitionTable[i][j];
			}
		}
		break;
	}
	case 3: {
		int i = 0;
		int j = 0;
		int x;
		while (fin >> x)
		{
			ParseGrammer[i][j] = x;
			if (x == 0) {
				i++;
				j = 0;
			}
			else
			{
				j++;
			}

		}
		break;
	}
	case 4: {
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 24; j++) {
				fin >> updatedParseTable[i][j];
			}
		}
		break;
	}
	default:
		break;
	}
}
void makeError() {
	ofstream errorFout;
	errorFout.open("error.txt", std::ios_base::app);
	errorFout << "line " << lineNumber << ": " << readingWord << endl;
	errorFout.close();
}
void makeToken() {



	ofstream tokenFout;
	tokenFout.open("token.txt", std::ios_base::app);



	if (searchWord(KEYWORDS, readingWord) != -1) //token for keywords
	{
		tokenFout << "<" << readingWord << "," << "KW" << ">" << endl;
		EXTRACTED_KEYWORDS = reGrow(EXTRACTED_KEYWORDS, readingWord);
	}
	else if (searchWord(OPERATORS, readingWord) != -1) //token for operators
	{
		tokenFout << "<" << readingWord << "," << "OP" << ">" << endl;
		EXTRACTED_OPERATORS = reGrow(EXTRACTED_OPERATORS, readingWord);
	}
	else if (searchWord(PUNCTUATIONS, readingWord) != -1) //token for punctuation
	{
		tokenFout << "<" << readingWord << "," << "PUNC" << ">" << endl;
		EXTRACTED_PUNCTUATIONS = reGrow(EXTRACTED_PUNCTUATIONS, readingWord);
	}
	else if (State > 2 && State < 9)//token for a digit
	{
		tokenFout << "<" << readingWord << "," << "Dig" << ">" << endl;
		EXTRACTED_NUMBER = reGrow(EXTRACTED_NUMBER, readingWord);
	}
	else //token for an identifier
	{
		tokenFout << "<" << readingWord << "," << "ID" << ">" << endl;
		EXTRACTED_IDENTIFIER = reGrow(EXTRACTED_IDENTIFIER, readingWord);
	}
	tokenFout.close();
}
bool checkfinalstate() {
	if (TransitionTable[State][21] == YES || searchWord(KEYWORDS, readingWord) != -1) {
		return true;
	}
	return false;
}
int checkTransition(char x) {
	int getState = 0;
	readingAlphabet = x;



	if (x == '\n') {
		lineNumber++;
	}
	else if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	{
		if (prevCharacter >= '0' && prevCharacter <= '9' && readingCharacter == 'E')
		{
			getState = TransitionTable[State][searchWord(SYMBOLS, readingAlphabet)];
		}
		else
		{
			getState = TransitionTable[State][0];
		}
	}
	else if (x >= '0' && x <= '9')
	{
		getState = TransitionTable[State][1];
	}
	else
	{
		int getRow = searchWord(SYMBOLS, readingAlphabet);



		if (getRow != -1)
		{
			getState = TransitionTable[State][getRow];



		}
		else
		{
			getState = 0;
		}
	}
	prevCharacter = readingCharacter;
	return getState;
}
int searchWord(string* array, const string word) {
	for (int i = 0; array[i] != "\0"; i++)
	{
		if (array[i] == word)
		{
			return i;
		}
	}
	return -1;
}
int SizeOf(string* x) {



	for (int i = 0; ; i++)
	{
		if (x[i] == "\0")
		{
			return i;
		}
	}
}