#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace  std;
int iskeyword(char buffer[]);
int isoperator(char buffer[]);
int isDigit(char buffer[]);
int isIdentifier(char buffer[]);
int isPunctuation(char buffer[]);

int main()
{
    char ch='\0', buffer[15];
    ifstream fin("SourceCode.txt");
    ofstream fout("Token.txt");
    ofstream fout1("Error.txt");
    int i = 0;
    int j = 0;
    if (!fin.is_open())
    {
        cout << " File not opening\n";
        exit(0);
    }
    while (!fin.eof())
    {
        fin >> buffer;
        if (iskeyword(buffer) == 1)
        {
            fout << "buffer" << buffer << "iskeyword" << endl;
        }
        else if (isDigit(buffer) == 1)
        {
            fout << "buffer" << buffer << "is Digit" << endl;
        }
        else if (isoperator(buffer) == 1)
        {
            fout << "buffer" << buffer << "is Operator" << endl;
        }
        else if (isPunctuation(buffer) == 1)
        {
            fout << "buffer" << buffer << "is Puntuation" << endl;
        }
        else if (isIdentifier(buffer) == 1)
        {
            fout << "buffer" << buffer << "Is Identifier" << endl;
        }
        else if (iskeyword(buffer) == 0)
        {
            fout1 << buffer << " " << "Error is Keyword" << endl;
        }
        else if (isDigit(buffer) == 0)
        {
            fout1 << buffer << " " << "Error is Number" << endl;
        }
        else if (isPunctuation(buffer) == 0)
        {
            fout1 << buffer << " " << "Error is Punctuations" << endl;
        }
        else if (isIdentifier(buffer) == 0)
        {
            fout1 << buffer << " " << "Error is Identifier" << endl;
        }
        else  if (isoperator(buffer) == 0)
        {
            fout1 << buffer << " " << "Error in Opeartor" << endl;
        }
    }
    fin.close();
    fout.close();
    fout1.close();
    return 0;
}
int iskeyword(char buffer[])
{
    char Key[61][10] = { "loop", "agar", "hagar", "asm", " else", "new", "this", "auto", "enum", "operator", "throw", "bool", "explicit", "private", "true", "break", "export", "protected", "try", "case", "extern", "public", "typedef", "catch", "false", "register", "typeid", "char", "float", "typename", "class", "for", "return", "union", "const", "friend", "short", "unsigned", "goto", "signed", "using", "continue", "if", "sizeof", "virtual", "default", "inline", "static", "void", "delete", "int", "volatile", "do", "long", "struct", "double", "mutable", "switch", "while", "namespace" };
    int i = 0,check = 0;
    for (i = 0; i < 61; i++)
    {
      if (strcmp(Key[i], buffer) == false)
        {
        check = 1;
        break;
        }
    }
    return check;
}
int isoperator(char buffer[])
{
    int flag = 0;
    char option[24][10] = {
        "!=", "<>", "=:=", "==", "*", "+", "/", "-", ">>", "<<", "++", "=+", "&&", "||", "=>", "=<", "%", ":", "::", "--" };
    for (int i = 0; i < 24; i++)
    {
        if (strcmp(option[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isDigit(char buffer[])
{
    int i=0, flag = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            flag = 1;
            break;
        }
        i++;
    }
    if (flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isIdentifier(char buffer[])
{
    int size = strlen(buffer);
    int i = 0;

    if (buffer[i] == '_' && buffer[size - 1] == '_')
        return 1;
    else
        return 0;
}
int isPunctuation(char buffer[])
{
    int j = 0, flag = 0;
    while (buffer[j] != '\0')
    {
        if (buffer[j] == '[' || buffer[j] == '{' || buffer[j] == '<' || buffer[j] == '>' || buffer[j] == '}' || buffer[j] == ']')
        {
            flag = 1;
            break;
        }
        j++;
    }
    if (flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}