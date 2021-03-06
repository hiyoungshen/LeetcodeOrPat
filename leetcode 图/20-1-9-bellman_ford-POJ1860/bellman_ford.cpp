//单源最短路径的bellman_ford算法, 复杂度O(VE)
//可以处理负权边图
//可以判断是否存在负环回路, 返回truem, 当且仅当图中不包含从源点可达的负权回路
//vector<Edge>E; 先E.clear() 初始化，然后加入所有边
//点的编号从1 开始(从0 开始简单修改就可以了)

const int INF=0x3f3f3f3f;
//顶点的数量
const int MAXN=550;
//顶点start到其他所有顶点的最短路径
int dist[MAXN];

struct Edge{
    int u,v;
    int cost;
    Edge(int _u=0,int _v=0,int _cost=0):u(_u),v(_v),cost(_cost){}
};
vector<Edge>E;
//点的编号从1开始
//顶点start到其他所有顶点的最短路径, 顶点的数量为n
bool bellman_ford(int start,int n){
    //dist初始化
    for(int i=1;i<=n;i++)
        dist[i]=INF;
    dist[start]=0;
    //最多做n-1次
    for(int i=1;i<n;i++){
        bool flag=false;
        //遍历所有的边进行松弛计算
        for(int j=0;j<E.size();j++){
            int u=E[j].u;
            int v=E[j].v;
            int cost=E[j].cost;
            if(dist[v]>dist[u]+cost){
                dist[v]=dist[u]+cost;
                flag=true;
            }
        }
        //这一遍松弛没有任何更新, 说明start点为源点的最短路求解完毕
        if(!flag)
            return true;//没有负环回路
    }
    //如果经过n-1次松弛后，还能继续松弛，说明有负权回路存在，
    //如果n-1次松弛后，如果有边（u，v）满足d[v]>d[u]+w[u][v]，
    //      说明还能继续松弛，存在负权回路。
    for(int j=0;j<E.size();j++)
        if(dist[E[j].v]>dist[E[j].u]+E[j].cost)
            return false;//有负环回路
    return true;//没有负环回路
}