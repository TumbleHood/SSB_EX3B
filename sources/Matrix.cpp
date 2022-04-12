#include "Matrix.hpp"
#include <stdexcept>

using namespace std;
using namespace zich;

Matrix::Matrix(const vector<double>& values, const int rows, const int columns){
    if (rows <= 0 || columns <= 0){
        throw invalid_argument("Matrix width and height must be positive!");
    }
    if (rows * columns != values.size()){
        throw invalid_argument("Width and height do not match the size!");
    }
    _values = vector<double>(values);
    _rows = (unsigned int)rows;
    _columns = (unsigned int)columns;
}

Matrix::Matrix(const Matrix& matrix){
    _values = vector<double>(matrix._values);
    _rows = matrix._rows;
    _columns = matrix._columns;
}

double zich::sum(const Matrix& matrix){
    double sum = 0;
    for (unsigned int i = 0; i < matrix._values.size(); i++){
        sum += matrix._values.at(i);
    }
    return sum;
}

void Matrix::same_size(const Matrix& matrix) const{
    if (_rows != matrix._rows || _columns != matrix._columns){
        throw invalid_argument("Matrices are not the same size!");
    }
}

Matrix Matrix::operator+() const{
    return *this;
}

Matrix Matrix::operator-() const{
    Matrix minus_matrix = Matrix(*this);
    for (unsigned int i = 0; i < minus_matrix._values.size(); i++){
        minus_matrix._values.at(i) *= -1;
    }
    return minus_matrix;
}

Matrix& Matrix::operator++(){
    *this += 1;
    return *this;
} 

Matrix& Matrix::operator--(){
    *this -= 1;
    return *this;
}

Matrix Matrix::operator++(int){
    Matrix temp_matrix = Matrix(*this);
    ++*this;
    return temp_matrix;
}

Matrix Matrix::operator--(int){
    Matrix temp_matrix = Matrix(*this);
    --*this;
    return temp_matrix;
}

Matrix Matrix::operator+(const double num) const{
    Matrix temp_matrix = Matrix(*this);
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) += num;
    }
    return temp_matrix;
}

Matrix Matrix::operator-(const double num) const{
    Matrix temp_matrix = Matrix(*this);
    temp_matrix += -num;
    return temp_matrix;
}

Matrix Matrix::operator*(const double num) const{
    Matrix temp_matrix = Matrix(*this);
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) *= num;
    }
    return temp_matrix;
}

Matrix Matrix::operator+(const Matrix& matrix) const{
    same_size(matrix);
    Matrix temp_matrix = Matrix(*this);
    for (unsigned int i = 0; i < temp_matrix._values.size(); i++){
        temp_matrix._values.at(i) += matrix._values.at(i);
    }
    return temp_matrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const{
    Matrix temp_matrix = Matrix(*this);
    temp_matrix = temp_matrix + -matrix;
    return temp_matrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const{
    if (_columns != matrix._rows){
        throw invalid_argument("The width of the first matrix must match the height of the second matrix!");
    }
    
    unsigned int new_rows = _rows;
    unsigned int new_columns = matrix._columns;
    vector<double> new_values(new_rows * new_columns, 0);

    for (unsigned int i = 0; i < new_rows; i++){
        for (unsigned int j = 0; j < new_columns; j++){
            for (unsigned int k = 0; k < _columns; k++){
                new_values.at(i * new_columns + j) += 
                _values.at(i * _columns + k) * matrix._values.at(k * matrix._columns + j);
            }
        }
    }

    return Matrix(new_values, (int)new_rows, (int)new_columns);
}

Matrix& Matrix::operator+=(const double num){
    *this = *this + num;
    return *this;
}

Matrix& Matrix::operator-=(const double num){
    *this = *this - num;
    return *this;
}

Matrix& Matrix::operator*=(const double num){
    *this = *this * num;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix){
    *this = *this + matrix;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix){
    *this = *this - matrix;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix){
    *this = *this * matrix;
    return *this;
}

Matrix& Matrix::operator=(const Matrix& matrix){
    _values = vector<double>(matrix._values);
    _rows = matrix._rows;
    _columns = matrix._columns;
    return *this;
}

bool Matrix::operator==(const Matrix& matrix) const{
    same_size(matrix);
    for (unsigned int i = 0; i < _values.size(); i++){
        if (_values.at(i) != matrix._values.at(i)){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& matrix) const{
    same_size(matrix);
    return !(*this == matrix);
}

bool Matrix::operator>(const Matrix& matrix) const{
    same_size(matrix);
    return sum(*this) > sum(matrix);
}

bool Matrix::operator<(const Matrix& matrix) const{
    same_size(matrix);
    return sum(*this) < sum(matrix);
}

bool Matrix::operator>=(const Matrix& matrix) const{
    same_size(matrix);
    return sum(*this) > sum(matrix) || *this == matrix;
}

bool Matrix::operator<=(const Matrix& matrix) const{
    same_size(matrix);
    return sum(*this) < sum(matrix) || *this == matrix;
}

ostream& zich::operator<<(ostream& os, const Matrix& matrix){
    for (unsigned int i = 0; i < matrix._rows; i++){
        os << "[";
        for (unsigned int j = 0; j < matrix._columns; j++){
            os << matrix._values.at(i * matrix._columns + j);
            if (j < matrix._columns - 1){
                os << " ";
            }
        }
        os << "]";
        if (i < matrix._rows - 1){
            os << "\n";
        }
    }
    return os;
}

istream& zich::operator>>(istream& is, Matrix& matrix){
    string s;
    getline(is, s);

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
    return matrix + num;
}

Matrix zich::operator-(const double num, Matrix& matrix){
    return -(matrix - num);
}

Matrix zich::operator*(const double num, Matrix& matrix){
    return matrix * num;
}