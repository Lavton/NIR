date = read.table("ito.out")
s = date[2]
hist(s[,1], breaks = 20)
hist(s[,1], breaks = 10)
hist(s[,1], breaks = 50)
