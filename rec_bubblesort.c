#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef int** solptr;
typedef int* arrptr[];
typedef int* temp;

solptr rec_bubblesort(int *arr , int phase , int bubble , int* ref_trav , int trav , int *size , solptr soln , bool* swap_flag, bool* base_flag){//b1
    
        //printf("\n arr[%d] - %d \n",phase,(*soln[phase]));
        if(*swap_flag){//b3
              return soln;
        }//b3
        
        if(phase >= *size){//b4
              *base_flag = true;
              return soln;
        }//b4
        
     
soln[phase] = ( //c1 - Main ternary expression start
    (bubble > 0) ? 
        ( //c2 - Bubble sorting active
            (trav > -1) ? 
                ( //c3 - Valid traversal index
                    (arr[trav+1] < arr[bubble-1]) ? 
                        ( //c4 - Swap needed case
                            (phase == 0) ? 
                                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] : 
                                ( //c5 - Non-zero phase cases
                                    (arr[trav+1] >= (*soln[phase-1])) ? 
                                        ( //c6 - Maintain sorted order
                                            (*ref_trav != trav+1) ? 
                                                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] : 
                                                ( //c7 - Reference pointer handling
                                                    (arr[bubble-1] > (*soln[phase-1])) ? 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase] : 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase]
                                                ) //c7
                                        ) : //c6
                                        ( //c8 - Out-of-order case
                                            (arr[bubble-1] >= (*soln[phase-1])) ? 
                                                ( //c9 - Bubble element comparison
                                                    (*ref_trav == bubble-1) ? 
                                                        rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] : 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]
                                                ) : //c9
                                                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]
                                        ) //c8
                                ) //c5
                        ) : //c4
                        ( //c10 - No swap needed case
                            (phase != 0 && trav != bubble - 2) ? 
                                (
                                    (arr[bubble - 1] <= arr[*ref_trav]) ?
                                    ( //c11 - Reference comparison
                                        (arr[bubble - 1] == arr[*ref_trav]) ? 
                                        ( //c11.3 - Equal elements
                                            (arr[bubble-1] >= (*soln[phase-1])) ? 
                                            ( //c12 - Equal element handling
                                                (*ref_trav >= bubble-1) ? 
                                                    rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] : 
                                                    rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]
                                            ) //c12
                                            :
                                            rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]
                                        ) : //c11.3
                                        ( //c13 - Unequal elements
                                            (arr[trav+1] >= (*soln[phase-1])) ? 
                                                ( //c14 - Traversal check
                                                    (*ref_trav >= trav+1) ? 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav , size, soln, swap_flag, base_flag)[phase] : 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]
                                                ) : //c14
                                                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]
                                        ) //c13
                                    ) : 
                                ( //c11 - Boundary handling
                                    (arr[bubble-1] >= (*soln[phase-1])) ? 
                                        ( //c12 - Phase end
                                            (*ref_trav == bubble-1) ? 
                                                rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] : 
                                                rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]
                                        ) : //c12
                                        ( //c13 - Final cases
                                            (arr[trav+1] >= (*soln[phase-1])) ? 
                                                ( //c14 - Last position
                                                    (*ref_trav == trav+1) ? 
                                                        rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase] : 
                                                        rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase]
                                                ) : //c14
                                                rec_bubblesort(arr, phase, bubble, ref_trav, trav - 1, size, soln, swap_flag, base_flag)[phase]
                                        ) //c13
                                ) //c11
                        ) : //c10
                        ( (trav == bubble - 2) ? 
                            rec_bubblesort(arr, phase, bubble - 1, ref_trav, trav, size, soln, swap_flag, base_flag)[phase] :
                            rec_bubblesort(arr, phase, bubble - 1, ref_trav, bubble - 2, size, soln, swap_flag, base_flag)[phase]
                        )
                )) : //c3
                (*swap_flag = true, &arr[trav+1]) // Traversal complete
        ) : //c2
        &arr[trav+1] // Base case
); //c1 - Main expression end
         
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


/*
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
    for (int i = 0; i < *records; i++) {//b6
        printf("Enter array[%d] :- ", i);
        scanf("%d", &array[i]);
    }//b6

    attach(*records , array , sortarr);
    // Function pointer for bubblesort, for flexibility or callbacks
    solptr (*rec_bubblesort_ptr)(int*,int,int,int*,int,int*,solptr,bool*,bool*) = rec_bubblesort;

    // Call bubble sort and get pointer to sorted array
    solptr final_arr = rec_bubblesort_ptr(array, 0 , *records - 1, ref, *records - 2 , records , (solptr)sortarr , &flag, &bflag);

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

*/