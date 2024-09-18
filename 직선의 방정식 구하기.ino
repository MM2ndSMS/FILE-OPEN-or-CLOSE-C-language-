### waypoint간의 거리에 대하여 직선의 방정식을 구하는 프로그램 ###
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <math.h>    // 수학 함수 사용을 위한 헤더 파일

int n = 0;   // 읽어온 웨이포인트 개수를 저장할 변수

// 파일을 읽어서 X, Y 좌표와 각도를 배열에 저장하는 함수
void read_file(const char* filename, double X[], double Y[], double Angle[])
{
    FILE* file = fopen(filename, "r");   // 파일을 읽기 모드로 열기

    if (file == NULL)   // 파일이 없을 경우 에러 메시지 출력
    {
        printf("File doesn't exist\n");
        return;
    }

    // 파일로부터 데이터를 읽어와 X, Y, Angle 배열에 저장
    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        n++;   // 데이터를 읽을 때마다 웨이포인트 개수를 증가
        if (n >= 100)   // 배열의 최대 크기를 초과하지 않도록 제한
        {
            break;
        }
    }

    fclose(file);   // 파일 닫기
}

// 두 점을 연결하는 직선의 기울기(a)와 절편(b)을 계산하는 함수
void equation(double X[], double Y[], double a[], double b[])
{
    for (int i = 0; i < n; i++)
    {
        a[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]);   // 두 점 사이의 기울기 계산
        b[i] = Y[i] - (a[i] * X[i]);   // 절편 계산
    }
}

int main(void)
{
    double X[100] = { 0.0 };   // X 좌표 저장 배열
    double Y[100] = { 0.0 };   // Y 좌표 저장 배열
    double Angle[100] = { 0.0 };   // 각도 저장 배열
    double a[100] = { 0.0 };   // 기울기 저장 배열
    double b[100] = { 0.0 };   // 절편 저장 배열

    printf("직선의 방정식 출력\n");

    read_file("waypoint.txt", X, Y, Angle);   // 웨이포인트 데이터를 파일에서 읽기


    // 웨이포인트 간의 직선 방정식을 출력
    equation(X, Y, a, b);
    printf("equation\n\n");
    for (int i = 0; i < n - 1; i++)
    {
        printf("직선의 방정식[%d ~ %d]: y = %lfx + %lf \n ", i, i + 1, a[i], b[i]);
    }
        return 0;   // 프로그램 종료
}


### waypoint에 대한 모드 코드 ###
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>   // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <math.h>    // 수학 함수 사용을 위한 헤더 파일

int n = 0;   // 읽어온 웨이포인트 개수를 저장할 변수

// 파일을 읽어서 X, Y 좌표와 각도를 배열에 저장하는 함수
void read_file(const char* filename, double X[], double Y[], double Angle[])
{
    FILE* file = fopen(filename, "r");   // 파일을 읽기 모드로 열기

    if (file == NULL)   // 파일이 없을 경우 에러 메시지 출력
    {
        printf("File doesn't exist\n");
        return;
    }

    // 파일로부터 데이터를 읽어와 X, Y, Angle 배열에 저장
    while (fscanf(file, "%lf %lf %lf", &X[n], &Y[n], &Angle[n]) != EOF)
    {
        n++;   // 데이터를 읽을 때마다 웨이포인트 개수를 증가
        if (n >= 100)   // 배열의 최대 크기를 초과하지 않도록 제한
        {
            break;
        }
    }

    fclose(file);   // 파일 닫기
}

// X, Y 좌표의 간격을 계산하는 함수
void interval(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 1; i < n; ++i)   // 두 번째 점부터 계산
    {
        X_ref[i] = X[i] - X[i - 1];   // 이전 좌표와의 차이를 계산하여 X_ref에 저장
        Y_ref[i] = Y[i] - Y[i - 1];   // 이전 좌표와의 차이를 계산하여 Y_ref에 저장
    }
}

// 첫 번째 웨이포인트를 기준으로 상대 좌표를 계산하는 함수
void relative_coordinate(double X_ref[], double Y_ref[], double X[], double Y[])
{
    for (int i = 0; i < n; ++i)
    {
        X_ref[i] = X[i] - X[0];   // 첫 번째 X 좌표를 기준으로 상대 좌표 계산
        Y_ref[i] = Y[i] - Y[0];   // 첫 번째 Y 좌표를 기준으로 상대 좌표 계산
    }
}

// 두 웨이포인트 간의 거리를 계산하는 함수
void DIST(double X[], double Y[], double Dist[])
{
    for (int i = 1; i < n; ++i)
    {
        Dist[i] = sqrt((X[i] - X[i - 1]) * (X[i] - X[i - 1]) + (Y[i] - Y[i - 1]) * (Y[i] - Y[i - 1]));   // 피타고라스의 정리로 거리 계산
    }
}

