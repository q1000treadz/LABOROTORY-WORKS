#include "list.h"
//#pragma warning(disable:4996)
void print(Mail* head, int N) {
	Mail* tmp = head;
	while (tmp != NULL) {
		
		if (N != 0) N--; else break;
		printf("from = %s\nto = %s\ntitle = %s\nmessage = %s\n\n", tmp->from, tmp->to, tmp->title,tmp->message);
		tmp = tmp->next;
	}
}
void print2(Mail* head, int* ids) {
	Mail* tmp = head;
	int t = 0;
	for (int i = 0; i < 10; i++) {
		if (ids[i] != 0) {
			tmp = find(head, ids[i]);
			printf("from = %s\nto = %s\ntitle = %s\nmessage = %s\n\n", tmp->from, tmp->to, tmp->title, tmp->message);
		}
	}
}
void printFile(Mail* head, char* file) {
	FILE* fp;

	fp = fopen(file, "w+");
	if (fp == NULL) { printf("ошибка\n"); return; }
	Mail* tmp = head;
	while (tmp != NULL) {
		fprintf(fp, "%s\n%s\n%s\n%s\n", tmp->from, tmp->to, tmp->title, tmp->message);
		tmp = tmp->next;
	}

	fclose(fp);
}
Mail* pushFront(Mail* head, int index, char* from, char* to, char* title, char* message) {
	Mail* tmp = (Mail*)malloc(sizeof(Mail));

	tmp->index = index;
	strcpy(tmp->from, from);
	strcpy(tmp->to, to);
	strcpy(tmp->title, title);
	strcpy(tmp->message, message);

	tmp->next = head;
	tmp->prev = NULL;

	if (head) { 
		head->prev = tmp;
	}
	return tmp;
}

void insert(Mail* head, int index, char* from, char* to, char* title, char* message) {
	Mail* elemBefore = find(head, index);
	if (!elemBefore)
		return;

	Mail* tmp = (Mail*)malloc(sizeof(Mail));
	tmp->index = index;
	strcpy(tmp->from, from);
	strcpy(tmp->to, to);
	strcpy(tmp->title, title);
	strcpy(tmp->message, message);

	tmp->next = elemBefore->next;
	tmp->prev = elemBefore;

	if (elemBefore->next) {
		elemBefore->next->prev = tmp;
	}
	elemBefore->next = tmp;
}

void freeList(Mail* head) {
	Mail* tmp = head;
	while (tmp != NULL) {
		Mail* p = tmp;
		tmp = tmp->next;
		free(p);
	}
}

void del(Mail* head, int index) {
	Mail* finded = find(head, index);
	if (!finded)
		return;

	if (finded->prev) {
		finded->prev->next = finded->next;
	}
	if (finded->next) {
		finded->next->prev = finded->prev;
	}
	free(finded);
}

Mail* find(Mail* head, int index) {
	Mail* finded = NULL, * tmp = head;

	while (tmp != NULL) {
		if (tmp->index == index) {
			finded = tmp;
			break;
		}
		tmp = tmp->next;
	}
	return finded;
}

int* findByTitle(Mail* head,char* value) {

	static int r[10]; //last ten
	int size = 0;
	Mail* tmp = head;
	while (tmp != NULL) {
		if (strcmp(tmp->title, value) == 0) {
			r[size] = tmp->index;
			size++;
		}
		if (size == 10) break;
		tmp = tmp->next;
	}
	return r;
}
int* findBySender(Mail* head, char* value) {
	static int r[10]; //last ten
	int size = 0;
	Mail* tmp = head;
	while (tmp != NULL) {
		if (strcmp(tmp->from, value) == 0) {
			r[size] = tmp->index;
			size++;
		}
		if (size == 10) break;
		tmp = tmp->next;
	}
	return r;
}
int* findByReceiver(Mail* head, char* value) {
	static int r[10]; //last ten
	int size = 0;
	Mail* tmp = head;
	while (tmp != NULL) {
		if (strcmp(tmp->to, value) == 0) {
			r[size] = tmp->index;
			size++;
		}
		if (size == 10) break;
		tmp = tmp->next;
	}
	return r;
}



void edit(Mail* head, int index, char* info/*"from,to,title,message"*/, char* newvalue) {
	Mail* finded = find(head, index);
	if (!finded) {
		printf("can't find index: %d", index);
		return;
	}
	if (strcmp("to", info)==0)
		strcpy(finded->to, newvalue);
	else if (strcmp("from", info)==0)
		strcpy(finded->from, newvalue);
	else if (strcmp("title", info)==0)
		strcpy(finded->title, newvalue);
	else if (strcmp("message", info)==0)
		strcpy(finded->message, newvalue);
}

int size(Mail* head) {
	Mail* tmp = head;
	int size = 0;
	while (tmp != NULL) {
		size++;
		tmp = tmp->next;
	}
	return size;
}
