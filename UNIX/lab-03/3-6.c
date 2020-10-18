#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char *fname;
	char fntmp[BUFSIZ];
	char template[32];

	fname = tmpnam(NULL); // 기존 파일과 충돌되지 않도록 생성된 임시 파일명을 fname에 저장한다.
	printf("1. TMP File Name(tmpnam) : %s\n", fname); // 생성된 임시 파일명 출력

	tmpnam(fntmp); // 기존 파일과 충돌되지 않도록 생성된 임시 파일명을 fntmp에 저장한다.
	printf("2. TMP File Name(tmpnam) : %s\n", fntmp); // 생성된 임시 파일명 출력

	fname = tempnam("/tmp", "coredump"); // 사용자가 지정한 디렉토리("/tmp")에서 사용할 수 있는 임시 파일명을 생성해서 return한다. 이때 두 번째 인자 *prefix가 NULL이 아닌 값으로 들어오면 최대 5자리까지 임시 파일명의 접두어로 적용된다.
	printf("3. TMP File Name(tempnam) : %s\n", fname); // 생성된 임시 파일명 출력

	strcpy(template, "/tmp/cordumpXXXXXX"); // template에 두번째 인자 string을 복사
	fname = mktemp(template); // mktemp()는 template에 지정된 템플릿을 기반으로 임시 파일명을 만든다. 이때 template는 "XXXXXX"으로 끝나야 하며 이 부분을 임시 파일명으로 대치시켜준다.
	printf("4. TMP File Name(mktemp) : %s\n", fname); // 생성된 임시 파일명 출력

	return 0;
}
