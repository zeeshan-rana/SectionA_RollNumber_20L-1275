#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;

int StringLength(char* str)
{
	int length = 0;
	for (char* temp = str; *temp != '\0'; temp++)
		length++;

	return length;
}

char* GetStringFromBuffer(char* buffer)
{
	int strLength = StringLength(buffer);
	char* str = NULL;

	if (strLength > 0)
	{
		str = new char[strLength + 1];
		char* tempStr = str;
		for (char* tempBuf = buffer; *tempBuf != '\0'; tempBuf++)
		{
			if (*tempBuf != ' ')
				*(tempStr++) = toupper(*tempBuf);
		}
		*tempStr = '\0';
	}
	return str;
}

char** Taking_Input(ifstream& IN, char** WordList, int NumberofWords)
{
	char temp[40];
	for (int i = 0; i < NumberofWords ; i++)
	{
		IN.getline(temp, 40);
		int len = strlen(temp);
		WordList[i] = new char[len + 1];
		WordList[i] = GetStringFromBuffer(temp);
	}
	return WordList;
}

int Max_Length_Of_Word(char** WordList, int &NumberofWords)
{ //for length of the longest word  

	int MaxWord = 0;
	MaxWord = strlen(WordList[1]);
	for (int i = 1; i < NumberofWords; i++)
	{
		if (MaxWord < strlen(WordList[i]))
			MaxWord = strlen(WordList[i]);
	}
	
	return MaxWord;
}

char** DefaultGrid(int NumberofWords, char** Grid, char** WordList, int rows, int cols)
{
	//int MaxWord = Max_Length_Of_Word(WordList, NumberofWords);
	Grid = new char* [rows];
	for (int i = 0; i < rows; i++)
		Grid[i] = new char[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			Grid[i][j] = '-';
	
	return Grid;
}

void Ouput_Grid(ofstream& OUT, int MaxWord,int rows,int cols, char** Grid)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			OUT << Grid[i][j] << " ";
		OUT << endl;
	}
}

char** SortArray(int NumberofWords, char** WordList) //sorts it in a descending order
{
	int MaxWord = Max_Length_Of_Word(WordList, NumberofWords);

	for (int i = 0; i < NumberofWords; i++)
	{
		if (MaxWord < strlen(WordList[i]))
			MaxWord = strlen(WordList[i]);
	}
	char* temp = 0;
	for (int i = 0; i < NumberofWords - 1; i++)
	{
		for (int j = 0; j < NumberofWords - i - 1; j++)
		{
			if (strlen(WordList[j]) < strlen(WordList[j + 1]))
			{
				temp = WordList[j];
				WordList[j] = WordList[j + 1];
				WordList[j + 1] = temp;
			}
		}
	}
	return  WordList;
}

