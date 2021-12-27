#include <iostream>
using namespace std;

#define MAXSIZE 50//˳������󳤶�
#define ENDFLAG 32767

/*- - - - - - - - - - ���� - - - - - - - - - - */
//˳�����
typedef int KeyType;
typedef int InfoType;
typedef struct
{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//������
}ElemType;
typedef struct
{
	ElemType* R;//����ռ����ַ
	int length;//��ǰ����
}SSTable;

//˳���ĳ�ʼ��
void InitList(SSTable& ST)
{
	ST.R = new ElemType[MAXSIZE + 1];//����һ���µ�˳���L ��Ϊ֮�����СΪMAXSIZE�Ŀռ�
	if (ST.R == NULL)
		exit(OVERFLOW);// �洢�ռ����ʧ���˳�
	ST.length = 0;
}

//˳���Ĵ���
void CreatSST(SSTable& ST)
{//���ζ���һ���ؼ���Ϊkey�Ľ�㣬���˽ڵ����˳���ST��
	InitList(ST);
	int i = 1; KeyType e;
	cout << "����������ؼ��֣�";
	cin >> e;
	while (e != ENDFLAG)//ENDFLAGΪ���������־��
	{
		ST.R[i].key = e;
		ST.R[i].otherinfo = 1; i++;//��������Ϊ1����������
		ST.length++;//˳�����+1
		cin >> e;
	}
}

//�۰����
int Search_Bin(SSTable ST, KeyType key)
{//�������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
	int low = 1, high = ST.length, mid;//���ʲ��������ֵ
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == ST.R[mid].key)//�ҵ�����Ԫ��
			return mid;
		else if (key < ST.R[mid].key)//������ǰһ�ӱ���в���
			high = mid - 1;
		else//�����ں�һ�ӱ���в���
			low = mid + 1;
	}//while
	return 0;//���в����ڴ���Ԫ��
}

//----�����������Ķ����������ʾ----
typedef struct BSTNode
{
	ElemType data;//ÿ���ڵ������������ؼ����������������
	struct BSTNode* lchild, * rchild;//���Һ���ָ��
}BSTNode, * BSTree;

//�����������Ĳ���
void InsertBST(BSTree& T, ElemType e)
{//������������T�в����ڹؼ��ֵ���e��key������Ԫ��ʱ��������Ԫ��
	if (!T)
	{//�ҵ�����λ�ã��ݹ����
		BSTNode* S = new BSTNode;//�����½��*S
		S->data = e;//�½��*S����������Ϊe
		S->lchild = S->rchild = NULL;//�½��*S��ΪҶ�ӽ��
		T = S;//���½��*S���ӵ����ҵ��Ĳ���λ��
	}
	else if (e.key < T->data.key)
		InsertBST(T->lchild, e);//��*S����������
	else if (e.key > T->data.key)
		InsertBST(T->rchild, e);//��*S����������
}

//�����������Ĵ���
void CreatBST(BSTree& T)
{//���ζ���һ���ؼ���Ϊkey�Ľ�㣬���˽ڵ�������������T��
	T = NULL;//������������T��ʼ��Ϊ����
	ElemType e;
	int i = 1;//���ڼ�¼Ԫ��λ��
	cout << "����������ؼ��֣�";
	cin >> e.key;
	while (e.key != ENDFLAG)//ENDFLAGΪ���������־��
	{
		e.otherinfo = i++;
		InsertBST(T, e);//���˽��������������T��
		cin >> e.key;
	}
}

//�����������ĵݹ����
BSTree SearchBST(BSTree T, KeyType key)
{//�ڸ�ָ��T��ָ�����������еݹ�ز�������ĳ�ؼ��ֵ���key������Ԫ��
 //�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
	if ((!T) || key == T->data.key)
		return T;//���ҽ���
	else if (key < T->data.key)
		return SearchBST(T->lchild, key);//���������м�������
	else
		return SearchBST(T->rchild, key);//���������м�������
}

/*- - - - - - - - - - ���� - - - - - - - - - - */
//������������������
typedef struct
{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//����������
}RedType;//��¼����
typedef struct
{
	RedType* r;//r[0]���û������ڱ���Ԫ
	int length;//˳�����
}SqList;//˳�������

//˳���ĳ�ʼ��
void InitList(SqList& L)
{
	L.r = new RedType[MAXSIZE + 1];//����һ���µ�˳���L ��Ϊ֮�����СΪMAXSIZE�Ŀռ�
	if (L.r == NULL)
		exit(OVERFLOW);// �洢�ռ����ʧ���˳�
	L.length = 0;
}

//˳���Ĵ���
void CreatList(SqList& L)
{//���ζ���һ���ؼ���Ϊkey�Ľ�㣬���˽ڵ����˳���ST��
	InitList(L);
	int i = 1; KeyType e;
	cout << "����������ؼ��֣�";
	cin >> e;
	while (e != ENDFLAG)//ENDFLAGΪ���������־��
	{
		L.r[i].key = e;
		L.r[i].otherinfo = 1; i++;//��������Ϊ1����������
		L.length++;//˳�����+1
		cin >> e;
	}
}

