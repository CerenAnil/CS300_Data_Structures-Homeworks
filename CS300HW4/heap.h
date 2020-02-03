////
//MOST OF THE IMPLEMENTATION OF HEAP CLASS IS TAKEN FROM https://gist.github.com/truncs/1810804
////
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef heap_h
#define heap_h

struct Job
{
   int jobID;
   int jobDeadline;
   Job(int id, int day): jobID(id), jobDeadline(day) {}
   Job(): jobID(0), jobDeadline(0) {}

   bool operator<(const Job & j) // TODO
	{ 
		return jobDeadline < j.jobDeadline;
	} 

    bool operator>(const Job & j) // TODO
	{ 
		return jobDeadline > j.jobDeadline;
	} 
};

struct Worker
{
    int workerID;
	int jobID;
	int daysLeft;
	Worker(): workerID(0), jobID(0), daysLeft(0) {}
	Worker(int workerid, Job j): workerID(workerid), jobID(j.jobID), daysLeft(j.jobDeadline) {}

    bool operator<(const Worker & w) // TODO
	{
		return daysLeft < w.daysLeft;
	}

    bool operator>(const Worker & w) // TODO
	{
		return daysLeft > w.daysLeft;
	}

    void operator-(const int & d) // TODO
	{
		daysLeft -= d;
	}
};

bool workerIDComparison(const Worker & x, const Worker & y) //checks whether x's ID is smaller than y's ID
{
    return x.workerID < y.workerID;
}
template <class T>
class Heap {
  vector<T> list;

  void bubbleUp();
  void bubbleDown();
  void swap(int child, int parent);
  int getLeftChild(int parent);
  int getRightChild(int parent);
  int getParent(int child);

public:
  Heap();
  void decreaseDay(int day); //TODO
  void insert(T);
  T remove();
  T getMin(); //TODO
  T deleteMin();
  int getSize();
  bool isEmpty(); //TODO

};

template <class T>
T Heap<T> :: deleteMin ()
{
	swap(list.size()-1, 0);
	T minimum = list.back();
	list.pop_back();
    bubbleDown();
    return minimum;

}

template <class T>
Heap<T> :: Heap(){
  
}

template <class T>
int Heap<T> :: getSize(){
  return list.size();
}

template <class T>
void Heap<T>::swap(int child, int parent) {
  T temp;
  temp = list[child];
  list[child] = list[parent];
  list[parent] = temp;
}

template <class T>
int Heap<T> :: getParent(int child) {
  if (child % 2 == 0)
	return (child /2 ) -1;
  else 
	return child/2;
  
}

template <class T>
int Heap<T> :: getLeftChild(int parent){
  return 2*parent +1;
}

template <class T>
int Heap<T> :: getRightChild(int parent){
  return 2 * parent + 2;
}

template <class T>
void Heap<T> :: insert(T value) {

  list.push_back(value);
  bubbleUp();
}

template <class T>
void Heap <T>:: bubbleUp() {
  int child = list.size() - 1;
  int parent = getParent(child);
  
  while (child >=0 && parent >= 0 && list[child] < list[parent] ) {
	
	swap(child, parent);
	child = parent;
	parent = getParent(child);
  }
}

template <class T>
T Heap<T> :: remove() {
  int child = list.size() - 1;
  swap(child, 0);
  
  T value = list.back();
  list.pop_back();
  
  bubbleDown();
  return value;
}

template <class T>
void Heap<T> :: bubbleDown() {
  int parent = 0;

  while (1) {
	int left = getLeftChild(parent);
	int right = getRightChild(parent);
	int length = list.size();
	int smallest = parent;

	if (left < length && list[left] < list[smallest])
	  smallest = left;

	if (right < length && list[right] < list[smallest])
	  smallest = right;

	if (smallest != parent) {
	  swap(smallest, parent);
	  parent = smallest;
	}
	else 
	  break;
  }
}

template <class T>
void Heap<T>::decreaseDay(int decreasedDay) // decreases days of all list of jobs
{
   for(unsigned int i = 0; i < list.size(); i++)
   {
	list[i] - decreasedDay;
   }
}

template <class T>
T Heap<T> :: getMin() //returns minimum element of heap
{
  T min = list[0];
  return min;
}

template <class T>
bool Heap<T>::isEmpty() //checks whether list is empty or not
{
	if(list.size() == 0)
		return true;
	else
		return false;
}

#endif heap_h