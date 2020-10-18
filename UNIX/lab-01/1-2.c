#include <unistd.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main(void) {
	//access()함수를 이용하여 파일의 존재 여부(F_OK)를 0(존재함) 또는 -1(존재하지 않음)으로 return받습니다.
	if (access("unix.txt", F_OK) == -1) { //"unix.txt"이 존재하지 않는다면
		printf("errno=%d\n", errno); //error 번호 출력
	}
	return 0;
}
























