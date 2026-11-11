# Homework 3 - Indicator Variables, Interactions, and Transformations

**STAT3008A | The Chinese University of Hong Kong**

This assignment covers categorical predictors, interaction terms, nested-model
tests, model selection, and response transformations using R. The scripts cover
Problems 2, 3, 5, and 6, which require R. Problems 1 and 4 are written exercises.

## Problem 2 - Presidential Election Regression

Analyze Democratic vote share in 21 U.S. presidential elections from 1916 to 1996.

**Tasks:**
- Fit the specified multiple regression model and interpret the incumbent-candidate coefficient.
- Test the incumbent-party indicator and the growth-by-party interaction.
- Explore additional pairwise interactions and simplify the candidate model.
- Compare the original, hierarchical, and selected models using adjusted R-squared,
  residual standard error, and exploratory leave-one-out prediction error.
- Examine residuals versus fitted values for the selected model.

**Code:** `Problem2.R`

The selected empirical model retains `GI` after removing the `G` main effect,
so it relaxes strong hierarchy. The script also reports a candidate retaining
`G`. Interaction screening and model selection use the same small dataset;
the reported leave-one-out errors evaluate fixed formulas without repeating
selection in each fold. They do not establish performance on future elections.

## Problem 3 - Categorical Predictors and a Partial F-Test

Replace the three-level incumbent-candidate variable with two indicator variables.

**Tasks:**
- Write fitted equations for the three categories and interpret the indicators.
- Show that the single-coefficient model is obtained when the indicator coefficients sum to zero.
- Test this restriction by comparing the nested regression models.

**Code:** `Problem3.R`

## Problem 5 - Logit Response Transformation

Compare the original vote proportion with its logit transformation using the
predictors from Problem 2.

**Tasks:**
- Compare standardized residuals versus fitted values and normal Q-Q plots.
- Fit the transformed-response model and derive its inverse logistic relationship.
- Calculate inverse-logit fitted vote proportions with `plogis()`.

**Code:** `Problem5.R`

## Problem 6 - Transformation with Two Indicators

Repeat Problem 5 using the indicator-variable model from Problem 3.

**Tasks:**
- Compare diagnostics before and after transforming the response.
- Derive the logistic relationship on the original response scale.
- Compare the transformed models from Problems 5 and 6 with a partial F-test.

**Code:** `Problem6.R`

The transformed models in Problems 5 and 6 use ordinary least squares on
`log(V / (1 - V))`. Inverse-transforming a fitted linear predictor does not,
in general, estimate the conditional mean of `V` without accounting for the error.

## Dataset

**File:** `Presidential_Election_Data.txt` (provided with the assignment;
the assignment credits Professor Ray Fair of Yale University).

| Variable | Description |
| --- | --- |
| `Year` | Election year |
| `V` | Democratic share of the two-party presidential vote |
| `I` | Incumbent-party indicator: 1 for Democratic, -1 for Republican |
| `D` | Incumbent candidate running: 1 for Democratic, -1 for Republican, 0 otherwise |
| `W` | War indicator: 1 for 1920, 1944, and 1948; 0 otherwise |
| `G` | Real per-capita GDP growth in the first three quarters of the election year |
| `P` | Absolute GDP-deflator growth in the first 15 quarters of the administration |
| `N` | Number of those 15 quarters with real per-capita GNP growth above 3.2% |

Growth rates are annual rates in percentage points. Each script constructs
`GI = G * I`; Problems 3 and 6 also construct the two indicators.

## Files

| File | Description |
| --- | --- |
| `Problem2.R` | Interaction screening, model comparison, and residual plot |
| `Problem3.R` | Indicator coding and nested-model test |
| `Problem5.R` | Logit transformation with the original predictors |
| `Problem6.R` | Logit transformation with two indicators |
| `Presidential_Election_Data.txt` | Presidential election data, 1916-1996 |

## Running the Code

Only base R is required. Run the scripts individually in R or RStudio with
the working directory set to this HW3 folder:

```r
source("Problem2.R")
source("Problem3.R")
source("Problem5.R")
source("Problem6.R")
```

Alternatively, run each script with `Rscript Problem2.R`, and similarly for
the other files, from this folder. Numerical results print to the console;
diagnostic plots appear in the R graphics device. In noninteractive command-line
sessions, R normally writes the plots to `Rplots.pdf` in the working directory.
