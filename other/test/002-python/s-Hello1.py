
class UserContext:
    def __init__(self):
        pass

def init(usercontext):
    a = 0
    while True:
        a = a + 1
    usercontext.name = "a test strategy"
    print("Hello Hello.py-init()");

def handle_bar(usercontext):
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

    #open('test.cpp', 'r')

from LMContext import *
import random
import time
from userapi import *
import pickle
from enum import IntEnum, unique

global context,bardict
bardict = BarDict()
context = Context()

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
    ban_builtins()
    init(usercontext)
    recover_builtins()
    return pickle.dumps(usercontext)

def v_handle_bar(bstr):
    context.__init__()
    usercontext = None
    usercontext = pickle.loads(bstr)
    ban_builtins()
    handle_bar(usercontext)
    recover_builtins()
    return pickle.dumps(usercontext)

ban_list = frozenset(['open'])
baned_list = {}
def ban_builtins():
    for b in  ban_list:
        baned_list[b] = __builtins__[b]
        del __builtins__[b]

def recover_builtins():
    for b in  ban_list:
        __builtins__[b] = baned_list[b]

if __name__ == '__main__':
    bstr=v_init();
    v_handle_bar(bstr)
