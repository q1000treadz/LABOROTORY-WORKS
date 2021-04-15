#include"clasess.h"


List* Menu::find(int index) {
	List* finded = NULL, * tmp = begin;
	int i = 0;
	while (tmp != NULL) {
		std::cout << index << ' ' << i << std::endl;
		if (i == index) {
			finded = tmp;
			break;
		}
		tmp = tmp->next;
		i++;
	}
	return finded;
}

List* Menu::findMessageByTitle(std::string ftitle) {
	List* finded = NULL, * tmp = begin;
	while (tmp != NULL) {
		if (tmp->info.GetTitle() == ftitle) {
			finded = tmp;
			break;
		}
		tmp = tmp->next;
	}
	return finded;
}
void Menu::edit(int index, std::string info, std::string newvalue) {
	List* finded = find(index);
	if (!finded) {
		std::cout << "can't find index: " << index << '\n';
		return;
	}
	if (info == "sender") {
		finded->info.SetSender(newvalue);
	}
	else if (info == "reciever") {
		finded->info.SetReceiver(newvalue);
	}
	else if (info == "title") {
		finded->info.SetTitle(newvalue);
	}
	else if (info == "message") {
		finded->info.SetMessage(newvalue);
	}
	else {
		std::cout << "can't find info string: " << info << '\n';
		return;
	}
}
size_t Menu::getSize() {
	return size;
}

void Menu::pushFront(std::string sender, std::string receiver, std::string title, std::string message) {

	List* tmp = new List(Mail(sender,receiver,title,message));
	tmp->next = NULL;
	tmp->prev = end;

	if (end) {
		end->next = tmp;
		end = tmp;
	}
	else {
		end = tmp;
		begin = tmp;
	}
	size++;
}

void Menu::print() {
	List* tmp = begin;
	int i = 1;
	while (tmp != NULL) {
		std::cout << "MESSAGE " << i << '\n';
		std::cout << tmp->info;
		tmp = tmp->next;
		i++;
	}
}
void Menu::readFile(std::string fileName) {
	std::ifstream in(fileName);
	std::string s,r,t,m;
	if (in.is_open())
	{
		while (1)
		{
			if (std::getline(in, s) && std::getline(in, r) && std::getline(in, t) && std::getline(in, m)) {
				this->pushFront(s, r, t, m);
			}
			else {
				break;
			}
		}
		in.close();
	}
	else {
		std::cout << "Can't open file " << fileName << '\n';
	}

}
void Menu::printFile(std::string fileName) {
	std::ofstream out(fileName);
	if (out.is_open())
	{
		List* tmp = begin;
		int i = 1;
		while (tmp != NULL) {
			out << tmp->info.GetSender() << '\n' << tmp->info.GetReceiver() << '\n' << tmp->info.GetTitle() << '\n' << tmp->info.GetMessage() << '\n';
			tmp = tmp->next;
			i++;
		}
	}
	else {
		std::cout << "Can't open file " << fileName << '\n';
	}
	out.close();
}

void Menu::del(int index) {

	List* finded = find(index);
	if (!finded)
		return;

	if (index == 0) {
		if (size != 1) {
			begin = finded->next;
			finded->next->prev = NULL;
		}
		else {
			begin = NULL;
			end = NULL;
			return;
		}
	}
	else {
		if (finded->prev) {
			finded->prev->next = finded->next;
		}
		if (finded->next) {
			finded->next->prev = finded->prev;
		}
	}
	delete finded;
	size--;

}

void Menu::freeList() {
	List* tmp = begin;
	while (tmp != NULL) {
		List* p = tmp;
		tmp = tmp->next;
		delete p;
	}
	size = 0;
}