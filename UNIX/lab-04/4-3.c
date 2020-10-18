#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
	struct stat buf;
	
	stat("password.txt", &buf); // "password.txt"의 성질을 buf에 저장
	printf("Mode before change = %o\n", (unsigned int)buf.st_mode); // buf의 permission을 바꾸기 전의 File type and mode 출력

	buf.st_mode |= S_IWGRP; // st_mode에 IWGRP(그룹이 쓸 수 있는 권한)를 부여한다.
	buf.st_mode &= ~(S_IROTH); // st_mode에 IROTH(others가 읽을 수 있는 권한)를 없앴다.
	chmod("password.txt", buf.st_mode); // chmod를 통해 "password.txt"의 permission을 새로운 buf.st_mode로 바꿔준다.
	stat("password.txt", &buf); // stat을 통해 "password.txt"의 상태 값을 buf에 다시 얻어온다.

	printf("mode after change = %o\n", (unsigned int)buf.st_mode); // buf의 permission을 바꾼 후의 File type and mode 출력

	return 0;
}
