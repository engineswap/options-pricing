Some of my observations:

Black scholes price: 9.715
Binomial tree (N=100,000): 9.71501
Time taken: 2 minutes

Parameters vs price
-------------------
- vol,rf,time to maturity are all positively correlated with the value of an option.
- Moneyness is negatively correlated with the value of the option.
- Decreasing timesteps will decrease the value, presumably because vol decreases, but increasing it a ton just makes it more continuous and closer to B.S. value.

One thing i've thought about in BSM pricing, the return distribution of the underlying is assumed to be log normal. Of course returns have fatter tails so 
farther from moneyness = 1 will be underpriced (part of the reason for volatility smile, which is a creepy concept to think about). But on top of that, its observed that the left tail of returns is bigger than the right, leading me to think that OTM puts in particular will be underpriced by BSM, GBM monte carlo, and binomial tree that we did in class.

