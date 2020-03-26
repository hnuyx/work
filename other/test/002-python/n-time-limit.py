
from contextlib import contextmanager
import signal
from time import sleep

class TimeoutException(BaseException): pass

@contextmanager
def time_limit(seconds):
    def signal_handler(signum, frame):
        raise TimeoutException("Timed out!")
    signal.signal(signal.SIGALRM, signal_handler)
    signal.alarm(seconds)
    try:
        yield
    finally:
        signal.alarm(0)

def long_function_call():
    while True:
        sleep(1)
        print(1)

try:
    with time_limit(3):
        long_function_call()
except TimeoutException:
    print("Timed out!")

