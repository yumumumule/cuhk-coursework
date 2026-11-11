# STAT3008A Homework 3 - Problem 2

votes <- read.table("Presidential_Election_Data.txt", header = TRUE)
votes$GI <- votes$G * votes$I

full <- lm(V ~ I + D + W + GI + P + N, data = votes)
b <- coef(full)
tab <- coef(summary(full))

# (a) Substitute D = -1, 0, 1

cat("\n(a) Regression equations:\n")

for (d in c(-1, 0, 1)) {
  cat(sprintf(
    "D = %2d: Vhat = %.4f %+.4f I %+.4f W %+.4f GI %+.4f P %+.4f N\n",
    d, b["(Intercept)"] + d * b["D"],
    b["I"], b["W"], b["GI"], b["P"], b["N"]
  ))
}

cat(sprintf(
  "Interpretation: A one-unit increase in D increases the predicted vote share by %.3f percentage points, holding the other predictors fixed.\n",
  100 * b["D"]
))

# (b) Test I in the original model

cat(sprintf(
  "\n(b) I: t = %.3f, p = %.4f; %s at 5%%.\n",
  tab["I", "t value"], tab["I", "Pr(>|t|)"],
  if (tab["I", "Pr(>|t|)"] < 0.05) "significant" else "not significant"
))

# (c) Test GI in the original model

cat(sprintf(
  "\n(c) GI: t = %.3f, p = %.6f; %s at 5%%.\n",
  tab["GI", "t value"], tab["GI", "Pr(>|t|)"],
  if (tab["GI", "Pr(>|t|)"] < 0.05) "significant" else "not significant"
))

# (d) Model selection

# Check pairwise interactions individually.
# I:G is already GI; I:W equals W in this dataset.

interaction_terms <- c("I:D", "I:P", "I:N",
                       "D:W", "D:G", "D:P", "D:N",
                       "W:G", "W:P", "W:N",
                       "G:P", "G:N", "P:N")

cat("\n(d) Additional pairwise interactions:\n")

for (term in interaction_terms) {
  m <- lm(as.formula(paste(
    "V ~ I + D + W + G + P + N + GI +", term
  )), data = votes)

  cat(sprintf(
    "%s: p = %.4f, adjusted R2 = %.3f\n",
    term, coef(summary(m))[term, "Pr(>|t|)"],
    summary(m)$adj.r.squared
  ))
}

# I:N and D:N are significant individually.
# Fit a model with both interactions.

m0 <- lm(V ~ I + D + W + G + P + N +
           GI + I:N + D:N, data = votes)

cat("\nBoth I:N and D:N: p-values\n")
print(round(coef(summary(m0))[, 4], 4))

# Remove D:N

m1 <- lm(V ~ I + D + W + G + P + N +
           GI + I:N, data = votes)

cat("\nRemove D:N: p-values\n")
print(round(coef(summary(m1))[, 4], 4))

# Remove W

m2 <- lm(V ~ I + D + G + P + N +
           GI + I:N, data = votes)

cat("\nRemove W: p-values\n")
print(round(coef(summary(m2))[, 4], 4))

# Remove P

m3 <- lm(V ~ I + D + G + N +
           GI + I:N, data = votes)

cat("\nRemove P: p-values\n")
print(round(coef(summary(m3))[, 4], 4))

# Remove G to reproduce the selected empirical model.
# This relaxes strong hierarchy: GI remains even though the G main effect is removed.
# Keep m3 as a hierarchy-preserving alternative.

final <- lm(V ~ I + D + N + GI + I:N,
            data = votes)

cat("\nFinal model:\n")
print(summary(final))

f <- coef(final)

cat(sprintf(
  "Conclusion (d): Vhat = %.4f %+.4f I %+.4f D %+.4f N %+.4f GI %+.4f (I*N)\n",
  f["(Intercept)"], f["I"], f["D"],
  f["N"], f["GI"], f["I:N"]
))

cat(sprintf(
  "Adjusted R2 = %.3f; residual SE = %.4f.\n",
  summary(final)$adj.r.squared,
  summary(final)$sigma
))

# Compare fixed candidate models. This is exploratory: selection used these data.
# PRESS/LOOCV here does not re-run the interaction search in each training fold.
candidates <- list(Original = full, Hierarchical = m3, Selected = final)
comparison <- do.call(rbind, lapply(candidates, function(model) {
  c(Adjusted_R2 = summary(model)$adj.r.squared,
    Residual_SE = summary(model)$sigma,
    LOOCV_RMSE = sqrt(mean((resid(model) / (1 - hatvalues(model)))^2)))
}))
cat("\nExploratory comparison of fixed candidate models:\n")
print(round(comparison, 4))
cat("Model selection is exploratory (21 elections, multiple interaction tests).\n")
cat("Validate on later elections before claiming superior future prediction.\n")

# Residual plot

plot(fitted(final), resid(final),
     xlab = "Fitted values",
     ylab = "Residuals",
     main = "Residuals vs Fitted")

abline(h = 0, lty = 2)
