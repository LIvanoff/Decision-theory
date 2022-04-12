#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

float n, p, d;
float str2[10][10];

float setValue()
{ 
	float limit;
	cout << "Введите порог: ";
	cin >> limit;
	return limit;
}

void copyArray(float str1[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			str2[i][k] = str1[i][k];
		}
	}
}

int printSet(float str[10][10])
{
	cout << "    1  2  3  4  5  6  7  8  9  10"<<endl;
	for (int i = 0; i < 10; i++)
	{
		if (i == 9)
		{
			cout << i + 1 << " ";
		}
		else
		{
			cout << " " << i + 1 << " ";
		}
		for (int k = 0; k < 10; k++)
		{
			if (str[i][k] == 0)
			{
				if (i == k)
				{
					cout << " x ";
				}
				else
				{
					cout << " ~ ";
				}
			}
			else if (str[i][k] == 1000000)
			{
				cout << " * ";
			}
			else
			{
				cout << setprecision(2) << str[i][k] << " ";
			}
		}
		cout << endl;
	}
	return 1;
}

int cost(int x)
{
	if (x == 0)
	{
		return 5;
	}
	else if (x == 1 || x == 2)
	{
		return 4;
	}
	else if (x == 3)
	{
		return 3;
	}
	else
	{
		return 2;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int set[10][5] = { {15,12,8,6,4},
						{15,8,12,9,6},
						{15,12,8,6,6},
						{10,12,8,3,2},
						{15,12,12,9,2},
						{10,8,4,6,2},
						{10,4,4,6,4},
						{10,8,8,3,2},
						{10,8,4,6,6},
						{5,4,4,6,6} };
	cout << "------------------\n";
	for (int i = 0; i < 10; i++)
	{
		cout << 'A' << i + 1 << "| ";
		for (int j = 0; j < 5; j++)
		{
			cout << set[i][j] << ' ';
		}
		cout << "\n------------------\n";
	}
	cout << "Вес| 5 4 4 3 2\n";
	cout << "------------------\n";
	cout << "asp| + + + + -\n";

	float str[10][10];

	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			str[i][k] = 0.0;
		}
	}
	cout << endl;
	/*
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if(k==i)
			{
				str[i][k] = 'x';
			}
			else
			{
				str[i][k] = '-';
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			cout << str[i][k];
		}
		cout << endl;
	}*/

	for (int i = 0; i < 9; i++)
	{
		for (int k = i + 1; k < 10; k++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (j != 4)
				{
					if (set[i][j] > set[k][j])
					{
						p += cost(j);
						//cout << " (1p ="<<p << ")";
					}
					else if (set[i][j] < set[k][j])
					{
						n += cost(j);
						//cout << " (1n =" << n << ")";
					}
				}
				else
				{
					if (set[i][j] < set[k][j])
					{
						p += cost(j);
						//cout << " (2p =" << p << ")";
					}
					else if (set[i][j] > set[k][j])
					{
						n += cost(j);
						// << " (2n =" << n << ")";
					}
				}
			}
			if (p > n && n != 0)
			{
				d = p / n;
				//cout << "1 p>n && n!=0" << "d=" << d << "=" << p << "/" << n << " i=" << i << " k=" << k << endl;
				str[i][k] = d;
			}
			else if (n > p && p != 0)
			{
				d = n / p;
				//cout <<"2 n>p && p!=0"<<"d="<< d<<"="<<n<<"/"<<p<<" i="<<i<<" k="<< k << endl;
				str[k][i] = d;
			}
			else if ((p == 0 || n == 0) && p != n)
			{
				if (p == 0)
				{
					//cout << "3 p==0" << "d=" << d << " i=" << i << " k=" << k << endl;
					str[k][i] = 1000000;
				}
				else
				{
					//cout << "4 n==0" << "d=" << d << " i=" << i << " k=" << k << endl;
					str[i][k] = 1000000;
				}
			}
			n = 0;
			p = 0;
			d = 0;

			//cout << " n=" << n << " " << " p=" << p << endl;
		}
	}
	printSet(str);
	cout << endl;
	
	
	for(;;)
	{
		float limit = setValue();
		if(limit ==0)
		{
			break;
		}
		int count = 0;
		copyArray(str);
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (str2[i][k] >= limit)
				{
					//cout << "i = "<<i<<" ";
					count++;
					//cout << count << endl;
				}
				else
				{
					str2[i][k] = 0;
					//cout <<"i"<<i<<" k"<<k <<" (" << str2[i][k] << ")" << endl;
				}
				if (i == k)
				{
					for (int j = 0; j < 10; j++)
					{
						if (str2[j][k] >= limit)
						{
							//cout << "j = " << j << " ";
							count++;
							//cout << count << endl;
						}
						else
						{
							str2[j][k] = 0;
							//cout << "j" << j << " k" << k << " (" << "("<<str2[j][k]<<")"<<endl;

						}
					}
				}
			}
			if (count == 0)
			{
				cout << "Слишком большой порог!!!" << endl;
				break;
			}
			count = 0;
			if (i == 9)
			{
				printSet(str2);
			}
		}
	}
}
