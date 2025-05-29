
#include <iostream>
#include "Matrix.hpp"

int main() {
    Matrix<int> A = {{1, 2}, {3, 4}};
    Matrix<int> B = {{5, 6}, {7, 8}};

    Matrix<int> C = A + B;
    Matrix<int> D = A * B.transpose();

    std::cout << "C = A + B:\n" << C;
    std::cout << "D = A * B^T:\n" << D;

    return 0;
}
