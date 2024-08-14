// main.cpp
#include "Option.h"
#include "BlackScholesModel.h"
#include "MonteCarloPricer.h"
#include <iostream>

int main() {
    // Example usage
    Option opt(100.0, 100.0, 0.2, 0.02, 1.0); // SpotPrice, StrikePrice, Volatility, RiskFreeRate, TimeToMaturity
    BlackScholesModel bsModel;
    MonteCarloOptionPricer monteCarloPricer(opt, 1000000, 0.01);

    double callPrice = bsModel.calculateCallPrice(opt);
    double monteCarloCallPrice = monteCarloPricer.callPrice;
    double putPrice = bsModel.calculatePutPrice(opt);
    double monteCarloPutPrice = monteCarloPricer.putPrice;

    std::cout << "Call Option Price with BS model: " << callPrice << std::endl;
    std::cout << "Call Price with monte carlo: " << monteCarloCallPrice << std::endl;

    std::cout << "Put Option Price with BS model: " << putPrice << std::endl;
    std::cout << "Put Price with monte carlo: " << monteCarloPutPrice << std::endl;

    std::cout << "Comparing the call greeks with BS // monte carlo simulation : " << std::endl;
    std::cout << "Delta: " << bsModel.calculateDelta(opt, "Call") << " // " << monteCarloPricer.calculateDelta("Call") << std::endl;
    std::cout << "Gamma: " << bsModel.calculateGamma(opt) << " // " << monteCarloPricer.calculateGamma() << std::endl;
    std::cout << "Vega: " << bsModel.calculateVega(opt) << " // " << monteCarloPricer.calculateVega() << std::endl;
    std::cout << "Theta: " << bsModel.calculateTheta(opt, "Call") << " // " << monteCarloPricer.calculateTheta("Call") << std::endl;
    std::cout << "Rho: " << bsModel.calculateRho(opt, "Call") << " // " << monteCarloPricer.calculateRho("Call") << std::endl;
    return 0;
}
