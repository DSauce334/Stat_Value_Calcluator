#include <iostream>
#include <thread>
using namespace std;

int processid[] = { 1,2,3,4 }; //process number
int runtime[] = { 8,4,9,5 }; //process runtime
int arrivaltime[] = { 0,1,2,3 }; //process arrivaltime
int priority[] = { 1,2,3,4 }; //process priority
int n = sizeof(processid)/sizeof(processid[0]);

int timequantum = 5;

void initialdisplay(int n, int runtime[], int arrivaltime[], int priority[], int timequantum)
{
	int i;
	cout << "Number of Processes: " << n << endl;
	cout << "Time Quantum for Round Robin: " << timequantum << "ms" << endl << endl;
	cout << "Original Values Presented: " << endl;
	cout << "Process : Arrival Time : Priority : Runtime " << endl;
	for (i = 0; i < n; i++)
	{
		cout << "P[" << processid[i] << "] : " << arrivaltime[i] << " : " << priority[i] << " : " << runtime[i] << endl;
	}
	cout << endl;
}
void fcfs(int n, int runtime[], int arrivaltime[], int processid[])
{
	int i, j;
	int temp, temp2, temp3, position;
	int completetime = 0;
	float avgwait = 0, avgtat = 0;

	cout << "Process : Arrival Time : Runtime : Completion time" << endl;
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
	for (i = 0; i < n; i++)
	{
		completetime += runtime[i];
		cout << "P[" << processid[i] << "] : " << arrivaltime[i] << " : " << runtime[i] << " : " << completetime << endl;
		
	}
	cout << endl;
}
void sjf(int n, int runtime[], int processid[])
{
	int i, j;
	int temp, temp2, position;
	int completetime = 0;

	cout << "Process : Runtime : Completion time" << endl;
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
	for (i = 0; i < n; i++)
	{
		completetime += runtime[i];
		cout << "P[" << processid[i] << "] : " << runtime[i] << " : " << completetime << endl;
	}
	cout << endl;
}
void roundrobin(int n, int runtime[], int arrivaltime[], int timequantum, int processid[])
{
	int i, count, time, remainder, flag = 0;
	int valcomp[10];
	remainder = n;
	for (count = 0; count < n; count++)
	{
		valcomp[count] = runtime[count];
	}
	for (time = 0; count = 0; remainder != 0)
	{
		if (valcomp[count] <= timequantum && valcomp[count] > 0)
		{
			time += valcomp[count];
			valcomp[count] = 0;
			flag = 1;
		}
		else if (valcomp[count] > 0)
		{
			valcomp[count] -= timequantum;
			time += timequantum;
		}
		if (valcomp[count] == 0 && flag == 1)
		{
			remainder--;
			printf("P[%d]\t|\t%d\t|\t%d\n", count + 1, time - arrivaltime[count], time - arrivaltime[count] - runtime[count]);

		}
	}
		
}
void priorsched(int n, int runtime[], int priority[], int processid[])
{
	int i, j;
	int temp, temp2, temp3, position;
	int completetime = 0;
	cout << "Process : Priority : Runtime : Completion time" << endl;
	for (i = 0; i < n; i++)
	{
		int position = i;
		for (j = i; j < n; j++)
		{
			if (priority[j] < priority[position])
			{
				position = j;
			}
			temp = priority[i];
			priority[i] = priority[position];
			priority[position] = temp;
			temp2 = runtime[i];
			runtime[i] = runtime[position];
			runtime[position] = temp2;
			temp3 = processid[i];
			processid[i] = processid[position];
			processid[position] = temp3;
		}

	}
	for (i = 0; i < n; i++)
	{
		completetime += runtime[i];
		cout << "P[" << processid[i] << "] : " << priority[i] << " : " << runtime[i] << " : " << completetime << endl;
	}
	cout << endl;
}

int main()
{
	initialdisplay(n, runtime, arrivaltime, priority, timequantum);
	cout << "Each Process Outputs with correctly sorted order" << endl << "in comparison to original provided order." << endl << endl;
	cout << "FCFS Output: " << endl;
	fcfs(n, runtime, arrivaltime, processid);
	cout << "SJF Output: " << endl;
	sjf(n, runtime, processid);
	cout << "Priority Output: " << endl;
	priorsched(n, runtime, priority, processid);
	return 0;
}
