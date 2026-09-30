#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

void printArray(const int arr[], int n){
    for (int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

void bubbleSort(int arr[], int n, int& comparisonCount, int &switchCount){
    int iterations = 0;
    for (int i = 0; i < n - 1; i++){ 
        bool swapTakesPlace = false;
        for (int j = 0; j < n - 1 - i; j++){ 
            comparisonCount++;
            if (arr[j] > arr[j + 1]){ 
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                switchCount++;
                swapTakesPlace = true;
            }
        }
        iterations++;
        if (!swapTakesPlace)
            break;
    }
    // I removed the printArray function since this Problem does not require us we print out the array
}

void insertionSort(int arr[], int n, int& comparisonCount, int &shiftCount){
    for (int i = 1; i < n; i++){
        int myKey = arr[i];
        int j  = i - 1;
        while (j>= 0 && arr[j] > myKey){
            comparisonCount++;
            arr[j+1] = arr[j];
            shiftCount++;
            j--;
        }
        if (j >= 0){
            comparisonCount++;
        }
        arr[j+1] = myKey;
    }
    // I removed the printArray function since this Problem does not require us we print out the array
}

void selectionSort(int arr[], int n, int& comparisonCount, int &shiftCount){
    for (int i = 0; i < n - 1; i++){ 
        int minIdx = i;
        for (int j = i + 1; j < n; j++){
            comparisonCount++;
            if (arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        
        if (minIdx != i){
            int tempVal = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tempVal;
            shiftCount++;
        }
    }
    // I removed the printArray function since this Problem does not require us we print out the array
}

int partition(int arr[], int n, int& comparisonCount, int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
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

    // I removed the printArray function since this Problem does not require us we print out the array

    return i + 1;
}

void quickSort(int arr[], int n, int& comparisonCount, int low, int high){
    if (low < high){
        int pivotCount = partition(arr, n, comparisonCount, low, high);
        quickSort(arr, n, comparisonCount, low, pivotCount - 1);
        quickSort(arr, n, comparisonCount, pivotCount + 1, high);
    }    
}

void merge(int arr[], int n, int& comparisonCount, int& mergeTotal, int low, int mid, int high){
    int x = 0;
    int y = 0;
    int k = low;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    int* leftSplit = new int[leftSize];
    int* rightSplit = new int[rightSize];
    
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
        
        while (x < leftSize) { 
            arr[k]= leftSplit[x];
            x++; 
            k++;
        }

        while (y < rightSize) {
            arr[k] = rightSplit[y];
            y++;
            k++; 
        }

    delete[] leftSplit;
    delete[] rightSplit;

    // I removed the printArray function since this Problem does not require us we print out the array
    }
}

void mergeSort(int arr[], int n, int& comparisonCount, int& mergeTotal, int low, int high){
    if (low < high){
        int mid = low + (high - low) / 2;
        mergeSort(arr, n, comparisonCount, mergeTotal, low, mid);
        mergeSort(arr, n, comparisonCount, mergeTotal, mid + 1, high);
        merge(arr, n, comparisonCount, mergeTotal, low, mid, high);
    }    
}

void siftDown(int arr[], int root, int size, int& comparisonCount){
    while (2 * root + 1 < size){
        int childNode = 2 * root + 1;
        if (childNode + 1 < size){
            comparisonCount++;
            if (arr[childNode + 1] > arr[childNode]){
                childNode = childNode + 1;
            }
        }

        comparisonCount++;

        if (arr[root] >= arr[childNode]){
            break;
        }

        int tempVal = arr[root];
        arr[root] = arr[childNode];
        arr[childNode] = tempVal;
        root = childNode;
    }
}

void heapSort(int arr[], int n, int& comparisonCount){
    for (int i = n / 2 - 1; i >= 0; i--){
        siftDown(arr, i, n, comparisonCount);
    }

    for (int lastVal = n - 1; lastVal >= 1; lastVal--){
        int tempVal = arr[0];
        arr[0] = arr[lastVal];
        arr[lastVal] = tempVal;
        siftDown(arr, 0, lastVal, comparisonCount);
    }

        // I removed the printArray function since this Problem does not require us we print out the array

}

int main(){

    // initialization of all varaibles to be used
    // ------------------------------------------------------
    // Part 1, Question 7

    int bubble = 0;
    int switches = 0;
    int insertion = 0;
    int shiftCount = 0;
    int selectionCount = 0;
    int selection = 0;
    int quick = 0;
    int merge = 0;
    int mergeTotal = 0;
    int heap = 0;

    int originalArray[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int sortedArray[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int reversedArray[] = {62, 34, 32, 23, 19, 14, 7, 5};

    // these valeus below distinguish the categories of arrays we need for our table
    int originalVal = sizeof(originalArray) / sizeof(originalArray[0]);
    int sortedVal = sizeof(sortedArray) / sizeof(sortedArray[0]);
    int reversedVal = sizeof(reversedArray) / sizeof(reversedArray[0]);

    int* bubbleArray = new int[originalVal];
    int* insertionArray = new int[originalVal];
    int* selectionArray = new int[originalVal];
    int* quickArray = new int[originalVal];
    int* mergeArray = new int[originalVal];
    int* heapArray = new int[originalVal];

    for (int i = 0; i < originalVal; i++){
        bubbleArray[i] = originalArray[i];
        insertionArray[i] = originalArray[i];
        selectionArray[i] = originalArray[i];
        quickArray[i] = originalArray[i];
        mergeArray[i] = originalArray[i];
        heapArray[i] = originalArray[i];
    }

    // methods calling the original given array in the problem
    bubbleSort(bubbleArray, originalVal, bubble, switches);
    insertionSort(insertionArray, originalVal, insertion, shiftCount);
    selectionSort(selectionArray, originalVal, selection, selectionCount);
    quickSort(quickArray, originalVal, quick, 0, originalVal - 1); 
    mergeSort(mergeArray, originalVal, merge, mergeTotal, 0, originalVal - 1);
    heapSort(heapArray, originalVal, heap); 
    cout << endl;

    cout << endl;
    cout << "Original Array Comparison Counts:" << endl;
    cout << endl;
    cout << "Bubble Sort: " << bubble << endl;
    cout << "Insertion Sort: " << insertion << endl;
    cout << "Selection Sort: " << selection << endl;
    cout << "Quick Sort: " << quick << endl;
    cout << "Merge Sort: " << merge << endl;
    cout << "Heap Sort: " << heap << endl;

    // reinitializing of all varaibles to be used once again for a sorted array

    bubble = 0;
    switches = 0;
    insertion = 0;
    shiftCount = 0;
    selectionCount = 0;
    selection = 0;
    quick = 0;
    merge = 0;
    mergeTotal = 0;
    heap = 0;

    for (int i = 0; i < sortedVal; i++){
        bubbleArray[i] = sortedArray[i];
        insertionArray[i] = sortedArray[i];
        selectionArray[i] = sortedArray[i];
        quickArray[i] = sortedArray[i];
        mergeArray[i] = sortedArray[i];
        heapArray[i] = sortedArray[i];
    }

    // methods calling the sorted array
    bubbleSort(bubbleArray, sortedVal, bubble, switches);
    insertionSort(insertionArray, sortedVal, insertion, shiftCount);
    selectionSort(selectionArray, sortedVal, selection, selectionCount);
    quickSort(quickArray, sortedVal, quick, 0, sortedVal - 1);
    mergeSort(mergeArray, sortedVal, merge, mergeTotal, 0, sortedVal - 1);
    heapSort(heapArray, sortedVal, heap);

    cout << endl;
    cout << "Sorted Array Comparison Counts:" << endl;
    cout << "Bubble Sort: " << bubble << endl;
    cout << "Insertion Sort: " << insertion << endl;
    cout << "Selection Sort: " << selection << endl;
    cout << "Quick Sort: " << quick << endl;
    cout << "Merge Sort: " << merge << endl;
    cout << "Heap Sort: " << heap << endl;

    // reinitializing of all varaibles to be used once again for a reverse array
    bubble = 0;
    switches = 0;
    insertion = 0;
    shiftCount = 0;
    selection = 0;
    quick = 0;
    merge = 0;
    mergeTotal = 0;
    heap = 0;

    for (int i = 0; i < reversedVal; i++){
        bubbleArray[i] = reversedArray[i];
        insertionArray[i] = reversedArray[i];
        selectionArray[i] = reversedArray[i];
        quickArray[i] = reversedArray[i];
        mergeArray[i] = reversedArray[i];
        heapArray[i] = reversedArray[i];
    }

    // methods calling the reversed array
    bubbleSort(bubbleArray, reversedVal, bubble, switches);
    insertionSort(insertionArray, reversedVal, insertion, shiftCount);
    selectionSort(selectionArray, reversedVal, selection, selectionCount);
    quickSort(quickArray, reversedVal, quick, 0, reversedVal - 1);
    mergeSort(mergeArray, reversedVal, merge, mergeTotal, 0, reversedVal - 1);
    heapSort(heapArray, reversedVal, heap);

    cout << endl;
    cout << "Reversed Array Comparison Counts:" << endl;
    cout << endl;
    cout << "Bubble Sort: " << bubble << endl;
    cout << "Insertion Sort: " << insertion << endl;
    cout << "Selection Sort: " << selection << endl;
    cout << "Quick Sort: " << quick << endl;
    cout << "Merge Sort: " << merge << endl;
    cout << "Heap Sort: " << heap << endl;

    delete[] bubbleArray;
    delete[] insertionArray;
    delete[] selectionArray;
    delete[] quickArray;
    delete[] mergeArray;
    delete[] heapArray;

    // cleaning up the extra temporary arrays

    // ------------------------------------------------------
    // Part 2, Question 7

    cout << endl;
    cout << "Sorting Times:" << endl;

    int sizes[] = {1000, 5000, 10000};
    int sizeTotal = sizeof(sizes) / sizeof(sizes[0]);

    for (int a = 0; a < sizeTotal; a++){
        int b = sizes[a];
        cout << "\nArray Size: " << b << endl;
        int* newArr = new int[b];
        for (int i = 0; i < b; i++){
            newArr[i] = rand() % 100000 + 1;
        }
        int* rand_bubble = new int[b];
        int* rand_insert = new int[b];
        int* rand_select = new int[b];
        int* rand_quick = new int[b];
        int* rand_merge = new int[b];
        int* rand_heap = new int[b];

        // Initializing new pointers for random arrays genereated for each sorting math

        for (int i = 0; i < b; i++){
            rand_bubble[i] = newArr[i];
            rand_insert[i] = newArr[i];
            rand_select[i] = newArr[i];
            rand_quick[i] = newArr[i];
            rand_merge[i] = newArr[i];
            rand_heap[i] = newArr[i];
        }

    // ------------------------------------------------------
    // Part 3, Question 7

        // Bubble Sort real-time analysis
        bubble = 0;
        switches = 0;
        auto beginBubble = chrono::high_resolution_clock::now();
        bubbleSort(rand_bubble, b, bubble, switches);
        auto endBubble = chrono::high_resolution_clock::now();
        auto bubbleTime = chrono::duration_cast<chrono::microseconds>(endBubble - beginBubble).count();
        cout << "Bubble Sort: "<< bubbleTime << " microseconds" << endl;
        
        // Insertion Sort real-time analysis
        insertion = 0;
        shiftCount = 0;
        auto beginInsertion = chrono::high_resolution_clock::now();
        insertionSort(rand_insert, b, insertion, shiftCount);
        auto endInsertion = chrono::high_resolution_clock::now();
        auto insertClock = chrono::duration_cast<chrono::microseconds>(endInsertion - beginInsertion).count();
        cout << "Insertion Sort: "<< insertClock << " microseconds" << endl;

        // Selection Sort real-time analysis
        selection = 0;
        int selectionCount = 0;
        auto beginSelection = chrono::high_resolution_clock::now();
        selectionSort(rand_select, b, selection, selectionCount);
        auto endSelection = chrono::high_resolution_clock::now();
        auto selectClock = chrono::duration_cast<chrono::microseconds>(endSelection - beginSelection).count();
        cout << "Selection Sort: " << selectClock << " microseconds" << endl;

        // Quick Sort real-time analysis
        quick = 0;
        auto beginQuick = chrono::high_resolution_clock::now();
        quickSort(rand_quick, b, quick, 0, b - 1);
        auto endQuick = chrono::high_resolution_clock::now();
        auto quickClock = chrono::duration_cast<chrono::microseconds>(endQuick - beginQuick).count();
        cout << "Quick Sort: " << quickClock << " microseconds" << endl;

        // Merge Sort real-time analysis
        merge = 0;
        mergeTotal = 0;
        auto beginMerge = chrono::high_resolution_clock::now(); // https://en.cppreference.com/cpp/chrono/high_resolution_clock
        mergeSort(rand_merge, b, merge, mergeTotal, 0, b - 1);
        auto endMerge = chrono::high_resolution_clock::now();
        auto mergeClock = chrono::duration_cast<chrono::microseconds>(endMerge - beginMerge).count();
        cout << "Merge Sort: " << mergeClock << " microseconds" << endl;

        // Heap sort real-time analysis
        heap = 0;
        auto beginHeap = chrono::high_resolution_clock::now(); // https://www.geeksforgeeks.org/cpp/chrono-in-c/
        heapSort(rand_heap, b, heap);
        auto endHeap = chrono::high_resolution_clock::now();
        auto heapClock = chrono::duration_cast<chrono::microseconds>(endHeap - beginHeap).count();
        cout << "Heap Sort: "<< heapClock << " microseconds" << endl;

        cout << endl;
        cout << "First 10 Sorted Elements:" << endl;
        cout << "Bubble Sort: ";
        printArray(rand_bubble, 10);
        cout << "Insertion Sort: ";
        printArray(rand_insert, 10);
        cout << "Selection Sort: ";
        printArray(rand_select, 10);
        cout << "Quick Sort: ";
        printArray(rand_quick, 10);
        cout << "Merge Sort: ";
        printArray(rand_merge, 10);
        cout << "Heap Sort: ";
        printArray(rand_heap, 10);

        delete[] newArr;
        delete[] rand_bubble;
        delete[] rand_insert;
        delete[] rand_select;
        delete[] rand_quick;
        delete[] rand_merge;
        delete[] rand_heap;
        // array cleanup
    }

    return 0;
}