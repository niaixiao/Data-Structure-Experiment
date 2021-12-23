#include<iostream>
using namespace std;
#define MAXSIZE 100					//˳��ջ����ռ�ĳ�ʼ������
#define OK 'o'
#define ERROR 'e'
typedef int SElemType;
typedef int Status;

//����˳��ջ�ṹ��
typedef struct
{
	SElemType* base;				//ջ��ָ��
	SElemType* top;					//ջ��ָ��
	int stacksize;					//ջ���õ��������
}SqStack;

//1.˳��ջ�ĳ�ʼ��
Status InitStack(SqStack& S)
{//����һ����ջ
	S.base = new SElemType[MAXSIZE];//Ϊ˳��ջ��̬�����������ΪMAXSIZE������ռ�
	if (!S.base)
		exit(OVERFLOW);				//����ռ����ʧ��ʱ�˳�
	S.top = S.base;					//top��ʼΪbase����ջ
	S.stacksize = MAXSIZE;			//stacksize��Ϊջ���������MAXSIZE
	return OK;
}

//2.˳��ջ����ջ
Status Push(SqStack& S, SElemType e)
{//����Ԫ��eΪ�µ�ջ��Ԫ��
	if (S.top - S.base == S.stacksize)
		return ERROR;				//ջ����
	*S.top++ = e;					//��Ԫ��eѹ��ջ����ջ��ָ���1
	return OK;
}

//3.˳��ջ�ĳ�ջ
Status Pop(SqStack& S, SElemType& e)
{//ɾ��S��ջ��Ԫ�أ���e������ֵ
	if (S.top == S.base)
		return ERROR;				//ջ��
	e = *--S.top;					//ջ��ָ���1����ջ��Ԫ�ظ�ֵ��e
	return OK;
}

//4.ȡ˳��ջ��ջ��Ԫ��
SElemType GetTop(SqStack S)
{//����S��ջ��Ԫ�أ����޸�ջ��ָ��
	if (S.top != S.base)			//ջ�ǿ�ʱ������ջ��Ԫ�ص�ֵ��ָ�벻��
		return *(S.top - 1);
	else
		return ERROR;
}

//��ʾ�����˵�
void ShowMenu()
{
	cout << "=========================" << endl;
	cout << "***   1---��ʼ��      ***" << endl;
	cout << "***   2---��ջ        ***" << endl;
	cout << "***   3---��ջ        ***" << endl;
	cout << "***   4---ȡջ��Ԫ��  ***" << endl;
	cout << "***   0---�˳�        ***" << endl;
	cout << "=========================" << endl;
}

//������
int main()
{
	SqStack S;				//����˳��ջS
	InitStack(S);			//��ʼ��˳��ջS
	
	int wm;					//��������ѡ�����
	ShowMenu();				//��ʾ�����˵�

	//�������ѭ��
	while (true)
	{
		cout << "������������룺";
		cin >> wm;			//ѡ���������
		switch (wm)
		{					//ѡ��ṹ
		case 1:
			if (InitStack(S) == OK)//��ʼ���ɹ�ʱ����ʾ�û�
				cout << "��ʼ���ɹ���" << endl;
			else//���ɹ�ʱ����ʾ����ʧ��
				cout << "����ռ����ʧ�ܣ�" << endl;
			break;

		case 2:
		{
			SElemType e_Push;
			cout << "������Ҫ��ջ��Ԫ�أ�";
			cin >> e_Push;
			if (Push(S, e_Push) == OK)//��ջ�ɹ�ʱ����ӡ����ջԪ�أ�������ʾ��ջʧ��
				cout << "\t\t\t��ջ��" << e_Push << endl;
			else
				cout << "\t\t\t��ջʧ�ܣ�ջ������" << endl;
			break;
		}

		case 3:
		{
			SElemType e_Pop;
			if (Pop(S, e_Pop) == OK)//��ջ�ɹ�ʱ����ӡ����ջԪ�أ�������ʾ��ջʧ��
				cout << "\t\t\t\t��ջ��" << e_Pop << endl;
			else
				cout << "\t\t\t\t��ջʧ�ܣ�ջ�գ�" << endl;
			break;
		}

		case 4:
			if (GetTop(S) != ERROR)//ջ��Ϊ��ʱ����ӡջ��Ԫ��
				cout << "ջ��Ԫ��Ϊ��" << GetTop(S) << endl;
			else//ջΪ��ʱ����ʾ�û�
				cout << "ջ�գ�" << endl;
			break;

		case 0:
		{
			int end = 0;
			cout << "ȷ��Ҫ�˳���\n������1��ȷ���˳�������������ȡ����" << endl;
			cin >> end;
			if (end == 1)
			{
				cout << "��ӭ�´�ʹ�ã�" << endl;
				return 0;
			}
			break;
		}

		default:
			cout << "��������ȷ�Ĳ������룡" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}