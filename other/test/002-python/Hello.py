
import talib
def init(uctx):
    context.log(uctx.ud)
    pass
 

def handle_bar(uctx):
    #ret = history_bars('00001.HK', 10, DataType.K1m, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime'], 20191216093000)
    #ret = history_bars('HSI', 10, DataType.K1m, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime', 'preclose_px'], 20191216093000)
    #context.log(ret)

    #ret = getHKL2(1700, '00700.HK')
    ret = getHKL2N(1700, '00700.HK', 10)
    context.log(ret)

    #ret = getL2DayDetails(20191025, '600000.SS')
    #ret = getL2DayDetailsMid(20191025, '600000.SS')
    #ret = getL2DayDetailsMinute(1300, '600000.SS')
    #ret = getL2LastNDay(20191025, '600000.SS', 10)
    #ret = getL2LastNDayDetailsMid(20191025, '600000.SS', 10)
    #ret = getL2LastNDayDetailsMinute(1300, '600000.SS', 10)
    #context.log(ret)
    #context.log(len(ret))

    #ret = getL2DayDetails(20191025, '600000.SS')

    #stock = '600000.SS';
    #ret = history_bars_r(stock, 10, DataType.K1m, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime'], 20191216103000, 20191216093000)
    #ret = history_bars_r(stock, 10, DataType.K1m, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime'], 20191216093000)
    #ret = history_bars_r(stock, 10, DataType.K1D, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime'], 20191201093000)
    #ret = history_bars_r(stock, 10, DataType.K1D, ['high', 'low', 'close'], 20191201093000)
    #context.log(ret)
    #maxH = max(ret[:, 0])
    #minL = min(ret[:, 1])
    #maxC = max(ret[:, 2])
    #minC = min(ret[:, 2])
    #context.log(maxH, minL, maxC, minC)

    #ret = getPrcRange('600000.SS', 10, 20191201093000)
    #context.log(ret)

    #ret = history_bars(stock, 10, DataType.K1m, ['open', 'high', 'low', 'close', 'volume', 'turnover', 'datetime'], 20191216093000)
    #OPEN   = ret[..., 0]
    #HIGH   = ret[..., 1]
    #LOW    = ret[..., 2]
    #CLOSE  = ret[..., 3]
    #VOLUME = ret[..., 4]
    #AMOUNT = ret[..., 5]

    #context.log(AMOUNT / (VOLUME + 1))

    #for stock in context.stocks:
    #    checksignal();prices = history_bars('600000.SS', 15, DataType.K1D1, 'close', context.now)
    #    #checksignal();prices = history_bars(stock1, 15, DataType.K1D, 'close', context.now)
    #    pass
    #    pass

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
from contextlib import contextmanager
import signal
from time import sleep
np.set_printoptions(suppress=True, precision=15)

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

def v_init(ud):
    usercontext = UserContext()
    usercontext.ud = ud
    try:
        with time_limit():
            init(usercontext)
    except TimeoutException:
        context.log("init 运行超时!")
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
        context.log("handle_bar 运行超时!")
        raise
    except:
        raise
    return pickle.dumps(usercontext)

kline_fields=["open", "high", "low", "close", "datetime", "volume", "turnover", "preclose_px"]
fundflow_fields=["inflow", "little_in", "little_out", "medium_in", "medium_out", "large_in",
                 "large_out", "super_in", "super_out", "ddx", "ddy", "tcl", "investor_level"]
def history_bars(stock_id, bar_count, frequency, field, start_time, end_time = 0):
    if len(stock_id) == 9:
        ret = context.hbar(stock_id, int(bar_count), frequency, field, start_time, end_time)
    else:
        ret = context.hkbar(stock_id, int(bar_count), frequency, field, start_time, end_time)
    if ret is None:
        ret = []
    return np.array(ret)

def history_bars_r(stock_id, bar_count, frequency, field, start_time, end_time = 0):
    if len(stock_id) == 9:
        ret = context.hbar(stock_id, int(bar_count), frequency, field, start_time, end_time, 1)
    else:
        ret = context.hkbar(stock_id, int(bar_count), frequency, field, start_time, end_time, 1)
    if ret is None:
        ret = []
    return np.array(ret)

def getPrcRange(stock_id, nd, start_time):
    ret = history_bars_r(stock_id, nd, DataType.K1D, ['high', 'low', 'close'], start_time)
    return max(ret[:, 0]), min(ret[:, 1]), max(ret[:, 2]), min(ret[:, 2])

def getL2Day(date, code=None):
    return getL2DayDetailsInterface(date, code, 0)

def getL2DayMid(date, code=None):
    return getL2DayDetailsInterface(date, code, 1)

def getL2Minute(minute, code=None):
    return getL2DayDetailsInterface(minute, code, 2)

def getL2DayDetailsInterface(date, code=None, group=0):
    tc = code
    if tc is None:
        tc = 'all'
    elif tc.upper() == 'ALL':
        tc = '000000.SI'
    elif tc.upper() == '000001.SS':
        tc = '000001.SI'
    elif tc.upper() == '399001.SZ':
        tc = '000002.SI'
    elif tc.upper() == '399005.SZ':
        tc = '000003.SI'
    elif tc.upper() == '399006.SZ':
        tc = '000004.SI'
    ret = context.l2d(date, tc, group)
    if ret is None or len(ret) == 0:
        return {}
    if tc == 'all':
        return ret
    else:
        return ret[code]

def getL2LastNDay(date, code, nd):
    return getL2LastNDayDetailsInterface(date, code, nd, 0)

def getL2LastNDayMid(date, code, nd):
    return getL2LastNDayDetailsInterface(date, code, nd, 1)

def getL2LastNMinute(minute, code, nd):
    return getL2LastNDayDetailsInterface(minute, code, nd, 2)

def getL2LastNDayDetailsInterface(date, code, nd, group=0):
    tc = code
    if tc is None:
        tc = 'all'
    elif tc.upper() == 'ALL':
        tc = '000000.SI'
    elif tc.upper() == '000001.SS':
        tc = '000001.SI'
    elif tc.upper() == '399001.SZ':
        tc = '000002.SI'
    elif tc.upper() == '399005.SZ':
        tc = '000003.SI'
    elif tc.upper() == '399006.SZ':
        tc = '000004.SI'
    ret = context.l2d_lnd(date, tc, nd, group)
    if ret is None:
        return {}
    return ret

def getHKL2(minute, code):
    ret = context.hkl2d(minute * 100, code, 1)
    if ret is None:
        return []
    return ret[0]

def getHKL2N(minute, code, N):
    ret = context.hkl2d(minute * 100, code, N)
    if ret is None:
        return []
    return ret

class TimeoutException(Exception):
    pass

@contextmanager
def time_limit():
    def signal_handler(signum, frame):
        raise TimeoutException("time out!")
    signal.signal(signal.SIGINT, signal_handler)
    try:
        yield
    finally:
        signal.signal(signal.SIGINT, signal.SIG_DFL)
        pass

