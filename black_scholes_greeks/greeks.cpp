// run command: g++ -std=c++14 ./greeks.cpp -o greeks && ./greeks 

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double e  = 2.7182818284;

enum OptionType {call = 1, put = 2};

double normal_cdf(double value){
	return 0.5 * erfc(-value * M_SQRT1_2);
}

float normal_pdf(float x, float m = 0, float s = 1){
    static const float inv_sqrt_2pi = 0.3989422804014327;
    float a = (x - m) / s;

    return inv_sqrt_2pi / s * std::exp(-0.5f * a * a);
}

vector<double> get_d(double S, double K, double T, double r, double vol){
	const double d1 = (log(S/K) + (r + pow(vol, 2)/2) * T) / (vol * pow(T, 0.5));
	cout << "d1: " << d1 << endl;
	const double d2 = d1 - vol*(pow(T,0.5));
	cout << "d2: " << d2 << endl;
	
	vector<double> res {d1, d2};

	return res;
}

double delta(double d1, OptionType type){
  if (type==call){
    return normal_cdf(d1);
  }else if(type == put){
    return normal_cdf(d1) - 1;
  } else{
    return 0.0;
  }
}

double gamma(double d1, double S, double vol, double T){
	return normal_pdf(d1) / (S * vol * sqrt(T));
}

double vega(double d1, double S, double T){
	return S * normal_pdf(d1) * sqrt(T);
}

double theta(double d1, double d2, double T, double S, double vol, double rf, double K, OptionType type){
	double multiplier = (type==call) ? -1 : 1;
	return -1 * (S * normal_pdf(d1) * vol) / 2 * sqrt(T) + multiplier * rf * K * exp(-rf*T) * normal_cdf(multiplier * -1 * d2);
}
double theta_call(double S, double K, double T, double r, double vol, double d1, double d2) {
    double term1 = - (S * vol * normal_pdf(d1)) / (2 * sqrt(T));
    double term2 = - r * K * exp(-r * T) * normal_cdf(d2);
    return term1 + term2;
}



double rho(double d2, double K, double T, double rf, OptionType type){
	double multiplier = (type==call) ? 1 : -1;
	return multiplier * K * T * exp(-rf * T) * normal_cdf(multiplier * d2);
}

int main(){
	double S = 100.0;
	double K = 100.0;
	double T = 1;
	double r = 0.05;
	double vol = 0.20;
	
	std::vector<double> prices = get_d(S,K,T,r,vol);
	double d1 = prices[0];
	double d2 = prices[1];

	cout << "Delta: " << delta(d1, OptionType::call) << endl;
	cout << "Gamma: " << gamma(d1, S, vol, T) << endl;
	cout << "Vega: " << vega(d1, S, T)/100 << endl;
	// cout << "Theta: " << theta(d1, d2, T, S, vol, r, K, OptionType::call) << endl;
	cout << "Theta call: " << theta_call(S, K, T, r, vol, d1, d2) << endl;
	cout << "Rho: " << rho(d2, K, T, r, OptionType::call)/100 << endl;

	return 0;
}



