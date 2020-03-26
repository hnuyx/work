
def init(usercontext):
    #context.log("我的第一个策略")
    pass

def handle_bar(usercontext):
    #context.log("be here")
    while True:
        #print("be here")
        context.log("be here--------------------------")
        print(os.getpid(), '--', threading.currentThread(), "--", ctypes.CDLL('libc.so.6').syscall(186))
        sleep(1)


from LMContext import *
import random
import time
from userapi import *
import pickle
from enum import IntEnum, unique
from contextlib import contextmanager
import signal
from time import sleep
import os
import threading
import ctypes

global context,bardict
bardict = BarDict()
context = Context()

global open
open=None

@unique
class DrawType(IntEnum):
    LINE  = 0
    DOT   = 1
    STICK = 2

@unique
class RunType(IntEnum):
    BACKTEST      = 0
    PAPER_TRADING = 1

@unique
class DataType(IntEnum):
    TickData  = 0
    K1m       = 1
    K5m       = 2
    K15m      = 3
    K30m      = 4
    K60m      = 5
    K1D       = 6
    K1W       = 7
    K1M       = 8
    K1Y       = 9
    Undefined = 10

@unique
class MatchingType(IntEnum):
    NEXT_BAR_OPEN     = 0
    CURRENT_BAR_CLOSE = 1

@unique
class OrderType(IntEnum):
    MARKET = 0
    LIMIT  = 1

@unique
class Side(IntEnum):
    BUY  = 0
    SELL = 1

@unique
class OrderStatus(IntEnum):
    PENDING_NEW     = 0
    ACTIVE          = 1
    FILLED          = 2
    PENDING_CANCEL  = 3
    CANCELLED       = 4
    REJECTED        = 5

@unique
class Color(IntEnum):
    ColorBase  = -4253158
    ColorRed   = ColorBase & 0xff0000
    ColorGreen = ColorBase & 0x00ff00
    ColorBlue  = ColorBase & 0x0000ff

# user context
class UserContext:
    def __init__(self):
        pass

def v_init():
    usercontext = UserContext()
    try:
        with time_limit():
            init(usercontext)
    except TimeoutException:
        context.log("init timed out!")
    return pickle.dumps(usercontext)

def v_handle_bar(bstr):
    context.__init__()
    usercontext = pickle.loads(bstr)
    try:
        #with time_limit():
        handle_bar(usercontext)
    #except TimeoutException:
    #    context.log("handle_bar timed out!")
    except:
        context.log("2 handle_bar timed out!")
    return pickle.dumps(usercontext)

kline_fields=["open", "high", "low", "close", "datetime", "volume", "turnover", "preclose_px"]
fundflow_fields=["inflow", "little_in", "little_out", "medium_in", "medium_out", "large_in",
                 "large_out", "super_in", "super_out", "ddx", "ddy", "tcl", "investor_level"]
def history_bars(stock_id, bar_count, frequency, field, start_time):
    if field in kline_fields:
        ret = context.hbar(stock_id, bar_count, frequency, field, start_time)
    elif field in fundflow_fields:
        ret = context.hff(stock_id, bar_count, frequency, field, start_time)
    if ret is None:
        ret = []
    return np.array(ret)

def getL2DayDetails(date, code='all'):
    if code is None:
        code = 'all'
    ret = context.l2d(date, code)
    if ret is None:
        return {}
    if code == 'all':
        return ret
    else:
        return ret[code]

def getL2LastNDayDetails(date, code, nd):
    if code is None:
        code = 'all'
    ret = context.l2d_lnd(date, code, nd)
    if ret is None:
        return {}
    return ret

class TimeoutException(BaseException):
    pass

@contextmanager
def time_limit():
    def signal_handler(signum, frame):
        print("be here hahahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
        raise TimeoutException("timed out!")
    signal.signal(signal.SIGINT, signal_handler)
    try:
        yield
    finally:
        signal.signal(signal.SIGINT, signal.SIG_DFL)
        pass

if __name__ == '__main__':
    bstr=v_init();
    v_handle_bar(bstr)

