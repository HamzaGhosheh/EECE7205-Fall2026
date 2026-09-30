#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n, int& comparisonCount, int &shiftCount){
    // Start at index 1 because the first value by itself can already be considered sorted
    // Each iteration inserts one new value into the newly sorted portion
    for (int i = 1; i < n; i++){ // this loop symbolizes how many passes I conducted through the array
        int myKey = arr[i];
        int j  = i - 1;
        
        while (j>= 0 && arr[j] > myKey){
        // this while loop backwards through the sorted portion
            comparisonCount++;
            arr[j+1] = arr[j];
            shiftCount++;
            j--;
        }

        if (j >= 0){
            comparisonCount++;
        }

        arr[j+1] = myKey;
        cout << "i = " << i << ", key = " << myKey << ": ";
        printArray(arr, n);
    }
}

int main(){
    int A[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisonCount = 0;
    int shiftCount = 0;


    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    insertionSort(A, n, comparisonCount, shiftCount); 
    cout << endl;
    cout << "Sorted: ";
    printArray(A, n);

    cout << endl;

    cout << "Comparisons: " << comparisonCount << endl;
    cout << "Shifts: " << shiftCount << endl;

    return 0;
}