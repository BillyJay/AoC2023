import string


file = open("input4.txt")

wins = []
for line in file:
	win_list = ((line.split(':')[1]).split('|')[0]).split(' ')
	got_list = ((line.split(':')[1]).split('|')[1]).split(' ')
	win_numbers = []
	got_numbers = []
	for el in win_list:
		if(el != ''):
			win_numbers.append(int(el))
	for el in got_list:
		if(el != ''):
			got_numbers.append(int(el))
	found = 0
	for el in win_numbers:
		if (el in got_numbers):
			found += 1
	wins.append(found)
ans = 0
dim = len(wins)
f = [1 for _ in wins]
for i in range(len(wins)):
	for j in range(i+1, min(dim, i+1+wins[i])):
		f[j] += f[i]

ans = sum(f)
print(ans)