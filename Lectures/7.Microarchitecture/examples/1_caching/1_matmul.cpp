#include <scope_timer.hpp>
#include <random_utils.hpp>
#include <vector>
#include <span>


template<typename T = double>
class Matrix{
    std::vector<T> _data;
    size_t linear_idx(size_t i, size_t j) const{
        return i*cols+j;
    }
public:

    Matrix(size_t rows, size_t cols): rows(rows), cols(cols), _data(rows*cols){}
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;


    const size_t rows, cols;

    std::span<T> data(){
        return _data;
    }

    std::span<const T> data() const{
        return {_data.data(), _data.size()};
    }

    T& operator[](size_t i, size_t j){
        return _data[linear_idx(i, j)];
    }

    T operator[](size_t i, size_t j) const{
        return (*const_cast<Matrix*>(this))[i, j];
    }

    Matrix transpose()const {
        Matrix result{cols, rows};
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                result[j, i] = (*this)[i, j];
        return result;
    }

};

template<typename T>
Matrix<T> mul(const Matrix<T>& a, const Matrix<T>& b){
    if(a.cols != b.rows)
        throw std::logic_error("Incompatible dimensions" );

    Matrix result{a.rows, b.cols};
    for (size_t i = 0; i < a.rows; ++i)
        for (size_t j = 0; j < b.cols; ++j) {
            T value = {};
            for (size_t k = 0; k < a.cols; ++k) {
                value += a[i, k]*b[k, j];
            }
            result[i, j] = value;
        }
    return result;
}


template<typename T>
Matrix<T> Tmul(const Matrix<T>& a, const Matrix<T>& b){
    if(a.cols != b.rows)
        throw std::logic_error("Incompatible dimensions" );

    Matrix result{a.rows, b.cols};
    Matrix tmp = b.transpose();
    for (size_t i = 0; i < a.rows; ++i)
        for (size_t j = 0; j < b.cols; ++j) {
            T value = {};
            for (size_t k = 0; k < a.cols; ++k) {
                value += a[i, k]*tmp[j, k];
            }
            result[i, j] = value;
        }
    return result;
}

constexpr size_t SIZE = 1024;
int main(){
    Matrix a{SIZE, SIZE};
    fill_random(a.data().begin(), a.data().end());
    Matrix b = a;

    {
        scope_timer _{"Matmul"};
        volatile Matrix x = mul(a, b);
    }

    {
        scope_timer _{"Matmul with transpose"};
        volatile Matrix x = Tmul(a, b);
    }

}
