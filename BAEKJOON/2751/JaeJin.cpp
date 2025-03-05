#include <iostream>

using namespace std;

void merge(int start, int mid, int end, int* array)
{
    int leftCnt = mid - start + 1;
    int rightCnt = end - mid;

    int* left = new int[leftCnt];
    int* right = new int[rightCnt];

    for (int i = 0; i < leftCnt; i++) left[i] = array[start + i];
    for (int i = 0; i < rightCnt; i++) right[i] = array[mid + 1 + i];

    int leftIdx = 0, rightIdx = 0, mergedIdx = start;

    while (leftIdx < leftCnt && rightIdx < rightCnt)
    {
        if (left[leftIdx] <= right[rightIdx])
        {
            array[mergedIdx++] = left[leftIdx++];
        }
        else
        {
            array[mergedIdx++] = right[rightIdx++];
        }
    }

    while (leftIdx < leftCnt)
    {
        array[mergedIdx++] = left[leftIdx++];
    }

    while (rightIdx < rightCnt)
    {
        array[mergedIdx++] = right[rightIdx++];
    }

    delete[] left;
    delete[] right;
}

void mergeSort(int start, int end, int* array)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    mergeSort(start, mid, array);
    mergeSort(mid + 1, end, array);
    merge(start, mid, end, array);
}

int main() {
    int N;
    cin >> N;

    int* array = new int[N];
    for (int i = 0; i < N; i++)
    {
        cin >> array[i];
    }

    mergeSort(0, N - 1, array);

    for (int i = 0; i < N; i++)
    {
        cout << array[i] << " ";
    }

    cout << endl;

    delete[] array;
    return 0;
}
