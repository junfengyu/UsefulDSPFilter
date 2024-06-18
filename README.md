
# Real-Time Signal Filtering

This project provides implementations of the Moving Average (MA) filter and the Median filter in C++. These filters are applied to a series of signal data to smooth out noise and spikes. The project includes code to test these filters with different input vectors, including a vector of size 255.

## Features

- **Moving Average Filter**: Smooths the input data by averaging over a fixed number of previous samples.
- **Median Filter**: Smooths the input data by taking the median value over a fixed number of previous samples.
- **Modular Design**: Functions are designed to be reusable and modular.
- **Test Cases**: Includes test cases to verify the functionality of the filters.

## Getting Started

### Prerequisites

- C++11 compatible compiler (e.g., `g++`)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/realtime-signal-filtering.git
   cd realtime-signal-filtering
   ```

2. Compile the code:
   ```bash
   g++ -o filters filters.cpp
   ```

### Usage

Run the compiled program:
```bash
./filters
```

The program will apply both the Moving Average and Median filters to two test vectors and display the filtered results.

### Code Overview

The main components of the code are:

- **`MedianFilterFunc`**: Template function to apply the Median filter.
- **`MAFilterFunc`**: Template function to apply the Moving Average filter.
- **`ApplyFiltersAndDisplay`**: Function to apply the filters to an input vector and display the results.
- **`TestFilters`**: Function to test the filters with different input vectors.
- **`main`**: Entry point of the program that calls `TestFilters`.

### Example Output

When you run the program, you will see output similar to the following:

```
Test with first vector (size: 70):
Moving Average Filtered Data:
... (filtered data) ...
Median Filtered Data:
... (filtered data) ...

Test with second vector (size: 255):
Moving Average Filtered Data:
... (filtered data) ...
Median Filtered Data:
... (filtered data) ...
```
