import redis
import json

pool = redis.ConnectionPool(host='r-bp170a80120560d4669.redis.rds.aliyuncs.com', port=6379, db=0,password='qF4thCEZ9Pw3', max_connections=50)
redis_cli = redis.Redis(connection_pool=pool)
key = "conv_bond_stocks"
ret = redis_cli.get(key)
ret = json.loads(ret.decode())
cbs = list(ret.keys())

for s in cbs:
    print(s, ret[s])
