// Description:
//      This project involves designing and creating a C++ program 
//     that will convert a “pipe-delimited” text file to a file in CSV format. 

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Function prototypes
void openInputFile(string& inputFileName, ifstream& inputFile);
void openOutputFile(string& outputFileName, ofstream& outputFile);
int splitLineToArray(string inputText, string inputDelim, string outputFieldArray[], int maxFields);
void processDataFile(ifstream& infile, ofstream& outfile, string delimiter, string array[], int size);
void DisplayHelp();

//Global variables
const int SIZE = 100;
const string delimiter = "|";

int main()
{
    ifstream inputFile; //object let's us open a file. 
    ofstream outputFile; //object let's us create a file. 

    string array[SIZE]; //array with 100 elements

    string inputFileName;
    string outputFileName;


    bool KeepRunning = true; // To control the loop

    while (KeepRunning == true)
    {
        string choice; // Will hold the user command. 
        cout << "Command: ";
        getline(cin, choice);

        if (choice == "i" || choice == "I")
            openInputFile(inputFileName, inputFile);

        else if (choice == "o" || choice == "O")
            openOutputFile(outputFileName, outputFile);

        else if (choice == "p" || choice == "P")
            processDataFile(inputFile, outputFile, delimiter, array, SIZE);

        else if (choice == "ci" || choice == "CI")
            inputFile.close();

        else if (choice == "co" || choice == "CO")
            outputFile.close();

        else if (choice == "h" || choice == "H")
            DisplayHelp();
            
        else if (choice == "q" || choice == "Q")
            KeepRunning = false;

    }

    return 0;
}

//*************************
//Function will open a file
//*************************
void openInputFile(string& inputFileName, ifstream& inputFile)
{
    cout << "Enter input filename: ";
    getline(cin, inputFileName); //Take the users input

    //Open the file
    inputFile.open(inputFileName);
  
}

//*************************
//Function will create a file. 
//*************************
void openOutputFile(string& outputFileName, ofstream& outputFile)
{
    cout << "Enter output filename: ";
    getline(cin, outputFileName); //Take the users input

    //Open the file
    outputFile.open(outputFileName);
 
}


int splitLineToArray(string inputText, string inputDelim, string outputFieldArray[], int maxFields)
{
	//	Local Variables:
	int nextFieldPosition = 0;		//	Start position of data field.
	int foundPosition;				//  Position where delimiter was found,
	int fieldCount = 0;		        //  Number of data fields found so far,
	bool endOfLine = false;			//	Flag -- end of input line detected,
	string dataField;				//  Copy of the data field.

	while (!endOfLine)
	{
		foundPosition = inputText.find(inputDelim, nextFieldPosition);
		if (foundPosition == string::npos)
		{
			// (Here if the string 'find' function reached the end of the input string.)
			endOfLine = true;
			foundPosition = inputText.length();

			if (foundPosition > nextFieldPosition)
			{
				dataField = inputText.substr(nextFieldPosition,
					foundPosition - nextFieldPosition);
				fieldCount++;
			}
		}
		else
		{
			// (Here if 'inputDelim' was found in the input string.)
			// Copy the data field contents from the input string to the
			// 'dataField' local variable.
			dataField = inputText.substr(nextFieldPosition, foundPosition - nextFieldPosition);
			fieldCount++;

			// Adjust 'nextFieldPosition' as preparation for finding NEXT delimiter.
			nextFieldPosition = foundPosition + 1;
		}

		if (fieldCount > 0)
		{
			if (fieldCount > maxFields)
			{
				cout << "ERROR at line __LINE__: too many input fields, fieldCount="
					<< fieldCount << endl;
			}
			else
			{
				outputFieldArray[fieldCount - 1] = dataField;
			}
		}
	} // (end while)


	return fieldCount;
} // (end function splitLineToArray )

void processDataFile(ifstream& infile, ofstream& outfile, string delimiter, string array[], int SIZE)
{
	 // Stores comma position, open and close double quotes position
    int CommaPosition, Open_DQuote_Position, Close_DQuote_Position;   

	string inputBuffer;
	int fieldCount = 0;               //Number of fields
    int StartFieldPosition = 0;      //Start of field

    string comma = ",";
    string DoubleQuote = "\"";

	while (getline(infile, inputBuffer)) 
	{
        cout << "\nInput data = " << inputBuffer;
        
        //Call the splitLineToArray function and assign it's return to fieldCount
        fieldCount = splitLineToArray(inputBuffer, delimiter, array, SIZE);
        
        for (int i = 0; i < fieldCount; i++)
        {
            
            string field = array[i]; //Store field in a string. Which will let us use the .find() function.
            
            //Use the find function to find a comma, double Quote
            CommaPosition = field.find(comma, StartFieldPosition);
            Open_DQuote_Position = field.find(DoubleQuote, StartFieldPosition);
            Close_DQuote_Position = field.find(DoubleQuote, Open_DQuote_Position + 1);
            
            // if comma is found add a double quote
            if (CommaPosition >= 0)
                outfile << DoubleQuote << field << DoubleQuote << comma;
            
            // If double quotes are found use the insert member function
            else if (Open_DQuote_Position >= 0 && Close_DQuote_Position >= 0)
                outfile << DoubleQuote << field.insert(Open_DQuote_Position + 1, DoubleQuote).insert(Close_DQuote_Position + 1, DoubleQuote) << DoubleQuote << comma;
            //If no commas or quotes are found. Add a comma at the end of the field. 
            else
                outfile << field << comma;
        }
        // Start a new line
        outfile << endl;
    }
    cout << "\nEnd of file encountered. " << endl;
}

void DisplayHelp()
{
        cout << "Supported commands: \n"
        << "\t CI \t\t\t Close inputfile. \n"
        << "\t CO \t\t\t Close output file. \n"
        << "\t h \t\t\t print this help text. \n"
        << "\t i \t\t\t open file for input. \n"
        << "\t o \t\t\t open file for output. \n"
        << "\t p \t\t\t process data file. \n"
        << "\t q\t\t\t quit. (end the program). \n";
}