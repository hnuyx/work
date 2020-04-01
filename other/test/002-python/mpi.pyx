#!/usr/bin/env python3
import time #时间模块
# Caculate PI with Taylor series
cpdef double TaylorPi(int k):
    cdef double sum = 0.0
    cdef int odd = 1
    cdef int i = 0
    for i in xrange(k):
        if odd == 1:
            sum += 1.0/(2.0*i+1.0)
            odd = 0
        else:
            sum -= 1.0/(2.0*i+1.0)
            odd = 1
    return sum*4.0

def caculateRunTime(int t):
    before = time.time() #生成开始时间,单位为秒
    timeSum = 0
    cdef int k = 10000000
    for i in range(t):
        start = time.time()
        TaylorPi(10000000)
        term = time.time() - start #每次循环耗时
        print("one term done, duration:",term)
        timeSum += term #累加
    return "total:%lf,averange:%lf"%(timeSum,timeSum/t)

print(caculateRunTime(10))
