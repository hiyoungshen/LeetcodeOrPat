/*
* Prim 求MST
* 耗费矩阵cost[][]，标号从0 开始，0∼n-1
* 返回最小生成树的权值，返回-1 表示原图不连通
*/

const int INF=0x3f3f3f3f;
const int MAXN=110;

bool vis[MAXN];
int lowc[MAXN];

// calculate the minimum cost of minimum spanning tree
int Prim(int cost[][MAXN],int n){
	// the minimum cost of minimum spanning tree
	int ans=0;
	memset(vis,false,sizeof(vis));
	// vertex 0 is set to root
	vis[0]=true;
	// initialize
	for(int i=1;i<n;i++){
		lowc[i]=cost[0][i];
	}
	// n-1 loops
	for(int i=1;i<n;i++){
		int minc=INF;
		int p=−1;
		// 
		for(int j=0;j<n;j++){
			if(!vis[j]&&minc>lowc[j]){
				minc=lowc[j];
				p=j;
			}
		}
		if(minc==INF){
			return −1;//原图不连通
		}
		ans+=minc;
		vis[p]=true;
		// the differences between prime and dijkstra is that they updated in different ways
		for(int j=0;j<n;j++){
			if(!vis[j]&&lowc[j]>cost[p][j]){
				lowc[j]=cost[p][j];
			}
		}
	}
	return ans;
}