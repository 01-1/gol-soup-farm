from collections import defaultdict

inp = list(map(lambda x: (x.strip()), open('a').readlines()))

inder = set()

for i,s in enumerate(inp):
    for j,c in enumerate(s):
        if c=='1':
            inder.add((i,j))

iters = 8640
# golad
tct = 0

for _ in range(iters):
    nindc = defaultdict(int)
    for (i, j) in inder:
        for a in (i-1, i, i+1):
            for b in (j-1, j, j+1):
                nindc[(a, b)]+=1
    ninder = set()
    for pt, ct in nindc.items():
    #for i in range(12):
        #for j in range(12):
            #pt = (i, j)
            #ct = nindc[pt]
            if ct == 3 or ct == 4 and pt in inder:
                ninder.add(pt)
    inder=ninder
    tct += len(inder)
    print(len(inder))

#print(len(inder))
print(tct)
