#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char buf[]="/tempXXXXXX\0"; // mkstemp() 에서 사용할 템플릿을 만든다.
	
	mkstemp(buf); // buf에 저장된 템플릿에 맞게 제작한 임시 파일명을 fname에 저장
	printf("TMP File Name : %s\n", buf); // 생성된 임시 파일명 출력

	return 0;
}
