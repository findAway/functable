/**
* 2016/8/6
* 此类用于存储函数指针，并与某消息对应起来，
* 可通过此消息获取到对应的函数指针
*/

#ifndef __FUNCTABLE_H__
#define __FUNCTABLE_H__

//定义函数指针，被注册的函数指针需为此类型
typedef int (*PFunc)(int nFlag1, int nFlag2, void* pData);

typedef struct tabFuncCell
{
	bool bUsed;    //此单元是否被使用
	int nMsgType;  //函数指针相关的消息类型
	PFunc pfFunc;  //函数的指针
	int nFlag1;    //标识1，可作为pfFunc调用时的参数传入，以便pfFunc中能做进一步的区分
	int nFlag2;    //标识2，可作为pfFunc调用时的参数传入，以便pfFunc中能做进一步的区分

	tabFuncCell()
	{
		bUsed = false;
		nMsgType = -1;
		pfFunc = NULL;
		nFlag1 = 0;
		nFlag2 = 0;
	}
} TFuncCell;

class CFuncTable
{
public:
	CFuncTable(int nTableSize);
	~CFuncTable();
	
	//注册函数指针，成功返回0，失败返回非0。已注册的消息再次注册返回失败。
	//nMsgType需大于0， pfFunc不为空
	int RegFunc(int nMsgType, PFunc pfFunc, int nFlag1, int nFlag2);

	//反注册nMsgType相关的函数指针，成功返回0，失败返回非0，重复调用返回成功。
	int UnRegFunc(int nMsgType);

	//根据消息nMsgType获取相关的函数， nFlag为输出型参数，
	//返回RegFunc时传入的nFlag值。
	PFunc GetFunc(int nMsgType, int& nFlag1, int& nFlag2);

private:
	bool m_bInit;
	int m_nTableSize;
	TFuncCell* m_ptFuncCells;
};

#endif /*__FUNCTABLE_H__*/