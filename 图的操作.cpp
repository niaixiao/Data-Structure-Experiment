#include<iostream>
using namespace std;

#define MaxInt 32767//表示极大值
#define MVNum 100//最大顶点数
#define OK 1
#define ERROR 0
typedef char VerTexType;//假设顶点的数据类型为字符型
typedef int ArcType;//假设边的权值类型为整形
typedef int OtherInfo;
typedef int Status;

//-----图的邻接矩阵储存表示-----
typedef struct
{
	VerTexType* vexs;//顶点表
	ArcType** arcs;//邻接矩阵
	int vexnum, arcnum;//图的当前点数和边数
}AMGraph;

//-----图的邻接表储存表示-----
typedef struct ArcNode//边结点
{
	int adjvex;//该边所指向的顶点的位置
	struct ArcNode* nextarc;//指向下一条边的指针
	OtherInfo info;//和边相关的信息
}ArcNode;
typedef struct VNode//顶点信息
{
	VerTexType data;
	ArcNode* firstarc;//指向第一条依附顶点的边的指针
}VNode, AdjList[MVNum];//AdjList表示邻接表类型
typedef struct//邻接表
{
	AdjList vertices;
	int vexnum, arcnum;//图的当前顶点数的边数
}ALGraph;

//图的初始化
Status InitGraph(AMGraph& G)
{//采用邻接矩阵表示的图的初始化
	G.vexs = new VerTexType[MVNum];
	G.arcs = new ArcType * [MVNum];
	for (int i = 0; i < MVNum; i++)
		G.arcs[i] = new int[MVNum];
	G.vexnum = 0; G.arcnum = 0;
	return OK;
}

//查找元素u在图中的位置
int LocateVex(AMGraph G, VerTexType u)
{
	if (G.vexnum == 0)//顶点数为0时返回-1
		return -1;
	for (int i = 0; i < G.vexnum; ++i)
		if (u == G.vexs[i])//遍历顶点表，如果u在顶点中返回其下标，否则返回-1
			return i;
	return -1;
}
int LocateVex(ALGraph G, VerTexType u)
{
	if (G.vexnum == 0)//顶点数为0时返回-1
		return -1;
	for (int i = 0; i < G.vexnum; ++i)
		if (u == G.vertices[i].data)//遍历顶点表，如果u在顶点中返回其下标，否则返回-1
			return i;
	return -1;
}

//邻接矩阵表示法创建无向网
Status CreateUDN(AMGraph& G)
{//采用邻接矩阵表示法，创建无向网G
	cout << "请输入总顶点数和总边数：";
	if (!(cin >> G.vexnum >> G.arcnum))//输入总顶点数，总边数
		return ERROR;
	int i, j, k;
	cout << "请输入各点的信息：";
	for (i = 0; i < G.vexnum; ++i)//依次输入点的信息
		cin >> G.vexs[i];
	for (i = 0; i < G.vexnum; ++i)//初始化邻接矩阵，边的权值均置为极大值MaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;
	VerTexType v1, v2; ArcType w;
	cout << "输入一条边依附的顶点及权值：";
	for (k = 0; k < G.arcnum; ++k)//构造邻接矩阵
	{
		cin >> v1 >> v2 >> w;//输入一条边依附的顶点及权值
		i = LocateVex(G, v1); j = LocateVex(G, v2);//确定v1和v2在G中的位置，即顶点数组的下标
		G.arcs[i][j] = w;//边<v1,v2>的权值置为w
		G.arcs[j][i] = G.arcs[i][j];//置<v1,v2>的对称边<v2,v1>的权值为w
	}
	return OK;
}

