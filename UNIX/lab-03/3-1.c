#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int fd;
	mode_t mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // USER에게는 R(read),W(write)권한을 그룹에게는 R, others에게는 R권한을 주도록 모드를 설정한다.

	fd = open("3-1.txt", O_CREAT, mode); // creat모드로 3-1.txt파일을 open한다.
	if (fd == -1) { // 오류가 생겼을 경우
		perror("Creat"); // 오류 출력
		exit(1); 
	}
	close(fd); // open했던 파일 닫기

	return 0;
}
