// run command: g++ ./greeks.cpp -o greeks && ./greeks 

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double e  = 2.7182818284;

enum option_type {call = 1, put = 2};

double normal_cdf(double value){
	return 0.5 * erfc(-value * M_SQRT1_2);
}

vector<double> price_option(double S, double K, double T, double r, double vol){
	const double d1 = (log(S/K) + (r + pow(vol, 2)/2) * T) / (vol * pow(T, 0.5));
	//std::cout << "d1: " << d1 << "\n";
	const double d2 = d1 - vol*(pow(T,0.5));
	//std::cout << "d2: " << d2 << "\n";
    
  vector<double> res = {d1, d2};

	return res;
}

double delta(double d1, option_type type){
  if (type==call){
    return normal_cdf(d1);
  }else if(type == put){
    return normal_cdf(d1) - 1;
  } else{
    return 0.0
  }
}

int main(){
	std::cout << "Please enter the stock price (S): $";
	double S;
	std::cin >> S;
	
	std::cout << "Please enter the strike price (K): $";
	double K;
	std::cin >> K;

	std::cout << "Please enter the time until expiration time in years (T): ";
	double T;
	std::cin >> T;

	std::cout << "Please enter the annualized risk-free rate as a decimal (r): ";
	double r;
	std::cin >> r;

	std::cout << "Please enter the volatility of the stock (vol): ";
	double vol;
	std::cin >> vol;
	
	std::vector<double> prices = price_option(S,K,T,r,vol);
	double d1 = prices[0];
	double d2 = prices[1];

  cout << delta(d1) << endl;

	return 0;
}



