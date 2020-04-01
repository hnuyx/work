#include "MsgStruct.h"  
#include <iostream>
#include <sstream>
using namespace std;

#define NEW_LINE true

const int AItemSize = 9;
OUTPUT_FORMAT format;


std::string AnalysisItem::toString(const char* name)
{
	stringstream ss;
	ss.precision(0);
	ss	<< fixed ;

	if(name != NULL)
	{
		ss << "#"<< name <<"#"  << format.SPLIT_CHAR;
	}
	else if(mMoney == DBL_MAX)
	{
		ss << "#INF#"  << format.SPLIT_CHAR;
	}
	else
		ss << "#" << mMoney <<"#"  << format.SPLIT_CHAR;

	ss 

		<< (pBuyVol+iBuyVol) << format.SPLIT_CHAR
		<< (pSellVol+iSellVol) << format.SPLIT_CHAR
		<< BuyOrderNum << format.SPLIT_CHAR
		<< SellOrderNum << format.SPLIT_CHAR
		<< (iMatchedSellOrders+pMatchedSellOrders) << format.SPLIT_CHAR
		<< (iMatchedBuyOrders+pMatchedBuyOrders)<< format.SPLIT_CHAR
		<< " " << format.SPLIT_CHAR
		;

	ss << iBuy  << format.SPLIT_CHAR 
		<< iBuyVol << format.SPLIT_CHAR
		<< iBuyOrderNum << format.SPLIT_CHAR 
		<< iMatchedSellOrders << format.SPLIT_CHAR;
	ss.precision(4);
	ss << (iBuyVol>0?(iBuy/iBuyVol):0) << format.SPLIT_CHAR ; //均价
	ss.precision(0);
	ss << (iBuyOrderNum>0?(iBuyVol/iBuyOrderNum):0) << format.SPLIT_CHAR  //均手

		<< iSell  << format.SPLIT_CHAR 
		<< iSellVol << format.SPLIT_CHAR
		<< iSellOrderNum << format.SPLIT_CHAR 
		<< iMatchedBuyOrders << format.SPLIT_CHAR;
	ss.precision(4);
	ss << (iSellVol>0?(iSell/iSellVol):0) << format.SPLIT_CHAR  ;//均价
	ss.precision(0);
	ss << (iSellOrderNum>0?(iSellVol/iSellOrderNum):0) << format.SPLIT_CHAR  //均手

		<< pBuy  << format.SPLIT_CHAR 
		<< pBuyVol << format.SPLIT_CHAR
		<< pBuyOrderNum << format.SPLIT_CHAR 
		<< pMatchedSellOrders << format.SPLIT_CHAR;
	ss.precision(4);
	ss << (pBuyVol>0?(pBuy/pBuyVol):0 )<< format.SPLIT_CHAR ; //均价
	ss.precision(0);
	ss << (pBuyOrderNum>0?(pBuyVol/pBuyOrderNum):0 )<< format.SPLIT_CHAR  //均手

		<< pSell  << format.SPLIT_CHAR 
		<< pSellVol << format.SPLIT_CHAR
		<< pSellOrderNum << format.SPLIT_CHAR 
		<< pMatchedBuyOrders << format.SPLIT_CHAR;
	ss.precision(4);
	ss << (pSellVol>0?(pSell/pSellVol):0 )<< format.SPLIT_CHAR  ;//均价
	ss.precision(0);
	ss << (pSellOrderNum>0?(pSellVol/pSellOrderNum):0) << format.SPLIT_CHAR  //均手
		;

	return ss.str();
}


std::string m_security_data::getMetaData()
{
	AnalysisItem* mTotal = &items[AItemSize-1];
	stringstream ss;

	ss << format.SPLIT_CHAR;

	ss << "SecurityID"  << format.SPLIT_CHAR ;
	ss << mTotal->getMetaData("SUM");
	if(!NEW_LINE)
	{
		for(int i=0;i<AItemSize-1;i++)
		{
			ss << items[i].getMetaData();
		}
	}

	return ss.str();
}

std::string m_security_data::toString()
{
	AnalysisItem* mTotal = &items[AItemSize-1];
	string SecurityID(code,0,8);
	stringstream ss;

	ss << format.SPLIT_CHAR << SecurityID  << format.SPLIT_CHAR ;
	for(int i=0;i<32;i++)
	{
		ss << format.SPLIT_CHAR;
	}
	ss << format.END_LINE;

	ss.precision(0);
	ss <<format.BEGIN_LINE << format.SPLIT_CHAR << SecurityID  << format.SPLIT_CHAR ;
	ss << mTotal->toString("SUM");

	for(int i=0;i<AItemSize-1;i++)
	{

		ss << format.END_LINE << format.BEGIN_LINE << format.SPLIT_CHAR << SecurityID << format.SPLIT_CHAR;
		ss << items[i].toString();
	}
	return ss.str();

}

std::string AnalysisItem::getMetaData(const char* name)
{
	stringstream ss;
	ss.precision(0);
	ss	<< fixed;
	if(name != NULL)
	{
		ss << "#"<< name <<"#"  << format.SPLIT_CHAR;
	}
	else if(mMoney == DBL_MAX)
	{
		ss << "#INF#"  << format.SPLIT_CHAR;
	}
	else
		ss << "#" << mMoney <<"#"  << format.SPLIT_CHAR;

	ss 
		<< "BuyOrderVol" << format.SPLIT_CHAR
		<< "SellOrderVol" << format.SPLIT_CHAR
		<< "BuyOrderNum" << format.SPLIT_CHAR
		<< "SellOrderNum" << format.SPLIT_CHAR
		<< "mtSellOrderNum" << format.SPLIT_CHAR
		<< "mtBuyOrderNum" << format.SPLIT_CHAR
		<< " "<<format.SPLIT_CHAR
		;

	ss	<< "iBuy"  << format.SPLIT_CHAR 
		<< "iBuyVol" << format.SPLIT_CHAR
		<< "iBuyOrderNum" << format.SPLIT_CHAR 
		<< "iMtSellOrderNum" << format.SPLIT_CHAR
		<< "VWAP" << format.SPLIT_CHAR  //均价
		<< "AVOL" << format.SPLIT_CHAR  //均手

		<< "iSell"  << format.SPLIT_CHAR 
		<< "iSellVol" << format.SPLIT_CHAR
		<< "iSellOrderNum" << format.SPLIT_CHAR 
		<< "iMtBuyOrderNum" << format.SPLIT_CHAR
		<< "VWAP" << format.SPLIT_CHAR  //均价
		<< "AVOL" << format.SPLIT_CHAR  //均手

		<< "pBuy"  << format.SPLIT_CHAR 
		<< "pBuyVol" << format.SPLIT_CHAR
		<< "pBuyOrderNum" << format.SPLIT_CHAR 
		<< "pMtSellOrderNum" << format.SPLIT_CHAR
		<< "VWAP" << format.SPLIT_CHAR  //均价
		<< "AVOL" << format.SPLIT_CHAR  //均手

		<< "pSell"  << format.SPLIT_CHAR 
		<< "pSellVol" << format.SPLIT_CHAR
		<< "pSellOrderNum" << format.SPLIT_CHAR 
		<< "pMtBuyOrderNum" << format.SPLIT_CHAR
		<< "VWAP" << format.SPLIT_CHAR  //均价
		<< "AVOL" << format.SPLIT_CHAR  //均手
		;

	return ss.str();
}