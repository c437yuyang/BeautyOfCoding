////网上看到的https://blog.csdn.net/caryaliu/article/details/8097209
//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <string>
//#include <climits>
//#include <cassert>
//using namespace std;
//
//#define MAXN    100  
//class Stack
//{
//public:
//	//构造函数，初始化堆栈：  
//	//|stackTop|指向当前堆栈的顶部元素，  
//	//|maxStackItemIndex|存储当前堆栈中最大元素的index  
//	Stack()
//	{
//		stackTop = -1;
//		maxStackItemIndex = -1;
//	}
//
//	//判断当前堆栈是否为空  
//	bool isEmpty()
//	{
//		return stackTop == -1;
//	}
//
//	//判断当前堆栈是否满  
//	bool isFull()
//	{
//		return stackTop == MAXN - 1;
//	}
//
//	//向堆栈中push元素，  
//	void push(int x)
//	{
//		if (this->isFull())
//		{                //首先检测堆栈空间是否满  
//			cout << "the stack is full now." << endl;
//		}
//		else
//		{
//			stackItem[++stackTop] = x;
//			//如果压入堆栈的值比之前记录的最大值大，那么那之前的最大值记录在  
//			//link2NextMaxItem[stackTop]的位置，把当前最大值在堆栈stackItem  
//			//中的位置用maxStackItemIndex保存  
//			if (x > maxValue())
//			{
//				link2NextMaxItem[stackTop] = maxStackItemIndex;
//				maxStackItemIndex = stackTop;
//			}
//			else
//				link2NextMaxItem[stackTop] = -1;
//		}
//	}
//
//	int pop()
//	{
//		int ret;
//		if (this->isEmpty())
//		{
//			cout << "the stack is empty." << endl;
//		}
//		else
//		{
//			ret = stackItem[stackTop];
//			//如果pop出的值是当前的最大值，那么则需要将之前保存到link2NextMaxItem[stackTop]  
//			//中的最大值取出，更新maxStackItemIndex的值  
//			if (stackTop == maxStackItemIndex)
//			{
//				maxStackItemIndex = link2NextMaxItem[stackTop];
//			}
//		}
//		--stackTop;
//		return ret;
//	}
//
//	//取出堆栈中当前的最大值  
//	int maxValue()
//	{
//		if (maxStackItemIndex >= 0)
//			return stackItem[maxStackItemIndex];
//		else
//		{
//			return INT_MIN;
//		}
//	}
//	void printItems()
//	{
//		for (int i = 0; i <= stackTop; ++i)
//		{
//			cout << " " << stackItem[i];
//		}
//	}
//	void reversePrintItems()
//	{
//		for (int i = stackTop; i >= 0; --i)
//		{
//			cout << " " << stackItem[i];
//		}
//	}
//private:
//	int stackItem[MAXN];
//	int stackTop;
//	int link2NextMaxItem[MAXN];
//	int maxStackItemIndex;
//};
//
//
//class Queue
//{
//public:
//	int maxValue(int x, int y)
//	{
//		if (x > y)
//			return x;
//		else
//			return y;
//	}
//
//	//返回队列中最大值  
//	int max()
//	{
//		return maxValue(stackA.maxValue(), stackB.maxValue());
//	}
//
//	void printQueue()
//	{
//		stackA.reversePrintItems();
//		stackB.printItems();
//		cout << endl;
//	}
//
//	//在队列末尾插入元素  
//	void insertQueue(int x)
//	{
//		stackB.push(x);
//	}
//
//	//删除并返回队首元素,
//	//如果stackA中是空，则先将stackB中的所有元素pop到stackA中，  
//	//这样stackB中先插入的元素就会pop到stackA中的顶部  
//	int deQueue()
//	{
//		if (stackA.isEmpty())
//		{
//			while (!stackB.isEmpty())
//				stackA.push(stackB.pop());
//		}
//		return stackA.pop();
//	}
//private:
//	Stack stackA;    //维护出队列操作  
//	Stack stackB;    //维护入队列操作  
//};
//
//int main()
//{
//	Queue queue;
//	int a[] = { 909, 2, 3, 4, 9, 4, 5, 10, 6 };
//	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
//	{
//		queue.insertQueue(a[i]);
//	}
//	queue.insertQueue(101);
//	cout << "queue maxvalue = " << queue.max() << endl;
//	queue.insertQueue(590);
//	cout << "queue maxvalue = " << queue.max() << endl;
//	queue.printQueue();
//	int deq = queue.deQueue();
//	cout << "deq = " << deq << endl;
//	cout << "queue maxvalue = " << queue.max() << endl;
//}


