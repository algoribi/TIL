#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int fd, n;
	off_t start, cur;
	char buf[256];

	fd = open("3-1.txt", O_RDONLY); // read모드로 3-1.txt파일 open
	if (fd == -1) { // open에 오류가 생겼을 경우
		perror("Open unix.txt"); // 오류 출력
		exit(1);
	}

	start = lseek(fd, 0, SEEK_CUR); // lseek()를 이용하면 원하는 위치로 커서를 이동시킬 수 있다. SEEK_CUR인자를 주어 현재 파일 오프셋에서 pos값(0)을 더한 값으로 설정한다.
	n = read(fd, buf, 255); // buf에 fd를 읽어온다.
	buf[n] = '\0'; // 문자열의 끝을 가리킨다.
	printf("Offset start=%d, Read Str=%s, n=%d\n", (int)start, buf, n); // lseek()에서 pos값이 0이었기 때문에 fd의 처음부터 전부 출력된다.
	cur = lseek(fd, 0, SEEK_CUR); // 위의 lseek와 같은 조건
	printf("offset cur=%d\n", (int)cur); // fd의 총 길이를 출력한다.

	start = lseek(fd, 7, SEEK_SET); // SEEK_SET은 파일의 커서가 처음에 있다고 가정하고 pos값(7)만큼 오프셋한 위치로 설정한다.
	n = read(fd, buf, 255); // buf에 fd를 읽어온다.
	buf[n] = '\0'; // 문자열의 끝을 가리킨다.
	printf("offset start=%d, Read Str=%s\n", (int)start, buf); // lseek()에서 pos값이 7이었기 때문에 커서를 7번 옮긴 후에 문자부터 출력을 시작한다.

	close(fd); // open했던 파일 닫기

	return 0;
}
