// Option.h
#pragma once

class Option {
public:
    // Constructor
    Option(double spotPrice, double strikePrice, double volatility, double riskFreeRate, double timeToMaturity);

    // Getters
    double getSpotPrice() const;
    double getStrikePrice() const;
    double getVolatility() const;
    double getRiskFreeRate() const;
    double getTimeToMaturity() const;

    // Setters
    void setSpotPrice(double spotPrice);
    void setStrikePrice(double strikePrice);
    void setVolatility(double volatility);
    void setRiskFreeRate(double riskFreeRate);
    void setTimeToMaturity(double timeToMaturity);

private:
    // Member variables
    double spotPrice;
    double strikePrice;
    double volatility;
    double riskFreeRate;
    double timeToMaturity;
};
