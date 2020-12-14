#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <locale.h> 
#include <Windows.h> 
#include <iomanip>
#include <fstream> 
#include <stdlib.h> 
#include <cstring> 
#include <string> 
#include <conio.h>
#include <shellapi.h>
#include <map>
#include <vector>
using namespace std;
template <typename T>
void check(T& i) {
	while (true) {
		cin >> i;
		if (!cin) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите корректное значение: ";
		}
		else break;
	}
}
namespace transportation {
	class Location {
	protected:
		string place;
	public:
		string places[12] = { "A100", "Белорусьнефть", "Газпром", "Лукойл", "Эффектлига", "Гусар-сервис", "Флайлвил", "WCC", "GAS", "Заправка", "Ремонт", "Тюннинг" };
		void setPlace() {
			cout << "Введите место расходов: ";
			while (true) {
				check<string>(place);
				bool temp = true;
				for (int i = 0; i < 20; i++)
				{
					if (place == places[i])
					{
						temp = false;
					}
				}
				break;
			}
		}
	};
	class TypeOfExpenses {
	protected:
		double costt;// costt -> cost
		string typeofExpenses;
	public:
		TypeOfExpenses() {
			this->costt = 0; // costt -> cost
		}
		virtual void setCostt() = 0;
		friend class Expenses;//purchase -> expenses
	};
	class Refill : public virtual TypeOfExpenses { //pain->refill
	
		double volume, cost;
		string typeOfPetrol;
	public:

