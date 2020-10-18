#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	DIR *dp;
	struct dirent *dent;
	
	if ((dp = opendir(".")) == NULL) { // opendir을 통해 디렉토리를 연다(DIR 타입의 포인터를 받아온다). 이때 "."에서 .은 지금 위치한 디렉토리를 뜻함으로 현재 디렉토리를 연다. 이때 오류가 발생하면 if문을 수행한다.
		perror("opendir: ."); // 오류 출력
		exit(1);
	}

	while ((dent = readdir(dp))) { // dp에 불러온 디렉토리 안의 내용을 하나씩 dent에 넣어 확인한다. 이때 디렉토리 내의 모든 파일을 확인했다면 NULL을 받아 while문을 종료하게 된다.
		printf("Name : %s ", dent->d_name); // dent로 넘어온 파일의 name을 출력한다.
		printf("Inode : %d\n", (int)dent->d_ino); // dent로 넘어온 파일의 inode를 출력한다.
	}

	closedir(dp); // 앞서 opendir을 통해 열었으니 closedir을 통해 닫아준다.

	return 0;
}
