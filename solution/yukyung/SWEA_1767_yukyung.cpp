//
//  main.cpp
//  SWEA_1767_yukyung
//
//  Created by 오유경 on 2020/08/20.
//  Copyright © 2020 오유경. All rights reserved.
//

#include <iostream>
using namespace std;

#define MAX_MAP_SIZE 16

typedef struct mexynos {
    int x;
    int y;
}mcore;

int T, N;
int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };

//동서남북
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int core_cnt;
int con_res = 0; //무슨 변수?
int res = 1e9; //무슨 변수?
mcore mc[13] = {0};

bool fill_line(int x, int y, int dir){
    int movx = x + dx[dir], movy = y + dy[dir];
    while (movx < N && movx >=0 && movy < N && movy >= 0){
        if(map[movx][movy]>0) return false;
        movx += dx[dir];
        movy += dy[dir];
    }
    movx = x + dx[dir], movy = y + dy[dir];
    while(movx<N&& movx>=0 && movy<N&&movy>=0){
        map[movx][movy] = 1;
        movx += dx[dir];
        movy += dy[dir];
    }
    return true;
    
}

void start(int step, int connect, int sum){
    
    int movx = mc[step].x, movy = mc[step].y;
    bool skip = false;
    bool result;
    
    for(int i = 0;i<4;i++){//동서남북 체크
        movx = mc[step].x + dx[i];
        movy = mc[step].y + dy[i];
        if(movx<0 || movx >= N || movy < 0 || movy >=N){ //가장자리일 경우
            skip = true;
            break;
        }
    }
    
    movx = mc[step].x, movy = mc[step].y;
    
    if(!skip){//skip이 false일 때 실행
        bool go = false;
        for (int j = 0; j < 4 ; j++){
            if(fill_line(movx, movy, j)){//혼란..
                start(step + 1, connect +1, sum + line(j, movx, movy));
                restore_line(movx, movy, j);
                
                
            }
        }
    }
}



int main(void)
{
    
    
    cin>>T;
    
    for(int tc = 0 ; tc<T ; tc++){ //testcase를 입력받은 T만큼 반복
        //반복시 코어 갯수, 선 갯수 등 초기화
        cin >> N;
        
        for(int i = 0 ; i < N ; i++){
            for(int j = 0; j < N ; j++){
                cin >> map[i][j];
                if(map[i][j]){//값이 1일때 core값 세어주고, 좌표 찍어준다.
                    mc[core_cnt].x=i;
                    mc[core_cnt++].y=j;
                }
            }
        }

        start(0,0,0);
        //cout << "#" << tc+1 << " " << min << "\n";
    }
    
    
}
