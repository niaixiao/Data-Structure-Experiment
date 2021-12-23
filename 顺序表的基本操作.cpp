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

//�����˳���
//˳���Ľ�����������һ����ΪSqList�Ľṹ��
typedef struct 
{
    ElemType *elem;//�洢�ռ�Ļ���ַ
    int length;//��ǰ����
}SqList;

// ˳���ĳ�ʼ��
Status InitList(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];//����һ���µ�˳���L ��Ϊ֮�����СΪMAXSIZE�Ŀռ�
    if (L.elem == NULL) 
        exit(OVERFLOW);// �洢�ռ����ʧ���˳�
    L.length = 0;
    return OK;
}

//1.˳�������
void ClearList(SqList &L)
{
    L.length = 0;
}

//2.�ж�˳����Ƿ��ǿձ���Ϊ�շ���TRUE�����򷵻�FALSE
bool ListEmpty(SqList &L)
{
    return(L.length == 0);
}

//3.�����Ա�ĳ���
int ListLength(SqList& L)
{
    return (L.length);
}

//4.˳����ȡֵ
Status GetElem(SqList L, int i, ElemType &e) 
{
    if (i<1 || i>L.length)//�ж�iȡֵ�Ƿ����
        return ERROR;
    else
    {
        e = L.elem[i - 1];
        return OK;
    }
}

//5.��ǰ��
Status PriorElem(SqList L, int cur_e, ElemType &pre_e) 
{
    int i;
    for (i = 0; i <= L.length; i++) 
    {    //��ͷ����˳���
        if (cur_e == L.elem[i])
        {  //���ҵ���֮ƥ������ݣ��򷵻ص�ǰ�ڵ���±�
            if (i == 0) 
            {//��һλԪ����ǰ��
                cout << "����ʧ�ܣ�" << cur_e << "��ǰ����" << endl;
                return ERROR;
            }
            else 
            {
                pre_e = L.elem[i - 1];
                cout << "�����ɹ���" << cur_e << "��ǰ��Ϊ��" << pre_e << endl;
                return OK;
            }
        }
        if (i == L.length) 
        {//�������Ա��ڷ���ERROR
            cout << "����ʧ�ܣ�" << cur_e << "�������Ա��ڣ�" << endl;
            return ERROR;
        }
    }
}

//6.����
Status NextElem(SqList L, int cur_e, ElemType& next_e) 
{
    int i;
    for (i = 0; i <= L.length; i++) 
    {    //��ͷ����˳���
        if (cur_e == L.elem[i])
        {  //���ҵ���֮ƥ������ݣ��򷵻ص�ǰ�ڵ���±�
            if (i == L.length-1) 
            {//���һλԪ���޺��
                cout << "����ʧ�ܣ�" << cur_e << "�޺�̣�" << endl;
                return ERROR;
            }
            else 
            {
                next_e = L.elem[i + 1];
                cout << "�����ɹ���" << cur_e << "�ĺ��Ϊ��" << next_e << endl;
                return OK;
            }
        }
        if (i == L.length)
        {//�������Ա��ڷ���ERROR
            cout << "����ʧ�ܣ�" << cur_e << "�������Ա��ڣ�" << endl;
            return ERROR;
        }
    }
}

//7.�����Ա�ָ��λ�ò���Ԫ��
Status ListInsert(SqList &L, int i, ElemType e) 
{
    if ((i < 1) || (i > L.length + 1))
    {//�ж�iֵ�Ƿ����
        cout << "�����ַ���Ϸ�" << endl;//iֵ���Ϸ�
        return ERROR;
    }

    if (L.length == MAXSIZE)
    {
        cout << "�洢�ռ�����" << endl;//��ǰ����ռ�����
        return ERROR;
    }
    for (int j = L.length - 1; j >= i - 1; j--)
        L.elem[j + 1] = L.elem[j];//����λ�ü�֮���Ԫ�غ���
    //�����ǴӺ�Ƚϵķ��� ���Ա߱Ƚϱ��ƶ�
    L.elem[i - 1] = e;//����Ԫ��e�����i��λ��
    ++L.length;//����1
    return OK;
}

//8.ɾ�����Ա�ָ��λ��Ԫ��
Status ListDelete(SqList &L, int i) 
{
    
    //iֵ�ĺϷ���Χ��1<=i<=L.length
    if ((i < 1) || (i > L.length))
    {
        cout << "ɾ����ַ���Ϸ�" << endl;
        return ERROR;
    }

    for (int j = i; j <= L.length; j++)
        L.elem[j - 1] = L.elem[j];//��ɾ��Ԫ��֮���Ԫ��ǰ��
    --L.length;//����1
    cout << "ɾ���ɹ���" << endl;
    return OK;
}

