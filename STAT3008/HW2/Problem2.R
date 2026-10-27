data <- read.csv("Examination_Data.txt", header = TRUE, sep = "\t")
F <- data$F
P1 <- data$P1
P2 <- data$P2

#(a)
md1 <- lm(F~P1)
md2 <- lm(F~P2)
md3 <- lm(F~P1 + P2)

cat(sprintf("Model 1: F = %.3f + %.3f P1\n",
            coef(md1)[1], coef(md1)[2]))

cat(sprintf("Model 2: F = %.3f + %.3f P2\n",
            coef(md2)[1], coef(md2)[2]))

cat(sprintf("Model 3: F = %.3f + %.3f P1 + %.3f P2\n",
            coef(md3)[1], coef(md3)[2], coef(md3)[3]))

#(b)
cat("\n(b) H0: beta0 = 0, H1: beta0 != 0\n")

for (m in list(md1, md2, md3)) {
  t <- summary(m)$coefficients[1, 3]
  p <- summary(m)$coefficients[1, 4]
  cat(sprintf("t = %.3f, p = %.3f: %s\n",
              t, p, ifelse(p < 0.05, "Reject H0", "Fail to reject H0")))
}


#(c)
r1 <- summary(md1)$r.squared
r2 <- summary(md2)$r.squared

cat(sprintf("R² of Model 1 = %.3f\n", r1))
cat(sprintf("R² of Model 2 = %.3f\n", r2))

if (r1 > r2) {
  cat("P1 is a better predictor of F because it has a higher R².\n")
} else {
  cat("P2 is a better predictor of F because it has a higher R².\n")
}

#(d)
cat("Adjusted R²:\n")
cat("Model 1:", summary(md1)$adj.r.squared, "\n")
cat("Model 2:", summary(md2)$adj.r.squared, "\n")
cat("Model 3:", summary(md3)$adj.r.squared, "\n")

cat("Model 3 is preferred because it has the highest adjusted R².\n")

newdata <- data.frame(P1 = 78, P2 = 85)
result <- predict(md3, newdata, interval = "prediction")

print(result)

