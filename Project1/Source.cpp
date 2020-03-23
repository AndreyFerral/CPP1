#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double Xn, Xk, dx, a, b, c, d;
	setlocale(LC_ALL, "Rus");
	cout << "¬ведите значение a, b, c, Xn, Xk, dx" << endl;
	cin >> a >> b >> c >> Xn >> Xk >> dx;
	cout.width(7);
	cout << "x";
	cout.width(7);
	cout << "|";
	cout.width(7);
	cout << "y" << endl;
	cout << " ---------------------------- " << endl;
	for (double x = Xn; x < Xk; x += dx)
	{
		if (x + 10 < 0 && b != 0) d = a * x * x - c * x + b;
		else if (x + 10 > 0 && b == 0) d = (x - a) / (x / c);
		else d = (- x) / (a - c);
		
		if ((int(a) | int(b)) & (!(int(a) | int(c)))) {
			cout << setw(7) << setprecision(10) << d << setw(7) << "|" << endl;
		}
		else {
			cout << setw(7) << setprecision(10) << int(d) << setw(7) << "|" << endl;
		}
	}
	system("pause");
}