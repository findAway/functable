#include <stdio.h>
#include "functable.h"

int PTemp(int nFlag1, int nFlag2, void* pData)
{
	printf("nFlag1:%d, nFlag2:%d\n", nFlag1, nFlag2);
	return 0;
}

class CTemp
{
public:
	CTemp();
	int Dump(int nFlag, void* pData);
};

#define FUNC_NAME(C, F) C##_##F

#define GEN_FUNC(C, F) int C##_##F(int nFlag1, int nFlag2, void* pData)\
						{\
							if (nFlag1 == 0) \
								return 1; \
							return ((C*)nFlag1)->F(nFlag2, pData); \
						}

CTemp::CTemp()
{
}

GEN_FUNC(CTemp, Dump);
int CTemp::Dump(int nFlag, void* pData)
{
	printf("nFlag:%d, pData:%d\n", nFlag, (int)pData);
	return 0;
}

int main(int argc, char* argv[])
{
	CFuncTable* pfFuncTable = new CFuncTable(5);

	for (int n = 0; n < 2; n++)
	{
		pfFuncTable->RegFunc(n, PTemp, n, 0);
	}

	int nFlag1;
	int nFlag2;
	PFunc pfFunc = pfFuncTable->GetFunc(1, nFlag1, nFlag2);
	if (pfFunc != NULL)
	{
		pfFunc(nFlag1, nFlag2, (void*)0);
	}

	//测试类方法的注册及使用
	CTemp* pCTemp = new CTemp;
	pfFuncTable->RegFunc(123, FUNC_NAME(CTemp, Dump), (int)pCTemp, 123);
	pfFunc = pfFuncTable->GetFunc(123, nFlag1, nFlag2);
	if (pfFunc != NULL)
	{
		pfFunc(nFlag1, nFlag2, (void*)0);
	}

	delete pCTemp;
	delete pfFuncTable;

	printf("Press any key to exit...\n");
	getchar();
	return 0;
}