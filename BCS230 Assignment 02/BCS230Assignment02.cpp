//Ian Liotta
//2/9/19
//Assignment 2
//Read IRIS.csv. Report the number of lines, columns, and different classes.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int countLines(string fileName);
int countColumns(string fileName);
int countClasses(string fileName);
bool isInFile(string fileName, string query);


int main() {
	cout << "Number of lines: " << countLines("IRIS.csv") << endl;
	cout << "Number of columns: " << countColumns("IRIS.csv") << endl;
	cout << "Number of classes: " << countClasses("IRIS.csv") << endl;

	return 0;
}

int countLines(string fileName) {
	ifstream inFile(fileName);
	int numLines = 0;
	string input;

	if (inFile) {
		//read one line at a time until end of file is reached
		while (getline(inFile, input, '\n')) {
			//count each line read
			numLines++;
		}
	}
	inFile.close();
	return numLines;
}

int countColumns(string fileName) {
	ifstream inFile(fileName);
	stringstream strStream;
	string input;
	int numCol = 0;

	//check if the file opened properly
	if (inFile) {
		//read a single line into a string
		getline(inFile, input, '\n');
		//copy string into a strstream
		strStream << input;
		//each comma in the stream indicates a new column
		while (getline(strStream, input, ',')) {
			numCol++;
		}
	}
	inFile.close();
	return numCol;
}

int countClasses(string fileName) {
	ifstream inFile(fileName);
	fstream classFile("classes.txt");
	stringstream strStream;
	string input, className;

	while (inFile) {
		//get an entire line and copy it to a stringstream
		getline(inFile, input, '\n');
		strStream << input;
		//read the last column into className
		while (getline(strStream, className, ',')) {}
		//if className is not present in classes.txt and we aren't done reading inFile, write it to the file. EOF check is to avoid writing a superflous line to classes.txt that would change the class count.
		if (classFile && !inFile.eof()) {
			if (!isInFile("classes.txt", className))
				classFile << className << endl;
		}
		strStream.clear();
	}
	classFile.close();
	inFile.close();

	return countLines("classes.txt");
}

//Search file fileName for string query. If it is found return true, else return false.
bool isInFile(string fileName, string query) {
	ifstream inFile;
	string input;

	inFile.open(fileName);
	if (inFile) {
		while (inFile >> input) {
			if (input != query)
				continue;
			else
				return true;
		}
	}
	inFile.close();
	return false;
}


