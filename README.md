# Quicksort
A modification of Hoarse's partition algorithm. Pivot is 
calculated as a median of the first, last and middle elements.
After partition the smaller subarray is processed recursively, while
the larger part is sorted iteratively. 

### Features
- Makes use of templates
- INSERTION_THRESHOLD is the parameter used to switch the sorting algorithm to insertion sort while processing a smaller structure. It's used to avoid the overhead of implemented hybrid algorithm when appropriate
- Google Tests