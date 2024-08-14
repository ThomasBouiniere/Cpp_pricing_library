#include "MonteCarloPricer.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>


MonteCarloOptionPricer::MonteCarloOptionPricer(Option& option, int numSimulations, double epsilon)
    : option(option), numSimulations(numSimulations), epsilon(epsilon) {
    callPrice = calculateOptionPrice("Call");
    putPrice = calculateOptionPrice("Put");
}


double MonteCarloOptionPricer::gaussian_box_muller() const {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

double MonteCarloOptionPricer::calculateOptionPrice(std::string OptionType) {

    double spot_price = option.getSpotPrice();
    double strike_price = option.getStrikePrice();
    double volatility = option.getVolatility();
    double risk_free_rate = option.getRiskFreeRate();
    double time_to_maturity = option.getTimeToMaturity();

    double S_adjust = spot_price * std::exp(time_to_maturity*(risk_free_rate-0.5*volatility*volatility));   // The adjustment to the spot price   
    double S_cur = 0.0;   // Our current asset price ("spot")
    double payoff_sum = 0.0;  // Holds the sum of all of the final option pay-offs

    for (int i=0; i<numSimulations; i++) {
        double gauss_bm = gaussian_box_muller();   // Generate a Gaussian random number via Box-Muller
        S_cur = S_adjust * exp(sqrt(volatility*volatility*time_to_maturity)*gauss_bm);   // Adjust the spot price via the Brownian motion final distribution
        if (OptionType == "Call")
            payoff_sum += std::max(S_cur - option.getStrikePrice(), 0.0);   // Take the option pay-off, then add it to the rest of the pay-off values
        else if (OptionType == "Put")
            payoff_sum += std::max(option.getStrikePrice() - S_cur, 0.0);   // Take the option pay-off, then add it to the rest of the pay-off values
        else
            std::cout << "Invalid option type" << std::endl;
    }

    // Average the pay-off sum via the number of paths and then 
    // discount the risk-free rate from the price
    return (payoff_sum / static_cast<double>(numSimulations)) * exp(-risk_free_rate*time_to_maturity);
}

// implement delta computation by monte carlo simulation

double MonteCarloOptionPricer::calculateDelta(std::string OptionType) {
    double PriceUp = 0.0; 
    double delta = 0.0; 

    double spotPrice = option.getSpotPrice();

    option.setSpotPrice(spotPrice *(1 + epsilon));

    if (OptionType == "Call") {
        PriceUp = calculateOptionPrice("Call");
        delta = (PriceUp - callPrice) / (epsilon * spotPrice);
    }
    else if (OptionType == "Put") {
        PriceUp = calculateOptionPrice("Put");
        delta = (PriceUp - putPrice) / (epsilon * spotPrice);
    }
    else {
        std::cout << "Invalid option type" << std::endl;
    }

    option.setSpotPrice(spotPrice);
    return delta;
}

// implement gamma computation by monte carlo simulation

double MonteCarloOptionPricer::calculateGamma() {
    double PriceUp = 0.0;
    double PriceDown = 0.0;
    double gamma = 0.0;
    double deltaUp = 0.0;
    double deltaDown = 0.0;

    double spotPrice = option.getSpotPrice();

    option.setSpotPrice(spotPrice *(1+ epsilon));
    PriceUp = calculateOptionPrice("Call");

    option.setSpotPrice(spotPrice *(1- epsilon));
    PriceDown = calculateOptionPrice("Call");

    // std::cout << "PriceUp: " << PriceUp << std::endl;
    // std::cout << "PriceDown: " << PriceDown << std::endl;
    // std::cout << "callPrice: " << callPrice << std::endl;
    // std::cout << "compute: " << (PriceUp - 2*callPrice + PriceDown) << std::endl;

    gamma = (PriceUp - 2*callPrice + PriceDown) / (spotPrice * spotPrice * epsilon * epsilon);

    option.setSpotPrice(spotPrice);
    return gamma;
}

// implement vega computation by monte carlo simulation

double MonteCarloOptionPricer::calculateVega() {
    double PriceUp = 0.0;
    double vega = 0.0;

    double volatility = option.getVolatility();

    option.setVolatility(volatility *(1+ epsilon));
    PriceUp = calculateOptionPrice("Call");

    vega = (PriceUp - callPrice) /  (epsilon * volatility);

    option.setVolatility(volatility);
    return vega;
}

// implement theta computation by monte carlo simulation

double MonteCarloOptionPricer::calculateTheta(std::string OptionType) {
    double PriceUp = 0.0;
    double PriceDown = 0.0;
    double theta = 0.0;

    double timeToMaturity = option.getTimeToMaturity();

    option.setTimeToMaturity(timeToMaturity *(1- epsilon));

    if (OptionType == "Call") {
        PriceUp = calculateOptionPrice("Call");
        theta = (PriceUp - callPrice) / (timeToMaturity * epsilon);
    }
    else if (OptionType == "Put") {
        PriceUp = calculateOptionPrice("Put");
        theta = (PriceUp - putPrice) / (timeToMaturity * epsilon);
    }
    else {
        std::cout << "Invalid option type" << std::endl;
    }

    option.setTimeToMaturity(timeToMaturity);
    return theta;
}

// implement rho computation by monte carlo simulation

double MonteCarloOptionPricer::calculateRho(std::string OptionType) {
    double PriceUp = 0.0;
    double PriceDown = 0.0;
    double rho = 0.0;

    double riskFreeRate = option.getRiskFreeRate();

    option.setRiskFreeRate(riskFreeRate * (1+epsilon));

    if (OptionType == "Call") {
        PriceUp = calculateOptionPrice("Call");
        // std::cout << "PriceUp: " << PriceUp << std::endl;
        // std::cout << "callPrice: " << callPrice << std::endl;

        rho = (PriceUp - callPrice) / (epsilon * riskFreeRate);
    }
    else if (OptionType == "Put") {
        PriceUp = calculateOptionPrice("Put");
        rho = (PriceUp - putPrice) / (epsilon * riskFreeRate);
    }
    else {
        std::cout << "Invalid option type" << std::endl;
    }

    option.setRiskFreeRate(riskFreeRate);
    return rho;
}
