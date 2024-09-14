# Filter Implementations: Moving Average and Median Filters in C++ and Rust

This repository provides implementations of two fundamental signal processing filters: the **Moving Average Filter** and the **Median Filter** in both **C++** and **Rust**. These filters are essential tools for smoothing data, reducing noise, and extracting meaningful information from datasets.


## Overview

This project provides robust and efficient implementations of the Moving Average and Median filters in both C++ and Rust. The implementations are designed with performance and safety in mind, leveraging modern programming practices in each language.

- **C++ Implementation**: Utilizes templates for flexibility, efficient algorithms for median calculation, and adheres to modern C++ best practices.
- **Rust Implementation**: Emphasizes memory safety without sacrificing performance, leveraging Rust's ownership model and powerful standard library features.

## Filters Implemented

### Moving Average Filter

The Moving Average Filter smooths data by replacing each data point with the average of its neighboring points within a specified window. It's widely used for noise reduction in time series data.

**Key Features:**
- Efficient window sliding using an accumulator.
- Handles boundary conditions by extending the data with the first and last elements.
- Template-based in C++ for type flexibility.
- Safe and performant in Rust with clear error handling.

### Median Filter

The Median Filter replaces each data point with the median of its neighboring points within a specified window. It's particularly effective for removing "salt and pepper" noise while preserving edges in signals.

**Key Features:**
- Utilizes `std::nth_element` in C++ and `select_nth_unstable` in Rust for efficient median computation.
- Handles boundary conditions by extending the data with the first and last elements.
- Template-based in C++ for type flexibility.
- Safe and performant in Rust with clear error handling.

- **cpp/**: Contains the C++ implementation.
- **rust/**: Contains the Rust implementation.
- **LICENSE**: Licensing information.
- **README.md**: Project overview and instructions.


## License

This project is licensed under the [MIT License](LICENSE).

