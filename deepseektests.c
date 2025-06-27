
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// ANSI Color Codes for Terminal Output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

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

// Test structure
typedef struct {
    char name[100];
    int* input;
    int* expected;
    int size;
    bool is_dynamic; // Track if input array is dynamically allocated
} TestCase;

// Utility function to create array copy
int* copy_array(int* arr, int size) {
    int* copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    return copy;
}

// Utility function to check if array is sorted
bool is_sorted(int** result, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (*result[i] > *result[i + 1]) {
            return false;
        }
    }
    return true;
}

// Function to run a single test
bool run_test(TestCase* test) {
    int* test_array = copy_array(test->input, test->size);
    int* size_ptr = malloc(sizeof(int));
    *size_ptr = test->size;
    
    bool flag = false;
    bool bflag = false;
    int* ref = malloc(sizeof(int));
    *ref = -1;
    
    int** sortarr = malloc(test->size * sizeof(int*));
    attach(test->size, test_array, sortarr);
    
    solptr result = rec_bubblesort(
        test_array, 0, test->size - 1, ref, test->size - 2,
        size_ptr, sortarr, &flag, &bflag
    );
    
    bool passed = is_sorted(result, test->size);
    
    // Additional check: verify all elements are present
    if (passed) {
        int* sorted_values = malloc(test->size * sizeof(int));
        for (int i = 0; i < test->size; i++) {
            sorted_values[i] = *result[i];
        }
        
        // Simple check: count occurrences
        for (int i = 0; i < test->size; i++) {
            int count_orig = 0, count_sorted = 0;
            for (int j = 0; j < test->size; j++) {
                if (test->input[j] == test->input[i]) count_orig++;
                if (sorted_values[j] == test->input[i]) count_sorted++;
            }
            if (count_orig != count_sorted) {
                passed = false;
                break;
            }
        }
        free(sorted_values);
    }
    
    // Cleanup
    free(test_array);
    free(size_ptr);
    free(ref);
    free(sortarr);
    
    return passed;
}

// Print test result with colored dots and bold text
void print_result(char* test_name, bool passed) {
    if (passed) {
        printf("%s● %s[PASS]%s %s\n", GREEN, BOLD, RESET, test_name);
    } else {
        printf("%s● %s[FAIL]%s %s\n", RED, BOLD, RESET, test_name);
    }
}

// Function to check if key is pressed (non-blocking)
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Array generation helper functions
int* generate_random_array(int size, int min, int max) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}

int* generate_sorted_array(int size, int start, int step) {
    int* arr = malloc(size * sizeof(int));
    arr[0] = start;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i-1] + step;
    }
    return arr;
}

int* generate_reverse_sorted_array(int size, int start, int step) {
    int* arr = malloc(size * sizeof(int));
    arr[0] = start;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i-1] - step;
    }
    return arr;
}

int* generate_all_same_array(int size, int value) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
    return arr;
}

int* generate_duplicates_array(int size, int distinct_count) {
    int* distinct_values = malloc(distinct_count * sizeof(int));
    for (int i = 0; i < distinct_count; i++) {
        distinct_values[i] = rand() % 100;
    }
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = distinct_values[rand() % distinct_count];
    }
    free(distinct_values);
    return arr;
}

int* generate_nearly_sorted_array(int size, int swap_count) {
    int* arr = generate_sorted_array(size, 0, 1);
    for (int i = 0; i < swap_count; i++) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
    return arr;
}

int* generate_mountain_array(int size) {
    int* arr = malloc(size * sizeof(int));
    int mid = size / 2;
    for (int i = 0; i <= mid; i++) {
        arr[i] = i;
    }
    for (int i = mid+1; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}

int* generate_valley_array(int size) {
    int* arr = malloc(size * sizeof(int));
    int mid = size / 2;
    for (int i = 0; i <= mid; i++) {
        arr[i] = mid - i;
    }
    for (int i = mid+1; i < size; i++) {
        arr[i] = i - mid;
    }
    return arr;
}

int* generate_alternating_array(int size, int low, int high) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = (i % 2 == 0) ? low : high;
    }
    return arr;
}

int* generate_arithmetic_array(int size, int start, int step) {
    return generate_sorted_array(size, start, step);
}

int* generate_geometric_array(int size, int start, int factor) {
    int* arr = malloc(size * sizeof(int));
    arr[0] = start;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i-1] * factor;
    }
    return arr;
}

