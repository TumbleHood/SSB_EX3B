/*  -------------------------------------------------------
    | Guy Gur-Arieh  -  System Software B  -  Exercise 3B |
    -------------------------------------------------------  */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace zich{
    class Matrix{
        public:
            vector<double> _values;
            unsigned int _columns;
            unsigned int _rows;

            Matrix(const vector<double>& values, const int rows, const int columns);

            Matrix operator+() const; //unaric plus
            Matrix operator-() const; //uaric minus

            Matrix& operator++(); //prefix ++
            Matrix& operator--(); //prefix --

            Matrix operator++(int); //postfix ++
            Matrix operator--(int); //postfix --

            Matrix operator+(const double) const; //Matrix + number
            Matrix operator-(const double) const; //Matrix - number
            Matrix operator*(const double) const; //Matrix * number

            Matrix operator+(const Matrix&) const; //Matrix + Matrix
            Matrix operator-(const Matrix&) const; //Matrix - Matrix
            Matrix operator*(const Matrix&) const; //Matrix * Matrix

            Matrix& operator+=(const double); //Matrix += number
            Matrix& operator-=(const double); //Matrix -= number
            Matrix& operator*=(const double); //Matrix *= number

            Matrix& operator+=(const Matrix&); //Matrix += Matrix
            Matrix& operator-=(const Matrix&); //Matrix -= Matrix
            Matrix& operator*=(const Matrix&); //Matrix *= Matrix

            Matrix& operator=(const Matrix&); //Matrix <- Other Matrix

            bool operator==(const Matrix&) const; //Matrix == Matrix ?
            bool operator!=(const Matrix&) const; //Matrix != Matrix ?
            bool operator>(const Matrix&) const; //Matrix > Matrix ? (sum of values)
            bool operator<(const Matrix&) const; //Matrix < Matrix ? (sum of values)
            bool operator>=(const Matrix&) const; //Matrix >= Matrix ? (sum of values or ==)
            bool operator<=(const Matrix&) const; //MAtrix <= Matrix ? (sum of values or ==)

            void same_size(const Matrix&) const; //simple inner function to check if 2 matrices are the same size
            //(throws an exception if otherwise)
            
            friend ostream& operator<<(ostream&, const Matrix&); //cout << Matrix
            friend istream& operator>>(istream&, Matrix&); //cin>> Matrix

            friend Matrix operator+(const double, Matrix&); //number + Matrix
            friend Matrix operator-(const double, Matrix&); //number - Matrix
            friend Matrix operator*(const double, Matrix&); //number * Matirx

            friend double sum(const Matrix&); //simple inner function to calculate sum of values
    };
}