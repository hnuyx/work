#!/bin/bash

#g++ -o test c-mongodb-cxx.cpp -I/usr/local/include/bsoncxx/v_noabi/ -I/usr/local/include/mongocxx/v_noabi --std=c++11 -lmongocxx -lbsoncxx -g
#g++ -o test l-trade-status.cpp -I/usr/local/include/bsoncxx/v_noabi/ -I/usr/local/include/mongocxx/v_noabi --std=c++11 -lmongocxx -lbsoncxx -g
#g++ -o test d-mongodb-cxx-index.cpp -I/usr/local/include/bsoncxx/v_noabi/ -I/usr/local/include/mongocxx/v_noabi --std=c++11 -lmongocxx -lbsoncxx -g
g++ -o test t-mysql.cpp -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient
