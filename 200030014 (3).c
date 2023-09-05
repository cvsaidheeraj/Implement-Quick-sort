#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two integers using pointers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to do partition of the array for quickSort
int partition(int arr[], int low, int high) {
    // Randomly select the pivot
    srand(time(NULL));
    int random_index = rand() % (high - low + 1) + low;
    int pivot = arr[random_index];

    // Move the pivot to the beginning of the array
    swap(&arr[low], &arr[random_index]);

    int i = low;

    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i], &arr[low]);
    return i;
}

// Function to implement quickSort algorithm
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Main function to read from input file, sort array, and write to output file
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *in_file = fopen(argv[1], "r");
    if (!in_file) {
        printf("Unable to open input file: %s\n", argv[1]);
        return 1;
    }

    // Open output file
    FILE *out_file = fopen("quicksort.txt", "w");
    if (!out_file) {
        printf("Unable to create output file: quicksort.txt\n");
        return 1;
    }

    int n = 0;
    int temp;

    // Count the number of integers in the input file
    while (fscanf(in_file, "%d", &temp) == 1) {
        n++;
    }

    // Allocate memory for the array
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        printf("Unable to allocate memory for array.\n");
        return 1;
    }

    // Rewind the input file to read from the beginning
    fseek(in_file, 0, SEEK_SET);

    // Read integers from the input file and store them in the array
    for (int i = 0; i < n; i++) {
        if (fscanf(in_file, "%d", &arr[i]) != 1) {
            printf("Unable to read element %d from input file.\n", i);
            return 1;
        }
    }

    // Sort the array using quickSort algorithm
    quickSort(arr, 0, n - 1);

    // Write the sorted array to the output file
    for (int i = 0; i < n; i++) {
        fprintf(out_file, "%d\n", arr[i]);
    }


// close input and output files
    fclose(in_file);
    fclose(out_file);

    free(arr);

    return 0;
}
