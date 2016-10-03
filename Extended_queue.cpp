#ifndef EXTENDED_QUEUE
#define EXTENDED_QUEUE
#include <iostream>
#include"Plane.cpp"
#include "utility.cpp"

using namespace std; 

typedef Plane Queue_entry ;

const int maxqueue = 1000; // small value for testing
class Queue {
public:
Queue( );
bool empty( ) const;
Error_code serve( );
Error_code append(const Queue_entry &item);
Error_code retrieve(Queue_entry &item) const;
protected:
int count;
int front, rear;
Queue_entry entry[maxqueue];
};

Queue :: Queue( )
/* Post: The Queue is initialized to be empty. */
{
count = 0;
rear = maxqueue - 1;
front = 0;
}
bool Queue :: empty( ) const
/* Post: Return true if the Queue is empty, otherwise return false. */
{
return count == 0;
}

Error_code Queue :: append(const Queue_entry &item)
/* Post: item is added to the rear of the Queue. If the Queue is full return an
Error_code of overflow and leave the Queue unchanged. */
{
if (count >= maxqueue) return overflow;
count++;
rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
entry[rear] = item;
return success;
}
Error_code Queue :: serve( )
/* Post: The front of the Queue is removed. If the Queue is empty return an
Error_code of underflow. */
{
if (count <= 0) return underflow;
count--;
front = ((front +1) == maxqueue) ? 0 : (front + 1);
return success;
}

Error_code Queue :: retrieve(Queue_entry &item) const
/* Post: The front of the Queue retrieved to the output parameter item. If the
Queue is empty return an Error_code of underflow. */
{
if (count <= 0) return underflow;
item = entry[front];
return success;
}

class Extended_queue: public Queue {
public:
bool full( ) const;
int size( ) const;
void clear( );
Error_code serve_and_retrieve(Queue_entry &item);
};


int Extended_queue::size( ) const
/* Post: Return the number of entries in the Extended_queue. */
{
return count;
}
bool Extended_queue::full() const {
return count==maxqueue;
}
void Extended_queue::clear(){
	int n = count;
	while(n--){
	serve(); 
	}
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
	if (retrieve(item) == success) {
		return serve();
	} else {
		return retrieve(item);
	}
}
#endif
