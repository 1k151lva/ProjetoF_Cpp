#include "Matrix.h" // Inclua o seu arquivo de cabe�alho
#include <iostream>

int main() {
    
    Matriz<int> A(2, 3, 5);
    Matriz<int> B = { {1, 2, 3}, {4, 5, 6} };
    Matriz<int> C = A + B;
    Matriz<int> D = C * 2;
    Matriz<int> E = 10 + D;

    std::cout << "Matriz E:\n" << A;
    std::cout << "Matriz E:\n" << B;
    std::cout << "Matriz E:\n" << C;
    std::cout << "Matriz E:\n" << D;
    std::cout << "Matriz E:\n" << E;

    return 0;
}