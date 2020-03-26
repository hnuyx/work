
import pymysql
cursor =  pymysql.connect(host='level2-parse-rds.mysql.rds.aliyuncs.com',port=3306,user='root',password='UUd9nAQOuCvwt2wil@DL',database='mysql_minute',
        charset='utf8',connect_timeout=10).cursor(pymysql.cursors.DictCursor)

sql = "select code from l2data_2019 where date = '20190910' order by code;"

rows = cursor.execute(sql)
data = cursor.fetchall()

with open('2.log', 'w') as fp:
    l = len(data)
    pre = 0
    for i in range(l):
        if(pre != data[i]['code']):
            fp.write(data[i]['code'])
            fp.write('\n')
            pre = data[i]['code']
    fp.close()


