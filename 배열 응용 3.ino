#define _CRT_SECURE_NO_WARNINGS  // 안전하지 않은 함수 사용에 대한 경고를 무시
#include <stdio.h>               // 표준 입출력 함수 사용을 위한 헤더 파일
#include <math.h>                // 수학 함수 사용을 위한 헤더 파일

int n = 0;  // waypoints의 개수를 추적하는 전역 변수

// 파일에서 waypoint 데이터를 읽어오는 함수
void read_file(const char* filename, double X[], double Y[], double Angle[])
{
    FILE* file = fopen(filename, "r");  // 파일을 읽기 모드로 엶

    if (file == NULL)  // 파일이 없을 경우 오류 처리
    {
        printf("File doesn't exist\n");
        return;
    }

    // 파일에서 좌표와 각도 데이터를 읽어오며 배열에 저장
    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        n++;  // 읽어온 좌표의 개수 증가
        if (n >= 100)  // 최대 100개의 데이터를 읽음
        {
            break;
        }
    }

    fclose(file);  // 파일 닫기
}

// waypoints 간의 간격(차이)을 계산하는 함수
void interval(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 1; i < n; ++i)  // 첫 번째 점은 기준으로 남겨두고 두 번째 점부터 시작
    {
        X_ref[i] = X[i] - X[i - 1];  // X좌표 간 차이를 계산하여 저장
        Y_ref[i] = Y[i] - Y[i - 1];  // Y좌표 간 차이를 계산하여 저장
    }
}

// 첫 번째 좌표를 기준으로 상대 좌표를 계산하는 함수
void relative_coordinate(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 0; i < n; ++i)
    {
        X_ref[i] = X[i] - X[0];  // 첫 번째 X 좌표를 기준으로 상대적인 X 좌표를 계산
        Y_ref[i] = Y[i] - Y[0];  // 첫 번째 Y 좌표를 기준으로 상대적인 Y 좌표를 계산
    }
}

// waypoints 간의 거리를 계산하는 함수
void DIST(double X[], double Y[], double Dist[])
{
    for (int i = 1; i < n; ++i)
    {
        // 피타고라스 정리를 이용하여 각 waypoints 간의 거리를 계산
        Dist[i] = sqrt((X[i] - X[i - 1]) * (X[i] - X[i - 1]) + (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));
    }
}

// 각 waypoints 사이의 Yaw 각도를 계산하는 함수
void YawAngles(double x[], double y[], int count, double yaw_angle[])
{
    for (int i = 0; i < n - 1; i++)
    {
        double dx = x[i + 1] - x[i];  // x 좌표의 차이
        double dy = y[i + 1] - y[i];  // y 좌표의 차이

        // atan2를 이용하여 각도를 계산하고, 라디안을 도 단위로 변환
        double angle = atan2(dy, dx) * 180.0 / 3.141592;

        if (angle < 0) angle += 360.0;  // 음수일 경우 360도를 더해 양수로 변환

        yaw_angle[i] = angle;  // 계산한 각도를 배열에 저장
    }
}

int main(void)
{
    // 좌표와 각도를 저장할 배열 선언 및 초기화
    double X[100] = { 0.0 };
    double Y[100] = { 0.0 };
    double Angle[100] = { 0.0 };
    double X_ref[100] = { 0.0 };
    double Y_ref[100] = { 0.0 };
    double Dist[100] = { 0.0 };
    double yaw_angle[100] = { 0.0 };
    int num = 0;  // 사용자 선택을 저장할 변수

    // 메뉴를 출력하고 사용자로부터 선택을 입력받음
    printf("(1) waypoint 데이터 출력\n");
    printf("(2) waypoint 간의 간격 출력\n");
    printf("(3) waypoint 상대좌표 출력\n");
    printf("(4) waypoint 거리 출력\n");
    printf("(5) waypoint 각도 출력\n");
    scanf("%d", &num);

    // 파일에서 waypoint 데이터를 읽어옴
    read_file("waypoint.txt", X, Y, Angle);

    // 사용자 선택에 따라 각각의 기능 실행
    switch (num)
    {
    case 1:  // waypoint 데이터 출력
    {
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf\n", i, X[i], i, Y[i], i, Angle[i]);
        }
        break;
    }

    case 2:  // waypoint 간의 간격 출력
    {
        interval(X_ref, Y_ref, X, Y);  // 간격 계산
        for (int i = 0; i < n; i++)
        {
            printf("Interval - X[%d] = %lf, Y[%d] = %lf\n", i, X_ref[i], i, Y_ref[i]);
        }
        break;
    }

    case 3:  // waypoint 상대좌표 출력
    {
        relative_coordinate(X_ref, Y_ref, X, Y);  // 상대 좌표 계산
        for (int i = 0; i < n; i++)
        {
            printf("Relative Coordinate - X_ref[%d] = %lf, Y_ref[%d] = %lf\n", i, X_ref[i], i, Y_ref[i]);
        }
        break;
    }

    case 4:  // waypoint 거리 출력
    {
        DIST(X, Y, Dist);  // 거리 계산
        for (int i = 0; i < n; i++)
        {
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }

    case 5:  // waypoint 각도 출력
    {
        YawAngles(X, Y, n, yaw_angle);  // 각도 계산
        for (int i = 0; i < n - 1; i++)
        {
            printf("Yaw angle %d and %d: %.2f degrees\n", i, i + 1, yaw_angle[i]);
        }
        break;
    }
    }
    return 0;  // 프로그램 종료
}
