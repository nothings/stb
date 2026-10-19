#ifdef DS_TEST
#define STBDS_SMALL_BUCKET
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STBDS_ASSERT assert
#include <assert.h>

#define STB_DS_IMPLEMENTATION
#include "../stb_ds.h"

#include <pthread.h>

// to track allocations while testing
static size_t alloc_count = 0;
static size_t  free_count = 0;
static size_t total_alloc = 0;

static void *test_context = (void*)0x12345678;

static void *test_realloc(void *ctx, void *ptr, size_t size)
{
  assert(ctx == test_context);
  alloc_count++;
  total_alloc += size;
  return realloc(ptr, size);
}

static void test_free(void *ctx, void *ptr)
{
  assert(ctx == test_context);
  free_count++;
  free(ptr);
}

// for multi-threading test
typedef struct
{
  int    thread_id;
  size_t alloc_count;
  size_t free_count;
  void*  context;
} thread_data_t;

static void *thread_realloc(void *ctx, void *ptr, size_t size)
{
  thread_data_t *td = (thread_data_t*) ctx;
  if (ptr == NULL && size > 0)
    td->alloc_count++;

  return realloc(ptr, size);
}

static void thread_free(void *ctx, void *ptr)
{
  thread_data_t *td = (thread_data_t*) ctx;
  if (ptr != NULL)
    td->free_count++;
  free(ptr);
}

static void *thread_func(void *args)
{
  thread_data_t *data = (thread_data_t*) args;
  stbds_allocator alloc = {
    .context = data,
    .realloc = thread_realloc,
    .free    = thread_free
  };

  int *arr = NULL;
  stbds_arrinit((void**)&arr, &alloc);

#define ELEMENTS_PER_THREAD 100

  int i;
  for (int i = 0; i < ELEMENTS_PER_THREAD; ++i) {
    arrput(arr, data->thread_id * 1000 + i);
  }
  assert(arrlen(arr) == ELEMENTS_PER_THREAD);

  for (int i = 0; i < ELEMENTS_PER_THREAD; ++i) {
    assert(arr[i] == data->thread_id * 1000 + i);
  }
  assert(data->alloc_count > 0);

  size_t free_count_before = data->free_count;
  arrfree(arr);
  assert(data->free_count > free_count_before);

  return 0;
}

#ifdef DS_TEST
#include <stdio.h>
int main(int argc, char *argv[])
{
  // TEST_1: array
  {
    // TEST_1A: array custom allocator support
    {
      int *arr = NULL;
      stbds_allocator alloc = {
        .context = test_context,
        .realloc = test_realloc,
        .free    = test_free
      };

      // reset global values
      alloc_count = 0;
      free_count = 0;

      stbds_arrinit((void**)&arr, &alloc);
      arrput(arr, 1);
      arrput(arr, 2);
      arrput(arr, 3);

      assert(arrlen(arr) == 3);

      assert(arr[0] == 1);
      assert(arr[1] == 2);
      assert(arr[2] == 3);

      assert(alloc_count > 0);

      size_t free_count_before = free_count;
      arrfree(arr);
      assert(free_count > free_count_before);
    }
    // TEST_1B: array fallback default memory allocation
    {
      int *arr = NULL;

      stbds_arrinit((void**)&arr, NULL);
      arrput(arr, 69);

      assert(arrlen(arr) == 1);

      assert(arr[0] == 69);
      arrfree(arr);
    }
  }

  // TEST_2: hash map
  {
    // TEST_2A: hash map custom allocator support
    {
      struct {
        int key;
        int value;
      } *hm = NULL;

      stbds_allocator alloc = {
        .context = test_context,
        .realloc = test_realloc,
        .free    = test_free
      };

      // reset global values
      alloc_count = 0;
      free_count = 0;

      stbds_hminit((void**)&hm, &alloc);
      hmput(hm, 10, 123);
      hmput(hm, 20, 456);

      assert(hmlen(hm) == 2);

      assert(hmget(hm, 10) == 123);
      assert(hmget(hm, 20) == 456);

      assert(alloc_count > 0);

      size_t free_count_before = free_count;
      hmfree(hm);
      assert(free_count > free_count_before);
    }
    // TEST_2B: hash map fallback default memory allocation
    {
      struct {
        int key;
        int value;
      } *hm = NULL;

      stbds_hminit((void**)&hm, NULL);
      hmput(hm, 10, 789);
      hmput(hm, 20, 101);

      assert(hmlen(hm) == 2);

      assert(hmget(hm, 10) == 789);
      assert(hmget(hm, 20) == 101);

      hmfree(hm);
    }
  }

  // TEST_3: string hash map
  {
    // TEST_3A: string hash map custom allocator support
    {
      struct {
        char *key;
        int value;
      } *sh = NULL;

      stbds_allocator alloc = {
        .context = test_context,
        .realloc = test_realloc,
        .free    = test_free
      };

      // reset global values
      alloc_count = 0;
      free_count = 0;

      stbds_shinit((void**)&sh, &alloc);
      sh_new_strdup(sh);
      shput(sh, "hello", 1);
      shput(sh, "world", 4);

      assert(shlen(sh) == 2);

      assert(shget(sh, "hello") == 1);
      assert(shget(sh, "world") == 4);

      assert(alloc_count > 0);

      size_t free_count_before = free_count;
      shfree(sh);
      assert(free_count > free_count_before);
    }
    // TEST_3B: string hash map fallback default memory allocation
    {
      struct {
        char *key;
        int value;
      } *sh = NULL;

      // reset global values
      alloc_count = 0;
      free_count = 0;

      stbds_shinit((void**)&sh, NULL);
      sh_new_strdup(sh);
      shput(sh, "foo", 69);
      shput(sh, "bar", 96);

      assert(shlen(sh) == 2);

      assert(shget(sh, "foo") == 69);
      assert(shget(sh, "bar") == 96);

      shfree(sh);
    }
  }

  // TEST_4: multi-threading test
  {
    #define NUM_THREADS 4
    thread_data_t thread_data[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; ++i) {
      thread_data[i].thread_id = i;
      thread_data[i].alloc_count = 0;
      thread_data[i].free_count = 0;
      thread_data[i].context = &thread_data[i];
    }

    for (i = 0; i < NUM_THREADS; ++i) {
      int ret = pthread_create(&threads[i], NULL, thread_func, &thread_data[i]);
      assert(ret == 0);
    }

    for (i = 0; i < NUM_THREADS; ++i) {
      int ret = pthread_join(threads[i], NULL);
      assert(ret == 0);
    }

    for (i = 0; i < NUM_THREADS; ++i) {
      assert(thread_data[i].alloc_count > 0);
      assert(thread_data[i].free_count > 0);
    }
  }

  return 0;
}


#endif


