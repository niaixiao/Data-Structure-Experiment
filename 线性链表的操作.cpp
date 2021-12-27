/*
Wang Meng @henu
*/
#include <iostream>
#define ERROR
using namespace std;
typedef int ElemType;

//������������
typedef struct LNode
{
	ElemType data;			//����������
	struct LNode* next;		//����ָ����
}LNode, * LinkList;

//��������ĳ�ʼ��
void InitList(LinkList& L)
{
	L = new LNode;			//�����½����Ϊͷ��㣬��ͷָ��Lָ��ͷ���
	L->next = NULL;			//ͷ����ָ�����ÿ�
}

//ͷ�巨����
void CreatList_H(LinkList& L, int n)
{
	LNode* p;				//�����½��
	cout << "������" << n << "�����ݣ�";
	for (int i = 1; i <= n; i++)
	{
		p = new LNode;
		cin >> p->data;
		//���½��嵽ͷָ�����
		p->next = L->next; L->next = p;
	}
}

//β�巨����
void CreatList_R(LinkList& L, int n)
{
	LNode* p;				//�����½��
	LNode* r;				//ָ���β���
	r = L;
	cout << "������" << n << "�����ݣ�";
	for (int i = 1; i <= n; i++)
	{
		p = new LNode;
		cin >> p->data;
		//���½��嵽��β
		r->next = p; r = p;
	}
	r->next = NULL;
}
//��ʾ����
void ShowList(LinkList L)
{
	LNode* p;				//���ڱ�����
	p = L->next;			//��ʼ����pָ����Ԫ���
	if (p == NULL)
		cout << "�գ�";
	while (p != NULL)
	{//���δ�ӡ����Ԫ��
		cout << " " << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//������İ�ֵ����
LNode* LocateElem(LinkList L, ElemType e)
{//�ڴ�ͷ���ĵ�����L�в���ֵΪe��Ԫ��
	LNode* p;				//���ڱ�����
	p = L->next;			//��ʼ����pָ����Ԫ���
	while (p && p->data != e)
		p = p->next;//������ֱ���ҵ���e��ȵ�Ԫ��
	return p;
}

//������Ĳ���
void ListInsert(LinkList& L, int i, ElemType e)
{//�ڴ�ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
	LNode* p, * s;
	int j = 0;
	p = L;
	while (p && (j < i - 1))
	{//���ҵ�i-1����㣬pָ��ý��
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
	{//�жϲ���λ���Ƿ����
		cout << "����λ�ò�����!" << endl;
		return ERROR;
	}
	s = new LNode;
	s->data = e;
	//������s
	s->next = p->next; p->next = s;
	cout << "����ɹ���" << endl;
}

//�������ɾ��
void ListDelete(LinkList& L, int i)
{//�ڴ�ͷ��������L�У�ɾ����i��Ԫ��
	LNode* p, * q;
	int j = 0;
	p = L;
	while ((p->next) && (j < i - 1))
	{//���ҵ�i-1����㣬pָ��ý��
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
	{//i>n��i<1ʱ��ɾ��λ�ò�����
		cout << "ɾ��λ�ò�����!" << endl;
		return ERROR;
	}
	q = p->next;			//��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
	p->next = q->next;		//�ı�ɾ�����ǰ������ָ����
	delete q;				//ɾ�����Ŀռ�
	cout << "ɾ���ɹ���" << endl;
}

//������ð�����򣨷ǽ���
LinkList Order(LinkList& L)
{
	LNode* p, * q;//�����½������L�е�Ԫ�رȽϴ�С
	//���м�ѡ������
	for (p = L->next; p != NULL; p = p->next)
	{//p����ƶ������г��ȼ�С
		for (q = p->next; q != NULL; q = q->next)
		{//ѡ����ǰ��������С��Ԫ�أ���ֵ��p->data
			if (p->data > q->data)
			{
				ElemType i = p->data;
				p->data = q->data;
				q->data = i;
			}
		}
	}
	return L;//����������L
}

//������������ĺϲ�
void MergeList_L(LinkList& LA, LinkList& LB, LinkList& LC)
{//��֪������LA��LB��Ԫ�ذ�ֵ�ǵݼ����� 
 //�鲢LA��LB�õ����±�LC��LC��Ԫ��Ҳ��ֵ�ǵݼ�����
	LNode* pa, * pb, * pc;
	pa = LA->next;
	pb = LB->next;			//pa��pb�ĳ�ֵ�ֱ�ָ��������ĵ�һ�����
	LC = LA;				//��LA��ͷ�����ΪLC��ͷ���
	pc = LC;				//pc�ĳ�ֵָ��LC��ͷ���
	while (pa && pb)
	{//LA��LB��δ�����β�����Ρ�ժȡ��������ֵ��С�Ľ����뵽LC�����
		if (pa->data <= pb->data)
		{//��ժȡ��pa��ָ���
			pc->next = pa;	//��pa��ָ������ӵ�pc��ָ���֮��
			pc = pa;		//pcָ��pa
			pa = pa->next;	//paָ����һ���
		}
		else
		{//��ժȡ��pb��ָ���
			pc->next = pb;	//��pb��ָ������ӵ�pc��ָ���֮��
			pc = pb;		//pcָ��pb
			pb = pb->next;	//pbָ����һ���
		}
	}
	pc->next = pa ? pa : pb;//���ǿձ��ʣ��β��뵽pc��ָ�Ľ���
	delete LB;				//�ͷ�LB��ͷ���
	cout << "�ϲ���ɣ�" << endl;
}

//��ʾ�����˵�
void showMenu()
{
	cout << "*******************************" << endl;
	cout << "****** 1������������     ******" << endl;
	cout << "****** 2����ʾ������     ******" << endl;
	cout << "****** 3�����ҵ�����     ******" << endl;
	cout << "****** 4�����뵥����     ******" << endl;
	cout << "****** 5��ɾ��������     ******" << endl;
	cout << "****** 6������������ϲ� ******" << endl;
	cout << "****** 0���˳�����       ******" << endl;
	cout << "*******************************" << endl;
}


int main()
{
	LNode* head;
	int wm = 0;
	InitList(head);//��ʼ������

	while (true)
	{
		showMenu();
		cout << "������������룺";
		if (!(cin >> wm))
		{//��������ʱ�������룬��ֹ��ѭ��
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		switch (wm)
		{
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		case 1://����������
			int n;
			cout << "��������������";
			cin >> n;
			CreatList_R(head, n);
			system("pause");
			system("cls");
			break;
		case 2://��ʾ������
			cout << "��ǰ����Ϊ��" << endl;
			ShowList(head);
			system("pause");
			system("cls");
			break;
		case 3://���ҵ�����
			ElemType eA;
			cout << "������������ݵ�ֵ��";
			cin >> eA;
			cout << "����" << eA << "��λ��Ϊ��" << LocateElem(head, eA) << endl;
			system("pause");
			system("cls");
			break;
		case 4://���뵥����
			int iB;
			ElemType eB;
			cout << "������������ݵ�λ�ã�";
			cin >> iB;
			cout << "������������ݵ�ֵ��";
			cin >> eB;
			ListInsert(head, iB, eB);
			system("pause");
			system("cls");
			break;
		case 5://ɾ��������
			int iC;
			cout << "������ɾ�����ݵ�λ�ã�";
			cin >> iC;
			ListDelete(head, iC);
			system("pause");
			system("cls");
			break;
		case 6://����������ϲ�
		{
			LNode* LA, * LB, * LC;
			InitList(LA); InitList(LB); InitList(LC);//��ʼ������
			//�½�����LA��LB
			int nA, nB;
			cout << "����������LA����������";
			cin >> nA; CreatList_R(LA, nA);//��������LA
			cout << "����������LB����������";
			cin >> nB; CreatList_R(LB, nB);//��������LB
			//������LA��LB����
			cout << "��������LAΪ��" << endl; ShowList(Order(LA));
			cout << "��������LBΪ��" << endl; ShowList(Order(LB));
			//�ϲ�LA��LB
			MergeList_L(LA, LB, LC);
			cout << "�ϲ���LCΪ��" << endl;
			ShowList(LC);
			system("pause");
			system("cls");
			break;
		}
		default:
			cout << "��������ȷ�����֣�" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}