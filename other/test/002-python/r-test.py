import time
import _thread

def f():
    time.sleep(5)
    print("Interrupt Main Thread")
    _thread.interrupt_main()

def g():
    _thread.start_new_thread(f, ())
    while True:
        time.sleep(1)
    #for i in range(0,10):
    #    for x in range(0,10000000000000):
    #        x += x
    print(1, time.time())

try:
    g()
except KeyboardInterrupt:
    print("keyboardinterrupt received")
    print (2, time.localtime())
