#include<stdio.h>
#include<string.h>
#include<ctype.h>

int find(char* str, int min, int max);


typedef struct dic {
	char *dan;
	char *fum;
	char mean[5000];
}dic;


dic diction[180000];

char b[5000];

char st[180000][5000];

int main()
{

	int i = 0, j = 0;
	int count = 1;
	int x;
	char s[100];
	char c;
	char *context = NULL;

	errno_t err;
	FILE *fp;



	err = fopen_s(&fp, "dict.txt", "r");
	if (err == 0)
		puts("파일오픈 성공(기다려 주세요)\n");
	else
		puts("파일 오픈 실패\n");


	while (fscanf_s(fp, "%c", &c) != EOF) {

		if (c != '\n') {

			b[i++] = c;

		}
		else if (i != 0) {

			b[i] = '\0';

			i = 0;

			strcpy_s(diction[j++].mean, 5000, b);

		}

	};

	fclose(fp);


	for (i = 0; i < j; i++) {

		strcpy_s(st[i], 5000, diction[i].mean);

		diction[i].dan = strtok_s(st[i], " ", &context);

		diction[i].fum = strtok_s(NULL, " ", &context);

	}




	printf("저장된 단어의 개수 : %d\n", j + 1);
	while (1) {

		printf("\n검색할 단어를 입력하시오 (종료:0):\n ");

		scanf_s("%s", s, sizeof(s));

		if (strcmp(s, "0") == 0) {

			printf("\nexit");

			return 0;

		}
		if (islower(s[0]))s[0] = toupper(s[0]);

		x = find(s, 0, j - 1);

		if (x > 0) {

			while (x != -1) {

				if (strcmp(diction[x].dan, diction[x - 1].dan) == 0)x--;

				else break;
			}

			while (x < j) {


				if (strcmp(diction[x].dan, diction[x + 1].dan) == 0) {
					count++;
					x++;
				}
				else break;
			}

			printf("\nFound %d items.\n", count);

			x = x - count + 1;

			for (i = 0; i < count; i++)printf("%s\n\n", diction[x++].mean);

		}

		else {

			printf("\nNot found.\n\n");

			printf("%s %s\n\n", diction[-x].dan, diction[-x].fum);

			printf("----\n\n");

			printf("%s %s\n\n", diction[-x + 1].dan, diction[-x + 1].fum);

		}

	}

	return 0;
}




int find(char* str, int min, int max) {
	int i;
	static int q = 0;
	int key = (max + min) / 2;


	i = strcmp(diction[key].dan, str);


	if (i == 0)return key;
	else if (min >= max)return -min;
	else if (i == 1)return find(str, min, key - 1);
	else  return find(str, key + 1, max);

}
