#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct _corridor{
    int num=0;
}_corridor;

int main(int argc, const char * argv[]) {
    int T;
    int N;
    int start;
    int arr;
    
    cin >> T;//테스트 케이스 수
    for(int i = 0; i<T; i++){
        cin >> N;//학생 수
        int room[400][2];//N으로 하니까 안됨
        _corridor c1[200];
        int _max=0;
        
        for(int j = 0; j<N; j++){//이동할 방을 room배열에 저장
            cin >> room[j][0] >> room[j][1];
        }
        
        for(int k = 0; k<N; k++){
            start = room[k][0];//start에 출발 방의 숫자 저장
            arr = room[k][1];//arr에 도착 방의 숫자 저장
            
            if(start%2==1){//start가 홀수이면
                start /= 2;
            }else{//짝수일때
                start = start/2-1;
            }
            
            if(arr%2==1){//arr가 홀수이면
                arr /= 2;
            }else{
                arr = arr/2-1;
            }
            
            if(start > arr){//start보다 arr이 크다면 순서 바꿔줌
                int temp;
                temp = start;
                start = arr;
                arr = temp;
            }
            
            for(int t = start; t<=arr; t++){
                c1[t].num+=1;
                if(c1[t].num > _max){
                    _max = c1[t].num;
                }
            }
        }
        
        cout << "#" << i+1 << " " << _max << endl;
        
    }
}
