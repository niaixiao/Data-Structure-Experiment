#include<iostream>
#include<sstream>
using namespace std;
typedef char TElemType;
#define N 400
//- - - - -二叉树的二叉链表存储表示- - - - -
typedef struct BiTNode
{
	TElemType data;//结点数据域
	struct BiTNode* lchild, * rchild;//左右孩子指针
}BiTNode, * BiTree;
//- - - - -哈夫曼树的存储表示- - - - -
typedef struct
{
	int weight;//结点的权值
	int parent, lchild, rchild;//结点的双亲、左孩子、右孩子的下标
}HTNode, * HuffmanTree;
//- - - - -哈夫曼编码表的存储表示- - - - -
typedef char** HuffmanCode;//动态分配数组存储哈夫曼编码表

//先序遍历建立二叉表
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

//先序遍历二叉树
void PreOrderTraverse(BiTree& T)
{
	if (T)//若二叉树非空
	{
		cout << T->data;//访问根结点
		PreOrderTraverse(T->lchild);//先序遍历左子树
		PreOrderTraverse(T->rchild);//先序遍历右子树
	}
}

//中序遍历二叉树
void InOrderTraverse(BiTree& T)
{
	if (T)//若二叉树非空
	{
		InOrderTraverse(T->lchild);//中序遍历左子树
		cout << T->data;//访问根结点
		InOrderTraverse(T->rchild);//中序遍历右子树
	}
}

//后序遍历二叉树
void PostOrderTraverse(BiTree& T)
{
	if (T)//若二叉树非空
	{
		PostOrderTraverse(T->lchild);//后序遍历左子树
		PostOrderTraverse(T->rchild);//后序遍历右子树
		cout << T->data;//访问根结点
	}
}

//计算二叉树的深度
int Depth(BiTree& T)
{
	int m, n;
	if (T == NULL)
		return 0;//空树的深度为0
	else
	{
		m = Depth(T->lchild);//递归计算左子树的深度，记为m
		n = Depth(T->rchild);//递归计算右子树的深度，记为n
		if (m > n)
			return(m + 1);//二叉树的深度为m与n的较大者+1
		else
			return(n + 1);
	}
}

//计算二叉树的叶子结点个数
int Node0Count(BiTree& T)
{
	if (T == NULL)
		return 0;//空树结点个数为0，递归结束
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;//叶子结点的左子树和右子树均为空
	else
		return Node0Count(T->lchild) + Node0Count(T->rchild);//否则结点数为左右子树的叶子结点数之和
}

//清空二叉树
void ClearBiTree(BiTree& T)
{
	T = NULL;
}

//Huffman编码
//Huffman中Select函数
void Select(HuffmanTree HT, int i, int& s1, int& s2)
{//选出HT中两个双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
	int min1 = INT_MAX, min2 = INT_MAX;//先令min1和min2为最大值
	for (int k = 1; k <= i; k++)
	{//第一遍遍历HT，选出符合条件的min1
		if (HT[k].parent == 0 && min1 > HT[k].weight)
		{
			min1 = HT[k].weight;
			s1 = k;
		}
	}
	for (int k = 1; k <= i; k++)
	{//第二编遍历HT，选出符合条件且不为min1的min2
		if (k != s1 && HT[k].parent == 0 && min2 > HT[k].weight)
		{
			min2 = HT[k].weight;
			s2 = k;
		}
	}
}
//构造哈夫曼树
void CreatHuffmanTree(HuffmanTree& HT, int n, int num[])
{//构造哈夫曼树HT
	int m, s1, s2;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = new HTNode[m + 1];//0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根节点
	for (int i = 1; i <= m; ++i)//将1~m号单元中的双亲、左孩子、右孩子的下标都初始化为0
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = 1; i <= n; ++i)//输入前n个单元中叶子结点的权值
		HT[i].weight = num[i-1];
		//cin >> HT[i].weight;
/*- - - - - -初始化工作结束，开始创建哈夫曼树- - - - - -*/
	for (int i = n + 1; i <= m; ++i)
	{//通过n-1次的选择、删除、合并来创建哈夫曼树
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;//得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为1
		HT[i].lchild = s1;
		HT[i].rchild = s2;//s1和s2分别作为i的左右孩子
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i的权值为左右孩子权值之和
	}
}
//根据哈夫曼树求哈夫曼编码
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{//从叶子结点到根逆向求每个字符的哈夫曼编码，储存在编码表HC中
	int start, c, f;
	HC = new char* [n + 1];//分配存储n个字符编码的编码表空间
	char* cd = new char[n];//分配临时存放每个字符编码的动态数组空间
	cd[n - 1] = '\0';//编码结束符
	for (int i = 1; i <= n; ++i)//逐个字符求哈夫曼编码
	{
		start = n - 1;//start开始时指向最后，即编码结束符位置
		c = i;
		f = HT[i].parent;//f指向结点c的双亲结点
		while (f != 0)//从叶子节点开始向上回溯，直到根节点
		{
			--start;
			if (HT[f].lchild == c)//结点c是f的左孩子，则生成代码0
				cd[start] = '0';
			else//结点c是f的右孩子，则生成代码1
				cd[start] = '1';
			c = f;
			f = HT[f].parent;//继续向上回溯
		}//求出第i个字符的编码
		HC[i] = new char[n - start];//为第i个字符编码分配空间
		strcpy_s(HC[i], strlen(&cd[start]) + 1, &cd[start]);//将求得的编码从临时空间cd复制到HC的当前行中
	}
	delete[] cd;//释放临时空间
}

