num=[0,1,0,0,0]
for x in range(2,5):
	num[x]=num[x-1]+num[x-2]
	print (num)
num.append(num[-1]+num[-2])
print (num)
num.pop(2)
print (num)
print (sum(num))