//采用邻接表表示法创建无向网
Status CreateUDG(ALGraph& G)
{//采用邻接表表示法，创建无向网G
	cout << "请输入总顶点数和总边数：";
	if (!(cin >> G.vexnum >> G.arcnum))//输入总顶点数，总边数
		return ERROR;
	int i, j, k;
	cout << "请输入各点的信息：";
	for (i = 0; i < G.vexnum; ++i)
	{
		cin >> G.vertices[i].data;//输入顶点值
		G.vertices[i].firstarc = NULL;//初始化表头结点的指针域为NULL
	}
	VerTexType v1, v2; ArcType w;
	cout << "输入一条边依附的顶点及权值：";
	for (k = 0; k < G.arcnum; ++k)//输入各边，构造邻接表
	{
		cin >> v1 >> v2 >> w;//输入一条边依附的两个顶点及权值
		i = LocateVex(G, v1); j = LocateVex(G, v2);//确定v1和v2在G中的位置，即顶点在G.vertices中的序号
		ArcNode* p1 = new ArcNode;//生成一个新的边结点*p1
		p1->adjvex = j;//邻接点序号为j
		p1->info = w;//边的权值为w
		p1->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p1;//将新结点*p1插入顶点vi的边表头部
		ArcNode* p2 = new ArcNode;//生成另一个对称的边结点*p2
		p2->adjvex = i;//邻接点序号为i
		p2->info = w;//边的权值为w
		p2->nextarc = G.vertices[j].firstarc; G.vertices[j].firstarc = p2;//将新结点*p2插入顶点vj的边表头部
	}
	return OK;
}

bool* visited = new bool[MVNum];//访问标志数组，其初值为“false”
//采用邻接矩阵表示图的深度优先搜索遍历
void DFS_AM(AMGraph G, int v)
{//图G为邻接矩阵类型，从第v+1个顶点出发深度优先搜索遍历图G
	cout << G.vexs[v]; visited[v] = true;//访问第v+1个顶点，并置访问标志数组的相应分量值为true
	for (int w = 0; w < G.vexnum; w++)
		if ((G.arcs[v][w] != MaxInt) && (!visited[w]))
		{//G.arcs[v][w]!=MaxInt表示w是v+1的邻接点，如果w未访问，则递归调用DFS_AM
			cout << ",";
			DFS_AM(G, w);
		}
}

//采用邻接表表示图的深度优先搜索遍历
void DFS_AL(ALGraph G, int v)
{//图G为邻接表类型，从第v+1个顶点出发深度优先搜索遍历图G
	cout << G.vertices[v].data; visited[v] = true;//访问第v+1个顶点，并置访问标志数组的相应分量值为true
	ArcNode* p = G.vertices[v].firstarc;//p指向v+1的边链表的第一个边结点
	int w;
	while (p != NULL)//边结点非空
	{
		w = p->adjvex;//表示w是v的邻接点
		if (!visited[w])
		{//如果w未访问，则递归调用DFS_AL
			cout << ",";
			DFS_AL(G, w);
		}
		p = p->nextarc;//p指向下一个边结点
	}//while
}

//采用邻接矩阵表示图的广度优先搜索遍历
void BFS_AM(AMGraph G, int v)
{//图G为邻接矩阵类型，从第v+1个顶点出发广度优先搜索遍历图G
	int* Q = new int[MVNum];//创建辅助队列Q
	int front = 0, rear = 0;//front、rear分别为Q的队头队尾指针
	cout << G.vexs[v]; visited[v] = true;//访问第v+1个顶点，并置访问标志数组的相应分量值为true
	Q[rear++] = v;//v进队
	while (front != rear)//队列非空
	{
		v = Q[front++];//队头元素出队，并赋值给v
		for(int w=0;w<G.vexnum;++w)
			if ((G.arcs[v][w] != MaxInt) && (!visited[w]))
			{//G.arcs[v][w]!=MaxInt表示w是v+1的邻接点，如果w未访问，则访问w，并置访问标志数组的相应分量值为true
				cout << "," << G.vexs[w]; visited[w] = true;
				Q[rear++] = w;//w进队
			}
	}
	delete[] Q;//释放临时结点
}

