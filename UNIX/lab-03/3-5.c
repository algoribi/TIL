#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	FILE *rfd, *wfd; // read와 write용도의 fd를 선언
	
	rfd = fopen("3-1.txt", "r"); // 원본 파일을 읽기 모드로 열기
	if (rfd == NULL) { // 파일 열기에 실패 했을 때
		perror("fopen fail");// 오류 출력
		exit(1);
	}
	
	wfd = fopen("3-5.txt", "w"); // 출력 파일을 쓰기 모드로 열기
	char ch = '\0';
	while(1) { // 원본 파일 스트림이 EOF를 만나지 않았다면 반복
		ch = getc(rfd);
		if (feof(rfd))
			break;
		putc(ch, wfd); // 원본 파일에서 하나의 문자를 읽어온 후 출력 파일에 쓰기
	}
	
	// open했던 파일 닫기
	fclose(rfd);
	fclose(wfd);

	return 0;
}
