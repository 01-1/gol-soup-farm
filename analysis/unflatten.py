m=int(input('mod? '))
flat = input()
for i,c  in enumerate(flat):
    print(c,end='')
    if i%m == m-1:
        print()


