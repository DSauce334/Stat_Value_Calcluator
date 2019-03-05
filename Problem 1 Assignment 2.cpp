#include <iostream>
#include<conio.h>

using namespace std;
//intializes the arrays of the values used in each of the functions
int processid[] = { 1,2,3,4 }; //process number
int runtime[] = { 8,4,9,5 }; //process runtime
int arrivaltime[] = { 0,1,2,3 }; //process arrivaltime
int n = sizeof(runtime) / sizeof(runtime[0]);//sets the size of n based on the number of processes

//special set of arrays to get roundrobin process working
int arrivaltimerr[] = { 0,1,2,3 }; //new arrivaltime array
int runtimerr[] = { 8,4,9,5 }; // new run
int n2 = sizeof(runtimerr) / sizeof(runtimerr[0]);
int timequantum = 5;//timequantum for roundrobin

//special array set to ensure priority process working
int priority[] = { 1, 2, 3, 4 };
int runtimepr[] = { 8, 4, 9, 5 };
int n3 = sizeof(runtimepr) / sizeof(runtimepr[0]);

void priorsched(int n, int runtimepr[], int priority[])
{
	int  p[20], wt[20], comptime[20], i, j, pos, temp;
	//prints out process number
	for (i = 0; i < n3; i++)
	{
		p[i] = i;
	}

	// sorts the arrays based on order of priority
	for (i = 0; i < n3; i++)
	{
		pos = i;
		for (j = i + 1; j < n3; j++)
		{
			if (priority[j] < priority[pos])
				pos = j;
		}

		temp = priority[i];
		priority[i] = priority[pos];
		priority[pos] = temp;

		temp = runtimepr[i];
		runtimepr[i] = runtimepr[pos];
		runtimepr[pos] = temp;

		temp = p[i];
		p[i] = p[pos];
		p[pos] = temp;
	}

	wt[0] = 0;

	//calculate waiting time for finding completion time
	for (i = 1; i < n3; i++)
	{
		wt[i] = 0;
		for (j = 0; j < i; j++)
			wt[i] += runtimepr[j];

	}

	//outputs the values of the system
	cout << "\nProcess : Priority : Runtime : Complete Time";
	for (i = 0; i < n3; i++)
	{
		comptime[i] = runtimepr[i] + wt[i];
		cout << "\nP[" << p[i] << "] : " << priority[i] << " : " << runtimepr[i] << " : " << comptime[i];
	}
	cout << endl << endl;
}

//function that displays the initial values for comparision with the later scheduling
void initialdisplay(int n, int runtime[], int arrivaltime[], int priority[], int timequantum)
{
	int i;
	cout << "Number of Processes: " << n << endl;
	cout << "Time Quantum for Round Robin: " << timequantum << endl << endl;
	cout << "Original Values Presented: " << endl;
	cout << "Process : Arrival Time : Priority : Runtime " << endl;
	for (i = 0; i < n; i++)
	{
		cout << "P[" << processid[i] << "] : " << arrivaltime[i] << " : " << priority[i] << " : " << runtime[i] << endl;
	}
	cout << endl;
}//calling of the first come first serve algorithm with considerations for arrival time
void fcfs(int n, int runtime[], int arrivaltime[], int processid[])
{
	int i, j;
	int temp, temp2, temp3, position = 0;
	int completetime = 0;
	cout << "Process : Arrival Time : Runtime : Completion time" << endl;
	//nested set of loops that sorts based on order of arrival time, and sorts other processes to follow arrival time order
	for (i = 0; i < n; i++)
	{
		int position = i;
		for (j = i; j < n; j++)
		{
			if (arrivaltime[j] < arrivaltime[position])
			{
				position = j;
			}
			temp = arrivaltime[i];
			arrivaltime[i] = arrivaltime[position];
			arrivaltime[position] = temp;
			temp2 = runtime[i];
			runtime[i] = runtime[position];
			runtime[position] = temp2;
			temp3 = processid[i];
			processid[i] = processid[position];
			processid[position] = temp3;
		}

	}


	//prints out each of the values for the arrival time, runtime, and completion time
	for (i = 0; i < n; i++)
	{
		completetime += runtime[i];
		cout << "P[" << processid[i] << "] : " << arrivaltime[i] << " : " << runtime[i] << " : " << completetime << endl;
	}
	cout << endl;
}
//implementation of the shortest job first algorithm
void sjf(int n, int runtime[], int processid[])
{
	int i, j;
	int temp, temp2, position = 0;
	int completetime = 0;
	int waitingtime = 0;
	cout << "Process : Runtime : Completion time" << endl;
	//sorts the values needed for sjf based on the order of ascending runtimes
	for (i = 0; i < n; i++)
	{
		int position = i;
		for (j = i; j < n; j++)
		{
			if (runtime[j] < runtime[position])
			{
				position = j;
			}
			temp = runtime[i];
			runtime[i] = runtime[position];
			runtime[position] = temp;
			temp2 = processid[i];
			processid[i] = processid[position];
			processid[position] = temp2;
		}

	}
	//prints the outputs desired
	for (i = 0; i < n; i++)
	{
		completetime += runtime[i];
		cout << "P[" << processid[i] << "] : " << runtime[i] << " : " << completetime << endl;
	}

	cout << endl;
}
void roundrobin(int n, int arrivaltime[], int runtime[], int timequantum)
{

	int count, time, remain, flag = 0;
	int wait_time = 0, turnaround_time = 0, rt[10];

	remain = n;
	for (count = 0; count < n; count++)
	{
		rt[count] = runtime[count];
	}
	cout << "Process : Arrival Time : Runtime : Complete Time : Waiting Time" << endl << endl;
	for (time = 0, count = 0; remain != 0;)
	{
		if (rt[count] <= timequantum && rt[count] > 0)
		{
			time += rt[count];
			rt[count] = 0;
			flag = 1;
		}
		else if (rt[count] > 0)
		{
			rt[count] -= timequantum;
			time += timequantum;
		}
		if (rt[count] == 0 && flag == 1)
		{
			remain--;
			cout << "P[" << count + 1 << "] : " << arrivaltime[count] << " : " << runtime[count] <<
				" : " << time - arrivaltime[count] << " : " << time - arrivaltime[count] - runtime[count] << endl;
			//wait_time += time - arrivaltime[count] - runtime[count];
			//turnaround_time += time - arrivaltime[count];
			flag = 0;
		}
		if (count == n - 1)
			count = 0;
		else if (arrivaltime[count + 1] <= time)
			count++;
		else
			count = 0;
	}
	//cout << "\nAverage Waiting Time = " << wait_time * 1.0 / n << endl;
	//cout << "Average Turnaround Time = " << turnaround_time * 1.0 / n << endl;
	cout << endl;
}
//implementation of the priority scheduling

//calls and indicates the outputs of each of the four scheduling processes
int main()
{
	initialdisplay(n, runtime, arrivaltime, priority, timequantum);
	cout << "Each Process Outputs with correctly sorted order" << endl << "in comparison to original provided order." << endl << endl;
	cout << "FCFS Output: " << endl;
	fcfs(n, runtime, arrivaltime, processid);
	cout << "SJF Output: " << endl;
	sjf(n, runtime, processid);
	cout << "Priority Output: ";
	priorsched(n, runtime, priority);
	cout << "Round-Robin Output: " << endl;
	roundrobin(n2, arrivaltimerr, runtimerr, timequantum);

	return 0;
}
