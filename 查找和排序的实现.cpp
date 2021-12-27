#include <iostream>
using namespace std;

#define MAXSIZE 50//顺序表的最大长度
#define ENDFLAG 32767

/*- - - - - - - - - - 查找 - - - - - - - - - - */
//顺序表定义
typedef int KeyType;
typedef int InfoType;
typedef struct
{
	KeyType key;//关键字域
	InfoType otherinfo;//其他域
}ElemType;
typedef struct
{
	ElemType* R;//储存空间基地址
	int length;//当前长度
}SSTable;

//顺序表的初始化
void InitList(SSTable& ST)
{
	ST.R = new ElemType[MAXSIZE + 1];//构造一个新的顺序表L 并为之分配大小为MAXSIZE的空间
	if (ST.R == NULL)
		exit(OVERFLOW);// 存储空间分配失败退出
	ST.length = 0;
}

//顺序表的创建
void CreatSST(SSTable& ST)
{//依次读入一个关键字为key的结点，将此节点插入顺序表ST中
	InitList(ST);
	int i = 1; KeyType e;
	cout << "请依次输入关键字：";
	cin >> e;
	while (e != ENDFLAG)//ENDFLAG为输入结束标志语
	{
		ST.R[i].key = e;
		ST.R[i].otherinfo = 1; i++;//其他域设为1，继续输入
		ST.length++;//顺序表长度+1
		cin >> e;
	}
}

//折半查找
int Search_Bin(SSTable ST, KeyType key)
{//在有序表ST中折半查找其关键字等于key的数据元素。若找到，则函数值为该元素在表中的位置，否则为0
	int low = 1, high = ST.length, mid;//访问查找区间初值
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == ST.R[mid].key)//找到待查元素
			return mid;
		else if (key < ST.R[mid].key)//继续在前一子表进行查找
			high = mid - 1;
		else//继续在后一子表进行查找
			low = mid + 1;
	}//while
	return 0;//表中不存在待查元素
}

//----二叉排序树的二叉链表储存表示----
typedef struct BSTNode
{
	ElemType data;//每个节点的数据域包括关键字项和其他数据项
	struct BSTNode* lchild, * rchild;//左右孩子指针
}BSTNode, * BSTree;

//二叉排序树的插入
void InsertBST(BSTree& T, ElemType e)
{//当二叉排序树T中不存在关键字等于e，key的数据元素时，则插入该元素
	if (!T)
	{//找到插入位置，递归结束
		BSTNode* S = new BSTNode;//生成新结点*S
		S->data = e;//新结点*S的数据域置为e
		S->lchild = S->rchild = NULL;//新结点*S作为叶子结点
		T = S;//把新结点*S链接到已找到的插入位置
	}
	else if (e.key < T->data.key)
		InsertBST(T->lchild, e);//将*S插入左子树
	else if (e.key > T->data.key)
		InsertBST(T->rchild, e);//将*S插入右子树
}

//二叉排序树的创建
void CreatBST(BSTree& T)
{//依次读入一个关键字为key的结点，将此节点插入二叉排序树T中
	T = NULL;//将二叉排序树T初始化为空树
	ElemType e;
	int i = 1;//用于记录元素位置
	cout << "请依次输入关键字：";
	cin >> e.key;
	while (e.key != ENDFLAG)//ENDFLAG为输入结束标志语
	{
		e.otherinfo = i++;
		InsertBST(T, e);//将此结点插入二叉排序树T中
		cin >> e.key;
	}
}

//二叉排序树的递归查找
BSTree SearchBST(BSTree T, KeyType key)
{//在跟指针T所指二叉排序树中递归地查找其他某关键字等于key的数据元素
 //若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
	if ((!T) || key == T->data.key)
		return T;//查找结束
	else if (key < T->data.key)
		return SearchBST(T->lchild, key);//在左子树中继续查找
	else
		return SearchBST(T->rchild, key);//在右子树中继续查找
}

/*- - - - - - - - - - 排序 - - - - - - - - - - */
//定义待排序的数据类型
typedef struct
{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项
}RedType;//记录类型
typedef struct
{
	RedType* r;//r[0]闲置或用作哨兵单元
	int length;//顺序表长度
}SqList;//顺序表类型

//顺序表的初始化
void InitList(SqList& L)
{
	L.r = new RedType[MAXSIZE + 1];//构造一个新的顺序表L 并为之分配大小为MAXSIZE的空间
	if (L.r == NULL)
		exit(OVERFLOW);// 存储空间分配失败退出
	L.length = 0;
}

