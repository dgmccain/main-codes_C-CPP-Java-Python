#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int getEncKey(string &encKey, vector<int> &newEncKey)
{
	int matrixSize = 0;
	
	//store the encKey string as int type in vector...
	stringstream iss(encKey);
	int number;
	while (iss >> number)
		newEncKey.push_back(number);

	matrixSize = newEncKey.at(0);  //first element is size of matrix...
	newEncKey.erase(newEncKey.begin() + 0);

	return matrixSize;
}

int getPText(string &plainText, vector<char> &newPText, int sizeMatrix)
{
	int sizePText = plainText.length();  //find plaintext length...
	newPText.resize(sizePText);  //resize vector to plaintext length...

	//transfer plaintext string to vector...
	for (int i = 0; i < sizePText; i++)
	{
		newPText.at(i) = plainText.at(i);
	}

	//make lowercase...
	for (int i = 0; i < sizePText; i++)
	{
		newPText[i] = tolower(newPText[i]);
	}

	//only keep letters...
	for (int i = 0; i < sizePText; i++)
	{
		if (isalpha(newPText[i]))  //check if vector[i] is a letter then keep if true...
		{
			//vector gets plaintext if newPText[i] is a letter...
		}
		else
		{
			newPText.erase(newPText.begin() + i);  //remove the non-letter...
			sizePText--; //update new vector size...
			i--;  //need to decrement for loop because of the ereased element...
		}
	}

	//pad with x...
	if (sizePText % sizeMatrix != 0)  //sizeMatrix used to determine matrix size for encryption...
	{
		do
		{
			newPText.push_back(1);  //add element...
			sizePText++;  //update vector size...
			newPText.back() = 'x';  //set last element to x...
		} while (sizePText % sizeMatrix != 0);  //loop until vector with new plaintext has been correctly padded...
	}

	return sizePText;
}

//MAKE SURE that (+-97) works/converts properly in terminal [ASCII only]...
void makePTextInt(vector<char> &newPText, int sizePText, vector<int> &newPTextInt)
{
	for (int i = 0; i < sizePText; i++)
	{
		newPTextInt.at(i) = (newPText.at(i) - 97);  //subtract 97 so that a=0...
	}
}

void getCText(int sizeMatrix, int matrixLength, vector<int> newEncKey, int sizePText, vector<int> &newPTextInt)
{
	vector<int> tempMatrix;
	tempMatrix.resize(matrixLength);
	int tempNum = 0;
	int count = 0;  //count will be used to help loop...
	int stopInd = 0;  //this will trigger loop to stop when end of plaintext is reached...

	do
	{
		//populate tempMatrix with int vector values multiplied by encryption key int values...
		for (int j = 0; j < sizeMatrix; j++)
			for (int i = 0; i < sizeMatrix; i++)
			{
				tempMatrix[i + (j*sizeMatrix)] = newPTextInt[i + (count * sizeMatrix)] * newEncKey[i + (j*sizeMatrix)];
				//count * sizeMatrix will take the next int portion of the vector to encrypt...
			}

		//finish encryption and then store value at variable tempNum...
		for (int j = 0; j < sizeMatrix; j++)
		{
			for (int i = 0; i < sizeMatrix; i++)
			{
				tempNum += tempMatrix[i + (j*sizeMatrix)];
				if (i == sizeMatrix - 1)  //before i loop ends, get tempNum...
				{
					tempNum = tempNum % 26;
					newPTextInt.at(j + (count * sizeMatrix)) = tempNum;  //replaces int vector values with encrypted int values...
					tempNum = 0;  //reset tempNum for next cipher value...
				}
			}
		}
		count++; //move...
		stopInd++;
	} while (stopInd < (sizePText / sizeMatrix));  //CHECK IF < NEEDS TO BE REPLACED BY <= !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void makeintTextP(vector<char> &newPText, int sizePText, vector<int> &newPTextInt)
{
	for (int i = 0; i < sizePText; i++)
	{
		newPText.at(i) = (newPTextInt.at(i) + 97);  //undo subtraction from earlier...
		//the plaintext stored in newPText has now become the ciphertext...
	}
	cout << endl << endl;
}

void outputEncKey(int sizeMatrix, int matrixLength, vector<int> newEncKey)
{
	int count = 0;

	cout << endl << endl << "Key matrix:" << endl << endl;
	for (int i = 0; i < matrixLength; i++)
	{
		if (count == sizeMatrix)  //output new line when end of matrix row is reached...
		{
			cout << endl;
			count = 0;
		}
		cout << newEncKey.at(i) << " ";  //output vector containing encryption key...
		count++;
	}
	cout << endl << endl << endl;
}

void outputPText(int sizePText, vector<char> newPText)
{
	cout << "Plaintext:" << endl << endl;
	for (int i = 0; i < sizePText; i++)
	{
		cout << newPText.at(i);
	}
	cout << endl;
}

void outputCText(int sizePText, vector<char> newPText)
{
	cout << "Ciphertext:" << endl << endl;
	for (int i = 0; i < sizePText; i++)
	{
		cout << newPText.at(i);
	}
	cout << endl << endl;
}

int main(int argc, char* argv[])
{
	string plainText;
	vector<char> newPText;  //create a char vector for plaintext which will later become the ciphertext...
	string encKey;
	vector<int> newEncKey;  //maybe change int to char...
	vector<int> newPTextInt;  //convert char to int for calculations...

	//file variables...
	ifstream keyFile;
	string tempString;
	ifstream pTextFile;
	string tempString2;

	//open files...
	if (argc > 2)
	{
		//argument 1...
		keyFile.open(argv[1]);
		if (!keyFile.is_open())  //check if file is not open for troubleshooting...
		{
			cout << "ERROR - could not open file 1..." << endl << endl;
		}
		else
		{
			while (keyFile.good())
			{
				getline(keyFile, tempString);
				encKey += tempString;
				encKey += "\n";
			}
		}
		keyFile.close();  //finished with encryption key file...

		//argument 2...
		pTextFile.open(argv[2]);
		if (!pTextFile.is_open())  //check if file is not open for troubleshooting...
		{
			cout << "ERROR - could not open file 2..." << endl << endl;
		}
		else
		{
			while (pTextFile.good())
			{
				getline(pTextFile, tempString2);
				plainText += tempString2;
				plainText += "\n";
			}
		}
		pTextFile.close();  //finished with plaintext file...
	}

	//get data...
	int sizeMatrix = getEncKey(encKey, newEncKey);
	int matrixLength = sizeMatrix * sizeMatrix;  //cannot use newEncKey.length() in for loops...
	int sizePText = getPText(plainText, newPText, sizeMatrix);  //sizeMatrix needed for padding...

	//resize vector...
	newPTextInt.resize(sizePText);  //resize int vector to match char vector length...

	//output before encryption...
	outputEncKey(sizeMatrix, matrixLength, newEncKey);
	outputPText(sizePText, newPText);

	//encryption...
	makePTextInt(newPText, sizePText, newPTextInt);  //copy char vector to int vector for calculations...
	getCText(sizeMatrix, matrixLength, newEncKey, sizePText, newPTextInt); //encryption calculations...
	makeintTextP(newPText, sizePText, newPTextInt);  //transfer int vector values to char vector as ciphertext...

	//output after encryption...
	outputCText(sizePText, newPText);  //ciphertext is stored as newPText vector...

	return 0;
}