#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const double E = 1e-5;

int main() {
	setlocale(LC_ALL, "ru");
	double Xn, Xk, dx;
	int maxIteration = 1000;
	cout << "Введите Xn, Xk, dx: " << endl; 
	cin >> Xn >> Xk >> dx;

	cout << "|  Аргумент |      Ответ      | Проверка | Кол-во просум. элементов" << endl;
	cout << "---------------------------------------------------------" << endl;

	for (double x = Xn; x < Xk; x += dx)
	{
		bool Result = true;
		int n;
		double check = log(x);
		double sum;
		cout << fixed << setprecision(5);

		if (x < E && x > 0) x = 0;
		double a = x-1;
		sum = a;
		for (n = 0; abs(a) >= E; n++)
		{
			a *= (-1 * (x - 1)*(n + 1)) / (n + 2);
			sum += a;
			if (n == maxIteration) {
				Result = false;
				break;
			}
		}

		if (Result) {
			cout << "|" << setw(10) << x << " | " << setw(15) << sum << " | " << setw(8) << check << " | " << n << endl;
		}
		else {
			cout << "|" << setw(10) << x << setw(20) << " | Ряд расходится! |" << setw(8) << check << endl;
		}
	}
	system("pause");
}

