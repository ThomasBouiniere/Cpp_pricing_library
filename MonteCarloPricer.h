#include "Option.h"
#include <iostream>


class MonteCarloOptionPricer {
public:
    MonteCarloOptionPricer(Option& option, int numSimulations, double epsilon = 0.001);

    double calculateOptionPrice(std::string OptionType);
    double calculateDelta(std::string OptionType);
    double calculateGamma();
    double calculateVega();
    double calculateTheta(std::string OptionType);
    double calculateRho(std::string OptionType);

    double callPrice;
    double putPrice;

private:
    Option& option;
    int numSimulations;
    double epsilon;
    std::string OptionType;
    


    double gaussian_box_muller() const;

};