#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <stack>

//其实就是先用两个栈，实现一个能随时返回最大值的栈MaxStack
//然后再用两个MaxStack实现一个MaxQueue


template<class T>
class MaxStack
{

public:
	MaxStack() = default;
	void push(const T&val)
	{
		data_stack_.push(val);
		if (max_stack_.empty())
			max_stack_.push(val);
		else
		{
			if (val > max_stack_.top())
				max_stack_.push(val);
			else
				max_stack_.push(max_stack_.top());
		}
	}

	T pop()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");

		T& top_val = data_stack_.top();
		data_stack_.pop();
		max_stack_.pop();
		return top_val;
	}

	T& top()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");
		return data_stack_.top();
	}

	T max()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");
		return max_stack_.top();
	}

	bool empty()
	{
		return data_stack_.empty();
	}

	size_t size()
	{
		return data_stack_.size();
	}

private:
	std::stack<T> data_stack_;
	std::stack<T> max_stack_;
};



template<class T, class Comp = std::less<T>>
class MaxMinStack
{
public:
	MaxMinStack() = default;
	void push(const T&val)
	{
		data_stack_.push(val);
		if (max_min_stack_.empty())
			max_min_stack_.push(val);
		else
		{
			//if (val > max_min_stack_.top())
			if (Comp(val,max_min_stack_.top()))
				max_min_stack_.push(val);
			else
				max_min_stack_.push(max_min_stack_.top());
		}
	}

	T pop()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");

		T& top_val = data_stack_.top();
		data_stack_.pop();
		max_min_stack_.pop();
		return top_val;
	}

	T& top()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");
		return data_stack_.top();
	}

	T max()
	{
		if (data_stack_.empty())
			throw std::exception("Empty Stack!!!");
		return max_min_stack_.top();
	}

	bool empty()
	{
		return data_stack_.empty();
	}

	size_t size()
	{
		return data_stack_.size();
	}

private:
	std::stack<T> data_stack_;
	std::stack<T> max_min_stack_;
};


template<class T>
class MaxQueue
{
public:
	void push(const T&val)
	{
		push_stack_.push(val);
	}

	T pop()
	{
		MoveBetweenStack();
		return pop_stack_.pop();
	}

	T& top()
	{
		MoveBetweenStack();
		return pop_stack_.top();
	}

	T max()
	{
		MoveBetweenStack();
		if (!push_stack_.empty())
			return std::max(push_stack_.max(), pop_stack_.max());
		else
			return pop_stack_.max();
	}

	bool empty()
	{
		return push_stack_.empty() && pop_stack_.empty();
	}

	size_t size()
	{
		return push_stack_.size() + pop_stack_.size();
	}

private:
	void MoveBetweenStack()
	{
		if (pop_stack_.empty())
		{
			if (push_stack_.empty())
				throw std::exception("empty stack!!!");
			while (!push_stack_.empty())
				pop_stack_.push(push_stack_.pop());
		}
	}

private:
	MaxStack<T> push_stack_;
	MaxStack<T> pop_stack_;
};


void testMaxStack()
{
	MaxStack<int> maxStack;
	maxStack.push(5);
	maxStack.push(4);
	maxStack.push(6);
	maxStack.push(3);

	assert(maxStack.max() == 6);
	assert(maxStack.top() == 3);
	assert(maxStack.pop() == 3);
	assert(maxStack.max() == 6);
	assert(maxStack.pop() == 6);
	assert(maxStack.max() == 5);
	assert(maxStack.pop() == 4);
	assert(maxStack.max() == 5);
	assert(maxStack.pop() == 5);

}

void testMaxQueue()
{
	MaxQueue<int> maxQueue;

	maxQueue.push(5);
	maxQueue.push(4);
	maxQueue.push(6);
	maxQueue.push(3);

	assert(maxQueue.max() == 6);
	assert(maxQueue.pop() == 5);
	assert(maxQueue.max() == 6);
	assert(maxQueue.top() == 4);
	assert(maxQueue.pop() == 4);
	assert(maxQueue.max() == 6);
	assert(maxQueue.pop() == 6);
	assert(maxQueue.max() == 3);
	assert(maxQueue.pop() == 3);
}



int main()
{
	testMaxStack();
	testMaxQueue();
	return 0;
}