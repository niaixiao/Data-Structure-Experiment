/*
Wang Meng @henu
*/
#include<iostream>
using namespace std;
#define MAXSIZE 100
#define ERROR 'e'
#define OK 'o'
typedef int ElemType;
typedef int Status;

//构造空顺序表
//顺序表的建立：定义了一个名为SqList的结构体
typedef struct 
{
    ElemType *elem;//存储空间的基地址
    int length;//当前长度
}SqList;

// 顺序表的初始化
Status InitList(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];//构造一个新的顺序表L 并为之分配大小为MAXSIZE的空间
    if (L.elem == NULL) 
        exit(OVERFLOW);// 存储空间分配失败退出
    L.length = 0;
    return OK;
}

//1.顺序表的清空
void ClearList(SqList &L)
{
    L.length = 0;
}

//2.判断顺序表是否是空表，若为空返回TRUE，否则返回FALSE
bool ListEmpty(SqList &L)
{
    return(L.length == 0);
}

//3.求线性表的长度
int ListLength(SqList& L)
{
    return (L.length);
}

//4.顺序表的取值
Status GetElem(SqList L, int i, ElemType &e) 
{
    if (i<1 || i>L.length)//判断i取值是否合理
        return ERROR;
    else
    {
        e = L.elem[i - 1];
        return OK;
    }
}

//5.求前驱
Status PriorElem(SqList L, int cur_e, ElemType &pre_e) 
{
    int i;
    for (i = 0; i <= L.length; i++) 
    {    //从头遍历顺序表
        if (cur_e == L.elem[i])
        {  //若找到与之匹配的数据，则返回当前节点的下标
            if (i == 0) 
            {//第一位元素无前驱
                cout << "操作失败！" << cur_e << "无前驱！" << endl;
                return ERROR;
            }
            else 
            {
                pre_e = L.elem[i - 1];
                cout << "操作成功！" << cur_e << "的前驱为：" << pre_e << endl;
                return OK;
            }
        }
        if (i == L.length) 
        {//不在线性表内返回ERROR
            cout << "操作失败！" << cur_e << "不在线性表内！" << endl;
            return ERROR;
        }
    }
}

//6.求后继
Status NextElem(SqList L, int cur_e, ElemType& next_e) 
{
    int i;
    for (i = 0; i <= L.length; i++) 
    {    //从头遍历顺序表
        if (cur_e == L.elem[i])
        {  //若找到与之匹配的数据，则返回当前节点的下标
            if (i == L.length-1) 
            {//最后一位元素无后继
                cout << "操作失败！" << cur_e << "无后继！" << endl;
                return ERROR;
            }
            else 
            {
                next_e = L.elem[i + 1];
                cout << "操作成功！" << cur_e << "的后继为：" << next_e << endl;
                return OK;
            }
        }
        if (i == L.length)
        {//不在线性表内返回ERROR
            cout << "操作失败！" << cur_e << "不在线性表内！" << endl;
            return ERROR;
        }
    }
}

//7.在线性表指定位置插入元素
Status ListInsert(SqList &L, int i, ElemType e) 
{
    if ((i < 1) || (i > L.length + 1))
    {//判断i值是否合理
        cout << "插入地址不合法" << endl;//i值不合法
        return ERROR;
    }

    if (L.length == MAXSIZE)
    {
        cout << "存储空间已满" << endl;//当前储存空间已满
        return ERROR;
    }
    for (int j = L.length - 1; j >= i - 1; j--)
        L.elem[j + 1] = L.elem[j];//插入位置及之后的元素后移
    //以上是从后比较的方法 可以边比较边移动
    L.elem[i - 1] = e;//将新元素e放入第i个位置
    ++L.length;//表长加1
    return OK;
}

//8.删除线性表指定位置元素
Status ListDelete(SqList &L, int i) 
{
    
    //i值的合法范围是1<=i<=L.length
    if ((i < 1) || (i > L.length))
    {
        cout << "删除地址不合法" << endl;
        return ERROR;
    }

    for (int j = i; j <= L.length; j++)
        L.elem[j - 1] = L.elem[j];//被删除元素之后的元素前移
    --L.length;//表长减1
    cout << "删除成功！" << endl;
    return OK;
}

