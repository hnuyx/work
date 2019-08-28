
import redis
import time

# connect to redis
def connect():
    pool = redis.ConnectionPool(host='r-bp195e31d04b0dd4.redis.rds.aliyuncs.com', port=6379, db=17,
        password='ADbugA2JU6yALx', max_connections=1000)
    return redis.Redis(connection_pool=pool)

# test without pipeline
def test(r, num):
    start = time.time() 
    for i in range(num):
        ret = r.lrange("onekline-600572.SS-0", 0, -1)
    end = time.time() 
    print("normal  ", num, "\tcmds cost:", end-start)

# test with pipeline
def test_pipeline(r, num):
    pipeline = r.pipeline(transaction=False)

    start = time.time() 
    for i in range(num):
        pipeline.lrange("onekline-600572.SS-0", 0, -1)
    ret = pipeline.execute()
    end = time.time() 
    print("pipeline", num, "\tcmds cost:", end-start)


if __name__ == '__main__':
    r = connect()
    anum = [1, 10, 100, 1000, 3000, 5000, 6000, 10000]
    for num in anum:
        test(r, num)
        test_pipeline(r, num)


