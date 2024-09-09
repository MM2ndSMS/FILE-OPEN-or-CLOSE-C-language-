#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  // 표준 입출력 함수 사용을 위한 헤더 파일 포함
#include <math.h>   // 수학 함수 사용을 위한 헤더 파일 포함 (ex: sqrt 함수)

int n = 0;  // 웨이포인트 데이터 개수를 추적하는 전역 변수

// 파일에서 웨이포인트 데이터를 읽어오는 함수
void read_file(const char* filename, double X[], double Y[], double Angle[], double waypoint[3][100])
{
    FILE* file = fopen(filename, "r");  // 파일을 읽기 모드로 오픈

    // 파일 열기 실패 시 오류 메시지 출력 후 함수 종료
    if (file == NULL)
    {
        printf("File doesn't exist\n");
        return;
    }

    // 파일에서 데이터를 읽어 배열에 저장, EOF(파일 끝)까지 반복
    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        // 읽은 데이터를 배열에 저장
        waypoint[0][n] = X[n];
        waypoint[1][n] = Y[n];
        waypoint[2][n] = Angle[n];
        n++;  // 데이터 개수 증가

        // 최대 100개 데이터를 초과하면 반복 종료
        if (n >= 100)
        {
            break;
        }
    }

    fclose(file);  // 파일 닫기
}

// 웨이포인트 간의 간격(이전 좌표와의 차이)을 계산하는 함수
void interval(double X_ref[], double Y_ref[], double X[], double Y[], double waypoint_ref[3][100])
{
    // 두 웨이포인트 간의 X, Y 좌표 차이를 계산
    for (int i = 1; i < n; ++i)
    {
        X_ref[i] = X[i] - X[i - 1];  // X 좌표 간의 차이
        waypoint_ref[0][i] = X_ref[i];  // 차이를 저장
        Y_ref[i] = Y[i] - Y[i - 1];  // Y 좌표 간의 차이
        waypoint_ref[1][i] = Y_ref[i];  // 차이를 저장
    }
}

// 첫 번째 웨이포인트를 기준으로 상대 좌표를 계산하는 함수
void relative_coordinate(double X_ref[], double Y_ref[], double X[], double Y[], double waypoint_ref[3][100])
{
    // 각 웨이포인트의 X, Y 좌표를 첫 번째 좌표를 기준으로 계산
    for (int i = 0; i < n; ++i)
    {
        X_ref[i] = X[i] - X[0];  // 첫 번째 웨이포인트와의 X 좌표 차이
        waypoint_ref[0][i] = X_ref[i];  // 상대 좌표 저장
        Y_ref[i] = Y[i] - Y[0];  // 첫 번째 웨이포인트와의 Y 좌표 차이
        waypoint_ref[1][i] = Y_ref[i];  // 상대 좌표 저장
    }
}

// 웨이포인트 간의 거리를 계산하는 함수
void DIST(double X[], double Y[], double Dist[])
{
    // 두 웨이포인트 간의 유클리드 거리를 계산
    for (int i = 1; i < n; ++i)
    {
        Dist[i] = sqrt((X[i] - X[i - 1]) * (X[i] - X[i - 1]) + (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));  // 거리 계산
    }
}

// 메인 함수
int main(void)
{
    // X, Y 좌표 및 각도, 상대 좌표, 거리 정보를 저장할 배열 선언 및 초기화
    double X[100] = { 0.0 };  // X 좌표 배열
    double Y[100] = { 0.0 };  // Y 좌표 배열
    double Angle[100] = { 0.0 };  // 각도 배열
    double waypoint[3][100] = { 0.0 };  // 웨이포인트 데이터를 저장할 2차원 배열
    double X_ref[100] = { 0.0 };  // 상대 X 좌표 배열
    double Y_ref[100] = { 0.0 };  // 상대 Y 좌표 배열
    double waypoint_ref[3][100] = { 0.0 };  // 상대 웨이포인트 데이터를 저장할 배열
    double Dist[100] = { 0.0 };  // 거리 배열
    int num = 0;  // 메뉴 선택을 위한 변수

    // 메뉴 출력
    printf("(1) waypoint 데이터 출력\n");
    printf("(2) waypoint 간의 간격 출력\n");
    printf("(3) waypoint 상대좌표 출력\n");
    printf("(4) waypoint 거리 출력\n");
    scanf("%d", &num);  // 사용자 입력을 받아 메뉴 선택

    read_file("waypoint.txt", X, Y, Angle, waypoint);  // 웨이포인트 데이터를 파일에서 읽음

    // 사용자가 선택한 메뉴에 따라 동작 수행
    switch (num)
    {
    case 1:
    {
        // 웨이포인트 데이터를 출력
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf\n", i, X[i], i, Y[i], i, Angle[i]);
        }
        break;
    }

    case 2:
    {
        // 웨이포인트 간의 간격을 계산하고 출력
        interval(X_ref, Y_ref, X, Y, waypoint_ref);
        for (int i = 1; i < n; i++)
        {
            printf("Interval - X[%d] = %lf, Y[%d] = %lf\n", i, waypoint_ref[0][i], i, waypoint_ref[1][i]);
        }
        break;
    }

    case 3:
    {
        // 웨이포인트의 상대 좌표를 계산하고 출력
        relative_coordinate(X_ref, Y_ref, X, Y, waypoint_ref);
        for (int i = 0; i < n; i++)
        {
            printf("Relative Coordinate - X_ref[%d] = %lf, Y_ref[%d] = %lf\n", i, waypoint_ref[0][i], i, waypoint_ref[1][i]);
        }
        break;
    }

    case 4:
    {
        // 웨이포인트 간의 거리를 계산하고 출력
        DIST(X, Y, Dist);
        for (int i = 1; i < n; i++)
        {
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }

    }

    return 0;  // 프로그램 정상 종료
}
