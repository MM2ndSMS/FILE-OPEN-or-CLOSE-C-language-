## 메모리 주소
#include <stdio.h>
 
int main(void)
{
    int num = 10;
 
    printf("%p\n", &num);
 
    return 0;
}

## 포인터의 선언과 동시에 초기화
#include <stdio.h>
 
int main(void) {
 
    int num;    // 일반 변수 선언
    int * pnum;    // 포인터 선언
    
    pnum = &num;    // 포인터에 num 주소 대입
    *pnum = 10;    // 포인터로 변수 num에 10 
 
    printf("변수명으로 num 값 출력 : %d\n", num);
    printf("포인터로 num 값 출력 : %d\n", *pnum);
 
    return 0;
}

## 포인터 연산자
#include <stdio.h>

int main()
{
	int num01 = 1234;
	double num02 = 3.14;

	int* ptr_num01 = &num01;
	double* ptr_num02 = &num02;

	printf("포인터의 크기는 %d입니다.\n", sizeof(ptr_num01));
	printf("포인터 ptr_num01이 가리키고 있는 주소값은 %#x입니다.\n", ptr_num01);
	printf("포인터 ptr_num02이 가리키고 있는 주소값은 %#x입니다.\n", ptr_num02);

	printf("포인터 ptr_num01이 가리키고 있는 주소에 저장된 값은 %d입니다.\n", *ptr_num01);
	printf("포인터 ptr_num02이 가리키고 있는 주소에 저장된 값은 %f입니다.\n", *ptr_num02);

	return 0;
}

