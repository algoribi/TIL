#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	struct stat buf;
	
	stat("password.txt", &buf); // "password.txt"의 permission을 buf에 저장
	printf("Link Count before link()= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	link("password.txt", "password.ln"); // link를 통해 "password.txt"의 또 다른 이름 "password.ln"을 link로 만들어 준다.

	stat("password.txt", &buf); // 다시 "password.txt"의 permission을 buf에 저장
	printf("Link Count after link()= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	stat("password.ln", &buf); // "password.ln"의 permission을 buf에 저장
	printf("Link Count of password.ln= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	symlink("password.txt", "password.sln"); //symlink를 통해 "password.txt"에 대해 "password.sln"라는 symbolic link를 만들어준다.

	stat("password.txt", &buf); // "password.txt"의 permission을 buf에 저장
	printf("Link Count of password.txt= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	stat("password.sln", &buf); // "password.sln"의 permission을 buf에 저장
	printf("Link Count of password.sln= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	lstat("password.sln", &buf); // lstat(지정된 파일이 심볼릭 링크면 그 링크가 가리키는 파일이 아니라 그 링크 자체에 대한 정보를 돌려준다.)을 통해 "password.sln"의 permission을 buf에 저장
	printf("Link Count of password.sln itself= %d\n", (int)buf.st_nlink); // buf의  Number of hard links 출력

	return 0;
}
