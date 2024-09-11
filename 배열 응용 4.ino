#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int n = 0;  // 파일에서 읽은 웨이포인트의 개수를 저장할 변수

// 파일에서 웨이포인트 데이터를 읽어오는 함수
void read_file(const char* filename, double X[], double Y[], double Angle[])
{
    FILE* file = fopen(filename, "r");  // 파일을 읽기 모드로 엶

    if (file == NULL)  // 파일을 여는 데 실패한 경우
    {
        printf("File doesn't exist\n");
        return;
    }

    // 파일에서 X, Y, Angle 값을 읽어 배열에 저장
    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        n++;
        if (n >= 100)  // 웨이포인트가 100개를 넘으면 종료
        {
            break;
        }
    }

    fclose(file);  // 파일을 닫음
}

// 웨이포인트 간 간격을 계산하는 함수
void interval(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 1; i < n; ++i)
    {
        X_ref[i] = X[i] - X[i - 1];  // 이전 웨이포인트와의 X 좌표 차이 계산
        Y_ref[i] = Y[i] - Y[i - 1];  // 이전 웨이포인트와의 Y 좌표 차이 계산
    }
}

// 첫 번째 웨이포인트를 기준으로 상대 좌표를 계산하는 함수
void relative_coordinate(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 0; i < n; ++i)
    {
        X_ref[i] = X[i] - X[0];  // 첫 번째 웨이포인트와의 X 좌표 차이 계산
        Y_ref[i] = Y[i] - Y[0];  // 첫 번째 웨이포인트와의 Y 좌표 차이 계산
    }
}

// 웨이포인트 간의 거리를 계산하는 함수
void DIST(double X[], double Y[], double Dist[])
{
    for (int i = 1; i < n; ++i)
    {
        // 피타고라스 정리를 사용하여 거리 계산
        Dist[i] = sqrt((X[i] - X[i - 1]) * (X[i] - X[i - 1]) + (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));
    }
}

// 두 웨이포인트 간의 Yaw 각도를 계산하는 함수
void YawAngles(double x[], double y[], int count, double yaw_angle[])
{
    for (int i = 0; i < n - 1; i++)
    {
        double dx = x[i + 1] - x[i];  // X 좌표 차이 계산
        double dy = y[i + 1] - y[i];  // Y 좌표 차이 계산

        // atan2를 사용하여 각도를 계산하고, 라디안을 각도로 변환
        double angle = atan2(dy, dx) * 180.0 / 3.141592;

        if (angle < 0) angle += 360.0;  // 음수일 경우 360도를 더해 양수로 변환

        yaw_angle[i] = angle;  // 계산된 각도를 저장
    }
}

// 웨이포인트 간의 거리를 기준으로 오름차순 정렬하는 함수
void ascending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{
    DIST(X, Y, Dist);  // 거리 계산 함수 호출
    double temp = 0;
    for (int i = 0; i < column; i++) 
    {
        for (int j = i; j < column; j++) 
        {
            if (Dist[i] > Dist[j])  // 거리가 큰 경우 교환
            {
                // 거리 교환
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                // X 교환
                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                // Y 교환
                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                // Angle 교환
                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

// 웨이포인트 간의 거리를 기준으로 내림차순 정렬하는 함수
void descending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{
    DIST(X, Y, Dist);  // 거리 계산 함수 호출
    double temp = 0;
    for (int i = 0; i < column; i++) 
    {
        for (int j = i; j < column; j++) 
        {
            if (Dist[i] < Dist[j])  // 거리가 작은 경우 교환
            {
                // 거리 교환
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                // X 교환
                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                // Y 교환
                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                // Angle 교환
                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

int main(void)
{
    double X[100] = { 0.0 };  // X 좌표를 저장할 배열
    double Y[100] = { 0.0 };  // Y 좌표를 저장할 배열
    double Angle[100] = { 0.0 };  // 각도를 저장할 배열
    double X_ref[100] = { 0.0 };  // 상대 좌표의 X값을 저장할 배열
    double Y_ref[100] = { 0.0 };  // 상대 좌표의 Y값을 저장할 배열
    double Dist[100] = { 0.0 };  // 웨이포인트 간 거리를 저장할 배열
    double yaw_angle[100] = { 0.0 };  // Yaw 각도를 저장할 배열
    double Distance[100] = { 0.0 };  // 거리를 저장할 배열
    int num = 0;  // 사용자 선택을 받을 변수

    // 사용자 메뉴 출력
    printf("(1) waypoint 데이터 출력\n");
    printf("(2) waypoint 간의 간격 출력\n");
    printf("(3) waypoint 상대좌표 출력\n");
    printf("(4) waypoint 거리 출력\n");
    printf("(5) waypoint 각도 출력\n");
    printf("(6) Distance 오름차순 출력\n");
    printf("(7) Distance 내림차순 출력\n");
    scanf("%d", &num);  // 사용자 입력

    read_file("waypoint.txt", X, Y, Angle);  // 파일에서 데이터를 읽음

    switch (num)
    {
    case 1:
    {
        // 웨이포인트 데이터 출력
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf\n", i, X[i], i, Y[i], i, Angle[i]);
        }
        break;
    }

    case 2:
    {
        // 웨이포인트 간 간격 출력
        interval(X_ref, Y_ref, X, Y);
        for (int i = 0; i < n; i++)
        {
            printf("Interval - X[%d] = %lf, Y[%d] = %lf\n", i, X_ref[i], i, Y_ref[i]);
        }
        break;
    }

    case 3:
    {
        // 웨이포인트의 상대 좌표 출력
        relative_coordinate(X_ref, Y_ref, X, Y);
        for (int i = 0; i < n; i++)
        {
            printf("Relative Coordinate - X_ref[%d] = %lf, Y_ref[%d] = %lf\n", i, X_ref[i], i, Y_ref[i]);
        }
        break;
    }

    case 4:
    {
        // 웨이포인트 간 거리 출력
        DIST(X, Y, Dist);
        for (int i = 0; i < n; i++)
        {
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }

    case 5:
    {
        // Yaw 각도 출력
        YawAngles(X, Y, n, yaw_angle);
        for (int i = 0; i < n - 1; i++)
        {
            printf("Yaw angle %d and %d: %.2f degrees\n", i, i + 1, yaw_angle[i]);
        }
        break;
    }

    case 6:
    {
        // 거리 오름차순 출력
        ascending_sort(X, Y, Angle, Distance, n);
        printf("Ascending\n\n");
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf, ", i, X[i], i, Y[i], i, Angle[i]);
            printf("Distance[%d] = %lf\n", i, Distance[i]);
        }
        break;
    }

    case 7:
    {
        // 거리 내림차순 출력
        descending_sort(X, Y, Angle, Dist, n);
        printf("Descending\n\n");
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf, ", i, X[i], i, Y[i], i, Angle[i]);
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }
    }

    return 0;  // 프로그램 종료
}
