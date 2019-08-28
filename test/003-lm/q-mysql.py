
import pymysql
import time

def connect():
    db = pymysql.connect(host='level2-parse-rds.mysql.rds.aliyuncs.com', port=3306, user='root',
            password='UUd9nAQOuCvwt2wil@DL', database='mysql_minute', charset='utf8')
    cursor = db.cursor(pymysql.cursors.DictCursor)  # 拿到游标,将拿到的信息转换成字典
