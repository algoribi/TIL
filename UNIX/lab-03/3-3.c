#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int rfd, wfd; // read와 write용도의 fd를 선언
	char buf[BUFSIZ]; // 읽어온 파일의 내용을 저장해 놓는 용도의 버퍼 선언
	
	rfd = open("3-1.txt", O_RDONLY); // read모드로 3-1.txt파일 open
	if (rfd == -1){ // open에 오류가 생겼을 경우
		perror("Open 3-1.txt"); // 오류 출력
		exit(1);
	}

	wfd = open("3-3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // 3-3.txt파일을 open한다. 이때 파일이 존재하면 write모드로 열고, 파일이 존재하지 않는다면 creat모드로 열고, 파일이 존재하고 내용이 존재하면 바꿀 수 있도록 한다.
	if (wfd == -1) { // open에 오류가 생겼을 경우
		perror("Open 3-3.txt"); // 오류 출력
		exit(2);
	}

	int n = read(rfd, buf, sizeof(buf)); // rfd에서 읽은 것을 buf에 넣는다.
	if (n == -1){ // read에 오류가 생겼을 경우
		perror("Read rfd"); // 오류 출력
		exit(1);
	}
	int n2 = write(wfd, buf, n); // buf에 있는 내용을 wfd에 write한다.
	if (n2 == -1) { // write에서 오류가 생겼을 경우
		perror("Write wfd"); // 오류 출력
		exit(2);
	}


	close(rfd);
	close(wfd);

	return 0;
}
