
from pymongo import MongoClient
import time
from datetime import datetime

# connect
def connect():
    client = MongoClient('172.16.2.70', 27017)
    return client

def load_dkline(client):
    table = client.kline.history_klines_day_0
    start = time.time() 

    now = datetime.now()
    etime = now.strftime("%Y%m%d")
    print("dkline end time:", etime)

    # read stocks
    with open('/data/quant/kline/stocks', 'r') as fd:
        stock = fd.readline()
        while stock:
            stock = stock[0:9]
            # creat data file
            df = '/data/quant/kline/.cache/dkline/' + stock
            with open(df, 'w') as dfd:
                print(df, etime, stock)
                ret = table.find({'date': {'$lte': etime}, 'stock_code': stock})
                cnt = ret.count()
                print(stock, ":", cnt)
                for i in range(cnt):
                    r = ret[i]
                    try:
                        d = str(r['open_px']) + ' ' + str(r['high_px']) + ' '+ str(r['low_px']) + ' ' + str(r['close_px']) + ' ' \
                                + str(r['preclose_px']) + ' ' + str(r['date']) + ' ' + str(r['business_amount']) + ' ' + str(r['business_balance']) + '\n'
                    
                    except KeyError as e:
                        d = str(r['data'][0][1]) + ' ' + str(r['data'][0][2]) + ' ' + str(r['data'][0][3]) + ' ' + str(r['data'][0][4]) + ' ' \
                                + str(r['preclose_px']) + ' ' + str(r['data'][0][0]) + ' ' + str(r['data'][0][5]) + ' ' + str(r['data'][0][6]) + '\n'
                    except Exception as e:
                        print(r)
                        print("error:", e)
                        continue
                    dfd.write(d)
                #dfd.flush()
                dfd.close()

            stock = fd.readline()

    end = time.time() 
    print("cost:", end-start)


if __name__ == '__main__':
    client = connect()
    load_dkline(client)
