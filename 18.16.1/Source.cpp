#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <list>
using namespace std;

class Integer {
protected:
	string numb;
public:
	virtual int operator+(int) = 0;
	virtual int operator-(int) = 0;
	virtual int operator*(int) = 0;
	virtual int operator/(int) = 0;
	virtual void output() = 0;
};

class Decimal : public Integer {
protected:
	int decimal;
public:
	int getDecimal() { return decimal; }

	int operator+(int x) override { return decimal + x; }
	int operator-(int x) override { return decimal - x; }
	int operator*(int x) override { return decimal * x; }
	int operator/(int x) override { return decimal / x; }

	void output() {
		int x = 0;
		//Строка -> число
		istringstream ist(numb);
		ist >> x;
		cout << x << endl;
	}

	Decimal(int x) {
		//Число -> строка
		ostringstream ost;
		ost << x;
		decimal = x;
		numb = /*"dec: " + */ost.str();
	}

	friend ostream& operator << (ostream& os, Decimal& dec) {
		return os << "Идентификатор: " << dec.numb << "\tЗначение: " << dec.decimal;
	}
};

class Binary: public Integer {
protected:
	int bin = 0;
public:
	int getBin() { return bin; }

	int ConvertToBinary(int x) {
		int temp = 0;
		for (int j = 0; x > 0; j++)
		{
			temp += (x % 2) * pow(10.0, j);
			x /= 2;
		}
		return temp;
	}

	int operator+(int x) override { return ConvertToBinary(bin + x); }
	int operator-(int x) override { return ConvertToBinary(bin - x); }
	int operator*(int x) override { return ConvertToBinary(bin * x); }
	int operator/(int x) override { return ConvertToBinary(bin / x); }

	void output() {
		int x = 0;
		//Строка -> число
		istringstream ist(numb);
		ist >> x;
		cout << x << endl;
	}


	Binary(int x) {
		//Число -> строка
		ostringstream ost;
		ost << x;
		numb = ost.str();
		for (int j = 0; x > 0; j++) {
			bin += (x % 10) * pow(2.0, j);
			x /= 10;
		}
	}

	friend ostream& operator << (ostream& os, Binary& bin) {
		return os << "Идентификатор: " << bin.numb << "\tЗначение: " << bin.ConvertToBinary(bin.bin);
	}
};

class Series {
protected:
	list<Decimal> listDecimal;
	list<Binary> listBinary;
public:
	Series(Decimal dec, Binary bin) {
		listDecimal.push_back(dec);
		listBinary.push_back(bin);
	}

	Series(Binary bin) {
		listBinary.push_back(bin);
	}

	Series(Decimal dec) {
		listDecimal.push_back(dec);
	}

	Series() {}

	void operator+=(Decimal dec) {
		listDecimal.push_back(dec);
	}

	void operator+=(Binary bin) {
		listBinary.push_back(bin);
	}

	int OutputSum10value() {
		int sum = 0;
		for (auto el : listDecimal) sum += el.getDecimal();
		return sum;
	}

	Decimal&getDecimalAt(int i) {
		list<Decimal>::iterator at = listDecimal.begin();
		advance(at, i);
			return *at;
	}

	Binary&getBinaryAt(int i) {
		list<Binary>::iterator at = listBinary.begin();
		advance(at, i);
		return *at;
	}
	
	friend ostream& operator << (ostream& os, Series& ser) {
		if (!ser.listDecimal.empty()) {
			for (auto el: ser.listDecimal)
			os << el << endl;
		}

		if (!ser.listBinary.empty()) {
			for (auto el : ser.listBinary)
				os << el << endl;
		}

		os << "\nВывод общей суммы всех десятичных значений: " << ser.OutputSum10value() << endl;
		return os;



	}

};

int main() {
	setlocale(LC_ALL, "Russian");
	int ab;
	Series abc;
	fstream readFile;
	readFile.open("Decimal.txt", ios::in);
	try {
		if (!readFile.is_open())
		throw exception("Не удалось открыть файл\n");
	}
	catch(exception&x) {
		cerr << x.what();
	}
	while (!readFile.eof()) {
		readFile >> ab;
		abc += Decimal(ab);
	}
	readFile.close();
	readFile.open("Binary.txt", ios::in);
	try {
		if (!readFile.is_open())
			throw exception("Не удалось открыть файл\n");
	}
	catch (exception&x) {
		cerr << x.what();
	}
	while (!readFile.eof()) {
		readFile >> ab;
		abc += Binary(ab);
	}
	cout << abc;
	
	
	cout << "\nДесятичные числа\n";	cout << "Сложение: " << abc.getDecimalAt(0) + abc.getDecimalAt(1).getDecimal() << endl;
	cout << "Вычитание: " << abc.getDecimalAt(0) - abc.getDecimalAt(1).getDecimal() << endl;
	cout << "Умножение: " << abc.getDecimalAt(0) * abc.getDecimalAt(1).getDecimal() << endl;
	cout << "Деление: " << abc.getDecimalAt(0) / abc.getDecimalAt(1).getDecimal() << endl;

	cout << "\nДвоичные числа\n";
	cout << "Сложение: " << abc.getBinaryAt(0) + abc.getBinaryAt(1).getBin() << endl;
	cout << "Вычитание: " << abc.getBinaryAt(0) - abc.getBinaryAt(1).getBin() << endl;
	cout << "Умножение: " << abc.getBinaryAt(0) * abc.getBinaryAt(1).getBin() << endl;
	cout << "Деление: " << abc.getBinaryAt(0) / abc.getBinaryAt(1).getBin() << endl;

	
	system("pause");
}