#include "pch.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

static vector<double> V;
static vector<double> sumV;
static vector<double> W;
static vector<double> S;
static vector<double> sumS; // вектор сумм столбцов
static vector<double> P;
static double lambda;
static vector<double> Vk;
static vector<double> sumVk;
static vector<double> Wk;
static vector<double> Sk;
static vector<double> sumSk;
static vector<double> Pk;
static double lambdaK;
static int k = 0;
static vector<double> q;
static vector<double> q1;
static vector<double> q2;
static vector<double> q3;
static vector<double> q4;
static vector<double> q5;
static vector<double> ahp;

static double k0[5][5] = {{1,0.25,0.2,0.2,0.167}, // матрица целей
						{4,1,0.33,0.25,0.142},
						{5,3,1,0.2,0.167}, 
						{5,4,5,1,0.33}, 
						{6,7,6,3,1}};
static double k1[5][5] = {{1,0.2,0.167,1,0.33},
						{5,1,1,5,3},
						{6,1,1,7,5},
						{1,0.2,0.142,1,0.25},
						{3,0.33,0.2,4,1}};
static double k2[5][5] = {{1,0.142,0.125,0.2,0.142},
						{7,1,0.5,3,1},
						{8,2,1,5,4},
						{5,0.33,0.2,1,0.25},
						{7,1,0.25,4,1}};
static double k3[5][5] = {{1,3,0.33,5,4},
						{0.33,1,0.5,6,3},
						{3,2,1,6,5},
						{0.2,0.167,0.167,1,0.5},
						{0.25,0.33,0.2,2,1}};
static double k4[5][5] = {{1,7,3,7,4},
						{0.142,1,0.25,1,0.5},
						{0.33,4,1,5,6},
						{0.142,1,0.2,1,0.33},
						{0.25,2,0.142,3,1}};
static double k5[5][5] = {{1,5,4,6,6},
						{0.2,1,0.5,3,3},
						{0.25,2,1,4,4},
						{0.142,0.33,0.25,1,1},
						{0.142,0.33,0.25,1,1}};
static double goal[5][5] = { {1,3,4,5,6},
						{0.33,1,2,3,4},
						{0.25,0.5,1,2,3},
						{0.2,0.33,0.5,1,2},
						{0.142,0.25,0.33,0.5,1} };
static void clear()
{
	Vk.clear();
	sumVk.clear();
	Wk.clear();
	Sk.clear();
	Pk.clear();
	sumSk.clear();
	lambdaK = 0;
}

static int calc(double array[][5])
{
	double SumS = 0;
	double Sum_row_V = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			V.push_back(array[i][k]);
			if (i == k)
			{
				for (int j = 0; j < 5; j++)
				{
					S.push_back(array[j][k]);
				}
				for(auto c : S)
				{
					SumS += c;
				}
				//cout << "S = " << SumS << endl;
				sumS.push_back(SumS);
				SumS = 0;
				S.clear();
			}
		}
		for (auto c : V)
		{
			Sum_row_V *= c;
		}
		double degree = pow(Sum_row_V, 0.2);
		sumV.push_back(degree);
		//cout << "SumV = " << degree << " "<<endl;
		Sum_row_V = 1;
		V.clear();
		
	}
	double sum = 0; // нормирующий коэффициент ∑Vi
	for (auto c : sumV)
	{
		sum += c;
	}
	for (auto c : sumV) // важность проритетов Wki= Vi /∑Vi
	{
		W.push_back(c / sum);
	}
	for(int i = 0; i<sumS.size() ;i++) // Рj = Sj*Wk
	{
		P.push_back(sumS[i] * W[i]);
	}
	for (int i = 0; i < P.size(); i++) // λmax
	{
		lambda += P[i];
	}
	double consistency = (lambda - 5) / (5 - 1);
	double consistency_rate = consistency / 1.12;
	if(consistency_rate >= 0.1)
	{
		cout << "Матрица целей не является солгасованной! \nВы должны перепрограммировать матрицу целей!";
		return 1;
	}
	return 0;
}

static int calc_crit(double array[][5])
{
	k++;
	double SumSk = 0;
	double Sum_row_Vk = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			Vk.push_back(array[i][k]);
			if (i == k)
			{
				for (int j = 0; j < 5; j++)
				{
					Sk.push_back(array[j][k]);
				}
				for (auto c : Sk)
				{
					SumSk += c;
				}
				sumSk.push_back(SumSk);
				SumSk = 0;
				Sk.clear();
			}
		}
		for (auto c : Vk)
		{
			Sum_row_Vk *= c;
		}
		double in = pow(Sum_row_Vk, 0.2);
		sumVk.push_back(in);
		Sum_row_Vk = 1;
		Vk.clear();

	}
	double sum = 0; // нормирующий коэффициент ∑Vi
	for (auto c : sumVk)
	{
		sum += c;
	}
	for (auto c : sumVk) // важность проритетов Wki= Vi /∑Vi
	{
		Wk.push_back(c / sum);
	}
	for (int i = 0; i < 5; i++) // Рj = Sj*Wk
	{
		Pk.push_back(sumSk[i] * Wk[i]);
	}
	for (int i = 0; i < Pk.size(); i++) // λmax
	{
		lambdaK += Pk[i];
	}
	double consistency = (lambdaK - 5) / (5 - 1);
	double consistency_rate = consistency / 1.12;
	if (consistency_rate >= 0.1)
	{
		cout << "Матрица критерия К"<< k <<" не является солгасованной! \nВы должны перепрограммировать матрицу целей!";
		return 1;
	}
	for(int i = 0; i <1; i++)
	{
		q1.push_back(Wk[i]);
		q2.push_back(Wk[i+1]);
		q3.push_back(Wk[i+2]);
		q4.push_back(Wk[i + 3]);
		q5.push_back(Wk[i + 4]);
	}
	/*
	for(int i = 0; i < 5; i++)
	{
		q.push_back(W[i] * Wk[i]);
	}
	double sum_q = 0;
	for(auto c : q)
	{
		sum_q += c;
	}
	ahp.push_back(sum_q);
	*/
	clear();
	return 0;
}

static int global_priority(vector<double> q_num)
{
	for (int i = 0; i < 5; i++)
	{
		q.push_back(W[i] * q_num[i]);
	}
	double sum_q = 0;
	for (auto c : q)
	{
		sum_q += c;
	}
	cout << "SUM_Q = " << sum_q<<endl;
	ahp.push_back(sum_q);
	q.clear();
	return 0;
}

static void print(double array[][5])
{
	for (int i = 0; i < 5; i++)
	{
		cout << 'A' << i + 1 << "| ";
		for (int j = 0; j < 5; j++)
		{
			cout << array[i][j] << ' ';
		}
		cout << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	if(calc(goal)==1)
	{
		return 1;
	}
	if (calc_crit(k1) == 1)
	{
		return 1;
	}
	if (calc_crit(k2) == 1)
	{
		return 1;
	}
	if (calc_crit(k3) == 1)
	{
		return 1;
	}
	if (calc_crit(k4) == 1)
	{
		return 1;
	}
	if (calc_crit(k5) == 1)
	{
		return 1;
	}
	for(auto c : ahp)
	{
		cout << c << ' ';
	}
	global_priority(q1);
	global_priority(q2);
	global_priority(q3);
	global_priority(q4);
	global_priority(q5);
	vector <double> ::iterator it = max_element(ahp.begin(), ahp.end());
	cout << *it;
	return 0;
}
