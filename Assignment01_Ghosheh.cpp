#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Problem 1

void mergeSort(int intervals[][2], int leftValue, int rightValue); // I chose mergesort because both the time complexity and way it is structured amde sense to solve this problem
// https://chatgpt.com/c/6ab56fce-8a20-83ea-8e9b-befbbd1eabe4

void sorting(int intervals[][2], int leftValue, int middle, int rightValue);

int mergeIntervals(int intervals[][2], int size){
     if (size == 0){
        return 0;
    }
    
    mergeSort(intervals, 0, size - 1);

    int (*merged)[2] = new int[size][2]; // adding the * makes the array a dynamic array, becase the value of merged is a pointer to arrays containing to ints
    // https://chatgpt.com/c/6ab56f64-2a14-83ea-9af3-e95aaaaed364
    int mergedSize = 0;

    int currentStart = intervals[0][0];
    int currentEnd = intervals[0][1];

    for (int i = 1; i < size; i++) { // this for loop combines the overlapping intervals
        if (intervals[i][0] <= currentEnd) { // does the next interval begin before the current one ends
            currentEnd = max(currentEnd, intervals[i][1]);
        }   
        else {
            merged[mergedSize][0] = currentStart; // going with the other possibility if there is no overlap
            merged[mergedSize][1] = currentEnd;
            mergedSize++;

            currentStart = intervals[i][0];
            currentEnd = intervals[i][1];
        }
    }
    merged[mergedSize][0] = currentStart;
    merged[mergedSize][1] = currentEnd;
    mergedSize++;

    for (int i = 0; i < mergedSize; i++) {
        intervals[i][0] = merged[i][0];
        intervals[i][1] = merged[i][1];
    }

    delete[] merged; // https://www.geeksforgeeks.org/cpp/delete-in-c/
    // the purpose here is to delete an array from memory to allocate for the heap that is created from the functions above
    return mergedSize;
}

void sorting(int intervals[][2], int leftValue, int middle, int rightValue) {
    int x = 0;
    int y = 0;
    int k = leftValue;

    if (leftValue < rightValue) {
        int leftSize = middle - leftValue + 1;
        int rightSize = rightValue - middle;

        int (*leftInterval)[2] = new int[leftSize][2]; // once again using an array pointer to make the array dynamic to allocate
        int (*rightInterval)[2] = new int[rightSize][2];

        for (int i = 0; i < leftSize; i++) {
            leftInterval[i][0] = intervals[leftValue + i][0];
            leftInterval[i][1] = intervals[leftValue + i][1];
        }

        for (int j = 0; j < rightSize; j++) {
            rightInterval[j][0] = intervals[middle + 1 + j][0];
            rightInterval[j][1] = intervals[middle + 1 + j][1];
        }

        while (x < leftSize && y < rightSize) {
            if (leftInterval[x][0] <= rightInterval[y][0]) {
                intervals[k][0] = leftInterval[x][0];
                intervals[k][1] = leftInterval[x][1];
                x++; // moves to next left Interval
                k++; // moves to next array position
            }
            else {
                intervals[k][0] = rightInterval[y][0];
                intervals[k][1] = rightInterval[y][1];
                y++; // moves to next right Interval
                k++; // moves to next array position
            }
        }
        
        while (x < leftSize) { // If there are any intervals remaining in the left half, they are moved into 
            intervals[k][0] = leftInterval[x][0];
            intervals[k][1] = leftInterval[x][1];
            x++; // moves to next left Interval
            k++; // moves to next array position
        }

        while (y < rightSize) {
            intervals[k][0] = rightInterval[y][0];
            intervals[k][1] = rightInterval[y][1];
            y++;// moves to next right Interval
            k++; // moves to next array position
        }

    delete[] leftInterval; // cleanup of unwanted memory
    delete[] rightInterval;
    }
}

void mergeSort(int intervals[][2], int leftValue, int rightValue) { // checks to see if there are more than one interval and implements the functions of a mergeSort()
    if (leftValue < rightValue) {
        int middle = leftValue + (rightValue - leftValue) / 2;
        mergeSort(intervals, leftValue, middle);
        mergeSort(intervals, middle + 1, rightValue);
        sorting(intervals, leftValue, middle, rightValue);
    }
}

