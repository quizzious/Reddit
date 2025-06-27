#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
int(*bubblesort(int size , int *arr ,  int(*ret_ptr)[]))[]{//b1
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


void display(int size , int(*ptr_to_arr)[size]){//b6

      for(int iter = 0 ; iter < size ; iter++)
          printf("array[%d] :- %d\n", iter, ((*ptr_to_arr)[iter]));

}//b6

int main(){//b7

      int* records = (int*)malloc(sizeof(int));
      printf("Enter the size of array :- ");
      scanf("%d" , records);
      int* array = (int*)malloc((*records) * sizeof(int));
      
      printf("\n"); 
      
       for(int iter = 0 ; iter < *records ; iter++){//b8
          printf("Enter array[%d] :- ", iter);
          scanf("%d" , &array[iter]);
      }//b8
      
      int ( * ( * bubblesort_ptr ) (int , int* , int(*)[] ) ) [] = bubblesort;
      int(*final_arr)[] = bubblesort_ptr(*records , array , (int(*)[])array);
      
      printf("\n");
      display(*records , final_arr);
      printf("\n");
      
      free(array);
      array = NULL;
      return 0;
      
}//b7
