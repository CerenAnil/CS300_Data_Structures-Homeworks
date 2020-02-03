#include <iostream>
#include <string>

using namespace std;

#ifndef stack_h
#define stack_h

struct Node { 
	char value; 
	struct Node *next; 
}; 
class Stack{
private:
	
public:
	Stack();
	void push(char newItem);
	char pop();
	bool isEmpty();
	void print();

	struct Node *top;
};
#endif stack_h

Stack::Stack( )
{
	top = NULL;
}


bool Stack::isEmpty( )
{
	return top == NULL;
}

char Stack::pop() {
	if(top==NULL){
		cout << "Stack is empty" << endl;
		return '#';
	}
	else {
		char temp = top->value;
		top = top->next;
		return temp;
	}
}
void Stack::push(char newItem) {
	struct Node* newnode = (struct Node*) malloc(sizeof(struct Node)); 
	newnode->value = newItem; 
	newnode->next = top; 
	top = newnode; 
}

void Stack::print() {
	struct Node* ptr;
	if(top==NULL)
		cout<<"Stack is empty";
	else {   
		ptr = top; 
		while (ptr != NULL) { 
			cout<< ptr->value ; 
			ptr = ptr->next; 
		} 
	}
	cout<<endl;

}