void printIntervals(int intervals[][2], int size){ // this function is going through every interval and displaying it as an output
    for (int i = 0; i < size; i++){
        cout << "[" << intervals[i][0] << ", " << intervals[i][1] << "] ";
    }
    cout << endl;
}

// Problem 2

void dutchAlgorithm(int array[], int size) {
    // https://chatgpt.com/c/6ab56e9a-9f04-83ea-a913-17263341ff8e
    // The dutch algorithm is essentially sorting an array into three distinct groups, which would be our lowVal, midVal and highVal
    int lowVal = 0;
    int midVal = 0;
    int highVal = size - 1; // maximum value in the array

    while (midVal <= highVal) { // so long as the high value is larger than the midVal, incrementation continues
        if (array[midVal] == 0) {
            swap(array[lowVal], array[midVal]);
            lowVal++;
            midVal++;
        }
        else if (array[midVal] == 1) {
            midVal++;
        }
        else {
            swap(array[midVal], array[highVal]); // https://www.geeksforgeeks.org/cpp/swap-in-cpp/
            // swap() allows us to switch two values with one another, which allows the groupings of the dutch algorithm to be easier
            highVal--;
        }
    }
}

void arrayDisplay(int array[], int size) { // this function is going thorugh eveyr array and displaying it at the end; recursive function
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// Problem 3

bool comparing(string x, string y){ // using a boolean here to assess a yes or no situation where a concatenated x + y > y +x
    return x + y > y + x;
}

string constructLargestInt (vector<int> integerVect){    
    if (integerVect.size() == 0){ // checks to see if there is an empty vector
        return ""; // empty return
    }
    
    vector<string> myString; 
    
    for (int i = 0; i < integerVect.size(); i++) {
        myString.push_back(to_string(integerVect[i])); // https://en.cppreference.com/cpp/string/basic_string/to_string
        // to_string() method here works to convert the values stored in the vector from int to string
    }

    sort(myString.begin(), myString.end(), comparing); // https://www.w3schools.com/cpp/ref_algorithm_sort.asp
    // the sort(0 fucntion has a .begin() and .end() portion to help organize the vector in a way that the user wants)
    if (myString[0] == "0") {
        return "0";
    }

    string completeString = ""; // initialized to an empty string

    for (int i = 0; i < myString.size(); i++) {
        completeString += myString[i];
    }

    return completeString;
}
    
// Problem 4

vector<vector<string>> sortAnagrams(vector<string> initialVector) {   
// https://chatgpt.com/c/6ab569d5-b8b4-83ea-8d96-5983d559b915
// this is essentially a layered form of data that is a three-dimensional for indexing the strings called initialVector
    vector<vector<string>> groups; // vector for groups, 2D 
    vector<string> keys; // vector for keys, 1D

    if (initialVector.size() == 0){ // checks to see if there is an empty input
        return groups;
    }

    for (int i = 0; i < initialVector.size(); i++){ // initializing begins when a vector of strings is created by going through every string
        string word = initialVector[i];
        string key = word;
        // makes a copy of every key
        sort(key.begin(), key.end());
        // sort() here allows us to log the keys of each string presented in the array

        bool found = false; // one of the many functions of bool is true/false, yes/no, found/not found

        for (int j = 0; j < keys.size(); j++){
            if (key == keys[j]){
                groups[j].push_back(word);
                found = true;
                break;
            }
        }
        if (found == false){ // checking for the condition to be true by searching through existing keys
            keys.push_back(key);
            vector<string> newGroup;
            newGroup.push_back(word);
            groups.push_back(newGroup);
            // push_back() adds the key to the end of the vector and subsequently creating a new vector
            // https://chatgpt.com/c/6ab56bf2-e6cc-83ea-a1e5-1bf8d050763a
        }
    }
    return groups;
}

// Problem 5

void sortingInterval(int current_Interval[][2], int leftNum, int middleNum, int rightNum) { // this function will eventually be called in recursion once 

    int a = 0;
    int b = 0;
    int c = leftNum;

    if (leftNum < rightNum) { // calculating on the side of each half by creating temporary arrays
        int length_l = middleNum - leftNum + 1;
        int length_r = rightNum - middleNum;

        int (*first_interval)[2] = new int[length_l][2];
        int (*second_interval)[2] = new int[length_r][2];

        for (int i = 0; i < length_l; i++) { // left half iteration 
            first_interval[i][0] = current_Interval[leftNum + i][0];
            first_interval[i][1] = current_Interval[leftNum + i][1];
        }

        for (int j = 0; j < length_r; j++) { // right half iteration
            second_interval[j][0] = current_Interval[middleNum + 1 + j][0];
            second_interval[j][1] = current_Interval[middleNum + 1 + j][1];
        }

        // both elements need to exist to make this statement work with both lengths
        while (a < length_l && b < length_r) {
            if (first_interval[a][0] <= second_interval[b][0]) {
                current_Interval[a][0] = first_interval[a][0];
                current_Interval[c][1] = first_interval[a][1];
                a++;
                c++;
            }
            else {
                current_Interval[c][0] = second_interval[b][0];
                current_Interval[c][1] = second_interval[b][1];
                b++;
                c++;
            }
        }

        // https://chatgpt.com/c/6ab5928e-ea88-83ea-b570-47205e73d2c5
        // the while loops here are useful because index advancement is unknown in its particular order
        
        while (a < length_l) {
            current_Interval[c][0] = first_interval[a][0];
            current_Interval[c][1] = first_interval[a][1];
            a++;
            c++;
            // double iteration
        }

        while (b < length_r) {
            current_Interval[c][0] = second_interval[b][0];
            current_Interval[c][1] = second_interval[b][1];
            b++;
            c++;
            // double iteration
        }

    delete[] first_interval; // these are the temporary arrays created as a result of iteration
    delete[] second_interval;
    }
}

void checkOverlap(int currentIntervals[][2], int leftVal, int rightVal) { // this is a standrad merge recursion where mergeSort behavior is being shown
    if (leftVal < rightVal) {
        int midVal = leftVal + (rightVal - leftVal) / 2;
        checkOverlap(currentIntervals, leftVal, midVal);
        checkOverlap(currentIntervals, midVal + 1, rightVal);
        sortingInterval(currentIntervals, leftVal, midVal, rightVal);
    }
}

bool overlappingIntervals(int meetingIntervals[][2], int size){ // this is chekcing to see if there is only one meeting, because you cannot have overlap if there is only one meeting
    if (size <= 1){
            return true;
    }
    
    checkOverlap(meetingIntervals, 0, size -1);

    for (int i = 0; i < size; i++){
        if (meetingIntervals[i][0] < meetingIntervals[i - 1][1]) {
            return false;
        }
    }

    return true;
}

// Problem 6

int distanceFormula(int x, int y){ // standard mathematical formula for solving distance
    return x*x + y*y;
}

// Note: the actual formula has a square root implement after adding the two squares, but for simplicity purposes comparing the sum is sufficient enough for this problem

void determinePointDistance(int coordinateSet[][2], int X_coord, int middleNum, int Y_coord) {
    // this function takes two-already sorted sections of coordinates and merges them into one section
    
    // this determines how large each half is
    int leftSize = middleNum - X_coord + 1;
    int rightSize = Y_coord - middleNum;
    int (*firstCoordinate)[2] = new int[leftSize][2];
    int (*comparingCoordinate)[2] = new int[rightSize][2];

    for (int i = 0; i < leftSize; i++) { // copying the left side
        firstCoordinate[i][0] = coordinateSet[X_coord + i][0];
        firstCoordinate[i][1] = coordinateSet[X_coord + i][1];
    }

    for (int j = 0; j < rightSize; j++) { // copying the right side
        comparingCoordinate[j][0] = coordinateSet[middleNum + 1 + j][0];
        comparingCoordinate[j][1] = coordinateSet[middleNum + 1 + j][1];
    }

    int i = 0;
    int j = 0;
    int k = X_coord;

    while (i < leftSize && j < rightSize) { // this while loop is instituted to compare the distances between two points
        int initialDistance = distanceFormula(firstCoordinate[i][0], firstCoordinate[i][1]);
        int comparisonDistance = distanceFormula(comparingCoordinate[j][0], comparingCoordinate[j][1]);
        // keeps comparing points until the temporary arrays have run out
        if (initialDistance <= comparisonDistance) { // put the closer point first after comparing
            coordinateSet[k][0] = firstCoordinate[i][0];
            coordinateSet[k][1] = firstCoordinate[i][1];
            i++;
        }
        else {
            coordinateSet[k][0] = comparingCoordinate[j][0];
            coordinateSet[k][1] = comparingCoordinate[j][1];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        coordinateSet[k][0] = firstCoordinate[i][0];
        coordinateSet[k][1] = firstCoordinate[i][1];
        i++;
        k++;
    }

    // https://chatgpt.com/c/6ab59063-5dc4-83e9-b436-129150e5e5de

    // There needs to be a continuous comparison for both sides to take place until the array runs out

    while (j < rightSize) {
        coordinateSet[k][0] = comparingCoordinate[j][0];
        coordinateSet[k][1] = comparingCoordinate[j][1];
        j++;
        k++;
    }

    delete[] firstCoordinate; // once again deleting the temporary arrays
    delete[] comparingCoordinate;
}

void sortPoints(int coordinates[][2], int leftDistance, int rightDistance) { // another mergeSort() behavior being shown to organize eveyrhting in order
    if (leftDistance < rightDistance) {
        int midpoint = leftDistance + (rightDistance - leftDistance) / 2;
        sortPoints(coordinates, leftDistance, midpoint);
        sortPoints(coordinates, midpoint + 1, rightDistance);
        determinePointDistance(coordinates, leftDistance, midpoint, rightDistance);
    }
}

void kClosestPoints(int coordinates[][2], int arraySize, int k){ // this function is taking in a number k to cap off the shortest distances presented in the array
    if (arraySize == 0) {
        cout << "[]" << endl;
        return;
    }
    
    for (int i = 0; i < k; i++){
        cout << "[" << coordinates[i][0] << ", " << coordinates[i][1] << "]";
    }
    cout << endl;
}

// Problem 7

bool compareFrequencies(int x, int y, const unordered_map<int, int>& IntegerFrequency) {
    // https://stackoverflow.com/questions/4629317/what-does-int-mean
    if (IntegerFrequency.at(x) != IntegerFrequency.at(y)) {
        return IntegerFrequency.at(x) > IntegerFrequency.at(y); // the ordered map has a pair fo a contants fixed integer that cannot be chanegd and its complement the integerFrequency
    }

    return x < y; // tiebreaker if both frequecnies are equal
}

vector<int> frequencyTracker(vector<int> array, int k){ 
    // the purpose here is to count how many times each number occurs
    unordered_map<int, int> IntegerFrequency; // https://chatgpt.com/c/6ab563e3-0be8-83ea-a948-dffd8aebe066
    // an unordered map stores everything as a pair and for associating two things together
    vector<int> frequencyValues;
    vector<int> finalSet;

    for (int i = 0; i < array.size(); i++) { // count how many times a number appears
        IntegerFrequency[array[i]]++;
    }

    for (auto numberPair : IntegerFrequency) { // https://stackoverflow.com/questions/6900459/the-new-keyword-auto-when-should-it-be-used-to-declare-a-variable-type
        // each element inside integerFrequency is not an int, but rather a pair; hence why the auto method automatically makes numberPair the desired type
        frequencyValues.push_back(numberPair.first); // https://chatgpt.com/c/6ab562ec-e590-83ea-b979-827956629f0d 
        // the .first method is useful when comparing two things in pairs, which is true in this case above when looking at the number pair
    }


    sort(frequencyValues.begin(), frequencyValues.end(),[&IntegerFrequency](int a, int b) {return compareFrequencies(a, b, IntegerFrequency);});
    // https://chatgpt.com/c/6ab57d32-2b58-83ea-bf52-92a95fcec237
    // the above function is a lambda expression, which is a small temporary functon whenever it needs to be called

    for (int i = 0; i < k && i < frequencyValues.size(); i++) {
        finalSet.push_back(frequencyValues[i]); // https://www.geeksforgeeks.org/cpp/vector-push-back-cpp-stl/
    }
    // push_back is used when a new element is inserted at the back of the vector, and memory allocation takes place accordingly once it reaches the maximum
    return finalSet;
}

void returnArray(vector<int> mode) {
    // returns the outputted array on display
    cout << "[";
    for (int i = 0; i < mode.size(); i++) {
        cout << mode[i];

        if (i < mode.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Problem 8

struct InspectingHeaps { // struct is a way of grouing together data types used for similar purposes; all under the same category of storing information about a number
    int key;
    int arrayPriority;
    int elementPriority;
    // https://chatgpt.com/c/6ab55bd5-874c-83ea-bc29-e763cf1a7f51
};

struct ComparingHeaps { // putting the function under one purpose allows for easier simplification; determines what number goes on top
    bool operator()(InspectingHeaps first, InspectingHeaps second) {
        return first.key > second.key;
    }
};

vector<int> mergingArrays(vector<vector<int>> arrayCollection) { // merges multiple sorted arrays in one array
    priority_queue<InspectingHeaps, vector<InspectingHeaps>, ComparingHeaps> minVal; // https://www.geeksforgeeks.org/cpp/priority-queue-in-cpp-stl/
    // the min heap is created as a result of creating the 2D vector
    vector<int> output;

    for (int i = 0; i < arrayCollection.size(); i++) { // this for loop puts the first number in every array into the heap
        if (!arrayCollection[i].empty()) {
            InspectingHeaps myIndex;
            // this is essentially finding the smallest number to make this work
            myIndex.key = arrayCollection[i][0];
            myIndex.arrayPriority = i;
            myIndex.elementPriority = 0;
            minVal.push(myIndex);
        }
    }

    while (!minVal.empty()) {
        InspectingHeaps smallestElement = minVal.top(); // https://chatgpt.com/c/6ab57eb5-d190-83ea-8a1b-d90a6a9637c2
        // top does not remove the value situated there, whereas pop does
        minVal.pop();
        output.push_back(smallestElement.key);
        int nextNum = smallestElement.elementPriority + 1;
        // ensures the next element must exist
        if (nextNum < arrayCollection[smallestElement.arrayPriority].size()) {
            InspectingHeaps nextVal; // object representing the first number and adding that to the next heap
            nextVal.key = arrayCollection[smallestElement.arrayPriority][nextNum];
            nextVal.arrayPriority = smallestElement.arrayPriority;
            nextVal.elementPriority = nextNum;
            minVal.push(nextVal);
        }
    }
    return output;
}

// Problem 9

int largestK(vector<int> emptyVector, int k) {
    // checks to see whether a is valid; must be between 1 and the size of the vector
    if (k <= 0 || k > emptyVector.size()) { // https://www.geeksforgeeks.org/cpp/arraysize-c-stl/
        return -1; // returning -1 is more about determining if there is a value, not about counting the size; checking if a is invalid
    }
    
    priority_queue<int, vector<int>, greater<int>> minimum;
    // https://www.geeksforgeeks.org/cpp/priority-queue-in-cpp-stl/
    // by default, a priority queue is a max-heap, so declaring greater int switches it to a min heap
    for (int i = 0; i < emptyVector.size(); i++) { // iteration through every number
        minimum.push(emptyVector[i]);
        // put the number into a heap
        if (minimum.size() > k) {
            minimum.pop();
            // removing numbers if the heap gets too big
        }
    }

    return minimum.top(); // insepcting the top value presented in the vector
}

// Problem 10

long long mergeArrays(vector<int>& array, int leftHalf, int midpoint, int rightHalf) {
    // this function here receives to portions of an array that have already been sorted
    vector<int> focus;
    vector<int> comparedArray;
    // temporary vectors being created for representing the two halves

    for (int i = leftHalf; i <= midpoint; i++) {
        focus.push_back(array[i]); // the focused point in the array is what is being looked at and compared when being copied
    }
    // copy the left half of the current section into a temporary vector
    
    for (int i = midpoint + 1; i <= rightHalf; i++) {
        comparedArray.push_back(array[i]);
    }
    // copy the right half of the current section into a temporary vector

    int m = 0;
    int n = 0;
    int current_element = leftHalf;
    long long quantity = 0;

    while (m < focus.size() && n < comparedArray.size()) {
    // the while loop compares the two halves
        if (focus[m] <= comparedArray[n]) {
            array[current_element] = focus[m];
            m++;
        }

        else {
            array[current_element] = comparedArray[n];
            quantity += focus.size() - m;
            n++;
        }
        current_element++;
        // moves the destination forward with incrementing
    }

    while (m < focus.size()) {
        array[current_element] = focus[m];
        m++;
        current_element++;
    }

    while (n < comparedArray.size()) {
        array[current_element] = comparedArray[n];
        n++;
        current_element++;
    }
    // both statements above copy leftover elements and the relevant comparisons have been properly handled
    return quantity;
}

long long counter(vector<int>& array, int leftHalf, int rightHalf) { // https://www.geeksforgeeks.org/cpp/difference-between-long-int-and-long-long-int-in-c-cpp/
// using the long long int is importna tbecause we are dealing with a 64-bit counter and the range is much larger than a standard int 

    if (leftHalf >= rightHalf) { // base case if we are down to one element
        return 0;
    }

    int quotient = leftHalf + (rightHalf - leftHalf) / 2;
    // finding the midpoint
    long long quantity = 0;
    quantity += counter(array, leftHalf, quotient);
    quantity += counter(array, quotient + 1, rightHalf);
    quantity += mergeArrays(array, leftHalf, quotient, rightHalf);
    // the quantity value keeps track of all inversion being added through iteration

    return quantity;
}

int main() { // main method for all 10 problems

// user has a selection of which problem they would like to see outputted
    int problemSelection;
    cout << "EECE 7205 - Assignment 01" << endl;
    cout << "Select a problem to evaluate:" << endl;
    cout << "Problem 1. Merge Intervals" << endl;
    cout << "Problem 2. Sort 0s, 1s, and 2s" << endl;
    cout << "Problem 3. Largest Number" << endl;
    cout << "Problem 4. Group Anagrams" << endl;
    cout << "Problem 5. Meeting Intervals" << endl;
    cout << "Problem 6. K Closest Points" << endl;
    cout << "Problem 7. K Most Frequent Elements" << endl;
    cout << "Problem 8. Merge K Sorted Arrays" << endl;
    cout << "Problem 9. Kth Largest Element" << endl;
    cout << "Problem 10. Inversion Count" << endl;
    cout << endl;
    cout << "Enter problem number (1-10): ";
    cin >> problemSelection;

    switch (problemSelection) {
        case 1:{
            int intervals[][2] = {};
            int size = sizeof(intervals) / sizeof(intervals[0]);
            cout << "Test Case 5 (Empty Interval): " << endl;
            cout << endl;
            cout << "Input: ";    
            if (size == 0) {
                cout << "[]" << endl;
            }
            else {
                printIntervals(intervals, size);
            }
            
            int mergedSize = mergeIntervals(intervals, size);
            cout << endl;
            cout << "Output: ";
            
            if (mergedSize == 0) {
                cout << "[]" << endl;
            }
            else {
                printIntervals(intervals, mergedSize);
            }

            break;
        }

        case 2:{
            int array[] = {};
            int size = sizeof(array) / sizeof(array[0]);

            cout << "Test Case 5 (Empty Array):" << endl;

            cout << "Input: ";
            if (size == 0) {
                cout << "[]" << endl;
            }
            else {
                arrayDisplay(array, size);
            }

            dutchAlgorithm(array, size);

            cout << "Output: ";
            if (size == 0) {
                cout << "[]" << endl;
            }
            else {
                arrayDisplay(array, size);
            }

            return 0;
            break;
        }

        case 3:{
            vector<int> array = {0, 0, 0};
            cout << "Test Case 5 (All frequencyValues are Zeros):" << endl;
            cout << "Input: [";
            for (int i = 0; i < array.size(); i++) {
                cout << array[i];

                if (i < array.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            cout << "Output: ";
            cout << constructLargestInt(array) << endl;
            break;
        }

        case 4:{
            vector<string> array = {};
            cout << "Test Case 5 (Empty Array):" << endl;

            cout << "Input: [";
            for (int i = 0; i < array.size(); i++) {
                cout << array[i];

                if (i < array.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            vector<vector<string>> result = sortAnagrams(array);
            cout << "Output: [";
            for (int i = 0; i < result.size(); i++) {
                cout << "[";
                for (int j = 0; j < result[i].size(); j++) {
                    cout << result[i][j];
                    if (j < result[i].size() - 1) {
                        cout << ", ";
                    }
                }
                cout << "]";

                if (i < result.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            break;
        }

        case 5: {
            int intervals[][2] = {{1,5}, {5, 12}};
            int size = sizeof(intervals) / sizeof(intervals[0]);
            cout << "Test Case 4 (Same End/Begin Times): " << endl;
            cout << endl;
            cout << "Input: ";  
        
            for (int i = 0; i < size; i++){
                cout << "[" << intervals[i][0] << ", " << intervals[i][1] << "]";
            }
            cout << endl;
            cout << endl;
            cout << "Output: ";

            if (overlappingIntervals(intervals, size)) {
                cout << "True. All meeting times attendable." << endl;
            }

            else {
                cout << "False. Cannot attend meetings." << endl;
            }

            break;
        }

        case 6:{
            int coordinates[][2] = {};
            int size = sizeof(coordinates) / sizeof(coordinates[0]);
            int k = 1;

            cout << "Test Case 5 (Empty Set): " << endl;
            cout << endl;
            cout << "Input: ";
            for (int i = 0; i < size; i++) {
                cout << "[" << coordinates[i][0] << ", " << coordinates[i][1] << "] ";
            }
            cout << endl;
            cout << "k = " << k << endl;
            sortPoints(coordinates, 0, size - 1);
            cout << "Output: ";
            kClosestPoints(coordinates, size, k);
            return 0;
            break;
        }

        case 7:{
            vector<int> array = {1, 2, 3, 4, 5};
            int k = 5;

            cout << "Test Case 4 (No Duplicating Numbers): " << endl;
            cout << endl;
            cout << "Input: ";
            returnArray(array);
            cout << "k = " << k << endl;

            vector<int> result = frequencyTracker(array, k);

            cout << "Output: ";
            returnArray(result);

            return 0;
            break;
        }

        case 8:{
            vector<vector<int>> arrayCollection = {};
            cout << "Test Case 5 (Empty Input): " << endl;
            cout << endl;
            
            cout << "Input:" << endl;
            for (int i = 0; i < arrayCollection.size(); i++) {
                cout << "[";

                for (int j = 0; j < arrayCollection[i].size(); j++) {
                    cout << arrayCollection[i][j];

                    if (j < arrayCollection[i].size() - 1) {
                        cout << ", ";
                    }
                }
                cout << "]" << endl;
            }
    
            vector<int> output = mergingArrays(arrayCollection);
            cout << "Output: [";
            for (int i = 0; i < output.size(); i++) {
                cout << output[i];

                if (i < output.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            return 0;
            break;
        }

        case 9:{    
            vector<int> array = {12};
            int k = 1;
            cout << "Test Case 5 (Single Element Array):" << endl << endl;
            cout << "Input: [";
            for (int i = 0; i < array.size(); i++) {
                cout << array[i];

                if (i < array.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            cout << "k = " << k << endl;

            int output = largestK(array, k);
            cout << "Output: " << output << endl;
            return 0;
            break;
        }

        case 10:{
            vector<int> input = {};
            cout << "Test Case 5 (Empty Array):" << endl << endl;
            cout << "Input: [";
            for (int i = 0; i < input.size(); i++) {
                cout << input[i];

                if (i < input.size() - 1) {
                    cout << ", ";
                }
            }

            cout << "]" << endl;
            long long inversionCount = 0;

            if (!input.empty()) {
                inversionCount = counter(input, 0, input.size() - 1);
            }

            cout << "Output: Inversion Count " << inversionCount << endl;
            return 0;
            break;
        }
        default:
            cout << "Invalid problem number." << endl;
    }

    return 0;
}