#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstdbool>

typedef int** solptr;
typedef int* arrptr[];
typedef int* temp;

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
    array = nullptr;
    free(records);

    free(sortarr);
    sortarr = nullptr;
    free(ref);
    ref = nullptr;
    //free(final_arr);
    records = nullptr;
    return true;
}//b5

