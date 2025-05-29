#include "Matrix.h" // Inclua o seu arquivo de cabeçalho
#include <iostream>

int main() {
    
    Matrix<int> A(2, 3, 5);
    Matrix<int> B = { {1, 2, 3}, {4, 5, 6} };
    Matrix<int> C = A + B;
    Matrix<int> D = C * 2;
    Matrix<int> E = 10 + D;

    std::cout << "Matriz E:\n" << A;
    std::cout << "Matriz E:\n" << B;
    std::cout << "Matriz E:\n" << C;
    std::cout << "Matriz E:\n" << D;
    std::cout << "Matriz E:\n" << E;

    return 0;
}