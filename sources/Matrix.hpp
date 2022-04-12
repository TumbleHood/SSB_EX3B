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
            Matrix(const Matrix& matrix);

            Matrix operator+() const;
            Matrix operator-() const;

            Matrix& operator++();
            Matrix& operator--();

            Matrix operator++(int);
            Matrix operator--(int);

            Matrix operator+(const double) const;
            Matrix operator-(const double) const;
            Matrix operator*(const double) const;

            Matrix operator+(const Matrix&) const;
            Matrix operator-(const Matrix&) const;
            Matrix operator*(const Matrix&) const;

            Matrix& operator+=(const double);
            Matrix& operator-=(const double);
            Matrix& operator*=(const double);

            Matrix& operator+=(const Matrix&);
            Matrix& operator-=(const Matrix&);
            Matrix& operator*=(const Matrix&);

            Matrix& operator=(const Matrix&);

            bool operator==(const Matrix&) const;
            bool operator!=(const Matrix&) const;
            bool operator>(const Matrix&) const;
            bool operator<(const Matrix&) const;
            bool operator>=(const Matrix&) const;
            bool operator<=(const Matrix&) const;

            void same_size(const Matrix&) const;
            
            friend ostream& operator<<(ostream&, const Matrix&);
            friend istream& operator>>(istream&, Matrix&);

            friend Matrix operator+(const double, Matrix&);
            friend Matrix operator-(const double, Matrix&);
            friend Matrix operator*(const double, Matrix&);

            friend double sum(const Matrix&);
    };
}