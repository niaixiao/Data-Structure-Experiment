#include<iostream>
using namespace std;

#define MaxInt 32767//��ʾ����ֵ
#define MVNum 100//��󶥵���
#define OK 1
#define ERROR 0
typedef char VerTexType;//���趥�����������Ϊ�ַ���
typedef int ArcType;//����ߵ�Ȩֵ����Ϊ����
typedef int OtherInfo;
typedef int Status;

//-----ͼ���ڽӾ��󴢴��ʾ-----
typedef struct
{
	VerTexType* vexs;//�����
	ArcType** arcs;//�ڽӾ���
	int vexnum, arcnum;//ͼ�ĵ�ǰ�����ͱ���
}AMGraph;

//-----ͼ���ڽӱ����ʾ-----
typedef struct ArcNode//�߽��
{
	int adjvex;//�ñ���ָ��Ķ����λ��
	struct ArcNode* nextarc;//ָ����һ���ߵ�ָ��
	OtherInfo info;//�ͱ���ص���Ϣ
}ArcNode;
typedef struct VNode//������Ϣ
{
	VerTexType data;
	ArcNode* firstarc;//ָ���һ����������ıߵ�ָ��
}VNode, AdjList[MVNum];//AdjList��ʾ�ڽӱ�����
typedef struct//�ڽӱ�
{
	AdjList vertices;
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ı���
}ALGraph;

//ͼ�ĳ�ʼ��
Status InitGraph(AMGraph& G)
{//�����ڽӾ����ʾ��ͼ�ĳ�ʼ��
	G.vexs = new VerTexType[MVNum];
	G.arcs = new ArcType * [MVNum];
	for (int i = 0; i < MVNum; i++)
		G.arcs[i] = new int[MVNum];
	G.vexnum = 0; G.arcnum = 0;
	return OK;
}

//����Ԫ��u��ͼ�е�λ��
int LocateVex(AMGraph G, VerTexType u)
{
	if (G.vexnum == 0)//������Ϊ0ʱ����-1
		return -1;
	for (int i = 0; i < G.vexnum; ++i)
		if (u == G.vexs[i])//������������u�ڶ����з������±꣬���򷵻�-1
			return i;
	return -1;
}
int LocateVex(ALGraph G, VerTexType u)
{
	if (G.vexnum == 0)//������Ϊ0ʱ����-1
		return -1;
	for (int i = 0; i < G.vexnum; ++i)
		if (u == G.vertices[i].data)//������������u�ڶ����з������±꣬���򷵻�-1
			return i;
	return -1;
}

//�ڽӾ����ʾ������������
Status CreateUDN(AMGraph& G)
{//�����ڽӾ����ʾ��������������G
	cout << "�������ܶ��������ܱ�����";
	if (!(cin >> G.vexnum >> G.arcnum))//�����ܶ��������ܱ���
		return ERROR;
	int i, j, k;
	cout << "������������Ϣ��";
	for (i = 0; i < G.vexnum; ++i)//������������Ϣ
		cin >> G.vexs[i];
	for (i = 0; i < G.vexnum; ++i)//��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵMaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;
	VerTexType v1, v2; ArcType w;
	cout << "����һ���������Ķ��㼰Ȩֵ��";
	for (k = 0; k < G.arcnum; ++k)//�����ڽӾ���
	{
		cin >> v1 >> v2 >> w;//����һ���������Ķ��㼰Ȩֵ
		i = LocateVex(G, v1); j = LocateVex(G, v2);//ȷ��v1��v2��G�е�λ�ã�������������±�
		G.arcs[i][j] = w;//��<v1,v2>��Ȩֵ��Ϊw
		G.arcs[j][i] = G.arcs[i][j];//��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw
	}
	return OK;
}

