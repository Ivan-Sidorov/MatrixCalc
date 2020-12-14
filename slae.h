#ifndef SLAE_H
#define SLAE_H

#include <iostream>
#include "matrix.h"
#include "squarematrix.h"

template <class T> class Slae {
private:
    int amEq, amVar;
    Matrix<T> a, b, x;
    bool isSolved;
    int rang;
    int* newOrder;

public:
    Slae(int m, int n) : a(m, n), b(1, m), x(1, n) {
        amEq = m;
        amVar = n;
        newOrder = new int [amVar];
        for (int i = 0; i < amVar; i++)
            newOrder[i] = i;
    }
    void solve() {
        if (amEq == amVar) {
            std::cout << "1 - Kramer's method" << std::endl;
            std::cout << "2 - Using inverse matrix" << std::endl;
            int i;
            std::cin >> i;
            if (i == 1) {
                std::string res = kramer();
                if (res == "Success")
                    kramer();
                else {
                    std::cout << "It is impossible to use Kramer's method" << std::endl;
                    std::cout << "Gauss' method:" << std::endl;
                    gauss();
                }
            }
            else {
                std::string res2 = inverseSolution();
                if (res2 == "Success")
                    inverseSolution();
                else {
                    std::cout << "It is impossible to use inverse matrix's method" << std::endl;
                    std::cout << "Gauss' method:" << std::endl;
                    gauss();
                }
            }
        }
        else {
            std::cout << "Gauss' method:" << std::endl;
            gauss();
        }
    }
    void gauss() {
        Matrix<T> A(a);
        Matrix<T> B(b);
        int zeroClmns = 0;
        for (int i = 0; i < amEq; i++) {
            if (A[i][i] != 0) {
                for (int i2 = 0; i2 < amEq; i2++) {
                    if (i2 == i)
                        continue;
                    T d = A[i2][i] / A[i][i];
                    for (int j = i; j < amVar; j++)
                        A[i2][j] = A[i2][j] - d * A[i][j];
                    B[0][i2] = B[0][i2] - d * B[0][i];
                }
                for (int j = i + 1; j < amVar; j++)
                    A[i][j] = A[i][j] / A[i][i];
                B[0][i] = B[0][i] / A[i][i];
                A[i][i] = 1;
            }
            else {
                int k;
                for (k = i + 1; k < amEq; k++)
                    if (A[k][i] != 0)
                        break;
                if (k == amEq) {
                    if (i == (amVar - 1 - zeroClmns)) {
                        zeroClmns++;
                        break;
                    }
                    for (int j = 0; j < amEq; j++) {
                        T tmp = A[j][i];
                        A[j][i] = A[j][amVar - zeroClmns - 1];
                        A[j][amVar - zeroClmns - 1] = tmp;
                    }
                    int tmp = newOrder[i];
                    newOrder[i] = newOrder[amVar - zeroClmns - 1];
                    newOrder[amVar - zeroClmns - 1] = tmp;
                    zeroClmns++;
                    i--;
                }
                else {
                    T* tmp = A[i];
                    A.setRowVect(i, A[k]);
                    A.setRowVect(k, tmp);
                    T tmp2 = B[0][i];
                    B[0][i] = B[0][k];
                    B[0][k] = tmp2;
                    i--;
                }
            }
        }
        if (amEq < (amVar - zeroClmns))
            rang = amEq;
        else
            rang = amVar - zeroClmns;
        for (int i = rang; i < amEq; i++)
            if (B[0][i] != 0) {
                isSolved = false;
                return;
            }
        Matrix<T> res(rang, 1 + amVar - rang);
        for (int i = 0; i < rang; i++) {
            res[i][0] = B[0][i];
            for (int j = rang; j < amVar; j++)
                res[i][j - rang + 1] = -A[i][j];
        }
        x = res;
        isSolved = true;
    }
    std::string kramer() {
        //   if (amVar != amEq)
        SquareMatrix<T> aSquare(a);
        SquareMatrix<T> bSquare(b);
        T d = aSquare.det();
        if (d == 0) {
            isSolved = false;
            return "Error";
        }
        else {
            rang = amVar;
            for (int j = 0; j < amEq; j++) {
                for (int i = 0; i < amEq; i++)
                    aSquare[i][j] = bSquare[0][i];
                x[0][j] = aSquare.det() / d;
                for (int i = 0; i < amEq; i++)
                    aSquare[i][j] = a[i][j];
            }
            isSolved = true;
            return "Success";
        }
    }
    std::string inverseSolution() {
        //    if (amVar != amEq)
        SquareMatrix<T> aSquare = a;
        std::string res = aSquare.inverse();
        if (res == "Error") {
            return "Error";
            isSolved = false;
        }
        SquareMatrix<T> bSquare = b;
        bSquare.transpose();
        Matrix<T> sol = aSquare * bSquare;
        x = sol;
        x.transpose();
        rang = amEq;
        isSolved = true;
        return "Success";
    }
    void printSolution(std::ostream& out) {
        if (!isSolved) {
            out << "The system is incompatible" << std::endl;
            return;
        }
        if (rang < amVar) {
            for (int i = 0; i < rang; i++) {
                out << "x" << (newOrder[i] + 1) << " = " << x[i][0];
                for (int j = 1; j <= amVar - rang; j++) {
                    if (x[i][j] == 0)
                        continue;
                    if (x[i][j] > 0)
                        out << "+" << x[i][j] << "*x" << (newOrder[rang + j - 1] + 1);
                    else {
                        out << x[i][j] << "*x" << (newOrder[rang + j - 1] + 1);
                    }
                }
                out << std::endl;
            }
        }
        else {
            out << "(";
            for (int i = 0; i < amVar - 1; i++)
                out << x[0][i] << ", ";
            out << x[0][amVar - 1] << ")" << std::endl;
        }
    }
    template <class T2> friend std::ostream& operator<<(std::ostream& out, Slae<T2>& obj) {
        for (int i = 0; i < obj.amEq; i++) {
            for (int j = 0; j < obj.amVar; j++)
                out << obj.a[i][j] << "\t";
            out << "\t" << obj.b[0][i] << std::endl;
        }
        out << "SLAE solution:" << std::endl;
        obj.printSolution(out);
        return out;
    }
    template <class T2> friend std::istream& operator>>(std::istream& in, Slae<T2>& obj) {
        std::cout << "Coefficient matrix:" << std::endl;
        in >> obj.a;
        std::cout << "Free members matrix:" << std::endl;
        in >> obj.b;
        return in;
    }
};

#endif // SLAE_H
