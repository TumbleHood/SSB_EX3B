/*  -------------------------------------------------------
    | Guy Gur-Arieh  -  System Software B  -  Exercise 3B |
    -------------------------------------------------------  */

#include "Matrix.hpp"
#include <stdexcept>

using namespace std;
using namespace zich;

Matrix::Matrix(const vector<double>& values, const int rows, const int columns){
    //Checks if the given rows and columns values are positive
    if (rows <= 0 || columns <= 0){
        throw invalid_argument("Matrix rows and columns must be positive!");
    }
    //Checks if the given rows and columns values match the given vector's size
    if (rows * columns != values.size()){
        throw invalid_argument("(Rows x Columns) do not match the size!");
    }
    _values = vector<double>(values); //copies the values
    _rows = (unsigned int)rows; //convert to unsigned int
    _columns = (unsigned int)columns; //convert to unsigned int
}

double zich::sum(const Matrix& matrix){
    //Implementation of the sum function -  calculates the sum of values
    double sum = 0;
    for (unsigned int i = 0; i < matrix._values.size(); i++){
        sum += matrix._values.at(i);
    }
    return sum;
}

void Matrix::same_size(const Matrix& matrix) const{
    //Compares the dimensions of the 2 matrices and throws an exeption if they are not equal
    if (_rows != matrix._rows || _columns != matrix._columns){
        throw invalid_argument("Matrices are not the same size!");
    }
}

Matrix Matrix::operator+() const{
    //Unaric plus has no meaning
    return *this;
}

Matrix Matrix::operator-() const{
    //Unaric minus - multiply every value by (-1). since we are not changing (this) we create a new matrix
    Matrix minus_matrix = Matrix(*this);
    for (unsigned int i = 0; i < minus_matrix._values.size(); i++){
        minus_matrix._values.at(i) *= -1;
    }
    return minus_matrix;
}

Matrix& Matrix::operator++(){
    //Implementation of the prefix ++ operator with the += operator
    *this += 1;
    return *this;
} 

Matrix& Matrix::operator--(){
    //Implementation of the prefix -- operator with the -= operator
    *this -= 1;
    return *this;
}

Matrix Matrix::operator++(int){
    //Postfix ++ - create a copy of the original matrix, increase the matrix by 1, return the copy
    Matrix temp_matrix = *this;
    *this += 1;
    return temp_matrix;
}

Matrix Matrix::operator--(int){
    //Postfix ++ - create a copy of the original matrix, increase the matrix by 1, return the copy
    Matrix temp_matrix = *this;
    *this -= 1;
    return temp_matrix;
}

Matrix Matrix::operator+(const double num) const{
    //Matrix + number  -  add the number to every values of the matrix
    Matrix temp_matrix = *this;
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) += num;
    }
    return temp_matrix;
}

Matrix Matrix::operator-(const double num) const{
    //Matrix - number == Matrix + -number
    Matrix temp_matrix = *this;
    temp_matrix += -num;
    return temp_matrix;
}

Matrix Matrix::operator*(const double num) const{
    //Matrix * number  -  multiply every values of the matrix by the number
    Matrix temp_matrix = *this;
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) *= num;
    }
    return temp_matrix;
}

