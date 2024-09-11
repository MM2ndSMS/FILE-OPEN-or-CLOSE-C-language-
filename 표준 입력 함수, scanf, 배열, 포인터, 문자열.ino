ex 1.
int main(void)
int num;
scanf("%d", &num);
......
}

ex 2. scanf의 잘못된 사용
int main(void)
{
	unsigned char age;
	scanf("%d", &age);
	......
}

=> 메모리 침범 발생, 심각한 버그

ex 2. 해결
int main(void)
{
	int temp;
	scanf("%d", &temp);
	age = (insigned *)temp;
	......
}

## rewind.01 ##
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void main()
{
	int temp = 0;
	while (1)
	{
		printf("나이를 입력하세요: ");
		scanf_s("%d", &temp);
		if (temp > 0 && temp < 200)
		{
			printf("나이 입력 성공\n");
			break;
		}
		else
		{
			printf("나이를 0 ~ 200 사이로 입력해주세요\n");
		}
	}
	printf("입력하신 나이는 :%d\n", temp);
}

## rewind.02 ##
#include <stdio.h>

void main()
{
	int temp = 0;
	while (1)
	{
		printf("나이를 입력하세요: ");
		scanf("%d", &temp);
		rewind(stdin);
		if(temp > 0 && temp<200)
		{
			printf("나이 입력 성공\n");
			break;
		}
		else
		{
			printf("나이를 0 ~ 200 사이로 입력해주세요\n");
		}
	}
	printf("입력하신 나이는 :%d\n", temp);
}

ex 4의 응용
int main(void)
{
	char astr[] = "OH MY GOD";
	astr = "OH MY GOODNESS";
}
=>  바뀌지 않는다.

int main(void)
{
	char* pstr = "OH MY GOD";
	pstr = "OH MY GOODNESS";
}
=> 바뀐다. 가리키고 있는 메모리 주소가 바뀌기 때문이다.

ex 5. '1' 의 정수형 변환
'1'에 대한 아스키 코드 값은 49
'0'에 대한 아스키 코드 값은 48
=> 49 - 48 = 1
혹은 
=> '1' - '0' = 1
// 결과적으로 "123"은 다음과 같이 표현이 된다.

('1'-'0')*100 + ('2'-'0')*10 + ('3'-'0') => 123

혹은 atoi("123");

## 배열과 포인터의 관계.01 ##
void main()
{
	int arr[3] = {0,};
	int *p = arr;
	Example(arr);
}

-> Example함수
void Example(int *ptr)
{
	```
}

배열을 받아주는 포인터 * ptr의 선언은 다음과 같이 바꿀 수 있다.

-> 같은 인자 선언
void Example(int ptr[])
{
	```
}

함수의 매개변수 선언에 있어서 배열을 받을 때 *ptr = ptr[]과 같이 사용할 수 있다.
하지만 위의 경우 외에는 절대 그렇게 쓰지 못한다.

## 배열과 포인터의 관계.03 ##
char data[8];의 배열에서
다음 두 개는 같은 표현이다
->
data[4] = 1;
*(data + 4) = 1;
->
배열은 자기 자료형으로만 사용할 수 있다. (캐스팅 연산이 안됨)
하지만 포인터는 캐스팅 연산을 할 수 있는 기회를 만들어준다.
->
(short*)data[4] = 1;
*(short*)(data + 4) = 1;

=> 이를 응용

int data[2] = {0x12345678, 0x9abcdef0}

1) data[1] = 0x22;
->
data[1] = 0x00000022;

2) *(char*)(data+1) = 0x22;
->
data[1] = 0x9abcde22;

## 포인터 다섯 개를 선언 : char *p[5] ##
char *p [5]
1. []연산자가 *연산자보다 우선순위가 높음
-> char형 배열 5개가 있음
2. 이 배열안에는 *p가 들어있음
-> 따라서
포인터 5개를 char*p[5]라는 배열에 넣은 것이고
총 크기는 20 Byte(5*4=20) 이다.
여기서의 5는 char형 배열의 크기고 4는 포인터의 크기이다.

## 포인터 한 개를 선어 : char(*p)[5] ##
char(*p) [5]
1. 포인터가 하나 있는데 *p
2. 얘가 가리키는 곳의 변위가 char형 5개 즉, 5Byte이다.
-> 따라서 포인터는 하나고 가리키는 대상을 배열처럼 가리키는 것이다.
이 선언의 총 크기는 4Byte(포인터의 크기) 이다.

이것은 다음과 같이 쓸 수 있는데

(*p)[2] = 5;
->
p가 가리키는 (*) 곳의 5 Byte 중 세 번째 Byte([2])에 5의 값을 집어 넣어라

## 2차원 배열과 포인터의 관계 ##
char arr[3][5];
char (*p)[5] = arr;

->
(*p)는 현재 arr[0][0]을 가리키는 중이고
(*(p+1))은 arr[1][0]을 가리킬 것이다.

-> 따라서
(*(p+2))[1] = 4;라고 선언을 하면
가리키는 곳은 arr의 [2][1]dlrh,
arr의 3번째 행(y) 2번째 열(x)에 4의 값이 저장될 것이다.

-> 추가적으로
표기상의 편함을 위해 다음과 같이 표현한다.
*(p+2)는 p[2]와 같기 때문에
(*(p+2))[1] == (p[2])[1] == p[2][1]
