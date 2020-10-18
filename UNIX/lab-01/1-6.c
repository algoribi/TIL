#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char *str;
	
	str = malloc(sizeof(char) * 20); // malloc()함수를 통해 char(1Byte)*20크기 만큼을 할당해준다.
	
	strcpy(str, "Hello"); //strcpy()함수를 통해 str에 문자열 "Hello"를 복사한다
	printf("%s\n", str); //str출력

	strcpy(str, "Good morning"); //str문자열에 "Good morning"을 복사한다
	printf("%s\n", str); //str출력

	free(str); //free()를 통해 할당받은 메모리를 반환한다
	return 0;
}
