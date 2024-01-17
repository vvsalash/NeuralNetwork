#include "../headers/data_loader.h"
#include "../headers/magic.h"

DataLoader::DataLoader() : count_of_inputs_(0), rows_(magic::kMnistRows), cols_(magic::kMnistCols) {
}

DataLoader::DataLoader(const std::string &inputs_data, const std::string &labels_data, uint32_t size_of_batch)
        : count_of_inputs_(0), size_of_batch_(size_of_batch), rows_(magic::kMnistRows), cols_(magic::kMnistCols) {
    LoadInputs(inputs_data);
    LoadLabels(labels_data);
}

int32_t DataLoader::GetBatchesCount() {
    if (!(count_of_inputs_ % size_of_batch_)) {
        return count_of_inputs_ / size_of_batch_;
    }
    return count_of_inputs_ / size_of_batch_ + 1;
}

std::pair<Data<double>, std::vector<int32_t>> DataLoader::NextBatch() {
    return {}; //soon
}

void DataLoader::LoadInputs(const std::string &data) {
    //soon
}

void DataLoader::LoadLabels(const std::string &data) {
    //soon
}


uint32_t DataLoader::ConvertBytesToInt(const char *bytes) {
    return static_cast<uint32_t>(static_cast<unsigned char>(bytes[0]) << 24 |
                                 static_cast<unsigned char>(bytes[1]) << 16 |
                                 static_cast<unsigned char>(bytes[2]) << 8 |
                                 static_cast<unsigned char>(bytes[3]) << 0);
}