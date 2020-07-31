# Calculate Integrated Information Meaures for the Ising model
## Introduction
In order to calculate the Integrated Information Measures ϕ_G

## Requirements

1. python3
	* numpy
	* scipy
	* random

2. c++ compiler

## How to use

1. Create a list of the stationary distributions with Boltzmann.py
	* Number of nodes: nodes
	* Weight matrix W, default is a random matrix
	* Path where the document with the stationary distributions should be stored: path
	* Directly calculte the integrated information measure: informint- works only for nodes = 2,3
	* Number of times beta is increased: num_steps 
	* Starting value of beta: beta_start
	* Value by which beta is increased: beta_diff

2. Calculate: Mutual Information, Stochastic Interaction, Geometric Integrated Information and Causal Information Integration
	1. Adjust path and number of nodes in main.cpp
	2. Conditions for Causal Information Integration and Geometric Integrated Information
	3. Execute the main.cpp program, on linux
		```console
			g++ main.cpp ProbabilityDist.cpp emIterate.cpp Test.cpp -o main
			./main
		```
	4. Output can be copy pasted to matplotlib

