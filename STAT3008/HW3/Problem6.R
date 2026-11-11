
# STAT3008A Homework 3 - Problem 6

votes <- read.table("Presidential_Election_Data.txt", header = TRUE)

votes$GI <- votes$G * votes$I
votes$D1 <- as.integer(votes$D == 1)
votes$D2 <- as.integer(votes$D == -1)
# The logit is defined only for proportions strictly between 0 and 1.
stopifnot(all(is.finite(votes$V)), all(votes$V > 0 & votes$V < 1))
votes$Y <- qlogis(votes$V)

# (a) Compare V and Y

m6V <- lm(V ~ I + D1 + D2 + W + GI + P + N,
          data = votes)

m6Y <- lm(Y ~ I + D1 + D2 + W + GI + P + N,
          data = votes)

cat("\n(a) Coefficients of transformed model:\n")
print(round(coef(m6Y), 6))

# Restore the previous graphics layout after drawing the diagnostics.
old_mfrow <- par("mfrow")
par(mfrow = c(2, 2))

plot(fitted(m6V), rstandard(m6V),
     main = "V: Residuals vs Fitted",
     xlab = "Fitted values",
     ylab = "Standardized residuals")
abline(h = 0, lty = 2)

qqnorm(rstandard(m6V), main = "V: Normal Q-Q")
qqline(rstandard(m6V))

plot(fitted(m6Y), rstandard(m6Y),
     main = "Y: Residuals vs Fitted",
     xlab = "Fitted values",
     ylab = "Standardized residuals")
abline(h = 0, lty = 2)

qqnorm(rstandard(m6Y), main = "Y: Normal Q-Q")
qqline(rstandard(m6Y))

par(mfrow = old_mfrow)

cat("(a) The residual plots are similar; the logit transformation does not clearly improve the assumptions.\n")

# (b) Logistic function

b <- coef(m6Y)

cat("\n(b) Fitted logit model:\n")
cat(sprintf(
  "Yhat = %.6f %+.6f I %+.6f D1 %+.6f D2 %+.6f W %+.6f GI %+.6f P %+.6f N\n",
  b[1], b["I"], b["D1"], b["D2"],
  b["W"], b["GI"], b["P"], b["N"]
))

cat("V = exp(eta)/(1 + exp(eta)), where eta is the linear predictor plus error.\n")

# Comparison with Problem 5

m5Y <- lm(Y ~ I + D + W + GI + P + N,
          data = votes)

test <- anova(m5Y, m6Y)

cat("\nComparison with Problem 5:\n")

cat(sprintf(
  "Adjusted R2: Problem 5 = %.3f, Problem 6 = %.3f\n",
  summary(m5Y)$adj.r.squared,
  summary(m6Y)$adj.r.squared
))

cat(sprintf(
  "Residual SE: Problem 5 = %.4f, Problem 6 = %.4f\n",
  summary(m5Y)$sigma, summary(m6Y)$sigma
))

cat(sprintf(
  "Partial F-test: F(%d, %d) = %.3f, p = %.3f\n",
  test[2, "Df"], df.residual(m6Y),
  test[2, "F"], test[2, "Pr(>F)"]
))

if (test[2, "Pr(>F)"] < 0.05) {
  cat("Conclusion: The two-indicator model significantly improves the fit at 5%.\n")
} else {
  cat("Conclusion: No significant improvement at 5%; prefer the simpler Problem 5 model.\n")
}

# Inverse-transform the fitted linear predictor (without the random error).
# This is not generally E[V | X], because inverse transformation is nonlinear.
cat("\nInverse-logit fitted vote proportions:\n")
print(data.frame(Year = votes$Year, Observed_V = votes$V,
                 Fitted_V = plogis(fitted(m6Y))))
