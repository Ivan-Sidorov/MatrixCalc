#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <class T> class Matrix {
protected:
    int nRow, mCol;
    T** matr;
public:
    Matrix() {
        this->nRow = 0;
        this->mCol = 0;
        this->matr = nullptr;
    }
    Matrix(int n, int m) {
        this->nRow = n;
        this->mCol = m;
        this->matr = new T* [nRow];
        for (int i = 0; i < nRow; i++)
            matr[i] = new T [n];
        for (int i = 0; i < nRow; i++)
            for( int j = 0; j < mCol; j++)
                matr[i][j] = 0;
    }
    Matrix(const Matrix& obj) {
        this->nRow = obj.nRow;
        this->mCol = obj.mCol;
        if (obj.matr == nullptr) {
            this->matr = nullptr;
            return;
        }
        this->matr = new T* [nRow];
        for (int i = 0; i < nRow; i++)
            matr[i] = new T [mCol];
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < mCol; j++)
                matr[i][j] = obj.matr[i][j];
    }
    ~Matrix() {
        if (matr != nullptr) {
            for (int i = 0; i < nRow; i++)
                delete [] matr[i];
            delete [] matr;
        }
    }
    std::pair<int, int> size() {
        std::pair<int, int> size;
        size.first = nRow;
        size.second = mCol;

        return size;
    }
    void setRow(int numRow) {
        this->nRow = numRow;
    }
    void setCol(int numCol) {
        this->mCol = numCol;
    }
    void setRowVect(int i, T* row) {
        matr[i] = row;
    }
    void transpose() {
        Matrix tmpMatr(mCol, nRow);
        for (int i = 0; i < nRow; i++)
            for( int j = 0; j < mCol; j++)
                tmpMatr.matr[j][i] = matr[i][j];
        *this = tmpMatr;
    }
    virtual void printSize() {
        std::cout << "Rows -- " << nRow << " Columns -- " << mCol << std::endl;
    }
    T* operator[] (int row) {
        return matr[row];
    }
    Matrix<T>& operator=(const Matrix<T>& obj) {
        if (nRow != obj.nRow || mCol != obj.mCol) {
            for (int i = 0; i < nRow; i++)
                delete [] matr[i];
            delete [] matr;
            this->nRow = obj.nRow;
            this->mCol = obj.mCol;
            this->matr = new T* [nRow];
            for (int i = 0; i < nRow; i++)
                    matr[i] = new T [mCol];
        }
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < mCol; j++)
                matr[i][j] = obj.matr[i][j];

        return *this;
    }
    Matrix<T> operator*(T num) { // mult by number (right)
        Matrix tmpMatr(nRow, mCol);
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < mCol; j++)
                tmpMatr.matr[i][j] = matr[i][j] * num;

        return tmpMatr;
    }
    template <class T2> friend Matrix<T> operator*(T num, const Matrix<T2>& obj) { // (left)
        Matrix tmpMatr(obj.nRow, obj.mCol);
        for (int i = 0; i < obj.nRow; i++)
            for (int j = 0; j < obj.mCol; j++)
                tmpMatr.matr[i][j] = tmpMatr.matr[i][j] * num;

        return tmpMatr;
    }
    Matrix<T> operator*(const Matrix<T>& obj) { // mult by matrix
        Matrix resMatr(nRow, obj.mCol);
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < obj.mCol; j++)
                for (int k = 0; k < mCol; k++)
                    resMatr.matr[i][j] += matr[i][k] * obj.matr[k][j];

        return resMatr;
    }
    Matrix<T> operator+(const Matrix<T>& obj) {
        Matrix resMatr(nRow, mCol);
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < mCol; j++)
                resMatr.matr[i][j] = matr[i][j] + obj.matr[i][j];

        return resMatr;
    }
    Matrix<T> operator-(const Matrix<T>& obj) {
        Matrix resMatr(nRow, mCol);
        for (int i = 0; i < nRow; i++)
            for (int j = 0; j < mCol; j++)
                resMatr.matr[i][j] = matr[i][j] - obj.matr[i][j];

        return resMatr;
    }
    template <class T2> friend std::ostream& operator<<(std::ostream& out, const Matrix<T2>& obj) {
        if (obj.matr != nullptr) {
            out << "Matrix:" << std::endl;
            for (int i = 0; i < obj.nRow; i++) {
                for (int j = 0; j < obj.mCol; j++)
                    out << obj.matr[i][j] << " ";
                out << std::endl;
            }
        }
        else
            out << "Empty matrix" << std::endl;
        return out;
    }
    template <class T2> friend std::istream& operator>>(std::istream& in, const Matrix<T2>& obj) {
        if (obj.matr != nullptr) {
            for (int i = 0; i < obj.nRow; i++)
                for (int j = 0; j < obj.mCol; j++)
                    in >> obj.matr[i][j];
        }
        return in;
    }
};

#endif // MATRIX_H
