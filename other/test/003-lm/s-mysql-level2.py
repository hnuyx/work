import pymysql
cursor =  pymysql.connect(host='level2-parse-rds.mysql.rds.aliyuncs.com',port=3306,user='root',password='UUd9nAQOuCvwt2wil@DL',database='mysql_minute',
        charset='utf8',connect_timeout=10).cursor(pymysql.cursors.DictCursor)
sql = "select code,date,name, BuyOrderNum as buyordernum,SellOrderNum as sellordernum,iBuy as ibuy, iBuyVol as ibuyvol,iBuyOrderNum as ibuyordernum,iSell as isell, iSellVol as isellvol,iSellOrderNum as isellordernum,pBuy as pbuy,pBuyVol as pbuyvol,pBuyOrderNum as pbuyordernum,pSell as psell, pSellVol as psellvol,pSellOrderNum as psellordernum from l2data_2019 where date = '20190611';"
rows = cursor.execute(sql)
data = cursor.fetchall()

{'code': 'SH600000', 'date': '20190611', 'name': '#SUM#', 'buyordernum': 14558, 'sellordernum': 13268, 'ibuy': 382050397, 'ibuyvol': 33582034, 'ibuyordernum': 9535, 'isell': 223213458, 'isellvol': 19633183, 'isellordernum': 5765, 'pbuy': 212413671, 'pbuyvol': 18684183, 'pbuyordernum': 5229, 'psell': 371250610, 'psellvol': 32633034, 'psellordernum': 7728}

for i in range(9):
    print(data[i]['code'], data[i]['date'], data[i]['name'], data[i]['buyordernum'], data[i]['sellordernum'], data[i]['ibuy'], data[i]['ibuyvol'], data[i]['ibuyordernum'], data[i]['isell'], data[i]['isellvol'], data[i]['isellordernum'], data[i]['pbuy'], data[i]['pbuyvol'], data[i]['pbuyordernum'], data[i]['psell'], data[i]['psellvol'], data[i]['psellordernum'])