//��ӡ���Ա�
void ShowList(SqList L)
{//����L������ӡ
	if (L.length == 0)
		cout << "�գ�" << endl;//�ձ��ӡ���գ���
	else
	{
		for (int i = 1; i <= L.length; i++)
			cout << " " << L.r[i].key;
		cout << endl;//��ӡ��������
	}
}

//ϣ������
void ShellInsert(SqList& L, int dk)
{//��˳���L��һ��������dk��ϣ����������
	int i, j;
	for (i = dk + 1; i <= L.length; ++i)//�轫L.r[i]�������������ӱ�
		if (L.r[i].key < L.r[i - dk].key)
		{
			L.r[0] = L.r[i];//�ݴ���L.r[0]
			for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)
				L.r[j + dk] = L.r[j];//��¼���ƣ�ֱ���ҵ�����λ��
			L.r[j + dk] = L.r[0];//��r[0]��ԭr[i]�����뵽��ȷλ��
		}//if
}
void ShellSort(SqList& L, int dt[], int t)
{//����������dt[0..t-1]��˳�����t��ϣ������
	for (int k = 0; k < t; ++k)
		ShellInsert(L, dt[k]);//һ������Ϊdt[k]��ϣ����������
}

//ð������
void BubbleSort(SqList& L)
{//��˳���L��ð������
	int m = L.length - 1, flag = 1;//flag�������ĳһ�������Ƿ�������
	RedType t;//t������ʱ��¼
	while ((m > 0) && (flag == 1))
	{
		flag = 0;//flag��Ϊ0�������������û�з����������򲻻�ִ����һ������
		for (int j = 1; j <= m; j++)
			if (L.r[j].key > L.r[j + 1].key)
			{
				flag = 1;//flag��Ϊ1����ʾ�����������˽���
				t = L.r[j]; L.r[j] = L.r[j + 1]; L.r[j + 1] = t;//����ǰ��������¼
			}//if
		--m;
	}//while
}//BubbleSort

//��ѡ������
void SelectSort(SqList& L)
{//��˳���L����ѡ������
	RedType t;
	for (int i = 1; i < L.length; ++i)
	{//��L.r[i..L.length]��ѡ��ؼ�����С�ļ�¼
		int k = i;
		for (int j = i + 1; j <= L.length; ++j)
			if (L.r[j].key < L.r[k].key)
				k = j;//kָ����������йؼ�����С�ļ�¼
		if (k != i)
		{
			t = L.r[i]; L.r[i] = L.r[k]; L.r[k] = t;//����r[i]��r[k]
		}
	}//for
}

//������
void HeapAdjust(SqList& L, int s, int m)
{//����r[s+1..m]�Ѿ��Ƕѣ���r[s..m]����Ϊ��r[s]Ϊ���Ĵ����
	RedType rc = L.r[s];
	for (int j = 2 * s; j < m; j *= 2)//��key�ϴ�ĺ��ӽ������ɸѡ
	{
		if (j < m && L.r[j].key < L.r[j + 1].key)
			++j;//jΪkey�ϴ�ļ�¼���±�
		if (rc.key >= L.r[j].key)
			break;//rcӦ������λ��s��
		L.r[s] = L.r[j]; s = j;
	}//for
	L.r[s] = rc;//����
}
void CreatHeap(SqList& L)
{//����������L.r[1..n]���ɴ����
	int n = L.length;
	for (int i = n / 2; i > 0; --i)//��������HeapAdjust
		HeapAdjust(L, i, n);
}
void HeapSort(SqList& L)
{//��˳���L���ж�����
	CreatHeap(L);//����������L.r[1..L.length]���ɴ����
	RedType x;
	for (int i = L.length; i > 1; --i)
	{
		x = L.r[1];//���Ѷ���¼�͵�ǰδ������������L.r[1..i]�����һ����¼����
		L.r[1] = L.r[i];
		L.r[i] = x;
		HeapAdjust(L, 1, i - 1);//��L.r[1..i-1]���µ���Ϊ�����
	}//for
}

//�鲢����
void Merge(RedType R[], RedType T[], int low, int mid, int high)
{//�������R[low..mid]��R[mid+1..high]�鲢Ϊ�����T[low..high]
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high)//��R�м�¼��С����ز���T��
	{
		if (R[i].key < R[j].key)
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	}//while
	while (i <= mid)
		T[k++] = R[i++];//��ʣ���R[i..mid]���Ƶ�T��
	while (j <= high)
		T[k++] = R[j++];//��ʣ���R[j..high]���Ƶ�T��
}
void MSort(RedType R[], RedType T[], int low, int high)
{//R[low..high]�鲢��������T[low..high]��
	RedType* S = new RedType[MAXSIZE + 1];
	if (low == high)
		T[low] = R[low];
	else
	{
		int mid = (low + high) / 2;//����ǰ����һ��Ϊ����������ѵ�mid
		MSort(R, S, low, mid);//��������R[low..mid]�ݹ�鲢���򣬽������S[low..mid]
		MSort(R, S, mid + 1, high);//��������R[mid+1..high]�ݹ�鲢���򣬽������S[mid+1..high]
		Merge(S, T, low, mid, high);//��S[low..mid]��S[mid+1..high]�鲢��T[low..high]
	}//else
}
void MergeSort(SqList& L)
{//��˳���L���鲢����
	MSort(L.r, L.r, 1, L.length);
}

