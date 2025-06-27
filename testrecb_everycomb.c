#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef int** solptr;
solptr rec_bubblesort(int *arr , int phase , int bubble , int* ref_trav , int trav , int *size , solptr soln , bool* swap_flag, bool* base_flag){//b1
    
        if(*swap_flag){//b3
              return soln;
        }//b3
        
        if(phase >= *size){//b4
              *base_flag = true;
              return soln;
        }//b4
        
     
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
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase]: //c6
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav == bubble-1) ?
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]: //c9
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]: //c4
                (phase != 0 && trav != bubble - 2) ?
                (arr[bubble - 1] <= arr[*ref_trav]) ?
                (arr[bubble - 1] == arr[*ref_trav]) ?
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav >= bubble-1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]:
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]: //c11.3
                (arr[trav+1] >= (*soln[phase-1])) ?
                (*ref_trav >= trav+1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]: //c14
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]:
                (arr[bubble-1] >= (*soln[phase-1])) ?
                (*ref_trav == bubble-1) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]: //c12
                (arr[trav+1] >= (*soln[phase-1])) ?
                (*ref_trav == trav+1) ?
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]: //c14
                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]: //c10
                (trav == bubble - 2) ?
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]: //c3
                (*swap_flag = true, &arr[trav+1]): //c2
                &arr[trav+1]; //c1 - Main expression end
         
         if(bubble==0){//b11
              *ref_trav = trav+1;
         }//b11
         
          if(*base_flag){//b4
              *swap_flag = true;
              return soln;
         }//b4
         
         if(!(*swap_flag)){//b5
                return rec_bubblesort(arr, phase + 1, *size - 1, ref_trav, *size - 2, size , soln , swap_flag, base_flag);
         }//b5  
         
         
}//b1



void display(int size, solptr ptr_ptr) {//b4
    for (int i = 0; i < size; i++)
        printf("array[%d] :- %d\n", i, (*ptr_ptr[i]));
}//b4


void attach(int size, int* arr , solptr ptr_ptr) {//b4
    for (int i = 0; i < size; i++){//b8
        ptr_ptr[i] = &arr[i];    
    }//b8
}//b4

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

bool arrays_equal(solptr a, int *b, int size) {
    for (int i = 0; i < size; ++i)
        if (*a[i] != b[i]) return false;
    return true;
}

int main() {
    const int SAMPLE_COUNT = 5000;
    const int SIZE = 5;
    int pool[] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
    const int POOL_SIZE = sizeof(pool) / sizeof(pool[0]);

    srand(time(NULL));
    int passed = 0;

    for (int t = 0; t < SAMPLE_COUNT; t++) {
        int input[SIZE];
        for (int i = 0; i < SIZE; i++) {
            input[i] = pool[rand() % POOL_SIZE];
        }

        int arr[SIZE], ref[SIZE];
        memcpy(arr, input, sizeof(arr));
        memcpy(ref, input, sizeof(ref));

        int *records = malloc(sizeof(int));
        *records = SIZE;
        int **sortarr = malloc(SIZE * sizeof(int*));
        bool flag = false;
        bool bflag = false;
        int *reftrav = malloc(sizeof(int));
        *reftrav = -1;

        attach(*records, arr, sortarr);
        solptr result = rec_bubblesort(arr, 0, SIZE - 1, reftrav, SIZE - 2, records, sortarr, &flag, &bflag);

        qsort(ref, SIZE, sizeof(int), compare_ints);

        if (arrays_equal(result, ref, SIZE)) {
            passed++;
        } else {
            printf("❌ Test %d failed\n", t + 1);
            printf("Input:   [%d, %d, %d, %d, %d]\n", input[0], input[1], input[2], input[3], input[4]);
            printf("Output:  [%d, %d, %d, %d, %d]\n", (*result)[0], (*result)[1], (*result)[2], (*result)[3], (*result)[4]);
            printf("Expected:[%d, %d, %d, %d, %d]\n\n", ref[0], ref[1], ref[2], ref[3], ref[4]);
        }

        free(records);
        free(reftrav);
        free(sortarr);
    }

    printf("\n✅ Passed %d / %d test cases.\n", passed, SAMPLE_COUNT);
    return 0;
}
/*✅ Passed 5000 / 5000 test cases. -- output*/
