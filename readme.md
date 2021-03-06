# Calculate Integrated Information Meaures for the Ising model
## Introduction

This repository consists of the code used to generate the results presented in https://www.mdpi.com/1099-4300/22/10/1107.
Integrated Information Measures like the ones presented in [1],[2] or [3] are calculated by computing the KL-divergence between the initial distribution and one corresponding to a "partial" or "split" system Q.

![Alt text](form2.png "Title")

This repository provides the possibility to create initial distributions systematically by fixing a weight matrix W = (v_ij) and increasing the inverse temperature β of an Ising model:

![Alt text](form1.png "Title")

After caclulating the distributions, main.cpp allows the computation of the measures  Φ_G,  Φ_SI,  Φ_I and the new measure  Φ_CII.

## Requirements

1. python3
	* numpy
	* scipy
	* random

2. c++ compiler

## How to use

1. Create a list of the stationary distributions with Boltzmann.py <br />
	Parameters:
	* nodes: 	Number of nodes
	* W:	 	Weight matrix, default is a random matrix
	* path:  	Path where the document with the stationary distributions should be stored
	* informint: 	Directly calculte the integrated information measure Φ_CIS- works only for nodes = 2,3
	* num_steps:	Number of times beta is increased 
	* beta_start:	Starting value of beta
	* beta_diff: 	Value by which beta is increased

2. Calculate: Mutual Information, Stochastic Interaction, Geometric Integrated Information and Causal Information Integration
	1. Adjust path and number of nodes in main.cpp
	2. Conditions for Causal Information Integration and Geometric Integrated Information
	3. Execute the main.cpp program, on linux
		```console
			g++ main.cpp ProbabilityDist.cpp emIterate.cpp Test.cpp -o main
			./main
		```
	4. Output can be copy pasted to plot.py

## References
[1] Amari, S.; Tsuchiya, N.; Oizumi, M. Geometry of Information Integration. In Information Geometry and Its
Applications; Ay, N.; Gibilisco, P.; Matúš, F. Eds.; Springer International Publishing, 2018; pp. 3–17.

[2] Kanwal, M.S.; Grochow J.A.; Ay, N. Comparing Information-Theoretic Measures of Complexity in Boltzmann
Machines. Entropy 2017, 19, 310–326

[3] Oizumi, M.; Tsuchiya, N.; and Amari, S. Unified framework for information integration based on information
geometry. PNAS 2016, 113,14817–14822.



