#include <cmath>
#include <iostream>
#include <algorithm>
#include <chrono>

// Run command: g++ -std=c++11 euro_option.cpp -o euro_option && ./euro_option

const double e = 2.7182818284;
const double K = 100; // Strike price
const double T = 1; // Time to maturity (years)
const double S = 100; // Current price of the underlying stock
const double r = 0.06; // Risk-free rate
const int N = 10000; // Number of time steps
const double sigma = 0.16509;

enum option_type{call = 1, put = 0}; 
option_type type = call; // Type of option

int main(){
	std::cout << "Pricing a european option\n";
	
	// For tracking performance
	auto start = std::chrono::high_resolution_clock::now();

	// Precompute constants
	const double dt = T/N; // Time step
	const double u = pow(e, (sigma * sqrt(dt))); //Factor change of upstate
	const double d = 1/u; //Factor change of downstate

	const double disc = pow(e, (-r*dt)); // Discount factor
	const double p = (pow(e, (r*dt)) - d) / (u - d); // Probability of upstate

	std::cout << "dt: " << dt << std::endl;
	std::cout << "u: " << u << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "disc: " << disc << std::endl;
	std::cout << "p: " << p << std::endl;

	// Initialize stock prices at maturity
	double St[N+1];
	St[0] = S * pow(d,N);
	// std::cout << St[0] << "\n";
	for(int j=1; j<N+1; j++){
		St[j] = St[j-1]*(u/d);
		// std::cout << St[j] << "\n";
	}

	// Get options value at last timestep
	double C[N+1];
	for(int j=0; j<N+1; j++){
		if(type == 1){
			// Call
			C[j] = std::max(0.0, St[j]-K);
		}else if(type==0){
			// Put
			C[j] = std::max(0.0, K-St[j]);
		}
	}

	for(int j=0; j<N; j++){
		// std::cout << "Time step: " << j+1 << "/" << N << "\n";
		for(int i=0; i < (N+1)-j-1; i++){
			C[i] = (C[i] * (1-p) + C[i+1] * p) * disc;
		}
	}

	std::cout << "Present option value: " << C[0] << "\n";

	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
}