bool Check_Straight_LefttoRight(char** Grid, char* str, int max, int row, int col)
{
	if (col + StringLength(str) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(str); i++, col++)
	{
		if (str[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool Check_Straight_RighttoLeft(char** Grid, char* tempArray, int max, int row, int col)
{
	if (col - StringLength(tempArray) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++, col--)
	{
		if (tempArray[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool Check_Straight_ToptoBottom(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row + StringLength(tempArray) > max)
		return false;

	bool temp = false;
	for (int i = 0; i < StringLength(tempArray); i++, row++)
	{
		if (tempArray[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}
	return temp;
}

bool Check_Straight_BottomtoTop(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row - StringLength(tempArray) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++, row--)
	{
		if (tempArray[i] == Grid[row][col] || Grid[row][col] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool Check_Daigonal_LefttoRight_Down(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row + StringLength(tempArray) > max || col + StringLength(tempArray) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++)
	{
		if (tempArray[i] == Grid[row + i][col + i] || Grid[row + i][col + i] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool Check_Daigonal_RighttoLeft_Down(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row + StringLength(tempArray) > max || col - StringLength(tempArray) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++)
	{
		if (tempArray[i] == Grid[row + i][col - i] || Grid[row + i][col - i] == '-')
			temp = true;
		else
			return false;
	}
	return temp;
}

bool Check_Daigonal_LefttoRight_Up(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row - StringLength(tempArray) + 1 < 0 || col + StringLength(tempArray) > max)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++)
	{
		if (tempArray[i] == Grid[row - i][col + i] || Grid[row - i][col + i] == '-')
			temp = true;
		else
			return false;
	}

	return temp;
}

bool Check_Daigonal_RighttoLeft_Up(char** Grid, char* tempArray, int max, int row, int col)
{
	if (row - StringLength(tempArray) + 1 < 0 || col - StringLength(tempArray) + 1 < 0)
		return false;

	bool temp = false;

	for (int i = 0; i < StringLength(tempArray); i++)
	{
		if (tempArray[i] == Grid[row - i][col - i] || Grid[row - i][col - i] == '-')
			temp = true;
		else
			return false;
	}
	return temp;
}

void GridMaking(int total_rows, int total_cols,int MaxWord, int NumberofWords, char** WordList, char** Grid)
{
	int row, col, direction, Possible_directions = 8, count = NumberofWords;
	srand(time(0));
	int i = 0;
	while (count != 0)
	{
		row = rand() % MaxWord;
		col = rand() % MaxWord;

		direction = rand() % Possible_directions + 1; //random directions generator

		switch (direction)
		{
		case 1:
			if (Check_Daigonal_LefttoRight_Down(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < StringLength(WordList[i]); j++)
				{
					if (Grid[row + j][col + j] == '-')
						WordList[row + j][col + j] = temp[j];
				}
				count--;
				i++;
			}
			break;
		case 2:
			if (Check_Daigonal_LefttoRight_Up(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < StringLength(WordList[i]); i++)
				{
					if (Grid[row - j][col + j] == '-')
						Grid[row - j][col + i] = temp[j];
				}
				count--;
				i++;
			}
			break;
		case 3:
			if (Check_Daigonal_RighttoLeft_Down(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < strlen(temp); j++)
				{
					if (Grid[row + j][col - j] == '-')
						Grid[row + j][col - j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 4:
			if (Check_Daigonal_RighttoLeft_Up(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < strlen(temp); j++)
				{
					if (Grid[row - j][col - i] == '-')
						Grid[row - j][col - j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 5:
			if (Check_Straight_BottomtoTop(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < StringLength(temp); j++)
				{
					if (Grid[row - j][col] == '-')
						Grid[row - j][col] = temp[i];
				}
				count--;
				i++;
			}
			break;
		case 6:
			if (Check_Straight_LefttoRight(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < StringLength(temp); j++)
				{
					if (Grid[row][col + j] == '-')
						Grid[row][col + j] = temp[j];
				}
				i++;
				count--;
			}
			break;
		case 7:
			if (Check_Straight_RighttoLeft(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];
				for (int j = 0; j < StringLength(WordList[i]); j++)
				{
					if (Grid[row][col - j] == '-')
						Grid[row][col - j] = temp[j];
				}
				i++;
				count--;

			}
			break;
		case 8:
			if (Check_Straight_ToptoBottom(Grid, WordList[i], MaxWord, row, col))
			{
				char* temp = WordList[i];

				for (int j = 0; j < StringLength(WordList[i]); j++)
				{
					if (Grid[row + j][col] == '-')
						Grid[row + j][col] = temp[j];
				}
				i++;
				count--;
			}
			break;
		default:
			break;
		}
	}

	srand(time(NULL));
	srand(rand());
	for (int i = 0; i < total_rows; i++) //used to generate random words
	{
		for (int j = 0; j < total_cols; j++)
		{
			if (Grid[i][j] == '-')
			{
				int alphabet = 90 - (rand() % 26);
				Grid[i][j] = alphabet;
			}
		}
	}
}

int ReadFile(ifstream& fin, ifstream& IN, char** WordSearch, char** Words, int& rows, int& cols, int& size)
{
	//This function is here to read the file
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			fin >> WordSearch[i][j];

	char temp[40];
	for (int i = -1; i < size + 1; i++)
	{
		IN.getline(temp, 40);
		int len = strlen(temp);
		Words[i] = new char[len + 1];
		Words[i] = GetStringFromBuffer(temp);
	}

	return size;
}

int FindWord_RightToLeft(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream &OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count1 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0]) //this condition is made to see if the first word matches or not
			{
				int index = 2;
				int k = j - 1;
				if (WordSearch[i][k] == Words[wordnumber][1])
				{
					while (index < countletter)
					{
						if (j > index)
						{
							if (WordSearch[i][j - index] == Words[wordnumber][index]) //here the entire string is compared other than 
																					  //the first two
							{
								count1++;
								xbegin = i;
								ybegin = j;
							}
						}
						index++;
					}
				}
			}
		}
	}

	if (count1 == countletter - 2) //Seeing if it actually matches
	{
		xend1 = xbegin;
		yend1 = ybegin - countletter + 1;

		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return count1;
	}
	else
		return 0;
}

int FindWord_LeftToRight(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0]) //Seeing of the first word matches with the string
			{
				index = 2;
				if (WordSearch[i][j + 1] == Words[wordnumber][1])
				{
					while (index < countletter)
					{
						if (WordSearch[i][j + index] == Words[wordnumber][index]) //Seeing if the rest of the string matches other than
						{                                                         //the first two
							count++;
							xbegin = i;
							ybegin = j;
						}
						index++;
					}
				}
			}
		}
	}

	if (count == countletter - 2)
	{
		xend1 = xbegin;
		yend1 = ybegin + countletter - 1;

		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;
}

int FindWord_TopToBottom(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count4 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (WordSearch[i + 1][j] == Words[wordnumber][1])
				{
					while (index < countletter)
					{

						if (WordSearch[i + index][j] == Words[wordnumber][index])
						{
							count4++;
							xbegin = i;
							ybegin = j;
						}
						index++;
					}
				}
			}
		}
	}

	if (count4 == countletter - 2 || count4 == countletter - 1)
	{
		xend1 = xbegin + countletter - 1;
		yend1 = ybegin;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;

}

int FindWord_BottomToTop(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count5 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (i - 1 > 0)
				{

					if (WordSearch[i - 1][j] == Words[wordnumber][1])
					{
						while (index < countletter)
						{
							{
								if (i - index > 0)
								{


									if (WordSearch[i - index][j] == Words[wordnumber][index]) //Bottom to top hardware //Coordinates rhtey hain
									{
										count5++;
										xbegin = i;
										ybegin = j;
									}
								}
							}
							index++;
						}
					}
				}
			}
		}
	}

	if (count5 == countletter - 2 || count5 == countletter - 1)
	{
		xend1 = xbegin - strlen(Words[wordnumber]) + 1;
		yend1 = ybegin;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;
}

int FindWord_TopDiagonalLeft(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count6 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (i - 1 > 0 && j - 1 > 0)
				{
					if (WordSearch[i - 1][j - 1] == Words[wordnumber][1])
					{
						while (index < countletter)
						{
							if (i > index && j > index)
							{
								if (i - index > 0 && j - index > 0)
								{
									if (WordSearch[i - index][j - index] == Words[wordnumber][index]) //top diagonal right jav
									{
										count6++;
										xbegin = i;
										ybegin = j;
									}
								}
							}
							index++;
						}
					}
				}
			}
		}
	}

	if (count6 == countletter - 2)
	{
		xend1 = xbegin - countletter + 1;
		yend1 = ybegin - countletter + 1;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;
}

int FindWord_TopDiagonalRight(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count8 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (i - 1 > 0 && j + 1 < cols)
				{
					if (WordSearch[i - 1][j + 1] == Words[wordnumber][1])
					{
						while (index < countletter)
						{
							if (i > index)
							{
								if (i - index > 0 && j + 1 < cols)
								{
									if (WordSearch[i - index][j + index] == Words[wordnumber][index])
									{
										xbegin = i;
										ybegin = j;
										count8++;
									}
								}
							}
							index++;
						}
					}
				}
			}
		}
	}

	if (count8 == countletter - 2)
	{
		xend1 = xbegin - countletter + 1;
		yend1 = ybegin + countletter - 1;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;
}

int FindWord_DownDiagonalRight(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count2 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (i + 1 < rows && j + 1 < cols)
				{
					if (WordSearch[i + 1][j + 1] == Words[wordnumber][1])
					{
						while (index < countletter)
						{
							if (i + index < rows && j + index < cols)
							{
								if (WordSearch[i + index][j + index] == Words[wordnumber][index]) //Down diagonal right																					  
								{
									count2++;
									xbegin = i;
									ybegin = j;
								}
							}
							index++;
						}
					}
				}
			}
		}
	}
	if (count2 == countletter - 2)
	{
		xend1 = xbegin + countletter - 1;
		yend1 = ybegin + countletter - 1;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;
		return 1;
	}
	else
		return 0;
}

