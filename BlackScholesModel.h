// BlackScholesModel.h
#pragma once
#include "Option.h"
#include <iostream>

class BlackScholesModel {
public:
    // Black-Scholes formula functions
    double normalCDF(double x) const;
    double normalPDF(double x) const;
    double calculateD1(const Option& option) const;
    double calculateD2(double d1, double volatility, double timeToMaturity) const;
    double calculateCallPrice(const Option& option) const;
    double calculatePutPrice(const Option& option) const;

    double calculateDelta(const Option& option, std::string optionType) const;
    double calculateGamma(const Option& option) const;
    double calculateVega(const Option& option) const;
    double calculateTheta(const Option& option, std::string optionType) const;
    double calculateRho(const Option& option, std::string optionType) const;


private:
    std::string optionType;
};
