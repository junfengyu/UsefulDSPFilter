
# Real-Time Signal Filtering

This project provides implementations of the Moving Average (MA) filter and the Median filter in C++. These filters are applied to a series of signal data to smooth out noise and spikes. 

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
   git clone https://github.com/junfengyu/UsefulDSPFilter.git
   cd UsefulDSPFilter
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

