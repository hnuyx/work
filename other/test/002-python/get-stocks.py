
from pymongo import MongoClient
import re
import redis
import json

def connect_to_server(ip, port):
    return MongoClient(ip, port)

def is_ss_mri(code, hq):
    if (hq == 'XSHG.MRI' or hq == 'MRI') and re.match(r'000\d{3}\.SS$', code):
        return True
    return False

def is_ss_esa_m(code, hq):
    if hq == 'ESA.M' and re.match(r'60\d{4}\.SS$', code):
        return True
    return False

def is_ss_esb(code, hq):
    if hq == 'ESB' and re.match(r'900\d{3}\.SS$', code):
        return True
    return False

def is_ss_em_etf(code, hq):
    if hq == 'EM.ETF' and re.match(r'51[0-3,8]\d{3}\.SS$', code):
        return True
    return False

def is_ss_em_lof(code, hq):
    if hq == 'EM.LOF' and re.match(r'50[1-2]\d{3}\.SS$', code):
        return True
    return False

def is_ss_esa_kcdr(code, hq):
    if hq == 'ESA.KCDR' and re.match(r'689\d{3}\.SS$', code):
        return True
    return False

def is_ss_esa_ksh(code, hq):
    if hq == 'ESA.KSH' and re.match(r'688\d{3}\.SS$', code):
        return True
    return False

def is_ss(code, hq):
    if is_ss_mri(code, hq) or is_ss_esa_m(code, hq) or is_ss_esa_kcdr(code, hq) or is_ss_esa_ksh(code, hq):
        return True
    return False

def is_sz_mri(code, hq):
    if hq == 'MRI' and re.match(r'39\d{4}\.SZ$', code):
        return True
    return False

def is_sz_esa_m(code, hq):
    if hq == 'ESA.M' and re.match(r'00[0-1]\d{3}\.SZ$', code):
        return True
    return False

def is_sz_esb(code, hq):
    if hq == 'ESB' and re.match(r'2\d{5}\.SZ$', code):
        return True
    return False

def is_sz_esa_smse(code, hq):
    if hq == 'ESA.SMSE' and re.match(r'00[2-4]\d{3}\.SZ$', code):
        return True
    return False

def is_sz_esa_gem(code, hq):
    if hq == 'ESA.GEM' and re.match(r'30\d{4}\.SZ$', code):
        return True
    return False

def is_sz_em_cef(code, hq):
    if hq == 'EM.CEF' and re.match(r'(16[0-9]|184|15[0-1])\d{3}\.SZ$', code):
        return True
    return False

def is_sz_em_etf(code, hq):
    if hq == 'EM.ETF' and re.match(r'159\d{3}\.SZ$', code):
        return True
    return False

def is_sz(code, hq):
    if is_sz_mri(code, hq) or is_sz_esa_m(code,hq) or is_sz_esa_smse(code, hq) or is_sz_esa_gem(code, hq):
        return True
    return False

def is_hk_es(code, hq):
    if hq == 'ES' and re.match(r'\d{5}\.HK$', code):
        return True
    return False

def is_hk(code, hq):
    if is_hk_es(code, hq):
        return True
    return False

# get conv-bond-stocks
def get_cbs():
    try:
        pool = redis.ConnectionPool(host='r-bp170a80120560d4669.redis.rds.aliyuncs.com', port=6379, db=0,password='qF4thCEZ9Pw3', max_connections=50)
        redis_cli = redis.Redis(connection_pool=pool)
        key = "conv_bond_stocks"
        ret = redis_cli.get(key)
        ret = json.loads(ret.decode())
        cbs = list(ret.keys())
        return cbs
    except:
        return []

def get_stocks(cli):
    # stocks collection
    #coll = cli.god.stocks
    #coll = cli.god.stocks_reals
    coll = cli.god.stocks_static_info
    ret = coll.find({}, {'_id', 'hq_type_code'})

    ss = []
    sz = []
    for s in ret:
        if None == s.get('_id') or None == s.get('hq_type_code'):
            continue
        if is_ss(s['_id'], s['hq_type_code']):
            ss.append(s['_id'])
        elif is_sz(s['_id'], s['hq_type_code']):
            sz.append(s['_id'])

    '''
    coll = cli.god.hkstocks
    ret = coll.find({}, {'_id', 'hq_type_code'})

    hk = []
    for s in ret:
        if None == s.get('_id') or None == s.get('hq_type_code'):
            continue
        if is_hk(s['_id'], s['hq_type_code']):
            hk.append(s['_id'])
    hk.sort()
    '''
    cbs = get_cbs()
    for s in cbs:
        if s[8] == 'S':
            ss.append(s)
        elif s[8] == 'Z':
            sz.append(s)
        else:
            pass


    ss.sort()
    sz.sort()
    with open('stocks', 'w') as fp:
        for s in ss:
            fp.write(s)
            fp.write('\n')
        for s in sz:
            fp.write(s)
            fp.write('\n')
        '''
        for s in hk:
            fp.write(s)
            fp.write('\n')
        '''
        fp.close()


if __name__ == '__main__':
    # product
    cli = connect_to_server('10.47.162.196', 27017)
    # test
    #cli = connect_to_server('10.46.64.71', 37017)
    get_stocks(cli)
