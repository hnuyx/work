
from pymongo import MongoClient
import time


# connect
def connect():
    client = MongoClient('172.16.2.70', 27017)
    return client

def test(c, num):
    t = c.kline.history_klines_1_0
    start = time.time() 
    for i in range(num):
        ret = t.find({'date': {'$lte': '20190628', '$gte': '20190628'}, 'stock_code': '600572.SS'})
        ret[0]
        print(ret[0])
    end = time.time() 
    print("normal  ", num, "\tcmds cost:", end-start)


if __name__ == '__main__':
    c = connect()
    #anum = [1, 10, 100, 1000, 3000, 5000, 6000, 10000]
    anum = [1]
    for num in anum:
        test(c, num)
