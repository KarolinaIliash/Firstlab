#include<iostream>
#include<vector>

using namespace std;

/*void swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
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


struct test_data {
	vector<vector<double>> input;
	vector<double> answer;
	int expect_return;
};

int main() {
	vector<test_data> data;
	test_data temp;
	vector<double> temp_row;
	temp_row.resize(4);
	temp_row[0] = temp_row[1] = 1;
	temp_row[2] = -1;
	temp_row[3] = 0;
	temp.input.push_back(temp_row);
	temp_row[0] = 2;
	temp_row[1] = -4;
	temp_row[2] = 1;
	temp_row[3] = 3;
	temp.input.push_back(temp_row);
	temp_row[0] = 1;
	temp_row[1] = temp_row[2] = -1;
	temp_row[3] = -4;
	temp.input.push_back(temp_row);
	temp.answer.resize(3);
	temp.answer[0] = 3;
	temp.answer[1] = 2;
	temp.answer[2] = 5;
	temp.expect_return = 1;
	data.push_back(temp);
	temp.input.resize(0);
	temp.answer.resize(0);
	temp_row.resize(5);
	temp_row[0] = 5;
	temp_row[1] = -3;
	temp_row[2] = 2;
	temp_row[3] = -8;
	temp_row[4] = 1;
	temp.input.push_back(temp_row);
	temp_row[0] = temp_row[1] = temp_row[2] = temp_row[3] = 1;
	temp_row[4] = 0;
	temp.input.push_back(temp_row);
	temp_row[0] = 3;
	temp_row[1] = 5;
	temp_row[2] = 1;
	temp_row[3] = 4;
	temp_row[4] = 0;
	temp.input.push_back(temp_row);
	temp_row[0] = 4;
	temp_row[1] = 2;
	temp_row[2] = 3;
	temp_row[3] = 1;
	temp_row[4] = 3;
	temp.input.push_back(temp_row);
	temp.answer.resize(4);
	temp.answer[0] = 7;
	temp.answer[1] = -8;
	temp.answer[2] = -5;
	temp.answer[3] = 6;
	temp.expect_return = 1;
	data.push_back(temp);
	temp.input.resize(0);
	temp_row.resize(4);
	temp_row[0] = temp_row[1] = temp_row[2] = temp_row[3] = 1;
	temp.input.push_back(temp_row);
	temp_row[0] = temp_row[1] = temp_row[2] = 2;
	temp_row[3] = 3;
	temp.input.push_back(temp_row);
	temp_row[0] = temp_row[1] = temp_row[2] = 3;
	temp_row[3] = 4;
	temp.input.push_back(temp_row);
	temp.answer.resize(0);
	temp.expect_return = 0;
	data.push_back(temp);
	temp.input.resize(0);
	temp_row.resize(4);
	temp_row[0] = temp_row[1] = temp_row[2] = temp_row[3] = 1;
	temp.input.push_back(temp_row);
	temp_row[0] = 2;
	temp_row[1] = temp_row[2] = 1;
	temp_row[3] = 2;
	temp.input.push_back(temp_row);
	temp_row[0] = 3;
	temp_row[1] = temp_row[2] = 2;
	temp_row[3] = 3;
	temp.input.push_back(temp_row);
	temp.answer.resize(0);
	temp.expect_return = 10;
	data.push_back(temp);
	int result;
	double eps = 0.000001;
	vector<double> real_answers;
	for (int i = 0; i < data.size(); i++) {
		result = gauss(data[i].input, real_answers);
		cout << "Input matrix:\n";
		for (int k = 0; k < data[i].input.size(); k++) {
			for (int j = 0; j < data[i].input[k].size(); j++)
				cout << data[i].input[k][j] << " ";
			cout << endl;
		}
		cout << "\nAnswers:\n";
		for (int k = 0; k < real_answers.size(); k++)
			cout << real_answers[k] << "  ";
		cout << "\nTrue answers:\n";
		for (int k = 0; k < data[i].answer.size(); k++)
			cout << data[i].answer[k] << "  ";
		cout << "\nAnswer = " << result;
		cout << "\nTrue answer = " << data[i].expect_return;
		if (real_answers.size() != data[i].answer.size() || result != data[i].expect_return)
			cout << "\nFALSE\n\n";
		else {
			double check_number = 0;
			for (int k = 0; k < real_answers.size(); k++)
				check_number += abs(real_answers[k] - data[i].answer[k]);
			if (check_number > eps)
				cout << "\nFALSE\n\n";
			else
				cout << "\nTRUE\n\n";
		}
	}
	system("pause");
}*/