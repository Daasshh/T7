// TASK_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

struct listSupermarket {
	int count;
	union { // Объединения также хранят набор элементов, но что разные элементы занимают в памяти один и тот же участок.
		struct
		{
			char* desserts = NULL;
			char* data = NULL;
		} desserts;//набор переменных
		struct
		{
			char* drinks = NULL;
			char* capacityOfDrink = NULL;
		} drinks;
	};struct listSupermarket* nextSup; listSupermarket() {};// конструктор для структуры
};

char* input(char* obj) {//нужен, чтобы вводить в конструктор массив char
	char c;
	char b;
	int len = 1;
	obj = (char*)malloc(sizeof(char));//malloc предоставляет ячейку памяти, создает указатель на нее и возвращает его
	while (((c = getchar()) != '\n'))//sizeof(char) – размер одного элемента массива. Считывает последовательно вводимые команды
	{
		obj[len - 1] = c;
		len++;
		obj = (char*)realloc(obj, len * sizeof(char));// динамически увеличивает массив
	}
	obj[len - 1] = '\0';
	return obj;
}

void init(int count, char* name, char* data, listSupermarket* mySup)//Инициализация списка для создания корневого узла списка, у которого поле указателя на следующий элемент содержит нулевое значение.
{
	mySup->count = count;
	mySup->desserts.desserts = name;
	mySup->desserts.data = data;
	mySup->nextSup = NULL; // next указатель на следующий список
}

void add(int count, char* base, listSupermarket* mySup) {// передается  count чтобы знать есть ли эл-ты 
	if (strcmp(base, "desserts") == 0) {
		listSupermarket* list = (listSupermarket*)malloc(sizeof(listSupermarket));
		listSupermarket* next;
		printf("Какой десерт вы хотите добавить?\n");
		char* name = NULL;
		name = input(name);
		printf("Введите срок годности: ");
		char* data = NULL;
		data = input(data);
		if (count == 0) {
			init(1, name, data, mySup);// заполняется следующий указатель null
		}
		else { // иначе создаем новый лист и заполняется
			next = mySup->nextSup; // сохранение указателя на следующий узел // следующий эл-т запоминается в null , а вместо null лист и у листа указано на null
			list->count = 1;
			list->desserts.desserts = name;
			list->desserts.data = data;
			list->nextSup = next;
			mySup->nextSup = list;
		}
	}
	else if (strcmp(base, "drinks") == 0) {
		listSupermarket* list = (listSupermarket*)malloc(sizeof(listSupermarket));
		listSupermarket* next;
		printf("Какой напиток вы хотите добавить?\n");
		char* name = NULL;
		name = input(name);
		printf("Введите емкость напитка: ");
		char* data = NULL;
		data = input(data);
		if (count == 0) {
			init(0, name, data, mySup);
		}
		else {
			next = mySup->nextSup;
			list->count = 0;
			list->drinks.drinks = name;
			list->drinks.capacityOfDrink = data;
			list->nextSup = next;
			mySup->nextSup = list;
		}
	}
	else {
		printf("Такой базы данных нет. \n");
	}
}

void print(listSupermarket* mySup, char* base) {// передает название структуры и распечатывает
	listSupermarket* next;
	next = mySup;
	int counter = 0;
	do {
		if (next->count == 1 && strcmp(base, "desserts") == 0) {
			printf("Название десерта[%d]: %s\n", counter, next->desserts.desserts);
			printf("Срок годности: %s\n", next->desserts.data);
			counter++;
		}
		else if (next->count == 0 && strcmp(base, "drinks") == 0) {
			printf("Название напитка[%d]: %s\n", counter, next->drinks.drinks);
			printf("Емкость: %s\n", next->drinks.capacityOfDrink);
			counter++;
		}
		next = next->nextSup;// переход к следующему узлу
	} while (next != NULL);
	if (counter == 0) {
		printf("Такой базы данных нет. \n");
	}
}

listSupermarket* del(listSupermarket* mySup, char* base) {// 
	printf("Какой объект вы хотите удалить?\n");
	char* name = NULL;
	name = input(name);
	listSupermarket* next = mySup;
	listSupermarket* list;
	int counter = 1;
	if (strcmp(base, "desserts") == 0) {
		if (strcmp(next->desserts.desserts, name) == 0 && next->count == 1) {//просматриваем пока не найдем узел, предшествующий lst
			next = mySup->nextSup;
			delete mySup;
			return next;
		}
		while (counter > 0 && next->nextSup != NULL) {// проверка на null у следующего элемента, если найдет, то в лист запоминается указатель на следующий эл-т
			if (strcmp(next->nextSup->desserts.desserts, name) == 0 && next->nextSup->count == 1) {
				list = next->nextSup;
				next->nextSup = next->nextSup->nextSup;// вместо него ставим следующий от него и удаляем то, что запомнили слева
				delete list;
				return mySup; // возвращаем список
			}
			next = next->nextSup;
		}
	}
	else if (strcmp(base, "drinks") == 0) { // тоже самое для другой структуры
		if (strcmp(next->drinks.drinks, name) == 0 && next->count == 0) {
			next = mySup->nextSup;
			delete mySup;
			return next;
		}
		while (counter > 0 && next->nextSup != NULL) {
			if (strcmp(next->nextSup->drinks.drinks, name) == 0 && next->nextSup->count == 0) {
				list = next->nextSup;
				next->nextSup = next->nextSup->nextSup;
				delete list;
				return mySup;
			}
			next = next->nextSup;
		}
	}
	if (counter > 0) {
		printf("Такого элемента нет. \n");
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");
	listSupermarket* mySup = (listSupermarket*)malloc(sizeof(listSupermarket));
	int count = 0;
	while (1) 
	{
		printf("Что вы хотите сделать: add, del, print или end работу ? \n");
			char* act = NULL;
		act = input(act);
		char* base = NULL;
		if (strcmp(act, "add") == 0)
		{
			printf("В какую базу данных вы хотите добавить: desserts, drinks\n");
			base = input(base);
			add(count, base, mySup);
			count++;
		}
		else if (strcmp(act, "del") == 0)
		{
			printf("Из какой базы данных вы хотите удалить: desserts, drinks\n");
			base = input(base);
			mySup = del(mySup, base);
		}
		else if (strcmp(act, "print") == 0)
		{
			printf("Из какой базы данных вы хотите вывести: desserts, drinks\n");
			base = input(base);
			print(mySup, base);
		}
		else if (strcmp(act, "end") == 0)
		{
			delete mySup;
			delete base;
			delete act;
			break;
		}
		else {
			printf("Такой команды не существует.\n");
		}
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
