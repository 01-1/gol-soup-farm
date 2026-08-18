base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

inp=input()

print('12 12 8640')
#assume div by 6
for a in inp.split(':'):
    for c in a:
        i = int(c)
        if i:
            print(1,end='')
        else:
            print(0,end='')
    #print()

print()
print('x=12,y=12')
for a in inp.split(':'):
    r=0
    for c in a:
        i = int(c)
        if i:
                print('o',end='')
        else:
            print('b',end='')
        r+=1
        if r==12:
            print('$')
            r=0

print()
