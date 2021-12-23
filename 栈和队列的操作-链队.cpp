#include<iostream>
using namespace std;
#define OK 'o'
#define ERROR 'e'
typedef int QElemType;
typedef int Status;

//定义链队结构体
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;	//队头指针
	QueuePtr rear;	//队尾指针
}LinkQueue;

//1.链队的初始化
Status InitQueue(LinkQueue& Q)
{//构造一个空队列
	Q.front = Q.rear = new QNode;	//生成新结点作为头结点，队头和队尾指针指向此节点
	Q.front->next = NULL;			//头结点的指针域置空
	return OK;
}

//2.链队的入队
Status EnQueue(LinkQueue& Q, QElemType e)
{//插入元素e作为Q的新的队尾元素
	QNode* p;			//开辟新结点
	p = new QNode;		//为入队元素分配结点空间，用指针p指向
	p->data = e;		//将新结点数据域置为e
	p->next = NULL;
	Q.rear->next = p;	//将新结点插入到队尾
	Q.rear = p;			//修改队尾指针
	return OK;
}

//3.链队的出队
Status DeQueue(LinkQueue& Q, QElemType& e)
{//删除Q的队头元素，并用e返回其值
	QNode* p;				//开辟新的临时结点p，用于指向队头元素
	if (Q.front == Q.rear)
		return ERROR;		//若队列为空，返回ERROR
	p = Q.front->next;		//p指向队头元素
	e = p->data;			//e保存队头元素的值
	Q.front->next = p->next;//修改头结点的指针域
	if (Q.rear == p)
		Q.rear = Q.front;	//最后一个元素被删，队尾指针指向头结点
	delete p;				//释放原队头元素的空间
	return OK;
}

//4.取链队的队头元素
QElemType GetHead(LinkQueue Q)
{//返回Q的队头元素，不修改头指针
	if (Q.front != Q.rear)
		return Q.front->next->data;	//若队列非空，返回队头元素的值，队头指针不变
	else
		return ERROR;				//若队列为空，返回ERROR
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
	LinkQueue Q;			//创建循环队列Q
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