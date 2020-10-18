#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) { //커맨드라인 인자(command-line argument) 사용
	//변수 선언 : 옵션을 받는 변수 n, 곱을 구할 변수 sum, 합을 구할 변수 add	
	int n = getopt(argc, argv, "am"), sum = 0, add = 0;
	switch (n) {
		case 'a' :
			for (int i = 1; i < argc; i++)
				sum += atoi(argv[i]);
			printf("합 : %d\n", sum);
			break;
		case 'm' :
			for (int i = 2; i < argc; i++) 
				sum *= atoi(argv[i]);
			printf("곱 : %d\n", sum);
			break;
	}
	return 0;
}
