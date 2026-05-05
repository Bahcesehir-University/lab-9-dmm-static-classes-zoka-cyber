// ============================================================
// Lab: Dynamic Memory Management & Static Classes
// Course: Object-Oriented Programming for Engineers
// Level: 2nd Year Engineering
// Duration: 50 minutes
// ============================================================
// This file contains ALL code for this lab.
// Do NOT create any .h files. Everything stays here.
// ============================================================

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// ================================================================
// CLASS DEFINITIONS
// ================================================================

// -------------------------------------------------
// Class: IntArray
// Purpose: A dynamic integer array that manages
//          its own memory using new/delete.
// -------------------------------------------------
class IntArray {
private:
    int* data;       // pointer to dynamically allocated array
    int  capacity;   // maximum number of elements
    int  count;      // current number of elements

public:
    // Constructor: allocate array of given capacity
    IntArray(int cap);

    // Destructor: free dynamically allocated memory
    ~IntArray();

    // Copy Constructor: deep copy another IntArray
    IntArray(const IntArray& other);

    // Copy Assignment Operator: deep copy with self-assignment check
    IntArray& operator=(const IntArray& other);

    // Add an element to the end. Return true if successful, false if full.
    bool add(int value);

    // Get element at index. Return -1 if index is out of bounds.
    int get(int index) const;

    // Return current number of elements
    int size() const;

    // Return the capacity
    int getCapacity() const;

    // Check if the array is empty
    bool isEmpty() const;

    // Remove the last element. Return true if successful, false if empty.
    bool removeLast();
};

// -------------------------------------------------
// Class: Tracker
// Purpose: A static utility class that counts how
//          many IntArray objects currently exist.
//          Cannot be instantiated.
// -------------------------------------------------
class Tracker {
private:
    static int objectCount;

    // Private constructor prevents instantiation
    Tracker() = delete;

public:
    // Increment the counter (call from IntArray constructor)
    static void objectCreated();

    // Decrement the counter (call from IntArray destructor)
    static void objectDestroyed();

    // Return current count of live IntArray objects
    static int getActiveCount();

    // Reset counter to zero (for testing purposes)
    static void resetCount();
};

// ================================================================
// STATIC MEMBER INITIALIZATION
// ================================================================

// TODO 1: Initialize Tracker's static member variable
// Hint: int Tracker::objectCount = ???;
int Tracker::objectCount = 0;

// ================================================================
// TRACKER FUNCTION IMPLEMENTATIONS
// ================================================================

void Tracker::objectCreated() {
    // TODO 2: Increment objectCount
    objectCount++;
}

void Tracker::objectDestroyed() {
    // TODO 3: Decrement objectCount
    objectCount--;
}

int Tracker::getActiveCount() {
    // TODO 4: Return objectCount
    return objectCount;
}

void Tracker::resetCount() {
    // TODO 5: Reset objectCount to 0
    objectCount = 0;
}

// ================================================================
// INTARRAY FUNCTION IMPLEMENTATIONS
// ================================================================

// Constructor
IntArray::IntArray(int cap) {
    // TODO 6: Allocate dynamic array of size cap using 'new'
    //         Initialize capacity, count
    //         Notify Tracker that an object was created
capacity = cap ;
 count = 0 ;
 data = new int [capacity];
Tracker::objectCreated();
}

// Destructor
IntArray::~IntArray() {
    // TODO 7: Free the dynamic array using 'delete[]'
    //         Notify Tracker that an object was destroyed

delete[] data;
Tracker::objectDestroyed();
}

// Copy Constructor
IntArray::IntArray(const IntArray& other) {
    capacity = other.capacity;
    count = other.count;
    data = new int[capacity];           // allocate NEW memory
    for (int i = 0; i < count; i++)
        data[i] = other.data[i];        // copy each element
}




// Copy Assignment Operator
IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {               // self-assignment guard
        delete[] data;                  // free old memory
        capacity = other.capacity;
        count = other.count;
        data = new int[capacity];       // allocate new memory
        for (int i = 0; i < count; i++)
            data[i] = other.data[i];
    }
    return *this;
}


// Add element
bool IntArray::add(int value) {
    // TODO 10: If count < capacity, add value at data[count],
    //          increment count, return true.
    //          Otherwise return false.
    if (count < capacity){
        data[count] = value;
        count++;
        return true;
    }
    return false;
}

// Get element at index
int IntArray::get(int index) const {
    // TODO 11: If index is valid (0 <= index < count), return data[index].
    //          Otherwise return -1.
   if (index >= 0 && index < count){
   return data[index] ;       
    }
    return -1;
}

// Size
int IntArray::size() const {
    // TODO 12: Return count
    return count;
}

// Capacity
int IntArray::getCapacity() const {
    // TODO 13: Return capacity
    return capacity;
}

// isEmpty
bool IntArray::isEmpty() const {
    // TODO 14: Return true if count == 0
    return count == 0;
}

// Remove last element
bool IntArray::removeLast() {
    // TODO 15: If not empty, decrement count and return true.
    //          Otherwise return false.
    if (count >0){ 
        count --;
    return true;
}
return false;
}
// ================================================================
// MAIN FUNCTION
// ================================================================

int main() {
    cout << "=== Dynamic Memory & Static Classes Lab ===" << endl;
    cout << endl;

    // Test basic creation
    cout << "[1] Creating IntArray with capacity 5..." << endl;
    IntArray arr(5);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;

    // Test adding elements
    cout << "[2] Adding elements: 10, 20, 30" << endl;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "    Size: " << arr.size() << ", Capacity: " << arr.getCapacity() << endl;

    // Test get
    cout << "[3] Elements: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.get(i) << " ";
    }
    cout << endl;

    // Test copy constructor
    cout << "[4] Copy constructing arr2 from arr..." << endl;
    IntArray arr2(arr);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    cout << "    arr2 size: " << arr2.size() << endl;

    // Test copy assignment
    cout << "[5] Creating arr3(2), then assigning arr to arr3..." << endl;
    IntArray arr3(2);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    arr3 = arr;
    cout << "    arr3 size after assignment: " << arr3.size() << endl;

    // Test removeLast
    cout << "[6] Removing last from arr..." << endl;
    arr.removeLast();
    cout << "    arr size after removeLast: " << arr.size() << endl;

    // Test scope-based destruction
    cout << "[7] Testing scope-based destruction..." << endl;
    {
        IntArray temp(3);
        temp.add(99);
        cout << "    Inside scope - Active objects: " << Tracker::getActiveCount() << endl;
    }
    cout << "    After scope  - Active objects: " << Tracker::getActiveCount() << endl;

    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}
