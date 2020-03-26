# init user context's data
# user can add more other attributes
# this function is implemented by default, can be overwrited by users
def init(uctx):
    #context.log("我的第一个策略")
    pass

# this function is implemented by users, must be defined in strategy file(current file)
def handle_bar(uctx):
    while True:checksignal();\
        continue
    #ret = getL2LastNDayDetails(20180102, "600000.SS", 1)
    #ret = history_bars('600000.SS', 10, DataType.K1D, ['hhhh', 'open', 'close', 'ddx', 'ddy'], 20190925150000)
    #ret = history_bars('600000.SS', 10, DataType.K1D, ['open', 'close', 'ddx', 'ddy'], 20190925150000)
    #ret = history_bars('600000.SS', 10, DataType.K1D, ['close'], 20190925150000)
    #context.log(ret)


####################################
# common tail
#
# ShangZhenJing, Liuheng
####################################

# pinkle for sequence user context
import pickle
from enum import IntEnum, unique
from LMContext import *
from userapi import *
import numpy as np
from time import sleep
from contextlib import contextmanager
import signal

def trace(f, e, a):
    print(f.f_lineno)
    return trace

@unique
class DrawType(IntEnum):
    LINE  = 0
    DOT   = 1
    STICK = 2

@unique
class RunType(IntEnum,):
    BACKTEST      = 0
    PAPER_TRADING = 1

@unique
class DataType(IntEnum,):
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
class MatchingType(IntEnum,):
    NEXT_BAR_OPEN     = 0
    CURRENT_BAR_CLOSE = 1

@unique
class OrderType(IntEnum,):
    MARKET = 0
    LIMIT  = 1

@unique
class Side(IntEnum,):
    BUY  = 0
    SELL = 1

@unique
class OrderStatus(IntEnum,):
    PENDING_NEW     = 0
    ACTIVE          = 1
    FILLED          = 2
    PENDING_CANCEL  = 3
    CANCELLED       = 4
    REJECTED        = 5

@unique
class Color(IntEnum,):
    RED             = 0xff0000
    GREEN           = 0x00ff00
    BLUE            = 0x0000ff
    PINK            = 0xff1cae
    YELLOW          = 0xffff00
    ORANGE          = 0xff6633
    PURPLE_RED      = 0xcc00ff
    CYAN            = 0x99ffff
    VIOLET          = 0xff00ff
    BROWN           = 0x663300
    GRAY            = 0x9999cc


# global info: context, bardict
global context,bardict
bardict = BarDict()
context = Context()

global checksignal
checksignal = context.checksignal

# ban open
global open
open = None

# user context
class UserContext:
    def __init__(self):
        pass

def v_init():
    usercontext = UserContext()
    init(usercontext)
    try:
        with time_limit():
            init(usercontext)
    except TimeoutException:
        context.log("init timed out!")
        raise
    except:
        raise
    return pickle.dumps(usercontext)

def v_handle_bar(uctx):
    context.__init__()
    usercontext = pickle.loads(uctx)
    try:
        with time_limit():
            handle_bar(usercontext)
    except TimeoutException:
        context.log("handle_bar timed out!")
        raise
    except:
        raise
    return pickle.dumps(usercontext)

kline_fields=["open", "high", "low", "close", "datetime", "volume", "turnover", "preclose_px"]
fundflow_fields=["inflow", "little_in", "little_out", "medium_in", "medium_out", "large_in",
                 "large_out", "super_in", "super_out", "ddx", "ddy", "tcl", "investor_level"]
def history_bars(stock_id, bar_count, frequency, field, start_time):
    #if field in kline_fields:
    #    ret = context.hbar(stock_id, bar_count, frequency, field, start_time)
    #elif field in fundflow_fields:
    #    ret = context.hff(stock_id, bar_count, frequency, field, start_time)
    ret = context.hbar(stock_id, bar_count, frequency, field, start_time)
    if ret is None:
        ret = []
    return np.array(ret)

def getL2DayDetails(date, code=None):
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
        raise TimeoutException("timed out!")
    signal.signal(signal.SIGINT, signal_handler)
    try:
        yield
    finally:
        signal.signal(signal.SIGINT, signal.SIG_DFL)
        pass

