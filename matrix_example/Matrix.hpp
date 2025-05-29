
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c, T val = T()) : rows(r), cols(c), data(r, std::vector<T>(c, val)) {}

    Matrix(const Matrix<T>& other) = default;

    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        rows = init.size();
        cols = init.begin()->size();
        for (auto& row : init) {
            if (row.size() != cols)
                throw std::invalid_argument("Rows must be same size.");
            data.emplace_back(row);
        }
    }

    T& operator()(size_t i, size_t j) { return data[i][j]; }
    const T& operator()(size_t i, size_t j) const { return data[i][j]; }

    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(j, i) = data[i][j];
        return result;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Sizes must match");
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(i, j) = data[i][j] + other(i, j);
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Invalid dimensions");
        Matrix<T> result(rows, other.cols, T());
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < other.cols; ++j)
                for (size_t k = 0; k < cols; ++k)
                    result(i, j) += data[i][k] * other(k, j);
        return result;
    }

    template<typename U>
    Matrix<T> operator+(U scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result(i, j) = data[i][j] + scalar;
        return result;
    }

    template<typename U>
    friend Matrix<T> operator+(U scalar, const Matrix<T>& m) {
        return m + scalar;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        for (const auto& row : m.data) {
            for (const auto& val : row) os << val << " ";
            os << '\n';
        }
        return os;
    }
};

#endif // MATRIX_HPP
