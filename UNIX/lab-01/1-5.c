#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(void) {

	char *str;

	if (access("linux.txt", F_OK) == -1) { //"linux.txt"이 존재하지 않는다면
		str = strerror(errno); //strerror()함수를 통해 에러 메시지 문자열을 가리키는 포인터를 받아온다.
		printf("linux.txt : %s\n", str); //에러 메시지를 출력한다.
		exit(1); //에러 메시지 종료
	}
	return 0;
}
