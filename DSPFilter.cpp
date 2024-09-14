#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>

// Median filter function template
template <typename InputIt, typename OutputIt>
OutputIt MedianFilterFunc(InputIt first, InputIt last, OutputIt d_first, size_t filterLen) {
    using ValueType = typename std::iterator_traits<InputIt>::value_type;

    if (filterLen == 0) {
        throw std::invalid_argument("Filter length must be greater than 0.");
    }

    size_t halfLen = filterLen / 2;
    std::deque<ValueType> window;

    // Handle empty input
    if (first == last) {
        return d_first;
    }

    // Initialize the window with the first element replicated to handle the start boundary
    ValueType firstVal = *first;
    for (size_t i = 0; i < filterLen; ++i) {
        window.push_back(firstVal);
    }

    InputIt itr = first;
    size_t posCounter = 0;

    // Temporary vector for median calculation
    std::vector<ValueType> sortedWindow;

    // Process the input data
    while (itr != last) {
        // Update the window
        window.push_back(*itr);
        window.pop_front();

        // Copy window to a vector for sorting
        sortedWindow.assign(window.begin(), window.end());

        // Find the median using nth_element for efficiency
        std::nth_element(sortedWindow.begin(), sortedWindow.begin() + halfLen, sortedWindow.end());
        ValueType median = sortedWindow[halfLen];

        // Write the median to the output once the initial window is filled
        if (posCounter >= halfLen) {
            *d_first++ = median;
        }

        ++itr;
        ++posCounter;
    }

    // Handle the end boundary by extending the window with the last value
    ValueType lastVal = *(last - 1);
    for (size_t i = 0; i < halfLen; ++i) {
        window.push_back(lastVal);
        window.pop_front();

        sortedWindow.assign(window.begin(), window.end());
        std::nth_element(sortedWindow.begin(), sortedWindow.begin() + halfLen, sortedWindow.end());
        ValueType median = sortedWindow[halfLen];

        *d_first++ = median;
    }

    return d_first;
}

// Moving average filter function template
template <typename InputIt, typename OutputIt>
OutputIt MAFilterFunc(InputIt first, InputIt last, OutputIt d_first, size_t filterLen) {
    using ValueType = typename std::iterator_traits<InputIt>::value_type;

    if (filterLen == 0) {
        throw std::invalid_argument("Filter length must be greater than 0.");
    }

    size_t halfLen = filterLen / 2;
    ValueType accumulator = ValueType{0};

    // Handle empty input
    if (first == last) {
        return d_first;
    }

    // Initialize the accumulator with the first element replicated to handle the start boundary
    ValueType firstVal = *first;
    for (size_t i = 0; i < filterLen; ++i) {
        accumulator += firstVal;
    }

    InputIt itr = first;
    InputIt tail = first;
    size_t posCounter = 0;

    // Process the input data
    while (itr != last) {
        if (posCounter >= filterLen) {
            // Move the tail forward as the window slides
            tail = itr - filterLen;
        }
        accumulator += *itr;
        if (posCounter >= filterLen) {
            accumulator -= *tail;
        }

        // Write the average to the output once the initial window is filled
        if (posCounter >= halfLen) {
            *d_first++ = accumulator / static_cast<ValueType>(filterLen);
        }

        ++itr;
        ++posCounter;
    }

    // Handle the end boundary by extending the window with the last value
    ValueType lastVal = *(last - 1);
    for (size_t i = 0; i < halfLen; ++i) {
        accumulator += lastVal;
        accumulator -= *tail++;
        *d_first++ = accumulator / static_cast<ValueType>(filterLen);
    }

    return d_first;
}

// Function to apply filters and display results
void ApplyFiltersAndDisplay(const std::vector<int>& input, size_t filterLen) {
    // Ensure filter length is appropriate
    if (filterLen == 0) {
        std::cerr << "Filter length must be greater than 0.\n";
        return;
    }

    // Prepare output containers with sufficient size
    std::vector<int> movingAvgFilteredData;
    movingAvgFilteredData.reserve(input.size() + filterLen); // Reserve extra space for boundary handling

    std::vector<int> medianFilteredData;
    medianFilteredData.reserve(input.size() + filterLen);

    // Apply Moving Average Filter
    try {
        MAFilterFunc(input.begin(), input.end(), std::back_inserter(movingAvgFilteredData), filterLen);
    } catch (const std::exception& e) {
        std::cerr << "Error in Moving Average Filter: " << e.what() << '\n';
        return;
    }

    // Apply Median Filter
    try {
        MedianFilterFunc(input.begin(), input.end(), std::back_inserter(medianFilteredData), filterLen);
    } catch (const std::exception& e) {
        std::cerr << "Error in Median Filter: " << e.what() << '\n';
        return;
    }

    // Display the results
    std::cout << "Original Data:\n";
    for (const auto& val : input)
        std::cout << val << ' ';
    std::cout << "\n\nMoving Average Filtered Data:\n";
    for (const auto& val : movingAvgFilteredData)
        std::cout << val << ' ';
    std::cout << "\n\nMedian Filtered Data:\n";
    for (const auto& val : medianFilteredData)
        std::cout << val << ' ';
    std::cout << '\n';
}

int main() {
    // Sample input data
    std::vector<int> data = { 5, 3, 8, 9, 2, 7, 4, 6, 1, 0, 3, 5, 2 };

    // Define filter length (must be odd for median filter to have a central element)
    size_t filterLength = 3;

    // Apply filters and display results
    ApplyFiltersAndDisplay(data, filterLength);

    return 0;
}
