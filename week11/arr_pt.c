// arr_pt.c
#include <stdio.h>

#define SIZE 10

int main(void) {
	char data[SIZE] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};
	int result = 0, // �ջ꿡 ����� result ����
		i;
	char* p = data; // data �迭�� ���� ��ġ

	// 10�� �ݺ��ϸ鼭 ������ p�� ����Ͽ� �迭�� �� ��Ҹ� result ������ �ջ���
	for (i = 0; i <SIZE; i++) { // data[9]
		printf("���� result: %d\n", result);
		// ������ p�� ����Ű�� ����� ���� �ջ���
		result = result + *p;
		// data �迭�� ���� �׸����� �ּҸ� �̵���
		p++;
	}

	printf("������ result ��: %d\n", result);


	return 0;
}