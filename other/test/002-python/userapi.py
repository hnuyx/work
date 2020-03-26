# _*_ coding=utf-8 _*_
import time
import re
from functools import wraps

import numpy as np
import redis
from pymongo import MongoClient
import datetime
import pymysql

now_time = datetime.datetime.now()  # 当前时间

class MySQLSingle():
    cursor =  pymysql.connect(host='level2-parse-rds.mysql.rds.aliyuncs.com',
                    port=3306,
                    user='root',
                    password='UUd9nAQOuCvwt2wil@DL',
                    database='mysql_minute',
                    charset='utf8',
                    connect_timeout=10).cursor(pymysql.cursors.DictCursor)

class MyMongoSingle():
    cl = MongoClient('10.47.51.126', 37017)
    block_db = cl.god.blocks
    stocks_base = cl.god.stocks
    stocks_reals = cl.god.stocks_reals

class KlineMongo():
    db_client =MongoClient('172.16.2.70', 27017)
    history_db = db_client.kline

class RedisConn():
    pool = redis.ConnectionPool(host='r-bp195e31d04b0dd4.redis.rds.aliyuncs.com', port=6379, db=17,
                                password='ADbugA2JU6yALx', max_connections=1000)
    redis_cli = redis.Redis(connection_pool=pool)

class Instrument:
    def __init__(self):
        self.stock_id = None  # 股票代码
        self.symbol = None
        self.concept_names = None
        self.exchange = None
        self.stockname = None  # 股票名字
        self.ltp = None  # 流通股
        self.zgb = None  # 总股本
    def __str__(self):
        return "{stockid:%s,stockname:%s}" % (self.stock_id, self.stockname)

class Sector:
    def __init__(self):
        self.code = None
        self.name = None
    def __str__(self):
        return "{code:%s,name:%s}" % (self.code,self.name)


def getSectors():
    """
    拿行业板块列表
    :return:
    """
    block_db = MyMongoSingle.block_db
    blocks = block_db.find({}, {'name', '_id'})
    block_list = []
    for i in blocks:
        res = re.search(r'^HY.*?', i['_id'])
        if res:
            sector_obj = Sector()
            sector_obj.name = i['name']
            sector_obj.code = i['_id']
            block_list.append(sector_obj)
    return block_list


def get_block_detail(id=None, name=None):
    """
    拿到某个版块下的详细股票代码列表
    :param id:
    :param name:
    :return:
    """
    block_db = MyMongoSingle.block_db
    block_list = block_db.find_one({'_id': id, 'name': name}, {'stocks'})
    return block_list['stocks']

