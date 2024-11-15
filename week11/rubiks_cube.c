// rubiks_cube.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	// rand(), srand()
#include <time.h>	// time()

#define LENGTH 3 // 길이
#define FACES 6 // 면

// 전역 변수 선언
char* colors[FACES] = {
	"white", "red","blue","green","orange","yellow"
};
char letters[FACES] = { 'W','R','B','G','O','Y' };
int hexColors[FACES] = {
	0xFFF, 0xF00, 0x00F, 0x0F0, 0xFA0, 0xFF0
};

// 3x3x6 배열로 큐브 상태 확인 (6개의 면)
int cube[LENGTH][LENGTH][FACES];

// 프린트 모드 선택 
enum PrintMode{ STRING, LETTER, HEX };

// 큐브 초기화 함수
void initCube() {
	for (int i = 0; i < FACES; i++) { // 열
		for (int j = 0; j < LENGTH; j++) { // 행
			for (int k = 0; k < LENGTH; k++) { // 열
				cube[i][j][k] = i; // 0~5로 각 명 초기화
			}
		}
	}
}

// 큐브 프린트 함수
void printCube(enum PrintMode mode) {
	const char* labels[FACES] = {
		"Up","Left","Front","Right","Back","Down"
	};
	for (int i = 0; i < FACES; i++) {
		printf("%s face:\n", labels[i]);
		for (int j = 0; j < LENGTH; j++) { // 행
			for (int k = 0; k < LENGTH; k++) { // 열
				switch (mode) {
				case STRING:
					printf("%-7s", colors[cube[i][j][k]]);
					break;
				case LETTER:
					printf("%c", letters[cube[i][j][k]]);
					break;
				case HEX:
					printf("%#05X", hexColors[cube[i][j][k]]);
					break;
				}
			}
			printf("\n"); // 다음 행으로 가기
		}
		printf("\n"); // 다음 면으로 가기
	}
}

// 90도 시계 방향 회전
void rotateFace(int face) {
	int temp[LENGTH][LENGTH]; // 임시 변수에 저장
	for (int i = 0; i < LENGTH; i++) { // 행
		for (int j = 0; j < LENGTH; j++) { // 열
			temp[i][j] = cube[face][i][j];
		}
	}
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			cube[face][j][2 - 1] = temp[i][j];
		}
	}
}

// 큐브 섞기 함수 (랜덤 회전)
void scrambleCube() {
	printf("Scrambling...");
	srand(time(0));
	for (int i = 0; i < 15; i++) {
		int face = rand() % FACES;
		switch (face) {
		case 0: rotateFace(0); printf("U "); break;
		case 1: rotateFace(1); printf("L "); break;
		case 2: rotateFace(2); printf("F "); break;
		case 3: rotateFace(3); printf("R "); break;
		case 4: rotateFace(4); printf("B "); break;
		case 5: rotateFace(5); printf("D "); break;
		}
	}
}

void rotateRight() {
	int temp[LENGTH];
	// 오른쪽 면 시계 방향회전
	for (int i = 0; i < LENGTH; i++) temp[i] = cube[3][i][2];
	for (int i = 0; i < LENGTH; i++) cube[3][i][2] = cube[0][2][2-i];
	for (int i = 0; i < LENGTH; i++) cube[0][2][2 - i] = cube[1][2-i][0];
	for (int i = 0; i < LENGTH; i++) cube[1][i][0] = cube[5][0][i];
	for (int i = 0; i < LENGTH; i++) cube[5][0][i] = temp[i];
}

void easyScramble() {
	printf("Scrambling...");
	for (int i = 0; i < 5; i++) {
		rotateRight(); // 단순 예제: 오른쪽 5회 회전 
	}
}

int main(void) {
	// 초기화
	initCube();
	printf("Initial Cube:\n");
	printCube(STRING);

	// 섞기
	for (int i = 1; i <= 4; i++) {
		easyScramble();
		printCube(LETTER);
	}

	return 0;
}