//9.显示线性表
Status PrintList(SqList L)
{
    if (L.length == 0)
    {//判断L是否为空表
        cout << "空！" << endl;
        return ERROR;
    }
    else
    {//遍历L
        for (int k = 0; k < L.length; k++)
        {
            if (k == L.length - 1)
            {
                cout << L.elem[k];
            }
            else {
                cout << L.elem[k] << ' ';//相邻元素中间用空格隔开
            }
        }
        cout << endl;
        return OK;
    }
}

//10.两个集合的运算部分
//建立顺序表
void CreateList(SqList& L, ElemType a[], int n)
{//把数组中的数据传递给L
    for (int i = 0; i < n; ++i)
        L.elem[i] = a[i];
    L.length = n;
}

//线性表按元素值查找
int LocateElem(SqList L, ElemType e)
{//查找与e相等的元素的位置，并返回给函数
    int i = 0;
    while (i < L.length && L.elem[i] != e)
        i++;//当前位置元素不等于e时，比较下一位置元素
    if (i >= L.length)
        return 0;
    else
        return i + 1;
}

//10.1 A∪B的求解
void BingList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//初始化C表 
    CreateList(L3, L1.elem, L1.length);//把L1中的元素传递给L3
    for (int i = 0; i < L2.length; ++i)//遍历L2中的元素
        if (!(LocateElem(L1, L2.elem[i])))
            ListInsert(L3, L3.length + 1, L2.elem[i]);//将L2中与L1不相等的元素插入L3中
}

//10.2 A∩B的求解
void JiaoList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//初始化C表
    for (int i = 0; i < L1.length; ++i)//遍历L1中的元素
        if ((LocateElem(L2, L1.elem[i])))
            ListInsert(L3, L3.length + 1, L1.elem[i]);//将两个集合中相等的元素插入L3中
}

//10.3 A-B的求解
void A_BJianList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//初始化C表
    for (int i = 0; i < L1.length; ++i)//遍历L1中的元素
        if (!(LocateElem(L2, L1.elem[i])))
            ListInsert(L3, L3.length + 1, L1.elem[i]);//将L1中与L2不相等的元素插入L3中
}

//10.4 B-A的求解
void B_AJianList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//初始化C表
    for (int i = 0; i < L2.length; ++i)//遍历L2中的元素
        if (!(LocateElem(L1, L2.elem[i])))
            ListInsert(L3, L3.length + 1, L2.elem[i]);//将L2中与L1不相等的元素插入L3中
}

//建立新函数完成两个集合的操作
int Operation()
{
    int i; int wm;
    //输入L1的元素，创建L1
    SqList L1;
    InitList(L1);
    ElemType arr1[MAXSIZE];
    int n1;
    cout << "请输入集合A的元素个数：";
    cin >> n1;
    cout << "请输入元素：";
    for (i = 0; i < n1; i++)
        cin >> arr1[i];
    CreateList(L1, arr1, n1);
    //输入L2的元素，创建L2
    SqList L2;
    InitList(L2);
    ElemType arr2[MAXSIZE];
    int n2;
    cout << "请输入集合B的元素个数：";
    cin >> n2;
    cout << "请输入元素：";
    for (i = 0; i < n2; i++)
        cin >> arr2[i];
    CreateList(L2, arr2, n2);
    //打印L1和L2
    cout << "集合A为："; PrintList(L1);
    cout << "集合B为："; PrintList(L2);

    //开始两个集合间的运算
    SqList L3;//创建L3
    InitList(L3);//L3初始化
    //打印操作菜单
    cout << "===操作菜单===" << endl;
    cout << "   1---A∪B" << endl;
    cout << "   2---A∩B" << endl;
    cout << "   3---A-B" << endl;
    cout << "   4---A+B" << endl;
    cout << "   5---退出" << endl;
    
    while (true)
    {
        cout << "请选择您想要进行的操作：";
        cin >> wm;
        switch (wm)
        {
        case 1:
            BingList(L1, L2, L3);
            cout << "\tA∪B集合的元素为:"; PrintList(L3);
            break;
        case 2:
            JiaoList(L1, L2, L3);
            cout << "\tA∩B集合的元素为:"; PrintList(L3);
            break;
        case 3:
            A_BJianList(L1, L2, L3);
            cout << "\tA-B集合的元素为:"; PrintList(L3);
            break;
        case 4:
            B_AJianList(L1, L2, L3);
            cout << "\tB-A集合的元素为:"; PrintList(L3);
            break;
        case 5:
            ClearList(L1);//释放ABC表 
            ClearList(L2);
            ClearList(L3);
            cout << "\n----顺序表已清空----" << endl;
            return 0;
        default:
            cout << "请输入正确的数字！" << endl;
            break;
        }
    }
    return 0;
}