//9.��ʾ���Ա�
Status PrintList(SqList L)
{
    if (L.length == 0)
    {//�ж�L�Ƿ�Ϊ�ձ�
        cout << "�գ�" << endl;
        return ERROR;
    }
    else
    {//����L
        for (int k = 0; k < L.length; k++)
        {
            if (k == L.length - 1)
            {
                cout << L.elem[k];
            }
            else {
                cout << L.elem[k] << ' ';//����Ԫ���м��ÿո����
            }
        }
        cout << endl;
        return OK;
    }
}

//10.�������ϵ����㲿��
//����˳���
void CreateList(SqList& L, ElemType a[], int n)
{//�������е����ݴ��ݸ�L
    for (int i = 0; i < n; ++i)
        L.elem[i] = a[i];
    L.length = n;
}

//���Ա�Ԫ��ֵ����
int LocateElem(SqList L, ElemType e)
{//������e��ȵ�Ԫ�ص�λ�ã������ظ�����
    int i = 0;
    while (i < L.length && L.elem[i] != e)
        i++;//��ǰλ��Ԫ�ز�����eʱ���Ƚ���һλ��Ԫ��
    if (i >= L.length)
        return 0;
    else
        return i + 1;
}

//10.1 A��B�����
void BingList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//��ʼ��C�� 
    CreateList(L3, L1.elem, L1.length);//��L1�е�Ԫ�ش��ݸ�L3
    for (int i = 0; i < L2.length; ++i)//����L2�е�Ԫ��
        if (!(LocateElem(L1, L2.elem[i])))
            ListInsert(L3, L3.length + 1, L2.elem[i]);//��L2����L1����ȵ�Ԫ�ز���L3��
}

//10.2 A��B�����
void JiaoList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//��ʼ��C��
    for (int i = 0; i < L1.length; ++i)//����L1�е�Ԫ��
        if ((LocateElem(L2, L1.elem[i])))
            ListInsert(L3, L3.length + 1, L1.elem[i]);//��������������ȵ�Ԫ�ز���L3��
}

//10.3 A-B�����
void A_BJianList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//��ʼ��C��
    for (int i = 0; i < L1.length; ++i)//����L1�е�Ԫ��
        if (!(LocateElem(L2, L1.elem[i])))
            ListInsert(L3, L3.length + 1, L1.elem[i]);//��L1����L2����ȵ�Ԫ�ز���L3��
}

//10.4 B-A�����
void B_AJianList(SqList L1, SqList L2, SqList& L3)
{
    L3.length = 0;		//��ʼ��C��
    for (int i = 0; i < L2.length; ++i)//����L2�е�Ԫ��
        if (!(LocateElem(L1, L2.elem[i])))
            ListInsert(L3, L3.length + 1, L2.elem[i]);//��L2����L1����ȵ�Ԫ�ز���L3��
}

//�����º�������������ϵĲ���
int Operation()
{
    int i; int wm;
    //����L1��Ԫ�أ�����L1
    SqList L1;
    InitList(L1);
    ElemType arr1[MAXSIZE];
    int n1;
    cout << "�����뼯��A��Ԫ�ظ�����";
    cin >> n1;
    cout << "������Ԫ�أ�";
    for (i = 0; i < n1; i++)
        cin >> arr1[i];
    CreateList(L1, arr1, n1);
    //����L2��Ԫ�أ�����L2
    SqList L2;
    InitList(L2);
    ElemType arr2[MAXSIZE];
    int n2;
    cout << "�����뼯��B��Ԫ�ظ�����";
    cin >> n2;
    cout << "������Ԫ�أ�";
    for (i = 0; i < n2; i++)
        cin >> arr2[i];
    CreateList(L2, arr2, n2);
    //��ӡL1��L2
    cout << "����AΪ��"; PrintList(L1);
    cout << "����BΪ��"; PrintList(L2);

    //��ʼ�������ϼ������
    SqList L3;//����L3
    InitList(L3);//L3��ʼ��
    //��ӡ�����˵�
    cout << "===�����˵�===" << endl;
    cout << "   1---A��B" << endl;
    cout << "   2---A��B" << endl;
    cout << "   3---A-B" << endl;
    cout << "   4---A+B" << endl;
    cout << "   5---�˳�" << endl;
    
    while (true)
    {
        cout << "��ѡ������Ҫ���еĲ�����";
        cin >> wm;
        switch (wm)
        {
        case 1:
            BingList(L1, L2, L3);
            cout << "\tA��B���ϵ�Ԫ��Ϊ:"; PrintList(L3);
            break;
        case 2:
            JiaoList(L1, L2, L3);
            cout << "\tA��B���ϵ�Ԫ��Ϊ:"; PrintList(L3);
            break;
        case 3:
            A_BJianList(L1, L2, L3);
            cout << "\tA-B���ϵ�Ԫ��Ϊ:"; PrintList(L3);
            break;
        case 4:
            B_AJianList(L1, L2, L3);
            cout << "\tB-A���ϵ�Ԫ��Ϊ:"; PrintList(L3);
            break;
        case 5:
            ClearList(L1);//�ͷ�ABC�� 
            ClearList(L2);
            ClearList(L3);
            cout << "\n----˳��������----" << endl;
            return 0;
        default:
            cout << "��������ȷ�����֣�" << endl;
            break;
        }
    }
    return 0;
}

