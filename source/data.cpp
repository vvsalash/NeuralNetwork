#include "../headers/data.h"


template<typename T>
Data<T>::Data() : dimensions_({}), data_(nullptr), size_(-1), count_of_dimensions_(0) {
}

template<typename T>
Data<T>::Data(int8_t count_of_dimensions, std::vector<int32_t> dimensions) : count_of_dimensions_(count_of_dimensions) {
    assert(count_of_dimensions > 0 && count_of_dimensions <= 4 && "Count of dimensions from one to four");
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

}

template<typename T>
T Data<T>::Set(int32_t i, T value) {
    assert(count_of_dimensions_ == 1 && "Dimension isn't equal to one");
    data_[i] = value;
}

template<typename T>
T Data<T>::Set(int32_t i, int32_t j, T value) {
    assert(count_of_dimensions_ == 2 && "Dimension isn't equal to two");
    data_[dimensions_[1] * i + j] = value;
}

template<typename T>
T Data<T>::Set(int32_t i, int32_t j, int32_t k, T value) {
    assert(count_of_dimensions_ == 3 && "Dimension isn't equal to three");
    data_[dimensions_[1] * dimensions_[2] * i + dimensions_[2] * j + k] = value;
}

template<typename T>
T Data<T>::Set(int32_t i, int32_t j, int32_t k, int32_t l, T value) {
    assert(count_of_dimensions_ == 4 && "Dimension isn't equal to four");
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