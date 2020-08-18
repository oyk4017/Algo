#include <iostream>
#include <vector>

#define MAX 12
using namespace std;

int N =0;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int test=0;
int map[MAX][MAX]={0,};
int dir[MAX]={0,};
int MIN;
int core_num;
vector <pair<int,int>> core;

void solve()
{
    int total=0;
    int len =0;
    int num=0;
    int tmp[MAX][MAX]={0,};
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) tmp[i][j]=map[i][j];
    }
    
    for(int i=0;i<core.size();i++)
    {
        int x= core[i].first;
        int y= core[i].second;
        int d = dir[i];
        len=0;
        
        while(1){
            x += dx[d];
            y += dy[d];
            
            if ( x < 0 || y < 0 || x >= N || y >= N){
                total += len;
                num++;
                break;

            }
            if ( tmp[x][y]==1)  break ;
            
            tmp[x][y]=1;
            len++;
        }
        
    }
    if(num > core_num ) {
        MIN = total;
        core_num = num;
    }
        
    else if (num == core_num){
        if( MIN > total){
            MIN = total;
            core_num = num;
        }
    }
    return ;
}

void DFS(int cnt)
{
    if(cnt == core.size())
    {
        solve();
        return;
    }
    
    for(int i=0;i<4;i++){
        int x = core[cnt].first;
        int y = core[cnt].second;
        
        if(map[x+dx[i]][y+dy[i]]==1)    continue;
        
        dir[cnt] = i;
        DFS(cnt+1);
        dir[cnt] = 0;
        
    }
}

int main(void)
{
    int T;
    
    cin >> T;
    for(int k=0;k<T;k++){
        
        cin >> N;
        core.clear();
        MIN=987654321;
        core_num=0;
        
        test=k+1;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cin >> map[i][j];
                if(map[i][j]==1 && i !=0 && j!=0 && i != N-1 && j!= N-1)
                    core.push_back(make_pair(i,j));
            }
        }
        
        DFS(0);
        cout << "#" << k+1 << " " << MIN<<"\n";

    }
    return 0;
    
}
