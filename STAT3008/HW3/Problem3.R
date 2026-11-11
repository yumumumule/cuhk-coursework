# STAT3008A Homework 3 - Problem 3

votes <- read.table("Presidential_Election_Data.txt", header = TRUE)
votes$GI <- votes$G * votes$I
votes$D1 <- as.integer(votes$D == 1)
votes$D2 <- as.integer(votes$D == -1)

m3 <- lm(V ~ I + D1 + D2 + W + GI + P + N, data = votes)
b <- coef(m3)

# (a) Substitute D1 and D2 into the fitted equation
cat("\n(a) Fitted regression equations:\n")

for (d in c(-1, 0, 1)) {
  intercept <- b["(Intercept)"] +
    b["D1"] * (d == 1) + b["D2"] * (d == -1)

  cat(sprintf(
    "D = %2d: Vhat = %.6f %+.6f I %+.6f W %+.6f GI %+.6f P %+.6f N\n",
    d, intercept, b["I"], b["W"], b["GI"], b["P"], b["N"]
  ))
}

cat(sprintf(
  "Interpretation: D1 changes predicted vote share by %+.3f percentage points; D2 by %+.3f percentage points (compared with D = 0, other regressors fixed).\n",
  100 * b["D1"], 100 * b["D2"]
))

# (b) Algebraic relationship
cat("\n(b) If alpha1 = -alpha2, then alpha1*D1 + alpha2*D2 = alpha1*(D1-D2) = alpha1*D.\n")
cat("Thus Problem 2 is a restricted version of Problem 3.\n")

# (c) Partial F-test for alpha1 + alpha2 = 0
m2 <- lm(V ~ I + D + W + GI + P + N, data = votes)
test <- anova(m2, m3)

cat("\n(c) H0: alpha1 + alpha2 = 0; H1: alpha1 + alpha2 != 0.\n")
cat(sprintf(
  "Partial F-test: F(%d, %d) = %.3f, p = %.3f. %s at 5%%.\n",
  test[2, "Df"], df.residual(m3),
  test[2, "F"], test[2, "Pr(>F)"],
  if (test[2, "Pr(>F)"] < 0.05) "Reject H0" else "Do not reject H0"
))
