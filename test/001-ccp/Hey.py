
import TempM2

class Temp:
    tmp1 = None
    tmp2 = None

temp = Temp()

def HeyWorld():
    print("Hey world!")

    tlist = TempM2.tmplist()
    print("Hey world!")

    '''
    for i in tlist:
        print(i.number)

    for i in tlist:
        print(i.number)
    '''

    a = {1,2}
    #print(a)
    tmp1 = TempM2.tmp1()
    #tmp1.helloFunc(a, 1,2, "2")
    #tmp1.heyFunc(address="address192.168.1.1")
    #tmp1.heyFunc(address="address192.168.1.1", abi="abi", types=1)
    #tmp1.heyFunc(address="address192.168.1.1", abi="abi", value=100.0, types=1)
    tmp1.heyFunc(address="address192.168.1.1", abi="abi", value=100.0, types=1, li=["1","2","3"])

    print(tmp1.number)
    print(tmp1.numa)
    print(tmp1.numb)

    #print(tmp1)
    '''
    temp.tmp1 = TempM2.tmp1()
    temp.tmp2 = TempM2.tmp2()
    print(temp.tmp1.number, temp.tmp2.number)
    temp.tmp1.number = 11;
    temp.tmp2.number = 22;
    print(temp.tmp1.number, temp.tmp2.number)
    tmp = TempM2.tmp1()
    print(tmp.number)
    tmp = TempM2.tmp2()
    print(tmp.number)
    '''

