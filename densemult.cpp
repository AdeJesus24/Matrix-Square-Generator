#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "ArgumentManager.h"

const short MAX_SIZE = 21;                           //21 is used because we are starting at 1, as is custom in linear algebra.
short matrixSize;                                    //This value will be determined later. It is the size of the array being worked with.
typedef float Matrix[MAX_SIZE][MAX_SIZE];            //All matrices will be 21 x 21 float arrays.

short fileReader(string, string*);                   //Read from the input file into a string array. Return the number of lines, or -1 if the input file does not exist.
bool fillMatrix(string*, Matrix);                    //Take the text from fileReader and enter them into the matrix. Return false if the text isn't a square.
void squareMatrix(Matrix, Matrix);                   //Square the matrix, put the contents into a new matrix.
bool fileWriter(string, Matrix);                     //Write the matrix to the output file. Return false if the output file does not exist.
void displayMatrix(Matrix);                          //Display the matrix in the terminal.
void columnToArray(Matrix, short, float[]);          //Take a column out of the matrix and save it to an array.
void multArray(float[], float[]);                    //Multiply one array's values with another, one by one.
float addArray(float[]);                             //Add array's values together. Return the sum.

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);    //Take the arguments passed and save them to strings.
    string inputFileName = "", outputFileName = "";
    inputFileName = am.get("A");
    outputFileName = am.get("C");
    
    if(inputFileName == "" || outputFileName == ""){
        std::cout << "Please provide both an input filename and an output filename in this format:" <<
        std::endl << "\"A={input file};C={output file}\"\n";
        return 0;
    }
    
    std::cout << "File A: " << inputFileName << 
    std::endl << "File C: " << outputFileName << 
    std::endl;

    Matrix A,C;     //Matrix A is our input, C is our output.
    
    string *inputText = new string[MAX_SIZE];   //An array containing the strings of the input file.
    matrixSize = fileReader(inputFileName, inputText);
    if(matrixSize == 0){
        std::cout << "\nError: The file \"" << inputFileName << "\" has no matrix values.\n";
        return 0;
    } else if(matrixSize < 0){
        std::cout << "\nError: The file \"" << inputFileName << "\" does not exist.\n";
        return 0;
    }
    std::cout << "\nFile A appears to have " << matrixSize << " matrix rows.\n";

    if(!fillMatrix(inputText, A)){
        std::cout << "\nError: The text in \"" << inputFileName << "\" needs to be a perfectly square matrix of numerical values.\n";
        return 0;
    }
    std::cout << "\nInput Matrix:\n";
    displayMatrix(A);
    
    squareMatrix(A, C);                 //Here is where C becomes A^2.
    std::cout << "\nSquared Matrix:\n";
    displayMatrix(C);

    if( !fileWriter(outputFileName, C) ){
        std::cout << "\nError: The file \"" << outputFileName << "\" does not exist.\n";
        return 0;
    }
    std::cout << "\nThe program ran successfully. Check \"" << outputFileName << "\" for the output matrix.\n";
    
    delete[] inputText;
    return 0;
}

short fileReader(string inputFileName, string *inputText){
    ifstream reader;
    reader.open(inputFileName);
    if(!reader.good()){
        reader.close();
        return -1;
    }
    
    short count = 0;
    string temp;
    while(std::getline(reader,temp)){
        if(*(temp.begin()) == '#') continue;
        *(inputText+(count++)+1) = temp;    //The +1 is, again, due to linear algebra notation.
    }

    reader.close();
    return count;
}

bool fillMatrix(string *inputText, Matrix fillMe){
    string str_value;
    float f_value;
    short m = 0, n = 0;
    while((m++) < matrixSize){
        stringstream tempStream;
        tempStream.str(*(inputText+m));
        while(std::getline(tempStream, str_value, ' ') && (++n)){   //n needs to be incremented in the outer namespace for the if statement underneath. A silly hack but it works.
            if(n > matrixSize) return false;
            try {f_value = stof(str_value);}
            catch(const std::invalid_argument& e) {return false;}
            fillMe[m][n] = f_value;
        }
        if(n < matrixSize) return false;
        n = 0;
    }
    return true;
}

void squareMatrix(Matrix input, Matrix output){
    short m = 0, n = 0;
    float arr[MAX_SIZE];
    while((m++) < matrixSize){
        while((n++) < matrixSize){
            columnToArray(input, n, arr);   //Take the n of every m in input and put into arr.
            multArray(arr, input[m]);
            output[m][n] = addArray(arr);
        }
        n = 0;
    }
}

bool fileWriter(string outputFileName, Matrix writeMe){
    ofstream writer;
    writer.open(outputFileName);
    if(!writer.good()){
        writer.close();
        return false;
    }

    short m = 0, n = 0;
    while((m++) < matrixSize){
        while((n++) < matrixSize)
            writer << fixed << setprecision(2) << writeMe[m][n] << " ";
        writer << std::endl;
        n = 0;
    }

    writer.close();
    return true;
}

void displayMatrix(Matrix displayMe){
    short m = 0, n = 0;
    while((m++) < matrixSize){
        while((n++) < matrixSize)
            std::cout << fixed << setprecision(2) << displayMe[m][n] << " ";
        std::cout << std::endl;
        n = 0;
    }
}

void columnToArray(Matrix toArr, short n, float arr[]){
    short m = 0;
    while((m++) < matrixSize){
        arr[m] = toArr[m][n];
    }
}

void multArray(float primaryArr[], float secondaryArr[]){
    short m = 0;
    while((m++) < matrixSize){
        primaryArr[m] = primaryArr[m] * secondaryArr[m];
    }
}

float addArray(float arr[]){
    float sum = 0.0;
    short m = 0;
    while((m++) < matrixSize){
        sum += arr[m];
    }

    return sum;
}