#include <bits/stdc++.h>
using namespace std;

char min1[20];
float minval;

void minimisation(int *,int *,int ,int ,int ,int ,char *);
float GetResult(char *,int);
float calc(float ,float ,char );
/*int main()
{
	/*int operands[10] = {0};
	int operators[4] = {0};
	cout<<"Enter the number of operands: ";
	int n,m,size;
	cin>>n;
	cout<<"Enter the number of operators: ";
	cin>>m;
	cout<<"Enter the operands"<<endl;
	char c;
	for(int i=0;i<n;i++)
	{
		cin>>c;
		operands[c-'0']++;
	}
	cout<<"Enter the operartors"<<endl;
	for(int i=0;i<m;i++)
	{
		cin>>c;
		if(c == '+')
			operators[0]++;
		else if(c == '-')
			operators[1]++;
		else if(c == '*')
			operators[2]++;
		else if(c == '/')
			operators[3]++;
	}
	size = n+m;
	minval = INT_MAX;
	char temp[20];
	minimisation(operands,operators,0,n,m,size,temp);
	for(int i=0;i<size;i++)
	{
		//cout<<"printing"<<endl;
		cout<<min1[i];
	}
	cout<<endl;
	/*char temp[] = {'1','-','2','+','3'};
	int ans = GetResult(temp,9);
	cout<<ans<<endl;*/
	//return 0; 
//}
void minimisation(int operand[],int operators[],int ind,int n,int m,int size,char temp[])
{
	/*cout<<"ind:"<<ind<<endl;
	for(int i=0;i<ind;i++)
		cout<<temp[i];*/
	//cout<<endl;
	if(ind == size)
	{
		float val = GetResult(temp,size);
		if(val < minval)
		{
			minval = val;
			/*for(int i=0;i<size;i++)
				cout<<temp[i];*/
			strcpy(min1,temp);
		}
	}
		else
		{
			if(ind%2 ==  0) //put operand
			{
				for(int i=0;i<=9;i++)
				{
					if(operand[i]>0)
					{
						operand[i]--;
						temp[ind] = i+'0';
						minimisation(operand,operators,ind+1,n,m,size,temp);
						operand[i]++;
					}
				}
			}
			else //put operator
			{
				for(int i=0;i<4;i++)
				{
					if(operators[i]>0)
					{
						operators[i]--;
						if(i == 0)
							temp[ind] = '+';
						else if(i == 1)
							temp[ind] = '-';
						else if(i == 2)
							temp[ind] = '*';
						else if(i == 3)
							temp[ind] = '/';
						minimisation(operand,operators,ind+1,n,m,size,temp);
						operators[i]++;
					}
				}
			}
		}
}
float GetResult(char *eq,int n)
{
	stack<float> st;
	for(int i=0;i<n;i++)
	{
		
		if(eq[i]>='0' && eq[i]<='9')
		{
			st.push(eq[i]-'0');
		}
		else if(eq[i] == '+')
		{
			st.push(-1);
		}
		else if(eq[i] == '-')
			st.push(-2);
		else if(eq[i] == '*')
		{
			float a = st.top();
			st.pop();
			float b = eq[i+1] - '0';
			float ans = calc(a,b,'*');
			st.push(ans);
			i++;
		}
		else if(eq[i] == '/')
		{
			float a = st.top();
			st.pop();
			float b = eq[i+1] - '0';
			float ans = calc(a,b,'/');
			st.push(ans);
			i++;
		}
		//cout<<"char: "<<eq[i]<<" top: "<<st.top()<<endl;
	}
	stack<float> evalst;
	while(!st.empty())
	{
		evalst.push(st.top());
		st.pop();
	}
	float lastval = evalst.top();
	evalst.pop();
	while(!evalst.empty())
	{
		//cout<<lastval<<endl;
		float a = evalst.top();
		evalst.pop();
		if(a == -1)
		{
			float b = evalst.top();
			evalst.pop();
			lastval = calc(b,lastval,'+');
			
		}
		else if(a == -2)
		{
			float b = evalst.top();
			evalst.pop();
			lastval = calc(lastval,b,'-');
		}

	}
	return lastval;
}
float calc(float a,float b,char op)
{
	if(op == '+')
		return a+b;
	else if(op == '-')
		return a-b;
	else if(op == '*')
		return a*b;
	else if(op == '/')
		return a/b;
}