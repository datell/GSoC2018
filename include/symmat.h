#ifndef GSOC_SYMMAT_H
#define GSOC_SYMMAT_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ostream>
#include "eigen3/Eigen/Eigen"

template<typename Scalar = void>
class SymMat {
    public:
    /**
     * Default constructor
     */
    SymMat() : dimension(0) {};

    /**
     * Constructor that builds a symmetric matrix from an Eigen::Matrix
     */
    SymMat(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& mat) 
    : dimension (mat.cols()) {
        for (int row = 0; row < dimension; row++) {
            for (int col = row; col < dimension; col++) {
                elements.push_back(mat(row,col));
            }
        }
    }

    /**
     * Construtor that builds a symmetric matrix from a row major std::vector<T>.
     */
    SymMat(const std::vector<Scalar>& vec) : elements(vec) {
        // Calculation of dimension
        dimension = (sqrt(1+8*vec.size())-1)/2;
    }

    /**
     * Constructor that builds a symmetric matrix from a row major std::vector<T>.
     * The dimension is passed as an arguments and does not have to be calculated
     */
    SymMat(const std::vector<Scalar>& vec, int dimension) : elements(vec),
                                                            dimension(dimension)
                                                            {}

    /**
     * Checks if a matrix is symmetric or not.
     * \param mat Matrix of type Eigen::Matrix.
     * \return True if mat is symmetric, false otherwise
     */
    static bool isSymmetric(const Eigen::Matrix<Scalar, Eigen::Dynamic, 
                                                Eigen::Dynamic>& mat) {
        return (mat == mat.transpose())?true:false;
    }
    
    /**
     * Dimension of the symmetric matrix.
     * /return Dimension of the symmetric matrix.
     */
    Eigen::Index dim() const {
        return dimension;
    }

    /**
     * Overloaded operator () to access elements of the matrix directly
     * \param row Row index 
     * \param col Column index
     * \retrun Matrix element at position (row, col)
     */
    Scalar operator()(int row, int col) const {
        if (row <= col) {
            return elements[row * dimension - (row-1)*((row-1) + 1)/2 + col - row];
        } else {
            return elements[col * dimension - (col-1)*((col-1) + 1)/2 + row - col];
        }
    }

    /**
     * Overloaded operator + for addition of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to add with.
     * \return Sum of the matrices.
     */
    SymMat<Scalar> operator+(const SymMat<Scalar>& other) {
        SymMat<Scalar> ret(elements, dimension);
        int numElements = elements.size();
        for (int i = 0; i < numElements; ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    /**
     * Overloaded operator - for subtraction of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to subtract with.
     * \return Difference of both matrices.
     */
    SymMat<Scalar> operator-(const SymMat<Scalar>& other) {
        SymMat<Scalar> ret(elements, dimension);
        int numElements = elements.size();
        for (int i = 0; i < numElements; ++i) {
           ret.elements[i] -= other.elements[i];
        }
        return ret;
    }

    /**
     * Overloaded operator + for addition of symmetric matrix with arbitrary 
     * matrix
     * \param other Matrix of type Eigen::Matrix
     * \return Sum of matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> 
    operator+(const Eigen::Matrix<Scalar, 
                                  Eigen::Dynamic, 
                                  Eigen::Dynamic>& other) {
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> ret;
        
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                ret(i,j) = operator()(i,j) + other(i,j);
            }
        }
        return ret;
    }

    /**
     * Construct a matrix of type Eigen::Matrix from a symmetric matrix
     * \return Eigen::Matrix that contains the same elements as the
     * symmetric matrix
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>  
    constructEigenMatrix() const {
        Eigen::Matrix<Scalar, 
                      Eigen::Dynamic, 
                      Eigen::Dynamic> ret(dimension, dimension);
        for (int i = 0; i < dimension; ++i) {
            for (int j = i; j < dimension; ++j) {
                ret(i, j) = operator()(i, j);
                ret(j, i) = operator()(i, j);
            }
        }
        return ret;
    }

    /**
     * Overloaded operator * for multiplying to symmetric matrices. 
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> 
    operator*(const SymMat<Scalar>& other) {
        return Eigen::Matrix<Scalar, 
                             Eigen::Dynamic, 
                             Eigen::Dynamic>(constructEigenMatrix() 
                                             * other.constructEigenMatrix());
    }

    /**
     * Overloaded operator * to multiply an arbitrary matrix with a symmetric
     * matrix.
     * \param other Arbitrary matrix to multiply with
     * \return Product of the matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator*(const Eigen::Matrix<Scalar, 
                                  Eigen::Dynamic, 
                                  Eigen::Dynamic>& other) {
        return Eigen::Matrix<Scalar, 
                             Eigen::Dynamic, 
                             Eigen::Dynamic>(constructEigenMatrix() * other);
    }

    /**
     * Overloaded operator << to print the matrix in human friendly form.
     * \param stream Output stream
     * \param mat Matrix that is printed
     * \return Output stream with representation of matrix pushed on
     */
    friend std::ostream& operator<<(std::ostream& stream, SymMat<Scalar>& mat) {
        for (int row = 0; row < mat.dim(); row++) {
            for (int col = 0; col < mat.dim(); col++) {
                stream << mat(row, col) << " ";
            }
            stream << "\n";
        }
        return stream;
    }

    private:
    std::vector<Scalar> elements;
    Eigen::Index dimension;
};


#endif /* GSOC_SYMMAT_H */