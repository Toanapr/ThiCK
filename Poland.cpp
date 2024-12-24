#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

int precedence(char c)
{
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '^')
		return 3;
	return 0;
}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return true;
	return false;
}

string infixToPostfix(string infix)
{
	string posfix = "";
	stack <char> s;

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
			continue;

		if (infix[i] == '(')
		{
			s.push('(');
		}
		else if (isalnum(infix[i]))
		{
			while (i < infix.size() && isdigit(infix[i]) || infix[i] == '.')
			{
				posfix += infix[i];
				i++;
			}
			i--;
			posfix += " ";
		}
		else if (infix[i] == ')')
		{
			while (!s.empty() && s.top() != '(')
			{
				posfix += s.top();
				posfix += " ";
				s.pop();
			}
			s.pop();
		}
		else if (isOperator(infix[i]))
		{
			while (!s.empty() && precedence(infix[i]) <= precedence(s.top()))
			{
				posfix += s.top();
				posfix += " ";
				s.pop();
			}

			s.push(infix[i]);
		}

	}
	while (!s.empty())
	{
		posfix += s.top();
		posfix += " ";
		s.pop();
	}

	return posfix;
}
int cal(string posfix)
{
	stack<int> s;
	stringstream ss(posfix);
	string word;
	while (ss >> word)
	{
		if (word != "+" && word != "-" && word != "*" && word != "/" && word != "^")
			s.push(stoi(word));
		else
		{
			int a = s.top(); s.pop();
			int b = s.top(); s.pop();
			
			if (word == "+")
				s.push(b + a);
			else if (word == "-")
				s.push(b - a);
			else if (word == "*")
				s.push(b * a);
			else if (word == "/")
				s.push(b / a);
			else
				s.push(pow(b, a));
		}
	}
	return s.top();
}
int main()
{
	string infix = "((u+v)^(p*x^3))";
	/*cout << "Nhập biểu thức trung tố: ";
	getline(cin, infix);*/

	string postfix = infixToPostfix(infix);
	cout << postfix << endl;
	// cout << cal(postfix);
	return 0;
}