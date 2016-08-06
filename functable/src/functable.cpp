#include <stdio.h>
#include "functable.h"

CFuncTable::CFuncTable(int nTableSize)
{
	m_bInit = false;
	m_nTableSize = 0;
	m_ptFuncCells = NULL;

	m_ptFuncCells = new TFuncCell[nTableSize];
	if (m_ptFuncCells != NULL)
	{
		m_bInit = true;
		m_nTableSize = nTableSize;
	}
}

CFuncTable::~CFuncTable()
{
	m_bInit = false;
	m_nTableSize = 0;

	if (m_ptFuncCells != NULL)
	{
		delete[] m_ptFuncCells;
		m_ptFuncCells = NULL;
	}
}

int CFuncTable::RegFunc(int nMsgType, PFunc pfFunc, int nFlag1, int nFlag2)
{
	if (!m_bInit)
	{
		printf("#### not init ####\n");
		return 1;
	}

	if (nMsgType < 0)
	{
		printf("#### nMsgType < 0 ####\n");
		return 1;
	}

	if (pfFunc == NULL)
	{
		printf("#### pfFunc NULL ####\n");
		return 1;
	}

	//查找nMsgType是否已经注册及查找未使用的单元
	bool bHasReg = false;
	int nNotUsedCell = -1;
	for (int n = 0; n < m_nTableSize; n++)
	{
		if (m_ptFuncCells[n].bUsed)
		{
			if (m_ptFuncCells[n].nMsgType == nMsgType)
			{
				bHasReg = true;
				break;
			}
		}
		else
		{
			if (nNotUsedCell == -1)
			{
				nNotUsedCell = n;
			}
		}
	}

	if (bHasReg)
	{
		printf("#### MsgType %d has reg ####\n", nMsgType);
		return 1;
	}

	if (nNotUsedCell == -1)
	{
		printf("#### full, reg fail ####\n", nMsgType);
		return 1;
	}

	m_ptFuncCells[nNotUsedCell].nMsgType = nMsgType;
	m_ptFuncCells[nNotUsedCell].pfFunc = pfFunc;
	m_ptFuncCells[nNotUsedCell].nFlag1 = nFlag1;
	m_ptFuncCells[nNotUsedCell].nFlag2 = nFlag2;
	m_ptFuncCells[nNotUsedCell].bUsed = true;

	return 0;
}

int CFuncTable::UnRegFunc(int nMsgType)
{
	if (!m_bInit)
	{
		printf("#### not init ####\n");
		return 1;
	}

	for (int n = 0; n < m_nTableSize; n++)
	{
		if (m_ptFuncCells[n].bUsed)
		{
			if (m_ptFuncCells[n].nMsgType == nMsgType)
			{
				m_ptFuncCells[n].bUsed = false;
				m_ptFuncCells[n].nMsgType = -1;
				m_ptFuncCells[n].pfFunc = NULL;
				m_ptFuncCells[n].nFlag1 = 0;
				m_ptFuncCells[n].nFlag2 = 0;
				break;
			}
		}
	}

	return 0;
}

PFunc CFuncTable::GetFunc(int nMsgType, int& nFlag1, int& nFlag2)
{
	if (!m_bInit)
	{
		printf("#### not init ####\n");
		return NULL;
	}

	PFunc pRetFunc = NULL;
	for (int n = 0; n < m_nTableSize; n++)
	{
		if (m_ptFuncCells[n].bUsed)
		{
			if (m_ptFuncCells[n].nMsgType == nMsgType)
			{
				nFlag1 = m_ptFuncCells[n].nFlag1;
				nFlag2 = m_ptFuncCells[n].nFlag2;
				pRetFunc = m_ptFuncCells[n].pfFunc;
				break;
			}
		}
	}

	return pRetFunc;
}