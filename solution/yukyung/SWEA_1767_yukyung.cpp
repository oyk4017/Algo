//
//  main.cpp
//  SWEA_1767_yukyung
//
//  Created by 오유경 on 2020/08/20.
//  Copyright © 2020 오유경. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
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
int con_res = 0; //연결된 프로세서 개수
int res = 1e9; //연결된 전선 길이 합
mcore mc[13] = {0};

bool fill_line(int x, int y, int dir){
    int movx = x + dx[dir], movy = y + dy[dir];
    while (movx < N && movx >=0 && movy < N && movy >= 0){//다음좌표가 맵 배열 안에 있고
        if(map[movx][movy]>0) return false;//다음 좌표가 0이 아니라면 false 리턴
        movx += dx[dir]; //다음 좌표가 0이면 전진
        movy += dy[dir];
    }
    movx = x + dx[dir], movy = y + dy[dir];
    while(movx<N&& movx>=0 && movy<N&&movy>=0){//다음 좌표가 배열 안에 있고
        map[movx][movy] = 2;//다음 좌표 2로 채움
        movx += dx[dir];
        movy += dy[dir];
    }
    return true;
    
}

int line(int dir, int x, int y){//연결된 선의 합 반환
    //전진 방향에 따라 값 다르게 반환
    if(dir==0) return x;
    else if (dir==1) return N-1-y;
    else if (dir==2) return N-1-x;
    else return y;
}

void restore_line(int x, int y, int dir){
    int movx = x + dx[dir], movy = y + dy[dir];
    while(movx < N && movx >= 0 && movy < N && movy >= 0) {//다음 좌표가 맵 배열 안에 있을 때
            map[movx][movy] = 0; //다시 0으로 초기화
            movx += dx[dir];
            movy += dy[dir];
        }
    }

void start(int step, int connect, int sum){
    if(step >= core_cnt){//탈출조건
        if(con_res <= connect){
            if(con_res < connect){
                con_res = connect;
                res = sum;//연결 선의 합 res에 저장
            }
            else{
                if(res > sum)
                    res = sum;
            }
        }
        return;
    }
    
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
    
    movx = mc[step].x;
    movy = mc[step].y;
    
    if(!skip){//skip이 false일 때 실행 (가장자리 아닌 경우)
        bool go = false;
        for (int j = 0; j < 4 ; j++){
            if(fill_line(movx, movy, j)){//다음좌표가 0일 경우
                start(step + 1, connect +1, sum + line(j, movx, movy));//다음 커넥트 진행
                restore_line(movx, movy, j);//이부분 잘 이해안가요 ㅜㅜ 백트래킹 어느 시점에서 일어나는지
                go = true;
                
                
            }
        }
        if(!go) start(step+1, connect, sum);//헷갈려뒤지는중
    }
    else{//가장자리라면
        start(step+1, connect+1, sum);//다음 커넥트 진행
    }
        return;
}



int main(void)
{
    freopen("input.txt", "r", stdin); //input.txt파일
    
    cin>>T; //수행할 테스트 케이스 갯수 입력받기
    
    for(int tc = 0 ; tc<T ; tc++){ //testcase를 입력받은 T만큼 반복
        //반복시 코어 갯수, 선 갯수 등 초기화
        core_cnt = 0;
        con_res = 0;
        res = 1e9;
        
        cin >> N;
        
        for(int i = 0 ; i < N ; i++){//NxN배열
            for(int j = 0; j < N ; j++){
                cin >> map[i][j];
                if(map[i][j]){//값이 1일때 core값 세어주고, 좌표 찍어준다.
                    mc[core_cnt].x=i;
                    mc[core_cnt++].y=j;
                }
            }
        }

        start(0,0,0);
        cout << "#" << tc+1 << " " << res << "\n";
    }
    
    
}
