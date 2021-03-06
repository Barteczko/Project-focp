#include "pch.h"
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include "header.h"

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void login()
{
	string pass = "";
	cout << "\n\n\n\n\n\n\n\t\t\t\t\tVehicle Parking Reservation System Login";
	cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t Enter Password: ";
	char ch = _getch();
	while (ch != 13) //character 13 is enter
	{
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	if (pass == "Bartek") //set password
	{

		cout << "\n\n\n\n\t\t\t\t\t  Access Granted! Welcome To Our System \n\n\n";
		printf("\t\t\t\t\t     Loading  ");

		for (int process = 0; process < 20; process++)
		{
			Sleep(30);
			printf(".");
		}

	}
	else
	{
		cout << "\n\n\n\n\t\t\t\t\t Access denied...Please Try Again!\n";
		system("PAUSE");
		system("CLS");
		login();
	}
}


int main()
{
	login();
	system("CLS");
choice:
	int choice;
	cout << "\n\n\t ====== Vehicle parking reservation system ======";
	cout << "\n\n                                          ";
	cout << " \n\t\t======================";
	cout << "\n\n\t\t  1. Arrival of a vehicle";
	cout << "\n\n\t\t  2. All vehicles parked";
	cout << "\n\n\t\t  3. Total parking charges of all vehicles with details";
	cout << "\n\n\t\t  4. Departure of the vehicle";
	cout << "\n\n\t\t  5. Exit program";
	cout << " \n\n\t\t======================";
	cout << "\n\n";
	cout << "\t\t Your choice : ";
	cin >> choice;

	if (choice == 5)
	{
		cout << "\n\t\t! The program will be terminated...";
		return 0;
	}

	if (choice < 0 || choice > 6)
	{
		system("CLS");
		cout << "\n\n               Invalid input ! Please try again ! " << endl;
		goto choice;
	}
	else
	{
		if (choice == 1)
		{
			ofstream f1("database.txt", ios::binary | ios::out | ios::app);
			x.arrival();
			f1.write((char*)&x, sizeof(x));
			system("Pause");
			system("cls");
			goto choice;
		}
		if (choice == 2)
		{
			ifstream infile("database.txt", ios::binary | ios::in);
			if (infile.read((char *)&x, sizeof(x)))
			{
				do
				{
					cout << "\n";
					x.details();
					cout << "\n";
					cout << endl;
					system("Pause");
					system("cls");
				} while (infile.read((char *)&x, sizeof(x)));

				goto choice;
			}
			else
			{
				cout << "\n\n\t Datebase is empty, you have to input car first\n";
				system("Pause");
				system("cls");
				goto choice;
			}

		}
		if (choice == 3)
		{
			ifstream infile("database.txt", ios::binary | ios::in);
			while (infile.read((char *)&x, sizeof(x)))
			{
				cout << "\n";
				x.costs();
				cout << "\n";
				cout << endl;
				system("Pause");
				system("cls");
			}
			goto choice;
		}
		if (choice == 4)
		{
			x.departure();
			goto choice;
		}
	}
}

void parking::arrival()
{
	system("CLS");

	cout << "\n\n\t\tEnter id of vehicle : ";
	while (!(cin >> id))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\n\n\t\tInvalid input. Enter number from 1 to 8.\n\n\t\t";
	}
	
	cout << "\n\n\t\tEnter the type of vehicle car(1), motorcycle(2), bus(3): ";
	cin >> type;
	while (type<1 || type>3)
	{
		cout << "\n\n\t\tInvalid input. Enter number from 1 to 3.\n\n\t\t";
		cin >> type;
	}
	cout << "\n\n\t\tEnter the car license plate : ";
	cin >> license;
	cout << "\n\n\t\tEnter the check in time(e.g 3,13,21): ";
	cin >> in_t;
	cout << "\n\n\t\tEnter the check out time : ";
	cin >> exit_t;

	if (exit_t >= in_t)
	{
		duration = exit_t - in_t;
	}
	else
	{
		duration = (12 - in_t) + exit_t;
	}
	cout << "\n\n\t\tParking duration : " << duration << endl;
}

void parking::details()
{
	system("cls");
	cout << "\n\n\t\tVehicle id: " << x.id << endl;
	cout << "\n\n\t\tType of vehicle : " << type << endl;
	cout << "\n\n\t\tThe car license plate : " << license << endl;
	cout << "\n\n\t\tThe check in time : " << in_t;
	cout << "\n\n\t\tThe check out time : " << exit_t;
	cout << "\n\n\t\tThe hours Of stay : " << duration;
}

void parking::costs()
{
	system("CLS");
	cout << "\t\n\tVehicle license plate : " << license;
	cout << "\n\t\n\tVehicle park time: " << duration;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\t\n\tThe total expense during parking ";
	cout << duration * 15 << " PLN";
	SetConsoleTextAttribute(hConsole, 15);
}

void parking::departure()
{
	int n;
	system("CLS");
	cout << "\n\n\t\tEnter the vehicle id you want to get depart : ";
	cin >> n;
	ifstream inFile;
	inFile.open("database.txt", ios::binary);
	ofstream outFile;
	outFile.open("temp.txt", ios::out | ios::binary);
	while (inFile.read((char*)&x, sizeof(x)))
	{
		if (x.id != n)
		{
			outFile.write((char*)&x, sizeof(x));
		}
	}
	cout << "\n\n\t\t Vehicle departed";

	inFile.close();
	outFile.close();

	remove("database.txt");
	rename("temp.txt", "database.txt");
}
