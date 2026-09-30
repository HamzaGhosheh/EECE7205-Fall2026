#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

// this function looks similar to print array, except its sole purpose is to prin otu the split parts needed for the output
void printingSplits(const int arr[], int low, int high){
    for (int i = low; i <= high; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(int arr[], int n, int& comparisonCount, int& mergeTotal, int low, int mid, int high){
// a merge function must be defined before officially making a mergeSort function
// https://chatgpt.com/c/6abc4eee-4b24-83e9-8add-4f93ebd30c1e
    int x = 0;
    int y = 0;
    int k = low;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    int* leftSplit = new int[leftSize];
    int* rightSplit = new int[rightSize];
    // array initialization

    // referenced Assignment 1, Problem 1 which involved using merge sort techniques and similar styles
    if (low < high) {
        for (int i = 0; i < leftSize; i++) {
            leftSplit[i] = arr[low + i];
        }

        for (int j = 0; j < rightSize; j++) {
            rightSplit[j]= arr[mid + 1 + j];
        }

        while (x < leftSize && y < rightSize) {
            comparisonCount++;
            if (low == 0 && high == n - 1){
                mergeTotal++;
            }
            if (leftSplit[x] <= rightSplit[y]) {
                arr[k] = leftSplit[x];
                x++;
            }
            else {
                arr[k] = rightSplit[y];
                y++; 
            }
               k++;
        }
        
        while (x < leftSize) {  // If there are any intervals remaining in the left half, they are moved 
            arr[k]= leftSplit[x];
            x++; 
            k++;
        }

        while (y < rightSize) { // If there are any intervals remaining in the right half, they are moved 
            arr[k] = rightSplit[y];
            y++;
            k++; 
        }

    cout << "merged: ";
    printingSplits(arr, low, high);
    delete[] leftSplit;
    delete[] rightSplit;
    }
}

void mergeSort(int arr[], int n, int& comparisonCount, int& mergeTotal, int low, int high){
    // checks to see if there are more than one interval and implements the functions of a mergeSort() as a recursive function
    if (low < high){
        cout << "split: ";
        printingSplits(arr, low, high);
        int mid = low + (high - low) / 2;
        mergeSort(arr, n, comparisonCount, mergeTotal, low, mid);
        mergeSort(arr, n, comparisonCount, mergeTotal, mid + 1, high);
        merge(arr, n, comparisonCount, mergeTotal, low, mid, high);
    }    
}

int main(){
    int A[] = {62, 34, 32, 23, 19, 14, 7, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisonCount = 0;
    int mergeTotal = 0;
    
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    mergeSort(A, n, comparisonCount, mergeTotal, 0, n - 1); 
    cout << endl;
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisonCount << endl;
    cout << "(final merge: "  << mergeTotal << ")" << endl;

    return 0;
}