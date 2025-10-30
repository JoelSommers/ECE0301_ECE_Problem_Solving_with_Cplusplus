#ifndef _SOLVER_HPP
#define _SOLVER_HPP

#include <cstdlib>
#include <iostream>
#include <cmath> //to use pow function
#include <fstream>//for file reading (bonus)
#include <string>//for string in bonus

#include "constants.hpp"

void matrix_vector_product(const double matrix[][CAP],
                           const double vector[],
                           double result[], const int dim)
{
    // loop over rows of matrix
    for (int i = 0; i < dim; i++)
    {
        // initialize product element for this row
        result[i] = 0;
        // loop over columns of matrix
        for (int j = 0; j < dim; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void submatrix(const double matrix[][CAP],
               int row, int col,
               double result[][CAP], const int dim)
{
    //intialize variables for interating the result matrix
    int result_i=0;
    int result_j=0;

    //loop through the matrix
    for (int i=0;i<dim;i++){
        // use if-statement to break out of loop if the last row needs removed
        if (i == row && row != dim-1)
        {
            i++;
        }
        else if (i == row && row == dim-1)
        {
            break;
        }

        for (int j = 0; j < dim; j++)
        {
            //use if-statement to break out of loop if the last col needs removed
            if (j==col&&col!=dim-1){
                j++;
            }
            else if (j==col&&col==dim-1){
                break;
            }
            
            //copy the array to result
            result[result_i][result_j]=matrix[i][j];
            result_j++;
        }
        result_j=0;
        result_i++;
    }
}

double determinant(const double matrix[][CAP], const int dim)
{
    double det=0;
    // if dim=1 then determinant = scalar
    if (dim==1){
        det=matrix[0][0];
    }

    //if dim>1
    if (dim>1){
        for (int i=0;i<dim;i++){
            double sub[dim-1][CAP];
            submatrix(matrix,0,i, sub, dim);
            det += pow(-1, i) * matrix[0][i] * determinant(sub,dim-1);
        }
    }

    return det;
}

void replace_column(const double matrix[][CAP],
                    int col, const double vector[],
                    double result[][CAP], const int dim)
{
    //loop through the matrix and replace the col provided with the vector(b)
    for (int i=0;i<dim;i++){
        for (int j=0;j<dim;j++){
            //if j=col then we replace the current element with the element in the same row in the vector(b)
            if (j==col){
                result[i][j]=vector[i];
            }
            else
            {
                result[i][j] = matrix[i][j];
            }
        }
    }
}

void cramers_rule(const double matrix[][CAP],
                  const double vector[],
                  double result[], const int dim)
{
    //find the determinant of the matrix
    double det=determinant(matrix,dim);
    
    //intitalize columns matrix
    double column_matrix[dim][CAP];
    
    //replace column i with the vector(b) and find det of that matrix. 
    //Divide this determinant by the determinant of the matrix and assign this value to the corresponding row i in the result vector.
    for (int i=0;i<dim;i++){
        replace_column(matrix,i,vector,column_matrix,dim);
        result[i]=determinant(column_matrix,dim)/det;
    }
}

int parse_file_input(std::string filename,
                     double matrix[][CAP],
                     double vector[])
{
    //open file
    std::ifstream input_file(filename);

    //string for line of input
    std::string line;

    //intitalize variable for dimension
    int dim;

    // intitalize flag variables
    bool A_start_flag=false;
    bool b_start_flag=false;

    //intitialize int count values
    int b_i=0;
    int A_i=0;

    while (getline(input_file, line))
    {

        if (line[0] == 'N')
        {
            //find equals
            int equals=line.find("=");

            //create substring for dim
            std::string sub_dim=line.substr(equals+2,line.length());

            //convert substring to int
            dim = std::stoi(sub_dim);
            std::cout<<dim;
            continue;
        }

        if (line[0] == 'A')
        {
            //flag that we are dealing with the A vector
            A_start_flag=true;
            b_start_flag=false;
            continue;
        }

        if ((line[0] != 'N') && (line[0] != 'A') && (line[0] != 'b') && (A_start_flag) && (!b_start_flag))
        {
            // pass line data to row of A matrix if and only if A starts, b has not started yet
        

            //initialize substring that will be used in the for loop
            std::string sub1;

            for (int j = 0; j < dim; j++)
            {
                // find space
                int space = line.find(" ");

                // return -1 if j=dim-1 and the space can be found (which tells us there is another element thus there dimensions are off)
                if (j == dim - 1 && space != std::string::npos)
                {
                    return -1;
                }

                //return -1 if they are not on the last element and the space can't be found
                else if (j<dim-1&&space==std::string::npos){
                    return -1;
                }

                //handling the last element 
                else if (space==std::string::npos){
                    sub1=line.substr(0,line.length());
                    matrix[A_i][j]=std::stod(sub1);
                    continue;
                }

                //create substring from the start to the space
                sub1 = line.substr(0, space);

                matrix[A_i][j]=std::stod(sub1);

                // split the line into a substring after the space and set line equal to it
                line=line.substr(space + 1, line.length());
                
            }

            //increment A_i to indicate how many rows are in the matrix provided
            A_i++;
        }

        if (line[0] == 'b')
        {
            // flag that we are dealing with the b vector
            b_start_flag = true;
            A_start_flag = false;
            continue;
        }

        if ((line[0] != 'N') && (line[0] != 'A') && (line[0] != 'b') && (b_start_flag))
        {
            // pass line data to b vector if and only if b starts

            // check if there is an additional column
            if (line.find(" ") != std::string::npos)
            {
                return -1;
            }
            
            vector[b_i]=std::stod(line);
            b_i++;
        }
    }
    //return -1 if b_i is not equal to dim
    if (b_i != dim){
        return -1;
    }

    // return -1 if A_i is not equal to dim 
    if (A_i != dim)
    {
        return -1;
    }
        return dim;
}

#endif