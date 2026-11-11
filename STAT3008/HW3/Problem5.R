
# STAT3008A Homework 3 - Problem 5

votes <- read.table("Presidential_Election_Data.txt", header = TRUE)
votes$GI <- votes$G * votes$I
# The logit is defined only for proportions strictly between 0 and 1.
stopifnot(all(is.finite(votes$V)), all(votes$V > 0 & votes$V < 1))
votes$Y <- qlogis(votes$V)

# (a) Compare the two models

mV <- lm(V ~ I + D + W + GI + P + N,
         data = votes)
mY <- lm(Y ~ I + D + W + GI + P + N,
         data = votes)

# Restore the previous graphics layout after drawing the diagnostics.
old_mfrow <- par("mfrow")
par(mfrow = c(2, 2))

plot(fitted(mV), rstandard(mV),
     main = "V: Residuals vs Fitted",
     xlab = "Fitted values",
     ylab = "Standardized residuals")
abline(h = 0, lty = 2)

qqnorm(rstandard(mV), main = "V: Normal Q-Q")
qqline(rstandard(mV))

plot(fitted(mY), rstandard(mY),
     main = "Y: Residuals vs Fitted",
     xlab = "Fitted values",
     ylab = "Standardized residuals")
abline(h = 0, lty = 2)

qqnorm(rstandard(mY), main = "Y: Normal Q-Q")
qqline(rstandard(mY))

par(mfrow = old_mfrow)

cat("(a) The residual plots are very similar for V and Y.\n")
cat("The logit transformation does not clearly improve the assumptions.\n")

# (b) Back-transform the model

cat("\n(b) Coefficients of the fitted Y model:\n")
print(round(coef(mY), 6))

cat("The model is log(V/(1-V)) = eta, where\n")
cat("eta = beta0 + beta1*I + beta2*D + beta3*W + beta4*(G*I) + beta5*P + beta6*N + error.\n")
cat("Therefore, V = exp(eta)/(1+exp(eta)) = 1/(1+exp(-eta)).\n")

# Inverse-transform the fitted linear predictor (without the random error).
# This is not generally E[V | X], because inverse transformation is nonlinear.
cat("\nInverse-logit fitted vote proportions:\n")
print(data.frame(Year = votes$Year, Observed_V = votes$V,
                 Fitted_V = plogis(fitted(mY))))
