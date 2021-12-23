#include<iostream>
using namespace std;
#define OK 'o'
#define ERROR 'e'
typedef int SElemType;
typedef int Status;

//����˳��ջ�ṹ��
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

//1.��ջ�ĳ�ʼ��
Status InitStack(LinkStack& S)
{//����һ����ջS��ջ��ָ���ÿ�
	S = NULL;
	return OK;
}

//2.��ջ����ջ
Status Push(LinkStack& S, SElemType e)
{//��ջ������Ԫ��e
	StackNode* p;
	p = new StackNode;	//�����½��
	p->data = e;		//���½����������Ϊe
	p->next = S;		//���½�����ջ��
	S = p;				//�޸�ջ��ָ��Ϊp
	return OK;
}

//3.��ջ�ĳ�ջ
Status Pop(LinkStack& S, SElemType& e)
{//ɾ��S��ջ��Ԫ�أ���e������ֵ
	StackNode* p;		//������ʱָ��p,������ʱ����ջ��Ԫ��
	if (S == NULL)
		return ERROR;	//ջ��
	e = S->data;		//��ջ��Ԫ�ظ���e
	p = S;				//��p��ʱ����ջ��Ԫ�ؿռ䣬�Ա��ͷ�
	S = S->next;		//�޸�ջ��ָ��
	delete p;			//�ͷ�p
	return OK;
}

//4.ȡ��ջ��ջ��Ԫ��
SElemType GetTop(LinkStack S)
{//����S��ջ��Ԫ�أ����޸�ջ��ָ��
	if (S != NULL)
		return S->data;	//����ջ��Ԫ�ص�ֵ��ջ��ָ�벻��
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
	LinkStack S;	//����˳��ջS
	InitStack(S);	//��ʼ��˳��ջS

	int wm;			//��������ѡ�����
	ShowMenu();		//��ʾ�����˵�

	//�������ѭ��
	while (true)
	{
		cout << "������������룺";
		cin >> wm;	//ѡ���������
		switch (wm)
		{//ѡ��ṹ
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