//顺序表的创建
void CreatList(SqList& L)
{//依次读入一个关键字为key的结点，将此节点插入顺序表ST中
	InitList(L);
	int i = 1; KeyType e;
	cout << "请依次输入关键字：";
	cin >> e;
	while (e != ENDFLAG)//ENDFLAG为输入结束标志语
	{
		L.r[i].key = e;
		L.r[i].otherinfo = 1; i++;//其他域设为1，继续输入
		L.length++;//顺序表长度+1
		cin >> e;
	}
}

//打印线性表
void ShowList(SqList L)
{//遍历L，并打印
	if (L.length == 0)
		cout << "空！" << endl;//空表打印‘空！’
	else
	{
		for (int i = 1; i <= L.length; i++)
			cout << " " << L.r[i].key;
		cout << endl;//打印结束换行
	}
}

//希尔排序
void ShellInsert(SqList& L, int dk)
{//对顺序表L做一趟增量是dk的希尔插入排序
	int i, j;
	for (i = dk + 1; i <= L.length; ++i)//需将L.r[i]插入有序增量子表
		if (L.r[i].key < L.r[i - dk].key)
		{
			L.r[0] = L.r[i];//暂存在L.r[0]
			for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)
				L.r[j + dk] = L.r[j];//记录后移，直到找到插入位置
			L.r[j + dk] = L.r[0];//将r[0]即原r[i]，插入到正确位置
		}//if
}
void ShellSort(SqList& L, int dt[], int t)
{//按增量序列dt[0..t-1]对顺序表作t趟希尔排序
	for (int k = 0; k < t; ++k)
		ShellInsert(L, dt[k]);//一趟增量为dt[k]的希尔插入排序
}

//冒泡排序
void BubbleSort(SqList& L)
{//对顺序表L做冒泡排序
	int m = L.length - 1, flag = 1;//flag用来标记某一趟排序是否发生交换
	RedType t;//t用于临时记录
	while ((m > 0) && (flag == 1))
	{
		flag = 0;//flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
		for (int j = 1; j <= m; j++)
			if (L.r[j].key > L.r[j + 1].key)
			{
				flag = 1;//flag置为1，表示本趟排序发生了交换
				t = L.r[j]; L.r[j] = L.r[j + 1]; L.r[j + 1] = t;//交换前后两个记录
			}//if
		--m;
	}//while
}//BubbleSort

//简单选择排序
void SelectSort(SqList& L)
{//对顺序表L做简单选择排序
	RedType t;
	for (int i = 1; i < L.length; ++i)
	{//在L.r[i..L.length]中选择关键字最小的记录
		int k = i;
		for (int j = i + 1; j <= L.length; ++j)
			if (L.r[j].key < L.r[k].key)
				k = j;//k指向此趟排序中关键字最小的记录
		if (k != i)
		{
			t = L.r[i]; L.r[i] = L.r[k]; L.r[k] = t;//交换r[i]与r[k]
		}
	}//for
}

//堆排序
void HeapAdjust(SqList& L, int s, int m)
{//假设r[s+1..m]已经是堆，将r[s..m]调整为以r[s]为根的大根堆
	RedType rc = L.r[s];
	for (int j = 2 * s; j < m; j *= 2)//沿key较大的孩子结点向下筛选
	{
		if (j < m && L.r[j].key < L.r[j + 1].key)
			++j;//j为key较大的记录的下标
		if (rc.key >= L.r[j].key)
			break;//rc应插入在位置s上
		L.r[s] = L.r[j]; s = j;
	}//for
	L.r[s] = rc;//插入
}
void CreatHeap(SqList& L)
{//把无序序列L.r[1..n]建成大根堆
	int n = L.length;
	for (int i = n / 2; i > 0; --i)//反复调用HeapAdjust
		HeapAdjust(L, i, n);
}
void HeapSort(SqList& L)
{//对顺序表L进行堆排序
	CreatHeap(L);//把无序序列L.r[1..L.length]建成大根堆
	RedType x;
	for (int i = L.length; i > 1; --i)
	{
		x = L.r[1];//将堆顶记录和当前未经排序子序列L.r[1..i]中最后一个记录互换
		L.r[1] = L.r[i];
		L.r[i] = x;
		HeapAdjust(L, 1, i - 1);//将L.r[1..i-1]重新调整为大根堆
	}//for
}

