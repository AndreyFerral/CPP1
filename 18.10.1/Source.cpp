#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
using std::setw;
using std::endl;
using std::cin;
using std::cout;
using std::ios;

struct NOTEBOOK {
	struct disp_res {
		int x, y;
	};
	disp_res res;
	int f; // частота регенерации
	int memory; // объем памяти
	float d; // размер диагонали дисплея
	int price; // цена
	char model[21]; // наименование

	friend std::ostream& operator << (std::ostream& out, NOTEBOOK& obj) { // Вывод
		return out << obj.model << " " << obj.price << " " << obj.res.x << " " << obj.res.y << " " << obj.f << " " << obj.d << " " << obj.memory << endl;
	}
	friend std::istream& operator >> (std::istream& in, NOTEBOOK& obj) { // Вывод
		cout << "model: "; in >> obj.model;
		cout << "price: "; in >> obj.price;
		cout << "x_res: "; in >> obj.res.x;
		cout << "y_res: "; in >> obj.res.y;
		cout << "freq: "; in >> obj.f;
		cout << "diagonal: "; in >> obj.d;
		cout << "memory: "; in >> obj.memory;
		return in;
	}
};

NOTEBOOK*& Initnoteb(int & size);
void ShowInfo(NOTEBOOK* noteb, int size);
void WriteBinaryFile(NOTEBOOK* noteb, int size);


int main() {
	setlocale(LC_ALL, "ru");

	int size; // размер массива структуры(определяется в Initnoteb())   
	// массив структур записывается в двоичный файл
	try {
		Initnoteb(size);
		ShowInfo(Initnoteb(size), size);
		WriteBinaryFile(Initnoteb(size), size);
	}
	catch (std::exception & ex) {
		cout << ex.what() << endl;
	}

system("pause");
}

NOTEBOOK*& Initnoteb(int & size) {

	NOTEBOOK* temp;
	std::string path = "note.txt";
	std::fstream f;
	f.open(path, ios::in);
	if (!f.is_open())
		throw std::exception("Не удалось открыть файл");
	f >> size;
	temp = new NOTEBOOK[size];

	int i = 0;
	while (!f.eof()) {
		f >> temp[i].model >> temp[i].price >> temp[i].res.x 
		  >> temp[i].res.y >> temp[i].f >> temp[i].d >> temp[i].memory;
		i++;
	}
	f.close();
	return temp;
}


void WriteBinaryFile(NOTEBOOK* noteb, int size) {
		int count = 0;
		int j = 0;
	std::ofstream os("binary.bin");
	std::string s = "\nRazdelitel\n";
	os.write(reinterpret_cast<char*> (&size), sizeof(short));
	for (int i = 0; i < size; i++)
		os.write(reinterpret_cast<char*> (&noteb[i]), sizeof(NOTEBOOK));
	os.write(reinterpret_cast<char*> (&s), sizeof(s));
	for (int i = 0; i < size; i++) if (noteb[i].memory > 1) count++;
	NOTEBOOK *temp = new NOTEBOOK[count];
	for (int i = 0; i < size; i++) if (noteb[i].memory > 1) {
		temp[j] = noteb[i];
		j++;
	}
	std::sort(temp, temp + count, [](NOTEBOOK a, NOTEBOOK b) { return a.d < b.d; });
	for (int i = 0; i < count; i++)
		os.write(reinterpret_cast<char*> (&temp[i]), sizeof(NOTEBOOK));
	/* проверка на сортировку по диагонали экрана
	for (int i = 0; i < count; i++) {
		cout << temp[i];
	}
	*/

	os.close();

}



void ShowInfo(NOTEBOOK* noteb, int size) {
	cout << "Модель\t" << "|     Цена" << "| Разрешение (x, y)" << " | Частота" << " | Диагональ" << " | Объем ЖД" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	for (int i = 0; i < size; i++, noteb++) {
		cout << noteb->model << "\t| "
			<< setw(7) << noteb->price << " | "
			<< setw(7) << noteb->res.x << " | "
			<< setw(7) << noteb->res.y << " | "
			<< setw(4) << noteb->f << " Гц" << " | "
			<< setw(9) << noteb->d << " | "
			<< setw(5) << noteb->memory << " Гб" << endl;
	}
}