int FindWord_DownDiagonalLeft(char** WordSearch, char** Words, int& wordnumber, int& rows, int& cols, ofstream& OUT)
{
	int countletter = strlen(Words[wordnumber]);
	int count7 = 0, xend1 = 0, yend1 = 0, xbegin = 0, ybegin = 0, index = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (WordSearch[i][j] == Words[wordnumber][0])
			{
				index = 2;
				if (i + 1 < rows && j - 1 > 0)
				{
					if (WordSearch[i + 1][j - 1] == Words[wordnumber][1])
					{
						while (index < countletter)
						{
							if (j > index)
							{
								if (i + index < rows && j - index < cols)
								{
									if (WordSearch[i + index][j - index] == Words[wordnumber][index])
									{
										count7++;
										xbegin = i;
										ybegin = j;
									}
								}
							}
							index++;
						}
					}
				}
			}
		}
	}
	if (count7 == countletter - 2)
	{
		xend1 = xbegin + countletter - 1;
		yend1 = ybegin - countletter + 1;
		OUT << Words[wordnumber] << ":   ";
		OUT << "{(" << xbegin << "," << ybegin << ")" << " , (";
		OUT << xend1 << "," << yend1 << ")}" << endl << endl;

		cout << Words[wordnumber] << ":   ";
		cout << "{(" << xbegin << "," << ybegin << ")" << " , (";
		cout << xend1 << "," << yend1 << ")}" << endl << endl;

		return 1;
	}
	else
		return 0;
}

