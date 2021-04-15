#include"clasess.h"
#include<iostream>
#include<locale.h>
using namespace std;
int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "No arguments\n";
		return 1;
	}
	setlocale(LC_ALL, "Russian");
	string fileName = argv[1];
	Menu menu;
	int choose = -1;
	while (choose != 8) {

		printf("1. Write mail\n2. Get mail list\n3. Edit mail\n4. Find by title\n5. Delete mail\n6. Exit\n");
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			cin.ignore(256, '\n');
			string to, from, title, message;
			cout<<"Sender:";
			getline(cin, to);
			cout << "Reciever:";
			getline(cin, from);
			cout << "Title:";
			getline(cin, title);
			cout << "Message:";
			getline(cin, message);

			menu.pushFront(to, from, title, message);
			menu.printFile(fileName);
		}
			break;
		case 2:
			menu.print();
			break;
		case 3:
		{
			int index;
			string editname;
			string value;
			cin >> index;
			printf("Enter edit line: sender, reciever, title, message: ");
			cin >> editname;
			printf("Enter value: ");
			cin >> value;
			menu.edit(index, editname, value);
			menu.printFile(fileName);
		}
			break;
		case 4:
		{
			string title;
			cin >> title;
			List* l = menu.findMessageByTitle(title);
			cout << "MESSAGE" << endl;
			cout << l->info << endl;
		}
			break;
		case 5:
		{
			int id;
			cout << "Mail ID: " << '\n';
			cin >> id;
			menu.del(id);
			menu.printFile(fileName);
		}
			break;
		case 6:
		default:
			break;
		}
	}
	return 0;
}