		void setCostt()
		{
			cout << "Введите объём топлива(до 100.00), стоимость 1 литра(до 3.00), тип топлива: ";
			while (true) {
				cin >> volume>>cost;
				check<string>(typeOfPetrol);
				if ((!cin) || (cost < 0) || (cost > (double)3)) {
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите корректное значение(от 0 до 3.00): ";
				}
				if ((!cin) || (volume < 0) || (volume > (double)100)) {
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите корректное значение(от 0 до 100.00): ";
				}
				else break;
			}

			costt = volume * cost;
		}
	};
	class Repair : public virtual TypeOfExpenses {
	public:
		void setCostt()
		{
			cout << "Введите стоимость ремонта(до 10000): ";
			while (true) {
				cin >> costt;
				if ((!cin) || (costt < 0) || (costt > 10000)) {
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите корректное значение(от 0 до 10000): ";
				}
				else break;
			}
		}
	};
	class Tunning : public virtual TypeOfExpenses {
	public:
		void setCostt()
		{
			cout << "Введите стоимость тюнинга(до 5000): ";
			while (true) {
				cin >> costt;
				if ((!cin) || (costt < 0) || (costt > 5000)) {
					cin.clear();
					while (cin.get() != '\n');
					cout << "Введите корректное значение(от 0 до 5000): ";
				}
				else break;
			}
		}
	};
	class Date {
	protected:
		int d, m, y;
	public:
		void setDate() {
			cout << "Введите дату" << endl;
			while (true) {
				cout << "Введите год(2020-2025): ";
				cin >> y;
				if ((!cin) || (y < 2020) || (y > 2025)) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else break;
			}
			while (true) {
				cout << "Введите месяц: ";
				cin >> m;
				if ((!cin) || (m > 12) || (m < 1)) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else break;
			}
			while (true) {
				cout << "Введите день: ";
				cin >> d;
				if ((!cin) || (d < 1) || (((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) && (d > 31))) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else if ((!cin) || (d < 1) || (((m == 4) || (m == 6) || (m == 9) || (m == 11)) && (d > 30))) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else if ((!cin) || (d < 1) || ((m == 2) && (y % 4 != 0) && (d > 28))) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else if ((!cin) || (d < 1) || ((m == 2) && (y % 4 == 0) && (d > 29))) {
					cin.clear();
					while (cin.get() != '\n');
				}
				else break;
			}
		}
	};
	template <typename T>
	class Temp {
	private:
		T value0[100], value1[100], value2[100], value3[100];
	public:
		void tabl() {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tabl.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			int count = 0, f = 1;
			while (in >> value0[f] >> value1[f] >> value2[f] >> value3[f]) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tabl.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> value0[f] >> value1[f] >> value2[f] >> value3[f];
			}
			in_new.close();
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
			cout << setw(4) << left << "|№" << setw(17) << left << "|Пункт назначения" << setw(10) << left << "|Самолет" << setw(10) << left << "|Поезд" << setw(10) << left << "|Авто" << setw(4) << left << "|№" << setw(17) << left << "|Пункт назначения" << setw(10) << left << "|Самолет" << setw(10) << left << "|Поезд" << setw(10) << left << "|Авто" << "|" << endl;
			for (int f = 1; f <= count - 10; f++) {
				cout << "|---|----------------|---------|---------|---------|---|----------------|---------|---------|---------|" << endl;
				cout << "|" << setw(3) << f << setw(17) << "|" + value0[f] << "|" << setw(9) << value1[f] + "$" << "|" << setw(9) << value2[f] + "$" << "|" << setw(9) << value3[f] + "$";
				cout << "|" << setw(3) << f + 10 << setw(17) << "|" + value0[f + 10] << "|" << setw(9) << value1[f + 10] + "$" << "|" << setw(9) << value2[f + 10] + "$" << "|" << setw(9) << value3[f + 10] + "$" << "|" << endl;
			}
			cout << "-------------------------------------------------------------------------------------------------------" << endl << endl;
		}
	};
	class Expenses : public Refill, public Repair, public Tunning, public Date, public Location {
	private:
		int id;
		string status;
	public:
		void setCostt() {
			cout << "Нельзя изменить стоимость." << endl;
		}
		bool operator >(Expenses time)
		{
			if (this->y > time.y)
				return true;
			else if ((this->y == time.y) && (this->m > time.m))
				return true;
			else if ((this->y == time.y) && (this->m == time.m) && (this->d > time.d))
				return true;
			return false;
		}
		void add(int p)// what is p
		{
			setPlace();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tabl.txt", ios_base::app);
			if (!in_new) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			string places[100],typeofExpenses[100];
			double t_cost[100];
			int   count = 0, f = 1;
			while (in_new >> places[f] >> t_cost[f] >> typeofExpenses[f] ) {
				count++;
				f++;
			}
			in_new.close();
			ifstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tabl.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> places[f] >> t_cost[f] >> typeofExpenses[f];
			}
			in_new2.close();
			double temp;
			for (int i = 1; i <= count; i++)
			{
				if (place == places[i])
				{
					temp = t_cost[i];
					
				}
			}
			TypeOfExpenses* point = 0;
			Refill refill;
			Repair repair;
			Tunning tunning;
			cout << "Выберите тип расходов" << endl;
			cout << "1.Заправка\n";
			cout << "2.Ремонт\n";
			cout << "3.Тюннинг\n";
			cout << "Введите нужный элемент: ";
			char ch_key;
			cin >> ch_key;
			switch (ch_key) {
			case '1': {
				point = &refill;
				break;
			}
			case '2': {
				point = &repair;
				break;
			}
			case '3': {
				point = &tunning;
				break;
			}
			default:
				cout << "Ввод ошибочен. Повторите ввод.\n";
				break;
			}
			point->setCostt();
			setDate();
			ofstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			int k;
			cout << "Расходы ";
			if (point == &refill) {
				cout<< "на заправку ";
			}
			else if (point == &repair) {
				cout << "на ремонт ";
			}
			else if (point == &tunning) {
				cout << "на тюннинг ";
			}
			cout << " составят" << point->costt << "$. Чтобы подтвердить введите 1: ";
			cin >> k;
			cout << endl;
			if (k == 1) {
				in << place << " ";
				if (point == &refill) {
					in << "Refill ";
				}
				else if (point == &repair) {
					in << "Repair ";
				}
				else if (point == &tunning) {
					in << "Tunning ";
				}
				in << point->costt << " ";
				in << d << " " << m << " " << y << " ";
				/*if (point == &refill) {
					in << point->costt << " ";
				}
				else if (point == &repair) {
					in << point->costt << " ";
				}
				else if (point == &tunning) {
					in << point->costt << " ";
				}*/
				in << "оплачен";
				in << "- " << p << endl;
				in.close();
			}
		}
		void sor() {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses div[100], temp;
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			cout << "1.Сортировка по месту расходов\n";
			cout << "2.Сортировка по дате \n";
			cout << "3.Сортировка по ID пользователя\n";
			cout << "Введите нужный элемент: ";
			char ch_key;
			cin >> ch_key;
			cout << endl;
			switch (ch_key) {
			case '1': {
				for (int i = 1; i < count + 1; i++) {
					for (int j = count; j > i; j--) {
						if (div[i].place > div[j].place) {
							temp = div[i];
							div[i] = div[j];
							div[j] = temp;
						}
					}
				}
				break;
			}
			case '2': {
				for (int i = 1; i < count + 1; i++) {
					for (int j = count; j > i; j--) {
						if (div[i] > div[j]) {
							temp = div[i];
							div[i] = div[j];
							div[j] = temp;
						}

					}
				}
				break;
			}
			case '3': {
				for (int i = 1; i < count + 1; i++) {
					for (int j = count; j > i; j--) {
						if (div[i].id > div[j].id) {
							temp = div[i];
							div[i] = div[j];
							div[j] = temp;
						}
					}
				}
				break;
			}
			default: {
				system("cls");
				cout << "Ввод ошибочен. Повторите ввод.\n";
				break;
			}
			}
			cout << "----------------------------------------------------------------------------------------------------------------" << endl;
			cout << setw(3) << left << "|№" << setw(17) << left << "|Место" << setw(15) << left << "| Вид расходов" << setw(15) << left << "| Стоимость" << setw(15) << left << "|Дата "  << setw(15) << left << "| Статус" << setw(15) << left << "|id пользователя|" << endl;
			for (int f = 1; f <= count; f++) {
				cout << "|--|----------------|--------------|--------------|--------------|--------------|--------------|-----------------|" << endl;
				cout << "|" << setw(2) << f << setw(17) << "| " + div[f].place << setw(15) << "| " + div[f].typeofExpenses << "| " << setw(13) << div[f].costt << "| ";
				if (div[f].d < 10)
					cout << "0" << div[f].d;
				else cout << div[f].d;
				cout << ".";
				if (div[f].m < 10)
					cout << "0" << div[f].m;
				else cout << div[f].m;
				cout << "." << div[f].y << "      | " <<  setw(13) << div[f].status << "| " << setw(14) << div[f].id << "|" << endl;
			}
			cout << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
		}
		void red() {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::trunc);// zachaem eto?
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);// zachaem eto?
			int key;
			cout << "Какой запись желаете изменить?: ";
			check(key);
			cout << endl;
			for (int f = 1; f <= count; f++) {
				if (f != key) {
					in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y << " " << div[f].status << " " << div[f].id << endl;
				}
				if (f == key) {
					Expenses a;
					a.add(div[f].id);
				}
			}
			in_new2.close();
			delete[] div;
		}
		void red(int p) {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::trunc);
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			int key;
			cout << "Какой заказ желаете изменить?: ";
			check(key);
			cout << endl;
			for (int f = 1, k = 1; f <= count; f++) {
				if (p == div[f].id)
				{
					if (k != key) {
						in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y <<  " " << div[f].status << " " << div[f].id << endl;
					}
					if (k == key) {
						Expenses a;
						a.add(p);
					}
					k++;
				}
				else in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y << " "  << div[f].status << " " << div[f].id << endl;
			}
			in_new2.close();
			delete[] div;
		}
		void del(int p)
		{
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::trunc);
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			int key;
			cout << "Какую запись желаете удалить?: ";
			check(key);
			cout << endl;
			for (int f = 1, k = 1; f <= count; f++) {
				if (p == div[f].id)
				{
					if (k != key) {
						in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y <<  " " << div[f].status << " " << div[f].id << endl;
					}
					k++;
				}
				else in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y << " "  << div[f].status << " " << div[f].id << endl;
			}
			in_new2.close();
			delete[] div;
		}
		void del() {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::trunc);
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			int key;
			cout << "Какой заказ желаете удалить?: ";
			check(key);
			cout << endl;
			for (int f = 1; f <= count; f++) {
				if (f != key) {
					in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y << " "  << div[f].status << " " << div[f].id << endl;
				}
			}
			in_new2.close();
			delete[] div;
		}
		void tab(int p) {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			cout << setw(3) << left << "|№" << setw(17) << left << "|Место расходов" << setw(15) << left << "| Вид расходов" << setw(15) << left << "| Затраты" << setw(15) << left << "|Дата " << setw(15) << left  <<  "| Статус" <<setw(15) << left << "| id пользователя|"<< endl;
			int c = 1;
			for (int f = 1; f <= count; f++) {
				if (div[f].id == p)
				{
					cout << "|--|----------------|--------------|--------------|--------------|--------------|----------------|" << endl;
					cout << "|" << setw(2) << f << setw(17) << "| " + div[f].place << setw(15) << "| " + div[f].typeofExpenses << "| " << setw(13) << div[f].costt << "| ";
					if (div[f].d < 10)
						cout << "0" << div[f].d;
					else cout << div[f].d;
					cout << ".";
					if (div[f].m < 10)
						cout << "0" << div[f].m;
					else cout << div[f].m;
					cout << "." << div[f].y  << "   | " << setw(13) << div[f].status << "|"  << setw(13) << div[f].id << "   |" <<  endl;
					c++;
				}
			}
			cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
			delete[] div;
		}
		void tab() {
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			cout << "-------------------------------------------------------------------------------------------------" << endl;
			cout << setw(3) << left << "|№" << setw(17) << left << "|Место расходов" << setw(15) << left << "| Вид расходов" << setw(15) << left << "| Стоимость" << setw(15) << left << "|Дата " << setw(15) << left << "| Статус" << setw(15) << left << "|id пользователя" << "|" << endl;
			for (int f = 1; f <= count; f++) {
				cout << "|--|----------------|--------------|--------------|--------------|--------------|---------------|" << endl;
				cout << "|" << setw(2) << f << setw(17) << "| " + div[f].place << setw(15) << "| " + div[f].typeofExpenses << "| " << setw(13) << div[f].costt << "| ";
				if (div[f].d < 10)
					cout << "0" << div[f].d;
				else cout << div[f].d;
				cout << ".";
				if (div[f].m < 10)
					cout << "0" << div[f].m;
				else cout << div[f].m;
				cout << "." << div[f].y << "   | " << setw(13) << div[f].status << "| " << setw(14) << div[f].id << "|" << endl;
			}
			cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
			delete[] div;
		}
		void red2()
		{
			ifstream in("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			if (!in) {
				cout << "Невозможно открыть файл";
				system("pause");
			}
			Expenses* div = new Expenses[100];
			int count = 0, f = 1;
			while (in >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id) {
				count++;
				f++;
			}
			in.close();
			ifstream in_new("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			for (int f = 1; f <= count; f++) {
				in_new >> div[f].place >> div[f].typeofExpenses >> div[f].costt >> div[f].d >> div[f].m >> div[f].y  >> div[f].status >> div[f].id;
			}
			in_new.close();
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::trunc);
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\tablica.txt", ios_base::app);
			int key;
			cout << "Статус какого заказа желаете изменить?: ";
			check(key);
			cout << endl;
			for (int f = 1; f <= count; f++) {
				if (f != key) {
					in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y << " " << div[f].status << " " << div[f].id << endl;
				}
				if (f == key) {
					in_new2 << div[f].place << " " << div[f].typeofExpenses << " " << div[f].costt << " " << div[f].d << " " << div[f].m << " " << div[f].y;
					cout << "Введите статус расхода" << endl;
					cout << "1.Оплачено" << endl;
					cout << "2.Запланированно" << endl;
					
					cout << "Введите нужный элемент: ";
					char ch_key;
					cin >> ch_key;
					cout << endl;
					switch (ch_key) {
					case '1': {
						in_new2 << " оплачен " << div[f].id << endl;
						break;
					}
					case '2': {
						in_new2 << " в планах " << div[f].id << endl;
						break;
					}
					
					default: {
						system("cls");
						cout << "Ввод ошибочен. Повторите ввод.\n";
						break;
					}
					}
				}
			}
			in_new2.close();
			delete[] div;
		}
	};
}
using namespace transportation;



