#include<iostream>
using namespace std;
#define MAXQSIZE 6
#define OK 'o'
#define ERROR 'e'
typedef int QElemType;
typedef int Status;

//����ѭ�����нṹ��
typedef struct
{
	QElemType* base;//����ռ����ַ
	int front;//ͷָ��
	int rear;//βָ��
}SqQueue;

//1.ѭ�����еĳ�ʼ��
Status InitQueue(SqQueue& Q)
{//����һ���ն���Q
	Q.base = new QElemType[MAXQSIZE];//Ϊ���з���һ���������ΪMAXQSIZE������ռ�
	if (!Q.base)
		exit(OVERFLOW);//�������ʧ��
	Q.front = Q.rear = 0;//ͷָ���βָ����Ϊ0������Ϊ��
	return OK;
}

//2.ѭ�����е����
Status EnQueue(SqQueue& Q, QElemType e)
{//����Ԫ��eΪQ���µĶ�βԪ��
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
		return ERROR;//βָ����ѭ�������ϼ�1�����ͷָ�룬��������
	Q.base[Q.rear] = e;//��Ԫ��e�����β
	Q.rear = (Q.rear + 1) % MAXQSIZE;//��βָ���1
	return OK;
}

//3.ѭ�����еĳ���
Status DeQueue(SqQueue& Q, QElemType& e)
{//ɾ��Q�Ķ�ͷԪ�أ���e������ֵ
	if (Q.front == Q.rear)
		return ERROR;//�ӿ�
	e = Q.base[Q.front];//�����ͷԪ��
	Q.front = (Q.front + 1) % MAXQSIZE;//��ͷָ���1
	return OK;
}

//4.ȡѭ�����еĶ�ͷԪ��
QElemType GetHead(SqQueue Q)
{//����Q�Ķ�ͷԪ�أ����޸Ķ�ͷָ��
	if (Q.front != Q.rear)
		return Q.base[Q.front];//���ض�ͷԪ�ص�ֵ����ͷָ�벻��
	else
		return ERROR;
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
	SqQueue	Q;				//����ѭ������Q
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