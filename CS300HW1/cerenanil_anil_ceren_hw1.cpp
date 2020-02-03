#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
	Stack defaultStack;
	Stack tempStack;
	Stack reverseStack;
	Stack reverseStack2;
	Stack deleteStack;
	Stack finalStack;

	string input;

	bool check = true;

	char ch;

	cout << "Write input:" << endl;
	cin >> input;
	
	for (int i = 0; check != false; i++)
	{
		bool comeFrom6 = false;
		if (input.at(i) == '1')
		{
			while (!tempStack.isEmpty())
			{
				ch = tempStack.pop();
				defaultStack.push(ch);
			}
			check = false;
		}
		if (input.at(i) == '2')
		{
			defaultStack.pop();
		}
		if (input.at(i) == '3')
		{
			ch = defaultStack.pop();
			tempStack.push(ch);
		}
		if (input.at(i) == '4')
		{
			if (!tempStack.isEmpty())
			{
				ch = tempStack.pop();
				defaultStack.push(ch);
			}
		}
		if (input.at(i) == '5')
		{
			while (!defaultStack.isEmpty())
			{
				ch = defaultStack.pop();
				reverseStack.push(ch);
			}

			while (!reverseStack.isEmpty())
			{
				ch = reverseStack.pop();
				reverseStack2.push(ch);
			}

			while (!reverseStack2.isEmpty())
			{
				ch = reverseStack2.pop();
				defaultStack.push(ch);
			}

		}
		if (input.at(i) == '6')
		{
			comeFrom6 = true;
			char willBeDeleted = input.at(i + 1);
			if (willBeDeleted == '1' | willBeDeleted == '2' | willBeDeleted == '3' | willBeDeleted == '4' | willBeDeleted == '5' | willBeDeleted == '6' | willBeDeleted == '7' | willBeDeleted == '8' | willBeDeleted == '9' | willBeDeleted == '0')
			{
				i++;
			}
			else
			{
				while (!defaultStack.isEmpty())
				{
					ch = defaultStack.pop();
					if (ch != willBeDeleted)
					{
						deleteStack.push(ch);
					}
				}
				while (!deleteStack.isEmpty())
				{
					ch = deleteStack.pop();
					defaultStack.push(ch);
				}
				i++;
			}

		}

		if (!comeFrom6 && !(input.at(i) == '1' | input.at(i) == '2' | input.at(i) == '3' | input.at(i) == '4' | input.at(i) == '5' | input.at(i) == '6' | input.at(i) == '7' | input.at(i) == '8' | input.at(i) == '9' | input.at(i) == '0'))
		{
			defaultStack.push(input.at(i));
		}
	}

	while (!defaultStack.isEmpty())
	{
		ch = defaultStack.pop();
		finalStack.push(ch);
	}

	finalStack.print();
	return 0;
}

