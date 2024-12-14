/***
*  =================================
 *  | Author | Hamed Firouzipouyaei |
 *  ---------------------------------
 *  | Version Control_______________|
 *  ---------------------------------
 *  | V.1.0.0 | December 14, 2024   |
 *  =================================
 ***/

#ifndef MATHH_LIBRARY_H
#define MATHH_LIBRARY_H
#include <stdexcept>
#include <vector>

using V1D       = std::vector<double>;
using V2D       = std::vector<V1D>;
using V3D       = std::vector<V2D>;

namespace MathH
{
    template<typename T>
    class Matrix
    {
        private:
        size_t rows_;               ///< The number of rows in the matrix.
        size_t cols_;               ///< The number of columns in the matrix.
        std::vector<T> data_;       ///< A contiguous vector of size (rows_ * cols_) holding all elements.

        public:

        /**
         * @brief Construct a new Matrix with given dimensions.
         *
         * This constructor creates a matrix with the specified number of rows and columns. All
         * elements are initialized to zero (0.0). Note that if T is not floating-point, it will
         * attempt to convert 0.0 to T, which should be valid for standard numeric types.
         *
         * @param rows The number of rows in the matrix.
         * @param cols The number of columns in the matrix.
         * @throws std::runtime_error if rows or cols is zero (not thrown by this code, but such checks could be added).
         */
        Matrix(const size_t rows, const size_t cols)
            : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

        /**
         * @brief Construct a new Matrix from a nested initializer list.
         *
         * This constructor allows convenient creation of matrices from a syntax like:
         * @code{.cpp}
         * Matrix<double> M = {
         *     {1.0, 2.0, 3.0},
         *     {4.0, 5.0, 6.0}
         * };
         * @endcode
         *
         * In this example, M would be a 2x3 matrix. The constructor verifies that all rows
         * have the same length. If they do not, it throws a std::runtime_error.
         *
         * @param values A nested initializer list of type T representing rows and columns.
         * @throws std::runtime_error if the rows do not have consistent lengths.
         */
        Matrix(std::initializer_list<std::initializer_list<T>> values)
        {
            rows_ = values.size();
            cols_ = values.begin()->size();
            data_.resize(rows_ * cols_);
            size_t i = 0;
            for (auto &row : values)
            {
                if (row.size() != cols_)
                    throw std::runtime_error("Inconsistent row length");
                for (auto &val : row)
                    data_[i++] = val;
            }
        }

        /**
         * @brief Overloaded operator () to access element at given row and column (modifiable).
         *
         * Provides direct read-write access to the element at position (r, c). Uses zero-based indexing.
         *
         * @param r The row index (0-based).
         * @param c The column index (0-based).
         * @return T& A reference to the element at (r, c).
         * @throws std::out_of_range if r or c are out of bounds (not implemented here, but could be added).
         */
        T &operator()(const size_t r, const size_t c)
        {
            return data_[r * cols_ + c];
        }

        /**
         * @brief Overloaded operator () to access element at given row and column (read-only).
         *
         * Provides read-only access to the element at position (r, c). Uses zero-based indexing.
         *
         * @param r The row index (0-based).
         * @param c The column index (0-based).
         * @return T The value of the element at (r, c).
         * @throws std::out_of_range if r or c are out of bounds (not implemented here, but could be added).
         */
        T operator()(const size_t r, const size_t  c) const
        {
            return data_[r * cols_ + c];
        }

        /**
         * @brief Get the number of rows in the matrix.
         *
         * @return size_t The number of rows.
         */
        size_t rows() const {return rows_;}

        /**
         * @brief Get the number of columns in the matrix.
         *
         * @return size_t The number of columns.
         */
        size_t cols() const {return cols_;}

    };

    template<typename T>
    class MathHClass
    {
        public:
        Matrix<T> multiply(Matrix<T> &A, Matrix<T> &B)
        {
            if (A.cols() != B.rows())
            {
                throw std::runtime_error("Matrix dimensions are not compatible for multiplication");
            }

            Matrix<T> C(A.rows(), B.cols());
            for (size_t i = 0; i < A.rows(); ++i)
            {
                for (size_t j = 0; j < B.cols(); ++j)
                {
                    double sum = 0.0;
                    for (size_t k = 0; k < A.cols(); ++k)
                    {
                        sum += A(i, k) * B(k, j);
                    }
                    C(i, j) = sum;
                }
            }
            return C;
        }

        private:
    };
}

#endif //MATHH_LIBRARY_H