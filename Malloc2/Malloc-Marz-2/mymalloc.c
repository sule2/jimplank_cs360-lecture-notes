#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//Chunk wears two hats:
// 1. Allocated - only size is used
// 2. Free - all three fields are used
struct chunk {
	//Size is used for both allocated and free frames
	int size;

	//Next and prev are only legitimate in the free list
	//and NOT if this chunk is allocated
	struct chunk *next;
	struct chunk *prev;
};

//We can typecast the raw memory pointer by:
//void *ptr = sbrk(8192);
//struct chunk *chunk = (struct chunk *)ptr;
//chunk->size - bytes 0, 1, 2,  3
//chunk->next - bytes 4, 5, 6,  7
//chunk->prev - bytes 8, 9, 10, 11
//
//Notice bytes 8, 9, 10, and 11 dig into user's data, but this is OK
//since these bytes are only used in a FREE chunk, and hence no user
//is using it.
//
//We need at least 12 bytes to store these three fields with a
//32 bit processor (or 32-bit on 64-bit emulation)
//
//We know all chunks will be in a pool of at least 16 bytes
//size + 8 aligned to 8 means that as long as size is at least 1
//you will get 16 bytes. Remember aligned = (size + 7 + 8) & -8:
//(1 + 7 + 8) & -8 = 16. This shows that even at size=1, we get 16 bytes.


//The head of the list. This isn't required,
//but you're only allowed one global! There might be a better
//way, but that's your job to figure out!
struct chunk *head = NULL;

void *my_malloc(size_t size)
{
	//Never take for granted the size given to you by the user. They are known
	//to screw over a programmer (much like 102 students seem to come up with awful
	//algorithms).

	//size + 7 -> this rounds size up, but still not a multiple of 8
	//+ 8      -> We need 8 bytes for bookkeeping!
	//& -8     -> This does the actual alignment to 8 bytes
	//            which zeros the last three bits (7 = 0b111, ~7 = 0b000)
	size = (size + 7 + 8) & -8;

	//1. Check to see if anything is free
	//2. What if nothing is free or head is null?
	//   a. SBRK
	//   ->sbrk(XX) -> 8192 or size whichever is greater
	//   ->All of that goes to the free list

	//Now we either have a pointer to what we just allocated or
	//to a free hole (hole->size <= size). Either way, both are
	//free and hence, allocatable

	//3. Allocate the memory
	//   a. free_ptr and update its size (free_ptr->size -= size)
	//   b. alloc_ptr (alloc_ptr->size = size)
	//
	//CONSIDER THIS: What happens if the free_ptr after -= size doesn't have
	//enough for another allocation? It is useless since it can never be re-allocated
	//until it is coalesced. Instead, give the user all of the bytes rather than
	//splitting the chunk.
	//
	//4. Return alloc_ptr + 8  (this puts the user's pointer past the bookkeeping bytes)
	//   Remember to properly typecast alloc_ptr before adding 8! Otherwise, it means
	//   8 chunk structures (96 bytes, not 8 bytes).

}

void my_free(void *ptr)
{
	//1. Back up by 8 bytes.
	//2. Add this to the free list
	//3. Start at bottom of free list.
	//4. If you find a spot to put the free chunk here, it'll make coalescing
	//   easier! The spot for ptr is where the memory address = prev < ptr < next
	//5. You may now use ptr->next and ptr->prev since it is free and we know
	//   the user won't (shouldn't!) use the data.

	//CONSIDER THIS: What if head is null? That could mean two things:
	// 1. The programmer is a 102 student and called free without a matching malloc
	// 2. You allocated all free chunks to the user, and there are none left
}

void *free_list_begin()
{
	//The head or NULL if there is no head
}

void *free_list_next(void *ptr)
{
	//ptr->next or NULL if there isn't a next
	//If you use a doubly-linked list, be careful
	//here or you'll have an infinite loop!
}

void coalesce_free_list()
{
	//You can only coalesce where the memory address
	//are contiguous.
	//1. Run through the free list
	//2. If ptr and ptr->next are contiguous, then merge
	//   them. You'll have to compare the pointers with
	//   each other to ensure they are indeed contiguous
}

//Requirements to consider:
//1. One global only!
//2. sbrk(size);  size must be max(size, 8192)
//3. No external procedure or system calls
//   No need for a malloc, qsort, or free if you do free right!
//4. You cannot assume the memory (allocated or free) is contiguous.
//   Some other function may call sbrk in between your sbrk calls!
//5. 8 bytes only for bookkeeping. Remember that ->prev uses the user's
//   data, but is only when it is free....so this is OK!
//6. Free list nodes have a minimum size of 8 or 12. If you use a doubly
//   linked list, the free node must be 12, otherwise you have no space
//   for the ->prev pointer!
//7. Compile with -m32. All pointers are 32 bits (4 bytes)


//No int main here, it is included with the gradescript
