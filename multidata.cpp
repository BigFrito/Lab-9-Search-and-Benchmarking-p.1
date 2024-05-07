#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

/**
 * @brief returns the first index of elem if it exists, otherwise returns -1
 * iteraticeSearch starts at the first index and iterates sequentially to the next until it either
 * finds the element or until it reaches the end (i.e. element does not exist)
 * 
 * @param v: vector of elements
 * @param elem: integer to look for
 * @return int
*/
template<typename T>
int interativeSearch(vector<T> & v, const T elem){
    for(T i = 0; i < v.size(); ++i){
        if(v[i] == elem){
            return i;
        }
    }
    return -1;
}

/**
 * @brief returns the index of elem, if it exists in v. Otherwise it returns -1.
 * binarySearch is recursive (i.e. function calls intself).
 * It utilizes the fact that v is increasing order (e.g. values go up and
 * duplicates are not allowed).
 * 
 * It calculates the mid from the start and end index. It compares v[mid](i.e. value
 * at mid) with elem and decides whether to search the left half (lower values)
 * or right half (upper values)
 * 
 * 
 * @param v: vector of elements
 * @param start: leftmost index (starting value is 0)
 * @param end: right most index (starting value is v.size())
 * @param elem: integer to look for
 * @return int
*/
template<typename T>
int binarySearch(vector<T> & v, int start, int end, const T& elem){
    if(start > end){
        return-1;
    }
T mid = (start + end) / 2;
if (v[mid] > elem){         //search left half
    end = mid -1;
} else if (v[mid] < elem){  //search right half
    start = mid + 1;
} else {                    //found elem
    return mid;
}
return binarySearch(v, start, end, elem);
}

/**
 * @brief updates v to contain the values from filename (leave as is)
 * 
 * It is expected that the files contain values ranging from one to
 * one hundred million in ascending order (no duplicates).
 * 
 * @param filename: string
 * @param v: vector
 */
template<typename T>
void vecGen(string filename, vector<T> & v){
    ifstream file(filename);
    T num;
    v.clear();
    while (file.is_open() && file >> num){
        v.push_back(num);
    }
    file.close();
}

int main(){
    // populate v with 10000 sorted numbers (leave as is)
    vector<int> v;
    vecGen("10000_numbers.csv", v);

    // test elements to search for (leave as is)
    vector<int> elem_to_find;
    vecGen("test_elem.csv", elem_to_find);


    // reads through all 10 of the test_elem values and call interative search
    // and records how long each search took (leave as is)
    for(int i = 0; i< elem_to_find.size(); i++){
        // gets the elem to search for
        int elem = elem_to_find[i];

        // stopwatches the time
        clock_t start = clock();                            // start time
        int index_if_found = interativeSearch(v, elem);     // call search
        clock_t end = clock();                              // end time

        // calculates the total time it took in seconds
        double elapsed_time_in_sec = (double(end - start)/CLOCKS_PER_SEC);

        // prints the index and how long it took to find it
        cout << index_if_found << ": " << elapsed_time_in_sec << endl;
    }

    // repeat the for loop above so that it records the time
    for(int i = 0; i< elem_to_find.size(); i++){
        // gets the elem to search for
        int elem = elem_to_find[i];

        // stopwatches the time
        clock_t start = clock();                            // start time
        int index_if_found = binarySearch(v, 0, v.size(), elem);     // call search
        clock_t end = clock();                              // end time

        // calculates the total time it took in seconds
        double elapsed_time_in_sec = (double(end - start)/CLOCKS_PER_SEC);

        // prints the index and how long it took to find it
        cout << index_if_found << ": " << elapsed_time_in_sec << endl;
    }
    // it takes for binarySearch to do the same operation
}