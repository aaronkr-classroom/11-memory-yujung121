// rubiks_cube.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	// rand(), srand()
#include <time.h>	// time()

#define LENGTH 3 // ����
#define FACES 6 // ��

// ���� ���� ����
char* colors[FACES] = {
	"white", "red","blue","green","orange","yellow"
};
char letters[FACES] = { 'W','R','B','G','O','Y' };
int hexColors[FACES] = {
	0xFFF, 0xF00, 0x00F, 0x0F0, 0xFA0, 0xFF0
};

// 3x3x6 �迭�� ť�� ���� Ȯ�� (6���� ��)
int cube[LENGTH][LENGTH][FACES];

// ����Ʈ ��� ���� 
enum PrintMode{ STRING, LETTER, HEX };

// ť�� �ʱ�ȭ �Լ�
void initCube() {
	for (int i = 0; i < FACES; i++) { // ��
		for (int j = 0; j < LENGTH; j++) { // ��
			for (int k = 0; k < LENGTH; k++) { // ��
				cube[i][j][k] = i; // 0~5�� �� �� �ʱ�ȭ
			}
		}
	}
}

// ť�� ����Ʈ �Լ�
void printCube(enum PrintMode mode) {
	const char* labels[FACES] = {
		"Up","Left","Front","Right","Back","Down"
	};
	for (int i = 0; i < FACES; i++) {
		printf("%s face:\n", labels[i]);
		for (int j = 0; j < LENGTH; j++) { // ��
			for (int k = 0; k < LENGTH; k++) { // ��
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
			printf("\n"); // ���� ������ ����
		}
		printf("\n"); // ���� ������ ����
	}
}

// 90�� �ð� ���� ȸ��
void rotateFace(int face) {
	int temp[LENGTH][LENGTH]; // �ӽ� ������ ����
	for (int i = 0; i < LENGTH; i++) { // ��
		for (int j = 0; j < LENGTH; j++) { // ��
			temp[i][j] = cube[face][i][j];
		}
	}
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			cube[face][j][2 - 1] = temp[i][j];
		}
	}
}

// ť�� ���� �Լ� (���� ȸ��)
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
	// ������ �� �ð� ����ȸ��
	for (int i = 0; i < LENGTH; i++) temp[i] = cube[3][i][2];
	for (int i = 0; i < LENGTH; i++) cube[3][i][2] = cube[0][2][2-i];
	for (int i = 0; i < LENGTH; i++) cube[0][2][2 - i] = cube[1][2-i][0];
	for (int i = 0; i < LENGTH; i++) cube[1][i][0] = cube[5][0][i];
	for (int i = 0; i < LENGTH; i++) cube[5][0][i] = temp[i];
}

void easyScramble() {
	printf("Scrambling...");
	for (int i = 0; i < 5; i++) {
		rotateRight(); // �ܼ� ����: ������ 5ȸ ȸ�� 
	}
}

int main(void) {
	// �ʱ�ȭ
	initCube();
	printf("Initial Cube:\n");
	printCube(STRING);

	// ����
	for (int i = 1; i <= 4; i++) {
		easyScramble();
		printCube(LETTER);
	}

	return 0;
}