//�˵�
void ShowMenu()
{
	cout << "--------------------------------" << endl;
	cout << "----- 1��������������ң�-----" << endl;
	cout << "----- 2���۰����          -----" << endl;
	cout << "----- 3������������        -----" << endl;
	cout << "----- 4������˳�������-----" << endl;
	cout << "----- 5��ϣ������          -----" << endl;
	cout << "----- 6��ð������          -----" << endl;
	cout << "----- 7����ѡ������      -----" << endl;
	cout << "----- 8��������            -----" << endl;
	cout << "----- 9���鲢����          -----" << endl;
	cout << "----- 0���˳�              -----" << endl;
	cout << "--------------------------------" << endl;
}

int main()
{
	SSTable ST; BSTree T = NULL; SqList L;
	InitList(ST); InitList(L);//��ʼ��˳���
	KeyType key; int loc;//keyΪ����Ԫ�أ�locΪ��Ԫ��λ��
	int dt[] = { 5,3,1 }, t = 3;//ϣ��������������У�tΪϣ���������
	int wm = 0;
	int i, n;
	ShowMenu();//�˵�

	//ʵ�ֳ������
	while (true)
	{	
		cout << "������������룺";
		if (!(cin >> wm))
		{//��������ʱ�������룬��ֹ��ѭ��
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		//ѡ��
		switch (wm)
		{
		case 1:
			//�����1 3 5 8 9 12 13 17 20 25 28 34 48 56 78 32767
			cout << "˳���" << endl; CreatSST(ST);//����˳���
			cout << "������������" << endl; CreatBST(T);//��������������
			cout << "�����ɹ���" << endl;
			break;
		case 2:
			cout << "������Ҫ���ҵ�Ԫ�أ�"; cin >> key;
			loc = Search_Bin(ST, key);//�����۰���Һ���
			if (loc == 0)//��loc����0�������ʧ��
				cout << "δ�ҵ���Ԫ�أ�" << endl;
			else
				cout << "��Ԫ��λ�ڵ�" << loc << "λ" << endl;
			break;
		case 3:
			if (T == NULL)//�ж�������Ƿ����
			{
				cout << "�����δ������" << endl;
				break;
			}
			cout << "������Ҫ���ҵ�Ԫ�أ�"; cin >> key;
			if (SearchBST(T, key) == NULL)//��SearchBST()���ؿ����������ʧ��
				cout << "δ�ҵ���Ԫ�أ�" << endl;
			else
			{
				loc = SearchBST(T, key)->data.otherinfo;
				cout << "��Ԫ��λ�ڵ�" << loc << "λ" << endl;
			}
			break;
		case 4:
			//������42 20 17 13 28 14 23 15 32767
			CreatList(L);
			cout << "�����ɹ���" << endl;
			break;
		case 5:
			if (L.length == 0)
			{//�жϱ��Ƿ����
				cout << "˳���Ϊ�գ�" << endl;
				break;
			}
			else
			{//ϣ������
				ShellSort(L, dt, t);
				cout << "�����"; ShowList(L);
				break;
			}
		case 6:
			if (L.length == 0)
			{//�жϱ��Ƿ����
				cout << "˳���Ϊ�գ�" << endl;
				break;
			}
			else
			{//ð������
				BubbleSort(L);
				cout << "�����"; ShowList(L);
				break;
			}
		case 7:
			if (L.length == 0)
			{//�жϱ��Ƿ����
				cout << "˳���Ϊ�գ�" << endl;
				break;
			}
			else
			{//��ѡ������
				SelectSort(L);
				cout << "�����"; ShowList(L);
				break;
			}
		case 8:
			if (L.length == 0)
			{//�жϱ��Ƿ����
				cout << "˳���Ϊ�գ�" << endl;
				break;
			}
			else
			{//������
				HeapSort(L);
				cout << "�����"; ShowList(L);
				break;
			}
		case 9:
			if (L.length == 0)
			{//�жϱ��Ƿ����
				cout << "˳���Ϊ�գ�" << endl;
				break;
			}
			else
			{//�鲢����
				MergeSort(L);
				cout << "�����"; ShowList(L);
				break;
			}
		case 0:
		{//�˳�
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
		}//switch
	}//while
	system("pause");
	return 0;
}

