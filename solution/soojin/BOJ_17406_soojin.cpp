#include <iostream>
#include <vector>

#define MAX 51

using namespace std;

int tmp[MAX][MAX];
int map[MAX][MAX];
int visited[6]={0,};
int N,M,K;
int MIN = 1e9;

int oper[6][3]={0,};
int r,c,s;

vector <int> order;

void move()
{
    for(int i=1;i<=s;i++){
        
        int tmp1 = tmp[r-i][c-i];
        int tmp2 = tmp[r-i][c+i];
        int tmp3 = tmp[r+i][c-i];
        int tmp4 = tmp[r+i][c+i];
        
        for(int j=0;j<2*i-1;j++){
            tmp[r-i][c+i-j] = tmp[r-i][c+i-1-j];
            tmp[r+i-j][c+i] = tmp[r+i-j-1][c+i];
            tmp[r+i][c-i+j] = tmp[r+i][c-i+j+1];
            tmp[r-i+j][c-i] = tmp[r-i+j+1][c-i];
        }
        
        tmp[r-i][c-i+1] = tmp1;
        tmp[r-i+1][c+i] = tmp2;
        tmp[r+i-1][c-i] = tmp3;
        tmp[r+i][c+i-1] = tmp4;
        
    }
}

int solve()
{
    for(int i=1 ;i<=N;i++){
        for(int j=1;j<=M;j++)   tmp[i][j] = map[i][j];
    }

    
    for(int i=0;i<K;i++)
    {
        int idx = order[i];
        
        r= oper[idx][0];
        c= oper[idx][1];
        s= oper[idx][2];
        
        move();
        
    }
    
    int min=1e9;
    
    for(int i=1;i<=N;i++){
        int sum =0;
        for(int j=1;j<=M;j++)  {
            sum+= tmp[i][j];
        }
        if(sum < min)   min = sum;
    }

    return min;
}


void DFS(int cnt)
{
    if(cnt == K ){
        int res = solve();
        if(res < MIN)   MIN = res;
        return ;
    }
    
    
    for(int i=0;i<K;i++)
    {
        if(!visited[i]){
            order.push_back(i);
            visited[i] =1;
            DFS(cnt+1);
            visited[i]=0;
            order.pop_back();
        }
    }
}

int main(void)
{
    cin >> N >> M >> K;
    for(int i=1 ;i<=N;i++){
        for(int j=1;j<=M;j++)   cin >> map[i][j];
    }
    
    for(int i=0;i<K;i++){
        cin >> r >> c >> s;
        
        oper[i][0] = r;
        oper[i][1] = c;
        oper[i][2] = s;
        
    }
    
    DFS(0);
    
    cout <<  MIN;
    return 0;
    
}


