#pragma warning(disable:4996)
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

/*
* 单源最短路SPFA
* 时间复杂度0(kE)
* 这个是队列实现，有时候改成栈实现会更加快，很容易修改
* 这个复杂度是不定的
*/
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v;
    int cost;
    Edge(int _v = 0, int _cost = 0) :v(_v), cost(_cost) {}
};
//邻接表存储每一个顶点的临界点
vector<Edge>E[MAXN];

void addedge(int u, int v, int w) {
    E[u].push_back(Edge(v, w));
}

bool vis[MAXN];//在队列标志
int cnt[MAXN];//每个点的入队列次数
int dist[MAXN];
bool SPFA(int start, int n) {
    memset(vis, false, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    //初始化
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    vis[start] = true;
    dist[start] = 0;
    queue<int>que;
    while (!que.empty())
        que.pop();
    que.push(start);
    memset(cnt, 0, sizeof(cnt));
    cnt[start] = 1;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        //扫描顶点u的所有临接点
        for (int i = 0; i < E[u].size(); i++) {
            int v = E[u][i].v;
            if (dist[v] > dist[u] + E[u][i].cost) {
                dist[v] = dist[u] + E[u][i].cost;
                //如果该顶点没有入队, 将其入队
                if (!vis[v]) {
                    vis[v] = true;
                    que.push(v);
                    if (++cnt[v] > n)
                        return false;
                    //因为存在负权边, 所以这个点会一直进行松弛
                    //cnt[i] 为入队列次数，用来判定是否存在负环回路
                }
            }
        }
    }
    return true;
}


int main() {
    int f, n, m, w;
    cin >> f;
    while (f--) {
        scanf("%d%d%d", &n, &m, &w);
        int u, v, ww;
        for (int i = 1; i <= n; i++) {
            E[i].clear();
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &ww);
            addedge(u, v, ww);
            addedge(v, u, ww);
        }
        for (int i = 0; i < w; i++) {
            scanf("%d%d%d", &u, &v, &ww);
            addedge(u, v, -ww);
        }
        int flag = SPFA(1, n);

        if (flag) {
            cout << "NO" << "\n";
        }
        else {
            cout << "YES" << "\n";
        }
    }
}