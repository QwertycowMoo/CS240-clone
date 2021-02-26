/**
 * Malloc
 * CS 240 - Fall 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _metadata_t {
    void* next;
    unsigned int size;
    unsigned char isUsed;
} metadata_t;

void *startOfHeap = NULL;
metadata_t* listStart = NULL;
metadata_t* listEnd = NULL;

void print_heap() {
    metadata_t *curMeta = startOfHeap;
    void *endOfHeap = sbrk(0);
    printf("-- Start of Heap (%p) --\n", startOfHeap);
    while ((void *)curMeta < endOfHeap) {   // While we're before the end of the heap...
        printf("metadata for memory %p: (%p, size=%d, isUsed=%d)\n", (void *)curMeta + sizeof(metadata_t), curMeta, curMeta->size, curMeta->isUsed);
        curMeta = (void *)curMeta + curMeta->size + sizeof(metadata_t);
    }
    printf("-- End of Heap (%p) --\n\n", endOfHeap);
}



/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block.  The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */
void *malloc(size_t size) {


    
    void *ptr;
    // implement malloc:
    //fprintf(stderr, "Inside malloc, inserting with size %ld\n", size);  // You'll eventually want to remove this.

    if (startOfHeap == NULL) {
        startOfHeap = sbrk(0);
        metadata_t *meta = sbrk(sizeof(metadata_t)); //allocates the metadata on the heap
        meta->size = size;
        meta->isUsed = 1;

        ptr = sbrk(size);
    } else {
        //this is all broken right now, fixing free first
        int isFree = 0;
        
        metadata_t* free = listStart;
        //printf("\tcurrent Meta pointer: %p \n", free);
        metadata_t* prev_free = NULL;
        while(free != NULL) {
            if (free->size >= size && free->isUsed == 0) {
                isFree = 1;
                //printf("found a free space at %p\n", free);
                break;
            }
            prev_free = free;
            free = free->next;
        }

        if (isFree) {
            //printf("Replacing an old chunk of memory\n");
            size_t old_size = free->size;
            ptr = (void*) free + sizeof(metadata_t);
            if (old_size - size > sizeof(metadata_t)) {   
                free->size = size;
                //need to split this memory and create a new metadata chunk
                //but if there's not enough memory to even create this small metadata part, we can't really use it
                metadata_t *new_meta = (void *) ptr + size;
                if (prev_free != NULL) {
                    prev_free->next = new_meta;
                }
                if (listStart == free) {
                    listStart = new_meta;
                }

                new_meta->isUsed = 0;
                new_meta->size = old_size - sizeof(metadata_t) - size;
                new_meta->next = free->next;
            } else {
                listStart = free->next;
            }
            free->isUsed = 1;
            
        } else {
            //makes a new chunk basically
            //printf("Making a new Chunk because there is no room\n");
            metadata_t *meta = sbrk(sizeof(metadata_t)); //allocates the metadata on the heap
            meta->size = size;
            meta->isUsed = 1;
            ptr = sbrk(size);

        }
    }
    
    //print_heap();
    return ptr;
}

/**
 * Allocate space for array in memory
 *
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 *
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */
void *calloc(size_t num, size_t size) {
    // implement calloc:
    //fprintf(stderr, "Inside calloc, inserting with num %ld and size %ld\n", num, size);  // You'll eventually want to remove this.
    if (startOfHeap == NULL){
        startOfHeap = sbrk(0);
    }
    //print_heap();
    

    void *ptr = malloc(size * num);
    return ptr;
}


/**
 * Deallocate space in memory
 *
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
void free(void *ptr) {
    // implement free:
    //printf("\n Freeing %p\n", ptr);
    metadata_t *meta = ptr - sizeof(metadata_t);
    
    meta->isUsed = 0;
    
    int newNode = 1;

    //remember that listStart is a metadata_t pointer since the block itself is a "listnode"
    if (listStart == NULL) {
        //printf("listStart is Null");
        listStart = meta;
        listEnd = (metadata_t*) listStart;
    } else {
        
        if (meta < listStart) {
            
            meta->next = listStart;
            listStart = meta;
        }
        //memory coalescing for memory blocks before our current pointer
        metadata_t* m = listStart;
        while(m != NULL) {
            
            if (m > meta) {
                //do the coalescing after
                if ((void*)meta + sizeof(metadata_t) + meta->size == m) {
                    
                    meta->size = meta->size + m->size + sizeof(metadata_t);
                    meta->next = m->next;
                    m = meta;
                    newNode = 0;
                }
            
            }
            if ((void*)m + sizeof(metadata_t) + m->size == meta) {
                //do the coalescing before
                m->size = m->size + meta->size + sizeof(metadata_t);
                m->next = meta->next;
                meta = NULL;
                newNode = 0;
            }
            m = (metadata_t *)m->next;
        }

        //if we cannot coalesce memory for this memory block, we add it to the end of the linkedList.
        if (newNode == 1){
            listEnd->next = meta;
            listEnd = meta;
        }
        
    }

    //print_heap();
    
}


/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */
void *realloc(void *ptr, size_t size) {
    // implement realloc:
    if (ptr == NULL) {
        return malloc(size);
    }
    if (size == 0) {
        free(ptr);
        return NULL;
    } 
    metadata_t *ptr_meta = ptr - sizeof(metadata_t);
    size_t cpy_size = ptr_meta->size < size ? ptr_meta->size : size;
    //@TODO: find the next available spot in memory
    //Rn its just gonna put it at the top of the heap
    void *new_ptr = malloc(size);

    if (new_ptr != NULL) {
        //should I be using memcpy?
        memcpy(new_ptr, ptr, cpy_size);
        free(ptr);
        ptr = new_ptr;
    }

    return ptr;
}