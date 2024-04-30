#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Person.h"

Person::Person()
{
	cout << "Вызвался конструктор без параметров для объекта " << this << endl;
	this->name = "никто";
	this->age = 0;
}

Person::Person(string name, int age)
{
	cout << "Вызвался конструктор с параметрами для объекта " << this << endl;
	this->name = name;
	this->age = age;
}

Person::Person(const Person& other)
{
	cout << "Вызвался конструктор копирования для объекта " << this << endl;
	this->name = other.name;
	this->age = other.age;
}

Person::~Person()
{
	cout << "Вызвался деструктор для объекта " << this << endl;
}

void Person::setName(const string name)
{
	this->name = name;
}

void Person::setAge(const int age)
{
	this->age = age;
}

void Person::operator=(const Person& person)
{
	this->name = person.name;
	this->age = person.age;
}

ostream& operator<<(ostream& stream, Person& person)
{
	stream << "ФИО: " << person.name << endl << "Возраст: " << person.age << "\n\n";
	return stream;
}

istream& operator>>(istream& stream, Person& person)
{
	string name; int age;
	cout << "Введите имя: ";
	cin.seekg(cin.eof());
	getline(cin, name);
	cout << "Введите возраст: ";
	cin >> age;
	person.setName(name);
	person.setAge(age);
	return stream;
}

Student::Student()
{
	this->name = "Никто Никтотович Никтотович";
	this->age = 0;
	this->subject = "Обед";
	this->mark = 5;
}

Student::Student(string name, int age, string subject, int mark)
{
	this->name = name;
	this->age = age;
	this->subject = subject;
	this->mark = mark;
}

void Student::setSubject(string subject)
{
	this->subject = subject;
}

void Student::setMark(int mark)
{
	this->mark = mark;
}

void Student::mark_status() 
{
	if (this->mark < 3)
	{
		cout << "Ты отчислен =(\n\n";
	}
	else
	{
		cout << "Все хорошо, пока учись =)\n\n";
	}
}

ostream& operator<<(ostream& stream, Student& student) 
{
	stream << "Имя: " << student.name << endl << "Возраст: " << student.age << endl;
	stream << "Предмет: " << student.subject << endl << "Оценка: " << student.mark;
	return stream;
}

istream& operator >>(istream& stream, Student& student) 
{
	string subject; int mark;
	cout << "Введите предмет: ";
	cin.seekg(cin.eof());
	getline(cin, subject);
	cout << "Введите оценку: ";
	stream >> mark;
	student.setSubject(subject);
	student.setMark(mark);
	return stream;
}