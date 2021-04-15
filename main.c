#include"list.h"
#include<locale.h>
#include <stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]) {
	if (argc < 2)
		return 1;


	char* fileName = argv[1];
	setlocale(LC_ALL, "Russian");


	Mail* head = NULL;

	FILE* mf;
	char to[100],from[100],title[100],message[255];
	char* tostr;
	char* fromstr;
	char* titlestr;
	char* messagestr;
	mf = fopen(fileName, "r");

	if (mf == NULL) { printf("warning\n"); return -1; }

	int ind = 1;
	while (1)
	{
		tostr = fgets(to, sizeof(to), mf);
		fromstr = fgets(from, sizeof(from), mf);
		titlestr = fgets(title, sizeof(title), mf);
		messagestr = fgets(message, sizeof(message), mf);
		if (tostr == NULL || fromstr == NULL || titlestr == NULL || messagestr == NULL)
		{
			if (feof(mf) != 0)
			{
				printf("\nEnd reading file\n");
				break;
			}
			else
			{
				printf("\nFile reading error\n");
				break;
			}
		}
		if (tostr[strlen(tostr) - 1] == '\n') tostr[strlen(tostr) - 1] = '\0';
		if (fromstr[strlen(fromstr) - 1] == '\n') fromstr[strlen(fromstr) - 1] = '\0';
		if (titlestr[strlen(titlestr) - 1] == '\n') titlestr[strlen(titlestr) - 1] = '\0';
		if (messagestr[strlen(messagestr) - 1] == '\n') messagestr[strlen(messagestr) - 1] = '\0';
		head = pushFront(head, ind, tostr, fromstr, titlestr, messagestr);
		ind++;
	}
	if (fclose(mf) == EOF) printf("warning\n");




	int choose = -1;
	while (choose != 8) {
		printf("1. Write mail\n2. Get last N mails\n3. Edit mail\n4. Find by sender\n5. Find by reciever\n6. Find by title\n7. Delete mail\n8. Exit\n");
		scanf("%d", &choose);
		if (choose == 1) {
			char to[100], from[100], title[100], message[255];
			printf("Sender:");
			scanf("%s", &to);
			printf("Reciever:");
			scanf("%s", &from);

			printf("Title:");
			scanf("%s", &title);
			printf("Message:");
			char temp;
			scanf("%c", &temp); // temp statement to clear buffer
			scanf("%[^\n]", message);
			head = pushFront(head, ind, to, from, title, message);
			ind++;
			printFile(head, fileName);
		}
		if (choose == 2) {
			int N;
			printf("Enter number of mails:");
			scanf("%d", &N);
			print(head, N);
			//printFile(head, fileName);
		}
		if (choose == 3) {
			int index;
			char editname[100];
			char value[255];
			scanf("%d", &index);
			printf("Enter edit line: from, to, title, message: ");
			scanf("%s", editname);
			printf("Enter value: ");
			char temp;
			scanf("%c", &temp); 
			scanf("%[^\n]", value);
			edit(head, index, editname, value);
			printFile(head, fileName);
		}
		if(choose == 4) {
			char sender[100];
			scanf("%s", &sender);
			int *r = findBySender(head, sender);
			print2(head, r);
		}
		if (choose == 5) {
			char receiver[100];
			scanf("%s", &receiver);
			int* r = findByReceiver(head, receiver);
			print2(head, r);
		}
		if (choose == 6) {
			char title[100];
			scanf("%s", &title);
			int* r = findByTitle(head, title);
			print2(head, r);
		}

		if (choose == 7) {
			int id;
			printf("Mail ID:");
			scanf("%d", &id);
			
			del(head, id);
			printFile(head, fileName);
		}
		
	}
	freeList(head);
	return 0;
}