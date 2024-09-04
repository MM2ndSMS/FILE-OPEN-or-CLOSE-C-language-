## 배열 a[100]을 정의하고 정수로 저장된 파일을 읽어서 배열에 저장
#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 보안 경고를 무시하도록 설정 (fopen 등 표준 라이브러리 함수 사용 시)
#include<stdio.h>  // 표준 입출력 함수들을 사용하기 위해 표준 입출력 헤더 파일을 포함

int main(void)
{
    int a[100] = {0};  // 크기 100의 정수 배열 a를 정의하고 모든 요소를 0으로 초기화
    int temp, result;  // temp는 파일에서 읽어온 값을 저장할 변수, result는 fscanf 함수의 반환값을 저장할 변수
    FILE* fp;  // 파일 포인터를 선언

    // 현재 작업 디렉토리에서 data.txt 파일을 읽기 모드로 엽니다.
    fp = fopen("data.txt", "r");
    if (fp == NULL)  // 파일을 여는 데 실패한 경우
    {
        printf("Error: Unable to open file.\n");  // 오류 메시지를 출력
        return 1;  // 프로그램을 종료하고 비정상 종료 코드 1을 반환
    }
    else
    {
        // 배열의 크기만큼 반복 (최대 100개 요소)
        for (int i = 0; i < 100; i++)  
        {
            // 파일에서 정수를 읽어 temp에 저장하고, 읽은 항목의 개수를 result에 저장
            result = fscanf(fp, "%d", &temp);

            // fscanf의 반환값이 1이 아니면, 즉 더 이상 읽을 데이터가 없으면 루프를 종료
            if (result != 1)
            {
                break;
            }

            a[i] = temp;  // 읽어온 값을 배열 a의 i번째 위치에 저장
            printf("a[%d] = %d\n", i, a[i]);  // 배열의 i번째 요소를 출력 (디버깅 또는 확인용)
        }
        fclose(fp);  // 파일을 닫음
    }

    return 0;  // 프로그램이 성공적으로 종료됨을 알리는 0을 반환
}

## 배열 a[100]을 정의하고 정수로 저장된 파일을 읽어서 배열에 저장 + 파일의 데이터 갯수는 출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int a[100] = {0};  // 크기 100의 정수 배열 a를 정의하고 모든 요소를 0으로 초기화
    int temp, result;  // temp는 파일에서 읽어온 값을 저장할 변수, result는 fscanf 함수의 반환값을 저장할 변수
    FILE* fp;  // 파일 포인터를 선언
    int count = 0;  // 읽어온 데이터의 개수를 저장할 변수

    // 현재 작업 디렉토리에서 data.txt 파일을 읽기 모드로 엽니다.
    fp = fopen("data.txt", "r");
    if (fp == NULL)  // 파일을 여는 데 실패한 경우
    {
        printf("Error: Unable to open file.\n");  // 오류 메시지를 출력
        return 1;  // 프로그램을 종료하고 비정상 종료 코드 1을 반환
    }
    else
    {
        // 배열의 크기만큼 반복 (최대 100개 요소)
        for (int i = 0; i < 100; i++)
        {
            // 파일에서 정수를 읽어 temp에 저장하고, 읽은 항목의 개수를 result에 저장
            result = fscanf(fp, "%d", &temp);

            // fscanf의 반환값이 1이 아니면, 즉 더 이상 읽을 데이터가 없으면 루프를 종료
            if (result != 1)
            {
                break;
            }

            a[i] = temp;  // 읽어온 값을 배열 a의 i번째 위치에 저장
            printf("a[%d] = %d\n", i, a[i]);  // 배열의 i번째 요소를 출력 (디버깅 또는 확인용)
            count++;  // 데이터 개수를 증가시킴
        }
        fclose(fp);  // 파일을 닫음
    }

    // 파일에서 읽어온 데이터의 개수를 출력
    printf("Number of data read: %d\n", count);

    return 0;  // 프로그램이 성공적으로 종료됨을 알리는 0을 반환
}
