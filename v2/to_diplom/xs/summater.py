data = [[float(el) for el in line.strip().split()] for line in open("f_x.dat")]
for i in range(len(data)):
	data[i] = [data[i][0]]+[sum(data[i][1:])]
f = open('s.txt', 'w')
for line in data:
	f.write(" ".join(((str(el) for el in line)))+"\n")
