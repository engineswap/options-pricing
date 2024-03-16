#include <cmath>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// Run command: g++ -std=c++11 gbm_euro.cpp -o gbm_euro && ./gbm_euro

const double e = 2.7182818284;
const double K = 100; // Strike price
const double T = 1; // Time to maturity (years)
const double S = 100; // Current price of the underlying stock
const double rf = 0.05; // Risk-free rate
const int N = 1000; // Number of time steps
const double sigma = 0.2; // vol
const int M = 5000; // number of simulations

enum option_type{call = 1, put = 0}; 
option_type type = call; // Type of option

int main(){
	auto start = std::chrono::high_resolution_clock::now(); // To track runtime

	double dt = T/N; // discrete time step
	// Generate array of discrete times until expiration
	double times[N+1];
	for(int i=0; i < (N+1); i++){
		times[i] = i*dt;
	}

	// Set up normal distribution
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // Seed for RNG
	default_random_engine generator(seed);
	normal_distribution<double> normal_dist{0.0, sqrt(dt)};

	double payoff_sum = 0;
	for (int i=0; i<M; i++){
		// cout << "Running simulation " << i+1 << endl;
		// Noise term
		double B[N];
		for(int i=0; i<N; i++){
			B[i] = normal_dist(generator);
		}
		// Prices 
		double St[N];
		St[0] = S;
		for(int i=1; i<N; i++){
			double ret = pow(e, (rf - pow(sigma,2)/2) * dt + sigma * B[i]); // return
			St[i] = St[i-1] * ret;
		}

		// Calculate payoff
		double payoff;
		if (type==1){ // call option
			payoff = std::max(0.0, St[N-1]-K);
		}else if (type==0){ // put option
			payoff = std::max(0.0, K-St[N-1]);
		}
		payoff_sum += payoff;
	}
	// discount payoff
	
	double payoff_pv = (payoff_sum / M) * pow(e, -rf * T);
	
	cout << "Present value: $" << payoff_pv << endl;
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Time taken for simulation: " << duration.count() << " ms" << std::endl;
}