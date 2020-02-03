#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "heap.h"

using namespace std;

void clearHeap(Heap <Worker> & wHeap, int & curr)
{
	Worker temp;

	while(!wHeap.isEmpty())
	{
		temp = wHeap.deleteMin();
	}

	curr += temp.daysLeft;
	
	cout <<	"All jobs are completed in " << curr << " days.\n";
}

void recursiveStep(int & workerNum, vector <Job> & vecOfJobs, Heap <Worker> & wHeap, unsigned int & i, int & curr) // for the remaining jobs
{
		Worker min = wHeap.deleteMin();
		vector <Worker> readyToWork;
		readyToWork.push_back(min);

		while(!wHeap.isEmpty() && min.daysLeft == wHeap.getMin().daysLeft) //if there are more than 1 available workers
		{
			Worker min2 = wHeap.deleteMin();
			readyToWork.push_back(min2);
		}
		curr = curr + min.daysLeft;
		wHeap.decreaseDay(min.daysLeft);
		sort(readyToWork.begin(), readyToWork.end(), workerIDComparison); //fast sorting algorirthm

		for(unsigned int w = 0; w < readyToWork.size() && i < vecOfJobs.size(); w++, i++)
		{
			Job j = vecOfJobs[i];
			Worker tempWorker = readyToWork[w];

			tempWorker.daysLeft = j.jobDeadline;
			tempWorker.jobID = j.jobID;
			
			wHeap.insert(tempWorker);
			cout << "Job-" << j.jobID << "->Worker-"<< tempWorker.workerID << " (Day: " << curr << ")\n";
		}
}

void firstWorkers(int & workerNum, vector <Job> & vecOfJobs, Heap <Worker> & wHeap, unsigned int & i, int & curr, unsigned int & w) //assign workers' first jobs to all of the workers
{		
		Job j = vecOfJobs[i];
		i++;
		Worker tempWorker(w+1, j);
		wHeap.insert(tempWorker);
		cout << "Job-" << j.jobID << "->Worker-"<< tempWorker.workerID << " (Day: " << curr << ")\n";
}

void fileRead(ifstream & iss, int & jobNum, int &workerNum, vector <Job> & vecOfJobs , int & jobID, int & jobDay) //reads file
{
	iss >> workerNum >> jobNum;

	for( int j = 0; j < jobNum; j++)
	{
		iss >> jobID >> jobDay;
		Job realJob = *new Job(jobID, jobDay);
		vecOfJobs.push_back(realJob);
	}
}

int main()
{
	int jobNum = 0, workerNum = 0,jobID = 0, jobDay = 0, curr = 0;
	unsigned int i = 0;
	vector <Job> vecOfJobs;
	Heap <Worker> wHeap;
	string filename;
	cout << "Enter the filename: ";
	cin >> filename;
	ifstream iss(filename);

	fileRead(iss,jobNum,workerNum, vecOfJobs, jobID, jobDay);

	for(unsigned int w = 0; w < workerNum; w++) //loop for the workers' first job
	{
		if(i >= vecOfJobs.size())
			break;
		firstWorkers(workerNum, vecOfJobs, wHeap, i, curr, w);
	}

	while(i < vecOfJobs.size())
	{
		recursiveStep(workerNum, vecOfJobs, wHeap, i, curr);
	}

	clearHeap(wHeap, curr);
	iss.close();
	return 0;
}
