#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
int temp;
vector<bool> variants = { false, false, false,false,false, false, false,false,false, false };
vector<bool> restriction = { false, false, false,false,false, false, false,false,false, false };
stack<int> stck;
char aspiration(int x)
{
	if(x==0||x==1||x==3)
	{
		return '+';
	}
	else
	{
		return '-';
	}
}
int pareto()
{
	int a = stck.top();
	if(a == temp)
	{
		return 0;
	}
	else
	{
		for(int i = 0 ; i < stck.size(); i++)
		{
			stck.pop();
		}
		return 1;
	}
}
void var(vector<bool> &x)
{
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] == 1)
		{
			cout << 'A' << i + 1 << ' ';
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int set[10][5] = { {0,8,164,51,15},
						{4,10,114,35,20},
						{0,13,109,33,33},
						{0,8,130,25,5},
						{1,7,138,30,10},
						{3,8,131,25,8},
						{4,7,213,45,13},
						{0,7,161,24,10},
						{3,6,167,34,24},
						{0,6,170,31,15} };
	cout << "  | + +  -  +  -\n";
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
	for (int i = 0; i < 9; i++)
	{
		for(int k = i; k < 9;k++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (aspiration(j) == '+')
				{
					if (set[i][j] >= set[k + 1][j] )
					{
						stck.push(0);
					}
					else if (set[i][j] < set[k + 1][j])
					{
						stck.push(1);
					}
				}
				else
				{
					if (set[i][j] <= set[k + 1][j])
					{
						stck.push(0);
					}
					else if (set[i][j] > set[k + 1][j] )
					{
						stck.push(1);
					}
				}
				if (j == 0) { temp = stck.top(); }
				if(j>=1)
				{
					if(pareto()==1)
					{
						j = 4;
					}
					else if (pareto() == 0 && j == 4 )
					{
						variants[i] = true;
					}
				}
			}
		}
	}
	cout << " Множество парето-оптимальных альтернатив: ";
	var(variants);

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "\n\n Сужение множества Парето - оптимальных исходов\n\n";

	//границей кол-ва ассистов будет не менее 3 ассистов
	//границей кол-ва голов будет не менее 8 голов
	for (int i = 0 ; i < 9; i++ )
	{
		for ( int j =0; j < 1; j++ )
		{
			if(set[i][0]>=3 && set[i][1] >= 8)
			{
				restriction[i] = true;
			}
		}
	}
	cout << " Варианты, удовлетворяющие этим ограничениям: ";
	var(restriction);
	cout << "\n Из них оптимальными по	Парето являются: ";
	for( int i = 0; i < restriction.size(); i++)
	{
		if(restriction[i] == variants[i] && restriction[i] == 1 )
		{
			cout << 'A' << i + 1 << ' ';
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "\n\n Субоптимизация на основе исходного множества альтернатив\n\n";

	cout << endl;
}
