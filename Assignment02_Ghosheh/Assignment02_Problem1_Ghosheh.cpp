#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

// https://chatgpt.com/c/6abc52b0-e02c-83e9-be7d-60d9bc686e83
// I used ChatGPT to better understand the loop bounds for bubble sort and see why the bounds look irregular
void bubbleSort(int arr[], int n, int& comparisonCount, int &switchCount){
    int iterations = 0;
    for (int i = 0; i < n - 1; i++){ // this loop symbolizes how many passes I conducted through the array
        bool swapTakesPlace = false;
        for (int j = 0; j < n - 1 - i; j++){ // this loop checks for adjacent values in the array
            comparisonCount++;
            if (arr[j] > arr[j + 1]){ // if condition is included to see if there differences with the adjacent elements and remains in bounds
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                switchCount++;
                swapTakesPlace = true;
            }
        }
        iterations++;

        cout << "Pass " << iterations << ": ";
        printArray(arr, n);
        if (!swapTakesPlace)
            break;
    }
}

int main() {
    int A[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisonCount = 0;
    int switches = 0;

    cout << "Original: ";
    printArray(A, n);
    bubbleSort(A, n, comparisonCount, switches); 
    cout << "Sorted: ";
    printArray(A, n);

    cout << "Comparisons: " << comparisonCount << endl;
    cout << "Swaps: " << switches << endl;

    return 0;
}