/** @file msort.c */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
	int *arr1;
	int *arr2;
	int size1;
	int size2;
	int full_size;
} arg_merge_t;

typedef struct {
	int* ptr;
	int size;
} arg_sort_t;

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void* sort_routine(void* ptr) {
	arg_sort_t *args = (arg_sort_t*) ptr;
	int* begin = args->ptr;
	int size = args->size;
	qsort(begin, size, sizeof(int), compare);
	fprintf(stderr, "Sorted %d elements.\n", size);
	return ptr;
}

void* merge(void* ptr) {
	//ptr is a pointer to an array of pointers
	//now we actually need to do the sort
	//Find out a way to handle the last part
	
	
	arg_merge_t* args = (arg_merge_t*)ptr;
	int* a1 = args->arr1;
	int* a2 = args->arr2;
	int size1 = args->size1;
	int size2 = args->size2;
	int full_size = size1 + size2;
	//fprintf(stderr, "full size: %d", full_size);
	int* out = malloc(sizeof(int) * full_size);

	//fprintf(stderr, "Inside merge with a1: %d and a2: %d values_per_segment: %d and %d\n", a1[0], a2[0], size1, size2);
	int dupes = 0;

	int a1_i = 0; //index of a1
	int a2_i = 0; //index of a2
	for (int i = 0; i < full_size; i++) {
		if (a1_i < size1) {
			if (a2_i == size2) {
				out[i] = a1[a1_i];
				a1_i++;
			} else {
				if (a1[a1_i] < a2[a2_i]) {
					//first array goes in
					out[i] = a1[a1_i];
					a1_i++;
				} else if (a1[a1_i] == a2[a2_i]) {
					out[i] = a1[a1_i];
					a1_i++;
					dupes++;
				} else {
					if (a2_i < size2) {
						out[i] = a2[a2_i];
						a2_i++;
					} else {
						out[i] = a1[a1_i];
						a1_i++;
					}
				}
			}
		} else {		
			out[i] = a2[a2_i];
			if(a2[a2_i] == a1[a1_i]) {
				dupes++;
			}
			a2_i++;
		}
		
	}
	//fprintf(stderr, "After merge with a1: %d and a2: %d\n", a1[a1_i - 1], a2[a2_i - 1]);
	fprintf(stderr, "Merged %d and %d elements with %d duplicates.\n", size1, size2, dupes);
	memcpy((void*) a1, (void*) out, full_size * sizeof(int));
	free(out);
	return (void*)a1;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./msort [# of threads] <[file to sort] \n");
		return 1;
	}

	int values_per_segment; /**< Maximum number of values per segment. */
	int count = 0; /**used to create storage array during merge**/
	int segmentCount = atoi(argv[1]);
	int i;
	int size = 250;
	int *numbers = malloc(size * sizeof(int));
	while (scanf("%d", &i) == 1) {

		if (count == size) {
			//allocating more memory if need to
			size = size * 2;
			void* tmp = realloc(numbers, size * sizeof(int));
			if (tmp == NULL) {
				//we ran out of virtual memory
				return 1;
			} else {
				numbers = tmp;
			}
		}
		numbers[count] = i;
		count++;
	}
	//
	void* tmp = realloc(numbers, count * sizeof(int));
	if (tmp == NULL) {
		//we ran out of virtual memory
		return 1;
	} else {
		numbers = tmp;
	}
	//setup threading
	pthread_t tid[segmentCount];

	if (count % segmentCount == 0) {
		values_per_segment = count / segmentCount;
	} else {
		//fails for 8 since 25/8 = 3 but 8 * 4 = 32.
		values_per_segment = (count / segmentCount) + 1;
		if (values_per_segment * (segmentCount - 1) > count) {
			values_per_segment = count / segmentCount;
		}
	}
	
	//setup arguments for sorting
	arg_sort_t args_sort[segmentCount];
	for (int i = 0; i < segmentCount; i++) {
		args_sort[i].ptr = numbers + (values_per_segment * i);
		if (i == segmentCount - 1) {
			args_sort[i].size = count - (values_per_segment * i);
		} else {
			args_sort[i].size = values_per_segment;
		}
	}
	
	//this sorts the entire thing 
	for (int i = 0; i < segmentCount; i++) {
		pthread_create(&tid[i], NULL, sort_routine, (void*) &args_sort[i]);
	}
	//joining threads
	for (int i = 0; i < segmentCount; i++) {
		pthread_join(tid[i], NULL);
	}
	//print after segmented sort
	// for (int i = 0; i < count; i++) {
	// 	printf("%d \n", numbers[i]);
	// }
	
	arg_merge_t arg_merge[segmentCount / 2];
	for (int i = 0; i < segmentCount / 2; i++) {
		
		arg_merge[i].arr1 = numbers + (i * 2 * values_per_segment);
		arg_merge[i].arr2 = numbers + (((i * 2) + 1) *values_per_segment);
		arg_merge[i].size1 = values_per_segment;
		if (i == (segmentCount / 2) - 1) {
			if (segmentCount % 2 == 0) {
				arg_merge[i].size2 = count - values_per_segment * (segmentCount - 1);
			} else {
				arg_merge[i].size2 = values_per_segment;
			}
			arg_merge[i].full_size = values_per_segment * 2;
		} else {
			arg_merge[i].size2 = values_per_segment;
			arg_merge[i].full_size = values_per_segment * 2;
		}
	}
	
	while (segmentCount > 1) {
		
		int thread_loop = segmentCount / 2;
		if (segmentCount % 2 == 0) {
			segmentCount = segmentCount / 2;
		} else {
			segmentCount = (segmentCount / 2) + 1;
		}
		
		for (int i = 0; i < thread_loop; i++) {
			
			pthread_create(&tid[i], NULL, merge, (void*) &arg_merge[i]);
		}
		for (int i = 0; i < thread_loop; i++) {
			pthread_join(tid[i], NULL);
		}
		
		//print after each thread run
		// for (int i = 0; i < count; i++) {
		// 	printf("%d \n", numbers[i]);
		// }

		values_per_segment = values_per_segment * 2;

		//create new thread params
		if (segmentCount == 2) {
			arg_merge[0].arr1 = numbers;	
			arg_merge[0].arr2 = numbers + (values_per_segment);
			arg_merge[0].size1 = values_per_segment;
			arg_merge[0].size2 = count - values_per_segment;
			arg_merge[0].full_size = count;
		} else {
			for (int i = 0; i < segmentCount / 2; i++) {
				arg_merge[i].arr1 = numbers + (i * 2 * values_per_segment);
				arg_merge[i].arr2 = numbers + (((i * 2) + 1) * values_per_segment);
				arg_merge[i].size1 = values_per_segment;
				arg_merge[i].size2 = values_per_segment;
				//fprintf(stderr, "arr1: %p  arr2: %p  size1: %d size2: %d", arg_merge[i].arr1, arg_merge[i].arr2, arg_merge[i].size1, arg_merge[i].size2);
				if (i == segmentCount / 2 - 1) {
					
					if (segmentCount % 2 == 0) {
						arg_merge[i].full_size = count - (values_per_segment * (segmentCount - 2));
						arg_merge[i].size2 = count - (values_per_segment * (segmentCount - 1));
					} else {
						arg_merge[i].full_size = values_per_segment * 2;
					}
					
				} else {
					arg_merge[i].full_size = values_per_segment * 2;
				}	
				
			}
		}
		
		
	}

	for (int i = 0; i < count; i++) {
		
		printf("%d\n", numbers[i]);
	}
	free(numbers);

	return 0;
}
