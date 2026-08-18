base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

print('12 12 8640')
#assume div by 6
for a in input().split(':'):
    for c in a:
        i = base64.index(c)
        for j in range(6):
            if i & (1 << j):
                print(1,end='')
            else:
                print(0,end='')
    #print()


print()
