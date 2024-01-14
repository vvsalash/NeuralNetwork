#pragma once

#include "magic.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <memory>
#include <random>
#include <vector>

template<typename T>
class Data {
public:
    Data();

    Data(int8_t count_of_dimensions, std::vector<int32_t> dimensions);

    Data(const Data<T> &other);

    Data<T>& operator=(const Data<T>& other);

    int32_t GetSize() const;

    T Set(int32_t i, T value);

    T Set(int32_t i, int32_t j, T value);

    T Set(int32_t i, int32_t j, int32_t k, T value);

    T Set(int32_t i, int32_t j, int32_t k, int32_t l, T value);

    T Get(int32_t i) const;

    T Get(int32_t i, int32_t j) const;

    T Get(int32_t i, int32_t j, int32_t k) const;

    T Get(int32_t i, int32_t j, int32_t k, int32_t l) const;

    Data<T> MatrixMultiplication(Data<T>& other);

    Data<T> Sigmoid();

    Data<T> ReLU();

    void NormalRandom(std::default_random_engine generator, std::normal_distribution<double> distribution,
                      double multiplier);


    static T SigmoidFunction();

    static T ReLUFunction();

    std::array<int32_t, magic::kMaxDimCount> GetDimensions() const;

    std::shared_ptr<T> GetData() const;

    int32_t GetDimension(size_t i) const;

    int8_t GetDimensionsCount() const;

private:
    std::array<int32_t, magic::kMaxDimCount> dimensions_;
    std::shared_ptr<T> data_;
    int32_t size_;
    int8_t count_of_dimensions_;
};