#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Person.h"

Person::Person()
{
	cout << "�������� ����������� ��� ���������� ��� ������� " << this << endl;
	this->name = "�����";
	this->age = 0;
}

Person::Person(string name, int age)
{
	cout << "�������� ����������� � ����������� ��� ������� " << this << endl;
	this->name = name;
	this->age = age;
}

Person::Person(const Person& other)
{
	cout << "�������� ����������� ����������� ��� ������� " << this << endl;
	this->name = other.name;
	this->age = other.age;
}

Person::~Person()
{
	cout << "�������� ���������� ��� ������� " << this << endl;
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
	stream << "���: " << person.name << endl << "�������: " << person.age << "\n\n";
	return stream;
}

istream& operator>>(istream& stream, Person& person)
{
	string name; int age;
	cout << "������� ���: ";
	cin.seekg(cin.eof());
	getline(cin, name);
	cout << "������� �������: ";
	cin >> age;
	person.setName(name);
	person.setAge(age);
	return stream;
}

Student::Student()
{
	this->name = "����� ���������� ����������";
	this->age = 0;
	this->subject = "����";
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
		cout << "�� �������� =(\n\n";
	}
	else
	{
		cout << "��� ������, ���� ����� =)\n\n";
	}
}

ostream& operator<<(ostream& stream, Student& student) 
{
	stream << "���: " << student.name << endl << "�������: " << student.age << endl;
	stream << "�������: " << student.subject << endl << "������: " << student.mark;
	return stream;
}

istream& operator >>(istream& stream, Student& student) 
{
	string subject; int mark;
	cout << "������� �������: ";
	cin.seekg(cin.eof());
	getline(cin, subject);
	cout << "������� ������: ";
	stream >> mark;
	student.setSubject(subject);
	student.setMark(mark);
	return stream;
}