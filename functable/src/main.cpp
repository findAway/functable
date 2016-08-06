#include <stdio.h>
#include "functable.h"

int PTemp(void* p, int nFlag1, int nFlag2)
{
	printf("nFlag1:%d, nFlag2:%d\n", nFlag1, nFlag2);
	return 0;
}

class CTemp
{
public:
	CTemp();
	int Dump(void* p, int nFlag);
};

#define FUNC_NAME(C, F) C##_##F

#define GEN_FUNC(C, F) int C##_##F(void* p, int nFlag1, int nFlag2)\
						{\
							return ((C*)nFlag1)->F(p, nFlag2); \
						}

CTemp::CTemp()
{
}

GEN_FUNC(CTemp, Dump);
int CTemp::Dump(void* p, int nFlag)
{
	printf("p:%d, nFlag:%d\n", (int)p, nFlag);
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
		pfFunc((void*)0, nFlag1, nFlag2);
	}

	//测试类方法的注册及使用
	CTemp* pCTemp = new CTemp;
	pfFuncTable->RegFunc(123, FUNC_NAME(CTemp, Dump), (int)pCTemp, 123);
	pfFunc = pfFuncTable->GetFunc(123, nFlag1, nFlag2);
	if (pfFunc != NULL)
	{
		pfFunc((void*)0, nFlag1, nFlag2);
	}

	delete pCTemp;
	delete pfFuncTable;

	printf("Press any key to exit...\n");
	getchar();
	return 0;
}