def getInstruments(sector=None, market=None):
    """
    拿到数据库里所有的股票, 区分上证a股, 深证A股, 中小板, 创业板
    根据条件获取股票的列表
    # stock_list = []  # all_stock
    # a_share = []  # 上证A股
    # shenzhen_a_share = []  # 深圳A股
    # middle_stocks = []  # 中小板
    # gemarket = []  # 创业板
    # stocks = stocks_base.find({}, {'_id'})
    :param sector: black id
    :param market: 'SS', 'SZ', 'ZXB', 'CYB'
    :return:
    """
    instrument_list = []
    stocks_reals = MyMongoSingle.stocks_reals
    stocks_base = MyMongoSingle.stocks_base
    block_db = MyMongoSingle.block_db
    def block_detail(block_set):
        for i in block_set:
            i = i.split('.')[0]
            instrument = Instrument()
            stock_detail = stocks_base.find_one({'stock_code': i}, {'stock_name'})
            # print(stock_detail)
            exresult = stocks_reals.find_one({'_id': i}, {'circulation_amount', 'total_shares'})
            instrument.stock_id = stock_detail['_id']
            # for v in stock_detail['blocks']:
            #     print(v)
            instrument.stockname = stock_detail['stock_name']
            instrument.ltp = exresult['circulation_amount']  # 流通股
            instrument.zgb = exresult['total_shares']  # 总股本
            instrument_list.append(instrument)

    if sector and not market:
        block_list = block_db.find_one({'_id': sector}, {'stocks'})
        if block_list:
            # print(block_list)
            block_set = set(block_list['stocks'])
            block_detail(block_set)
    elif market and not sector:
        stocks = stocks_base.find({}, {'_id'})
        search_stock = []
        for i in stocks:
            if market == 'SS':
                res = re.search(r'^60\d{4}.SS', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'SZ':
                res = re.search(r'\d{6}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'ZXB':
                res = re.search(r'^002\d{3}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'CYB':
                res = re.search(r'^300\d{3}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'KCB':
                res = re.search(r'68[8|9]\d+\.SS', i['_id'])
                if res:
                    search_stock.append(res.group())
        block_set = set(search_stock)
        block_detail(block_set)
    elif sector and market:
        block_list = block_db.find_one({'_id': sector}, {'stocks'})
        block_set = []
        if block_list:
            block_set = set(block_list['stocks'])
        stocks = stocks_base.find({}, {'_id'})
        search_stock = []
        for i in stocks:
            if market == 'SS':
                res = re.search(r'^60\d{4}.SS', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'SZ':
                res = re.search(r'\d{6}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'ZXB':
                res = re.search(r'^002\d{3}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'CYB':
                res = re.search(r'^300\d{3}.SZ', i['_id'])
                if res:
                    search_stock.append(res.group())
            elif market == 'KCB':
                res = re.search(r'68[8|9]\d+\.SS', i['_id'])
                if res:
                    search_stock.append(res.group())
        search_stock = set(search_stock)
        block_set = list(block_set.intersection(search_stock))
        block_detail(block_set)
    elif not sector and not market:
        stocks = stocks_base.find({}, {'_id'})
        all_stocks = []
        for i in stocks:
            all_stocks.append(i['_id'])
        block_set = set(all_stocks)
        # print(len(block_set))
        block_detail(block_set)
    return instrument_list

# deal code for mysql
# such as: 600000.SS -> SH600000
# such as: 300127.SZ -> SZ300127
def deal_code_to_mysql(code):
    if re.match(r'^\d{6}\.S[SZ]$', code) is None:
        return None
    # SH
    if code[8] == 'S':
        return 'SH' + code.split('.')[0]
    # SZ
    return 'SZ' + code.split('.')[0]

# fetch sql data and store into blocks
def extract_sql_data(sql, blocks):
    # fetch data
    cursor = MySQLSingle.cursor
    rows = cursor.execute(sql)
    data = cursor.fetchall()

    # store into blocks
    # blocks[code] --> sql rows
    # such as: block['600000.SS'] --> data
    for line in data:
        # print(line)
        if line['code'].startswith('SH'):
            line['code'] = line['code'][2:] + '.SS'
        elif line['code'].startswith('SZ'):
            line['code'] = line['code'][2:] + '.SZ'
        if line['code'] not in blocks:
            blocks[line['code']] = {}
        block = blocks[line['code']]
        block[line['name']] = line

# getL2Details
# time can be 0, YYYYMMDD, such as: 20190729
def getL2Details(date, code=None, time=None):
    # convert date to string
    if isinstance(date, int):
        date = str(date)

    # blocks for result
    # codes for sql string
    # onecode for result
    blocks = {}
    codes = []
    onecode = ''

    # get codes and count of codes
    cnt = 0
    if type(code) is list:
        for c in code:
            tmp = deal_code_to_mysql(c)
            if tmp:
                codes.append(tmp)
                onecode = c
                cnt += 1
    elif type(code) is str:
        tmp = deal_code_to_mysql(code)
        if tmp:
            codes.append(tmp)
            onecode = code
            cnt += 1

    # useless 'X' in case of tuple (code, )
    if cnt == 1:
        codes.append('X')

    # sql base
    sql_base = "select code,date,name,{}BuyOrderNum as buyordernum,SellOrderNum as sellordernum,iBuy as ibuy, iBuyVol as ibuyvol,iBuyOrderNum as ibuyordernum,iSell as isell, iSellVol as isellvol,iSellOrderNum as isellordernum,pBuy as pbuy,pBuyVol as pbuyvol,pBuyOrderNum as pbuyordernum,pSell as psell, pSellVol as psellvol,pSellOrderNum as psellordernum "
    sql_cond = ''


    # has code
    if cnt > 0:
        if time == 0:
            table = 'l2data_' + date
            sql_base = sql_base.format('minute,')
            sql_cond = "from {} where minute = (select max(minute) from {}) and code IN {} ;".format(table, table, tuple(codes))
        elif time:
            table = 'l2data_' + date
            sql_base = sql_base.format('minute,')
            sql_cond = "from {} where minute= '{}' and code IN {} ;".format(table, time, tuple(codes))
        else:
            table = 'l2data_' + date[0:4]
            sql_base = sql_base.format(' ')
            sql_cond = "from {} where date='{}' and code IN {} ;".format(table, date, tuple(codes))
    else: # no code
        if time == 0:
            table = 'l2data_' + date
            sql_base = sql_base.format('minute,')
            sql_cond = "from {} where minute = (select max(minute) from {});".format(table, table)
        elif time:
            table = 'l2data_' + date
            sql_base = sql_base.format('minute,')
            sql_cond = "from {} where minute = '{}';".format(table, time)
        else:
            table = 'l2data_' + date[0:4]
            sql_base = sql_base.format(' ')
            sql_cond = "from {} where date = '{}';".format(table, date)

    sql = sql_base + sql_cond
    #print(sql)
    extract_sql_data(sql, blocks)

    # print(block)
    if cnt == 1:
        return blocks[onecode]
    else:
        return blocks

def getNTradingDays(date, n):
    """
    返回股票日期列表
    :param date: int
    :param n:  int
    :return:
    """
    time_list = []
    history_db = KlineMongo.history_db
    history_data = history_db.history_klines_day_0.find(
        {"date": {"$lte": str(date)}, 'stock_code': '000001.SS'}).sort('date', -1).limit(n)
    for i in history_data:
        time_list.append(int(i['date']))
    return time_list

# valid color of RGB, should be [0, 0xff]
def valid_color(c):
    if c < 0:
        return 0
    if c > 0xff:
        return 0xff
    return c

# calculate RGB
def RGB(red, green, blue):
    return (valid_color(red) << 16) + (valid_color(green) << 8) + valid_color(blue)

if __name__ == '__main__':
    start_time = time.time()
    # getInstruments('L00001.XBHS')
    # get_block_detail('HY0011.XBHS', '房地产')
    # getSectors()
    #stock = getL2Details('20190611')
    #stock = getL2Details('20190611', '600000.SS')
    #stock = getL2Details('20190611', ['600000.SS'])
    #stock = getL2Details('20190611', ['600000.SS', '300127.SZ'])
    #stock = getL2Details('20190611', ['600000.SS', '300127.SZ'], 0)
    for i in range(1,1000):
        # stock=getL2Details('20190611','600000.SS', 0)
        stock = getL2Details('20190611', ['600000.SS', '300127.SZ'], 0)
    #getL2Details('20190611', time=1350)
    #getL2Details('20190611','600000.SS', time=1100)
    #getL2Details('20190611', time=0)
    #getL2Details('20190611', '600000.SS', time=0)
    #getNTradingDays('20190611', 10)
    stop_time = time.time()
    print('Used:',stop_time - start_time,'MS')
    #stock = stocks['600000.SS']
    print(len(stock),stock)

# 上证指数: 000001.SS 沪深300: 000300.SS 深圳成指: 399001.SZ 中小板指数: 399005.SZ 创业板: 399006.SZ #  cl.god.stocks_reals表里
# db.getCollection('stocks').find({"_id":{"$in":["000001.SS","000300.SS","399001.SZ","399005.SZ","399006.SZ"]}},{"stock_name":1,"_id":1})