//�����ڽӱ��ʾ������������
Status CreateUDG(ALGraph& G)
{//�����ڽӱ��ʾ��������������G
	cout << "�������ܶ��������ܱ�����";
	if (!(cin >> G.vexnum >> G.arcnum))//�����ܶ��������ܱ���
		return ERROR;
	int i, j, k;
	cout << "������������Ϣ��";
	for (i = 0; i < G.vexnum; ++i)
	{
		cin >> G.vertices[i].data;//���붥��ֵ
		G.vertices[i].firstarc = NULL;//��ʼ����ͷ����ָ����ΪNULL
	}
	VerTexType v1, v2; ArcType w;
	cout << "����һ���������Ķ��㼰Ȩֵ��";
	for (k = 0; k < G.arcnum; ++k)//������ߣ������ڽӱ�
	{
		cin >> v1 >> v2 >> w;//����һ�����������������㼰Ȩֵ
		i = LocateVex(G, v1); j = LocateVex(G, v2);//ȷ��v1��v2��G�е�λ�ã���������G.vertices�е����
		ArcNode* p1 = new ArcNode;//����һ���µı߽��*p1
		p1->adjvex = j;//�ڽӵ����Ϊj
		p1->info = w;//�ߵ�ȨֵΪw
		p1->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p1;//���½��*p1���붥��vi�ı߱�ͷ��
		ArcNode* p2 = new ArcNode;//������һ���ԳƵı߽��*p2
		p2->adjvex = i;//�ڽӵ����Ϊi
		p2->info = w;//�ߵ�ȨֵΪw
		p2->nextarc = G.vertices[j].firstarc; G.vertices[j].firstarc = p2;//���½��*p2���붥��vj�ı߱�ͷ��
	}
	return OK;
}

bool* visited = new bool[MVNum];//���ʱ�־���飬���ֵΪ��false��
//�����ڽӾ����ʾͼ�����������������
void DFS_AM(AMGraph G, int v)
{//ͼGΪ�ڽӾ������ͣ��ӵ�v+1������������������������ͼG
	cout << G.vexs[v]; visited[v] = true;//���ʵ�v+1�����㣬���÷��ʱ�־�������Ӧ����ֵΪtrue
	for (int w = 0; w < G.vexnum; w++)
		if ((G.arcs[v][w] != MaxInt) && (!visited[w]))
		{//G.arcs[v][w]!=MaxInt��ʾw��v+1���ڽӵ㣬���wδ���ʣ���ݹ����DFS_AM
			cout << ",";
			DFS_AM(G, w);
		}
}

//�����ڽӱ��ʾͼ�����������������
void DFS_AL(ALGraph G, int v)
{//ͼGΪ�ڽӱ����ͣ��ӵ�v+1������������������������ͼG
	cout << G.vertices[v].data; visited[v] = true;//���ʵ�v+1�����㣬���÷��ʱ�־�������Ӧ����ֵΪtrue
	ArcNode* p = G.vertices[v].firstarc;//pָ��v+1�ı�����ĵ�һ���߽��
	int w;
	while (p != NULL)//�߽��ǿ�
	{
		w = p->adjvex;//��ʾw��v���ڽӵ�
		if (!visited[w])
		{//���wδ���ʣ���ݹ����DFS_AL
			cout << ",";
			DFS_AL(G, w);
		}
		p = p->nextarc;//pָ����һ���߽��
	}//while
}

//�����ڽӾ����ʾͼ�Ĺ��������������
void BFS_AM(AMGraph G, int v)
{//ͼGΪ�ڽӾ������ͣ��ӵ�v+1������������������������ͼG
	int* Q = new int[MVNum];//������������Q
	int front = 0, rear = 0;//front��rear�ֱ�ΪQ�Ķ�ͷ��βָ��
	cout << G.vexs[v]; visited[v] = true;//���ʵ�v+1�����㣬���÷��ʱ�־�������Ӧ����ֵΪtrue
	Q[rear++] = v;//v����
	while (front != rear)//���зǿ�
	{
		v = Q[front++];//��ͷԪ�س��ӣ�����ֵ��v
		for(int w=0;w<G.vexnum;++w)
			if ((G.arcs[v][w] != MaxInt) && (!visited[w]))
			{//G.arcs[v][w]!=MaxInt��ʾw��v+1���ڽӵ㣬���wδ���ʣ������w�����÷��ʱ�־�������Ӧ����ֵΪtrue
				cout << "," << G.vexs[w]; visited[w] = true;
				Q[rear++] = w;//w����
			}
	}
	delete[] Q;//�ͷ���ʱ���
}

