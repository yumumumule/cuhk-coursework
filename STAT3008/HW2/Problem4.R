data <- read.csv("Supervisor.txt", header = TRUE, sep = "\t")

#(a)
cat("(a) H0: beta1 = beta3 = 0.5\n")
cat("H1: At least one coefficient differs from 0.5\n\n")

data$Z <- data$Y - 0.5*data$X1 - 0.5*data$X3

rm <- lm(Z ~ 1, data = data)
fm <- lm(Z ~ X1 + X3, data = data)

result <- anova(rm, fm)
print(result)

F <- result$F[2]
p <- result[["Pr(>F)"]][2]

cat(sprintf("\nF = %.3f, p = %.3f\n", F, p))

if (p < 0.05) {
  cat("Reject H0 at the 5% significance level.\n")
} else {
  cat("Fail to reject H0 at the 5% significance level.\n")
}

#(b)
cat("(b) H0: beta1 = beta3 = 0.5\n")
cat("H1: At least one coefficient differs from 0.5\n\n")

data$Z <- data$Y - 0.5*data$X1 - 0.5*data$X3

rm <- lm(Z ~ X2, data = data)
fm <- lm(Z ~ X1 + X2 + X3, data = data)

result <- anova(rm, fm)
print(result)

F <- result$F[2]
p <- result[["Pr(>F)"]][2]

cat(sprintf("\nF = %.3f, p = %.3f\n", F, p))

if (p < 0.05) {
  cat("Reject H0 at the 5% significance level.\n")
} else {
  cat("Fail to reject H0 at the 5% significance level.\n")
}
