#include<iostream>
using namespace std;
#define MAXQSIZE 6
#define OK 'o'
#define ERROR 'e'
typedef int QElemType;
typedef int Status;

//定义循环队列结构体
typedef struct
{
	QElemType* base;//储存空间基地址
	int front;//头指针
	int rear;//尾指针
}SqQueue;

//1.循环队列的初始化
Status InitQueue(SqQueue& Q)
{//构造一个空队列Q
	Q.base = new QElemType[MAXQSIZE];//为队列分配一个最大容量为MAXQSIZE的数组空间
	if (!Q.base)
		exit(OVERFLOW);//储存分配失败
	Q.front = Q.rear = 0;//头指针和尾指针置为0，队列为空
	return OK;
}

//2.循环队列的入队
Status EnQueue(SqQueue& Q, QElemType e)
{//插入元素e为Q的新的队尾元素
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
		return ERROR;//尾指针在循环意义上加1后等于头指针，表明队满
	Q.base[Q.rear] = e;//将元素e插入队尾
	Q.rear = (Q.rear + 1) % MAXQSIZE;//队尾指针加1
	return OK;
}

//3.循环队列的出队
Status DeQueue(SqQueue& Q, QElemType& e)
{//删除Q的队头元素，用e返回其值
	if (Q.front == Q.rear)
		return ERROR;//队空
	e = Q.base[Q.front];//保存队头元素
	Q.front = (Q.front + 1) % MAXQSIZE;//队头指针加1
	return OK;
}

//4.取循环队列的队头元素
QElemType GetHead(SqQueue Q)
{//返回Q的队头元素，不修改队头指针
	if (Q.front != Q.rear)
		return Q.base[Q.front];//返回队头元素的值，队头指针不变
	else
		return ERROR;
}

//显示操作菜单
void ShowMenu()
{
	cout << "=========================" << endl;
	cout << "***   1---初始化      ***" << endl;
	cout << "***   2---入队        ***" << endl;
	cout << "***   3---出队        ***" << endl;
	cout << "***   4---取队头元素  ***" << endl;
	cout << "***   0---退出        ***" << endl;
	cout << "=========================" << endl;
}

int main()
{
	SqQueue	Q;				//创建循环队列Q
	InitQueue(Q);			//初始化Q

	int wm;					//创建操作选择参数
	ShowMenu();				//显示操作菜单

	//进入操作循环
	while (true)
	{
		cout << "请输入操作代码：";
		cin >> wm;			//选择操作代码
		switch (wm)
		{//选择结构
		case 1:
			if (InitQueue(Q) == OK)//初始化成功时，提示用户
				cout << "初始化成功！" << endl;
			else//不成功时，提示分配失败
				cout << "储存空间分配失败！" << endl;
			break;

		case 2:
		{
			QElemType e_EnQ;
			cout << "请输入要入队的元素：";
			cin >> e_EnQ;
			if (EnQueue(Q, e_EnQ) == OK)//入队成功时，打印出入队元素，否则提示入队失败
				cout << "\t\t\t入队：" << e_EnQ << endl;
			else
				cout << "\t\t\t入队失败！队列已满！" << endl;
			break;
		}

		case 3:
		{
			QElemType e_DeQ;
			if (DeQueue(Q, e_DeQ) == OK)//出队成功时，打印出出队元素，否则提示出队失败
				cout << "\t\t\t\t出队：" << e_DeQ << endl;
			else
				cout << "\t\t\t\t出队失败！队空！" << endl;
			break;
		}

		case 4:
			if (GetHead(Q) != ERROR)//队不为空时，打印队头元素
				cout << "队头元素为：" << GetHead(Q) << endl;
			else//队列为空时，提示用户
				cout << "队列为空！" << endl;
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