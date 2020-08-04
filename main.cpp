#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

double monte_carlo_call_price(int N_sims, int N_time_steps, double S, double X, double r,double T, double sigma) {
    double time_step { T/N_time_steps};
    double S_0 {S};
    double sum_call_value{};
    std::default_random_engine generator;
    std::normal_distribution<double> norm_dist(0,1.0);
    for (int i=0; i<N_sims; i++) {
        S=S_0; //reset the stock price to the price at t=0 
        for(int j=0; j<N_time_steps;j++ ){
            S = S * exp((r-0.5*sigma*sigma)*time_step + sigma*sqrt(time_step)*norm_dist(generator));
        }
        sum_call_value+=std::max(S - S_0, 0.0); // add the value of the call under that simulation of the stock price
    }
    // The value of the option is the present value of the expectation under the risk-neutral random walk
    // an approximation for this is the average value of a call found from our simulations of the stock prices
    // under the risk-neutral random walk.
  return (sum_call_value / N_sims) * exp(-r*T);
}

int main()
{
    double S { 100};  //  price of underlying spot
    double X {100};  // strike price
    double r {0.05};   // risk-free rate 
    double T {1};    // time until expiry
    double sigma {0.2};  //volatility
    double N_sims {10001}; // the number of simulation
    double N_time_steps{100}; // the number of time_steps in each path
    
    double call_price {monte_carlo_call_price(N_sims,N_time_steps,S,X,r,T,sigma)};
    std::cout << "Call price is: " << call_price <<std::endl;
    

	return 0;
}
