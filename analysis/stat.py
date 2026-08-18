awawa = [[0]*12 for _ in range(12)]
lines = open('statin').readlines()

CONST = 17295
CONST_SHIFT = CONST * CONST // 2;

counts = [0] * 145

for line in lines:
    #awa = [[0]*12 for _ in range(12)]
    counts[len(line.split())]+=1
    for w in map(int, line.split()):
        i = (w - CONST_SHIFT) // CONST
        j = (w - CONST_SHIFT) % CONST
        awawa[i][j] += 1

for row in awawa:
    for col in row:
        print('{:.4f}'.format(col / len(lines)), end=' ')
    print()
    

for i,e in enumerate(counts):
    print(i, e, sep='\t')
