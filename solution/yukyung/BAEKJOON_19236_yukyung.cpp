#include <iostream>
using namespace std;

typedef struct Fish{//물고기 구조체 좌표값, 방향값, 생존여부 저장
    int x;
    int y;
    int dir;
    bool dead;
}Fish;

Fish fish[17];//16개의 물고기 구조체 변수 선언
int map[4][4];

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
//int movx, movy;

int _max = 0;

void move_fish(){
    for(int k = 1 ; k<=16;k++){
        if(fish[k].dead){//물고기가 죽었으면 패스
            continue;
        }
        
        //이동방향 설정
        int d = fish[k].dir;
        int go_x = fish[k].x + dx[d-1];
        int go_y = fish[k].y + dy[d-1];
        
        int n=0;
        
        //이동방향에 상어가 있거나 벽일때 방향 전환
        while(map[go_x][go_y]==-1|| go_x < 0 || go_y < 0 || go_x >= 4 || go_y >= 4){
            
            if(n==8){
                break;
            }
            
            if(d==8){
                d = 1;
            }else{
                d += 1;
            }
            
            //이동방향 재설정
            go_x = fish[k].x + dx[d-1];
            go_y = fish[k].y + dy[d-1];
            n++;
        }
        
        if(n==8){
            continue;
        }
        
        //이동방향이 빈칸이면 이동만
        if(map[go_x][go_y]==0){
            map[fish[k].x][fish[k].y] = 0;//이동한 자리 초기화
            map[go_x][go_y] = k;//물고기 인덱스 이동
            fish[k].x = go_x;
            fish[k].y = go_y;
            fish[k].dir = d;
            
        }else{//물고기 있으면 자리 교환
            int go_idx = map[go_x][go_y];//이동할 곳의 인덱스 저장
            
            fish[0].x = fish[k].x; //0번은 임시보관함
            fish[0].y = fish[k].y;
            fish[0].dir = fish[k].dir;
            
            fish[k].x = go_x;
            fish[k].y = go_y;
            fish[k].dir = d;
            map[fish[k].x][fish[k].y] = k;
            
            fish[go_idx].x = fish[0].x;
            fish[go_idx].y = fish[0].y;
            map[fish[go_idx].x][fish[go_idx].y] = go_idx;
            
            
        }
    }
}

void DFS(int x, int y, int dir, int sum){
    
    int movx, movy;
    movx = x + dx[dir-1]; //다음 좌표
    movy = y + dy[dir-1];
    
    //상어가 탈출하는 경우 : 다음 이동에 물고기 없거나 이동 불가능일때
    if(_max<sum){
        _max = sum;
    }
    
    Fish copy_fish[17];
    int copy_map[4][4];
    
    //물고기 이동 전 맵과 구조체 복사
    for(int i = 1; i<=16; i++){
        copy_fish[i] = fish[i];//구조체 통째로 복사됨
        //copy_fish[idx].x = fish[idx].x;
        //copy_fish[idx].y = fish[idx].y;
        //copy_fish[idx].dir = fish[idx].dir;
        //copy_fish[idx].dead = fish[idx].dead;
    }
    
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            int idx = map[i][j];
            copy_map[i][j] = idx;
        }
    }
    
    //물고기 이동
    move_fish();
    
    //상어이동
    for(int k = 1; k<=3; k++){
        movx = x + dx[dir-1]*k;
        movy = y + dy[dir-1]*k;
        
        if(map[movx][movy]==0 || movx<0 || movy <0 || movx>=4 || movy>=4){

            continue;
        }
        
        int num = map[movx][movy];//이동할 곳의 인덱스를 sum에 합친다
        
        int reset1 = map[x][y];//현재 위치 인덱스 저장
        int reset2 = map[movx][movy];//이동할 곳의 인덱스를 저장
        
        map[x][y] = 0; //현재 물고기는 먹혔으니까 0으로 초기화
        fish[reset2].dead = true;//먹힐 물고기 뒈짐
        map[movx][movy] = -1;//이동할 상어의 위치 -1로 초기화
        
        DFS(movx, movy, fish[reset2].dir, sum+num);//DFS
        
        map[x][y] = reset1;
        map[movx][movy] = reset2;//백트래킹
        fish[reset2].dead = false;

    }
    
    for(int i=1; i<=16; i++){
        fish[i] = copy_fish[i];//구조체 전체 복사
        //fish[idx].x = copy_fish[idx].x;
        //fish[idx].y = copy_fish[idx].y;
        //fish[idx].dir = copy_fish[idx].dir;
        //fish[idx].dead = copy_fish[idx].dead;
    }
    
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            int idx = copy_map[i][j];
            map[i][j] = idx;

        }
    }
    
}


int main(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            int idx, dir;
            cin >> idx >> dir;
            
            map[i][j] = idx;
            fish[idx].x = i;
            fish[idx].y = j;
            fish[idx].dir = dir;
            fish[idx].dead = false;
        }
    }
    
    //상어 투입
    _max = map[0][0];//먹은 물고기 인덱스 합계에 저장
    fish[map[0][0]].dead = true;
    map[0][0] = -1; //상어는 -1
    DFS(0, 0, fish[_max].dir, _max);
    
    cout << _max;
}