int* generate_permutation(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    for (int i = size-1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}

int* generate_almost_constant_array(int size, int constant, int different_index, int different_value) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = constant;
    }
    arr[different_index] = different_value;
    return arr;
}

int main() {
    printf("\033[2J\033[H"); // Clear screen and move cursor to top
    printf("%s%sBUBBLE SORT TEST SUITE%s\n", BOLD, CYAN, RESET);
    printf("================================\n\n");
    
    // Initialize test cases
    TestCase tests[1000];
    int test_count = 0;
    
    // Original test cases (99 tests)
    // Test 1: Single element
    int* arr1 = malloc(sizeof(int));
    arr1[0] = 5;
    tests[test_count] = (TestCase){
        "Single element", arr1, NULL, 1, true
    };
    test_count++;
    
    // Test 2: Two elements (ascending)
    int* arr2 = malloc(2 * sizeof(int));
    arr2[0] = 1; arr2[1] = 2;
    tests[test_count] = (TestCase){
        "Two elements ascending", arr2, NULL, 2, true
    };
    test_count++;
    
    // Test 3: Two elements (descending)
    int* arr3 = malloc(2 * sizeof(int));
    arr3[0] = 2; arr3[1] = 1;
    tests[test_count] = (TestCase){
        "Two elements descending", arr3, NULL, 2, true
    };
    test_count++;
    
    // Test 4: Already sorted
    int* arr4 = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) arr4[i] = i + 1;
    tests[test_count] = (TestCase){
        "Already sorted array", arr4, NULL, 5, true
    };
    test_count++;
    
    // Test 5: Reverse sorted
    int* arr5 = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) arr5[i] = 5 - i;
    tests[test_count] = (TestCase){
        "Reverse sorted array", arr5, NULL, 5, true
    };
    test_count++;
    
    // Test 6-15: Random small arrays
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 8) + 3; // 3-10 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 100;
        }
        sprintf(tests[test_count].name, "Random array %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 16-25: Arrays with duplicates
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 6) + 4; // 4-9 elements
        int* arr = malloc(size * sizeof(int));
        int base_val = rand() % 10;
        for (int j = 0; j < size; j++) {
            arr[j] = base_val + (rand() % 3);
        }
        sprintf(tests[test_count].name, "Duplicates array %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 26-35: All same elements
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 7) + 3; // 3-9 elements
        int* arr = malloc(size * sizeof(int));
        int val = rand() % 50;
        for (int j = 0; j < size; j++) {
            arr[j] = val;
        }
        sprintf(tests[test_count].name, "All same elements %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 36-45: Negative numbers
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 6) + 4; // 4-9 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = (rand() % 100) - 50;
        }
        sprintf(tests[test_count].name, "Negative numbers %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 46-55: Large numbers
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 5) + 3; // 3-7 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 10000 + 1000;
        }
        sprintf(tests[test_count].name, "Large numbers %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 56-65: Edge cases with zeros
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 5) + 3; // 3-7 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = (rand() % 3) - 1;
        }
        sprintf(tests[test_count].name, "Around zero %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 66-75: Partially sorted arrays
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 6) + 5; // 5-10 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size/2; j++) {
            arr[j] = j;
        }
        for (int j = size/2; j < size; j++) {
            arr[j] = rand() % 100;
        }
        sprintf(tests[test_count].name, "Partially sorted %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 76-85: Nearly sorted (one swap needed)
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 5) + 4; // 4-8 elements
        int* arr = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = j * 2;
        }
        if (size >= 2) {
            int temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        sprintf(tests[test_count].name, "Nearly sorted %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 86-95: Mountain arrays (peak in middle)
    for (int i = 0; i < 10; i++) {
        int size = (rand() % 5) + 5; // 5-9 elements
        int* arr = malloc(size * sizeof(int));
        int mid = size / 2;
        for (int j = 0; j < mid; j++) {
            arr[j] = j;
        }
        for (int j = mid; j < size; j++) {
            arr[j] = size - j - 1;
        }
        sprintf(tests[test_count].name, "Mountain array %d (size %d)", i+1, size);
        tests[test_count].input = arr;
        tests[test_count].expected = NULL;
        tests[test_count].size = size;
        tests[test_count].is_dynamic = true;
        test_count++;
    }
    
    // Test 96-99: Special patterns
    int* fib_arr = malloc(8 * sizeof(int));
    int fib_vals[] = {8, 5, 13, 3, 21, 2, 1, 1};
    for (int i = 0; i < 8; i++) fib_arr[i] = fib_vals[i];
    tests[test_count] = (TestCase){
        "Fibonacci sequence", fib_arr, NULL, 8, true
    };
    test_count++;
    
    int* pow_arr = malloc(7 * sizeof(int));
    int pow_vals[] = {64, 1, 16, 4, 32, 2, 8};
    for (int i = 0; i < 7; i++) pow_arr[i] = pow_vals[i];
    tests[test_count] = (TestCase){
        "Powers of 2", pow_arr, NULL, 7, true
    };
    test_count++;
    
    int* alt_arr = malloc(10 * sizeof(int));
    int alt_vals[] = {1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
    for (int i = 0; i < 10; i++) alt_arr[i] = alt_vals[i];
    tests[test_count] = (TestCase){
        "Alternating pattern", alt_arr, NULL, 10, true
    };
    test_count++;
    
    int* three_arr = malloc(3 * sizeof(int));
    three_arr[0] = 3; three_arr[1] = 2; three_arr[2] = 1;
    tests[test_count] = (TestCase){
        "Three elements reverse", three_arr, NULL, 3, true
    };
    test_count++;
    
    // Test 100: Size 0 array
    int* arr0 = malloc(0);
    tests[test_count] = (TestCase){
        "Size 0 array", arr0, NULL, 0, true
    };
    test_count++;
    
    // Generate 97 tests for very small arrays (sizes 1-5)
    for (int size = 1; size <= 5; size++) {
        int count_per_size = (size == 1) ? 19 : 
                            (size == 2) ? 18 : 20;
        for (int i = 0; i < count_per_size; i++) {
            int* arr = generate_random_array(size, -100, 100);
            char name[100];
            sprintf(name, "Very small random %d (size %d)", i+1, size);
            tests[test_count] = (TestCase){
                name, arr, NULL, size, true
            };
            test_count++;
        }
    }
    
    // Generate 400 tests for large arrays (sizes 100, 50, 20, 10)
    int large_sizes[] = {100, 50, 20, 10};
    for (int s = 0; s < 4; s++) {
        int size = large_sizes[s];
        for (int pattern = 0; pattern < 10; pattern++) {
            for (int i = 0; i < 10; i++) {
                int* arr = NULL;
                char pattern_name[100];
                switch (pattern) {
                    case 0: // random
                        arr = generate_random_array(size, -1000, 1000);
                        strcpy(pattern_name, "random");
                        break;
                    case 1: // sorted
                        arr = generate_sorted_array(size, rand()%1000, (rand()%10)+1);
                        strcpy(pattern_name, "sorted");
                        break;
                    case 2: // reverse sorted
                        arr = generate_reverse_sorted_array(size, rand()%1000, (rand()%10)+1);
                        strcpy(pattern_name, "reverse sorted");
                        break;
                    case 3: // all same
                        arr = generate_all_same_array(size, rand()%1000);
                        strcpy(pattern_name, "all same");
                        break;
                    case 4: // duplicates
                        arr = generate_duplicates_array(size, (rand()%5)+1);
                        strcpy(pattern_name, "duplicates");
                        break;
                    case 5: // nearly sorted (one swap)
                        arr = generate_nearly_sorted_array(size, 1);
                        strcpy(pattern_name, "nearly sorted (one swap)");
                        break;
                    case 6: // nearly sorted (5 swaps)
                        arr = generate_nearly_sorted_array(size, 5);
                        strcpy(pattern_name, "nearly sorted (5 swaps)");
                        break;
                    case 7: // mountain
                        arr = generate_mountain_array(size);
                        strcpy(pattern_name, "mountain");
                        break;
                    case 8: // valley
                        arr = generate_valley_array(size);
                        strcpy(pattern_name, "valley");
                        break;
                    case 9: // alternating
                        arr = generate_alternating_array(size, rand()%100, rand()%100+100);
                        strcpy(pattern_name, "alternating");
                        break;
                }
                char name[100];
                sprintf(name, "Size %d %s %d", size, pattern_name, i+1);
                tests[test_count] = (TestCase){
                    name, arr, NULL, size, true
                };
                test_count++;
            }
        }
    }
    
    // Generate 100 arithmetic sequence tests
    for (int i = 0; i < 100; i++) {
        int size = (rand() % 46) + 5; // 5-50
        int start = (rand() % 2001) - 1000; // -1000 to 1000
        int step = (rand() % 101) - 50; // -50 to 50
        int* arr = generate_arithmetic_array(size, start, step);
        char name[100];
        sprintf(name, "Arithmetic %d (size %d, start %d, step %d)", i+1, size, start, step);
        tests[test_count] = (TestCase){
            name, arr, NULL, size, true
        };
        test_count++;
    }
    
    // Generate 100 geometric sequence tests
    for (int i = 0; i < 100; i++) {
        int size = (rand() % 6) + 5; // 5-10
        int start = (rand() % 21) - 10;
        if (start == 0) start = 1;
        int factor = (rand() % 5) - 2;
        if (factor == 0) factor = 1;
        int* arr = generate_geometric_array(size, start, factor);
        char name[100];
        sprintf(name, "Geometric %d (size %d, start %d, factor %d)", i+1, size, start, factor);
        tests[test_count] = (TestCase){
            name, arr, NULL, size, true
        };
        test_count++;
    }
    
    // Generate 100 permutation tests
    for (int i = 0; i < 100; i++) {
        int size = (rand() % 46) + 5; // 5-50
        int* arr = generate_permutation(size);
        char name[100];
        sprintf(name, "Permutation %d (size %d)", i+1, size);
        tests[test_count] = (TestCase){
            name, arr, NULL, size, true
        };
        test_count++;
    }
    
    // Generate 103 almost constant tests
    for (int i = 0; i < 103; i++) {
        int size = (rand() % 46) + 5; // 5-50
        int constant = (rand() % 201) - 100; // -100 to 100
        int different_index = rand() % size;
        int different_value;
        do {
            different_value = constant + (rand() % 100) + 1;
        } while (different_value == constant);
        int* arr = generate_almost_constant_array(size, constant, different_index, different_value);
        char name[100];
        sprintf(name, "One element different %d (size %d, constant %d, different at %d)", i+1, size, constant, different_index);
        tests[test_count] = (TestCase){
            name, arr, NULL, size, true
        };
        test_count++;
    }
    
    // Run all tests
    int passed_count = 0;
    printf("Running %d test cases...\n\n", test_count);
    
    clock_t start_time = clock();
    for (int i = 0; i < test_count; i++) {
        bool result = run_test(&tests[i]);
        print_result(tests[i].name, result);
        if (result) passed_count++;
        
        if (tests[i].is_dynamic && tests[i].input) {
            free(tests[i].input);
            tests[i].input = NULL;
        }
    }
    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("\n%s================================%s\n", CYAN, RESET);
    printf("Test Results: %s● %d PASSED%s, %s● %s%d FAILED%s\n", 
           GREEN, passed_count, RESET, 
           (test_count - passed_count > 0) ? RED : GREEN,
           (test_count - passed_count > 0) ? BOLD : "", 
           test_count - passed_count, RESET);
    printf("Execution Time: %.2f seconds\n", total_time);

    if (passed_count == test_count) {
        printf("\n%s%s", BOLD, RED);
        printf("    ██████  ██    ██ ██████  ██████  ██      ███████ \n");
        printf("    ██   ██ ██    ██ ██   ██ ██   ██ ██      ██      \n");
        printf("    ██████  ██    ██ ██████  ██████  ██      █████   \n");
        printf("    ██   ██ ██    ██ ██   ██ ██   ██ ██      ██      \n");
        printf("    ██████   ██████  ██████  ██████  ███████ ███████ \n");
        printf("%s", RESET);

        printf("\n%s%s", BOLD, YELLOW);
        printf("    ███████  ██████  ██████  ████████ \n");
        printf("    ██      ██    ██ ██   ██    ██    \n");
        printf("    ███████ ██    ██ ██████     ██    \n");
        printf("         ██ ██    ██ ██   ██    ██    \n");
        printf("    ███████  ██████  ██   ██    ██    \n");
        printf("%s\n", RESET);

        printf("%s%s🎉 ALL TESTS PASSED! 🎉%s\n", BOLD, GREEN, RESET);
        printf("%s%s🔥 BUBBLE SORT WORKS! 🔥%s\n", BOLD, YELLOW, RESET);
    } else {
        printf("\n%s● %sSome tests failed. Please check your implementation.%s\n", 
               RED, BOLD, RESET);
    }
    
    return 0;
}

