#pragma once
#include<string>
#include<iostream>
#include<fstream>

class Mail {
private:
	std::string sender;
	std::string receiver;
	std::string title;
	std::string message;
public:
	Mail() {

	}
	Mail(std::string sender, std::string receiver, std::string title, std::string message) : sender(sender), receiver(receiver), title(title), message(message) {

	}
	friend std::ostream& operator<< (std::ostream& out, const Mail& mail)
	{
		out << "from " + mail.sender + " to " + mail.receiver << '\n';
		out << "title: " + mail.title << '\n';
		out << "-------------------------------------------------" << '\n' << mail.message << '\n' << "-------------------------------------------------" << '\n';
		return out;
	}
	
	friend std::istream& operator>> (std::istream& is, Mail& mail)
	{
		is >> mail.sender >> mail.receiver >> mail.title>>mail.message;
		return is;
	}

	void SetSender(std::string s) {
		this->sender = s;
	}
	std::string GetSender() {
		return this->sender;
	}
	void SetReceiver(std::string s) {
		this->receiver = s;
	}
	std::string GetReceiver() {
		return this->receiver;
	}

	void SetTitle(std::string s) {
		this->title = s;
	}
	std::string GetTitle() {
		return this->title;
	}
	void SetMessage(std::string s) {
		this->message = s;
	}
	std::string GetMessage() {
		return this->message;
	}
	~Mail() {

	}
};


class List {
public:
	Mail info;
	List* next;
	List* prev;
	List() {
		next = NULL;
		prev = NULL;
	}
	List(Mail ml) : info(ml) {
		next = NULL;
		prev = NULL;
	}
	
	List(const List& copy) :
		info(copy.info), next(copy.next), prev(copy.prev)
	{

	}

	List& operator= (const List& drob)
	{
		info = drob.info;
		next = drob.next;
		prev = drob.prev;
		return *this;
	}

	~List() {

	}
};

class Menu {
private:
	List* begin;
	List* end;
	size_t size;
	List* find(int index);
public:
	Menu() {
		begin = NULL;
		end = NULL;
		size = 0;
	}
	Menu(Mail ml) {
		List* tmp = new List(ml);
		end = tmp;
		begin = tmp;
		size = 1;
	}
	
	Menu(List* h) : end(h) {
		List* tmp = new List();
		tmp->info = h->info;
		end = tmp;
		begin = tmp;
		size = 1;
	}
	/*
	List& operator[](int i) {
		if (i > size) {
			std::cout << "Index out of bounds" << std::endl;
			return *head;
		}

		List* tmp = head;
		int j = 0;
		while (j < i) {
			if (tmp->next == NULL) break;
			tmp = tmp->next;
			j++;
		}
		return *tmp;
	}*/

	
	Mail& operator[](int i) {
		if (i > size) {
			std::cout << "Index out of bounds" << std::endl;
			return end->info;
		}

		List* tmp = begin;
		int j = 0;
		while (j<i) {
			if (tmp->next == NULL) break;
			tmp = tmp->next;
			j++;
		}
		return tmp->info;
	}
	List* findMessageByTitle(std::string ftitle);

	size_t getSize();

	void edit(int index, std::string info, std::string newvalue);

	void pushFront(std::string sender, std::string receiver, std::string title, std::string message);

	void print();
	
	void readFile(std::string fileName);

	void printFile(std::string fileName);

	void del(int index);

	void freeList();

	~Menu() {
		freeList();
	}
};