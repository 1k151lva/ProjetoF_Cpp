#pragma once

#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept> // Para lançar exceções

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    // Construtor: rows, cols, initialValue
    Matrix(size_t numRows, size_t numCols, const T& initialValue = T())
        : rows(numRows), cols(numCols) {
        if (numRows == 0 || numCols == 0) {
            throw std::invalid_argument("Matrix dimensions must be positive.");
        }
        data.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i].resize(cols, initialValue);
        }
    }

    // Construtor de cópia
    Matrix(const Matrix<T>& other)
        : rows(other.rows), cols(other.cols), data(other.data) {
        // A cópia profunda é tratada pelo construtor de cópia de std::vector
    }

    // Construtor com std::initializer_list
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        rows = list.size();
        if (rows == 0) {
            cols = 0; // Matriz vazia
            return;
        }

        // Determina o número de colunas a partir da primeira linha
        cols = list.begin()->size();
        if (cols == 0) {
            throw std::invalid_argument("Initializer list rows cannot be empty.");
        }

        data.resize(rows);
        size_t r = 0;
        for (const auto& row_list : list) {
            if (row_list.size() != cols) {
                throw std::invalid_argument("Initializer list rows must have consistent column counts.");
            }
            data[r].assign(row_list.begin(), row_list.end());
            r++;
        }
    }

    // Métodos de acesso às dimensões
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Acesso aos elementos (operador ())
    T& operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Matrix element access out of bounds.");
        }
        return data[r][c];
    }

    const T& operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Matrix element access out of bounds.");
        }
        return data[r][c];
    }

    // Operações Matemáticas Entre Matrizes
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Number of columns of first matrix must equal number of rows of second matrix for multiplication.");
        }
        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T(); // Inicializa com o valor padrão para T (e.g., 0 para numéricos)
                for (size_t k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // Operadores compostos entre matrizes
    Matrix<T>& operator+=(const Matrix<T>& other) {
        *this = *this + other; // Reutiliza o operador +
        return *this;
    }

    Matrix<T>& operator-=(const Matrix<T>& other) {
        *this = *this - other; // Reutiliza o operador -
        return *this;
    }

    Matrix<T>& operator*=(const Matrix<T>& other) {
        *this = *this * other; // Reutiliza o operador *
        return *this;
    }

    // Operações com Escalares (Matrix op U)
    Matrix<T> operator+(const T& scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + scalar;
            }
        }
        return result;
    }

    Matrix<T> operator-(const T& scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - scalar;
            }
        }
        return result;
    }

    Matrix<T> operator*(const T& scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix<T> operator/(const T& scalar) const {
        if (scalar == T()) { // Verifica divisão por zero (assumindo T() é o zero para o tipo T)
            throw std::invalid_argument("Division by zero scalar.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Operadores compostos com escalares (Matrix op= U)
    Matrix<T>& operator+=(const T& scalar) {
        *this = *this + scalar;
        return *this;
    }

    Matrix<T>& operator-=(const T& scalar) {
        *this = *this - scalar;
        return *this;
    }

    Matrix<T>& operator*=(const T& scalar) {
        *this = *this * scalar;
        return *this;
    }

    Matrix<T>& operator/=(const T& scalar) {
        *this = *this / scalar;
        return *this;
    }

    // Transposição de Matrizes
    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows); // Inverte rows e cols
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Operadores com escalar à esquerda (friend functions)
    template <typename U>
    friend Matrix<U> operator+(const U& scalar, const Matrix<U>& m);
    template <typename U>
    friend Matrix<U> operator*(const U& scalar, const Matrix<U>& m);

    // Impressão (operador <<) (friend function)
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);
};

// Implementações das funções friend fora da classe
template <typename U>
Matrix<U> operator+(const U& scalar, const Matrix<U>& m) {
    return m + scalar; // Reutiliza o operador + da classe
}

template <typename U>
Matrix<U> operator*(const U& scalar, const Matrix<U>& m) {
    return m * scalar; // Reutiliza o operador * da classe
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            os << m.data[i][j] << "\t"; // Usa tab para alinhar
        }
        os << std::endl;
    }
    return os;
}