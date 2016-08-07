/**
* 2016/8/6
* �������ڴ洢����ָ�룬����ĳ��Ϣ��Ӧ������
* ��ͨ������Ϣ��ȡ����Ӧ�ĺ���ָ��
*/

#ifndef __FUNCTABLE_H__
#define __FUNCTABLE_H__

//���庯��ָ�룬��ע��ĺ���ָ����Ϊ������
typedef int (*PFunc)(int nFlag1, int nFlag2, void* pData);

typedef struct tabFuncCell
{
	bool bUsed;    //�˵�Ԫ�Ƿ�ʹ��
	int nMsgType;  //����ָ����ص���Ϣ����
	PFunc pfFunc;  //������ָ��
	int nFlag1;    //��ʶ1������ΪpfFunc����ʱ�Ĳ������룬�Ա�pfFunc��������һ��������
	int nFlag2;    //��ʶ2������ΪpfFunc����ʱ�Ĳ������룬�Ա�pfFunc��������һ��������

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
	
	//ע�ắ��ָ�룬�ɹ�����0��ʧ�ܷ��ط�0����ע�����Ϣ�ٴ�ע�᷵��ʧ�ܡ�
	//nMsgType�����0�� pfFunc��Ϊ��
	int RegFunc(int nMsgType, PFunc pfFunc, int nFlag1, int nFlag2);

	//��ע��nMsgType��صĺ���ָ�룬�ɹ�����0��ʧ�ܷ��ط�0���ظ����÷��سɹ���
	int UnRegFunc(int nMsgType);

	//������ϢnMsgType��ȡ��صĺ����� nFlagΪ����Ͳ�����
	//����RegFuncʱ�����nFlagֵ��
	PFunc GetFunc(int nMsgType, int& nFlag1, int& nFlag2);

private:
	bool m_bInit;
	int m_nTableSize;
	TFuncCell* m_ptFuncCells;
};

#endif /*__FUNCTABLE_H__*/