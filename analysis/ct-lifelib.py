import lifelib
sess = lifelib.load_rules("b3s23")
lt = sess.lifetree()
#rle = open('ctin').read()
rle = ''
while '!' not in rle:
    rle += input() + '\n'

lidka = lt.pattern(rle)
print("Initial population: %d" % lidka.population)
lidka_end = lidka[8640]
print("Final population: %d" % lidka_end.population)

SKIP = 1

tpop = 0
for pop in range(1, 8640//SKIP + 1):
    lidka = lidka.advance(SKIP)
    tpop += lidka.population
    print(lidka.population)
    
print('Ans:',tpop*SKIP)
#lidka.viewer()

ltp = lt.pattern(rle)
for i in range(12):
    for j in range(12):
        print(ltp[i, j],end='')
    print()
print()

'''#CLL state-numbering golly
x = 12, y = 12, rule = B3/S23
2A5.2A$3A.A.2A2.2A$3A3.3A2.A$2.2A.3A3.A$5A2.A2.A$5.3A2.2A$A.3A6.A$
3.A.A2.A.2A$5A2.A.A$2A4.A4.A$.A.A.A.A.2A$4.A.2A.A!'''
