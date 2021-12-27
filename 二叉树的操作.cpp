#include<iostream>
#include<sstream>
using namespace std;
typedef char TElemType;
#define N 400
//- - - - -�������Ķ�������洢��ʾ- - - - -
typedef struct BiTNode
{
	TElemType data;//���������
	struct BiTNode* lchild, * rchild;//���Һ���ָ��
}BiTNode, * BiTree;
//- - - - -���������Ĵ洢��ʾ- - - - -
typedef struct
{
	int weight;//����Ȩֵ
	int parent, lchild, rchild;//����˫�ס����ӡ��Һ��ӵ��±�
}HTNode, * HuffmanTree;
//- - - - -�����������Ĵ洢��ʾ- - - - -
typedef char** HuffmanCode;//��̬��������洢�����������

//����������������
void CreateBiTree(BiTree& T)
{
	TElemType ch;
	cin >> ch;
	if (ch == '#')
		T = NULL;
	else
	{
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

//�������������
void PreOrderTraverse(BiTree& T)
{
	if (T)//���������ǿ�
	{
		cout << T->data;//���ʸ����
		PreOrderTraverse(T->lchild);//�������������
		PreOrderTraverse(T->rchild);//�������������
	}
}

//�������������
void InOrderTraverse(BiTree& T)
{
	if (T)//���������ǿ�
	{
		InOrderTraverse(T->lchild);//�������������
		cout << T->data;//���ʸ����
		InOrderTraverse(T->rchild);//�������������
	}
}

//�������������
void PostOrderTraverse(BiTree& T)
{
	if (T)//���������ǿ�
	{
		PostOrderTraverse(T->lchild);//�������������
		PostOrderTraverse(T->rchild);//�������������
		cout << T->data;//���ʸ����
	}
}

//��������������
int Depth(BiTree& T)
{
	int m, n;
	if (T == NULL)
		return 0;//���������Ϊ0
	else
	{
		m = Depth(T->lchild);//�ݹ��������������ȣ���Ϊm
		n = Depth(T->rchild);//�ݹ��������������ȣ���Ϊn
		if (m > n)
			return(m + 1);//�����������Ϊm��n�Ľϴ���+1
		else
			return(n + 1);
	}
}

//�����������Ҷ�ӽ�����
int Node0Count(BiTree& T)
{
	if (T == NULL)
		return 0;//����������Ϊ0���ݹ����
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;//Ҷ�ӽ�������������������Ϊ��
	else
		return Node0Count(T->lchild) + Node0Count(T->rchild);//��������Ϊ����������Ҷ�ӽ����֮��
}

//��ն�����
void ClearBiTree(BiTree& T)
{
	T = NULL;
}

//Huffman����
//Huffman��Select����
void Select(HuffmanTree HT, int i, int& s1, int& s2)
{//ѡ��HT������˫����Ϊ0��Ȩֵ��С�Ľ�㣬������������HT�е����s1��s2
	int min1 = INT_MAX, min2 = INT_MAX;//����min1��min2Ϊ���ֵ
	for (int k = 1; k <= i; k++)
	{//��һ�����HT��ѡ������������min1
		if (HT[k].parent == 0 && min1 > HT[k].weight)
		{
			min1 = HT[k].weight;
			s1 = k;
		}
	}
	for (int k = 1; k <= i; k++)
	{//�ڶ������HT��ѡ�����������Ҳ�Ϊmin1��min2
		if (k != s1 && HT[k].parent == 0 && min2 > HT[k].weight)
		{
			min2 = HT[k].weight;
			s2 = k;
		}
	}
}
//�����������
void CreatHuffmanTree(HuffmanTree& HT, int n, int num[])
{//�����������HT
	int m, s1, s2;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = new HTNode[m + 1];//0�ŵ�Ԫδ�ã�������Ҫ��̬����m+1����Ԫ��HT[m]��ʾ���ڵ�
	for (int i = 1; i <= m; ++i)//��1~m�ŵ�Ԫ�е�˫�ס����ӡ��Һ��ӵ��±궼��ʼ��Ϊ0
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = 1; i <= n; ++i)//����ǰn����Ԫ��Ҷ�ӽ���Ȩֵ
		HT[i].weight = num[i-1];
		//cin >> HT[i].weight;
/*- - - - - -��ʼ��������������ʼ������������- - - - - -*/
	for (int i = n + 1; i <= m; ++i)
	{//ͨ��n-1�ε�ѡ��ɾ�����ϲ���������������
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;//�õ��½��i����ɭ����ɾ��s1��s2����s1��s2��˫������0��Ϊ1
		HT[i].lchild = s1;
		HT[i].rchild = s2;//s1��s2�ֱ���Ϊi�����Һ���
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i��ȨֵΪ���Һ���Ȩֵ֮��
	}
}
//���ݹ������������������
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{//��Ҷ�ӽ�㵽��������ÿ���ַ��Ĺ��������룬�����ڱ����HC��
	int start, c, f;
	HC = new char* [n + 1];//����洢n���ַ�����ı����ռ�
	char* cd = new char[n];//������ʱ���ÿ���ַ�����Ķ�̬����ռ�
	cd[n - 1] = '\0';//���������
	for (int i = 1; i <= n; ++i)//����ַ������������
	{
		start = n - 1;//start��ʼʱָ����󣬼����������λ��
		c = i;
		f = HT[i].parent;//fָ����c��˫�׽��
		while (f != 0)//��Ҷ�ӽڵ㿪ʼ���ϻ��ݣ�ֱ�����ڵ�
		{
			--start;
			if (HT[f].lchild == c)//���c��f�����ӣ������ɴ���0
				cd[start] = '0';
			else//���c��f���Һ��ӣ������ɴ���1
				cd[start] = '1';
			c = f;
			f = HT[f].parent;//�������ϻ���
		}//�����i���ַ��ı���
		HC[i] = new char[n - start];//Ϊ��i���ַ��������ռ�
		strcpy_s(HC[i], strlen(&cd[start]) + 1, &cd[start]);//����õı������ʱ�ռ�cd���Ƶ�HC�ĵ�ǰ����
	}
	delete[] cd;//�ͷ���ʱ�ռ�
}

//����WPL
int HuffmanWPL(HuffmanTree HT, int n)
{//���á�Ҷ�ӽڵ��Ȩ·�����ȳ˻��ĺ�=��Ҷ�ӽڵ�Ȩֵ�ĺ͡���WPL
	if (n < 1)//��������������ʱWPL=0
		return 0;
	int m = 2 * n - 1, wpl = 0;
	for (int i = 1; i <= m; ++i)
	{//���Ҷ�ӽڵ�Ȩֵ�ĺͣ����Һ��Ӷ������ڵĽ��Ϊ��Ҷ�ӽڵ�
		if (HT[i].lchild != 0 && HT[i].rchild != 0)
			wpl += HT[i].weight;
	}
	return wpl;
}

void ShowMenu()
{
	cout << "======================" << endl;
	cout << "----1.����������  ----" << endl;
	cout << "----2.�������    ----" << endl;
	cout << "----3.�������    ----" << endl;
	cout << "----4.�������    ----" << endl;
	cout << "----5.���������  ----" << endl;
	cout << "----6.Ҷ�ӽ����  ----" << endl;
	cout << "----7.��ն�����  ----" << endl;
	cout << "----8.Huffman���� ----" << endl;
	cout << "----0.�˳�        ----" << endl;
	cout << "======================" << endl;
}

int main()
{
	BiTree T = NULL;
	
	int wm;
	ShowMenu();
	while (true)
	{
		cout << "������������룺";
		if (!(cin >> wm))//��������ʱ�������룬��ֹ��ѭ��
		{
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		switch (wm)
		{
		case 1:
			cout << "��������ʽ��";//	+-a##*b##/c##+d##*e##f##*g##+h##i##
			CreateBiTree(T);
			cout << "�����ɹ���" << endl;
			break;
		case 2:
			if (T == NULL)
				cout << "�գ�" << endl;
			else
			{
				cout << "�������У�";
				PreOrderTraverse(T);
				cout << endl;
			}
			break;
		case 3:
			if (T == NULL)
				cout << "�գ�" << endl;
			else
			{
				cout << "�������У�";
				InOrderTraverse(T);
				cout << endl;
			}
			break;
		case 4:
			if (T == NULL)
				cout << "�գ�" << endl;
			else
			{
				cout << "�������У�";
				PostOrderTraverse(T);
				cout << endl;
			}
			break;
		case 5:
			cout << "�ö����������Ϊ��" << Depth(T) << endl;
			break;
		case 6:
			cout << "�ö�������Ҷ�ӽ����Ϊ��" << Node0Count(T) << endl;
			break;
		case 7:
			system("cls");
			ShowMenu();
			ClearBiTree(T);
			cout << "����������գ�" << endl;
			break;
		case 8:
		{
			string ch;//���ڴ���ַ���
			cout << "�������ַ�����" << endl;
			cin >> ch;//ch= AADBAACACCDACACAADBBCD
			char a;//�����ж��ַ������ַ�����
			int num[4] = { 0 };//���ڴ���ַ������ַ����ִ���
			for (istringstream sin(ch); sin >> a;)//�����ַ���
			{//ͳ��ABCD���ֵĴ���
				if (a == 'A')
					num[0]++;
				if (a == 'B')
					num[1]++;
				if (a == 'C')
					num[2]++;
				if (a == 'D')
					num[3]++;
			}
			cout << "���ִ�����\n��A��:" << num[0] << " ��B��:" << num[1]
				<< " ��C��:" << num[2] << " ��D��:" << num[3] << endl;
			//��ABCD���ֵĴ�����ΪȨֵ������������
			HuffmanTree HT;
			CreatHuffmanTree(HT, 4, num);//n=4
			//���ݹ��������������������
			HuffmanCode HC;
			CreatHuffmanCode(HT, HC, 4);//n=4
			cout << "����������Ϊ��\n\tA:" << HC[1] << "\n\tB:"
				<< HC[2] << "\n\tC:" << HC[3] << "\n\tD:" << HC[4] << endl;
			//���ݹ���������WPL
			cout << "��Ȩ·������(WPL)Ϊ��" << HuffmanWPL(HT, 4) << endl;
			break;
		}	
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