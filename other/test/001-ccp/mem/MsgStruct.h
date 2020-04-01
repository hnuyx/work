#pragma once

#include <string>  
#include <limits.h>
#include <float.h>
using namespace std;  



#pragma pack(push) //保存对齐状态
#pragma pack(4)//设定为4字节对齐


class DayInfo
{
public:
	DayInfo()
	{
		open = 0;
		high = 0;
		low = DBL_MAX;
		close = 0;
		prev_close = 0;
		turnover = 0;
		volume = 0;
		trd_time = 0;
		ref_time = 0;
		bidprice = 0;
		bidsize = 0;
		askprice = 0;
		asksize = 0;
	}
	int trd_time;
	int ref_time;
	double turnover;
	double prev_close;
	double open;
	double high;
	double low;
	double close;

	double bidprice;
	unsigned int bidsize;
	double askprice;
	unsigned int asksize;

	long long volume;
};

class OrderInfo;
class AnalysisItem
{

public:
	double mMoney;
	//int matchedBuyOrders;
	//int matchedSellOrders;

	int iMatchedBuyOrders;
	int iMatchedSellOrders;
	int pMatchedBuyOrders;
	int pMatchedSellOrders;

	int BuyOrderNum;
	int SellOrderNum;

	double iBuy;
	double iBuyVol;
	int iBuyOrderNum;

	double iSell;
	double iSellVol;
	int iSellOrderNum;

	double pBuy;
	double pBuyVol;
	int pBuyOrderNum;

	double pSell;
	double pSellVol;
	int pSellOrderNum;

	double cancelledBuyVol;
	double cancelledSellVol;

	AnalysisItem(double money);
	bool processOrder(OrderInfo* oi);
	string toString(const char* name = NULL);
	std::string getSqlData(const char* name = NULL);
	std::string getMetaData(const char* name = NULL);
	bool isInRange(OrderInfo* order,double money);
	void removeOrder( OrderInfo * order );
};


class m_security_data
{
public:
	char code[8];
	DayInfo dayinfo;
	unsigned int WFLAG;
	AnalysisItem items[10]; 
	std::string getMetaData();
	std::string toString();
};

#pragma pack(pop)//恢复对齐状态

int initShareMem();
void closeShareMem();

struct OUTPUT_FORMAT{
	string BEGIN_TABLE;
	string BEGIN_LINE;
	string SPLIT_CHAR;
	string END_LINE;
	string END_TABLE;
};

extern OUTPUT_FORMAT format;

