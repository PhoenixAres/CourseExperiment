#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;
const int maxn = 10000;

int a[maxn];
int arr[maxn];

void SelectSort(int arr[], int len)
{//逐步选择无序序列中的最小值，整体n-1，局部n-1-i，不稳定 
	for (int i = 0; i < len-1; ++i)
	{
		for (int j = i+1, temp=arr[i]; j < len; ++j)
		{
			if (arr[j] < arr[i])
            {
				arr[i] = arr[j];
				arr[j] = temp;
				temp = arr[i];
			}
		}
	}
}

void InsertSort(int arr[], int len)
{//无序序列元素插入有序序列中,整体不变，局部减小 
	for (int i = 1; i < len; ++i)
	{
		for (int j = i, temp = arr[i]; j > 0 && arr[j] > arr[j-1]; --j)
		{
			arr[j] = arr[j-1];
			arr[j-1] = temp;
		}
	}
}

void BubbleSort(int arr[], int len)
{//两两比较，只要没有交换，则停止，整体减小，局部减小 
	for (int last = len-1, current = 0; last > 0; last = current)
	{
		current = 0;
		for (int j = 0; j < last; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				current = j;
			}
		}
	}
 }

void heapify(int arr[], int first, int end)
{//end表示最后一个元素的下一个元素 
 	int father = first;
	int son = father*2+1;
	while (son < end)
	{
		if (son+1 < end && arr[son] < arr[son+1]) ++son;
		if (arr[father] > arr[son]) break;
		else
        {
			int temp = arr[father];
			arr[father] = arr[son];
			arr[son] = temp;
		}
		father = son;
		son = father*2+1;
	} 
}
void HeapSort(int arr[], int len)
{//不稳定 
    for (int i = len/2-1; i >= 0; --i)//从第一个父节点，初始化堆 
        heapify(arr, i, len);
    for (int i = len-1; i > 0; --i)  //排序，堆的第一个元素和未排序的最后一个元素互换 
    {
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        heapify(arr, 0, i);
    }
}

int onceSort(int arr[], int first, int end)
{ //end表示最后一个元素 
 	int i = first, j = end;
 	while (i < j)
	{
	 	while (i < j && arr[i] <= arr[j]) --j;//arr[i]<=arr[j]尽量避免不稳定，但还是不稳定
	 	if (i < j)
        {
	 		int temp = arr[i];
	 		arr[i] = arr[j];
	 		arr[j] = temp;
		}
	 	while (i < j && arr[i] <= arr[j]) ++i;
	 	if (i < j)
        {
	 		int temp = arr[i];
	 		arr[i] = arr[j];
	 		arr[j] = temp;
		}
	} 
	return i;
}
 
void QuickSort(int arr[], int first, int end)
 {
 	if (first >= end) return;
 	int pivot = onceSort(arr, first, end);
 	QuickSort(arr, first, pivot-1);
 	QuickSort(arr, pivot+1, end);
 }


void merge(int arr[], int reg[], int first, int end) 
{//end表示最后一个元素 
	if (first >= end) return;
	int len = end-first;
	int mid = len/2+first;//划分成单个元素
	int start1 = first, end1=mid;
	int start2 = mid+1, end2=end; 
	merge(arr, reg, start1, end1);
	merge(arr, reg, start2, end2);
	int k = first;//归并 
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1]<=arr[start2]?arr[start1++]:arr[start2++];
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	while(start2 <= end2)
		reg[k++] = arr[start2++];	
	for(k = first; k <= end; ++k)//赋值 
	 	arr[k] = reg[k];
}
void MergeSort(int arr[], int len)
{//稳定排序 
	int reg[len];
	merge(arr, reg, 0, len-1);
}

int main()
{
    srand(777);

    cout << "n:" << maxn << endl;
    for (int i = 0; i < maxn; ++i)
        a[i] = rand()%mod;
    double s, e;    

    memcpy(arr, a, sizeof(a));
    s = clock();
    SelectSort(arr, maxn);
    e = clock();
    cout << "SelectSort:" << e - s << endl;

    memcpy(arr, a, sizeof(a));
    s = clock();
    InsertSort(arr, maxn);
    e = clock();
    cout << "InsertSort:" << e - s << endl;

    memcpy(arr, a, sizeof(a));
    s = clock();
    BubbleSort(arr, maxn);
    e = clock();
    cout << "BubbleSort:" << e - s << endl;

    memcpy(arr, a, sizeof(a));
    s = clock();
    HeapSort(arr, maxn);
    e = clock();
    cout << "HeapSort:" << e - s << endl;
    
    memcpy(arr, a, sizeof(a));
    s = clock();
    QuickSort(arr, 0, maxn-1);
    e = clock();
    cout << "QuickSort:" << e - s << endl;

    memcpy(arr, a, sizeof(a));
    s = clock();
    MergeSort(arr, maxn);
    e = clock();
    cout << "MergeSort:" << e - s << endl;
  
    return 0;
}