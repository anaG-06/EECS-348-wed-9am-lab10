/*
Date: 11.4.26
Author: Ana Gonzalez Yuil
Lab: 10
Sources: personal code from lab5 modified to fit lab10
Description: matrix manipulation using classes
*/

// overload operators
// same conditions as lab5

// myMatrix = Matrix(filename) <-- initialization should look like this
// N x N (square matricies)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

//each method should return a MatrixType

class Matrix
{
    private: 
    std::vector<std::vector<int>> matrix;
    int n; //dimensions of matrix
    
    public:
    //constructing Matrix with file
    Matrix (std::string filename, int start)
    {
        if (!(this->loadMatrix(filename, start)))
        {
            std::cout << "Matrix could not be created.\n";
        }
    }
    
    //constructing matrix without file
    Matrix()
    {
        // std::cout << "Matrix created\n";
        n = matrix.size();
    }

    int getSize()
    {
        return n;
    }

    void setSize(int n)
    {
        this->n = n;
    }
    
    bool loadMatrix(std::string filename, int start)
    {
        //input file holds both matrices, so there should be some sort of var
        //that tells row creator loop where to start reading lines?
        std::vector<std::string> fileRaw;
        std::string line;
        std::ifstream myFile(filename);
        
        std::vector<int> row;
        std::string element;
        int elementINT;

        int temp_n = n;

        
        //open and read file
        if (myFile.is_open())
        {
            while (getline(myFile,line))
            {
                fileRaw.push_back(line); //push file contents into unorganized vector
            }
            myFile.close();
        }
        else
        {
            std::cout << "unable to open file. ";
            return false;
        }
        
        n = stoi(fileRaw[0]); //set dimensions
        
        //where to start reading for matrix formation
        // 1 signifies that reading should start from the top
        if (start != 1)
        {
            start = n + 1; //otherwise start after first matrix
            temp_n = n * 2;
        }
        else
        {
            start = 1;
            temp_n = n;
        }
        
        //create matrix
        for (int i = start; i <= temp_n; i++)
        {
            std::string temp = fileRaw.at(i).c_str(); //hold row of text
            
            //makes it so that there is one unwanted character in front of start of line, 
            //makes it easier to clean/get desired part of string
            temp.insert(temp.begin(),'_'); 
            
        //create row
        for (int j = 0; j < temp.length()-2; j = j+3)
        {
            if (temp.at(j+1) == '0') //if number only has single digit, dont take zero in front
            {
                element += temp.at(j+2);
            }
            else{// else take 2 digit number 
                element += temp.at(j+1);
                element += temp.at(j+2);
            }

            // std::cout << element << "\n"; //testing

            elementINT = stoi(element);

            row.push_back(elementINT);

            element.clear();//clears element for reuse
        }

        //push onto class matrix
        this->matrix.push_back(row);
        row.clear(); //clear row for reuse

        }
        
        // std::cout << "Matrix created using: " << filename << "\n";
        return true;
    }

    void printMatrix()
    {
        for (int i =0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << std::setw(3) << matrix.at(i).at(j) << "  ";
            }
            std::cout << "\n";
        }
    }

    //overloading addition
    friend Matrix operator+(Matrix A, Matrix B)
    {
        Matrix result;
        result.setSize(A.getSize());

        std::vector<int> row;
        int numA;
        int numB;
        
        for (int i = 0; i < A.getSize(); i++)
        {
            for (int j = 0; j < A.getSize(); j++)
            {
                numA = A.matrix.at(i).at(j);// A[i][j]
                numB = B.matrix.at(i).at(j);// B[i][j]

                row.push_back(numA + numB); //add them together and push to row
            }

            result.matrix.push_back(row); //push row into result matrix
            row.clear();
        }
        
        return result;

    }

    //overloading multiplication
    friend Matrix operator*(Matrix A, Matrix B)
    {
        int dim = A.getSize();
        
        Matrix result;
        result.setSize(dim);

        std::vector<int> row;
       
        int element = 0;
        int numA;
        int numB;
        int temp_num;

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                for (int k = 0; k < dim; k++)
                {
                    numA = A.matrix.at(i).at(k);
                    numB = B.matrix.at(k).at(j);

                    temp_num = numA * numB;
                    element += temp_num;

                }
                row.push_back(element);
                element = 0;
            }
            result.matrix.push_back(row);
            row.clear();
        }

        return result;
    }

    void sumDiagonal()
    {
        int main = 0;
        int secondary = 0;
        int dim = this->getSize();

        for (int i = 0; i < dim; i++)
        {
            main += this->matrix.at(i).at(i);
            secondary += this->matrix.at(i).at(dim-1-i);
        }

        std::cout << "\nMain Diagonal Sum: " << main;
        std::cout << "\nSecondary Diagonal Sum: " << secondary<<"\n";
    }

};

void run(Matrix A, Matrix B)
{
    //printing matricies
    std::cout << "Matrix A: \n";
    A.printMatrix();
    std::cout << "\nMatrix B: \n";
    B.printMatrix();

    //adding matrices
    Matrix sum = A + B;
    std::cout << "\nA + B: \n";
    sum.printMatrix();

    //multiplying matricies
    Matrix product = A * B;
    std::cout << "\nA * B: \n";
    product.printMatrix();

    //finding diagonals
    std::cout<< "\nDiagonal sums for Matrix A:";
    A.sumDiagonal();


}

int main()
{
    Matrix a("input-1.txt", 1);
    Matrix b("input-1.txt", 0);

    if (a.getSize() > 0 && b.getSize() > 0) //checks that matrix was created properly
    {
        run(a,b);
    }

    return 0;
}