string crypt(string word, string login) {
	const string KEY = login;
	for (int counter = 0; counter < word.length(); counter++) {
		word[counter] -= (KEY[counter % KEY.length()] - 33) % 159;
		if (word[counter] > 175)
			word[counter] += 49;
		if (word[counter] > 241)
			word[counter] -= 208;
	}
	return word;
}
string decrypt(string word, string login) {
	const string KEY = login;
	for (int counter = 0; counter < word.length(); counter++) {
		word[counter] += (KEY[counter % KEY.length()] - 33) % 159;
		if (word[counter] > 175)
			word[counter] -= 49;
		if (word[counter] > 241)
			word[counter] += 208;
	}
	return word;
}


void shifr_admin() {
	char ch_key;
	bool MENU = true;
	while (MENU) {
		string str1[100], str2[100];
		int k = 1;
		ifstream fin;
		fin.open("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt");
		int i = 1, f = 0;
		while (!fin.eof()) {
			str1[i] = "";
			fin >> str1[i];
			i++;
		}
		cout << "Пользователи:";
		for (int f = 3; f <= i; f++) {
			if ((f + 1) % 2 == 0)
				cout << endl << str1[f];
		}
		cout << endl;
		cout << "1.Добавление пользователя\n";
		cout << "2.Удаление пользователя\n";
		cout << "0.Выход из меню управления пользователями\n";
		cout << "Введите нужный элемент: ";
		check(ch_key);
		cout << endl;
		switch (ch_key) {
		case '1': {
			ofstream file("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt", ios_base::app);
			string name, pas;
			cout << "Введите логин: ";
			cin >> name;
			cout << "Введите пароль: ";
			cin >> pas;
			cout << endl;
			pas = crypt(pas, name);
			file << " " << name << " " << pas << endl;
			break;
		}
		case '2': {
			ofstream in_new1("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt", ios_base::trunc);
			in_new1.close();
			ofstream in_new2("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt", ios_base::app);
			int key;
			cout << "Введите номер пользователя, которого желаете удалить: ";
			check(key);
			cout << endl;
			int r = 0;
			for (int f = 1; f <= i;) {
				if (r != key)
					in_new2 << " " << str1[f] << " " << str1[f + 1] << endl;
				r++;
				f += 2;
			}
			in_new2.close();
			break;
		}
		case '0': {
			MENU = false;
			cout << "Выход из программы\n";
			break;
		}
		default:
			system("cls");
			cout << "Ввод ошибочен. Повторите ввод.\n";
			break;
		}
	}
}
void adminisrator() {
	char i;
	bool MENU2 = true;
	while (MENU2) {
		cout << "Меню\n";
		cout << "1.Изменение записей пользователя\n";
		cout << "2.Удаление записей пользователя\n";
		cout << "3.Просмотр всех расходов пользователей\n";
		cout << "4.Поиск и фильтрация расходов пользователей\n";
		//cout << "5.Просмотр цен на перевозки\n";
		cout << "5.Управление пользователями\n";
		cout << "0.Выход в меню 1-го уровня\n";
		cout << "Выберите необходимый вам пункт меню: ";
		check(i);
		cout << endl;
		Expenses a;
		switch (i) {
		case '1': {
			cout << "Введите статус расхода" << endl;
			cout << "1.Изменение всей информации о расходах" << endl;
			cout << "2.Изменение статуса расхода" << endl;
			cout << "Введите нужный элемент: ";
			char ch_key;
			cin >> ch_key;
			cout << endl;
			switch (ch_key) {
			case '1': {
				a.red();
				break;
			}
			case '2': {
				a.red2();
				break;
			}
			default: {
				system("cls");
				cout << "Ввод ошибочен. Повторите ввод.\n";
				break;
			}
			}
			break;
		}
		case '2': {
			a.del();
			break;
		}
		case '3': {
			a.tab();
			break;
		}
		case '4': {
			a.sor();
			break;
		}
		//case '5': {
		//	//price();
		//	Temp<string> a;
		//	a.tabl();
		//	break;
		//}
		case '5': {
			shifr_admin();
			break;
		}
		case '0': {
			MENU2 = false;
			break;
		}
		default:
			system("cls");
			cout << "Ввод ошибочен. Повторите ввод.\n";
			break;
		}
	}
}
int proverka() {
	string str1[100];
	string str2[2];
	int k = 1;
	int n = 0;
	while (k == 1) {
		ifstream fin;
		fin.open("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt");
		int i = 1, f = 0;
		while (!fin.eof()) {
			fin >> str1[i];
			i++;
		}
		cout << "Введите логин: ";
		cin >> str2[0];
		cout << "Введите пароль: ";
		cin >> str2[1]; //= invisible();
		cout << endl;
		for (int p = 1; p < i; p++) {
			if (str1[p] == str2[0]) {
				str1[p + 1] = decrypt(str1[p + 1], str1[p]);
				if (str1[p + 1] == str2[1]) {
					f = 0;
					n = (p + 1) / 2;
					break;
				}
			}
			else f++;
		}
		if (f == 0) {
			k = 0;
			return n;
		}
		else {
			cout << "Логин или пароль ошибочны. Повторить ввод?(1/0): ";
			cin >> k;
			if (k == 0)
				return n;
		}
		fin.close();
	}
}
void user_menu(int p)
{
	char i;
	bool MENU2 = true;
	while (MENU2) {
		cout << "Меню\n";
		cout << "1.Добавление записи\n";
		cout << "2.Изменение затрат\n";
		cout << "3.Удаление записи\n";
		cout << "4.Просмотр добавленных записей\n";
		cout << "0.Выход в меню 1-го уровня\n";
		cout << "Выберите необходимый вам пункт меню: ";
		cin >> i;
		cout << endl;
		Expenses a;
		switch (i) {
		case '1': {
			a.add(p);
			break;
		}
		case '2': {
			a.red(p);
			break;
		}
		case '3': {
			a.del(p);
			break;
		}
		case '4': {
			a.tab(p);
			break;
		}
		case '0':
			MENU2 = false;
			break;
		default:
			system("cls");
			cout << "Ввод ошибочен. Повторите ввод.\n";
			break;
		}
	}
}
bool proverka_admin() {
	
	string str1[100];
	string str2[100];
	int k = 1;
	while (k == 1) {
		ifstream fin;
		fin.open("C:\\Users\\DELL\\source\\repos\\Cursovaya_transport\\Kurgan\\Transport\\users.txt");
		int i = 1, f = 0;
		while (!fin.eof()) {
			str1[i] = "";
			fin >> str1[i];
			i++;
		}
		str2[k] = "admin";
		cout << "Введите пароль: ";
		cin >> str2[k + 1]; //= invisible();
		for (int p = 1; p < i; p++) {
			if (str1[p] == str2[k]) {
				str2[p + 1] = decrypt(str2[p + 1], str2[p]);
				if (str1[p + 1] == str2[k + 1]) {
					f = 0;
					break;
				}
			}
			else f++;
		}
		if (f == 0) {
			k = 0;
			cout << endl;
			return true;
		}
		else {
			cout << "Пароль ошибочный. Повторить ввод?(1/0): ";
			cin >> k;
			if (k == 0)
				return false;
		}
		fin.close();
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	char ch_key;
	bool MENU = true;
	while (MENU) {
		cout << "Меню\n";
		cout << "1.Вход под администратором\n";
		cout << "2.Вход под пользователем\n";
		cout << "0.Выход из программы\n";
		cout << "Введите нужный элемент: ";
		cin >> ch_key;
		cout << endl;
		switch (ch_key) {
		case '1': {
			cout << "Вход под администратором\n";
			if (proverka_admin() == true)
				adminisrator();
			break;
		}
		case '2': {
			cout << "Вход под пользователем\n";
			int p = proverka();
			if (p > 0)
				user_menu(p);
			break;
		}
		case '0': {
			MENU = false;
			cout << "Выход из программы\n";
			break;
		}
		default:
			system("cls");
			cout << "Ввод ошибочен. Повторите ввод.\n";
			break;
		}
	}
	system("pause");
	return 0;
}