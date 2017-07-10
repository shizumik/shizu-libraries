#pragma once

#include"queuewithstack.h"

void Queue::pop()
{
	if (!s2.empty())
		s2.pop();
	else
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
	}
}

int Queue::top()
{
	int ret;
	if (!s2.empty())
	{
		ret = s2.top();
	}
	else
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
		ret = s2.top();
	}
	return ret;
}

void Queue::push(int val)
{
	s1.push(val);
}