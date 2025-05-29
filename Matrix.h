#pragma once

#include <vector>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

// Classe template Matriz: representa uma matriz genérica de tipo T
template <typename T>
class Matriz {
private:
    std::vector<std::vector<T>> dados; // Armazena os dados da matriz
    size_t linhas; // Número de linhas
    size_t colunas; // Número de colunas

public:
    // Construtor padrão com valor inicial
    Matriz(size_t numLinhas, size_t numColunas, const T& valorInicial = T())
        : linhas(numLinhas), colunas(numColunas) {
        if (numLinhas == 0 || numColunas == 0) {
            throw std::invalid_argument("As dimensões da matriz devem ser positivas.");
        }
        dados.resize(linhas);
        for (size_t i = 0; i < linhas; ++i) {
            dados[i].resize(colunas, valorInicial);
        }
    }
    
    // Construtor de cópia
    Matriz(const Matriz<T>& outra)
        : linhas(outra.linhas), colunas(outra.colunas), dados(outra.dados) {}

    // Construtor com lista de inicialização
    Matriz(std::initializer_list<std::initializer_list<T>> lista) {
        linhas = lista.size();
        if (linhas == 0) {
            colunas = 0; 
            return;
        }

        colunas = lista.begin()->size();
        if (colunas == 0) {
            throw std::invalid_argument("As linhas da lista de inicializadores não podem estar vazias.");
        }

        dados.resize(linhas);
        size_t l = 0;
        for (const auto& linha_lista : lista) {
            if (linha_lista.size() != colunas) {
                throw std::invalid_argument("Todas as linhas devem ter a mesma quantidade de colunas.");
            }
            dados[l].assign(linha_lista.begin(), linha_lista.end());
            l++;
        }
    }

    // Retorna o número de linhas
    size_t obterLinhas() const { return linhas; }

    // Retorna o número de colunas
    size_t obterColunas() const { return colunas; }

    // Acesso com verificação de limites (modificável)
    T& operator()(size_t l, size_t c) {
        if (l >= linhas || c >= colunas) {
            throw std::out_of_range("Acesso ao elemento fora dos limites.");
        }
        return dados[l][c];
    }

    // Acesso com verificação de limites (constante)
    const T& operator()(size_t l, size_t c) const {
        if (l >= linhas || c >= colunas) {
            throw std::out_of_range("Acesso ao elemento fora dos limites.");
        }
        return dados[l][c];
    }

    // Soma de matrizes
    Matriz<T> operator+(const Matriz<T>& outra) const {
        if (linhas != outra.linhas || colunas != outra.colunas) {
            throw std::invalid_argument("As dimensões devem ser iguais para somar.");
        }
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] + outra.dados[i][j];
            }
        }
        return resultado;
    }

    // Subtração de matrizes
    Matriz<T> operator-(const Matriz<T>& outra) const {
        if (linhas != outra.linhas || colunas != outra.colunas) {
            throw std::invalid_argument("As dimensões devem ser iguais para subtrair.");
        }
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] - outra.dados[i][j];
            }
        }
        return resultado;
    }

    // Multiplicação de matrizes
    Matriz<T> operator*(const Matriz<T>& outra) const {
        if (colunas != outra.linhas) {
            throw std::invalid_argument("O número de colunas da primeira deve ser igual ao número de linhas da segunda.");
        }
        Matriz<T> resultado(linhas, outra.colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < outra.colunas; ++j) {
                T soma = T(); 
                for (size_t k = 0; k < colunas; ++k) {
                    soma += dados[i][k] * outra.dados[k][j];
                }
                resultado.dados[i][j] = soma;
            }
        }
        return resultado;
    }

    // Operadores compostos com outra matriz
    Matriz<T>& operator+=(const Matriz<T>& outra) {
        *this = *this + outra;
        return *this;
    }

    Matriz<T>& operator-=(const Matriz<T>& outra) {
        *this = *this - outra;
        return *this;
    }

    Matriz<T>& operator*=(const Matriz<T>& outra) {
        *this = *this * outra;
        return *this;
    }

    // Operadores com escalar
    Matriz<T> operator+(const T& escalar) const {
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] + escalar;
            }
        }
        return resultado;
    }

    Matriz<T> operator-(const T& escalar) const {
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] - escalar;
            }
        }
        return resultado;
    }

    Matriz<T> operator*(const T& escalar) const {
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] * escalar;
            }
        }
        return resultado;
    }

    Matriz<T> operator/(const T& escalar) const {
        if (escalar == T()) {
            throw std::invalid_argument("Divisão por escalar zero.");
        }
        Matriz<T> resultado(linhas, colunas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] / escalar;
            }
        }
        return resultado;
    }

    // Operadores compostos com escalar
    Matriz<T>& operator+=(const T& escalar) {
        *this = *this + escalar;
        return *this;
    }

    Matriz<T>& operator-=(const T& escalar) {
        *this = *this - escalar;
        return *this;
    }

    Matriz<T>& operator*=(const T& escalar) {
        *this = *this * escalar;
        return *this;
    }

    Matriz<T>& operator/=(const T& escalar) {
        *this = *this / escalar;
        return *this;
    }

    // Retorna a matriz transposta
    Matriz<T> transposta() const {
        Matriz<T> resultado(colunas, linhas);
        for (size_t i = 0; i < linhas; ++i) {
            for (size_t j = 0; j < colunas; ++j) {
                resultado.dados[j][i] = dados[i][j];
            }
        }
        return resultado;
    }

    // Operadores amigos para escalar + matriz e escalar * matriz
    template <typename U>
    friend Matriz<U> operator+(const U& escalar, const Matriz<U>& m);

    template <typename U>
    friend Matriz<U> operator*(const U& escalar, const Matriz<U>& m);

    // Impressão da matriz
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matriz<U>& m);
};

// Implementações dos operadores amigos

template <typename U>
Matriz<U> operator+(const U& escalar, const Matriz<U>& m) {
    return m + escalar;
}

template <typename U>
Matriz<U> operator*(const U& escalar, const Matriz<U>& m) {
    return m * escalar;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Matriz<U>& m) {
    for (size_t i = 0; i < m.linhas; ++i) {
        for (size_t j = 0; j < m.colunas; ++j) {
            os << m.dados[i][j] << "\t";
        }
        os << std::endl;
    }
    return os;
}
