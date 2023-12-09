import string


file = open("input2.txt")

maxRed = 12
maxGreen = 13
maxBlue = 14

game = 1
tot_ans = 0
for line in file:
	red_tot = 0
	green_tot = 0
	blue_tot = 0
	line_red = line.split(':')[1]
	line_red = line_red.split(';')
	for round in range(len(line_red)):		
		line_round = line_red[round].split(',')
		for i in range(len(line_round)):
			line_round_split = line_round[i].split(' ')
			if(line_round_split[2] == 'red' or line_round_split[2] =='red\n'):
				red_tot = max(red_tot, int(line_round_split[1]))
			if(line_round_split[2] == 'blue' or line_round_split[2] =='blue\n'):
				blue_tot = max(blue_tot, int(line_round_split[1]))
			if(line_round_split[2] == 'green' or line_round_split[2] =='green\n'):
				green_tot = max(green_tot, int(line_round_split[1]))
	tot_ans += red_tot*green_tot*blue_tot
	game+=1
print(tot_ans)