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
INF = 10**9

for _ in range(iters):
    nindc = defaultdict(int)
    for (i, j) in inder:
        for a in (i-1, i, i+1):
            for b in (j-1, j, j+1):
                nindc[(a, b)]+=1
    ninder = set()

    mini = INF
    minj = INF
    maxi = -INF
    maxj = -INF

    for (i, j), ct in nindc.items():

        if ct == 3 or ct == 4 and (i, j) in inder:
            ninder.add((i, j))
            mini = min(mini, i)
            minj = min(minj, j)
            maxi = max(maxi, i)
            maxj = max(maxj, j)

    inder=ninder
    
    print(mini, minj, '-', maxi, maxj)
    maxi = mini - 1

    for i in range(mini, maxi+1):
        for j in range(minj, maxj+1):
            if (i, j) in ninder:
                print('██',end='')
            else:
                print('  ',end='')
        print()
    print()


    tct += len(inder)
    

#print(len(inder))
print(tct)
