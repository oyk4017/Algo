#include <iostream>
#include <queue>

#define MAX 101

using namespace std;

int N,T;

int map[MAX][MAX]={0,};
long long tm[MAX][MAX]={0,};

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

    
struct pos{
    int x,y;
};

void BFS()
{
    queue <pos> q;
    
    q.push({0,0});
    
    
    while(!q.empty()){
        
        int x= q.front().x;
        int y= q.front().y;
        
        q.pop();
        
        if(x == N-1 && y == N-1 )   break;
        
        for(int i=0;i<4;i++){
            
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if( nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if( tm[nx][ny] != 0 && tm[nx][ny] < tm[x][y]+map[nx][ny])    continue;
            if(nx == 0 && ny ==0 )  continue;
            
            q.push({nx,ny});
            tm[nx][ny]=tm[x][y]+map[nx][ny];
        }
    }
}

int main(void)
{
    cin >> T;
    for(int k=0;k<T;k++){
        cin >> N;
        
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                scanf("%1d",&map[i][j]);
                tm[i][j]=0;
            }
        }
        
        BFS();
        cout << "#" << k+1 << " " << tm[N-1][N-1] << "\n";
    }
    
    return 0;
}

