#pragma warning(disable:4996)
#include <cstdio>
#include <cstring>
#include <queue>
#include<iostream>
#include <algorithm>
#include<queue>
using namespace std;

const int maxn = 1005;
const int maxm = 1000005;

struct Edge {
	int to, cost;
	int next;
	Edge(int to_ = 0, int cost_ = 0, int next_ = 0) :to(to_), cost(cost_), next(next_) {}
};
Edge edge[maxm * 2 + 100];
int cnt = 0;
int head[maxn];
bool vis[maxn];//判断顶点i是否在队列中
int times[maxn];
int dist[maxn];
bool spfa(int start, int n) {
	memset(times, 0, sizeof(times));
	memset(vis, false, sizeof(vis));
	memset(dist, 0x3f, sizeof(dist));
	vis[start] = true;
	dist[start] = 0;
	queue<int>q;
	while (!q.empty()) {
		q.pop();
	}
	q.push(start);
	times[start] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].to;
			int cost = edge[i].cost;
			if (dist[v] > dist[u] + cost) {
				dist[v] = dist[u] + cost;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
					if (++times[v] > n + 1) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void addEdge(int u_, int v_, int cost_) {
	edge[cnt].to = v_, edge[cnt].cost = cost_;
	edge[cnt].next = head[u_];
	head[u_] = cnt++;
}

//设最北方有一个零点, dist[i]代表其到顶点i的距离
//dist[i] + cost == dist[j], 两个条件
	//dist[j]-dist[i]<=cost, 顶点i指向顶点j的一条边, 权值为cost
	//dist[j]-dist[i]>=cost, 即dist[i]-dist[j]<=-cost, 顶点j指向顶点i的一条边, 权值为-cost
//dist[i]+1<=dist[j], 即dist[i]-dist[j]<=-1, 顶点j指向i的一条权值为-1的边

int n, m;
int main() {
	while (cin >> n >> m) {
		memset(head, 0xff, sizeof(head));
		cnt = 0;
		char c[5];
		int a, b;
		int cost;
		for (int i = 0; i < m; i++) {
			getchar();
			scanf("%s", c);
			if (c[0] == 'P') {
				scanf("%d%d%d", &a, &b, &cost);
				addEdge(a, b, cost);
				addEdge(b, a, -cost);
			}
			else {
				scanf("%d%d", &a, &b);
				addEdge(b, a, -1);
			}
		}
		//一个超级源点和所有点都有连接, 权值为0
		for (int i = 1; i <= n; i++) {
			addEdge(0, i, 0);
		}
		if (spfa(0, n + 1) == true) {
			cout << "Reliable" << "\n";
		}
		else {
			cout << "Unreliable\n";
		}
	}

}
/*
3 4
P 1 2 1
P 2 3 1
V 1 3
P 1 3 1
5 5
V 1 2
V 2 3
V 3 4
V 4 5
V 3 5
*/