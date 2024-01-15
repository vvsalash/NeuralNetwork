#pragma once

#include <vector>

class DataLoader {
public:
    DataLoader();
    int32_t GetBatchesCount();

private:
    std::vector<std::vector<std::vector<double>>> inputs_;
    std::vector<std::vector<int32_t>> labels_;
};