#ifndef LIBRARYASSIGNMENT_UTILS_H
#define LIBRARYASSIGNMENT_UTILS_H

#include <vector>

template<typename T> using GTCompare = bool (*)(const T &, const T &);

class Utils {
public:
    /**
     * Heap Sort implementation that can be used in place of std::sort in the application.
     */
    template<typename T>
    static void HeapSort(std::vector<T> toSort, GTCompare<T> greaterThan);

    template<typename T>
    static int BinarySearch(std::vector<T> sorted, T value);
};

template<typename T>
void Swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void Heapify(std::vector<T> toShift, int size, int start, GTCompare<T> greaterThan) {
    int largest = start;
    int l = 2 * start + 1;
    int r = 2 * start + 2;

    if (l < size && greaterThan(toShift[l], toShift[largest]))
        largest = l;

    // If right child is larger than largest so far
    if (r < size && greaterThan(toShift[r], toShift[largest]))
        largest = r;

    // If largest is not root
    if (largest != start) {
        swap(toShift[start], toShift[largest]);

        // Recursively heapify the affected sub-tree
        Heapify(toShift, size, largest, greaterThan);
    }
}

template<typename T>
void Utils::HeapSort(std::vector<T> toSort, GTCompare<T> greaterThan) {
    //build heap -- only need to heapify non-leaf nodes
    int size = toSort.size();
    for (int i = size / 2 - 1; i >= 0; i--)
        Heapify(toSort, size, i, greaterThan);

    for (int i = size - 1; i > 0; i--) {
        Swap(toSort[0], toSort[i]);
        Heapify(toSort, i, 0, greaterThan);
    }
}

template<typename T> int binarySearch(std::vector<T> sortedArray, int l, int r, T x)
{
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        // If the element is present at the middle itself
        if (sortedArray[mid] == x)  return mid;

        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (sortedArray[mid] > x) return binarySearch(sortedArray, l, mid - 1, x);

        // Else the element can only be present in right subarray
        return binarySearch(sortedArray, mid + 1, r, x);
    }

    // We reach here when element is not present in array
    return -1;
}

template<typename T>
int Utils::BinarySearch(std::vector<T> sorted, T value) {
    return binarySearch<T>(sorted, 0, sorted.size() - 1, value);
}

#endif //LIBRARYASSIGNMENT_UTILS_H
