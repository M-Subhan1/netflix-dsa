#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
using namespace std;

template <class T> class Queue {
public:
	T* queue;
	int rear, front, size;

	//Constructors
	Queue(int size_) :size(size_), front(0), rear(-1) {
		queue = new T[size];
	}

	Queue() :size(10), front(0), rear(-1){
		queue = new T[size];
	}

    ~Queue(){
        if(queue) delete queue;
    }

	void Enqueue(T); // add an element at the rear end of the queue
	T Dequeue(); // removes and display the element from the front end of the queue
	bool isEmpty(); // checks if the queue is empty or not
	bool isFull(); // checks if the queue is full or not
	void Clear(); //release the memory allocated by queue
	T FirstElement(); // display the contents of first element of queue at front location
};

template <class T> bool Queue<T>::isEmpty()
{
	return (front == 0) && (size == 0); 
}

template <class T> bool Queue<T>::isFull()
{
	return rear == size;
}

template <class T> void Queue<T>::Enqueue(T element)
{
	if (!isFull())
	{
		rear++; 
		queue[rear] = element; //inserting element at end
	}
	else cout << "The queue is full. Operation invalid" << endl;
}

template <class T> T Queue<T>::Dequeue()
{
	if (!isEmpty()) {
		T del_element = queue[front];
		front++; //increment front to point to next element in array
		return del_element;
	}
}

template <class T> T Queue<T>::FirstElement()
{
	if (!isEmpty()) return queue[front]; //display the first element inside the queue
}

template <class T> void Queue<T>::Clear()
{
	if (!isEmpty())
	{
		delete[]queue; 
		size = front = 0; //setting variables to default values
		rear = -1;
	}
}

#endif