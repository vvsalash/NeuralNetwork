#include "../headers/data.h"


template<typename T>
Data<T>::Data() : dimensions_({}), data_(nullptr), size_(magic::kUndefinedSize), count_of_dimensions_(0) {
}

template<typename T>
Data<T>::Data(int8_t count_of_dimensions, std::vector<int32_t> dimensions) : count_of_dimensions_(count_of_dimensions) {
    assert(count_of_dimensions > 0 && count_of_dimensions <= 4 && "Count of dimensions from one to four!");
    size_ = 1;
    for (int8_t i = 0; i < count_of_dimensions; ++i) {
        dimensions_[i] = dimensions[i];
        size_ *= dimensions[i];
    }
    std::shared_ptr<T> data(new T[size_]);
    data_ = data;
}

template<typename T>
Data<T>::Data(const Data<T> &other) : dimensions_(other.GetDimensions()), size_(other.GetSize()),
                                      count_of_dimensions_(other.GetDimensionsCount()), data_(other.GetData()) {
}

template<typename T>
Data<T> &Data<T>::operator=(const Data<T> &other) {
    if (this != &other) {
        if (size_ != magic::kUndefinedSize) {
            data_.reset(other.GetData());
        }
        data_ = other.GetData();
    }
    return *this;
}

template<typename T>
Data<T> Data<T>::operator+(const Data<T> &other) {
    if (count_of_dimensions_ == 2 && other.GetDimensionsCount() == 1 && dimensions_[1] == other.GetSize()) {
        Data<T> result(count_of_dimensions_, dimensions_);
        for (int32_t i = 0; i < dimensions_[0]; ++i) {
            for (int32_t j = 0; j < dimensions_[1]; ++j) {
                result.Set(i, j, Get(i, j) + other.Get(j));
            }
        }
        return result;
    } else if (size_ == other.GetSize() && count_of_dimensions_ == other.GetDimensionsCount()) {
        Data<T> result(count_of_dimensions_, dimensions_);
        for (int32_t i = 0; i < size_; ++i) {
            result.GetData()[i] = data_[i] + other.GetData()[i];
        }
        return result;
    }
    throw std::runtime_error("You can not summarize data!");
}

template<typename T>
Data<T> Data<T>::operator*(const T value) {
    Data<T> result(count_of_dimensions_, dimensions_);
    for (int32_t i = 0; i < size_; ++i) {
        result.GetData()[i] = value * data_[i];
    }
    return result;
}

template<typename T>
Data<T> Data<T>::operator/(const T value) {
    Data<T> result(count_of_dimensions_, dimensions_);
    for (int32_t i = 0; i < size_; ++i) {
        result.GetData()[i] = data_[i] / value;
    }
    return result;
}

template<typename T>
Data<T>::~Data() = default;

template<typename T>
void Data<T>::Set(int32_t i, T value) {
    assert(count_of_dimensions_ == 1 && "Dimension is not equal to one!");
    data_[i] = value;
}

template<typename T>
void Data<T>::Set(int32_t i, int32_t j, T value) {
    assert(count_of_dimensions_ == 2 && "Dimension is not equal to two!");
    data_[dimensions_[1] * i + j] = value;
}

template<typename T>
void Data<T>::Set(int32_t i, int32_t j, int32_t k, T value) {
    assert(count_of_dimensions_ == 3 && "Dimension is not equal to three!");
    data_[dimensions_[1] * dimensions_[2] * i + dimensions_[2] * j + k] = value;
}

template<typename T>
void Data<T>::Set(int32_t i, int32_t j, int32_t k, int32_t l, T value) {
    assert(count_of_dimensions_ == 4 && "Dimension is not equal to four!");
    data_[dimensions_[1] * dimensions_[2] * dimensions_[3] * i + dimensions_[2] * dimensions_[3] * j +
          dimensions_[3] * k + l] = value;
}

template<typename T>
T Data<T>::Get(int32_t i) const {
    return data_[i];
}

template<typename T>
T Data<T>::Get(int32_t i, int32_t j) const {
    return data_[dimensions_[1] * i + j];
}

template<typename T>
T Data<T>::Get(int32_t i, int32_t j, int32_t k) const {
    return data_[dimensions_[1] * dimensions_[2] * i + dimensions_[2] * j + k];
}

template<typename T>
T Data<T>::Get(int32_t i, int32_t j, int32_t k, int32_t l) const {
    return data_[dimensions_[1] * dimensions_[2] * dimensions_[3] * i + dimensions_[2] * dimensions_[3] * j +
                 dimensions_[3] * k + l];
}

template<typename T>
Data<T> Data<T>::MatrixMultiplication(Data<T> &other) {
    assert(count_of_dimensions_ == 2 && other.GetDimensionsCount() == 2 && "Dimensions are not equal to two!");
    assert(dimensions_[1] == other.GetDimension(0) && "You can not multiply the matrices!");
    std::vector<int32_t> new_dimensions{dimensions_[0], other.GetDimension(1)};
    Data<T> result(count_of_dimensions_, new_dimensions);
    for (int32_t i = 0; i < new_dimensions[0]; ++i) {
        for (int32_t j = 0; j < new_dimensions[1]; ++j) {
            T value = 0;
            for (int32_t k = 0; k < dimensions_[1]; ++k) {
                value += Get(i, k) * other.Get(k, j);
            }
            result.Set(i, j, value);
        }
    }
    return result;
}

template<typename T>
Data<T> Data<T>::Transpose() {
    assert(count_of_dimensions_ == 2 && "Dimension is not equal to two!");
    std::vector<int32_t> new_dimensions{dimensions_[1], dimensions_[0]};
    Data<T> transposed_matrix(count_of_dimensions_, new_dimensions);
    for (int32_t i = 0; i < dimensions_[0]; ++i) {
        for (int32_t j = 0; j < dimensions_[1]; ++j) {
            transposed_matrix.Set(j, i, Get(i, j));
        }
    }
    return transposed_matrix;
}

template<typename T>
Data<T> Data<T>::Sigmoid() {
    Data<T> result(count_of_dimensions_, dimensions_);
    for (int32_t i = 0; i < size_; ++i) {
        result.GetData()[i] = SigmoidFunction(data_[i]);
    }
    return result;
}

template<typename T>
Data<T> Data<T>::ReLU() {
    Data<T> result(count_of_dimensions_, dimensions_);
    for (int32_t i = 0; i < size_; ++i) {
        result.GetData()[i] = ReLUFunction(data_[i]);
    }
    return result;
}

template<typename T>
void Data<T>::NormalRandom(std::default_random_engine generator, std::normal_distribution<double> distribution,
                           double multiplier) {
    for (int32_t i = 0; i < size_; ++i) {
        data_[i] = multiplier * distribution(generator);
    }
}

template<typename T>
std::array<int32_t, magic::kMaxDimCount> Data<T>::GetDimensions() const {
    return dimensions_;
}

template<typename T>
int32_t Data<T>::GetDimension(size_t i) const {
    return dimensions_[i];
}

template<typename T>
std::shared_ptr<T> Data<T>::GetData() const {
    return data_;
}

template<typename T>
int32_t Data<T>::GetSize() const {
    return size_;
}

template<typename T>
int8_t Data<T>::GetDimensionsCount() const {
    return count_of_dimensions_;
}

template<typename T>
T Data<T>::SigmoidFunction(T argument) {
    return 1.0 / (1.0 + std::exp(-argument));
}

template<typename T>
T Data<T>::ReLUFunction(T argument) {
    return argument > 0 ? 1 : 0;
}