//�����ڽӱ��ʾͼ�Ĺ��������������
void BFS_AL(ALGraph G, int v)
{//ͼGΪ�ڽӱ����ͣ��ӵ�v+1������������������������ͼG
	int* Q = new int[MVNum];//������������Q
	int front = 0, rear = 0;//front��rear�ֱ�ΪQ�Ķ�ͷ��βָ��
	ArcNode* p;//p����ָ��v+1�ı�����ĵ�һ���߽��
	cout << G.vertices[v].data; visited[v] = true;//���ʵ�v+1�����㣬���÷��ʱ�־�������Ӧ����ֵΪtrue
	Q[rear++] = v;//v����
	int w;
	while (front != rear)//���зǿ�
	{
		v = Q[front++];//��ͷԪ�س��ӣ�����ֵ��v
		p = G.vertices[v].firstarc;//pָ��v+1�ı�����ĵ�һ���߽��
		while (p != NULL)//�߽��ǿ�
		{
			w = p->adjvex;//��ʾw��v���ڽӵ�
			if (!visited[w])
			{//���wδ���ʣ�����w�����÷��ʱ�־�������Ӧ����ֵΪtrue
				cout << "," << G.vertices[w].data; visited[w] = true;
				Q[rear++] = w;//w����
			}
			p = p->nextarc;//pָ����һ���߽��
		}//while(p!=NULL)
	}//whlie(front!=rear)
	delete[] Q;//�ͷ���ʱ���
}

//�Ͻ�˹�����㷨
void ShortestPath_DIJ(AMGraph G, int v0)
{//��Dijkstra�㷨��������G��v0���㵽���ඥ������·��
	int n = G.vexnum;//nΪG�ж���ĸ���
	bool* S = new bool[MVNum];
	ArcType* D = new ArcType[MVNum];
	int* Path = new int[MVNum];
	int v, i, w, min;
	for (v = 0; v < n; ++v)//n���������γ�ʼ��
	{
		S[v] = false;//S��ʼΪ�ռ�
		D[v] = G.arcs[v0][v];//��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		if (D[v] != MaxInt)//���v0��v֮���л�����v��ǰ����Ϊv0
			Path[v] = v0;
		else//���v0��v֮���޻�����v��ǰ����Ϊ-1
			Path[v] = -1;
	}//for
	S[v0] = true;//��v0����S
	D[v0] = 0;//Դ�㵽Դ��ľ���Ϊ0
/*-----��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��-----*/
	
	for (i = 1; i < n; ++i)//������n-1�����㣬���ν��м���
	{
		min = MaxInt;
		for (int w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{//ѡ��һ����ǰ���·�����յ�Ϊv
				v = w;
				min = D[w];
			}//if
		S[v] = true;//��v����S
		for(w=0;w<n;++w)
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//����D[w]
				Path[w] = v;//����w��ǰ��Ϊv
			}//if
	}//for
/*---------------����Path�ж�Ӧ��ǰ����������·��---------------*/
	VerTexType vk; int k;
	int* path = new int[MVNum];//path[]���ڴ�����·�������Ľ���λ��
	while (true)
	{
		i = 0;
		cout << "�������յ�(���롮#���˳�)��";
		if ((cin >> vk)&&(vk=='#'))
			break;
		k = LocateVex(G, vk);//��ȡ�յ�vk��λ��
		if (k == -1||k==0)
		{//�ж�λ���Ƿ�Ϸ�
			cout << "�յ㲻�Ϸ������������룡" << endl;
			continue;
		}
		path[i++] = k;//��vk��λ�ô���path[]
		while (Path[k] != 0)
		{//������path[]�д�����·�������Ľ���λ��
			path[i++] = Path[k];
			k = Path[k];
		}
		cout << G.vexs[v0] << "��" << vk << "�����·��Ϊ��" << endl << G.vexs[v0];
		for (i=i-1; i >= 0; --i)//��λ�õ��������㣬��Ϊ���·��
			cout << "->" << G.vexs[path[i]];
		cout << endl;
	}
	delete[] S, D, Path, path;//ɾ����ʱ�ռ�
}


void ShowMenu()
{
	cout << "================================" << endl;
	cout << "==== 1���ڽӾ����ʾ����ͼ  ====" << endl;
	cout << "==== 2���ڽӱ��ʾ����ͼ    ====" << endl;
	cout << "==== 3������������� DFS_AM ====" << endl;
	cout << "==== 4������������� DFS_AL ====" << endl;
	cout << "==== 5������������� BFS_AM ====" << endl;
	cout << "==== 6������������� BFS_AL ====" << endl;
	cout << "==== 7���Ͻ�˹�����㷨 DIJ  ====" << endl;
	cout << "==== 0���˳�                ====" << endl;
	cout << "================================" << endl;
}

