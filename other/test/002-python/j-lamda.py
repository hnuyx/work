
def Func():
    temp = [lambda x: i*x for i in range(4)]
    return temp

for t in Func():
    print(t(2))
