#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
//static int dom = 0;
//int d, sm;
int temp;
vector<bool> variants = { false, false, false,false,false, false, false,false,false, false };
//vector<int> pareto;
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
/*
int dominant()
{
	for(int i = 0;i<pareto.size()-2;i++)
	{
		cout << " in i="<<i<<" ";
		if(pareto[i]==0&&pareto[i+1]==1)
		{
			cout << " - i ="<<i<<" ";
			pareto.clear();
			return 1;
		}
		else if (pareto[i] == 1 && pareto[i + 1] == 0)
		{
			cout << " + =" << i << " ";
			pareto.clear();
			return 1;
		}
		else if (pareto.empty()) { continue; }
	}
	return 0;
	
	if(dom%2==0)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
	
}*/
int pareto()
{
	int a = stck.top();
	//cout << "value in stack " << stck.top();
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
						//dom += 2;
						//pareto.push_back(0);
						stck.push(0);
						//d += 1;
						//cout << set[i][j] << '>' << set[k + 1][j] << ' ';
					}
					else if (set[i][j] < set[k + 1][j])
					{
						//dom += 1;
						//pareto.push_back(1);
						stck.push(1);
						//sm += 1;
						//cout << set[i][j] << '<' << set[k + 1][j] << ' ';
					}
				}
				else
				{
					if (set[i][j] <= set[k + 1][j])
					{
						//dom += 2;
						//pareto.push_back(1);
						stck.push(0);
						//d += 1;
						//cout << set[i][j] << '<' << set[k + 1][j] << ' ';
					}
					else if (set[i][j] > set[k + 1][j] )
					{
						//dom += 1;
						//pareto.push_back(0);
						stck.push(1);
						//sm += 1;
						//cout << set[i][j] << '>' << set[k + 1][j] << ' ';
					}
				}
				if (j == 0) { temp = stck.top(); }
				if(j>=1)
				{
					//for (auto c : pareto) { cout << c; }
					//if(dominant()==1)
					if(pareto()==1)
					{
						//cout << "domin = "<<dominant();
						//dom = 0;
						j = 4;
					}
					//else if(dominant()==0 && j==4 && sm != d)
					else if (pareto() == 0 && j == 4 )
					{
						//cout << "pareto() = " <<pareto();
						variants[i] = true;
						//cout << " (A" << i + 1 << ")";
						//pareto.clear();
					}
				}
				//cout << " (" << j << ") ";
			}
			//cout << " k = " << k << " i = " <<i << endl;
		}
	}
	cout << " Множество парето-оптимальных альтернатив: ";
	for(int i = 0; i < variants.size(); i++ )
	{
		if(variants[i]==1)
		{
			cout << 'A' << i + 1 << ' ';
		}
	}
	cout << endl;
}
