from pymongo import MongoClient

client = MongoClient('10.46.64.71', 37017)
#mt = client.god.fundflows
mt = client.god.fundflow_histories



def find_minmax(fields):
    size = len(fields)
    #print(size)
    mm = [[0.0]*2 for i in range(size)]
    #print(mm)
    ret = mt.find({'stock_code': '603309', 'date': {'$gte': '20190409'}})
    for t in ret:
        #print(t)
        for i in range(size):
            f = fields[i]
            v = t.get(f)
            if v is None:
                continue
            #print(mm)
            #print(f, v, mm[i][0], mm[i][1], v < mm[i][0], v > mm[i][1])
            if v < mm[i][0] and v != float('-inf'):
                mm[i][0] = v
                #print("min", f, t['date'], t['stock_code'])
            if v > mm[i][1] and t[f] != float('inf'):
                mm[i][1] = v
                #print("max", f, t['date'], t['stock_code'])
        #return

    for i in range(size):
        print(fields[i], mm[i][0], mm[i][1])


find_minmax(['inflow', 'little_in','little_out' ,'medium_in', 'medium_out', 'large_in', 'large_out', 'super_in', 'super_out', 'ddx', 'ddy', 'tcl', 'investor_level'])
#find_minmax(['ddx', 'ddy'])
