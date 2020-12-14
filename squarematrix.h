#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"

template <class T> class SquareMatrix : public Matrix<T> {
public:
    using Matrix<T>::matr;
    SquareMatrix(int size) : Matrix<T>(size, size) {}
    SquareMatrix(const Matrix<T>& obj) : Matrix<T>(obj) {
//        this->nRow = obj.nRow;
//        this->mCol = obj.mCol;
//        if (obj.matr == nullptr) {
//            this->matr = nullptr;
//            return;
//        }
//        this->matr = new T* [this->nRow];
//        for (int i = 0; i < this->nRow; i++)
//            this->matr[i] = new T [this->mCol];
//        for (int i = 0; i < this->nRow; i++)
//            for (int j = 0; j < this->mCol; j++)
//                this->matr[i][j] = obj.matr[i][j];
    }
    std::string inverse() {
        SquareMatrix<T> resMatr(this->mCol);
        double d = det();
        if (d == 0)
            return "Error";
        //    if (det == 0)
        //SquareMatrix addMatr(mCol - 1);
        int sign;
        for (int i = 0; i < this->mCol; i++) {
            if (i % 2 == 0)
                sign = 1;
            else
                sign = -1;
            for (int j = 0; j < this->mCol; j++) {
                SquareMatrix addMatr = subMatr(i, j);
                resMatr[j][i] = (sign * addMatr.det()) / d;
                sign = -sign;
            }
        }
        //    for (int i = 0; i < nRow; i++)
        //        for (int j = 0; j < mCol; j++) {
        //            SquareMatrix tmpMatr = subMatr(i, j);
        //            addMatr.matr[i][j] = tmpMatr.det();
        //        }
        //    addMatr.transpose();
        //    for (int i = 0; i < nRow; i++)
        //        for(int j = 0; j < mCol; j++)
        //            resMatr.matr[i][j] = addMatr.matr[i][j] / d;

        *this = resMatr;

        return "Success";
    }
    T det() {
        T d = 0;
        if (this->nRow == 1)
            d = this->matr[0][0];
        else {
            SquareMatrix resMatr(this->nRow - 1);
            for (int j = 0; j < this->mCol; j++) {
                SquareMatrix tmpMatr = subMatr(0, j);
                resMatr = tmpMatr;
                if (j % 2 == 0)
                    d += resMatr.det() * this->matr[0][j];
                else
                    d -= resMatr.det() * this->matr[0][j];
            }
        }

        return d;
    }
    SquareMatrix<T> subMatr(int iDel, int jDel) {
        SquareMatrix resMatr(this->nRow - 1);
        for (int i = 0; i < iDel; i++) {
            for (int j = 0; j < jDel; j++)
                resMatr.matr[i][j] = this->matr[i][j];
            for (int j = jDel + 1; j < this->mCol; j++)
                resMatr.matr[i][j - 1] = this->matr[i][j];
        }
        for (int i = iDel + 1; i < this->nRow; i++) {
            for (int j = 0; j < jDel; j++)
                resMatr.matr[i - 1][j] = this->matr[i][j];
            for (int j = jDel + 1; j < this->mCol; j++)
                resMatr.matr[i - 1][j - 1] = this->matr[i][j];
        }

        return resMatr;
    }
    virtual void printSize() {
        std::cout << "Matrix is square" << std::endl;
        std::cout << "Size -- " << this->nRow << std::endl;
    }
    SquareMatrix<T>& operator=(const SquareMatrix<T>& obj) {
        Matrix<T>::operator=(obj);

        return *this;
    }
};

#endif // SQUAREMATRIX_H
