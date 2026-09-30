#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(int arr[], int n, int& comparisonCount, int &shiftCount){
    for (int i = 0; i < n - 1; i++){ // this loop symbolizes how many passes I conducted through the array
        int minIdx = i;
        for (int j = i + 1; j < n; j++){ // this loop searches through the unsorted part of the array
            comparisonCount++;
            if (arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        // We only need n - 1 passes since the final element will automatically be in the correct position
        
        cout << "Pass: " << i + 1<< " min = " << arr[minIdx] << " at index " << minIdx << " --> ";

        // if statement checking if minIdx is smaller than the current minimum
        if (minIdx != i){
            int tempVal = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tempVal;
            shiftCount++;
        }

        printArray(arr, n);
    }
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisonCount = 0;
    int shiftCount = 0;


    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    selectionSort(A, n, comparisonCount, shiftCount); 
    cout << endl;
    cout << "Sorted: ";
    printArray(A, n);

    cout << endl;

    cout << "Comparisons: " << comparisonCount << endl;
    cout << "Swaps: " << shiftCount << endl;

    return 0;
}