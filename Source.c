#define _CRT_SECURE_NO_WARNINGS
#define DEBUG 0
#define UNIT 0101
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable : 4996)

int main()
{
	system("chcp 1251");        
	system("cls");		    
	char current;		    
	int k = 1;		
	void CountingSort(int* e, int n, int min, int max);
	int pos, i, j, n, length, dem=0, min=0, max = 0;    
	int full;                   
	FILE* file;		   
	int sum = 0;
	//		���� ������������ �������			//
	printf("������� ���������� �����: ");
	scanf_s("%d", &n);					// ���������� �����
	int** a = (int**)malloc((n+1) * sizeof(int*));		// ��������� ������ ��� ������ �����
	int* e = (int*)calloc(n, sizeof(int));
	for (int arr = 0; arr < n; arr++)			// �������� �� ����� ������ ������ �������� int � ������ ������

	{
		a[arr] = (int*)malloc(sizeof(int));
	}
	current = getchar();			// ������� �� ����� ������ ����� ����� ���������� �����
	for (i = 0; i < n; i++)
	{
		printf("%d  : ", i + 1);
		current = getchar();			// ���� ������ ������
		for (j = 0; current != '\n'; j++)	// ������ � ���������� �� ����� ������
		{
			if ((current == '1') || (current == '0'))	
			{
				a[i] = (int*)realloc(a[i], sizeof(int) * k);	// ���������� ������ �� ���� ������ (� ������ int k = 1)
				(a[i])[k - 1] = (int)current - '0';		// ���������� �������� � ����� �������
				++k;						//���. ������� ��� ��������� ������
			}
			current = getchar();	// �������� ����� ��������	
		}
		current = '\0';				
		length = k - 1;				// length - ����� �����
		k = 1;					// ����������� int � ��������� ��������
	}
	printf("\n\n");
	//�������� �����
	printf("������� �������� �������: \n");
	scanf("%d", &pos);
	for (j = 0; j < (n + 1); j++)	// ������ � ���������� �� ����� ������
	{
		if ((a[pos - 1])[k - 1] == 1) {
			for (i = 0; i <n; i++) {
				(a[i])[k-1] = '0' - '0';
			}
}
		
		(a[pos - 1])[k - 1] = '0' - '0';
		++k;						//���. ������� ��� ��������� ������
	}
	k = 1;					// ����������� int � ��������� ��������
	// ������������ �� ������� ������� (����� �������� � ��������� �������)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < length; j++) {
			dem = dem + a[i][j];
		}
		if (dem < min) {
			min = dem;
		}
		if (dem > max) {
			max = dem;
		}
		e[i] = dem;
		dem = 0;
	}
//�����  � �������
	printf("\n\n   ");
	for (j = 0; j <= length - 1; j++)
	{
		printf("%3c", j + UNIT);
	}
	printf("\n");
	for (j = 1; j <= ((3 * length) + 7); j++)
	{
		printf("-");
	}
	printf("\n");

	for (i = 0; i < n; i++)
	{
		printf("%i| ", (i+1));
		for (j = 0; j < length; j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	CountingSort(e, n, min, max);
	//			������ � dot ������			//
	if ((file = fopen("Dot_file.txt", "w+b")) == NULL) {	// ������� ���� Dot_file.txt ��� ������
		printf("Cannot open file.\n");			// ���� ������, �� �������� ������
		exit(1);					// ��������� ���������
	}
	fprintf(file, "graph G{\n");				// ��������� ���� �� ����� dot


	int t = -1;				// ������ ������ ������������� �������
	full = 0;				// ������ ���������� ������
	for (i = 0; i < n; i++)
	{
		fprintf(file, "\t%d;\n", (i + 1));
	}
	for (j = 0; j < length; j++)			// ���� �� ��������
	{
		for (i = 0; i < n; i++)				// ���� �� �������
		{
			if ((a[i][j] == 1) && (full > 2))  // ���� � ����� �������  ����� ���� 1, �� �������� ������, �.�. ��� ������������ ����������� ������� �������������
			{
				printf("������ ������� ������ 2 ������� � �������");
				exit(-1);
			}
			else {
				if ((a[i][j] == 1) && (full == 0)) {       // ���������� full = 0;
					fprintf(file, "\t%d", (i + 1));	 // ���� ����� ������� ������� � �������, �� ���������� � ����
					fprintf(file, " -- ");
					full++;				 // ���. full ��� ������ ������ �������
					t = i;				 // ������ ������ ������� ����� i
				}
				else {

					if ((a[i][j] == 1) && (full == 1)) {      // ���� ����� ��� ������� � ��� ���� ������� (full = 1)
					
						fprintf(file, "%d", (i + 1));	 // �������� � ������������ � ��������
						fprintf(file, " [label=%c];\n", (j + UNIT));
						full++;
					}
				}
			}
		}
		if (t != -1) {
			if (full == 1) {			// ���� ����������� ������ ���� ������� � ������� �� ������ ������� �������� ���� �� ����
				fprintf(file, "\t%d", (t + 1));   // �������� � ��
				fprintf(file, ";\n");
			}
		}
		full = 0;		// �������� �������� ��� ������� ���. �������
		t = -1;
	}
	fprintf(file, "}");
	fclose(file);		// ��������� ����
	system("dot -Tbmp Dot_file.txt -o Dot_file.bmp");	// �������� dot � �������� ��� ���������� 
	// ������� ������ //
	free(a);
	getchar();
	return 0;
}
void CountingSort(int* e, int n, int min, int max) {
	int d = 0, cs = max - min;
	// ������ ���������� ���������� ����������� ���������
	int* count = (int*)malloc(n, sizeof(int) * (cs + 1));
	// ���������� �������� ��������� ������� �� 0
	for (int i = 0; i <= cs; i++)
		count[i] = 0;    
	for (int i = 0; i < n; i++)
		count[e[i] - min]++;
	//����������� ����� ������ �� ������� 
	for (int i = cs; i >= 0; i--) {
		if (count[i] > 0) {
			for (int j = 0; j < n; j++) {
				if ((e[j] == i))
					printf("%2d", j+1);
			}
		}
	}
}