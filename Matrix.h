#pragma once

#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

// Classe template Matrix: representa uma matriz genérica de tipo T
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data; // Armazena os dados da matriz
    size_t rows; // Número de linhas
    size_t cols; // Número de colunas

public:
    Matrix(size_t numRows, size_t numCols, const T& initialValue = T())
        : rows(numRows), cols(numCols) {
        if (numRows == 0 || numCols == 0) {
            throw std::invalid_argument("As dimensões da matriz devem ser positivas.");
        }
        data.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i].resize(cols, initialValue);
        }
    }
    
    // Construtor de cópia
    Matrix(const Matrix<T>& other)
        : rows(other.rows), cols(other.cols), data(other.data) {
        
    }

    // Construtor com lista de inicialização
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        rows = list.size();
        if (rows == 0) {
            cols = 0; 
            return;
        }

    
        cols = list.begin()->size();
        if (cols == 0) {
            throw std::invalid_argument("As linhas da lista de inicializadores não podem estar vazias.");
        }

        data.resize(rows);
        size_t r = 0;
        for (const auto& row_list : list) {
            if (row_list.size() != cols) {
                throw std::invalid_argument("As linhas da lista de inicializadores devem ter contagens de colunas consistentes.");
            }
            data[r].assign(row_list.begin(), row_list.end());
            r++;
        }
    }

    // Retorna o número de linhas da matriz
    size_t getRows() const { return rows; }

    // Retorna o número de colunas da matriz
    size_t getCols() const { return cols; }


    T& operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Acesso ao elemento da matriz fora dos limites.");
        }
        return data[r][c];
    }

    const T& operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Acesso ao elemento da matriz fora dos limites.");
        }
        return data[r][c];
    }

    // Soma de matrizes
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("As dimensões da matriz devem corresponder para adição.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Subtração de matrizes
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("As dimensões da matriz devem corresponder para subtração.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Multiplicação de matrizes
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("O número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz para multiplicação.");
        }
        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T(); 
                for (size_t k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // Soma composta
    Matrix<T>& operator+=(const Matrix<T>& other) {
        *this = *this + other; 
        return *this;
    }

    // Subtração composta
    Matrix<T>& operator-=(const Matrix<T>& other) {
        *this = *this - other; 
        return *this;
    }

    // Multiplicação composta
    Matrix<T>& operator*=(const Matrix<T>& other) {
        *this = *this * other; 
        return *this;
    }

      // Operadores com escalar (retornam nova matriz)
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
        if (scalar == T()) { 
            throw std::invalid_argument("Divisão por escalar zero.");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

   // Operadores compostos com escalar
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

    // Retorna a matriz transposta
    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows); 
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Permite soma escalar + matriz
    template <typename U>
    friend Matrix<U> operator+(const U& scalar, const Matrix<U>& m);

    // Permite multiplicação escalar * matriz
    template <typename U>
    friend Matrix<U> operator*(const U& scalar, const Matrix<U>& m);

    // Impressão formatada da matriz
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);
};


template <typename U>
Matrix<U> operator+(const U& scalar, const Matrix<U>& m) {
    return m + scalar; 
}

template <typename U>
Matrix<U> operator*(const U& scalar, const Matrix<U>& m) {
    return m * scalar; 
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            os << m.data[i][j] << "\t";
        }
        os << std::endl;
    }
    return os;
}
