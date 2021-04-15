#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mail {
	int index; 
	char from[100];
	char to[100];
	char title[100];
	char message[255];
	struct Mail* next;
	struct Mail* prev;
} Mail;

void print(Mail* head, int N); 
void print2(Mail* head, int* ids);
void printFile(Mail* head, char* file);
Mail* pushFront(Mail* head, int index,char* from, char* to, char* title, char* message); //int a, int b (из struct exam)
void insert(Mail* head, int index,char* from, char* to, char* title, char* message);
void del(Mail* head, int index);
void edit(Mail* head, int index,char* info/*"from,to,title,message"*/, char* newvalue);
Mail* find(Mail* head, int index);
int* findByTitle(Mail* head, char* value);
int* findBySender(Mail* head, char* value);
int* findByReceiver(Mail* head, char* value);
int size(Mail* head);
void freeList(Mail* head);