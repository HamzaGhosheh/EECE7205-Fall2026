#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }

    cout << endl;
}
// https://chatgpt.com/c/6abc54de-50dc-83e9-b39d-a2110ac9313a
// I used ChatGPT to have it explain the purpose of using a partition when hard-coding a quicksort function
int partition(int arr[], int n, int& comparisonCount, int low, int high){
    int pivot = arr[high]; 
    int i = low - 1;
    // i keeps track of the boundary for elements <= pivot
    // We start one position before low because we have not found any elements in the array
    for (int j = low; j < high; j++){ // this loop symbolizes how many passes I conducted through the array
        comparisonCount++;
        if (arr[j] <= pivot){
            i++;
            int num = arr[i];
            arr[i] = arr[j];
            arr[j] = num;
        }
    }
    int num = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = num;

    cout << "pivot = " << arr[i+1] << ": ";
    printArray(arr, n);
    return i + 1;
}

// This function repeatedly partitions smaller sections of the array
void quickSort(int arr[], int n, int& comparisonCount, int low, int high){ // 
    if (low < high){
        int pivotCount = partition(arr, n, comparisonCount, low, high);
        quickSort(arr, n, comparisonCount, low, pivotCount - 1);
        quickSort(arr, n, comparisonCount, pivotCount + 1, high);
    }    
}

int main(){
    int A[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisonCount = 0;
    
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    quickSort(A, n, comparisonCount, 0, n - 1); 
    cout << endl;
    cout << "Comparisons: " << comparisonCount << endl;
    cout << "Sorted: ";
    printArray(A, n);

    return 0;
}