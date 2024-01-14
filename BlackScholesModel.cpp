// BlackScholesModel.cpp
#include "BlackScholesModel.h"
#include "Option.h"
#include <cmath>
#include <iostream>

double BlackScholesModel::calculateD1(const Option& option) const {
    double numerator = std::log(option.getSpotPrice() / option.getStrikePrice())
                        + (option.getRiskFreeRate() + 0.5 * std::pow(option.getVolatility(), 2)) * option.getTimeToMaturity();
    double denominator = option.getVolatility() * std::sqrt(option.getTimeToMaturity());
    return numerator / denominator;
}

double BlackScholesModel::calculateD2(double d1, double volatility, double timeToMaturity) const {
    return d1 - volatility * std::sqrt(timeToMaturity);
}

double BlackScholesModel::calculateCallPrice(const Option& option) const {
    double d1 = calculateD1(option);
    double d2 = calculateD2(d1, option.getVolatility(), option.getTimeToMaturity());
    double callPrice = option.getSpotPrice() * normalCDF(d1) - option.getStrikePrice() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(d2);
    return callPrice;
}

double BlackScholesModel::calculatePutPrice(const Option& option) const {
    double d1 = calculateD1(option);
    double d2 = calculateD2(d1, option.getVolatility(), option.getTimeToMaturity());
    double putPrice = option.getStrikePrice() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(-d2) - option.getSpotPrice() * normalCDF(-d1);
    return putPrice;
}

// Helper function to calculate the cumulative distribution function (CDF) of the standard normal distribution
double BlackScholesModel::normalCDF(double x) const {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double BlackScholesModel::normalPDF(double x) const {
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}

double BlackScholesModel::calculateDelta(const Option& option, std::string optionType) const {
    double d1 = calculateD1(option);
    if (optionType == "Call")
        return normalCDF(d1);
    else if (optionType == "Put")
        return normalCDF(d1) - 1.0;
    else {
        std::cout << "Invalid option type" << std::endl;
        return 0.0;
    }
}

double BlackScholesModel::calculateGamma(const Option& option) const {
    double d1 = calculateD1(option);
    return normalPDF(d1) / (option.getSpotPrice() * option.getVolatility() * std::sqrt(option.getTimeToMaturity()));
}

double BlackScholesModel::calculateVega(const Option& option) const {
    double d1 = calculateD1(option);
    return option.getSpotPrice() * normalPDF(d1) * std::sqrt(option.getTimeToMaturity());
}

double BlackScholesModel::calculateTheta(const Option& option, std::string optionType) const {
    double d1 = calculateD1(option);
    double d2 = calculateD2(d1, option.getVolatility(), option.getTimeToMaturity());
    if (optionType == "Call")
        return -option.getSpotPrice() * normalPDF(d1) * option.getVolatility() / (2.0 * std::sqrt(option.getTimeToMaturity())) - option.getRiskFreeRate() * option.getStrikePrice() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(d2);
    else if (optionType == "Put")
        return -option.getSpotPrice() * normalPDF(d1) * option.getVolatility() / (2.0 * std::sqrt(option.getTimeToMaturity())) + option.getRiskFreeRate() * option.getStrikePrice() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(-d2);
    else {
        std::cout << "Invalid option type" << std::endl;
        return 0.0;
    }
}

double BlackScholesModel::calculateRho(const Option& option, std::string optionType) const {
    double d1 = calculateD1(option);
    double d2 = calculateD2(d1, option.getVolatility(), option.getTimeToMaturity());
    if (optionType == "Call")
        return option.getStrikePrice() * option.getTimeToMaturity() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(d2);
    else if (optionType == "Put")
        return -option.getStrikePrice() * option.getTimeToMaturity() * std::exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normalCDF(-d2);
    else {
        std::cout << "Invalid option type" << std::endl;
        return 0.0;
    }
}   

