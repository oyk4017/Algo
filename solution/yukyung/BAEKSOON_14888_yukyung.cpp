//백준 14888 연산자 끼워넣기
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int N;
int num[11];
int op_cnt[4];//0은 + 갯수, 1은 - 갯수, 2는 * 갯수, 3은 / 갯수
int _max = -1e9;//max값을 0으로 했었는데 이 부분이 오류였음. 최솟값과 최댓값의 범위는 -1e9~1e9 사이의 값
int _min = 1e9;

void start(int idx, int op, int sum){//DFS
    if(idx==N-2){//탈출 조건 설정. N이 마지막에서 2번째 값일 때 계산 후 탈출
        if(op==0){//연산자가 +인 경우
            sum += num[idx+1];
        }
        else if(op==1){//연산자가 -인 경우
            sum -= num[idx+1];
        }
        else if(op==2){//연산자가 *인 경우
            sum *= num[idx+1];
        }
        else if(op==3){//연산자가 /인 경우
            sum /= num[idx+1];
        }
        if(_min > sum){//최솟값이 현재 결과값보다 크면 갱신
            _min = sum;
        }
        if(_max < sum){//최댓값이 현재 결과값보다 작으면 갱신
            _max = sum;
        }
        return;
    }
    
    if(op==0){//연산자가 +인 경우
        sum += num[idx+1];
    }
    else if(op==1){//연산자가 -인 경우
        sum -= num[idx+1];
    }
    else if(op==2){//연산자가 *인 경우
        sum *= num[idx+1];
    }
    else if(op==3){//연산자가 /인 경우
        sum /= num[idx+1];
    }
    
    for(int i = 0; i<4; i++){//다음 숫자와 연산자에 대해 반복문 실행
        if(op_cnt[i]!=0){//남은 연산자 갯수가 0이 아닐 때
            op_cnt[i]--;
            start(idx+1, i, sum);
            op_cnt[i]++;//back tracking!!!
        }
    }
    
}

int main(void) {

    cin >> N; //수 갯수 입력받기
    
    for(int i = 0; i<N; i++){//숫자 입력받기
        cin >> num[i];
    }
    
    
    for(int i = 0; i<4; i++){//연산자 갯수 입력받기
        cin >> op_cnt[i];
    }
    
    for(int i = 0; i<4; i++){
        if(op_cnt[i]!=0){//남은 연산자 갯수가 0이 아닐 때
            op_cnt[i]--;
            start(0, i, num[0]);//첫번째 수의 위치와 현재 연산자의 위치, 현재 계산값을 넘겨준다.
            op_cnt[i]++;//back tracking!!!
        }
    }
    
    //결과값 출력
    cout << _max <<endl;
    cout << _min <<endl;
}
