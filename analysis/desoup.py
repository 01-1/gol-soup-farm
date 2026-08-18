
CONST = 17295
CONST_SHIFT = CONST * CONST // 2;

awa = [['b']*12+['$'] for _ in range(12)]

l = list(map(int, input().split()))
for w in l:
    i = (w - CONST_SHIFT) // CONST
    j = (w - CONST_SHIFT) % CONST
    awa[i][j] = 'o'

print('x=12,y=12')
print('\n'.join(map(lambda l:''.join(l),awa)))
    
awa = [['0']*12 for _ in range(12)]

for w in l:
    i = (w - CONST_SHIFT) // CONST
    j = (w - CONST_SHIFT) % CONST
    awa[i][j] = '1'

print('12 12 8640')
print(''.join(map(lambda l:''.join(l),awa)))