//归并排序
void Merge(RedType R[], RedType T[], int low, int mid, int high)
{//将有序表R[low..mid]和R[mid+1..high]归并为有序表T[low..high]
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high)//将R中记录由小到大地并入T中
	{
		if (R[i].key < R[j].key)
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	}//while
	while (i <= mid)
		T[k++] = R[i++];//将剩余的R[i..mid]复制到T中
	while (j <= high)
		T[k++] = R[j++];//将剩余的R[j..high]复制到T中
}
void MSort(RedType R[], RedType T[], int low, int high)
{//R[low..high]归并排序后放入T[low..high]中
	RedType* S = new RedType[MAXSIZE + 1];
	if (low == high)
		T[low] = R[low];
	else
	{
		int mid = (low + high) / 2;//将当前序列一分为二，求出分裂点mid
		MSort(R, S, low, mid);//对子序列R[low..mid]递归归并排序，结果放入S[low..mid]
		MSort(R, S, mid + 1, high);//对子序列R[mid+1..high]递归归并排序，结果放入S[mid+1..high]
		Merge(S, T, low, mid, high);//将S[low..mid]和S[mid+1..high]归并到T[low..high]
	}//else
}
void MergeSort(SqList& L)
{//对顺序表L做归并排序
	MSort(L.r, L.r, 1, L.length);
}

//菜单
void ShowMenu()
{
	cout << "--------------------------------" << endl;
	cout << "----- 1、创建有序表（查找）-----" << endl;
	cout << "----- 2、折半查找          -----" << endl;
	cout << "----- 3、二叉排序树        -----" << endl;
	cout << "----- 4、创建顺序表（排序）-----" << endl;
	cout << "----- 5、希尔排序          -----" << endl;
	cout << "----- 6、冒泡排序          -----" << endl;
	cout << "----- 7、简单选择排序      -----" << endl;
	cout << "----- 8、堆排序            -----" << endl;
	cout << "----- 9、归并排序          -----" << endl;
	cout << "----- 0、退出              -----" << endl;
	cout << "--------------------------------" << endl;
}

int main()
{
	SSTable ST; BSTree T = NULL; SqList L;
	InitList(ST); InitList(L);//初始化顺序表
	KeyType key; int loc;//key为查找元素，loc为该元素位置
	int dt[] = { 5,3,1 }, t = 3;//希尔排序的增量序列，t为希尔排序次数
	int wm = 0;
	int i, n;
	ShowMenu();//菜单

	//实现程序界面
	while (true)
	{	
		cout << "请输入操作代码：";
		if (!(cin >> wm))
		{//错误输入时重新输入，防止死循环
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		//选择
		switch (wm)
		{
		case 1:
			//输入表：1 3 5 8 9 12 13 17 20 25 28 34 48 56 78 32767
			cout << "顺序表：" << endl; CreatSST(ST);//创建顺序表
			cout << "二叉排序树：" << endl; CreatBST(T);//创建二叉排序树
			cout << "创建成功！" << endl;
			break;
		case 2:
			cout << "请输入要查找的元素："; cin >> key;
			loc = Search_Bin(ST, key);//调用折半查找函数
			if (loc == 0)//若loc等于0，则查找失败
				cout << "未找到该元素！" << endl;
			else
				cout << "该元素位于第" << loc << "位" << endl;
			break;
		case 3:
			if (T == NULL)//判断有序表是否存在
			{
				cout << "有序表未创建！" << endl;
				break;
			}
			cout << "请输入要查找的元素："; cin >> key;
			if (SearchBST(T, key) == NULL)//若SearchBST()返回空树，则查找失败
				cout << "未找到该元素！" << endl;
			else
			{
				loc = SearchBST(T, key)->data.otherinfo;
				cout << "该元素位于第" << loc << "位" << endl;
			}
			break;
		case 4:
			//创建表：42 20 17 13 28 14 23 15 32767
			CreatList(L);
			cout << "创建成功！" << endl;
			break;
		case 5:
			if (L.length == 0)
			{//判断表是否存在
				cout << "顺序表为空！" << endl;
				break;
			}
			else
			{//希尔排序
				ShellSort(L, dt, t);
				cout << "排序后："; ShowList(L);
				break;
			}
		case 6:
			if (L.length == 0)
			{//判断表是否存在
				cout << "顺序表为空！" << endl;
				break;
			}
			else
			{//冒泡排序
				BubbleSort(L);
				cout << "排序后："; ShowList(L);
				break;
			}
		case 7:
			if (L.length == 0)
			{//判断表是否存在
				cout << "顺序表为空！" << endl;
				break;
			}
			else
			{//简单选择排序
				SelectSort(L);
				cout << "排序后："; ShowList(L);
				break;
			}
		case 8:
			if (L.length == 0)
			{//判断表是否存在
				cout << "顺序表为空！" << endl;
				break;
			}
			else
			{//堆排序
				HeapSort(L);
				cout << "排序后："; ShowList(L);
				break;
			}
		case 9:
			if (L.length == 0)
			{//判断表是否存在
				cout << "顺序表为空！" << endl;
				break;
			}
			else
			{//归并排序
				MergeSort(L);
				cout << "排序后："; ShowList(L);
				break;
			}
		case 0:
		{//退出
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
		}//switch
	}//while
	system("pause");
	return 0;
}

