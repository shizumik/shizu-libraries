#pragma once
#ifndef QUEUE_WITH_STACK_H
#define QUEUE_WITH_STACK_H
#include <stack>

class Queue
{
public:
	void push(int val);
	void pop();
	int top();
private:
	std::stack<int> s1;
	std::stack<int> s2;
};
#endif // !QUEUE_WITH_STACK_H
