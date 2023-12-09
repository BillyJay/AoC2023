import string


file = open("input4.txt")
ans = 0
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
	found = -1
	for el in win_numbers:
		if (el in got_numbers):
			found += 1
	if(found!=-1): ans += (2**found)

print(ans)