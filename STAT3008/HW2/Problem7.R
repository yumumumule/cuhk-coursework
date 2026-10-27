
# Problem 7: Computer Repair

data <- read.csv("Computer_Repair.txt",
                 header = TRUE, sep = "\t")

# (a) Fit a simple linear regression model
md <- lm(Minutes ~ Units, data = data)

cat("(a) Fitted Model\n")
cat(sprintf("Minutes = %.3f %+.3f Units\n",
            coef(md)[1], coef(md)[2]))
cat(sprintf("R-squared = %.3f\n", summary(md)$r.squared))

# (b) Regression diagnostics
r <- rstandard(md)
h <- hatvalues(md)
cook <- cooks.distance(md)
n <- nrow(data)
p <- length(coef(md)) - 1

outlier_cutoff <- 3
leverage_cutoff <- 2 * (p + 1) / n
cook_cutoff <- 1

show_points <- function(indices) {
  if (length(indices) == 0) "None"
  else paste(indices, collapse = ", ")
}

cat("\n(b) Regression Diagnostics\n")

cat("Response outliers (|r_i| >= 3): ",
    show_points(which(abs(r) >= outlier_cutoff)),
    "\n", sep = "")

cat(sprintf("High-leverage cutoff = %.3f\n",
            leverage_cutoff))

cat("High-leverage points: ",
    show_points(which(h >= leverage_cutoff)),
    "\n", sep = "")

cat("Influential points (Cook's D > 1): ",
    show_points(which(cook > cook_cutoff)),
    "\n", sep = "")

cat(sprintf("Maximum Cook's distance = %.3f (observation %d)\n",
            max(cook), which.max(cook)))

# Six diagnostic plots
par(mfrow = c(2, 3))

# 1. Scatter Plot
plot(data$Units, data$Minutes,
     main = "Minutes vs Units",
     xlab = "Units", ylab = "Minutes")
abline(md, col = "red", lwd = 2)

# 2. Standardized Residuals vs Units
plot(data$Units, r,
     main = "Residuals vs Units",
     xlab = "Units",
     ylab = "Standardized Residuals")
abline(h = 0, col = "red")

# 3. Normal Q-Q Plot
qqnorm(r, main = "Normal Q-Q Plot")
qqline(r, col = "red")

# 4. Standardized Residual Index Plot
plot(r, type = "h",
     ylim = range(c(r, -3, 3)),
     main = "Residual Index Plot",
     xlab = "Observation",
     ylab = "Standardized Residuals")
abline(h = 0, col = "red")
abline(h = c(-3, 3), col = "grey", lty = 2)

# 5. Leverage Index Plot
plot(h, type = "h",
     main = "Leverage Index Plot",
     xlab = "Observation", ylab = "Leverage")
abline(h = leverage_cutoff, col = "red", lty = 2)

# 6. Cook's Distance Plot
plot(cook, type = "h",
     ylim = c(0, max(1.05, max(cook))),
     main = "Cook's Distance",
     xlab = "Observation", ylab = "Cook's Distance")
abline(h = cook_cutoff, col = "red", lty = 2)

par(mfrow = c(1, 1))

# Conclusions
cat("\nConclusions\n")

cat("Linearity: Violated. Residuals show a clear curved pattern.\n")

cat("Normality: Reasonably satisfied. The Q-Q plot is approximately linear.\n")

cat("Constant variance: Inconclusive because of the strong nonlinear pattern.\n")

cat("Independence: Cannot be verified; row order is sorted by Units, not known sampling order.\n")

cat("No response outliers or influential observations exceed the selected cutoffs.\n")

cat("Observation 24 has high leverage and the largest Cook's distance.\n")

cat("Overall: The main violation is linearity; a nonlinear model may be more appropriate.\n")

