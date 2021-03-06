// Languages.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <cmath>
using namespace std;

void open(string file, map<char, float> &w, map <char, float> ::iterator it)
{
	char ch;
	int tmp = 0;
	fstream myfile;
	myfile.open(file.c_str());

	if (myfile.is_open())
	{
		
		myfile.get(ch);
		ch = toupper(ch);
		if (ch >= 65 && ch <= 90)
		{
			w.insert(pair<char, float>(ch, 1));
		}
		
		while (myfile.get(ch))
		{
			ch = toupper(ch);
			if (ch >= 65 && ch <= 90) 
			{
				for (it = w.begin(); it != w.end(); it++)
				{
					if (it->first == ch)
					{
						it->second++;
					}
					else
					{
					w.insert(pair<char, float>(ch, 0));
					}
				}
			}
		}
	}
	else cout << "Blad otwierania pliku" << endl;

	myfile.close();
}

void save(string file, map<char, float> &w, map <char, float> ::iterator it)
{
	ofstream myfile;
	myfile.open(file.c_str());

	if (myfile.is_open())
	{
		for (it = w.begin(); it != w.end(); it++)
		{
			myfile << it->first << endl;
			myfile << it->second << endl;
		}
	}
	else cout << "Blad otwierania pliku" << endl;

	myfile.close();
}

int counter(string file, map<char, float> &w, map <char, float> ::iterator it)
{
	char ch;
	int tmp = 0;
	fstream myfile;
	myfile.open(file.c_str());

	if (myfile.is_open())
	{
		while (myfile.get(ch))
		{
			ch = toupper(ch);
			if (ch >= 65 && ch <= 90) tmp++;
		}
	}
	else cout << "Blad otwierania pliku" << endl;

	myfile.close();
	return tmp;
}

float check(map<char, float> &w, map <char, float> ::iterator it, map<char, float> &ex, map <char, float> ::iterator e)
{
	float sum=0;
	int counter = 0;
	for (it = w.begin(); it != w.end(); it++)
	{
		for (e = ex.begin(); e != ex.end(); e++)
		{
			if (e->first == it->first)
			{
				sum += abs(e->second - it->second);
				counter++;
			}
		}
	}
	float aver = (sum / counter);
	return aver;
}

void load(string file, map<char, float> &w, map <char, float> ::iterator it)
{
	char c;
	float f;
	fstream myfile;
	myfile.open(file.c_str());

	if (myfile.is_open())
	{
		while (myfile >> c)
		{
			myfile >> f;
			w.insert(pair<char, float>(c, f));
		}
	}
	else cout << "Blad otwierania pliku" << endl;

	myfile.close();
}

int main()
{
	map <char, float> letters;
	map <char, float> ::iterator it;
	map <char, float> english;
	map <char, float> ::iterator en;
	map <char, float> german;
	map <char, float> ::iterator ge;
	map <char, float> french;
	map <char, float> ::iterator fr;
	map <char, float> polish;
	map <char, float> ::iterator po;


	open("tekst.txt", letters, it);
	for (it = letters.begin(); it != letters.end(); it++)
	{
		it->second = it->second / counter("tekst.txt", letters, it);
	}

	load("polski.txt", polish, po);
	load("angielski.txt", english, en);
	load("niemiecki.txt", german, ge);
	load("francuski.txt", french, fr);

	cout << "**IM BLIZEJ ZERA TYM BARDZIEJ PEWNE UZYCIE DANEGO JEZYKA**" << endl;
	cout << "Roznice z jezykiem polskim wynosza "<< check(letters, it, polish, po)<<endl;
	cout << "Roznice z jezykiem angielskim wynosza " << check(letters, it, english, en) << endl;
	cout << "Roznice z jezykiem francuskim wynosza " << check(letters, it, french, fr) << endl;
	cout << "Roznice z jezykiem niemieckim wynosza " << check(letters, it, german, ge) << endl;

	float result = abs (check(letters, it, polish, po));
	string re = "polski";
	if (result > abs(check(letters, it, english, en)))
	{
		result = abs(check(letters, it, english, en));
		re = "angielski";
	}
	if (result > abs(check(letters, it, french, fr)))
	{
		result = abs(check(letters, it, french, fr));
		re = "francuski";
	}
	if (result > abs(check(letters, it, german, ge)))
	{
		result = abs(check(letters, it, german, ge));
		re = "niemiecki";
	}
	cout <<endl<< "Najprawdopodobniej zostal uzyty jezyk " << re << endl<<endl;
	system("PAUSE");
    return 0;
}



