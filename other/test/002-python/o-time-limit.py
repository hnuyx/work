
from threading import Timer
from time import sleep
 
def time_limit(interval):
    def wraps(func):
        def time_out():
            raise RuntimeError()

        def deco(*args, **kwargs):
            timer = Timer(interval, time_out)
            timer.start()
            res = func(*args, **kwargs)
            timer.cancel()
            return res
        return deco
    return wraps

@time_limit(3)
def func():
    while True:
        sleep(1)
        print(1)

try:
    func()
except Exception as e:
    print("be here")