//采用邻接表表示图的广度优先搜索遍历
void BFS_AL(ALGraph G, int v)
{//图G为邻接表类型，从第v+1个顶点出发广度优先搜索遍历图G
	int* Q = new int[MVNum];//创建辅助队列Q
	int front = 0, rear = 0;//front、rear分别为Q的队头队尾指针
	ArcNode* p;//p用于指向v+1的边链表的第一个边结点
	cout << G.vertices[v].data; visited[v] = true;//访问第v+1个顶点，并置访问标志数组的相应分量值为true
	Q[rear++] = v;//v进队
	int w;
	while (front != rear)//队列非空
	{
		v = Q[front++];//队头元素出队，并赋值给v
		p = G.vertices[v].firstarc;//p指向v+1的边链表的第一个边结点
		while (p != NULL)//边结点非空
		{
			w = p->adjvex;//表示w是v的邻接点
			if (!visited[w])
			{//如果w未访问，访问w，并置访问标志数组的相应分量值为true
				cout << "," << G.vertices[w].data; visited[w] = true;
				Q[rear++] = w;//w进队
			}
			p = p->nextarc;//p指向下一个边结点
		}//while(p!=NULL)
	}//whlie(front!=rear)
	delete[] Q;//释放临时结点
}

//迪杰斯特拉算法
void ShortestPath_DIJ(AMGraph G, int v0)
{//用Dijkstra算法求有向网G的v0顶点到其余顶点的最短路径
	int n = G.vexnum;//n为G中顶点的个数
	bool* S = new bool[MVNum];
	ArcType* D = new ArcType[MVNum];
	int* Path = new int[MVNum];
	int v, i, w, min;
	for (v = 0; v < n; ++v)//n个顶点依次初始化
	{
		S[v] = false;//S初始为空集
		D[v] = G.arcs[v0][v];//将v0到各个终点的最短路径长度初始化为弧上的权值
		if (D[v] != MaxInt)//如果v0和v之间有弧，则将v的前驱置为v0
			Path[v] = v0;
		else//如果v0和v之间无弧，则将v的前驱置为-1
			Path[v] = -1;
	}//for
	S[v0] = true;//将v0加入S
	D[v0] = 0;//源点到源点的距离为0
/*-----初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集-----*/
	
	for (i = 1; i < n; ++i)//对其余n-1个顶点，依次进行计算
	{
		min = MaxInt;
		for (int w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{//选择一条当前最短路径，终点为v
				v = w;
				min = D[w];
			}//if
		S[v] = true;//将v加入S
		for(w=0;w<n;++w)
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//更新D[w]
				Path[w] = v;//更改w的前驱为v
			}//if
	}//for
/*---------------利用Path中对应的前驱，求得最短路径---------------*/
	VerTexType vk; int k;
	int* path = new int[MVNum];//path[]用于存放最短路径经过的结点的位置
	while (true)
	{
		i = 0;
		cout << "请输入终点(输入‘#’退出)：";
		if ((cin >> vk)&&(vk=='#'))
			break;
		k = LocateVex(G, vk);//获取终点vk的位置
		if (k == -1||k==0)
		{//判断位置是否合法
			cout << "终点不合法，请重新输入！" << endl;
			continue;
		}
		path[i++] = k;//将vk的位置存入path[]
		while (Path[k] != 0)
		{//依次在path[]中存放最短路径经过的结点的位置
			path[i++] = Path[k];
			k = Path[k];
		}
		cout << G.vexs[v0] << "到" << vk << "的最短路径为：" << endl << G.vexs[v0];
		for (i=i-1; i >= 0; --i)//按位置倒序输出结点，即为最短路径
			cout << "->" << G.vexs[path[i]];
		cout << endl;
	}
	delete[] S, D, Path, path;//删除临时空间
}


void ShowMenu()
{
	cout << "================================" << endl;
	cout << "==== 1、邻接矩阵表示法建图  ====" << endl;
	cout << "==== 2、邻接表表示法建图    ====" << endl;
	cout << "==== 3、深度优先搜索 DFS_AM ====" << endl;
	cout << "==== 4、深度优先搜索 DFS_AL ====" << endl;
	cout << "==== 5、广度优先搜索 BFS_AM ====" << endl;
	cout << "==== 6、广度优先搜索 BFS_AL ====" << endl;
	cout << "==== 7、迪杰斯特拉算法 DIJ  ====" << endl;
	cout << "==== 0、退出                ====" << endl;
	cout << "================================" << endl;
}

