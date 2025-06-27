#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Typedef for a pointer to an array of unspecified size
typedef int (*IntArrayPtr)[];

// Bubble Sort function that sorts an array in-place and returns a pointer to it
IntArrayPtr bubblesort(int size, int *arr, IntArrayPtr ret_ptr) {//b1
    int trav = 0;

    // INT_MAX used to enter the outer loop the first time
    int swap_flag = INT_MAX;

    // Used as a pointer to hold and iterate bubble index dynamically
    int *bubble = malloc(sizeof(int));

    // Outer loop: continues until no swaps are made in a pass (optimized bubble sort)
    for (int *phase = &trav; (*phase < size - 1) && (swap_flag > (*phase + 1 - size)) ; (*phase)++) {//b2
        swap_flag = 0; // Reset swap flag for this pass

        // Inner loop: compares adjacent elements and swaps them if needed
        for (*bubble = 0; (*bubble < size - 1 - *phase) ; (*bubble)++) {//b3

            // XOR-swap trick used for swapping without temp variable
            // Cleverly uses ternary and side effects: swap_flag++ or swap_flag-- to track swaps
            arr[*bubble] = (arr[*bubble] > arr[*bubble + 1]
                            ?
                            ((arr[*bubble] ^= (arr[*bubble + 1] ^= (arr[*bubble] ^= arr[*bubble + 1]))) + (swap_flag++)*0)
                            :
                            (arr[*bubble] + (swap_flag--)*0)
            );
        }//b3
    }//b2

    // Cleanup dynamically allocated bubble pointer
    free(bubble);
    bubble = NULL;

    // Return pointer to sorted array (same as input in this case)
    return ret_ptr;
}//b1

// Function to display array elements using pointer-to-array syntax
void display(int size, IntArrayPtr ptr_to_arr) {//b4
    for (int i = 0; i < size; i++)
        printf("array[%d] :- %d\n", i, (*ptr_to_arr)[i]);
}//b4


int main() {//b5
    // Allocate memory for array size (records holds the value entered by user)
    int *records = malloc(sizeof(int));

    printf("Enter the size of array :- ");
    scanf("%d", records);

    // Allocate memory for array elements based on user input
    int *array = malloc((*records) * sizeof(int));

    // Input loop to fill the array
    for (int i = 0; i < *records; i++) {//b6
        printf("Enter array[%d] :- ", i);
        scanf("%d", &array[i]);
    }//b6

    // Function pointer for bubblesort, for flexibility or callbacks
    IntArrayPtr (*bubblesort_ptr)(int,int*,IntArrayPtr) = bubblesort;

    // Call bubble sort and get pointer to sorted array
    IntArrayPtr final_arr = bubblesort_ptr(*records, array, (IntArrayPtr)array);

    // Display the sorted array
    display(*records, final_arr);

    // Cleanup dynamic memory
    free(array);
    free(records);
    return 0;
}//b5