Matrix Matrix::operator+(const Matrix& matrix) const{
    //Matrix + Matrix  -  new_matrix[i, j] = first_matrix[i, j] + second_matrix[i, j]
    same_size(matrix); //works only if they are the same size
    Matrix temp_matrix = *this;
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) += matrix._values.at(i);
    }
    return temp_matrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const{
    //Matrix - Matrix == Matrix + -Matrix
    Matrix temp_matrix = *this;
    temp_matrix = temp_matrix + -matrix;
    return temp_matrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const{
    //Matrix * Matrix  -  multiplication of matrices
    if (_columns != matrix._rows){ //works only if the columns of the first matrix equals the rows of the second
        throw invalid_argument("The width of the first matrix must match the height of the second matrix!");
    }
    
    unsigned int new_rows = _rows;
    unsigned int new_columns = matrix._columns;
    vector<double> new_values(new_rows * new_columns, 0); //create new vector

    for (unsigned int i = 0; i < new_rows; i++){ //go over the rows
        for (unsigned int j = 0; j < new_columns; j++){ //go over the columns
            for (unsigned int k = 0; k < _columns; k++){ //go over the columns of the original matrices
                new_values.at(i * new_columns + j) += 
                _values.at(i * _columns + k) * matrix._values.at(k * matrix._columns + j);
                //since the implementation of the matrix class is a 1D array,
                //we use the formula: Matrix[i, j] = 1D_Matrix[i*columns + j];
            }
        }
    }

    return Matrix(new_values, (int)new_rows, (int)new_columns); //return the new matrix
}

Matrix& Matrix::operator+=(const double num){
    //Matrix += num -> Matrix = Matrix + num
    *this = *this + num;
    return *this;
}

Matrix& Matrix::operator-=(const double num){
    //Matrix -= num -> Matrix = Matrix - num
    *this = *this - num;
    return *this;
}

Matrix& Matrix::operator*=(const double num){
    //Matrix *= num -> Matrix = Matrix * num
    *this = *this * num;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix){
    //Matrix_a += Matrix_b -> Matrix_a = Matrix_a + Matrix_b
    *this = *this + matrix;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix){
    //Matrix_a -= Matrix_b -> Matrix_a = Matrix_a - Matrix_b
    *this = *this - matrix;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix){
    //Matrix_a *= Matrix_b -> Matrix_a = Matrix_a * Matrix_b
    *this = *this * matrix;
    return *this;
}

Matrix& Matrix::operator=(const Matrix& matrix){
    //Simple copy constructor
    _values = vector<double>(matrix._values);
    _rows = matrix._rows;
    _columns = matrix._columns;
    return *this;
}

bool Matrix::operator==(const Matrix& matrix) const{
    //Checks if the values of the matrices match
    same_size(matrix); //works only if they are the smae size
    for (unsigned int i = 0; i < _values.size(); i++){
        if (_values.at(i) != matrix._values.at(i)){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& matrix) const{
    //a != b -> !(a == b)
    same_size(matrix);
    return !(*this == matrix);
}

bool Matrix::operator>(const Matrix& matrix) const{
    //Checks if the sum of the first matrix is greater than the sum of the second
    same_size(matrix);
    return sum(*this) > sum(matrix);
}

bool Matrix::operator<(const Matrix& matrix) const{
    //Checks if the sum of the first matrix is less than the sum of the second
    same_size(matrix);
    return sum(*this) < sum(matrix);
}

bool Matrix::operator>=(const Matrix& matrix) const{
    //a >= b -> a > b || a == b
    same_size(matrix);
    return sum(*this) > sum(matrix) || *this == matrix;
}

bool Matrix::operator<=(const Matrix& matrix) const{
    //a <= b -> a < b || a == b
    same_size(matrix);
    return sum(*this) < sum(matrix) || *this == matrix;
}

ostream& zich::operator<<(ostream& os, const Matrix& matrix){
    //Prints the matrix
    for (unsigned int i = 0; i < matrix._rows; i++){
        os << "["; //start each row with "["
        for (unsigned int j = 0; j < matrix._columns; j++){
            os << matrix._values.at(i * matrix._columns + j); //add the value
            if (j < matrix._columns - 1){ //if this is not the last value in the row we add a blank space
                os << " ";
            }
        }
        os << "]"; //we finished a row - add "]"
        if (i < matrix._rows - 1){ //if this is not the last columns we add a new line character
            os << "\n";
        }
    }
    return os;
}

istream& zich::operator>>(istream& is, Matrix& matrix){
    //Take input from the user and create a matrix
    string s;
    getline(is, s); //get the intire input

    unsigned int columns = 1;
    unsigned int rows = 1;
    unsigned int current_columns = 0;

    for (unsigned int i = 0; i < s.length()-1; i++){
        if (s.at(i) == ' '){
            columns++;
        }
        if (s.at(i) == '['){
            if (s.at(i+1) == '[' || s.at(i+1) == ' ' || s.at(i+1) == ']' || s.at(i+1) == ',' || s.at(i+1) == '\n'){
                throw invalid_argument("Must have a number after \"[\"!");
            }
        }
        if (s.at(i) == ']' && i < s.length() && s.at(i+1) != ','){
            throw invalid_argument("Must have a comma after \"]\"!");
        }
        if (s.at(i) == ','){
            if (s.at(++i) != ' '){
                throw invalid_argument("Must have a space after comma!");
            }
            rows++;
            if (current_columns == 0){
                current_columns = columns;
            }
            else if (columns != current_columns){
                throw invalid_argument("Number of values per row is inconsistent!");
            }
            columns = 1;
        }
    }

    vector<double> values(rows * columns, 0);

    unsigned int i = 0;
    string word;
    for (unsigned int x = 0; x < s.length(); x++){
        if (s.at(x) == ' ' || s.at(x) == '[' || s.at(x) == ']' || s.at(x) == ',' || s.at(x) == '\n'){
            try{
                values.at(i++) = stod(word);
            }
            catch (invalid_argument e){
                word = "";
            }
            word = "";
        }
        else{
            word += s.at(x);
        }
    }

    matrix = Matrix(values, (int)rows, (int)columns);

    return is;
}

Matrix zich::operator+(const double num, Matrix& matrix){
    //number + Matrix == Matrix + number
    return matrix + num;
}

Matrix zich::operator-(const double num, Matrix& matrix){
    //number - Matrix == -(Matrix - number)
    return -(matrix - num);
}

Matrix zich::operator*(const double num, Matrix& matrix){
    //number * Matrix = Matrix * number
    return matrix * num;
}