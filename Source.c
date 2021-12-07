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
	//		Ввод динамической матрицы			//
	printf("Введите количество узлов: ");
	scanf_s("%d", &n);					// количество узлов
	int** a = (int**)malloc((n+1) * sizeof(int*));		// выделение памяти под массив строк
	int* e = (int*)calloc(n, sizeof(int));
	for (int arr = 0; arr < n; arr++)			// выделяем по одной ячейке помяти размером int в каждой строке

	{
		a[arr] = (int*)malloc(sizeof(int));
	}
	current = getchar();			// переход на новую строку после ввода количества узлов
	for (i = 0; i < n; i++)
	{
		printf("%d  : ", i + 1);
		current = getchar();			// берём первый символ
		for (j = 0; current != '\n'; j++)	// читаем с клавиатуры до конца строки
		{
			if ((current == '1') || (current == '0'))	
			{
				a[i] = (int*)realloc(a[i], sizeof(int) * k);	// довыделяем память на один больше (в начале int k = 1)
				(a[i])[k - 1] = (int)current - '0';		// записываем значение в ячёку массива
				++k;						//инк. счетчик для веделения памяти
			}
			current = getchar();	// получаем новое значение	
		}
		current = '\0';				
		length = k - 1;				// length - длина строк
		k = 1;					// присваиваем int к начальное значение
	}
	printf("\n\n");
	//удаление ребер
	printf("Введите заданную вершину: \n");
	scanf("%d", &pos);
	for (j = 0; j < (n + 1); j++)	// читаем с клавиатуры до конца строки
	{
		if ((a[pos - 1])[k - 1] == 1) {
			for (i = 0; i <n; i++) {
				(a[i])[k-1] = '0' - '0';
			}
}
		
		(a[pos - 1])[k - 1] = '0' - '0';
		++k;						//инк. счетчик для веделения памяти
	}
	k = 1;					// присваиваем int к начальное значение
	// Сортирование по степени вершины (поиск минимума и максимума степени)
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
//Вывод  в консоль
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
	//			Работа с dot файлом			//
	if ((file = fopen("Dot_file.txt", "w+b")) == NULL) {	// открыли файл Dot_file.txt для записи
		printf("Cannot open file.\n");			// если ошибка, то печатаем ошибку
		exit(1);					// завершаем программу
	}
	fprintf(file, "graph G{\n");				// заполняем файл на языке dot


	int t = -1;				// индекс первой встретившийся единицы
	full = 0;				// индекс количества единиц
	for (i = 0; i < n; i++)
	{
		fprintf(file, "\t%d;\n", (i + 1));
	}
	for (j = 0; j < length; j++)			// цикл по столбцам
	{
		for (i = 0; i < n; i++)				// цикл по строкам
		{
			if ((a[i][j] == 1) && (full > 2))  // если в одном столбце  более двух 1, то печатаем ошибку, т.к. это противоречит определению матрицы инцидентности
			{
				printf("Нельзя вводить больше 2 единицы в столбце");
				exit(-1);
			}
			else {
				if ((a[i][j] == 1) && (full == 0)) {       // изначально full = 0;
					fprintf(file, "\t%d", (i + 1));	 // если нашли первыую единицу в столбце, то записываем в файл
					fprintf(file, " -- ");
					full++;				 // инк. full для поиска второй единицы
					t = i;				 // индекс первой единицы равен i
				}
				else {

					if ((a[i][j] == 1) && (full == 1)) {      // если нашли еще единицу и уже была единица (full = 1)
					
						fprintf(file, "%d", (i + 1));	 // печатаем в соответствии с форматом
						fprintf(file, " [label=%c];\n", (j + UNIT));
						full++;
					}
				}
			}
		}
		if (t != -1) {
			if (full == 1) {			// если встретилась только одна единица в столбце то значит вершина замкнута сама на себя
				fprintf(file, "\t%d", (t + 1));   // печатаем её же
				fprintf(file, ";\n");
			}
		}
		full = 0;		// обнуляем счётчики для анализа всл. столбца
		t = -1;
	}
	fprintf(file, "}");
	fclose(file);		// закрываем файл
	system("dot -Tbmp Dot_file.txt -o Dot_file.bmp");	// вызываем dot и передаем ему записанный 
	// Очистка памяти //
	free(a);
	getchar();
	return 0;
}
void CountingSort(int* e, int n, int min, int max) {
	int d = 0, cs = max - min;
	// массив сохранения количества присутствия элементов
	int* count = (int*)malloc(n, sizeof(int) * (cs + 1));
	// Передавать значение элементов массива на 0
	for (int i = 0; i <= cs; i++)
		count[i] = 0;    
	for (int i = 0; i < n; i++)
		count[e[i] - min]++;
	//Отображение номер вершин по убываню 
	for (int i = cs; i >= 0; i--) {
		if (count[i] > 0) {
			for (int j = 0; j < n; j++) {
				if ((e[j] == i))
					printf("%2d", j+1);
			}
		}
	}
}