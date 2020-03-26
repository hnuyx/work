#!/usr/bin/python3
import redis 
import sys

# configuration
HOST = 'level2-parse.redis.rds.aliyuncs.com'
PORT = 6379
DB = 31
PASSWORD = 'PKFDYfjZB8mfE62'


# redis client 
def get_redisclient(host, port, db, pwd):
    pool = redis.ConnectionPool(host=host, port=port, db=db, password=pwd, max_connections=100)
    return redis.Redis(connection_pool=pool)

def usage(exe):
    print("Usage:")
    print("\tpython", exe, "<jobid> [<start-index> <end-index>]")
    print("Example:")
    print("\tpython", exe, "baa090a8-323b-45da-a542-202b59a799bd 0 -1")


if __name__ == '__main__':
    argc = len(sys.argv)
    if argc != 2 and argc != 4:
        usage(sys.argv[0])
        sys.exit()

    start = 0
    end = -1
    jid = sys.argv[1]
    if argc == 4:
        start = sys.argv[2]
        end = sys.argv[3]

    rc = get_redisclient(HOST, PORT, DB, PASSWORD)
    ret = rc.lrange(jid, start, end)
    try:
        for r in ret:
            print(r.decode())
    except Exception:
        print("wrong db")
        pass
