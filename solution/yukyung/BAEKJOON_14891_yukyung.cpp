#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int T[4][8];//N은 0, S는 1
int K;//회전시킬 갯수
int num_t;

int tmp;

typedef struct PAIR{
    int num;
    int dir;
}pair_t;

pair_t command[100];

void rotation(int num, int dir){//회전함수
    //회전
    if(dir==1){//시계방향
        tmp = T[num][7];
        for(int i = 7; i>0; i--){
            T[num][i] = T[num][i-1];
        }
        T[num][0]=tmp;
    }
    if(dir==-1) {//반시계방향
        tmp = T[num][0];
        for(int i = 0; i<7; i++){
            T[num][i] = T[num][i+1];
        }
        T[num][7]=tmp;
    }
    
}

int main(void) {
    
    for(int i = 0; i<4;i++){//톱니바퀴 입력
        for(int j = 0; j<8;j++){
            scanf("%1d", &T[i][j]);
        }
    }
    cin >> K;//회전 횟수 입력
    
    for(int i = 0; i<K; i++){//회전방법 입력
        cin >> command[i].num >> command[i].dir;
    }
    
    for(int i=0; i<K; i++){//오른쪽 왼쪽에 따라 비교하고 회전
        int turn_dir[4]={0};//1이면 시계방향, -1이면 반시계방향, 0이면 정지
        turn_dir[command[i].num-1] = command[i].dir;
        
        //오른쪽
        for(int j = command[i].num-1; j<3; j++){
            int right_t = T[j][2];
            if(right_t==T[j+1][6]){
                break;
            }else{
                turn_dir[j+1] = turn_dir[j]*(-1);
            }
        }
        //왼쪽
        for(int j = command[i].num-1; j>0;j--){
            int left_t = T[j][6];
            if(left_t==T[j-1][2]){
                break;
            }else{
                turn_dir[j-1] = turn_dir[j]*(-1);
            }
            
        }
        
        for(int j = 0; j<4;j++){
            rotation(j, turn_dir[j]);
            
        }
        

    }
    int sum=0;
    for(int i = 0; i<4; i++){//점수 합
        if(T[i][0]==1){
            sum += 1 << i;
        }
    }
    
    cout << sum;
}
