### 2X2 행렬 곱 ###
#include <iostream>
using namespace std;

int main()
{
	int A[2][2] = { {1, 2}, {3, 4} };
	int B[2][2] = { {5, 6}, {7, 8} };
	int C[2][2] = {0};
	
	// 행렬 곱셈 연
	for(int i=0; i<2; ++i)
	{
			for(int j=0; j<2; ++j)
			{
					for(int k=0; k<2; ++k)
					{
							C[i][j] += A[i][k] * B[i][k];
					}
			}
	}
	
	//결과 출력
	for(int i=0; i<2; ++i)
	{
			for(int j=0; j<2; ++j)
			{
					count<<C[i][j]<<" ";
			}
			cout<<"\n";
	}
}

### 3X3 행렬 곱 ###
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int A[3][3] = {{1,1,1},
                   {2,2,2},
                   {3,3,3}};                
    int B[3][3] = {{1,2,3},
                   {1,2,3},
                   {1,2,3}};
    int C[3][3] = {0};
    
    //3X3 행렬곱 
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<C[i][j];
            if(j<2) cout<<" ";
        }
        cout<<endl;
    }   
    return 0;
}


### 벡터를 사용한 행렬 곱셈 ###
#include<iostream>
#include<vector>
using namespace std;

int main()
{
		vector<vector<int>>A = { {1,2}, {3,4} };
		vector<vector<int>>B = { {5,6}, {7,8} };
		int n = A,size();
		int m = B[0],size();
		int inner = B,size();
		vector<vector<int>> C(n, vector<int>(m, 0));
		
		// 행렬 곱셈 연산
    for(int i=0; i<n; ++i)
	  {
			for(int j=0; j<m; ++j)
			{
					for(int k=0; k<inner; ++k)
					{
							C[i][j] += A[i][k] * B[i][k];
					}
			}
	  }
	
	// 결과 출력
	for(int i=0; i<n; ++i)
	{
			for(int j=0; j<m; ++j)
			{
					count<<C[i][j]<<" ";
			}
			count<<"\n";
	}
}

### 두 개의 3x3 행렬을 입력받아 그 행렬을 곱한 결과를 출력 ###
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 출력함수
void printMatrix(int m[][3]) { 
	printf("----- 출력 -----\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%5d", m[i][j]);
		}
		printf("\n");
	}
}
// 입력함수
void setMatrix(int m[][3]) { 
	int i, j;
	for (i = 0; i < 3; i++) {  
		for (j = 0; j < 3; j++) {
			printf("[%d][%d] : 입력\n", i, j);
			scanf("%d", &m[i][j]);
		}
		if (j != 3)
			printf("mA[%d][%d] : 입력\n", i, j);
	}
}
//계산 함수 
void calcMatrix(int a[][3],int b[][3], int c[][3]){  
	int k, temp;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp = 0;
			for (k = 0; k < 3; k++) {
				temp += (a[i][k] * b[k][j]);
			}
			c[i][j] = temp;
		}
	}
}
int main(void) {
	int mA[3][3] = { 0 };
	int mB[3][3] = { 0 };
	int mC[3][3] = { 0};

	while (1) {
		int s = NULL;
		printf("프로그램을 계속 진행시키고 싶으시면 1을 입력해주세요\n");
		printf("<<프로그램 종료는 0을 입력해주세요>>");
		scanf("%d", &s);
		if (s == 0) break;
		
		printf("mA 입력\n");
		setMatrix(mA);
		printf("mB 입력\n");
		setMatrix(mB);

		printf("mA 출력\n");
		printMatrix(mA);
		printf("mB 출력\n");
		printMatrix(mB);
		printf("mC 계산\n");
		calcMatrix(mA, mB, mC);

		printf("mC 출력\n");
		printMatrix(mC);
	}
	return 0;
}
