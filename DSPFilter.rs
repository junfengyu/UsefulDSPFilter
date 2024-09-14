
/// Applies a moving average filter to the input data.
///
/// # Arguments
///
/// * `input` - A slice of integers to be filtered.
/// * `filter_len` - The length of the moving average window.
///
/// # Returns
///
/// A vector containing the moving average filtered data.
///
/// # Panics
///
/// Panics if `filter_len` is zero.
fn moving_average_filter(input: &[i32], filter_len: usize) -> Vec<i32> {
    if filter_len == 0 {
        panic!("Filter length must be greater than 0.");
    }

    let half_len = filter_len / 2;
    let mut filtered = Vec::with_capacity(input.len() + filter_len);

    // Handle empty input
    if input.is_empty() {
        return filtered;
    }

    // Initialize the accumulator with the first element replicated filter_len times
    let first_val = input[0];
    let mut accumulator: i64 = (0..filter_len).map(|_| first_val as i64).sum();
    
    let len = input.len();

    // Process the input data
    for (pos, &current) in input.iter().enumerate() {
        if pos >= filter_len {
            // Subtract the element that is moving out of the window
            accumulator -= input[pos - filter_len] as i64;
        }
        // Add the current element
        accumulator += current as i64;

        // Once the initial window is filled, start recording the average
        if pos >= half_len {
            let avg = (accumulator / filter_len as i64) as i32;
            filtered.push(avg);
        }
    }

    // Handle the end boundary by extending the window with the last value
    let last_val = *input.last().unwrap();
    for i in 0..half_len {
        accumulator += last_val as i64;
        if filter_len <= i + 1 {
            accumulator -= input[len - filter_len + i + 1] as i64;
        }
        let avg = (accumulator / filter_len as i64) as i32;
        filtered.push(avg);
    }

    filtered
}

/// Applies a median filter to the input data.
///
/// # Arguments
///
/// * `input` - A slice of integers to be filtered.
/// * `filter_len` - The length of the median window.
///
/// # Returns
///
/// A vector containing the median filtered data.
///
/// # Panics
///
/// Panics if `filter_len` is zero.
fn median_filter(input: &[i32], filter_len: usize) -> Vec<i32> {
    if filter_len == 0 {
        panic!("Filter length must be greater than 0.");
    }

    let half_len = filter_len / 2;
    let mut filtered = Vec::with_capacity(input.len() + filter_len);

    // Handle empty input
    if input.is_empty() {
        return filtered;
    }

    // Initialize the window with the first element replicated filter_len times
    let first_val = input[0];
    let mut window = Vec::with_capacity(filter_len);
    for _ in 0..filter_len {
        window.push(first_val);
    }

    // Temporary vector for median calculation
    let mut sorted_window = Vec::with_capacity(filter_len);

    // Process the input data
    for (pos, &current) in input.iter().enumerate() {
        // Update the window
        window.push(current);
        window.remove(0);

        // Copy and sort the window to find the median
        sorted_window.clear();
        sorted_window.extend_from_slice(&window);
        sorted_window.select_nth_unstable(half_len);
        let median = sorted_window[half_len];

        // Write the median to the output once the initial window is filled
        if pos >= half_len {
            filtered.push(median);
        }
    }

    // Handle the end boundary by extending the window with the last value
    let last_val = *input.last().unwrap();
    for _ in 0..half_len {
        window.push(last_val);
        window.remove(0);

        sorted_window.clear();
        sorted_window.extend_from_slice(&window);
        sorted_window.select_nth_unstable(half_len);
        let median = sorted_window[half_len];

        filtered.push(median);
    }

    filtered
}

/// Applies both moving average and median filters to the input data and displays the results.
///
/// # Arguments
///
/// * `input` - A vector of integers to be filtered.
/// * `filter_len` - The length of the filter window.
///
fn apply_filters_and_display(input: &[i32], filter_len: usize) {
    // Apply Moving Average Filter
    let moving_avg_filtered = moving_average_filter(input, filter_len);

    // Apply Median Filter
    let median_filtered = median_filter(input, filter_len);

    // Display the results
    println!("Original Data:");
    for &val in input {
        print!("{} ", val);
    }
    println!("\n");

    println!("Moving Average Filtered Data:");
    for val in &moving_avg_filtered {
        print!("{} ", val);
    }
    println!("\n");

    println!("Median Filtered Data:");
    for val in &median_filtered {
        print!("{} ", val);
    }
    println!();
}

fn main() {
    // Sample input data
    let data = vec![5, 3, 8, 9, 2, 7, 4, 6, 1, 0, 3, 5, 2];

    // Define filter length (should be odd for median filter to have a central element)
    let filter_length = 3;

    // Apply filters and display results
    apply_filters_and_display(&data, filter_length);
}