int main()
{
	AMGraph G1; ALGraph G2{};
	InitGraph(G1);//初始化图
	int wm = 0, end = 0, vex = 0;
	VerTexType v;
	ShowMenu();//菜单
	while (true)
	{
		cout << "请输入操作代码：";
		if (!(cin >> wm))//错误输入时重新输入，防止死循环
		{
			cin.clear();
			cin.ignore(1024, '\n');
			wm = -1;
		}
		//1 2 5 1 3 3 2 4 1 2 5 3 2 6 6 3 5 8 3 6 7 4 7 3 5 7 5 5 8 2 6 7 6 6 8 6 7 9 4 8 9 3
		switch (wm)
		{
		case 1://邻接矩阵表示法建图
			if (CreateUDN(G1))
				cout << "创建成功！" << endl;
			else
				cout << "创建失败！" << endl;
			break;
		case 2://邻接表表示法建图
			if (CreateUDG(G2))
				cout << "创建成功！" << endl;
			else
				cout << "创建失败！" << endl;
			break;
		case 3://深度优先搜索 DFS_AM
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{//无向网未创建时终止操作
				cout << "操作失败！无向网未创建！" << endl;
				break;
			}
			for (int i = 0; i < G1.vexnum; ++i)//访问标志数组初始化
				visited[i] = false;
			cout << "请输入起始顶点的位置：";
			if ((cin >> vex) && (vex <= 0 || vex > G1.vexnum))
			{//判断起始顶点位置是否合法
				cout << "位置不合法！" << endl;
				break;
			}
			cout << "遍历结果为：" << endl;
			DFS_AM(G1, vex - 1);
			cout<<endl;
			break;
		case 4://深度优先搜索 DFS_AL
			if (G2.vexnum == 0 || G2.arcnum == 0)
			{//无向网未创建时终止操作
				cout << "操作失败！无向网未创建！" << endl;
				break;
			}
			for (int i = 0; i < G2.vexnum; ++i)//访问标志数组初始化
				visited[i] = false;
			cout << "请输入起始顶点的位置：";
			if ((cin >> vex) && (vex <= 0 || vex > G2.vexnum))
			{//判断起始顶点位置是否合法
				cout << "位置不合法！" << endl;
				break;
			}
			cout << "遍历结果为：" << endl;
			DFS_AL(G2, vex - 1);
			cout << endl;
			break;
		case 5://广度优先搜索 BFS_AM
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{//无向网未创建时终止操作
				cout << "操作失败！无向网未创建！" << endl;
				break;
			}
			for (int i = 0; i < G1.vexnum; ++i)//访问标志数组初始化
				visited[i] = false;
			cout << "请输入起始顶点的位置：";
			if ((cin >> vex) && (vex <= 0 || vex > G1.vexnum))
			{//判断起始顶点位置是否合法
				cout << "位置不合法！" << endl;
				break;
			}
			cout << "遍历结果为：" << endl;
			BFS_AM(G1, vex - 1);
			cout << endl;
			break;
		case 6://广度优先搜索 BFS_AL
			if (G2.vexnum == 0 || G2.arcnum == 0)
			{//无向网未创建时终止操作
				cout << "操作失败！无向网未创建！" << endl;
				break;
			}
			for (int i = 0; i < G2.vexnum; ++i)//访问标志数组初始化
				visited[i] = false;
			cout << "请输入起始顶点的位置：";
			if ((cin >> vex) && (vex <= 0 || vex > G2.vexnum))
			{//判断起始顶点位置是否合法
				cout << "位置不合法！" << endl;
				break;
			}
			cout << "遍历结果为：" << endl;
			BFS_AL(G2, vex - 1);
			cout << endl;
			break;
		case 7://迪杰斯特拉算法 DIJ
			if (G1.vexnum == 0 || G1.arcnum == 0)
			{
				cout << "图未创建！" << endl;
				break;
			}
			cout << "请输入起始点：";
			cin >> v;
			ShortestPath_DIJ(G1, LocateVex(G1, v));//调用ShortestPath_DIJ()函数，LocateVex()为起始点的位置
			break;
		case 0:
			cout << "确定要退出吗？\n（按‘1’确认退出，‘其他键’取消）" << endl;
			cin >> end;
			if (end == 1)
			{
				cout << "欢迎下次使用！" << endl;
				return 0;
			}
			break;
		default:
			cout << "请输入正确的操作代码!" << endl;
			break;
		}
	}
	return 0;
}