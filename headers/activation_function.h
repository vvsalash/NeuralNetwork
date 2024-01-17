#pragma once

#include "data.h"

class ActivationFunction {
public:
    virtual Data<double> &ForwardPropagation(Data<double> &input) = 0;

    virtual Data<double> BackwardPropagation(Data<double> &gradient) = 0;

    virtual ~ActivationFunction() = default;
};