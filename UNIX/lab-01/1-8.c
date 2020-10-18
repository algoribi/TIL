#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { //커맨드라인 인자(command-line argument) 사용
	int i, sum = 0;
	
	for (i = 1; i < argc; i++) {
		sum += atoi(argv[i]); //인자로 받아온 값을 sum에 더한다(반복)
	}

	printf("%d\n", sum); // 더한 값(sum)을 출력
	return 0;

}
