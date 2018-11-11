//============================================================================
// Name        : TypeThis.cpp
// Author      : Mohammed Hossain
// Version     : Final;GoodToSubmit
// Copyright   : Your copyright notice
// Description : Akira's second assignment (Type This) in C++, Ansi-style
//============================================================================

#include <iostream>
#include <numeric>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstdlib>
#include <ctype.h>
#include<cctype>
#include <string>
#include <vector>
using namespace std::chrono;
using namespace std;
string generateRandomString(int length) {
	string random="";
	//string number = "[0-9]";
	int chance;
	char c;
	for (int i = 0; i < length; i++)
	{
		chance = rand() % 100+1;
		if ((chance>=1)&&(chance<=40))
		{
			c = rand() % 26 + 65;
			random += c;
		}

		else if ((chance >= 41) && (chance <= 80))
		{
			c = rand() % 26 + 97;
			random += c;
		}
		else if ((chance >= 81) && (chance <= 90))
		{
			random += "[0-9]";
		}
		else if ((chance >= 91) && (chance <= 100))
		{
			random += "[%-!]";
		}
	}
	return random;
}

int offset(string generated, string user) {
	int offset = 0;
	string getFinal = generated;
	for (unsigned int i = 0; i < getFinal.size(); i++)
	{
		for (unsigned int k = i+1; k <=i+1; k++) //[0-9]//[%-!]
		{
//Example String aJ[0-9]K[%-!] --> aJ0K[%-!] --> aJ0K*
			if ((getFinal.at(i) == '[') && (getFinal.at(k) == '0'))
			{
				getFinal.at(i) = '0';
				getFinal.erase(k, 4);
			}
			else if ((getFinal.at(i) == '[') && (getFinal.at(k) == '%'))
			{
				getFinal.at(i) = '*';
				getFinal.erase(k, 4);
			}
		}
	}
	for (unsigned int i = 0; i < user.size(); i++)
	{
		//Tracing back to the last example: aJ[0-9]K[%-!]
		//Example UserString = aJ9K$ --> aJ0K*
		if (isdigit(user.at(i))) //If the ith index of userString contains a digit
		{
			user.at(i) = '0'; //replace that index value with 0
		}
		else if (!isalnum(user.at(i)))
		//else if ((user.at(i) == '%') || (user.at(i) == '$') || (user.at(i) == '#') || (user.at(i) == '@') || (user.at(i) == '!'))
		{
			user.at(i) = '*';
		}
	}
	if (getFinal == user) {
		return 0;
	}
	//Example: getFinal: aJ0K* , User: aJ0
	if (getFinal.size() > user.size()) {
		user.insert(user.begin(), getFinal.size() - user.size(), ' ');
	}


	for (unsigned int i = 0; i < getFinal.size(); i++) {

		//if ((isdigit(getFinal.at(i))) && (!(isdigit(user.at(i)))))
		if(isdigit(getFinal.at(i)))
		{
			if (getFinal.at(i)!=user.at(i))
			offset += (getFinal.at(i) > user.at(i)) ?
				getFinal.at(i) - '0' : '0' - getFinal.at(i);
		}

		if (!isalnum(getFinal.at(i)))
		{
			if (getFinal.at(i) != user.at(i))
				offset += (getFinal.at(i) > user.at(i)) ?
				getFinal.at(i) - '*' : '*' - getFinal.at(i);
		}

		if (getFinal.at(i) != user.at(i)) {
			offset += (getFinal.at(i) > user.at(i)) ?
				getFinal.at(i) - user.at(i) : user.at(i) - getFinal.at(i);
		}
	}
	return offset;
}

int main() {
	srand(time(NULL));
	string userInput = "";
	int randomStringLen = 5;
	double alottedTime = 10000.0;
	int userPoint = 2000;


	while (true) {
		string randomString = generateRandomString(randomStringLen);

		cout << "Your current points " << userPoint << " , just type -> " <<randomString<<": ";

		//cout << "Enter the String you see in " << alottedTime << " milli seconds\"" << randomString << "\" : ";

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		cin >> userInput;

	/*	if ((userInput == "end")||(userInput=="END")||(userInput=="End")) {
			//cout << endl;
			break;
		}
		*/
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		int offsetValue = offset(randomString, userInput);
		duration<double> time_span = duration_cast<duration<double>>((t2 - t1) * 1000);
		double time = time_span.count();
		//std::cout << "you took " << time << " Milli seconds.";
		//std::cout << std::endl;

		if (offsetValue == 0) {
			if (time <= alottedTime) {
				userPoint += 500;
				cout << time << " milliseconds, you made it within the interval of 10000..." << endl;

			}
			else if (time > alottedTime)
			{
				userPoint -= (time - alottedTime);
			}
		}
		else {
			if (time <= alottedTime) {
				userPoint -= offsetValue;
				cout << "String offset is " << offsetValue << ", your total penalty is " << offsetValue << "..." << endl;
			}
			else if (time > alottedTime) {
				int overageOffset;
				cout << time << " milliseconds, you *failed* it within the interval of 10000..." << endl;
				overageOffset = 2 * offsetValue;
				userPoint -= overageOffset;
				userPoint -= (time - alottedTime);
				cout << "String offset is " << offsetValue << ", your total penalty is " << overageOffset+(time-alottedTime) << "..." << endl;
			}


		}

		if (userPoint < 0) {
			cout <<  "Bye" << endl;
			break;
		}
		if (userPoint > 5000) {
			cout <<  "Bye" << endl;
			break;
		}
	}
	return 0;
}
