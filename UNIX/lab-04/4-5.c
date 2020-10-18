#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	if (mkdir("linux", 0755) == -1) { // mkdir을 이용하여 linux라는 이름의 디렉토리를 0755 permission으로 만든다. 이때 오류가 생긴다면 if문을 수행한다.
		perror("linux"); // 오류 출력
		exit(1);
	}

	if (mkdir("programming", 0644) == -1) { // mkdir을 이용하여 programming라는 이름의 디렉토리를 0644 permission으로 만든다. 이때 오류가 생긴다면 if문을 수행한다.
		perror("programming"); // 오류 출력
		exit(1);
	}

	return 0;
}
