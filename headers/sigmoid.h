#pragma once

#include "activation_function.h"

class Sigmoid : public ActivationFunction {
public:
    Data<double> &ForwardPropagation(Data<double> &input) override;

    Data<double> BackwardPropagation(Data<double> &gradient) override;
private:
};