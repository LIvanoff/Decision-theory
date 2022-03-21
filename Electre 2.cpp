#include <iostream>

using namespace std;

double n, p, d;

int cost(int x)
{
	if(x==0)
	{
		return 5;
	}
	else if(x==1||x==2)
	{
		return 4;
	}
	else if(x==3)
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
						{10,8,4,4,6},
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

	for (int i = 0; i < 9; i++)
	{
		for (int k = i; k < 9; k++)
		{
			for (int j = 0; j < 5; j++)
			{
				if(j!=4)
				{
					if (set[i][j] > set[i + 1][j])
					{
						p += cost(j);
					}
					else if (set[i][j] < set[i + 1][j])
					{
						n += cost(j);
					}
				}
				else
				{
					if (set[i][j] < set[i + 1][j])
					{
						p += cost(j);
					}
					else if (set[i][j] > set[i + 1][j])
					{
						n += cost(j);
					}
				}
			}
			if(p>n && n!=0)
			{
				d = p / n;
			}
			else if(n>p && p!=0)
			{
				d = n / p;
			}
			else if(p == n)
			{
			
			}
			else if(p==0 || n==0)
			{
				if(p==0)
				{
						
				}
				else
				{

				}
			}
		}
	}
}
