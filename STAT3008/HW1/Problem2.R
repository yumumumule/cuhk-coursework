x <- c(240,243,250,254,264,279,284,285,290,298,302,310,312,315,322,337,348,384,386,520)
mu0  <- 200
alpha <- 0.02

t.test(x, mu = mu0, alternative = "two.sided", conf.level = 1 - alpha)
