#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
typedef int** solptr;
typedef int* arrptr[];
typedef int* temp;

// Your original bubble sort implementation
solptr rec_bubblesort(int *arr,
                     int phase,
                     int bubble,
                     int* ref_trav,
                     int trav,
                     int *size,
                     solptr soln,
                     bool* swap_flag,
                     bool* base_flag)
{
    if (*swap_flag) {
        return soln;
    }

    if (phase >= *size) {
        *base_flag = true;
        return soln;
    }

   soln[phase] =
                (bubble > 0) ?
                (trav > -1) ?
                (arr[trav+1] < arr[bubble-1]) ?
                (phase == 0) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                (arr[trav+1] >= (*soln[phase-1])) ?
                (*ref_trav != trav+1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                (arr[bubble-1] > (*soln[phase-1])) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase]:
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav == bubble-1) ?
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]:
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]:
                (phase != 0 && trav != bubble - 2) ?
                (arr[bubble - 1] <= arr[*ref_trav]) ?
                (arr[bubble - 1] == arr[*ref_trav]) ?
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav >= bubble-1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]:
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]:
                (arr[trav+1] >= (*soln[phase-1])) ?
                (*ref_trav >= trav+1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]:
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]:
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav == bubble-1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]:
                (arr[trav+1] >= (*soln[phase-1])) ?
                (*ref_trav == trav+1) ?
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]:
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]:
                (trav == bubble - 2) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]:
                (*swap_flag = true, &arr[trav+1]):
                &arr[trav+1];
         
    if (bubble == 0) {
        *ref_trav = trav + 1;
    }

    if (*base_flag) {
        *swap_flag = true;
        return soln;
    }

    if (!(*swap_flag)) {
        return rec_bubblesort(arr,
                              phase + 1,
                              *size - 1,
                              ref_trav,
                              *size - 2,
                              size,
                              soln,
                              swap_flag,
                              base_flag);
    }

    return soln;
}

void attach(int size, int* arr, solptr ptr_ptr) {
    for (int i = 0; i < size; i++) {
        ptr_ptr[i] = &arr[i];
    }
}

#define MAX_SIZE 100

void print_array(int *arr, int size, const char *label) {
    printf("%s: { ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}
void print_array2(int **arr, int size, const char *label) {
    printf("%s: { ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", *arr[i]);
    }
    printf("}\n");
}

void test_case(int *arr, int size, const char *desc, int test_num) {
    printf("\n=== Test Case %d: %s ===\n", test_num, desc);
    int *ref_trav = (int *)calloc(1, sizeof(int));
    int *size_ptr = (int *)malloc(sizeof(int));
    *size_ptr = size;
    bool *swap_flag = (bool *)calloc(1, sizeof(bool));
    bool *base_flag = (bool *)calloc(1, sizeof(bool));
    solptr solution = (int **)malloc(sizeof(int *) * MAX_SIZE); // Adjust for safety

    print_array(arr, size, "Input");

    // Call recursive bubble sort
    solution = rec_bubblesort(arr, 0, 0, ref_trav, 0, size_ptr, solution, swap_flag, base_flag);

    print_array2(solution, size, "Sorted");

    free(ref_trav);
    free(size_ptr);
    free(swap_flag);
    free(base_flag);
    free(solution);
}

void display(int size, solptr ptr_ptr) {//b4
    for (int i = 0; i < size; i++)
        printf("array[%d] :- %d\n", i, (*ptr_ptr[i]));
}//b4


bool main() {//b5
    // Allocate memory for array size (records holds the value entered by user)
    int *records = malloc(sizeof(int)); 
    printf("Enter the size of array :- ");
    scanf("%d", records);

    bool flag = false;
    bool bflag = false;
    int* ref = (int*)malloc(sizeof(int));
    *ref = -1;
    int **sortarr = malloc((*records) * sizeof(int*)); // ✅ uses initialized value
    // Allocate memory for array elements based on user input
    int *array = malloc((*records) * sizeof(int));

    // Input loop to fill the array
    /*for (int i = 0; i < *records; i++) {//b6
        printf("Enter array[%d] :- ", i);
        scanf("%d", &array[i]);
    }//b6*/
    //int a[] = { 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int a[] = {42};
    attach(*records , a , sortarr);
    // Function pointer for bubblesort, for flexibility or callbacks
    solptr (*rec_bubblesort_ptr)(int*,int,int,int*,int,int*,solptr,bool*,bool*) = rec_bubblesort;

    // Call bubble sort and get pointer to sorted array
    solptr final_arr = rec_bubblesort_ptr(a, 0 , *records - 1, ref, *records - 2 , records , (solptr)sortarr , &flag, &bflag);

    // Display the sorted array
    display(*records, final_arr);
   
                                    
    // Cleanup dynamic memory
    free(array);
    array = NULL;
    free(records);

    free(sortarr);
    sortarr = NULL;
    free(ref);
    ref = NULL;
    //free(final_arr);
    records = NULL;
    return true;
}//b5


