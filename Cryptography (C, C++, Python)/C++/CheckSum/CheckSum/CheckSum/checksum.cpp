#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

string decToHex(int n)
{
	string tempStr; 
	char hexNum[50];
	string buffStr = "0";  //used for attaching 0 to beginning of string for math...
	int i = 0;  //used for while loop

	while (n != 0)
	{
		int tempRem = 0;

		tempRem = n % 16;  //remainder is stored in tempRem...
						   //also, 16 is chosen because there are 16 potential hex values...

		if (tempRem < 10)  //if remainder is less than 10, 
		{
			hexNum[i] = tempRem + 48;  //add 48, which is 0 in ascii table...
			i++;
		}
		else
		{
			hexNum[i] = tempRem + 55;  //should only occur during at the end of calculation...
			i++;
		}

		n = n / 16;  //update n...
	}
	for (int j = i - 1; j >= 0; j--)  //tempStr gets hex number array in reverse... 
		tempStr += hexNum[j];
	if (tempStr.length() == 1)  //check if string has 2 values for math...
	{
		buffStr += tempStr;  //add 0 to beginning of string if length is less than 2...
		tempStr = buffStr;
	}
	return tempStr;
}

int getData(string &fileTxt, vector<char> &newFileTxt, int sizeMessage, int numBits)
{
	sizeMessage = fileTxt.length();
	newFileTxt.resize(sizeMessage);  //resize vector to file text length...

	//transfer file text string to vector...
	for (int i = 0; i < sizeMessage; i++)
	{
		newFileTxt.at(i) = fileTxt.at(i);
	}

	//pad with X...
	switch (numBits)
	{
	case 8:
		//no padding for 8 bits...
		break;
	case 16:
		if (sizeMessage % 2 != 0)  //16 bit checksums use 2 bits at a time...
		{
			do
			{
				newFileTxt.push_back(1);  //add element...
				sizeMessage++;  //update size...
				newFileTxt.back() = 'X';  //set last element to x...
			} while (sizeMessage % 2 != 0);  //loop until vector with new plaintext has been correctly padded...
		}
		break;
	case 32:
		if (sizeMessage % 4 != 0)  //32 bit checksums use 4 bits at a time...
		{
			do
			{
				newFileTxt.push_back(1);  //add element...
				sizeMessage++;  //update size...
				newFileTxt.back() = 'X';  //set last element to x...
			} while (sizeMessage % 4 != 0);  //loop until vector with new plaintext has been correctly padded...
		}
		break;
	default:
		cout << "ERROR - something went wrong with the bit input..." << endl;
	}

	return sizeMessage;
}

unsigned long int findChecksum(unsigned long int checksum, vector<char> &newFileTxt, int sizeMessage, int numBits)
{
	string tempStr;  //used for 16 and 32 bits...
	long unsigned int tempInt = 0;

	switch (numBits)
	{
	case 8:
		for (int i = 0; i < sizeMessage; i++)
		{
			checksum += newFileTxt.at(i);
			if (checksum > 255)  //handles overflow - checks if more than 8 bits...
			{
				checksum -= 256;  //if more than 8 bits then subtract the overflow...
			}
		}
		break;
	case 16:
		for (int i = 0; i < sizeMessage; i++)
		{
			//convert dec to hex before adding to tempStr...
			tempStr += decToHex(newFileTxt[i]);
			tempStr += decToHex(newFileTxt[i+1]);
			//get full tempStr by converting second dec to hex and adding to tempStr...
			stringstream(tempStr) >> hex >> tempInt;  //convert hex to dec and store in tempInt before checksum transfer...
			checksum += tempInt;
			if (checksum > 65535)  //checks if more than 16 bits...
			{
				checksum -= 65536;  //subtracts overflow...
			}
			tempStr.clear();
			i++;  //i needs to be incremented for tempVal...
		}
		break;
	case 32:
		for (int i = 0; i < sizeMessage; i++)
		{
			tempStr += decToHex(newFileTxt[i]);
			tempStr += decToHex(newFileTxt[i+1]);
			tempStr += decToHex(newFileTxt[i+2]);
			tempStr += decToHex(newFileTxt[i+3]);
			stringstream(tempStr) >> hex >> tempInt;  //use stringstream to convert hex to int...
			checksum += tempInt;
			if (checksum > 4294967295)
			{
				checksum -= 4294967296;
			}
			tempStr.clear();
			i++;
			i++;
			i++;
		}
		break;
	default:
		cout << "ERROR - something went wrong when determining number of bits for checksum..." << endl;
	}
	return checksum;
}

int outputData(int sizeMessage, vector<char> newFileTxt, unsigned long int checksum, int numBits)
{
	//output file text...
	for (int i = 0; i < sizeMessage; i++)
	{
		if (i % 80 == 0)
		{
			cout << endl;
		}
		cout << newFileTxt.at(i);
	}
	//output checksum...
	cout << endl;
	printf("%2d bit checksum is %8lx for all %4d chars\n", numBits, checksum, sizeMessage);
	cout << endl;

	return 0;
}

int main(int argc, char* argv[])
{
	//variables with file data for manipulation...
	string tempString;
	string fileTxt;  //will contain original plaintext...
	vector<char> newFileTxt;  //will contain file string in char format...
	int sizeMessage = 0;

	//checksum...
	unsigned long int checksum = 0;  //change from string to int...

	//get input from arg[2]...
	string bitInput = argv[2];
	int numBits = 0;

	//file...
	ifstream file1;

	//flag
	bool flag = false;

	//open files...
	if (argc > 2)
	{
		//argument 1...
		file1.open(argv[1]);
		if (!file1.is_open())  //check if file is not open for troubleshooting...
		{
			cout << "ERROR - could not open file 1..." << endl << endl;
		}
		else
		{
			while (file1.good())  //copy file data to string...
			{
				getline(file1, tempString);
				fileTxt += tempString;
			}
			fileTxt += '\n';  //NEWLINE added to file text before padding...
		}
		file1.close();  //finished with encryption key file...

		//argument 2...
		//the following if statements DO NOT read input from a file, but instead read
		//from the command line input directly to determine if the input was within bounds...
		if (bitInput == "8")  //use a switch case if argv[2] int/char casting issues can be solved...
		{
			numBits = 8;
		}
		else if (bitInput == "16")
		{
			numBits = 16;
		}
		else if (bitInput == "32")
		{
			numBits = 32;
		}
		else
		{
			cerr << "Valid checksum sizes are 8, 16, or 32" << endl;  //error message...
			flag = true;
		}
	}

	if (flag == false)
	{
	//get data...
	sizeMessage = getData(fileTxt, newFileTxt, sizeMessage, numBits);

	//resize vector...
	newFileTxt.resize(sizeMessage);  //resize vector to file text length...

	//find checksum...
	checksum = findChecksum(checksum, newFileTxt, sizeMessage, numBits);

	//output...
	outputData(sizeMessage, newFileTxt, checksum, numBits);
	}

	system("pause");

	return 0;
}