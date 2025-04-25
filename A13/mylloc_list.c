#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size <= 0) return NULL;
  
  size_t required_size = size+sizeof(struct chunk);

  struct chunk *ptr = flist;
  struct chunk *prev = NULL;

  while (ptr != NULL){
    if (ptr->size >= required_size){
      size_t remaining_size = ptr->size - required_size;
      if (remaining_size >= required_size){
        //split chunk into two
        struct chunk *allocated = ptr;
        allocated->size = size;
        allocated->used = size;

        struct chunk *new_chunk = (struct chunk *)((char*)ptr + required_size);
        new_chunk->size = remaining_size;
        new_chunk->used = 0;
        new_chunk->next = flist;
        flist = new_chunk;

        if(prev != NULL){//not first in flist
          prev->next = ptr->next;
        }
        else{//first in flist
          flist = ptr->next;
        }
      } else {
        // Use the entire chunk
        ptr->used = size;
        if(prev != NULL){//not first in flist
          prev->next = ptr->next;
        }
        else{//first in flist
          flist = ptr->next;
        }
      }
      return (void *)(ptr + 1);
    }
    prev = ptr;
    ptr = ptr->next;
  }

  void *memory = sbrk(size+sizeof(struct chunk));
  if (memory == (void*)-1){
    return NULL;
  }else{
    struct chunk *cnk = (struct chunk*)memory;
    cnk->size = size;
    cnk->next = NULL;
    cnk->used = size;
    return (void*) (cnk+1);
  }
}

void free(void *memory) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (memory != NULL){
    struct chunk *cnk = (struct chunk*) ((struct chunk*)memory -1);
    cnk->next = flist;
    flist = cnk;
  }
  return;
}
