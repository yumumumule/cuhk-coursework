# Homework 1 — Applied Regression Analysis

**STAT3008A | The Chinese University of Hong Kong**

This assignment covers statistical hypothesis testing, covariance, correlation, and simple linear regression using R.

## Problem 2 — One-Sample t-Test

Given 20 independent observations from a normal distribution, test whether the population mean differs from 200 at the 2% significance level.

**Tasks:**
- Calculate the sample mean and standard deviation.
- Perform a two-sided one-sample t-test.
- Verify the result using R's `t.test()` function.

**Code:** `Problem2.R`

## Problem 9 — Heights of Husbands and Wives

Analyze the relationship between husbands' and wives' heights using a dataset of newly married couples.

**Tasks:**
- Calculate covariance and Pearson correlation between husbands' and wives' heights.
- Examine the effects of unit conversion and a hypothetical perfect linear relationship.
- Fit a simple linear regression model with the wife's height as the response and the husband's height as the predictor.
- Test the significance of the regression slope and intercept at the 5% level.

**Code:** `Problem9.R`  
**Dataset:** `Heights_of_husband_and_wife.txt`

## Files

| File | Description |
|---|---|
| `Problem2.R` | One-sample t-test |
| `Problem9.R` | Covariance, correlation, and linear regression |
| `Heights_of_husband_and_wife.txt` | Dataset for Problem 9 |

## Running the Code

The scripts are written in R. Run them in R or RStudio, with the working directory set to this folder.

For Problem 9, ensure that the dataset is available at the path specified in the script.
