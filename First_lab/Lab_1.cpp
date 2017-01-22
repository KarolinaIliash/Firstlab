#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void input_from_file(vector<vector<double>>& a);
int gauss(vector<vector<double>> a, vector<double>& answers);
void print_equation(vector<vector<double>> equation);
void swap(int& a, int& b);

int main() {
	vector<vector<double>> equation;
	input_from_file(equation);
	int N = equation.size();
	vector<double>answers;
	cout << "Equation from file:\n";
	print_equation(equation);
	int result = gauss(equation, answers);
	if (result == 10) cout << "An infinite number of solutions" << endl;
	else {
		if (result == 0) cout << "There is no solution" << endl;
		else
			for (int i = 0; i < N; i++)
				cout << "x" << i + 1 << " = " << answers[i] << endl;
	}
	system("pause");
}

void input_from_file(vector<vector<double>>& a) {
	char file_name[20];
	cout << "Enter the name of file" << endl;
	while (true) {
		cin >> file_name;
		ifstream input_file(file_name);
		if (input_file.fail()) cerr << "Error with opening file " << file_name << endl << "Enter the name of file" << endl;
		else { input_file.close(); break; }
	}
	char Temp[20];
	ifstream input_file(file_name);
	input_file >> Temp;
	int N;
	N = atoi(Temp);
	vector<double> row(N + 1);
	double temp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N; j++) {
			input_file >> Temp;
			temp = atof(Temp);
			row[j] = temp;
		}
		a.push_back(row);
	}
	input_file.close();
}

int gauss(vector<vector<double>> a, vector<double>& answers) {
	double eps = 0.000000001;
	int n = a.size();
	answers.resize(n);
	vector<int> what_row(n);
	what_row.assign(n, -1);
	for (int col = 0, row = 0; col < n && row < n; col++) {
		int temp = row;
		for (int i = row; i < n; i++) {
			if (abs(a[temp][col]) < abs(a[i][col]))
				temp = i;
		}
		if (abs(a[temp][col]) < eps)
			continue;
		if (row != temp) {
			for (int i = col; i <= n; i++)
				swap(a[row][i], a[temp][i]);
		}
		what_row[col] = row;
		double c;
		for (int i = 0; i < n; i++) {
			if (i != row) {
				c = a[i][col] / a[row][col];
				for (int j = col; j <= n; j++)
					a[i][j] -= a[row][j] * c;
			}
		}
		++row;
	}
	for (int i = 0; i < n; i++) {
		if (what_row[i] != -1)
			answers[i] = a[what_row[i]][n] / a[what_row[i]][i];
	}
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			sum += answers[j] * a[i][j];
		}
		double u = abs(sum - a[i][n]);

		if (abs(sum - a[i][n]) > eps) {
			answers.resize(0);
			return 0;
		}
	}
	for (int i = 0; i < n; i++)
		if (what_row[i] == -1) {
			answers.resize(0);
			return 10; // infinity
		}
	return 1;
}

void swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void print_equation(vector<vector<double>> equation) {
	int N = equation.size();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++)
			cout << equation[i][j] << "x" << i + 1 << j + 1 << " + ";
		cout << equation[i][N - 1] << "x" << i + 1 << N << " = " << equation[i][N] << endl;
	}
	cout << endl;
}

