def getLevels(chaine):
	levels = []
	level = 0
	for c in chaine:
		if c == ')':
			level -= 1
		levels += [level]
		if c == '(':
			level += 1
	return levels			

def indexes(chaine, c):
	ind = []
	for i in range(len(chaine)):
		if chaine[i] == c:
			ind += [i]
	return ind

def Eval(chaine):
	chaine = chaine.lstrip()
	if chaine[0] == '(' and chaine[-1] == ')':
		chaine = chaine[1:-1]
	levels = getLevels(chaine)
	for operator in "-+/*^":
		pos = indexes(chaine, operator)
		if pos != []:
			pos = [p for p in pos if levels[p] == 0]
			if pos != []:
				sub_1 = chaine[0:pos[0]]
				sub_2 = chaine[pos[0]+1:len(chaine)]
				if operator == '-':
					return Eval(sub_1) - Eval(sub_2)
				elif operator == '+':
					return Eval(sub_1) + Eval(sub_2)
				elif operator == '/':
					return Eval(sub_1) / Eval(sub_2)
				elif operator == '*':
					return Eval(sub_1) * Eval(sub_2)
				elif operator == '^':
					return Eval(sub_1) ** Eval(sub_2)
	return float(chaine)
	
			
			