// 두 웨이포인트 사이의 각도를 계산하는 함수
void YawAngles(double x[], double y[], int count, double yaw_angle[])
{
    for (int i = 0; i < n - 1; i++)   // 각도를 계산할 때 마지막 좌표는 계산하지 않음
    {
        double dx = x[i + 1] - x[i];   // X 좌표 차이 계산
        double dy = y[i + 1] - y[i];   // Y 좌표 차이 계산

        double angle = atan2(dy, dx) * 180.0 / 3.141592;   // 아크탄젠트 함수로 각도 계산

        if (angle < 0) angle += 360.0;   // 음수 각도는 360도를 더해 양수로 변환

        yaw_angle[i] = angle;   // 계산된 각도를 배열에 저장
    }
}

// 거리를 기준으로 오름차순 정렬하는 함수
void ascending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{
    DIST(X, Y, Dist);   // 우선 거리 계산
    double temp = 0;
    for (int i = 0; i < column; i++)
    {
        for (int j = i; j < column; j++)
        {
            if (Dist[i] > Dist[j])   // 거리를 비교해 오름차순으로 정렬
            {
                // 거리 교환
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                // X 좌표 교환
                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                // Y 좌표 교환
                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                // 각도 교환
                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

// 거리를 기준으로 내림차순 정렬하는 함수
void descending_sort(double X[], double Y[], double Angle[], double Dist[], int column)
{
    DIST(X, Y, Dist);   // 우선 거리 계산
    double temp = 0;
    for (int i = 0; i < column; i++)
    {
        for (int j = i; j < column; j++)
        {
            if (Dist[i] < Dist[j])   // 거리를 비교해 내림차순으로 정렬
            {
                // 거리 교환
                temp = Dist[i];
                Dist[i] = Dist[j];
                Dist[j] = temp;

                // X 좌표 교환
                temp = X[i];
                X[i] = X[j];
                X[j] = temp;

                // Y 좌표 교환
                temp = Y[i];
                Y[i] = Y[j];
                Y[j] = temp;

                // 각도 교환
                temp = Angle[i];
                Angle[i] = Angle[j];
                Angle[j] = temp;
            }
        }
    }
}

// 두 점을 연결하는 직선의 기울기(a)와 절편(b)을 계산하는 함수
void equation(double X[], double Y[], double a[], double b[])
{
    for (int i = 0; i < n; i++)
    {
        a[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]);   // 두 점 사이의 기울기 계산
        b[i] = Y[i] - (a[i] * X[i]);   // 절편 계산
    }
}

int main(void)
{
    double X[100] = { 0.0 };   // X 좌표 저장 배열
    double Y[100] = { 0.0 };   // Y 좌표 저장 배열
    double Angle[100] = { 0.0 };   // 각도 저장 배열
    double X_ref[100] = { 0.0 };   // 상대 X 좌표 저장 배열
    double Y_ref[100] = { 0.0 };   // 상대 Y 좌표 저장 배열
    double Dist[100] = { 0.0 };   // 거리 저장 배열
    double yaw_angle[100] = { 0.0 };   // 각도 저장 배열
    double Distance[100] = { 0.0 };   // 정렬된 거리 저장 배열
    double a[100] = { 0.0 };   // 기울기 저장 배열
    double b[100] = { 0.0 };   // 절편 저장 배열
    int num = 0;   // 사용자가 선택한 메뉴 번호 저장 변수

    printf("(1) waypoint 데이터 출력\n");
    printf("(2) waypoint 간의 간격 출력\n");
    printf("(3) waypoint 상대좌표 출력\n");
    printf("(4) waypoint 거리 출력\n");
    printf("(5) waypoint 각도 출력\n");
    printf("(6) Distance 오름차순 출력\n");
    printf("(7) Distance 내림차순 출력\n");
    printf("(8) 직선의 방정식 출력\n");
    scanf("%d", &num);   // 사용자로부터 선택한 메뉴 입력받기

    read_file("waypoint.txt", X, Y, Angle);   // 웨이포인트 데이터를 파일에서 읽기

    // 사용자가 선택한 번호에 따라 해당 기능 수행
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
        // 웨이포인트 간의 간격 출력
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
        // 웨이포인트 간의 거리 출력
        DIST(X, Y, Dist);
        for (int i = 0; i < n; i++)
        {
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }

    case 5:
    {
        // 웨이포인트 간의 각도 출력
        YawAngles(X, Y, n, yaw_angle);
        for (int i = 0; i < n - 1; i++)
        {
            printf("Yaw angle %d and %d: %.2f degrees\n", i, i + 1, yaw_angle[i]);
        }
        break;
    }
    case 6:
    {
        // 거리를 오름차순으로 정렬하여 출력
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
        // 거리를 내림차순으로 정렬하여 출력
        descending_sort(X, Y, Angle, Dist, n);
        printf("Descending\n\n");
        for (int i = 0; i < n; i++)
        {
            printf("X[%d] = %lf, Y[%d] = %lf, Angle[%d] = %lf, ", i, X[i], i, Y[i], i, Angle[i]);
            printf("Distance[%d] = %lf\n", i, Dist[i]);
        }
        break;
    }
    case 8:
    {
        // 웨이포인트 간의 직선 방정식을 출력
        equation(X, Y, a, b);
        printf("equation\n\n");
        for (int i = 0; i < n-1; i++)
        {
            printf("직선의 방정식[%d ~ %d]: y = %lfx + %lf \n ",i, i+1, a[i], b[i]);
        }
        break;
    }
    }
    return 0;   // 프로그램 종료
}
