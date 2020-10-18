#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
	struct stat buf;
	
	stat("password.txt", &buf); // "password.txt"의 성질을 buf에 저장

	printf("Mode = %o (16진수 : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode); // buf의 File type and mode 출력

	if(S_ISFIFO(buf.st_mode)) printf("password.txt: FIFO\n"); // 만약 buf의 st_mode 값이 FIFO라면 printf문을 출력한다.
	if(S_ISDIR(buf.st_mode)) printf("password.txt: Directory\n"); // 만약 buf의 st_mode 값이 DIR(디렉토리)이라면 printf문을 출력한다.
	if(S_ISREG(buf.st_mode)) printf("password.txt: Regualr File\n"); // 만약 buf의 st_mode 값이 REG(레귤러 파일)라면 printf문을 출력한다.

	return 0;
}
