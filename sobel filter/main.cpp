#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class Matris
{
public:
	Matris(int rc = 255, int cc = 255) {
		rowCount = rc;
		colCount = cc;

		items = new int*[rowCount];
		int i;
		for (i = 0; i < rowCount; i++) {
			items[i] = new int[colCount];
		}
	}

	void displayItems() {
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				cout << items[i][j];
			}
			cout << endl;
		}
	}

	int getRowCount() { return rowCount; }
	void setRowCount(int rowCount) { this->rowCount = rowCount; }
	int getColCount() { return colCount; }
	void setColCount(int colCount) { this->colCount = colCount; }
	int getItems(int i, int j) { return items[i][j]; }
	void setItems(int i, int j, int count) { this->items[i][j] = count; }

protected:
	int rowCount;
	int colCount;
	int **items;

};

class Goruntu :public Matris {
public:
	Goruntu(int rc = 255, int cc = 255){
		rowCount = rc;
		colCount = cc;

		items = new int*[rowCount];
		int i;
		for (i = 0; i < rowCount; i++) {
			items[i] = new int[colCount];
		}
	}

	void threshold(int sinir = 100) {

		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {

				if (this->items[i][j] >= sinir)
					items[i][j] = 1;
				else
					items[i][j] = 0;
			}
		}
	}

	void sobel() {

		int dikeyS[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
		int yatayS[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

		Matris S;

		int Sx = 0, Sy = 0;
		for (size_t i = 1; i < getRowCount() - 1; i++) {
			for (size_t j = 1; j < getColCount() - 1; j++) {

				Sx += items[i - 1][j - 1] * yatayS[0][0];
				Sx += items[i - 1][j] * yatayS[0][1];
				Sx += items[i - 1][j + 1] * yatayS[0][2];
				Sx += items[i + 1][j - 1] * yatayS[2][0];
				Sx += items[i + 1][j] * yatayS[2][1];
				Sx += items[i + 1][j + 1] * yatayS[2][2];

				Sy += items[i - 1][j - 1] * dikeyS[0][0];
				Sy += items[i - 1][j + 1] * dikeyS[0][2];
				Sy += items[i][j - 1] * dikeyS[1][0];
				Sy += items[i][j + 1] * dikeyS[1][2];
				Sy += items[i + 1][j - 1] * dikeyS[2][0];
				Sy += items[i + 1][j + 1] * dikeyS[2][2];

				S.setItems(i, j, pow(((Sx*Sx) + (Sy*Sy)), 0.5));
				Sx = Sy = 0;

			}
		}
		for (int i = 1; i < getRowCount() - 1; i++) {
			for (int j = 1; j < getColCount() - 1; j++) {

				this->items[0][j] = 0;
				this->items[getRowCount()][j] = 0;
				this->items[i][0] = 0;
				this->items[i][getColCount()] = 0;

				this->items[i][j] = S.getItems(i - 1, j - 1);
			}
		}
	}

	Goruntu operator + (const Goruntu &m)
	{
		Goruntu m1(rowCount, colCount);

		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {

				(this->items[i][j] && m.items[i][j]) == 1 ? m1.items[i][j] = m.items[i][j] : m1.items[i][j] = this->items[i][j] + m.items[i][j];
			}
		}
		return m1;
	}
	Goruntu operator *(const Goruntu m)
	{
		Goruntu m1(rowCount, colCount);//constructor da private erişimi var.
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {

				m1.items[i][j] = this->items[i][j] * m.items[i][j];

			}
		}
		return m1;
	}
	Goruntu operator !()

	{
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < colCount; j++) {
				this->items[i][j] == 1 ? items[i][j] = 0 : items[i][j] = 1;
			}
		}
		return  *this;

	}

};

istream &operator >> (istream  &file, Goruntu &s) {
	file.seekg(0, file.end);
	streamsize length = file.tellg();
	file.seekg(0, file.beg);

	char* buffer = new char[length];
	file.read(buffer, length);

	int horizontal = (((int)buffer[1] + 256) % 256);
	int vertical = (((int)buffer[0] + 256) % 256);

	s.setRowCount(horizontal);
	s.setColCount(vertical);

	int k = 0, l = 0,hold = 0;

	for (int i = 2; i < length; i++) {

		hold = (((int)buffer[i] + 256) % 256);
		s.setItems(k, l,hold );
		l++;
		if (l == s.getColCount()) { k++; l = 0; }
	}

	delete[] buffer;

	return file;
}
ostream &operator << (ostream &file, Goruntu &s) {
	for (int i = 0; i < s.getRowCount(); i++) {
		for (int j = 0; j < s.getColCount(); j++) {

			s.getItems(i, j) == 0 ? file << "-" : file << "*";

		}
		file << "\n";
	}
	return file;
}

int main(int argc, char* argv[]) {

	Goruntu g1, g2, g3;
	ifstream dosya1, dosya2;

	dosya1.open(argv[1], ios::in | ios::binary);
	dosya1 >> g1;
	dosya1.close();
	dosya2.open(argv[2], ios::in | ios::binary);
	dosya2 >> g2;
	dosya2.close();

	g1.sobel();
	g2.sobel();
	g1.threshold();
	g2.threshold();

	g3 = g1 + g2;
	g3 = g1 * g2;
	g3 = !g1;

	ofstream dosya3;
	dosya3.open(argv[3], ios::out | ios::binary);
	if (!dosya3.is_open()) cout << "dosya3 acilmadi";
	dosya3 << g1;
	dosya3.close();

	ofstream dosya4;
	dosya4.open(argv[4], ios::out | ios::binary);
	if (!dosya4.is_open()) cout << "dosya4 acilmadi";
	g3 = g1 + g2;
    dosya4<<g3;
	dosya3.close();

	ofstream dosya5;
	dosya5.open(argv[5], ios::out | ios::binary);
	if (!dosya5.is_open()) cout << "dosya5 acilmadi";
	g3 = !g1;
	dosya5 << g3;

	dosya3.close();



	//getchar();
	return 0;
}
