#include "matriz.h" // Inclua o seu arquivo de cabeçalho
#include <iostream>

int main() {
    try {
        // Exemplo de uso fornecido na imagem
        Matrix<int> A(2, 3, 5); // Matriz 2x3 preenchida com o valor 5
        std::cout << "Matriz A (2x3, valor 5):\n" << A << std::endl;

        Matrix<int> B = { {1, 2, 3}, {4, 5, 6} };
        std::cout << "Matriz B (initializer_list):\n" << B << std::endl;

        Matrix<int> C = A + B; // Soma de matrizes
        std::cout << "Matriz C = A + B:\n" << C << std::endl;

        Matrix<int> D = C * 2; // Multiplicação de matriz por escalar
        std::cout << "Matriz D = C * 2:\n" << D << std::endl;

        Matrix<int> E = 10 + D; // Soma de escalar + matriz
        std::cout << "Matriz E = 10 + D:\n" << E << std::endl;

        // --- Exemplos adicionais para testar outras funcionalidades ---

        // Subtração de matrizes
        Matrix<int> F = C - B;
        std::cout << "Matriz F = C - B:\n" << F << std::endl;

        // Multiplicação de matrizes (álgebra linear)
        Matrix<int> M_prod1 = { {1, 2}, {3, 4} }; // 2x2
        Matrix<int> M_prod2 = { {5, 6}, {7, 8} }; // 2x2
        Matrix<int> M_result_prod = M_prod1 * M_prod2;
        std::cout << "Multiplicação M_prod1 * M_prod2:\n" << M_result_prod << std::endl;
        // (1*5 + 2*7) = 5+14 = 19 | (1*6 + 2*8) = 6+16 = 22
        // (3*5 + 4*7) = 15+28 = 43 | (3*6 + 4*8) = 18+32 = 50

        // Transposição
        Matrix<int> G = { {1, 2, 3}, {4, 5, 6} };
        Matrix<int> G_transposed = G.transpose();
        std::cout << "Matriz G original:\n" << G << std::endl;
        std::cout << "Matriz G transposta:\n" << G_transposed << std::endl;

        // Operadores compostos
        Matrix<int> H = { {1, 1}, {1, 1} };
        Matrix<int> I = { {2, 2}, {2, 2} };
        H += I; // H = H + I
        std::cout << "Matriz H depois de H += I:\n" << H << std::endl;

        Matrix<double> J(2, 2, 1.0);
        J(0, 0) = 5.0; J(0, 1) = 10.0;
        J(1, 0) = 15.0; J(1, 1) = 20.0;
        std::cout << "Matriz J original:\n" << J << std::endl;
        J /= 5.0; // J = J / 5.0
        std::cout << "Matriz J depois de J /= 5.0:\n" << J << std::endl;


        // Testando exceções (descomente para testar)
        // Matrix<int> invalid_sum = A + M_prod1; // Dimensões incompatíveis para soma
        // Matrix<int> invalid_mul = A * B; // Dimensões incompatíveis para multiplicação
        // Matrix<int> div_by_zero = C / 0; // Divisão por zero
        // Matrix<int> empty_matrix(0, 0); // Dimensões zero no construtor
        // Matrix<int> inconsistent_initializer = { {1, 2}, {3, 4, 5} }; // Initializer list inconsistente

    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}