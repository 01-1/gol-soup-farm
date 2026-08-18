flat = input()
for i,c  in enumerate(flat):
    print(('  ','██')[int(c)],end='')
    if i%12 == 11:
        print()


