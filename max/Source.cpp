#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using std::setw;
using std::endl;
using std::cin;
using std::cout;
using std::ios;

struct scan_info {
	char model[25]; // наименование модели
	int price; // цена
	double x_size; // гориз. размер обл. сканировани€
	double y_size; // вертик. размер обл. сканировани€
	int optr; // оптическое разрешение
	int grey; // число градаций серого

	friend std::ostream& operator << (std::ostream& out, scan_info& obj) { // ¬ывод
		return out << obj.model << " " << obj.price << " " << obj.x_size << " "
			<< obj.y_size << " " << obj.optr << " " << obj.grey << endl;
	}
	friend std::istream& operator >> (std::istream& in, scan_info& obj) { // ¬ывод
		cout << "model: "; in >> obj.model;
		cout << "price: "; in >> obj.price;
		cout << "x_size: "; in >> obj.x_size;
		cout << "y_size: "; in >> obj.y_size;
		cout << "optr: "; in >> obj.optr;
		cout << "grey: "; in >> obj.grey;
		return in;
	}
};

int ChangePad(scan_info* pads, int size, int index);
scan_info *& InitPads(int & size);
void ShowPads(scan_info* pads, int size);
int SizeOfChar(char* model);
int SizeOfInt(int number);
void WriteBinaryFile(scan_info* pads, int size);
scan_info*& ReadBinaryFile(int size);

int main()
{
	setlocale(LC_ALL, "ru");
	int index; // номер планшета, который нужно заменить
	int size; // размер массива структуры(определ€етс€ в InitPads())   
	// массив структур записываетс€ в двоичный файл
	try {
		WriteBinaryFile(InitPads(size), size);
	}
	catch (std::exception & ex) {
		cout << ex.what() << endl;
	}
	ShowPads(ReadBinaryFile(size), size);
	while (true) {
		cout << "¬ведите номер записи, который нужно заменить(с нул€): ";
		cin >> index;
		if (!ChangePad(ReadBinaryFile(size), size, index)) {
			ShowPads(ReadBinaryFile(size), size);
		}
		else {
			cout << "«апись не удалось заменить!" << endl;
			break;
		}
	}

	system("pause");
}

scan_info *& InitPads(int & size) {

	scan_info* temp;
	std::string path = "scan_info.txt";
	std::fstream f;
	f.open(path, ios::in);
	if (!f.is_open())
		throw std::exception("Ќе удалось открыть файл");
	f >> size;
	temp = new scan_info[size];

	int i = 0;
	while (!f.eof()) {
		f >> temp[i].model >> temp[i].price >> temp[i].x_size
			>> temp[i].y_size >> temp[i].optr >> temp[i].grey;
		i++;
	}
	f.close();
	return temp;
}
scan_info*& ReadBinaryFile(int size) {
	std::ifstream is("binary.bin");
	scan_info* temp = new scan_info[size];
	for (int i = 0; i < size; i++)
		is.read(reinterpret_cast<char*> (&temp[i]), sizeof(scan_info));
	is.close();

	return temp;
}
void ShowPads(scan_info * pads, int size) {
	cout << "model" << setw(15) << "| price" << "   | x_size" << "  | y_size" << "  | optr" << " | grey" << endl;
	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < size; i++, pads++) {
		cout << pads->model << setw(15 - SizeOfChar(pads->model)) << "| "
			<< pads->price << setw(10 - SizeOfInt(pads->price)) << " | "
			<< pads->x_size << setw(10 - SizeOfInt(pads->x_size)) << " | "
			<< pads->y_size << setw(10 - SizeOfInt(pads->y_size)) << " | "
			<< pads->optr << setw(7 - SizeOfInt(pads->optr)) << " | "
			<< pads->grey << endl;
	}
}
int SizeOfChar(char* model)
{
	int i = 0;
	while (model[i] != '\0') i++;
	return i;
}
int SizeOfInt(int number)
{
	int i = 0;
	while (number != 0) {
		number /= 10;
		i++;
	}
	return i;
}
void WriteBinaryFile(scan_info* pads, int size) {
	std::ofstream os("binary.bin");
	for (int i = 0; i < size; i++)
		os.write(reinterpret_cast<char*> (&pads[i]), sizeof(scan_info));
	os.close();
}
int ChangePad(scan_info * pads, int size, int index) {
	if (index < 0 || size <= index) return -1;
	cin >> pads[index];
	WriteBinaryFile(pads, size);
	return 0;
}