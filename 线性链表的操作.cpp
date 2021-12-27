/*
Wang Meng @henu
*/
#include <iostream>
#define ERROR
using namespace std;
typedef int ElemType;

//定义线性链表
typedef struct LNode
{
	ElemType data;			//结点的数据域
	struct LNode* next;		//结点的指针域
}LNode, * LinkList;

//线性链表的初始化
void InitList(LinkList& L)
{
	L = new LNode;			//生成新结点作为头结点，用头指针L指向头结点
	L->next = NULL;			//头结点的指针域置空
}

//头插法建表
void CreatList_H(LinkList& L, int n)
{
	LNode* p;				//开辟新结点
	cout << "请输入" << n << "个数据：";
	for (int i = 1; i <= n; i++)
	{
		p = new LNode;
		cin >> p->data;
		//将新结点插到头指针后面
		p->next = L->next; L->next = p;
	}
}

//尾插法建表
void CreatList_R(LinkList& L, int n)
{
	LNode* p;				//开辟新结点
	LNode* r;				//指向表尾结点
	r = L;
	cout << "请输入" << n << "个数据：";
	for (int i = 1; i <= n; i++)
	{
		p = new LNode;
		cin >> p->data;
		//将新结点插到表尾
		r->next = p; r = p;
	}
	r->next = NULL;
}
//显示链表
void ShowList(LinkList L)
{
	LNode* p;				//用于遍历表
	p = L->next;			//初始化，p指向首元结点
	if (p == NULL)
		cout << "空！";
	while (p != NULL)
	{//依次打印链表元素
		cout << " " << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//单链表的按值查找
LNode* LocateElem(LinkList L, ElemType e)
{//在带头结点的单链表L中查找值为e的元素
	LNode* p;				//用于遍历表
	p = L->next;			//初始化，p指向首元结点
	while (p && p->data != e)
		p = p->next;//遍历表，直到找到与e相等的元素
	return p;
}

//单链表的插入
void ListInsert(LinkList& L, int i, ElemType e)
{//在带头结点的单链表L中第i个位置插入值为e的新结点
	LNode* p, * s;
	int j = 0;
	p = L;
	while (p && (j < i - 1))
	{//查找第i-1个结点，p指向该结点
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
	{//判断插入位置是否合理
		cout << "插入位置不合理!" << endl;
		return ERROR;
	}
	s = new LNode;
	s->data = e;
	//插入结点s
	s->next = p->next; p->next = s;
	cout << "插入成功！" << endl;
}

//单链表的删除
void ListDelete(LinkList& L, int i)
{//在带头结点的链表L中，删除第i个元素
	LNode* p, * q;
	int j = 0;
	p = L;
	while ((p->next) && (j < i - 1))
	{//查找第i-1个结点，p指向该结点
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
	{//i>n或i<1时，删除位置不合理
		cout << "删除位置不合理!" << endl;
		return ERROR;
	}
	q = p->next;			//临时保存被删结点的地址以备释放
	p->next = q->next;		//改变删除结点前驱结点的指针域
	delete q;				//删除结点的空间
	cout << "删除成功！" << endl;
}

//单链表冒泡排序（非降序）
LinkList Order(LinkList& L)
{
	LNode* p, * q;//创建新结点用于L中的元素比较大小
	//进行简单选择排序
	for (p = L->next; p != NULL; p = p->next)
	{//p向后移动，序列长度减小
		for (q = p->next; q != NULL; q = q->next)
		{//选出当前子序列最小的元素，赋值给p->data
			if (p->data > q->data)
			{
				ElemType i = p->data;
				p->data = q->data;
				q->data = i;
			}
		}
	}
	return L;//返回排序后的L
}

//两个有序单链表的合并
void MergeList_L(LinkList& LA, LinkList& LB, LinkList& LC)
{//已知单链表LA个LB的元素按值非递减排列 
 //归并LA和LB得到的新表LC，LC的元素也按值非递减排列
	LNode* pa, * pb, * pc;
	pa = LA->next;
	pb = LB->next;			//pa和pb的初值分别指向两个表的第一个结点
	LC = LA;				//用LA的头结点作为LC的头结点
	pc = LC;				//pc的初值指向LC的头结点
	while (pa && pb)
	{//LA和LB均未到达表尾，依次“摘取”两表中值较小的结点插入到LC的最后
		if (pa->data <= pb->data)
		{//“摘取”pa所指结点
			pc->next = pa;	//将pa所指结点链接到pc所指结点之后
			pc = pa;		//pc指向pa
			pa = pa->next;	//pa指向下一结点
		}
		else
		{//“摘取”pb所指结点
			pc->next = pb;	//将pb所指结点链接到pc所指结点之后
			pc = pb;		//pc指向pb
			pb = pb->next;	//pb指向下一结点
		}
	}
	pc->next = pa ? pa : pb;//将非空表的剩余段插入到pc所指的结点后
	delete LB;				//释放LB的头结点
	cout << "合并完成！" << endl;
}

//显示操作菜单
void showMenu()
{
	cout << "*******************************" << endl;
	cout << "****** 1、建立单链表     ******" << endl;
	cout << "****** 2、显示单链表     ******" << endl;
	cout << "****** 3、查找单链表     ******" << endl;
	cout << "****** 4、插入单链表     ******" << endl;
	cout << "****** 5、删除单链表     ******" << endl;
	cout << "****** 6、两个单链表合并 ******" << endl;
	cout << "****** 0、退出程序       ******" << endl;
	cout << "*******************************" << endl;
}


int main()
{
	LNode* head;
	int wm = 0;
	InitList(head);//初始化链表

	while (true)
	{
		showMenu();
		cout << "请输入操作代码：";
		if (!(cin >> wm))
		{//错误输入时重新输入，防止死循环
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}

		switch (wm)
		{
		case 0:
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		case 1://建立单链表
			int n;
			cout << "请输入数据量：";
			cin >> n;
			CreatList_R(head, n);
			system("pause");
			system("cls");
			break;
		case 2://显示单链表
			cout << "当前链表为：" << endl;
			ShowList(head);
			system("pause");
			system("cls");
			break;
		case 3://查找单链表
			ElemType eA;
			cout << "请输入查找数据的值：";
			cin >> eA;
			cout << "数据" << eA << "的位置为：" << LocateElem(head, eA) << endl;
			system("pause");
			system("cls");
			break;
		case 4://插入单链表
			int iB;
			ElemType eB;
			cout << "请输入插入数据的位置：";
			cin >> iB;
			cout << "请输入插入数据的值：";
			cin >> eB;
			ListInsert(head, iB, eB);
			system("pause");
			system("cls");
			break;
		case 5://删除单链表
			int iC;
			cout << "请输入删除数据的位置：";
			cin >> iC;
			ListDelete(head, iC);
			system("pause");
			system("cls");
			break;
		case 6://两个单链表合并
		{
			LNode* LA, * LB, * LC;
			InitList(LA); InitList(LB); InitList(LC);//初始化链表
			//新建链表LA和LB
			int nA, nB;
			cout << "请输入链表LA的数据量：";
			cin >> nA; CreatList_R(LA, nA);//创建链表LA
			cout << "请输入链表LB的数据量：";
			cin >> nB; CreatList_R(LB, nB);//创建链表LB
			//给链表LA和LB排序
			cout << "有序链表LA为：" << endl; ShowList(Order(LA));
			cout << "有序链表LB为：" << endl; ShowList(Order(LB));
			//合并LA和LB
			MergeList_L(LA, LB, LC);
			cout << "合并后，LC为：" << endl;
			ShowList(LC);
			system("pause");
			system("cls");
			break;
		}
		default:
			cout << "请输入正确的数字！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}