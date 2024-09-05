#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5  // 배열 크기를 5로 정의

int main(void)
{
    FILE* file;  // 파일 포인터 선언
    int i;
    int j;
    int temp;
    int num[5] = { 0 };  // 5개의 정수 배열 초기화

    // 파일을 "descending_order.txt"로 열기 (쓰기 모드)
    file = fopen("descending_order.txt", "w");
    if (file == NULL)  // 파일이 존재하지 않으면 오류 메시지 출력
    {
        printf("File does not exist");
        return -1;  // 오류 발생 시 프로그램 종료
    }

    // SIZE만큼 정수를 입력받기
    printf("SIZE수 만큼의 정수를 입력하시오: ");
    for (i = 0; i < SIZE; i++)
    {
        scanf_s("%d", &num[i]);  // 각 숫자를 배열에 저장
    }

    // 내림차순으로 배열 정렬
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            //if (num[i] > num[j])  // 내림차순 정렬 조건
            if (num[i] > num[j])  // 오름차순 정렬 조건
            {
                temp = num[i];  // 값 교환
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }

    // 정렬 결과 출력
    printf("결과: ");
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", num[i]);
    }

    // 정렬된 결과를 파일에 출력
    for (i = 0; i < SIZE; i++)
    {
        fprintf(file, "%d\n", num[i]);  // 파일에 숫자 저장
    }

    fclose(file);  // 파일 닫기

    return 0;  // 프로그램 종료
}

