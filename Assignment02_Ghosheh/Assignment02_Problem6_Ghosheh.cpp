#include <iostream>
using namespace std;

// printArray function serves at displaying the array to terminal
void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void siftDown(int arr[], int root, int size, int& swapCount){

    // The right child is one index after the left child
    // If the right child exists AND is larger than the left child, use the right child instead
    while (2 * root + 1 < size){
        int childNode = 2 * root + 1;
        if (childNode + 1 < size && arr[childNode + 1] > arr[childNode]){ 
            // https://chatgpt.com/c/6abc424c-dd5c-83e9-99cd-d79c68292f15
            childNode = childNode + 1;
        }

        // I used ChatGPT to understand the characteristics and the organization of a child node within an array

        if (arr[root] >= arr[childNode]){
            break;
        }

        int tempVal = arr[root];
        arr[root] = arr[childNode];
        arr[childNode] = tempVal;
        swapCount++;
        root = childNode;
    }
}

void heapSort(int arr[], int n, int& swapCount){
    for (int i = n / 2 - 1; i >= 0; i--){
        siftDown(arr, i, n, swapCount);
    }

    cout << "Heap: ";
    printArray(arr, n); 

    for (int lastVal = n - 1; lastVal >= 1; lastVal--){
    // This loop repeatedly decreases the size of the heap and moves the largest value to the end of the array
        int tempVal = arr[0];
        arr[0] = arr[lastVal];
        arr[lastVal] = tempVal;

        siftDown(arr, 0, lastVal, swapCount);

        cout << "end = " << lastVal << ": heap: ";
        printArray(arr, lastVal);
        cout << "       sorted: ";
        printArray(arr + lastVal, n - lastVal);
        cout << endl;
    }
}

int main(){
    int A[] = {4, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int swapCount = 0;
    
    cout << "Original: ";

    printArray(A, n);
    cout << endl;
    heapSort(A, n, swapCount); 
    cout << endl;
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Swaps in siftDown: " << swapCount;
    
    cout << endl;

    return 0;
}