//显示菜单界面
void showMenu()
{
    cout << "  1----清空线性表" << endl;
    cout << "  2----判断线性表是否为空" << endl;
    cout << "  3----求线性表长度" << endl;
    cout << "  4----获取线性表指定位置元素" << endl;
    cout << "  5----求前驱" << endl;
    cout << "  6----求后继" << endl;
    cout << "  7----在线性表指定位置插入元素" << endl;
    cout << "  8----删除线性表指定位置元素" << endl;
    cout << "  9----显示线性表" << endl;
    cout << "  10---进入两个集合的运算" << endl;
    cout << "  0----退出" << endl;
}

int main()
{
    //创建空顺序表
    SqList L;
    InitList(L);
    int wm = 0;
    int i;

    //实现程序界面
    while (true)
    {
        showMenu();
        cout << "请输入操作代码：";
        cin >> wm;

        //选择
        switch (wm)
        {
        case 1:
            ClearList(L);
            cout << "----顺序表已清空----" << endl;
            system("pause");
            system("cls");
            break;

        case 2:
            if (ListEmpty(L) == true)
            {
                cout << "该线性表为空表！\n" << endl;
            }
            else
            {
                cout << "该线性表为非空表！\n" << endl;
            }
            system("pause");
            system("cls");
            break;

        case 3:
            cout << "该线性表的长度为: " << ListLength(L) << endl;
            system("pause");
            system("cls");
            break;

        case 4:
            cout << "请输入想要查找元素的位置 i=";
            cin >> i;
            ElemType e_Get;
            if (GetElem(L, i, e_Get) == ERROR)
                cout << "--ERROR-- i值不合理！" << endl;
            else
                cout << "第" << i << "位元素的值为：" << e_Get << "\n" << endl;
            system("pause");
            system("cls");
            break;

        case 5:
            int cur_e;
            ElemType pre_e;
            cout << "请输入要查询前驱的数据：";
            cin >> cur_e;
            PriorElem(L, cur_e, pre_e);
            system("pause");
            system("cls");
            break;

        case 6:
            ElemType next_e;
            cout << "请输入要查询后继的数据：";
            cin >> cur_e;
            NextElem(L, cur_e, next_e);
            system("pause");
            system("cls");
            break;

        case 7: 
        {
            int i_Ins, e_Ins;
            cout << "请输入要插入元素的位置和数据:" << endl;
            cin >> i_Ins >> e_Ins;
            if (ListInsert(L, i_Ins, e_Ins) != ERROR)
                cout << "插入成功！" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 8:
        {
            int i_Del;
            cout << "请输入要删除的元素的位置" << endl;
            cin >> i;
            cout << "----正在删除第" << i << "位元素----" << endl;
            ListDelete(L, i);
            system("pause");
            system("cls");
            break;
        }

        case 9:
            cout << "当前线性表为：" << endl;
            PrintList(L);
            system("pause");
            system("cls");
            break;

        case 10:
            Operation();
            system("pause");
            system("cls");
            break;

        case 0:
            cout << "欢迎下次使用" << endl;
            system("pause");
            return 0;
            break;

        default:
            cout << "请输入正确的数字！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}
