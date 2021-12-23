#include<iostream>
using namespace std;
#define OK 'o'
#define ERROR 'e'
typedef int QElemType;
typedef int Status;

//�������ӽṹ��
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;	//��ͷָ��
	QueuePtr rear;	//��βָ��
}LinkQueue;

//1.���ӵĳ�ʼ��
Status InitQueue(LinkQueue& Q)
{//����һ���ն���
	Q.front = Q.rear = new QNode;	//�����½����Ϊͷ��㣬��ͷ�Ͷ�βָ��ָ��˽ڵ�
	Q.front->next = NULL;			//ͷ����ָ�����ÿ�
	return OK;
}

//2.���ӵ����
Status EnQueue(LinkQueue& Q, QElemType e)
{//����Ԫ��e��ΪQ���µĶ�βԪ��
	QNode* p;			//�����½��
	p = new QNode;		//Ϊ���Ԫ�ط�����ռ䣬��ָ��pָ��
	p->data = e;		//���½����������Ϊe
	p->next = NULL;
	Q.rear->next = p;	//���½����뵽��β
	Q.rear = p;			//�޸Ķ�βָ��
	return OK;
}

//3.���ӵĳ���
Status DeQueue(LinkQueue& Q, QElemType& e)
{//ɾ��Q�Ķ�ͷԪ�أ�����e������ֵ
	QNode* p;				//�����µ���ʱ���p������ָ���ͷԪ��
	if (Q.front == Q.rear)
		return ERROR;		//������Ϊ�գ�����ERROR
	p = Q.front->next;		//pָ���ͷԪ��
	e = p->data;			//e�����ͷԪ�ص�ֵ
	Q.front->next = p->next;//�޸�ͷ����ָ����
	if (Q.rear == p)
		Q.rear = Q.front;	//���һ��Ԫ�ر�ɾ����βָ��ָ��ͷ���
	delete p;				//�ͷ�ԭ��ͷԪ�صĿռ�
	return OK;
}

//4.ȡ���ӵĶ�ͷԪ��
QElemType GetHead(LinkQueue Q)
{//����Q�Ķ�ͷԪ�أ����޸�ͷָ��
	if (Q.front != Q.rear)
		return Q.front->next->data;	//�����зǿգ����ض�ͷԪ�ص�ֵ����ͷָ�벻��
	else
		return ERROR;				//������Ϊ�գ�����ERROR
}

//��ʾ�����˵�
void ShowMenu()
{
	cout << "=========================" << endl;
	cout << "***   1---��ʼ��      ***" << endl;
	cout << "***   2---���        ***" << endl;
	cout << "***   3---����        ***" << endl;
	cout << "***   4---ȡ��ͷԪ��  ***" << endl;
	cout << "***   0---�˳�        ***" << endl;
	cout << "=========================" << endl;
}

int main()
{
	LinkQueue Q;			//����ѭ������Q
	InitQueue(Q);			//��ʼ��Q

	int wm;					//��������ѡ�����
	ShowMenu();				//��ʾ�����˵�

	//�������ѭ��
	while (true)
	{
		cout << "������������룺";
		cin >> wm;			//ѡ���������
		switch (wm)
		{//ѡ��ṹ
		case 1:
			if (InitQueue(Q) == OK)//��ʼ���ɹ�ʱ����ʾ�û�
				cout << "��ʼ���ɹ���" << endl;
			else//���ɹ�ʱ����ʾ����ʧ��
				cout << "����ռ����ʧ�ܣ�" << endl;
			break;

		case 2:
		{
			QElemType e_EnQ;
			cout << "������Ҫ��ӵ�Ԫ�أ�";
			cin >> e_EnQ;
			if (EnQueue(Q, e_EnQ) == OK)//��ӳɹ�ʱ����ӡ�����Ԫ�أ�������ʾ���ʧ��
				cout << "\t\t\t��ӣ�" << e_EnQ << endl;
			else
				cout << "\t\t\t���ʧ�ܣ�����������" << endl;
			break;
		}

		case 3:
		{
			QElemType e_DeQ;
			if (DeQueue(Q, e_DeQ) == OK)//���ӳɹ�ʱ����ӡ������Ԫ�أ�������ʾ����ʧ��
				cout << "\t\t\t\t���ӣ�" << e_DeQ << endl;
			else
				cout << "\t\t\t\t����ʧ�ܣ��ӿգ�" << endl;
			break;
		}

		case 4:
			if (GetHead(Q) != ERROR)//�Ӳ�Ϊ��ʱ����ӡ��ͷԪ��
				cout << "��ͷԪ��Ϊ��" << GetHead(Q) << endl;
			else//����Ϊ��ʱ����ʾ�û�
				cout << "����Ϊ�գ�" << endl;
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