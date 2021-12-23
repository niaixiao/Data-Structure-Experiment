#include<iostream>
using namespace std;
#define MAXSIZE 100					//顺序栈储存空间的初始分配量
#define OK 'o'
#define ERROR 'e'
typedef int SElemType;
typedef int Status;

//定义顺序栈结构体
typedef struct
{
	SElemType* base;				//栈底指针
	SElemType* top;					//栈顶指针
	int stacksize;					//栈可用的最大容量
}SqStack;

//1.顺序栈的初始化
Status InitStack(SqStack& S)
{//构造一个空栈
	S.base = new SElemType[MAXSIZE];//为顺序栈动态分配最大容量为MAXSIZE的数组空间
	if (!S.base)
		exit(OVERFLOW);				//储存空间分配失败时退出
	S.top = S.base;					//top初始为base，空栈
	S.stacksize = MAXSIZE;			//stacksize置为栈的最大容量MAXSIZE
	return OK;
}

//2.顺序栈的入栈
Status Push(SqStack& S, SElemType e)
{//插入元素e为新的栈顶元素
	if (S.top - S.base == S.stacksize)
		return ERROR;				//栈已满
	*S.top++ = e;					//将元素e压入栈顶，栈顶指针加1
	return OK;
}

//3.顺序栈的出栈
Status Pop(SqStack& S, SElemType& e)
{//删除S的栈顶元素，用e返回其值
	if (S.top == S.base)
		return ERROR;				//栈空
	e = *--S.top;					//栈顶指针减1，将栈顶元素赋值给e
	return OK;
}

//4.取顺序栈的栈顶元素
SElemType GetTop(SqStack S)
{//返回S的栈顶元素，不修改栈顶指针
	if (S.top != S.base)			//栈非空时，返回栈顶元素的值，指针不变
		return *(S.top - 1);
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
	SqStack S;				//创建顺序栈S
	InitStack(S);			//初始化顺序栈S
	
	int wm;					//创建操作选择参数
	ShowMenu();				//显示操作菜单

	//进入操作循环
	while (true)
	{
		cout << "请输入操作代码：";
		cin >> wm;			//选择操作代码
		switch (wm)
		{					//选择结构
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