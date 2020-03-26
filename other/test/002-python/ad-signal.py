

#a = [1,2,3,4,5]
#b = {1:2, 2:4, 3:6}

import time

def mid(i):
    #print("-----------------------------check")
    return i

def func(l):
    for i in l:
        yield mid(i)

c = 1
start = time.time() 
for i in func(range(5000)):
#for i in range(5000):
    c += 1
    pass
end = time.time() 
print("cost:", end-start)

#def check():
#    print("-----------------------------check")
#    return True
#
#while True and check():
#    print("body")