int main()
{
	string check;
	cout << "Hello there! You can choose what to do from the three options down below:" << endl << endl;
	while (check != "Q")
	{	
		cout << "1) Create grid(Press C)" << endl;
		cout << "2) Search Words from Grid(Press G)" << endl;
		cout << "3) Quit(Press Q)" << endl << endl;
		cout << "Enter youre option ";
		getline(cin, check);

		while (check != "G" && check != "C" && check != "Q")
		{
			cout << endl;
			cout << "Sorry! Youre input does not match the ones available" << endl << "Try again!" << endl;
			cout << endl << "Enter youre option ";
			getline(cin, check);
		}
		if (check == "Q")
		{
			cout << endl << "Goodbye.Come again!" << endl << endl;
			return 0;
		}
		if (check == "C")
		{
			string filename1, filename2, filename3;
			int NumberofWords = 0;

			cout << "Enter the file where the words are ";
			getline(cin, filename1);
			ifstream IN(filename1.c_str());


			if (!IN)
			{
				cout << "Sorry! The file could not be opened!" << endl;
				cout << "Enter the file again where the words are ";
				getline(cin, filename1);
				ifstream IN(filename1.c_str());
			}

			int row, col;
			cout << "Enter the name of the file in which you want the results in(Enter name without .txt) ";
			getline(cin, filename2);
			ofstream OUT(filename2.c_str());
			
			cout << "Enter the number of words in the file ";
			cin >> NumberofWords;

		    char** WordList = new char* [NumberofWords + 1];
			WordList = Taking_Input(IN, WordList, NumberofWords);
			int MaxWord = Max_Length_Of_Word(WordList, NumberofWords);

			cout << "Enter the number of rows ";
			cin >> row;
			cout << endl << "Enter the number of columns ";
			cin >> col;
			cout << endl;

			while (row < MaxWord && col < MaxWord)
			{
				cout << "The number of rows and columns must be larger than the maximum!!"<<endl;
				cout << "Enter the number of rows ";
				cin >> row;
				cout << endl << "Enter the number of columns ";
				cin >> col;
				cout << endl;
			}
			char** Grid = new char* [row];
			for (int i = 0; i < row; i++)
				Grid[i] = new char[col];

			Grid = DefaultGrid(NumberofWords, Grid, WordList, row, col);
			WordList = SortArray(NumberofWords, WordList);
			GridMaking(row, col, MaxWord, NumberofWords, WordList, Grid);
			Ouput_Grid(OUT, MaxWord,row,col, Grid);
			cout << "DATA TRANSFERED SUCCESSFULLY!" << endl << endl;

		}
		if (check == "G")
		{
			string filename1, filename2, filename3;
			cout << endl << "Enter the file where the grid is ";
			getline(cin, filename1);
			ifstream fin(filename1.c_str());//("Input.txt");
			cout << "Enter the file where the words are ";
			getline(cin, filename2);
			ifstream IN(filename2.c_str());

			if (!fin)
			{
				cout << "Sorry! The file could not be opened!" << endl;
				cout << endl << "Enter the file where the grid is ";
				getline(cin, filename1);
				ifstream fin(filename1.c_str());//("Input.txt");
			}
			
			if (!IN)
			{
				cout << "Sorry! The file could not be opened!" << endl;
				cout << "Enter the file where the words are ";
				getline(cin, filename2);
				ifstream IN(filename2.c_str());
			}
				cout << "Enter the name of the file in which you want the results in(Enter name without .txt) ";
				getline(cin, filename3);
				ofstream OUT(filename3.c_str());

				cout << "Youre results have been transferred succesfully!" << endl << endl;
				cout << "Youre results:" << endl;
				char** WordSearch, ** Words;
				int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, rows = 0, cols = 0, size;

				IN >> rows;
				IN >> cols;
				IN >> size;

				WordSearch = new char* [rows];
				for (int i = 0; i < rows; i++)
					WordSearch[i] = new char[cols];

				Words = new char* [size];
				size = ReadFile(fin, IN, WordSearch, Words, rows, cols, size);

				for (int wordnumber = 0; wordnumber < size; wordnumber++)
				{
					count1 = FindWord_RightToLeft(WordSearch, Words, wordnumber, rows, cols, OUT);
					count2 = FindWord_LeftToRight(WordSearch, Words, wordnumber, rows, cols, OUT);
					count3 = FindWord_TopToBottom(WordSearch, Words, wordnumber, rows, cols, OUT);
					count4 = FindWord_BottomToTop(WordSearch, Words, wordnumber, rows, cols, OUT);
					count5 = FindWord_TopDiagonalLeft(WordSearch, Words, wordnumber, rows, cols, OUT);
					count6 = FindWord_TopDiagonalRight(WordSearch, Words, wordnumber, rows, cols, OUT);
					count7 = FindWord_DownDiagonalRight(WordSearch, Words, wordnumber, rows, cols, OUT);
					count8 = FindWord_DownDiagonalLeft(WordSearch, Words, wordnumber, rows, cols, OUT);

					if (count1 == 0 && count2 == 0 && count3 == 0 && count4 == 0 && count5 == 0
						&& count6 == 0 && count7 == 0 && count8 == 0)
					{
						OUT << Words[wordnumber] << ": Not Found" << endl << endl;
						cout << Words[wordnumber] << ": Not Found" << endl << endl;
					}
				}			
		}
	}
	system("pause");


}