//计算WPL
int HuffmanWPL(HuffmanTree HT, int n)
{//利用“叶子节点加权路径长度乘积的和=非叶子节点权值的和”求WPL
	if (n < 1)//哈夫曼树不存在时WPL=0
		return 0;
	int m = 2 * n - 1, wpl = 0;
	for (int i = 1; i <= m; ++i)
	{//求非叶子节点权值的和，左右孩子都不存在的结点为非叶子节点
		if (HT[i].lchild != 0 && HT[i].rchild != 0)
			wpl += HT[i].weight;
	}
	return wpl;
}

void ShowMenu()
{
	cout << "======================" << endl;
	cout << "----1.创建二叉树  ----" << endl;
	cout << "----2.先序遍历    ----" << endl;
	cout << "----3.中序遍历    ----" << endl;
	cout << "----4.后序遍历    ----" << endl;
	cout << "----5.二叉树深度  ----" << endl;
	cout << "----6.叶子结点数  ----" << endl;
	cout << "----7.清空二叉树  ----" << endl;
	cout << "----8.Huffman编码 ----" << endl;
	cout << "----0.退出        ----" << endl;
	cout << "======================" << endl;
}

int main()
{
	BiTree T = NULL;
	
	int wm;
	ShowMenu();
	while (true)
	{
		cout << "请输入操作代码：";
		if (!(cin >> wm))//错误输入时重新输入，防止死循环
		{
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		switch (wm)
		{
		case 1:
			cout << "请输入表达式：";//	+-a##*b##/c##+d##*e##f##*g##+h##i##
			CreateBiTree(T);
			cout << "创建成功！" << endl;
			break;
		case 2:
			if (T == NULL)
				cout << "空！" << endl;
			else
			{
				cout << "先序序列：";
				PreOrderTraverse(T);
				cout << endl;
			}
			break;
		case 3:
			if (T == NULL)
				cout << "空！" << endl;
			else
			{
				cout << "中序序列：";
				InOrderTraverse(T);
				cout << endl;
			}
			break;
		case 4:
			if (T == NULL)
				cout << "空！" << endl;
			else
			{
				cout << "后序序列：";
				PostOrderTraverse(T);
				cout << endl;
			}
			break;
		case 5:
			cout << "该二叉树的深度为：" << Depth(T) << endl;
			break;
		case 6:
			cout << "该二叉树的叶子结点数为：" << Node0Count(T) << endl;
			break;
		case 7:
			system("cls");
			ShowMenu();
			ClearBiTree(T);
			cout << "二叉树已清空！" << endl;
			break;
		case 8:
		{
			string ch;//用于存放字符串
			cout << "请输入字符串：" << endl;
			cin >> ch;//ch= AADBAACACCDACACAADBBCD
			char a;//用于判断字符串中字符类型
			int num[4] = { 0 };//用于存放字符串中字符出现次数
			for (istringstream sin(ch); sin >> a;)//遍历字符串
			{//统计ABCD出现的次数
				if (a == 'A')
					num[0]++;
				if (a == 'B')
					num[1]++;
				if (a == 'C')
					num[2]++;
				if (a == 'D')
					num[3]++;
			}
			cout << "出现次数：\n‘A’:" << num[0] << " ‘B’:" << num[1]
				<< " ‘C’:" << num[2] << " ‘D’:" << num[3] << endl;
			//以ABCD出现的次数作为权值创建哈夫曼树
			HuffmanTree HT;
			CreatHuffmanTree(HT, 4, num);//n=4
			//根据哈夫曼树构造哈夫曼编码
			HuffmanCode HC;
			CreatHuffmanCode(HT, HC, 4);//n=4
			cout << "哈夫曼编码为：\n\tA:" << HC[1] << "\n\tB:"
				<< HC[2] << "\n\tC:" << HC[3] << "\n\tD:" << HC[4] << endl;
			//根据哈夫曼树求WPL
			cout << "带权路径长度(WPL)为：" << HuffmanWPL(HT, 4) << endl;
			break;
		}	
		case 0:
		{
			int end = 0;
			cout << "确定要退出吗？\n（按‘1’确认退出，‘其他键’取消）" << endl;
			cin >> end;
			if (end == 1)
			{
				cout << "欢迎下次使用！" << endl;
				return 0;
			}
			break;
		}
		default:
			cout << "请输入正确的操作代码！" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}