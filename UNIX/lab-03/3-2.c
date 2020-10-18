#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int fd;
	int n;

	char str[] = "UNIX SYSTEM PROGRAMMING";

	fd = open("3-1.txt", O_WRONLY); // 3-1.txt파일을 open한다.
	if (fd == -1) { // 오류가 생겼을 경우
		perror("Open"); // 오류 출력
		exit(1); 
	}

	n = write(fd, str, strlen(str)); // str에 있는 문자를 strlen만큼 fd에 write한다.
	if (n != strlen(str)) { // write에서 오류가 생겼을 경우
		perror("Write"); // 오류 출력
		exit(2);
	}

	close(fd); // open했던 파일 닫기

	return 0;
}
