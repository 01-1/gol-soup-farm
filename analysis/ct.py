rle = ''
while '!' not in rle:
    rle += input() + '\n'
    if 'x' in rle:
        rle = ''
k=""
count=0
for i in rle:
    if i in "ob":
        if (count==0):
            k+=i
        else:
            #print(count)
            k+=i*count
            count=0
    elif (i in "$!"):
        #print(len(k))
        if (i in "$" and count>0):
            k+=(12-len(k)%12)%12*'b'
            count-=1
            k+=12*count*'b'
            count=0
        else:
            k+=(12-len(k)%12)%12*'b'
    else:
        count=10*count+int(i)
print(k.replace("b","0").replace("o","1"),end="")
