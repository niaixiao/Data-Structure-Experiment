#include<iostream>
using namespace std;
#define OK 'o'
#define ERROR 'e'
typedef int SElemType;
typedef int Status;

//定义顺序栈结构体
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

//1.链栈的初始化
Status InitStack(LinkStack& S)
{//构造一个空栈S，栈顶指针置空
	S = NULL;
	return OK;
}

//2.链栈的入栈
Status Push(LinkStack& S, SElemType e)
{//在栈顶插入元素e
	StackNode* p;
	p = new StackNode;	//生成新结点
	p->data = e;		//将新结点数据域置为e
	p->next = S;		//将新结点插入栈顶
	S = p;				//修改栈顶指针为p
	return OK;
}

//3.链栈的出栈
Status Pop(LinkStack& S, SElemType& e)
{//删除S的栈顶元素，用e返回其值
	StackNode* p;		//创建临时指针p,用于临时保存栈顶元素
	if (S == NULL)
		return ERROR;	//栈空
	e = S->data;		//将栈顶元素赋给e
	p = S;				//用p临时保存栈顶元素空间，以备释放
	S = S->next;		//修改栈顶指针
	delete p;			//释放p
	return OK;
}

//4.取链栈的栈顶元素
SElemType GetTop(LinkStack S)
{//返回S的栈顶元素，不修改栈顶指针
	if (S != NULL)
		return S->data;	//返回栈顶元素的值，栈顶指针不变
	else
		return ERROR;
}

//显示操作菜单
void ShowMenu()
{
	cout << "=========================" << endl;
	cout << "***   1---初始化      ***" << endl;
	cout << "***   2---入栈        ***" << endl;
	cout << "***   3---出栈        ***" << endl;
	cout << "***   4---取栈顶元素  ***" << endl;
	cout << "***   0---退出        ***" << endl;
	cout << "=========================" << endl;
}

//主函数
int main()
{
	LinkStack S;	//创建顺序栈S
	InitStack(S);	//初始化顺序栈S

	int wm;			//创建操作选择参数
	ShowMenu();		//显示操作菜单

	//进入操作循环
	while (true)
	{
		cout << "请输入操作代码：";
		cin >> wm;	//选择操作代码
		switch (wm)
		{//选择结构
		case 1:
			if (InitStack(S) == OK)//初始化成功时，提示用户
				cout << "初始化成功！" << endl;
			else//不成功时，提示分配失败
				cout << "储存空间分配失败！" << endl;
			break;

		case 2:
		{
			SElemType e_Push;
			cout << "请输入要入栈的元素：";
			cin >> e_Push;
			if (Push(S, e_Push) == OK)//入栈成功时，打印出入栈元素，否则提示入栈失败
				cout << "\t\t\t入栈：" << e_Push << endl;
			else
				cout << "\t\t\t入栈失败！栈已满！" << endl;
			break;
		}

		case 3:
		{
			SElemType e_Pop;
			if (Pop(S, e_Pop) == OK)//出栈成功时，打印出出栈元素，否则提示出栈失败
				cout << "\t\t\t\t出栈：" << e_Pop << endl;
			else
				cout << "\t\t\t\t出栈失败！栈空！" << endl;
			break;
		}

		case 4:
			if (GetTop(S) != ERROR)//栈不为空时，打印栈顶元素
				cout << "栈顶元素为：" << GetTop(S) << endl;
			else//栈为空时，提示用户
				cout << "栈空！" << endl;
			break;

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