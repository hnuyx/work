#!/usr/bin/env python3
import time #时间模块
# Caculate PI with Taylor series
def TaylorPi(k):
    sum,odd = 0,True
    for i in range(1,k):
        sum += 1/(2*i-1) if odd==True else -1/(2*i-1)
        odd = not odd
    return sum*4

def caculateRunTime():
    before = time.time() #生成开始时间,单位为秒
    timeSum = 0
    for i in range(100):
        start = time.time()
        TaylorPi(10000000)
        term = time.time() - start #每次循环耗时
        print("one term done, duration:",term)
        timeSum += term #累加
    return "total:%lf,averange:%lf"%(timeSum,timeSum/100)

print(caculateRunTime())
