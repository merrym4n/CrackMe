// CrackMe.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string.h>


char passwd_key[] = { 0x3,
0x7,
0x15,
0xb,
0x1a,
0x3b,
0x1,
0xa,
0x9,
0x39,
0x30,
0x15,
0x3e,
0x3,
0x16,
0x5,
0x2,
0x1c,
0x6,
0x15,
0x2,
0x1c };

int flag = 0;

char problem[] = {
0x4,
0x5,
0x7,
0x1b,
0x11 };

long dummy1 = 1111111111111;
float dummy2 = 2.23423512612341234;

char again[] = { 0x3,
0x19,
0x18,
0xd
};

unsigned int dummy3 = 19970728;
unsigned long dummy4 = 16011129;

char make[] = { 0xc,
0xd,
0x1,
0x9,
0xc,
0x8,
0x1,
0x1b
};

int verify0(char key[]);
int verify1(char key[]);

int compare(char key[]);
int compare1(char key[]);
int compare2(char key[]);
int compare3(char key[]);

int is_prime(int n);
void decode(char key[], int index);

int main() {
	char key[100] = "answkektlaksemfrl";
	int ret = 100;

	while (ret) {
		printf("Input the key: ");
		scanf("%s", key);
		getchar();

		ret = verify0(key);
		if (!ret) {
			printf("올바른 패스워드 입니다.\n");
			if (flag) printf("하지만 비밀번호 파일이 오염되었습니다.\n");
		}
		else {
			flag = 1;
			printf("틀린 패스워드 입니다.\n%d\n", ret);
		}
		decode(key, 0);
	}
    return 0;
}


int verify0(char key[]) {
	int ret;
	if (key[0] - 97) return -10;
	if (key[9] - 97) return -11;
	if (ret = compare(key)) return ret;
	return verify1(key);
}

int verify1(char key[]) {
	if (strlen(key) % 10 != 7) return -20;
	if (strlen(key) / 10 != 1) return -21;
	if (!is_prime(strlen(key)))return -22;
	return 0;
}

int compare(char key[]) {
	if (compare1(key)) return -12;
	if (compare2(key)) return -13;
	if (compare3(key)) return -14;
	return 0;
}

int compare1(char key[]) {
	char buf[100];
	int len_passwd = strlen(passwd_key), len_key = strlen(key);
	//strncpy(buf, problem, strlen(problem));
	for (int i = 0; i < strlen(problem); i++) { 
		buf[i] = key[i] ^ key[(i + strlen(problem)) % len_key];
		if (strncmp(buf + i, problem + i, 1)) {
			//printf("%d %d %d\n", i, buf[i], passwd_key[i]);
			return -121;
		}
	}
	//printf("=====%d", strncmp(buf, problem, len_passwd));
	if (strncmp(buf, problem, len_passwd)) {
		//printf("%d\n\n\n", strncmp(key, problem, len_passwd));
		return -12;
	}
	//printf("====================\n");
	return 0;
	if (strncmp(key, problem, strlen(problem))) {
		//printf("============\n");
		return -122;
	}
	return 0;
}

int compare2(char key[]) {
	char buf[100];
	int len_passwd = strlen(passwd_key), len_key = strlen(key);
	//strncpy(buf, problem, strlen(problem));
	for (int i = strlen(problem); i < strlen(again); i++) {
		buf[i] = key[i] ^ key[(i + strlen(again)) % len_key];
		if (strncmp(buf + i, again + i-strlen(problem), 1)) {
			//printf("%d %d %d\n", i, buf[i], again[i-strlen(problem)]);
			return -13;
		}
	}
	return 0;
}

int compare3(char key[]) {
	char buf[100];
	int len_passwd = strlen(passwd_key), len_key = strlen(key);
	//strncpy(buf, problem, strlen(problem));
	//printf("%d==========\n", strlen(make));
	for (int i = strlen(again); i < strlen(make); i++) {
		buf[i] = key[i] ^ key[(i + strlen(again) - strlen(problem)) % len_key];
		if (strncmp(buf + i, make + i - strlen(again), 1)) {
			//printf("%d %d %d\n", i, buf[i], again[i-strlen(problem)]);
			return -14;
		}
	}
	return 0;
}

int is_prime(int n) {
	if (n <= 1) return 0;
	for (int i = 2; i < n / 2; i++) if (!(n%i)) return 0;
	return 1;
}

void decode(char key[], int index) {
	int len_passwd = strlen(passwd_key) - index, len_key = strlen(key);
	for (int i = 0; i < len_passwd; i++) passwd_key[i+index] ^= key[(i + (len_passwd - len_key)) % len_key];
	printf("%s\n", passwd_key);
}