int main()
{
	AMGraph G1; ALGraph G2{};
	InitGraph(G1);//��ʼ��ͼ
	int wm = 0, end = 0, vex = 0;
	VerTexType v;
	ShowMenu();//�˵�
	while (true)
	{
		cout << "������������룺";
		if (!(cin >> wm))//��������ʱ�������룬��ֹ��ѭ��
		{
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}
		//1 2 5 1 3 3 2 4 1 2 5 3 2 6 6 3 5 8 3 6 7 4 7 3 5 7 5 5 8 2 6 7 6 6 8 6 7 9 4 8 9 3
		switch (wm)
		{
		case 1://�ڽӾ����ʾ����ͼ
			if (CreateUDN(G1))
				cout << "�����ɹ���" << endl;
			else
				cout << "����ʧ�ܣ�" << endl;
			break;
		case 2://�ڽӱ��ʾ����ͼ
			if (CreateUDG(G2))
				cout << "�����ɹ���" << endl;
			else
				cout << "����ʧ�ܣ�" << endl;
			break;
		case 3://����������� DFS_AM
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{//������δ����ʱ��ֹ����
				cout << "����ʧ�ܣ�������δ������" << endl;
				break;
			}
			for (int i = 0; i < G1.vexnum; ++i)//���ʱ�־�����ʼ��
				visited[i] = false;
			cout << "��������ʼ�����λ�ã�";
			if ((cin >> vex) && (vex <= 0 || vex > G1.vexnum))
			{//�ж���ʼ����λ���Ƿ�Ϸ�
				cout << "λ�ò��Ϸ���" << endl;
				break;
			}
			cout << "�������Ϊ��" << endl;
			DFS_AM(G1, vex - 1);
			cout<<endl;
			break;
		case 4://����������� DFS_AL
			if (G2.vexnum == 0 || G2.arcnum == 0)
			{//������δ����ʱ��ֹ����
				cout << "����ʧ�ܣ�������δ������" << endl;
				break;
			}
			for (int i = 0; i < G2.vexnum; ++i)//���ʱ�־�����ʼ��
				visited[i] = false;
			cout << "��������ʼ�����λ�ã�";
			if ((cin >> vex) && (vex <= 0 || vex > G2.vexnum))
			{//�ж���ʼ����λ���Ƿ�Ϸ�
				cout << "λ�ò��Ϸ���" << endl;
				break;
			}
			cout << "�������Ϊ��" << endl;
			DFS_AL(G2, vex - 1);
			cout << endl;
			break;
		case 5://����������� BFS_AM
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{//������δ����ʱ��ֹ����
				cout << "����ʧ�ܣ�������δ������" << endl;
				break;
			}
			for (int i = 0; i < G1.vexnum; ++i)//���ʱ�־�����ʼ��
				visited[i] = false;
			cout << "��������ʼ�����λ�ã�";
			if ((cin >> vex) && (vex <= 0 || vex > G1.vexnum))
			{//�ж���ʼ����λ���Ƿ�Ϸ�
				cout << "λ�ò��Ϸ���" << endl;
				break;
			}
			cout << "�������Ϊ��" << endl;
			BFS_AM(G1, vex - 1);
			cout << endl;
			break;
		case 6://����������� BFS_AL
			if (G2.vexnum == 0 || G2.arcnum == 0)
			{//������δ����ʱ��ֹ����
				cout << "����ʧ�ܣ�������δ������" << endl;
				break;
			}
			for (int i = 0; i < G2.vexnum; ++i)//���ʱ�־�����ʼ��
				visited[i] = false;
			cout << "��������ʼ�����λ�ã�";
			if ((cin >> vex) && (vex <= 0 || vex > G2.vexnum))
			{//�ж���ʼ����λ���Ƿ�Ϸ�
				cout << "λ�ò��Ϸ���" << endl;
				break;
			}
			cout << "�������Ϊ��" << endl;
			BFS_AL(G2, vex - 1);
			cout << endl;
			break;
		case 7://�Ͻ�˹�����㷨 DIJ
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{
				cout << "ͼδ������" << endl;
				break;
			}
			cout << "��������ʼ�㣺";
			cin >> v;
			ShortestPath_DIJ(G1, LocateVex(G1, v));//����ShortestPath_DIJ()������LocateVex()Ϊ��ʼ���λ��
			break;
		case 0:
			cout << "ȷ��Ҫ�˳���\n������1��ȷ���˳�������������ȡ����" << endl;
			cin >> end;
			if (end == 1)
			{
				cout << "��ӭ�´�ʹ�ã�" << endl;
				return 0;
			}
			break;
		default:
			cout << "��������ȷ�Ĳ�������!" << endl;
			break;
		}
	}
	return 0;
}