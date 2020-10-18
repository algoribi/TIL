#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) { //커맨드라인 인자(command-line argument) 사용
	int fl = 0;
	if (argv[1][0] == '-') { //첫 번째 인자의 첫 번째 글자가 '-'라면 옵션
		if (strlen(argv[1]) == 2 && argv[1][1] == 'a')
			fl = 1; //'a'옵션임을 체크 한다.
		else if (strlen(argv[1]) == 3 && argv[1][1] == 'a' && argv[1][2] == 'm')
			fl = 2; //'am'옵션임을 체크한다.
		else if (strlen(argv[1]) == 2 && argv[1][1] == 'm')
			fl = 3; //'a'옵션임을 체크한다.
		else
			printf("부적절한 옵션입니다."); //부적절한 옵션 대응
	}
	else
		fl = 1; //옵션이 따로 들어오지 않았다면 'a'옵션과 같은 일을 한다.

	//합 구하기
	if (fl == 1 || fl == 2) {
		int sum = 0;
		for (int i = 1; i < argc; i++)
			sum += atoi(argv[i]);
		printf("합 : %d\n", sum);
	}
	//곱 구하기
	if (fl == 3 || fl == 2) {
		int sum = 1;
		for (int i = 2; i < argc; i++) 
			sum *= atoi(argv[i]);
		printf("곱 : %d\n", sum);
	}
	return 0;
}