//��ʾ�˵�����
void showMenu()
{
    cout << "  1----������Ա�" << endl;
    cout << "  2----�ж����Ա��Ƿ�Ϊ��" << endl;
    cout << "  3----�����Ա���" << endl;
    cout << "  4----��ȡ���Ա�ָ��λ��Ԫ��" << endl;
    cout << "  5----��ǰ��" << endl;
    cout << "  6----����" << endl;
    cout << "  7----�����Ա�ָ��λ�ò���Ԫ��" << endl;
    cout << "  8----ɾ�����Ա�ָ��λ��Ԫ��" << endl;
    cout << "  9----��ʾ���Ա�" << endl;
    cout << "  10---�����������ϵ�����" << endl;
    cout << "  0----�˳�" << endl;
}

int main()
{
    //������˳���
    SqList L;
    InitList(L);
    int wm = 0;
    int i;

    //ʵ�ֳ������
    while (true)
    {
        showMenu();
        cout << "������������룺";
        cin >> wm;

        //ѡ��
        switch (wm)
        {
        case 1:
            ClearList(L);
            cout << "----˳��������----" << endl;
            system("pause");
            system("cls");
            break;

        case 2:
            if (ListEmpty(L) == true)
            {
                cout << "�����Ա�Ϊ�ձ�\n" << endl;
            }
            else
            {
                cout << "�����Ա�Ϊ�ǿձ�\n" << endl;
            }
            system("pause");
            system("cls");
            break;

        case 3:
            cout << "�����Ա�ĳ���Ϊ: " << ListLength(L) << endl;
            system("pause");
            system("cls");
            break;

        case 4:
            cout << "��������Ҫ����Ԫ�ص�λ�� i=";
            cin >> i;
            ElemType e_Get;
            if (GetElem(L, i, e_Get) == ERROR)
                cout << "--ERROR-- iֵ������" << endl;
            else
                cout << "��" << i << "λԪ�ص�ֵΪ��" << e_Get << "\n" << endl;
            system("pause");
            system("cls");
            break;

        case 5:
            int cur_e;
            ElemType pre_e;
            cout << "������Ҫ��ѯǰ�������ݣ�";
            cin >> cur_e;
            PriorElem(L, cur_e, pre_e);
            system("pause");
            system("cls");
            break;

        case 6:
            ElemType next_e;
            cout << "������Ҫ��ѯ��̵����ݣ�";
            cin >> cur_e;
            NextElem(L, cur_e, next_e);
            system("pause");
            system("cls");
            break;

        case 7: 
        {
            int i_Ins, e_Ins;
            cout << "������Ҫ����Ԫ�ص�λ�ú�����:" << endl;
            cin >> i_Ins >> e_Ins;
            if (ListInsert(L, i_Ins, e_Ins) != ERROR)
                cout << "����ɹ���" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 8:
        {
            int i_Del;
            cout << "������Ҫɾ����Ԫ�ص�λ��" << endl;
            cin >> i;
            cout << "----����ɾ����" << i << "λԪ��----" << endl;
            ListDelete(L, i);
            system("pause");
            system("cls");
            break;
        }

        case 9:
            cout << "��ǰ���Ա�Ϊ��" << endl;
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
            cout << "��ӭ�´�ʹ��" << endl;
            system("pause");
            return 0;
            break;

        default:
            cout << "��������ȷ�����֣�" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}
