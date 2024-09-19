#include <stdio.h>  // 표준 입출력 라이브러리 포함
#define _CRT_SECURE_NO_WARNINGS  // scanf 보안 경고를 비활성화하기 위한 정의

// 두 행렬 a와 b의 합을 계산하여 c에 저장하는 함수
void Addmatrix(int a[][3], int b[][3], int c[][3], int size)
{
    for (int i = 0; i < size; i++)  // 각 행을 순회
        for (int j = 0; j < 3; j++)  // 각 열을 순회
            c[i][j] = (a[i][j] + b[i][j]);  // a와 b의 같은 위치 값을 더해 c에 저장
}

// 행렬을 출력하는 함수
void printMatrix(int a[][3], int size)
{
    for (int i = 0; i < size; i++)  // 각 행을 순회
    {
        for (int j = 0; j < 3; j++)  // 각 열을 순회
        {
            printf("%5d", a[i][j]);  // 각 원소를 출력
        }
        printf("\n");  // 행이 끝날 때마다 줄바꿈
    }
}

// 사용자로부터 행렬을 입력받는 함수
void readMatrix(int a[][3], int size)
{
    for (int i = 0; i < size; i++)  // 각 행을 순회
    {
        for (int j = 0; j < 3; j++)  // 각 열을 순회
        {
            scanf_s("%d", &a[i][j]);  // 행렬 원소를 입력받아 a에 저장
        }
    }
}

// 행렬 a와 b에 대해 상수 number를 곱한 결과를 출력하는 함수
void scalarMatrix(int a[][3], int b[][3], int size, int number)
{
    printf("행렬 a\n\n");  // 행렬 a에 상수를 곱한 결과 출력 시작
    for (int i = 0; i < size; i++)  // 각 행을 순회
    {
        for (int j = 0; j < 3; j++)  // 각 열을 순회
        {
            printf("%5d", (a[i][j]) * number);  // a의 각 원소에 상수를 곱한 값을 출력
        }
        printf("\n\n");  // 각 행이 끝날 때마다 줄바꿈
    }

    printf("행렬 b\n\n");  // 행렬 b에 상수를 곱한 결과 출력 시작
    for (int i = 0; i < size; i++)  // 각 행을 순회
    {
        for (int j = 0; j < 3; j++)  // 각 열을 순회
        {
            printf("%5d", (b[i][j]) * number);  // b의 각 원소에 상수를 곱한 값을 출력
        }
        printf("\n\n");  // 각 행이 끝날 때마다 줄바꿈
    }
}

// 프로그램의 시작점
int main(void)
{
    int A[3][3], B[3][3], C[3][3];  // 3x3 행렬 A, B, C 선언
    int number = 0;  // 곱할 상수를 저장할 변수

    // 사용자로부터 행렬 A 입력
    printf("(3 x 3) 행렬 A 입력 : \n");
    readMatrix(A, 3);

    // 사용자로부터 행렬 B 입력
    printf("(3 x 3) 행렬 B 입력: \n");
    readMatrix(B, 3);

    // A와 B의 합을 C에 저장
    Addmatrix(A, B, C, 3);

    // C 행렬을 출력 (A와 B의 합)
    printf("행렬 합:\n"); 
    printMatrix(C, 3);
    printf("\n");

    // 스칼라 곱할 상수를 입력받음
    printf("곱할 상수를 입력해주세요:\n");
    scanf_s("%d", &number);

    // A와 B 행렬에 각각 상수를 곱한 결과 출력
    printf("스칼라 곱:\n"); 
    scalarMatrix(A, B, 3, number);

    return 0;  // 프로그램 종료
}
