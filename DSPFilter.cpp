#include <iostream>
#include <vector>
#include <deque>
#include <numeric>
#include <array>
#include <algorithm>
using namespace std;

// Median filter function template
template<class InputIt, class OutputIt>
OutputIt MedianFilterFunc(InputIt first1, InputIt last1, OutputIt d_first, unsigned short FilterLen)
{
    // 1. Prefill the working deque
    unsigned short halflen = FilterLen / 2;
    deque<typename InputIt::value_type> workdeque;
    auto first1val = *first1;

    for (int i = 1; i < FilterLen; i++)
        workdeque.push_back(first1val);

    // 2. Run filter
    InputIt itr_front = first1;
    OutputIt itr_out = d_first;
    int poscounter = 0;
    while (itr_front != last1)
    {
        workdeque.push_back(*itr_front);
        workdeque.pop_front();
        vector<typename InputIt::value_type> sortingvec(workdeque.begin(), workdeque.end());
        nth_element(sortingvec.begin(), sortingvec.begin() + halflen, sortingvec.end());
        if (poscounter >= halflen) {
            *itr_out = *(sortingvec.begin() + halflen);
            itr_out++;
        }
        itr_front++;
        poscounter++;
    }

    // 3. Extend the end
    auto last1val = *(last1 - 1);
    for (int i = 0; i < halflen; i++)
    {
        workdeque.push_back(last1val);
        workdeque.pop_front();
        vector<typename InputIt::value_type> sortingvec(workdeque.begin(), workdeque.end());
        nth_element(sortingvec.begin(), sortingvec.begin() + halflen, sortingvec.end());
        *itr_out = *(sortingvec.begin() + halflen);
        itr_out++;
    }
    return d_first;
}

// Moving average filter function template
template<class InputIt, class OutputIt>
OutputIt MAFilterFunc(InputIt first1, InputIt last1, OutputIt d_first, unsigned short FilterLen)
{
    // 1. Prefill the accumulator
    unsigned short halflen = FilterLen / 2;
    typename InputIt::value_type accu{ 0 };
    auto first1val = *first1;
    for (int i = 1; i < FilterLen; i++)
        accu += first1val;

    // 2. Run filter
    InputIt itr_front = first1;
    OutputIt itr_out = d_first;
    int poscounter = 0;
    auto itr_tail = first1;
    while (itr_front != last1)
    {
        if (poscounter >= FilterLen)
            itr_tail = itr_front - FilterLen;
        accu += *itr_front;
        accu -= *itr_tail;
        if (poscounter >= halflen) {
            *itr_out = accu / FilterLen;
            itr_out++;
        }
        itr_front++;
        poscounter++;
    }

    // 3. Extend the end
    auto last1value = *(last1 - 1);
    for (int i = 0; i < halflen; i++)
    {
        accu += last1value;
        accu -= *itr_tail;
        *itr_out = accu / FilterLen;
        itr_tail++;
        itr_out++;
    }
    return d_first;
}

// Function to apply filters and display results
void ApplyFiltersAndDisplay(const vector<int>& input, unsigned short filterLen) {
    vector<int> filteredData(input.size());
    vector<int> medianFilteredData(input.size());

    MAFilterFunc(input.begin(), input.end(), filteredData.begin(), filterLen);
    MedianFilterFunc(input.begin(), input.end(), medianFilteredData.begin(), filterLen);

    cout << "Moving Average Filtered Data:\n";
    for (const auto& val : filteredData)
        cout << val << " ";
    cout << "\n\nMedian Filtered Data:\n";
    for (const auto& val : medianFilteredData)
        cout << val << " ";
    cout << endl;
}

// Test function
void TestFilters() {
    vector<int> testVector1 = {
        537, 536, 535, 534, 533, 532, 531, 530, 529, 528, 527, 527, 526, 526, 525, 524, 524, 1523, 1523, 1523,
        1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 2523, 2673, 2523, 2100, 1523, 1523,
        1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 1523, 524, 524, 525, 526, 527, 528, 528, 529,
        530, 531, 531, 532, 533, 534, 534, 536, 537, 538, 541, 542, 544, 546
    };

    vector<int> testVector2(255, 100); // Vector of size 255 with all values set to 100
    testVector2[127] = 200; // Add a peak to test the filter

    cout << "Test with first vector (size: " << testVector1.size() << "):\n";
    ApplyFiltersAndDisplay(testVector1, 50);

    cout << "\nTest with second vector (size: " << testVector2.size() << "):\n";
    ApplyFiltersAndDisplay(testVector2, 50);
}

int main() {
    TestFilters();
    return 0;
}
