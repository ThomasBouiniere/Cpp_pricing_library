// Option.cpp
#include "Option.h"
#include <cmath>

Option::Option(double spotPrice, double strikePrice, double volatility, double riskFreeRate, double timeToMaturity)
    : spotPrice(spotPrice), strikePrice(strikePrice), volatility(volatility), riskFreeRate(riskFreeRate), timeToMaturity(timeToMaturity) {}

double Option::getSpotPrice() const {
    return spotPrice;
}

double Option::getStrikePrice() const {
    return strikePrice;
}

double Option::getVolatility() const {
    return volatility;
}

double Option::getRiskFreeRate() const {
    return riskFreeRate;
}

double Option::getTimeToMaturity() const {
    return timeToMaturity;
}

void Option::setSpotPrice(double spotPrice) {
    this->spotPrice = spotPrice;
}

void Option::setStrikePrice(double strikePrice) {
    this->strikePrice = strikePrice;
}

void Option::setVolatility(double volatility) {
    this->volatility = volatility;
}

void Option::setRiskFreeRate(double riskFreeRate) {
    this->riskFreeRate = riskFreeRate;
}

void Option::setTimeToMaturity(double timeToMaturity) {
    this->timeToMaturity = timeToMaturity;
}

