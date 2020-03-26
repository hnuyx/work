
def init(usercontext):
    usercontext.name = "a test strategy"
    print("Hello Hello.py-init()");

def handle_bar(usercontext):
    '''
    bar = bardict["001"]
    print("StrategyName is",usercontext.name)
    print("Hello Hello.py-handle_bar()");
    print("This is updated HelloH")
    print("Bar member:", bar.stock_id, bar.datetime, bar.open, bar.close, bar.high, bar.low, bar.volume,
            bar.turnover, bar.prev_close)
    for o in context.orders:
        print("Order member:", o.order_id, o.stock_id, o.datetime, o.side, o.price,o.quantity,
                o.filled_quantity,o.unfilled_quantity, o.type,o.transaction_cost, o.avg_price, o.status, o.message)
    for s in context.stocks:
        print("Stocks:", s)
    print("Account member:", context.account.cash, context.account.frozen_cash, context.account.market_value,
            context.account.total_value, context.account.dividend_receivable)
    print("RunInfo member:", context.runinfo.run_type, context.runinfo.start_date, context.runinfo.end_date,
            context.runinfo.frequency, context.runinfo.stock_starting_cash, context.runinfo.slippage,
            context.runinfo.commission_multiplier, context.runinfo.benchmark, context.runinfo.matching_type)
    for p in context.positions:
        print("Posiions:", p.stock_id, p.quantity, p.pnl, p.sellable, p.market_value, p.vlaue_percent, p.avg_price)
    print("now:", context.now)
    print(context.order_percent(id="id001", percent=0.9, side=Side.SELL, price=100.0))
    print(context.order_percent("id001", 0.9, Side.SELL, 100.0))
    #print(context.get_open_orders())
    for o in context.orders:
        print(context.cancel_order(o))
    print(context.select(id="id001", name="SZ"))
    print(context.select("id001", "SZ"))
    print(context.draw(value=100.0, name="SZ", type=DrawType.DOT, color=Color.ColorRed))
    print(context.draw(100.0, "SZ", DrawType.DOT, Color.ColorRed))
    print(context.log("this is a log from handle bar"))
    a = {1, 2, 3}
    b = [1, 2, 3]
    print(context.log(a, b, 1, 2, "this is a log from handle bar"))
    print("Account member:", context.account.cash, context.account.frozen_cash, context.account.market_value,
            context.account.total_value, context.account.transaction_cost, context.account.dividend_receivable)
    print("RunInfo member:", context.runinfo.run_type, context.runinfo.start_date, context.runinfo.end_date,
            context.runinfo.frequency, context.runinfo.stock_starting_cash, context.runinfo.slippage,
            context.runinfo.commission_multiplier, context.runinfo.benchmark, context.runinfo.matching_type)

    print("Draw type:", DrawType.LINE.value, DrawType.DOT.value, DrawType.STICK.value)

    print("color red:", Color.ColorRed.value)
    print("color green:", Color.ColorGreen.value)
    print("color blue:", Color.ColorBlue.value)

    #for i in range(-100,100,1):
    #    print(context.stocks[i])
    #ret = history_bars('603811.SS', 10, DataType.K1D, 'ddx', 20190820150000)
    #print(ret)

    #num = 300
    #start = time.time() 
    #t = int(time.time())
    #ds = 24 * 60 * 60
    #for i in range(num):
    #    t = t - ds
    #    lt = time.localtime(t)
    #    date = time.strftime("%Y%m%d", lt)
    #    ret = getL2DayDetails(int(date))
    #ret = getL2DayDetails(20190822)
    #end = time.time() 
    #print("normal  ", num, "\tcmds cost:", end-start)
    #print(len(ret))
    #print(ret)

    #days = 10
    #start = time.time() 
    #ret = getL2LastNDayDetails(20190826, '600000.SS', days);
    #end = time.time() 
    #print("days ", days, "\tcmds cost:", end-start)
    #print(ret)
    #for k,v in ret.items():
    #    print(k, ":", v)
    '''

    while True:
        sleep(1)
        #print(os.getpid(), '--', threading.currentThread(), "--", ctypes.CDLL('libc.so.6').syscall(186))


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
        with time_limit():
            handle_bar(usercontext)
    except TimeoutException:
        context.log("handle_bar timed out!")
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

