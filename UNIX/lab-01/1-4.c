#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	//access()함수를 이용하여 파일의 존재 여부(F_OK)를 0(존재함) 또는 -1(존재하지 않음)으로 return받습니다.
	if (access("linux.txt", F_OK) == -1) { //"linux.txt"이 존재하지 않는다면
		perror("linux.txt"); //perror()함수를 통해 오류 메시지 출력
		exit(1); //에러 메시지 종료
	}
	return 0;
}
