# LTCG-Tax-Comparison

## Overview
This project compares two Long-Term Capital Gains (LTCG) taxation schemes on real estate investments in India:
1. **Pre-2024 Scheme:** 20% tax on inflation-adjusted gains.
2. **Post-2024 Scheme:** 12.5% tax without inflation adjustment.

The program calculates the estimated selling price and LTCG tax based on user inputs, such as the year of sale and initial property cost.

## Problem Statement
Given a property purchase year, initial cost, and annual inflation/property appreciation rates (from a CSV file spanning 2001-2030), the program:
1. Calculates the estimated selling price.
2. Computes LTCG tax for both pre-2024 and post-2024 schemes.
3. Compares the two taxation methods to determine which results in higher taxes.

## Features
- User-friendly interface to input selling year.
- Dynamic computation based on CSV data.
- Clear comparison of both taxation schemes.

## Prerequisites
- C Compiler
- Make Utility
- CSV File containing annual inflation and property rates (2001–2030).

## How to execute?

1. `cd ./MT24119` to change the directory  
2. `make` to build the file and compiled outputs will be stored in the same directory  
3. `./Q1_optimised` or `./Q2_optimised` to execute the desired optimised build  

## References
1. File management: [CSV File Management Using C](https://www.geeksforgeeks.org/csv-file-management-using-c/)
2. Inflation adjustment formula: [Investopedia - Inflation Adjusted Return](https://www.investopedia.com/terms/i/inflation_adjusted_return.asp)