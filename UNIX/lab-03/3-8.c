#include <stdio.h>
#include <stdlib.h>

// 학생들의 이름과 과목별 점수를 저장할 구조체를 선언
typedef struct student {
	char name[20];
	double score1, score2, score3, sum_score;
}stu;

int main(void) {
	FILE *dat, *out;
	char name1[20], name2[20], name3[20];
	double kor, eng, math, kor_ave = 0.0, eng_ave = 0.0, math_ave = 0.0;
	stu arr[100];
	
	dat = fopen("3-8.dat", "r"); // 3-8.dat파일을 read모드로 open
	if (dat == NULL) { // fopen에 실패했을 때
		perror("3-8.dat fail");// 오류 출력
		exit(1);
	}

	out = fopen("3-8.out", "w"); // 3-8.out파일을 write모드로 open
	if (dat == NULL) { // fopen에 실패했을 때
		perror("3-8.out fail");// 오류 출력
		exit(1);
	}

	fscanf(dat,"%s\t%s\t%s", name1, name2, name3); // 첫 줄의 과목명을 받는다.
	int counter = 0; // 학생 수를 세 주는 변수
	// dat 파일의 끝이 아닐 동안 반복한다.
	while (!feof(dat)) {
		// fscanf를 이용해 한 줄 씩 받아 저장한다.
		fscanf(dat, "%s\t%lf\t%lf\t%lf", arr[counter].name, &arr[counter].score1, &arr[counter].score2, &arr[counter].score3);
		// 각 과목의 평균 계산을 위해 값을 더한다.
		kor_ave += arr[counter].score1;
		eng_ave += arr[counter].score2;
		math_ave += arr[counter].score3;
		counter++;
	}
	counter -= 1;
	// 각 과목의 평균 계산
	kor_ave /= (counter);
	eng_ave /= (counter);
	math_ave /= (counter);

	// 성적순 정렬
	stu temp;
	for (int i = counter; i > 1; i--) {
		for (int j = 1; j < i; j++) {
			int num1 = arr[j - 1].score1 + arr[j - 1].score2 + arr[j - 1].score3; // j-1번째 학생의 점수 총합
			int num2 = arr[j].score1 + arr[j].score2 + arr[j].score3; // j번째 학생의 점수 총합
			if (num1 < num2) { // 두 학생의 점수 비교 후 정렬
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}

	// out파일에 결과 저장
	fprintf(out, "이름  과목총합\n");
	for (int i = 0; i < counter; i++) {
		fprintf(out, "%s\t%.1lf\n", arr[i].name, (arr[i].score1+arr[i].score2+arr[i].score3));
	}
	fprintf(out, "\n각 과목별 평균\n");
	fprintf(out, "%s : %.2lf\n", name1, kor_ave);
	fprintf(out, "%s : %.2lf\n", name2, eng_ave);
	fprintf(out, "%s : %.2lf\n", name3, math_ave);

	return 0;
}
