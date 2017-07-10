#include <iostream>

#include "queuewithstack.h"

using namespace std;

int main()
{
	Queue q;
	q.push(3);
	q.push(4);
	q.push(5);
	cout << q.top();
	q.pop();
	cout << q.top();
	q.push(4);
	return 0;
}