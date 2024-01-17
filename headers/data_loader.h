#pragma once

#include "data.h"

#include <vector>
#include <utility>

class DataLoader {
public:
    DataLoader();

    DataLoader(const std::string& inputs_data, const std::string& labels_data, uint32_t size_of_batch);

    int32_t GetBatchesCount();

    std::pair<Data<double>, std::vector<int32_t>> NextBatch();

private:
    void LoadInputs(std::string& data);

    void LoadLabels(std::string& data);

    uint32_t ConvertBytesToInt(const char* bytes);

    std::vector<std::vector<std::vector<double>>> inputs_;
    std::vector<std::vector<int32_t>> labels_;
    uint32_t count_of_inputs_;
    uint32_t size_of_batch_;
    uint32_t rows_;
    uint32_t cols_;
};