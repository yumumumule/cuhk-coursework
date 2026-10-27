dat <- read.table("Heights_of_husband_and_wife.txt", header = TRUE)

x <- dat$Husband
y <- dat$Wife

# (a)
cov_xy <- cov(x, y)
cat("(a) Covariance between husband and wife heights =", cov_xy, "\n\n")

# (b)
x_in <- x / 2.54
y_in <- y / 2.54

cov_in <- cov(x_in, y_in)
cat("(b) Covariance in inches =", cov_in, "\n\n")

# (c)
cor_xy <- cor(x, y)
cat("(c) Correlation between husband and wife heights =", cor_xy, "\n\n")

# (d)
y_new <- x - 5
cor_new <- cor(x, y_new)

cat("(d) Correlation between Husband and Husband - 5 =", cor_new, "\n\n")

# (e)
model <- lm(Wife ~ Husband, data = dat)

b0 <- coef(model)[1]
b1 <- coef(model)[2]

cat("(e) Fitted regression model:\n")
cat("Wife_hat =", round(b0, 4), "+", round(b1, 4), "* Husband\n\n")

cat("Regression summary:\n")
print(summary(model))

# (f)
alpha <- 0.05
p_slope <- summary(model)$coefficients["Husband", "Pr(>|t|)"]

cat("\n(f) Test for slope:\n")
cat("H0: beta1 = 0\n")
cat("H1: beta1 != 0\n")
cat("p-value =", p_slope, "\n")

if (p_slope < alpha) {
  cat("Reject H0.\n")
  cat("There is sufficient evidence of a linear relationship between husbands' and wives' heights.\n")
} else {
  cat("Fail to reject H0.\n")
  cat("There is insufficient evidence of a linear relationship between husbands' and wives' heights.\n")
}

# (g)
p_intercept <- summary(model)$coefficients["(Intercept)", "Pr(>|t|)"]

cat("\n(g) Test for intercept:\n")
cat("H0: beta0 = 0\n")
cat("H1: beta0 != 0\n")
cat("p-value =", p_intercept, "\n")

if (p_intercept < alpha) {
  cat("Reject H0.\n")
  cat("There is sufficient evidence that the intercept is different from 0.\n")
} else {
  cat("Fail to reject H0.\n")
  cat("There is insufficient evidence that the intercept is different from 0.\n")
}