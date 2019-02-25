/* stb_ds.h - v0.3 - public domain data structures - Sean Barrett 2019
  
   This is a single-header-file library that provides easy-to-use
   dynamic arrays and hash tables for C (also works in C++).

   For a gentle introduction:
      http://nothings.org/stb_ds

   To use this library, do this in *one* C or C++ file:
      #define STB_DS_IMPLEMENTATION
      #include "stb_ds.h"

TABLE OF CONTENTS

  Table of Contents
  Compile-time options
  License
  Documentation
  Notes
  Notes - Dynamic arrays
  Notes - Hash maps
  Credits

COMPILE-TIME OPTIONS

  #define STBDS_NO_SHORT_NAMES

     This flag needs to be set globally.
       
     By default stb_ds exposes shorter function names that are not qualified
     with the "stbds_" prefix. If these names conflict with the names in your
     code, define this flag.

  #define STBDS_SIPHASH_2_4

     This flag only needs to be set in the file containing #define STB_DS_IMPLEMENTATION.

     By default stb_ds.h hashes using a weaker variant of SipHash and a custom hash for
     4- and 8-byte keys. On 64-bit platforms, you can define the above flag to force
     stb_ds.h to use specification-compliant SipHash-2-4 for all keys. Doing so makes
     hash table insertion about 20% slower on 4- and 8-byte keys, 5% slower on
     64-byte keys, and 10% slower on 256-byte keys on my test computer.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

DOCUMENTATION

  Dynamic Arrays

    Non-function interface:

      Declare an empty dynamic array of type T
        T* foo = NULL;    

      Access the i'th item of a dynamic array 'foo' of type T, T* foo:
        foo[i]

    Functions (actually macros)

      arrfree:
        void arrfree(T*);
          Frees the array.

      arrlen:
        ptrdiff_t arrlen(T*);
          Returns the number of elements in the array.

      arrlenu:
        size_t arrlenu(T*);
          Returns the number of elements in the array as an unsigned type.

      arrput:
        T arrput(T* a, T b);
          Appends the item b to the end of array a. Returns b.

      arrins:
        T arrins(T* a, int p, T b);
          Inserts the item b into the middle of array a, into a[p],
          moving the rest of the array over. Returns b.

      arrinsn:
        void arrins(T* a, int p, int n);
          Inserts n uninitialized items into array a starting at a[p],
          moving the rest of the array over.

      arrdel:
        void arrdel(T* a, int p);
          Deletes the element at a[p], moving the rest of the array over.

      arrdeln:
        void arrdel(T* a, int p, int n);
          Deletes n elements starting at a[p], moving the rest of the array over.

      arrdelswap:
        void arrdelswap(T* a, int p);
          Deletes the element at a[p], replacing it with the element from
          the end of the array. O(1) performance.

      arrsetlen:
        void arrsetlen(T* a, int n);
          Changes the length of the array to n. Allocates uninitialized
          slots at the end if necessary.

      arrsetcap:
        size_t arrsetcap(T* a, int n);
          Sets the length of allocated storage to at least n. It will not
          change the length of the array.

      arrcap:
        size_t arrcap(T* a);
          Returns the number of total elements the array can contain without
          needing to be reallocated.

  Hash maps & String hash maps

    Given T is a structure type: struct { TK key; TV value; }. Note that some
    functions do not require TV value and can have other fields. For string
    hash maps, TK must be 'char *'.

    Special interface:

      stbds_rand_seed:
        void stbds_rand_seed(size_t seed);
          For security against adversarially chosen data, you should seed the
          library with a strong random number. Or at least seed it with time().

      stbds_hash_string:
        size_t stbds_hash_string(char *str, size_t seed);
          Returns a hash value for a string.

      stbds_hash_bytes:
        size_t stbds_hash_bytes(void *p, size_t len, size_t seed);
          These functions hash an arbitrary number of bytes. The function
          uses a custom hash for 4- and 8-byte data, and a weakened version
          of SipHash for everything else. On 64-bit platforms you can get
          specification-compliant SipHash-2-4 on all data by defining
          STBDS_SIPHASH_2_4, at a significant cost in speed.

    Non-function interface:

      Declare an empty hash map of type T
        T* foo = NULL;

      Access the i'th entry in a hash table T* foo:
        foo[i]

    Function interface (actually macros):

      hmfree
      shfree
        void hmfree(T*);
        void shfree(T*);
          Frees the hashmap and sets the pointer to NULL.

      hmlen
      shlen
        ptrdiff_t hmlen(T*)
        ptrdiff_t shlen(T*)
          Returns the number of elements in the hashmap.

      hmlenu
      shlenu
        size_t hmlenu(T*)
        size_t shlenu(T*)
          Returns the number of elements in the hashmap.

      hmgeti
      shgeti
        ptrdiff_t hmgeti(T*, TK key)
        ptrdiff_t shgeti(T*, char* key)
          Returns the index in the hashmap which has the key 'key', or -1
          if the key is not present.

      hmget
      shget
        TV hmget(T*, TK key)
        TV shget(T*, char* key)
          Returns the value corresponding to 'key' in the hashmap.
          The structure must have a 'value' field

      hmgets
      shgets
        T hmgets(T*, TK key)
        T shgets(T*, char* key)
          Returns the structure corresponding to 'key' in the hashmap.

      hmdefault
      shdefault
        TV hmdefault(T*, TV value)
        TV shdefault(T*, TV value)
          Sets the default value for the hashmap, the value which will be
          returned by hmget/shget if the key is not present.

      hmdefaults
      shdefaults
        TV hmdefaults(T*, T item)
        TV shdefaults(T*, T item)
          Sets the default struct for the hashmap, the contents which will be
          returned by hmgets/shgets if the key is not present.

      hmput
      shput
        TV hmput(T*, TK key, TV value)
        TV shput(T*, char* key, TV value)
          Inserts a <key,value> pair into the hashmap. If the key is already
          present in the hashmap, updates its value.

      hmputs
      shputs
        T hmputs(T*, T item)
        T shputs(T*, T item)
          Returns the structure corresponding to 'key' in the hashmap.

      hmdel
      shdel
        int hmdel(T*, TK key)
        int shdel(T*, char* key)
          If 'key' is in the hashmap, deletes its entry and returns 1.
          Otherwise returns 0.

    Function interface (actually macros) for strings only:

      sh_new_strdup
        void sh_new_strdup(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate and free
          each string key using malloc/free

      sh_new_arena
        void sh_new_arena(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate each string
          key to a string arena. Every string key ever used by this
          hash table remains in the arena until the arena is freed.
          Additionally, any key which is deleted and reinserted will
          be allocated multiple times in the string arena.

NOTES

  * These data structures are realloc'd when they grow, and the macro "functions"
    write to the provided pointer. This means: (a) the pointer must be an lvalue,
    and (b) the pointer to the data structure is not stable, and you must maintain
    it the same as you would a realloc'd pointer. For example, if you pass a pointer
    to a dynamic array to a function which updates it, the function must return
    back the new pointer to the caller. This is the price of trying to do this in C.

  * You iterate over the contents of a dynamic array and a hashmap in exactly
    the same way, using arrlen/hmlen/shlen:

      for (i=0; i < arrlen(foo); ++i)
         ... foo[i] ...

  * All operations except arrins/arrdel are O(1) amortized, but individual
    operations can be slow, so these data structures may not be suitable
    for real time use. Dynamic arrays double in capacity as needed, so
    elements are copied an average of once. Hash tables double/halve
    their size as needed, with appropriate hysteresis to maintain O(1)
    performance.

NOTES - DYNAMIC ARRAY

  * If you know how long a dynamic array is going to be in advance, you can avoid
    extra memory allocations by using arrsetlen to allocate it to that length in
    advance and use foo[n] while filling it out, or arrsetcap to allocate the memory
    for that length and use arrput/arrpush as normal.

  * Unlike some other versions of the dynamic array, this version should
    be safe to use with strict-aliasing optimizations.

NOTES - HASH MAP

  * For compilers other than GCC and clang (e.g. Visual Studio), for hmput/hmget/hmdel
    and variants, the key must be an lvalue (so the macro can take the address of it).
    For GCC and clang, extensions are used that eliminate this requirement if you're
    using C99 and later or using C++.

  * To test for presence of a key in a hashmap, just do 'hmget(foo,key) >= 0'.

  * The iteration order of your data in the hashmap is determined solely by the
    order of insertions and deletions. In particular, if you never delete, new
    keys are always added at the end of the array. This will be consistent
    across all platforms and versions of the library. However, you should not
    attempt to serialize the internal hash table, as the hash is not consistent
    between different platforms, and may change with future versions of the library.

  * Use sh_new_arena() for string hashmaps that you never delete from. Initialize
    with NULL if you're managing the memory for your strings, or your strings are
    never freed (at least until the hashmap is freed). Otherwise, use sh_new_strdup().
    @TODO: make an arena variant that garbage collects the strings with a trivial
    copy collector into a new arena whenever the table shrinks / rebuilds. Since
    current arena recommendation is to only use arena if it never deletes, then
    this can just replace current arena implementation.

  * If adversarial input is a serious concern and you're on a 64-bit platform,
    enable STBDS_SIPHASH_2_4 (see the 'Compile-time options' section), and pass
    a strong random number to stbds_rand_seed.
     
  * The default value for the hash table is stored in foo[-1], so if you
    use code like 'hmget(T,k)->value = 5' you can overwrite the value
    stored by hmdefault if 'k' is not present.

CREDITS

  Sean Barrett -- library, idea for dynamic array API/implementation
  Per Vognsen  -- idea for hash table API/implementation
*/

#ifndef INCLUDE_STB_DS_H
#define INCLUDE_STB_DS_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifndef STBDS_NO_SHORT_NAMES
#define arrlen      stbds_arrlen
#define arrlenu     stbds_arrlenu
#define arrput      stbds_arrput
#define arrpush     stbds_arrput
#define arrfree     stbds_arrfree
#define arraddn     stbds_arraddn
#define arrsetlen   stbds_arrsetlen
#define arrlast     stbds_arrlast
#define arrins      stbds_arrins
#define arrinsn     stbds_arrinsn
#define arrdel      stbds_arrdel
#define arrdeln     stbds_arrdeln
#define arrdelswap  stbds_arrdelswap
#define arrcap      stbds_arrcap
#define arrsetcap   stbds_arrsetcap

#define hmput       stbds_hmput
#define hmputs      stbds_hmputs
#define hmget       stbds_hmget
#define hmgets      stbds_hmgets
#define hmgetp      stbds_hmgetp
#define hmgeti      stbds_hmgeti
#define hmdel       stbds_hmdel
#define hmlen       stbds_hmlen
#define hmlenu      stbds_hmlenu
#define hmfree      stbds_hmfree
#define hmdefault   stbds_hmdefault
#define hmdefaults  stbds_hmdefaults

#define shput       stbds_shput
#define shputs      stbds_shputs
#define shget       stbds_shget
#define shgets      stbds_shgets
#define shgetp      stbds_shgetp
#define shgeti      stbds_shgeti
#define shdel       stbds_shdel
#define shlen       stbds_shlen
#define shlenu      stbds_shlenu
#define shfree      stbds_shfree
#define shdefault   stbds_shdefault
#define shdefaults  stbds_shdefaults
#define sh_new_arena  stbds_sh_new_arena
#define sh_new_strdup stbds_sh_new_strdup

#define stralloc    stbds_stralloc
#define strreset    stbds_strreset
#endif      
#ifdef __cplusplus
extern "C" {
#endif

// for security against attackers, seed the library with a random number, at least time() but stronger is better
extern void stbds_rand_seed(size_t seed);

// these are the hash functions used internally if you want to test them or use them for other purposes
extern size_t stbds_hash_bytes(void *p, size_t len, size_t seed);
extern size_t stbds_hash_string(char *str, size_t seed);

// this is a simple string arena allocator, initialize with e.g. 'stbds_string_arena my_arena={0}'.
typedef struct stbds_string_arena stbds_string_arena;
extern char * stbds_stralloc(stbds_string_arena *a, char *str);
extern void   stbds_strreset(stbds_string_arena *a);

// have to #define STBDS_UNIT_TESTS to call this
extern void stbds_unit_tests(void);

///////////////
//
// Everything below here is implementation details
//

extern void * stbds_arrgrowf(void *a, size_t elemsize, size_t addlen, size_t min_cap);
extern void   stbds_hmfree_func(void *p, size_t elemsize, size_t keyoff);
extern void * stbds_hmget_key(void *a, size_t elemsize, void *key, size_t keysize, int mode);
extern void * stbds_hmput_default(void *a, size_t elemsize);
extern void * stbds_hmput_key(void *a, size_t elemsize, void *key, size_t keysize, int mode);
extern void * stbds_hmdel_key(void *a, size_t elemsize, void *key, size_t keysize, size_t keyoffset, int mode);
extern void * stbds_shmode_func(size_t elemsize, int mode);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) || defined(__clang__)
#define STBDS_HAS_TYPEOF
#ifdef __cplusplus
//#define STBDS_HAS_LITERAL_ARRAY  // this is currently broken for clang
#endif
#endif

#if !defined(__cplusplus)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define STBDS_HAS_LITERAL_ARRAY
#endif
#endif

// this macro takes the address of the argument, but on gcc/clang can accept rvalues
#if defined(STBDS_HAS_LITERAL_ARRAY) && defined(STBDS_HAS_TYPEOF)
  #if __clang__
  #define STBDS_ADDRESSOF(typevar, value)     ((__typeof__(typevar)[1]){value}) // literal array decays to pointer to value
  #else
  #define STBDS_ADDRESSOF(typevar, value)     ((typeof(typevar)[]){value}) // literal array decays to pointer to value
  #endif
#else
#define STBDS_ADDRESSOF(typevar, value)     &(value)
#endif

#define STBDS_OFFSETOF(var,field)           ((char *) &(var)->field - (char *) (var))

#define stbds_header(t)  ((stbds_array_header *) (t) - 1)
#define stbds_temp(t)    stbds_header(t)->temp

#define stbds_arrsetcap(a,n) (stbds_arrgrow(a,0,n))
#define stbds_arrsetlen(a,n) ((stbds_arrcap(a) < n ? stbds_arrsetcap(a,n),0 : 0), (a) ? stbds_header(a)->length = (n) : 0)
#define stbds_arrcap(a)       ((a) ? stbds_header(a)->capacity : 0)
#define stbds_arrlen(a)       ((a) ? (ptrdiff_t) stbds_header(a)->length : 0)
#define stbds_arrlenu(a)      ((a) ?             stbds_header(a)->length : 0)
#define stbds_arrput(a,v)     (stbds_arrmaybegrow(a,1), (a)[stbds_header(a)->length++] = (v))
#define stbds_arrpush         stbds_arrput  // synonym
#define stbds_arraddn(a,n)    (stbds_arrmaybegrow(a,n), stbds_header(a)->length += (n))
#define stbds_arrlast(a)      ((a)[stbds_header(a)->length-1])
#define stbds_arrfree(a)      ((void) ((a) ? realloc(stbds_header(a),0) : 0), (a)=NULL)
#define stbds_arrdel(a,i)     stbds_arrdeln(a,i,1)
#define stbds_arrdeln(a,i,n)  (memmove(&(a)[i], &(a)[(i)+(n)], sizeof *(a) * (stbds_header(a)->length-(n)-(i))), stbds_header(a)->length -= (n))
#define stbds_arrdelswap(a,i) ((a)[i] = stbds_arrlast(a), stbds_header(a)->length -= 1)
#define stbds_arrinsn(a,i,n)  (stbds_arraddn((a),(n)), memmove(&(a)[(i)+(n)], &(a)[i], sizeof *(a) * (stbds_header(a)->length-(n)-(i))))
#define stbds_arrins(a,i,v)   (stbds_arrinsn((a),(i),1), (a)[i]=(v))

#define stbds_arrmaybegrow(a,n)  ((!(a) || stbds_header(a)->length + (n) > stbds_header(a)->capacity) \
                                  ? (stbds_arrgrow(a,n,0),0) : 0)

#define stbds_arrgrow(a,b,c)   ((a) = stbds_arrgrowf_wrapper((a), sizeof *(a), (b), (c)))

#define stbds_hmput(t, k, v) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, 0),   \
     (t)[stbds_temp((t)-1)].key = (k), \
     (t)[stbds_temp((t)-1)].value = (v))

#define stbds_hmputs(t, s) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), &(s).key, sizeof (s).key, STBDS_HM_BINARY), \
     (t)[stbds_temp((t)-1)] = (s))

#define stbds_hmgeti(t,k) \
    ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, STBDS_HM_BINARY), \
      stbds_temp((t)-1))

#define stbds_hmgetp(t, k) \
    ((void) stbds_hmgeti(t,k), &(t)[stbds_temp((t)-1)])

#define stbds_hmdel(t,k) \
    (((t) = stbds_hmdel_key_wrapper((t),sizeof *(t), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, STBDS_OFFSETOF((t),key), STBDS_HM_BINARY)),(t)?stbds_temp((t)-1):0)

#define stbds_hmdefault(t, v) \
    ((t) = stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1].value = (v))

#define stbds_hmdefaults(t, s) \
    ((t) = stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1] = (s))

#define stbds_hmfree(p)        \
    ((void) ((p) != NULL ? stbds_hmfree_func((p)-1,sizeof*(p),STBDS_OFFSETOF((p),key)),0 : 0),(p)=NULL)

#define stbds_hmgets(t, k) (*stbds_hmgetp(t,k))
#define stbds_hmget(t, k)  (stbds_hmgetp(t,k)->value)
#define stbds_hmlen(t)     (stbds_arrlen((t)-1)-1)
#define stbds_hmlenu(t)    (stbds_arrlenu((t)-1)-1)

#define stbds_shput(t, k, v) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), (void*) (k), sizeof (t)->key, STBDS_HM_STRING),   \
     (t)[stbds_temp(t-1)].value = (v))

#define stbds_shputs(t, s) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), (void*) (s).key, sizeof (s).key, STBDS_HM_STRING), \
     (t)[stbds_temp(t-1)] = (s))

#define stbds_shgeti(t,k) \
     ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), (void*) (k), sizeof (t)->key, STBDS_HM_STRING), \
      stbds_temp(t))

#define stbds_shgetp(t, k) \
    ((void) stbds_shgeti(t,k), &(t)[stbds_temp(t-1)])

#define stbds_shdel(t,k) \
    (((t) = stbds_hmdel_key_wrapper((t),sizeof *(t), (void*) (k), sizeof (t)->key, STBDS_OFFSETOF((t),key), STBDS_HM_STRING)),(t)?stbds_temp((t)-1):0)

#define stbds_sh_new_arena(t)  \
    ((t) = stbds_shmode_func_wrapper(t, sizeof *(t), STBDS_SH_ARENA))
#define stbds_sh_new_strdup(t) \
    ((t) = stbds_shmode_func_wrapper(t, sizeof *(t), STBDS_SH_STRDUP))

#define stbds_shdefault(t, v) stbds_hmdefault(t,v)
#define stbds_shdefaults(t, s) stbds_hmdefaults(t,s)

#define stbds_shfree       stbds_hmfree
#define stbds_shlenu       stbds_hmlenu

#define stbds_shgets(t, k) (*stbds_shgetp(t,k))
#define stbds_shget(t, k)  (stbds_shgetp(t,k)->value)
#define stbds_shlen        stbds_hmlen

typedef struct
{
  size_t      length;
  size_t      capacity;
  void      * hash_table;
  ptrdiff_t   temp;
} stbds_array_header;

typedef struct stbds_string_block
{
  struct stbds_string_block *next;
  char storage[8];
} stbds_string_block;

struct stbds_string_arena
{
  stbds_string_block *storage;
  size_t remaining;
  unsigned char block;
  unsigned char mode;  // this isn't used by the string arena itself
};

enum
{
   STBDS_HM_BINARY,
   STBDS_HM_STRING,
};

enum
{
   STBDS_SH_NONE,
   STBDS_SH_STRDUP,
   STBDS_SH_ARENA
};

#ifdef __cplusplus
// in C we use implicit assignment from these void*-returning functions to T*.
// in C++ these templates make the same code work
template<class T> static T * stbds_arrgrowf_wrapper(T *a, size_t elemsize, size_t addlen, size_t min_cap) {
  return (T*)stbds_arrgrowf((void *)a, elemsize, addlen, min_cap);
}
template<class T> static T * stbds_hmget_key_wrapper(T *a, size_t elemsize, void *key, size_t keysize, int mode) {
  return (T*)stbds_hmget_key((void*)a, elemsize, key, keysize, mode);
}
template<class T> static T * stbds_hmput_default_wrapper(T *a, size_t elemsize) {
  return (T*)stbds_hmput_default((void *)a, elemsize);
}
template<class T> static T * stbds_hmput_key_wrapper(T *a, size_t elemsize, void *key, size_t keysize, int mode) {
  return (T*)stbds_hmput_key((void*)a, elemsize, key, keysize, mode);
}
template<class T> static T * stbds_hmdel_key_wrapper(T *a, size_t elemsize, void *key, size_t keysize, size_t keyoffset, int mode){
  return (T*)stbds_hmdel_key((void*)a, elemsize, key, keysize, keyoffset, mode);
}
template<class T> static T * stbds_shmode_func_wrapper(T *, size_t elemsize, int mode) {
  return (T*)stbds_shmode_func(elemsize, mode);
}
#else
#define stbds_arrgrowf_wrapper            stbds_arrgrowf
#define stbds_hmget_key_wrapper           stbds_hmget_key
#define stbds_hmput_default_wrapper       stbds_hmput_default
#define stbds_hmput_key_wrapper           stbds_hmput_key
#define stbds_hmdel_key_wrapper           stbds_hmdel_key
#define stbds_shmode_func_wrapper(t,e,m)  stbds_shmode_func(e,m)
#endif

#endif // INCLUDE_STB_DS_H


//////////////////////////////////////////////////////////////////////////////
//
//   IMPLEMENTATION
//

#ifdef STB_DS_IMPLEMENTATION
#include <assert.h>
#include <string.h>

#ifndef STBDS_ASSERT
#define STBDS_ASSERT(x)   ((void) 0)
#endif

#ifdef STBDS_STATISTICS
#define STBDS_STATS(x)   x
size_t stbds_array_grow;
size_t stbds_hash_grow;
size_t stbds_hash_shrink;
size_t stbds_hash_rebuild;
size_t stbds_hash_probes;
size_t stbds_hash_alloc;
size_t stbds_rehash_probes;
size_t stbds_rehash_items;
#else
#define STBDS_STATS(x)
#endif

//
// stbds_arr implementation
//

void *stbds_arrgrowf(void *a, size_t elemsize, size_t addlen, size_t min_cap)
{
  void *b;
  size_t min_len = stbds_arrlen(a) + addlen;

  // compute the minimum capacity needed
  if (min_len > min_cap)
    min_cap = min_len;

  if (min_cap <= stbds_arrcap(a))
    return a;

  // increase needed capacity to guarantee O(1) amortized
  if (min_cap < 2 * stbds_arrcap(a))
    min_cap = 2 * stbds_arrcap(a);
  else if (min_cap < 4)
    min_cap = 4;

  b = realloc((a) ? stbds_header(a) : 0, elemsize * min_cap + sizeof(stbds_array_header));
  b = (char *) b + sizeof(stbds_array_header);
  if (a == NULL) {
    stbds_header(b)->length = 0;
    stbds_header(b)->hash_table = 0;
  } else {
    STBDS_STATS(++stbds_array_grow);
  }
  stbds_header(b)->capacity = min_cap;
  return b;
}

//
// stbds_hm hash table implementation
//

#define STBDS_CACHE_LINE_SIZE   64
#define STBDS_BUCKET_LENGTH      8
#define STBDS_BUCKET_SHIFT       3
#define STBDS_BUCKET_MASK       (STBDS_BUCKET_LENGTH-1)

#define STBDS_ALIGN_FWD(n,a)   (((n) + (a) - 1) & ~((a)-1))

typedef struct
{
   size_t    hash [STBDS_BUCKET_LENGTH];
   ptrdiff_t index[STBDS_BUCKET_LENGTH];
} stbds_hash_bucket; // in 32-bit, this is one 64-byte cache line; in 64-bit, each array is one 64-byte cache line

typedef struct
{
  size_t slot_count;
  size_t used_count;
  size_t used_count_threshold;
  size_t used_count_shrink_threshold;
  size_t tombstone_count;
  size_t tombstone_count_threshold;
  size_t seed;
  size_t slot_count_log2;
  stbds_string_arena string;
  stbds_hash_bucket *storage; // not a separate allocation, just 64-byte aligned storage after this struct
} stbds_hash_index;

#define STBDS_INDEX_EMPTY    -1
#define STBDS_INDEX_DELETED  -2
#define STBDS_INDEX_IN_USE(x)  ((x) >= 0)

#define STBDS_HASH_EMPTY      0
#define STBDS_HASH_DELETED    1

static size_t stbds_hash_seed=0x31415926;

void stbds_rand_seed(size_t seed)
{
  stbds_hash_seed = seed;
}

#define stbds_load_32_or_64(var, temp, v32, v64_hi, v64_lo)                                          \
  temp = v64_lo ^ v32, temp <<= 16, temp <<= 16, temp >>= 16, temp >>= 16, /* discard if 32-bit */   \
  var = v64_hi, var <<= 16, var <<= 16,                                    /* discard if 32-bit */   \
  var ^= temp ^ v32

#define STBDS_SIZE_T_BITS           ((sizeof (size_t)) * 8)

static size_t stbds_probe_position(size_t hash, size_t slot_count, size_t slot_log2)
{
  #if 1
  size_t pos = (hash >> (STBDS_SIZE_T_BITS-slot_log2));
  STBDS_ASSERT(pos < slot_count);
  return pos;
  #else
  return hash & (slot_count-1);
  #endif
}

static size_t stbds_log2(size_t slot_count)
{
  size_t n=0;
  while (slot_count > 1) {
    slot_count >>= 1;
    ++n;
  }
  return n;
}

static stbds_hash_index *stbds_make_hash_index(size_t slot_count, stbds_hash_index *ot)
{
  stbds_hash_index *t;
  t = (stbds_hash_index *) realloc(0,(slot_count >> STBDS_BUCKET_SHIFT) * sizeof(stbds_hash_bucket) + sizeof(stbds_hash_index) + STBDS_CACHE_LINE_SIZE-1);
  t->storage = (stbds_hash_bucket *) STBDS_ALIGN_FWD((size_t) (t+1), STBDS_CACHE_LINE_SIZE);
  t->slot_count = slot_count;
  t->slot_count_log2 = stbds_log2(slot_count);
  t->tombstone_count = 0;
  t->used_count = 0;

  #if 0 // A1
  t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink
  #elif 1 // A2
  //t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  //t->tombstone_count_threshold   = slot_count* 3/16; // if tombstones are 3/16th of table, rebuild
  //t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink

  // compute without overflowing
  t->used_count_threshold        = slot_count - (slot_count>>2);
  t->tombstone_count_threshold   = (slot_count>>3) + (slot_count>>4);
  t->used_count_shrink_threshold = slot_count >> 2;

  #elif 0 // B1
  t->used_count_threshold        = slot_count*13/16; // if 13/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 5/16; // if table is only 5/16th full, shrink
  #else // C1
  t->used_count_threshold        = slot_count*14/16; // if 14/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 6/16; // if table is only 6/16th full, shrink
  #endif
  // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
    // Note that the larger tables have high variance as they were run fewer times
  //     A1            A2          B1           C1
  //    0.10ms :     0.10ms :     0.10ms :     0.11ms :      2,000 inserts creating 2K table   
  //    0.96ms :     0.95ms :     0.97ms :     1.04ms :     20,000 inserts creating 20K table  
  //   14.48ms :    14.46ms :    10.63ms :    11.00ms :    200,000 inserts creating 200K table 
  //  195.74ms :   196.35ms :   203.69ms :   214.92ms :  2,000,000 inserts creating 2M table   
  // 2193.88ms :  2209.22ms :  2285.54ms :  2437.17ms : 20,000,000 inserts creating 20M table  
  //   65.27ms :    53.77ms :    65.33ms :    65.47ms : 500,000 inserts & deletes in 2K table  
  //   72.78ms :    62.45ms :    71.95ms :    72.85ms : 500,000 inserts & deletes in 20K table 
  //   89.47ms :    77.72ms :    96.49ms :    96.75ms : 500,000 inserts & deletes in 200K table
  //   97.58ms :    98.14ms :    97.18ms :    97.53ms : 500,000 inserts & deletes in 2M table  
  //  118.61ms :   119.62ms :   120.16ms :   118.86ms : 500,000 inserts & deletes in 20M table 
  //  192.11ms :   194.39ms :   196.38ms :   195.73ms : 500,000 inserts & deletes in 200M table

  if (slot_count <= STBDS_BUCKET_LENGTH)
    t->used_count_shrink_threshold = 0;
  // to avoid infinite loop, we need to guarantee that at least one slot is empty and will terminate probes
  STBDS_ASSERT(t->used_count_threshold + t->tombstone_count_threshold < t->slot_count);
  STBDS_STATS(++stbds_hash_alloc);
  if (ot) {
    t->string = ot->string;
    // reuse old seed so we can reuse old hashes so below "copy out old data" doesn't do any hashing
    t->seed = ot->seed;
  } else {
    size_t a,b,temp;
    memset(&t->string, 0, sizeof(t->string));
    t->seed = stbds_hash_seed;
    // LCG
    // in 32-bit, a =          2147001325   b =  715136305
    // in 64-bit, a = 2862933555777941757   b = 3037000493
    stbds_load_32_or_64(a,temp, 2147001325, 0x27bb2ee6, 0x87b0b0fd);
    stbds_load_32_or_64(b,temp,  715136305,          0, 0xb504f32d);
    stbds_hash_seed = stbds_hash_seed  * a + b;
  }

  {
    size_t i,j;
    for (i=0; i < slot_count >> STBDS_BUCKET_SHIFT; ++i) {
      stbds_hash_bucket *b = &t->storage[i];
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j)
        b->hash[j] = STBDS_HASH_EMPTY;
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j)
        b->index[j] = STBDS_INDEX_EMPTY;
    }
  }

  // copy out the old data, if any
  if (ot) {
    size_t i,j;
    t->used_count = ot->used_count;
    for (i=0; i < ot->slot_count >> STBDS_BUCKET_SHIFT; ++i) {
      stbds_hash_bucket *ob = &ot->storage[i];
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j) {
        if (STBDS_INDEX_IN_USE(ob->index[j])) {
          size_t hash = ob->hash[j];
          size_t pos = stbds_probe_position(hash, t->slot_count, t->slot_count_log2);
          size_t step = STBDS_BUCKET_LENGTH;
          STBDS_STATS(++stbds_rehash_items);
          for (;;) {
            size_t limit,z;
            stbds_hash_bucket *bucket;
            pos &= (t->slot_count-1);
            bucket = &t->storage[pos >> STBDS_BUCKET_SHIFT];
            STBDS_STATS(++stbds_rehash_probes);

            for (z=pos & STBDS_BUCKET_MASK; z < STBDS_BUCKET_LENGTH; ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }

            limit = pos & STBDS_BUCKET_MASK;
            for (z = 0; z < limit; ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }

            pos += step;                  // quadratic probing
            step += STBDS_BUCKET_LENGTH;
          }
        }
       done:
        ;
      }
    }
  }

  return t;
}

#define STBDS_ROTATE_LEFT(val, n)   (((val) << (n)) | ((val) >> (STBDS_SIZE_T_BITS - (n))))
#define STBDS_ROTATE_RIGHT(val, n)  (((val) >> (n)) | ((val) << (STBDS_SIZE_T_BITS - (n))))

size_t stbds_hash_string(char *str, size_t seed)
{
  size_t hash = seed;
  while (*str)
     hash = STBDS_ROTATE_LEFT(hash, 9) + (unsigned char) *str++;

  // Thomas Wang 64-to-32 bit mix function, hopefully also works in 32 bits
  hash ^= seed;
  hash = (~hash) + (hash << 18);
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,31);
  hash = hash * 21;
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,11);
  hash += (hash << 6);
  hash ^= STBDS_ROTATE_RIGHT(hash,22);
  return hash+seed;
}

#ifdef STBDS_SIPHASH_2_4
#define STBDS_SIPHASH_C_ROUNDS 2
#define STBDS_SIPHASH_D_ROUNDS 4
typedef int STBDS_SIPHASH_2_4_can_only_be_used_in_64_bit_builds[sizeof(size_t) == 8 ? 1 : -1];
#endif

#ifndef STBDS_SIPHASH_C_ROUNDS
#define STBDS_SIPHASH_C_ROUNDS 1
#endif
#ifndef STBDS_SIPHASH_D_ROUNDS
#define STBDS_SIPHASH_D_ROUNDS 1
#endif

static size_t stbds_siphash_bytes(void *p, size_t len, size_t seed)
{
  unsigned char *d = (unsigned char *) p;
  size_t i,j;
  size_t v0,v1,v2,v3, data;

  // hash that works on 32- or 64-bit registers without knowing which we have
  // (computes different results on 32-bit and 64-bit platform)
  // derived from siphash, but on 32-bit platforms very different as it uses 4 32-bit state not 4 64-bit
  v0 = ((((size_t) 0x736f6d65 << 16) << 16) + 0x70736575) ^  seed;
  v1 = ((((size_t) 0x646f7261 << 16) << 16) + 0x6e646f6d) ^ ~seed;
  v2 = ((((size_t) 0x6c796765 << 16) << 16) + 0x6e657261) ^  seed; 
  v3 = ((((size_t) 0x74656462 << 16) << 16) + 0x79746573) ^ ~seed;

  #ifdef STBDS_TEST_SIPHASH_2_4
  // hardcoded with key material in the siphash test vectors
  v0 ^= 0x0706050403020100ull ^  seed;
  v1 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
  v2 ^= 0x0706050403020100ull ^  seed;
  v3 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
  #endif

  #define STBDS_SIPROUND() \
    do {                   \
      v0 += v1; v1 = STBDS_ROTATE_LEFT(v1, 13);  v1 ^= v0; v0 = STBDS_ROTATE_LEFT(v0,STBDS_SIZE_T_BITS/2); \
      v2 += v3; v3 = STBDS_ROTATE_LEFT(v3, 16);  v3 ^= v2;                                                 \
      v2 += v1; v1 = STBDS_ROTATE_LEFT(v1, 17);  v1 ^= v2; v2 = STBDS_ROTATE_LEFT(v2,STBDS_SIZE_T_BITS/2); \
      v0 += v3; v3 = STBDS_ROTATE_LEFT(v3, 21);  v3 ^= v0;                                                 \
    } while (0)

  for (i=0; i+sizeof(size_t) <= len; i += sizeof(size_t), d += sizeof(size_t)) {
    data = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    data |= (size_t) (d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24)) << 16 << 16; // discarded if size_t == 4

    v3 ^= data;
    for (j=0; j < STBDS_SIPHASH_C_ROUNDS; ++j)
      STBDS_SIPROUND();
    v0 ^= data;
  }
  data = len << (STBDS_SIZE_T_BITS-8);
  switch (len - i) {
    case 7: data |= ((size_t) d[6] << 24) << 24;
    case 6: data |= ((size_t) d[5] << 20) << 20;
    case 5: data |= ((size_t) d[4] << 16) << 16;
    case 4: data |= (d[3] << 24);
    case 3: data |= (d[2] << 16);
    case 2: data |= (d[1] << 8);
    case 1: data |= d[0];
    case 0: break;
  }
  v3 ^= data;
  for (j=0; j < STBDS_SIPHASH_C_ROUNDS; ++j)
    STBDS_SIPROUND();
  v0 ^= data;
  v2 ^= 0xff;
  for (j=0; j < STBDS_SIPHASH_D_ROUNDS; ++j)
    STBDS_SIPROUND();
#ifdef STBDS_SIPHASH_2_4
  return v0^v1^v2^v3;
#else
  return v1^v2^v3; // slightly stronger since v0^v3 in above cancels out final round operation
#endif
}

size_t stbds_hash_bytes(void *p, size_t len, size_t seed)
{
#ifdef STBDS_SIPHASH_2_4
  return stbds_siphash_bytes(p,len,seed);
#else
  unsigned char *d = (unsigned char *) p;

  if (len == 4) {
    unsigned int hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    #if 0
    // HASH32-A  Bob Jenkin's hash function w/o large constants
    hash ^= seed ^ len;
    hash -= (hash<<6);
    hash ^= (hash>>17);
    hash -= (hash<<9);
    hash ^= (hash<<4);
    hash -= (hash<<3);
    hash ^= (hash<<10);
    hash ^= (hash>>15);
    #elif 1
    // HASH32-BB  Bob Jenkin's presumably-accidental version of Thomas Wang hash with rotates turned into shifts.
    // Note that converting these back to rotates makes it run a lot slower, presumably due to collisions, so I'm
    // not really sure what's going on.
    hash ^= seed ^ len;
    hash = (hash ^ 61) ^ (hash >> 16);
    hash = hash + (hash << 3);
    hash = hash ^ (hash >> 4);
    hash = hash * 0x27d4eb2d;
    hash = hash ^ (hash >> 15);
    #else  // HASH32-C   -  Murmur3
    hash *= 0xcc9e2d51;
    hash = (hash << 17) | (hash >> 15);
    hash *= 0x1b873593;
    hash ^= seed;
    hash = (hash << 19) | (hash >> 13);
    hash = hash*5 + 0xe6546b64;
    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;
    #endif
    // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
    // Note that the larger tables have high variance as they were run fewer times
    //  HASH32-A   //  HASH32-BB  //  HASH32-C
    //    0.10ms   //    0.10ms   //    0.10ms :      2,000 inserts creating 2K table   
    //    0.96ms   //    0.95ms   //    0.99ms :     20,000 inserts creating 20K table  
    //   14.69ms   //   14.43ms   //   14.97ms :    200,000 inserts creating 200K table 
    //  199.99ms   //  195.36ms   //  202.05ms :  2,000,000 inserts creating 2M table   
    // 2234.84ms   // 2187.74ms   // 2240.38ms : 20,000,000 inserts creating 20M table  
    //   55.68ms   //   53.72ms   //   57.31ms : 500,000 inserts & deletes in 2K table  
    //   63.43ms   //   61.99ms   //   65.73ms : 500,000 inserts & deletes in 20K table 
    //   80.04ms   //   77.96ms   //   81.83ms : 500,000 inserts & deletes in 200K table
    //  100.42ms   //   97.40ms   //  102.39ms : 500,000 inserts & deletes in 2M table  
    //  119.71ms   //  120.59ms   //  121.63ms : 500,000 inserts & deletes in 20M table 
    //  185.28ms   //  195.15ms   //  187.74ms : 500,000 inserts & deletes in 200M table
    //   15.58ms   //   14.79ms   //   15.52ms : 200,000 inserts creating 200K table with varying key spacing

    return (((size_t) hash << 16 << 16) | hash) ^ seed;
  } else if (len == 8 && sizeof(size_t) == 8) {
    size_t hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    hash |= (size_t) (d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24)) << 16 << 16; // avoid warning if size_t == 4
    hash ^= seed ^ len;
    hash = (~hash) + (hash << 21);
    hash ^= STBDS_ROTATE_RIGHT(hash,24);
    hash *= 265;
    hash ^= STBDS_ROTATE_RIGHT(hash,14);
    hash *= 21;
    hash ^= STBDS_ROTATE_RIGHT(hash,28);
    hash += (hash << 31);
    hash = (~hash) + (hash << 18);
    return hash^seed;
  } else {
    return stbds_siphash_bytes(p,len,seed);
  }
#endif
}

static int stbds_is_key_equal(void *a, size_t elemsize, void *key, size_t keysize, int mode, size_t i)
{
  if (mode >= STBDS_HM_STRING)
    return 0==strcmp((char *) key, * (char **) ((char *) a + elemsize*i));
  else
    return 0==memcmp(key, (char *) a + elemsize*i, keysize);
}

#define STBDS_HASH_TO_ARR(x,elemsize) ((char*) (x) - (elemsize))
#define STBDS_ARR_TO_HASH(x,elemsize) ((char*) (x) + (elemsize))
#define STBDS_FREE(x)  realloc(x,0)

#define stbds_hash_table(a)  ((stbds_hash_index *) stbds_header(a)->hash_table)
 
void stbds_hmfree_func(void *a, size_t elemsize, size_t keyoff)
{
  if (a == NULL) return;
  if (stbds_hash_table(a) != NULL) {
     if (stbds_hash_table(a)->string.mode == STBDS_SH_STRDUP) {
       size_t i;
       // skip 0th element, which is default
       for (i=1; i < stbds_header(a)->length; ++i)
         STBDS_FREE(*(char**) ((char *) a + elemsize*i));
     }
     stbds_strreset(&stbds_hash_table(a)->string);
   }
  STBDS_FREE(stbds_header(a)->hash_table);
  STBDS_FREE(stbds_header(a));
}

static ptrdiff_t stbds_hm_find_slot(void *a, size_t elemsize, void *key, size_t keysize, int mode)
{
  void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
  stbds_hash_index *table = stbds_hash_table(raw_a);
  size_t hash = mode >= STBDS_HM_STRING ? stbds_hash_string((char*)key,table->seed) : stbds_hash_bytes(key, keysize,table->seed);
  size_t step = STBDS_BUCKET_LENGTH;
  size_t limit,i;
  size_t pos;
  stbds_hash_bucket *bucket;

  if (hash < 2) hash += 2; // stored hash values are forbidden from being 0, so we can detect empty slots

  pos = stbds_probe_position(hash, table->slot_count, table->slot_count_log2);

  for (;;) {
    STBDS_STATS(++stbds_hash_probes);
    bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];

    // start searching from pos to end of bucket, this should help performance on small hash tables that fit in cache
    for (i=pos & STBDS_BUCKET_MASK; i < STBDS_BUCKET_LENGTH; ++i) {
      if (bucket->hash[i] == hash) {
        if (stbds_is_key_equal(a, elemsize, key, keysize, mode, bucket->index[i])) {
          return (pos & ~STBDS_BUCKET_MASK)+i;
        }
      } else if (bucket->hash[i] == STBDS_HASH_EMPTY) {
        return -1;
      }
    }

    // search from beginning of bucket to pos
    limit = pos & STBDS_BUCKET_MASK;
    for (i = 0; i < limit; ++i) {
      if (bucket->hash[i] == hash) {
        if (stbds_is_key_equal(a, elemsize, key, keysize, mode, bucket->index[i])) {
          return (pos & ~STBDS_BUCKET_MASK)+i;
        }
      } else if (bucket->hash[i] == STBDS_HASH_EMPTY) {
        return -1;
      }
    }

    // quadratic probing
    pos += step;
    step += STBDS_BUCKET_LENGTH;
    pos &= (table->slot_count-1);
  }
  /* NOTREACHED */
  return -1;
}

void * stbds_hmget_key(void *a, size_t elemsize, void *key, size_t keysize, int mode)
{
  if (a == NULL) {
    // make it non-empty so we can return a temp
    a = stbds_arrgrowf(0, elemsize, 0, 1);
    stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    stbds_temp(a) = STBDS_INDEX_EMPTY;
    // adjust a to point after the default element
    return STBDS_ARR_TO_HASH(a,elemsize);
  } else {
    stbds_hash_index *table;
    void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
    // adjust a to point to the default element
    table = (stbds_hash_index *) stbds_header(raw_a)->hash_table;
    if (table == 0) {
      stbds_temp(raw_a) = -1;
    } else {
      ptrdiff_t slot = stbds_hm_find_slot(a, elemsize, key, keysize, mode);
      if (slot < 0) {
        stbds_temp(raw_a) = STBDS_INDEX_EMPTY;
      } else {
        stbds_hash_bucket *b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
        stbds_temp(raw_a) = b->index[slot & STBDS_BUCKET_MASK];
      }
    }
    return a;
  }
}

void * stbds_hmput_default(void *a, size_t elemsize)
{
  // three cases:
  //   a is NULL <- allocate
  //   a has a hash table but no entries, because of shmode <- grow
  //   a has entries <- do nothing
  if (a == NULL || stbds_header(STBDS_HASH_TO_ARR(a,elemsize))->length == 0) {
    a = stbds_arrgrowf(a ? STBDS_HASH_TO_ARR(a,elemsize) : NULL, elemsize, 0, 1);
    stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    a=STBDS_ARR_TO_HASH(a,elemsize);
  }
  return a;
}

static char *stbds_strdup(char *str);

void *stbds_hmput_key(void *a, size_t elemsize, void *key, size_t keysize, int mode)
{
  void *raw_a;
  stbds_hash_index *table;

  if (a == NULL) {
    a = stbds_arrgrowf(0, elemsize, 0, 1);
    memset(a, 0, elemsize);
    stbds_header(a)->length += 1;
    // adjust a to point AFTER the default element
    a = STBDS_ARR_TO_HASH(a,elemsize);
  }

  // adjust a to point to the default element
  raw_a = a;
  a = STBDS_HASH_TO_ARR(a,elemsize);

  table = (stbds_hash_index *) stbds_header(a)->hash_table;

  if (table == NULL || table->used_count >= table->used_count_threshold) {
    stbds_hash_index *nt;
    size_t slot_count;

    slot_count = (table == NULL) ? STBDS_BUCKET_LENGTH : table->slot_count*2;
    nt = stbds_make_hash_index(slot_count, table);
    if (table) {
      STBDS_FREE(table);
    }
    stbds_header(a)->hash_table = table = nt;
    STBDS_STATS(++stbds_hash_grow);
  }

  // we iterate hash table explicitly because we want to track if we saw a tombstone
  {
    size_t hash = mode >= STBDS_HM_STRING ? stbds_hash_string((char*)key,table->seed) : stbds_hash_bytes(key, keysize,table->seed);
    size_t step = STBDS_BUCKET_LENGTH;
    size_t limit,i;
    size_t pos;
    ptrdiff_t tombstone = -1;
    stbds_hash_bucket *bucket;

    // stored hash values are forbidden from being 0, so we can detect empty slots to early out quickly
    if (hash < 2) hash += 2;

    pos = stbds_probe_position(hash, table->slot_count, table->slot_count_log2);

    for (;;) {
      STBDS_STATS(++stbds_hash_probes);
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];

      // start searching from pos to end of bucket
      for (i=pos & STBDS_BUCKET_MASK; i < STBDS_BUCKET_LENGTH; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // search from beginning of bucket to pos
      limit = pos & STBDS_BUCKET_MASK;
      for (i = 0; i < limit; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // quadratic probing
      pos += step;
      step += STBDS_BUCKET_LENGTH;
      pos &= (table->slot_count-1);
    }
   found_empty_slot:
    if (tombstone >= 0) {
      pos = tombstone;
      --table->tombstone_count;
    }
    ++table->used_count;

    {
      ptrdiff_t i = (ptrdiff_t) stbds_arrlen(a);
    // we want to do stbds_arraddn(1), but we can't use the macros since we don't have something of the right type
      if ((size_t) i+1 > stbds_arrcap(a))
        *(void **) &a = stbds_arrgrowf(a, elemsize, 1, 0);
      raw_a = STBDS_ARR_TO_HASH(a,elemsize);

      STBDS_ASSERT((size_t) i+1 <= stbds_arrcap(a));
      stbds_header(a)->length = i+1;
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];
      bucket->hash[pos & STBDS_BUCKET_MASK] = hash;
      bucket->index[pos & STBDS_BUCKET_MASK] = i-1;
      stbds_temp(a) = i-1;

      switch (table->string.mode) {
         case STBDS_SH_STRDUP: *(char **) ((char *) a + elemsize*i) = stbds_strdup((char*) key); break;
         case STBDS_SH_ARENA:  *(char **) ((char *) a + elemsize*i) = stbds_stralloc(&table->string, (char*)key); break;
         default:              *(char **) ((char *) a + elemsize*i) = (char *) key; break;
      }
    }
    return STBDS_ARR_TO_HASH(a,elemsize);
  }
}

void * stbds_shmode_func(size_t elemsize, int mode)
{
  void *a = stbds_arrgrowf(0, elemsize, 0, 1);
  stbds_hash_index *h;
  stbds_header(a)->hash_table = h = (stbds_hash_index *) stbds_make_hash_index(STBDS_BUCKET_LENGTH, NULL);
  h->string.mode = mode;
  return STBDS_ARR_TO_HASH(a,elemsize);
}

void * stbds_hmdel_key(void *a, size_t elemsize, void *key, size_t keysize, size_t keyoffset, int mode)
{
  if (a == NULL) {
    return 0;
  } else {
    stbds_hash_index *table;
    void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
    table = (stbds_hash_index *) stbds_header(raw_a)->hash_table;
    stbds_temp(raw_a) = 0;
    if (table == 0) {
      return a;
    } else {
      ptrdiff_t slot;
      slot = stbds_hm_find_slot(a, elemsize, key, keysize, mode);
      if (slot < 0)
        return a;
      else {
        stbds_hash_bucket *b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
        int i = slot & STBDS_BUCKET_MASK;
        ptrdiff_t old_index = b->index[i];
        ptrdiff_t final_index = (ptrdiff_t) stbds_arrlen(raw_a)-1-1; // minus one for the raw_a vs a, and minus one for 'last'
        STBDS_ASSERT(slot < (ptrdiff_t) table->slot_count);
        --table->used_count;
        ++table->tombstone_count;
        stbds_temp(raw_a) = 1;
        STBDS_ASSERT(table->used_count >= 0);
        //STBDS_ASSERT(table->tombstone_count < table->slot_count/4);
        b->hash[i] = STBDS_HASH_DELETED;
        b->index[i] = STBDS_INDEX_DELETED;

        if (mode == STBDS_HM_STRING && table->string.mode == STBDS_SH_STRDUP)
          STBDS_FREE(*(char**) ((char *) a+elemsize*old_index));

        // if indices are the same, memcpy is a no-op, but back-pointer-fixup will fail, so skip
        if (old_index != final_index) {
          // swap delete 
          memmove((char*) a + elemsize*old_index, (char*) a + elemsize*final_index, elemsize);

          // now find the slot for the last element
          if (mode == STBDS_HM_STRING)
            slot = stbds_hm_find_slot(a, elemsize, *(char**) ((char *) a+elemsize*old_index + keyoffset), keysize, mode);
          else
            slot = stbds_hm_find_slot(a, elemsize,  (char* ) a+elemsize*old_index + keyoffset, keysize, mode);
          STBDS_ASSERT(slot >= 0);
          b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
          i = slot & STBDS_BUCKET_MASK;
          STBDS_ASSERT(b->index[i] == final_index);
          b->index[i] = old_index;
        }
        stbds_header(raw_a)->length -= 1;

        if (table->used_count < table->used_count_shrink_threshold && table->slot_count > STBDS_BUCKET_LENGTH) {
          stbds_header(raw_a)->hash_table = stbds_make_hash_index(table->slot_count>>1, table);
          STBDS_FREE(table);
          STBDS_STATS(++stbds_hash_shrink);
        } else if (table->tombstone_count > table->tombstone_count_threshold) {
          stbds_header(raw_a)->hash_table = stbds_make_hash_index(table->slot_count   , table);
          STBDS_FREE(table);
          STBDS_STATS(++stbds_hash_rebuild);
        }

        return a;
      }
    }
  }
  /* NOTREACHED */
  return 0;
}

static char *stbds_strdup(char *str)
{
  // to keep replaceable allocator simple, we don't want to use strdup.
  // rolling our own also avoids problem of strdup vs _strdup
  size_t len = strlen(str)+1;
  char *p = (char*) realloc(0, len);
  memmove(p, str, len);
  return p;
}

#ifndef STBDS_STRING_ARENA_BLOCKSIZE_MIN
#define STBDS_STRING_ARENA_BLOCKSIZE_MIN  512
#endif
#ifndef STBDS_STRING_ARENA_BLOCKSIZE_MAX
#define STBDS_STRING_ARENA_BLOCKSIZE_MAX  1<<20
#endif

char *stbds_stralloc(stbds_string_arena *a, char *str)
{
  char *p;
  size_t len = strlen(str)+1;
  if (len > a->remaining) {
    // compute the next blocksize
    size_t blocksize = a->block;

    // size is 512, 512, 1024, 1024, 2048, 2048, 4096, 4096, etc., so that
    // there are log(SIZE) allocations to free when we destroy the table
    blocksize = (size_t) (STBDS_STRING_ARENA_BLOCKSIZE_MIN) << (blocksize>>1);

    // if size is under 1M, advance to next blocktype
    if (blocksize < (size_t)(STBDS_STRING_ARENA_BLOCKSIZE_MAX))
      ++a->block;

    if (len > blocksize) {
      // if string is larger than blocksize, then just allocate the full size.
      // note that we still advance string_block so block size will continue
      // increasing, so e.g. if somebody only calls this with 1000-long strings,
      // eventually the arena will start doubling and handling those as well
      stbds_string_block *sb = (stbds_string_block *) realloc(0, sizeof(*sb)-8 + len);
      memmove(sb->storage, str, len);
      if (a->storage) {
        // insert it after the first element, so that we don't waste the space there
        sb->next = a->storage->next;
        a->storage->next = sb;
      } else {
        sb->next = 0;
        a->storage = sb;
        a->remaining = 0; // this is redundant, but good for clarity
      }
      return sb->storage;
    } else {
      stbds_string_block *sb = (stbds_string_block *) realloc(0, sizeof(*sb)-8 + blocksize);
      sb->next = a->storage;
      a->storage = sb;
      a->remaining = blocksize;
    }
  }

  STBDS_ASSERT(len <= a->remaining);
  p = a->storage->storage + a->remaining - len;
  a->remaining -= len;
  memmove(p, str, len);
  return p;
}

void stbds_strreset(stbds_string_arena *a)
{
  stbds_string_block *x,*y;
  x = a->storage;
  while (x) {
    y = x->next;
    realloc(x,0);
    x = y;
  }
  memset(a, 0, sizeof(*a));
}

#endif

//////////////////////////////////////////////////////////////////////////////
//
//   UNIT TESTS
//

#ifdef STBDS_UNIT_TESTS
#include <stdio.h>
#ifndef STBDS_ASSERT
#define STBDS_ASSERT assert
#include <assert.h>
#endif

typedef struct { int key,b,c,d; } stbds_struct;

static char buffer[256];
char *strkey(int n)
{
   sprintf(buffer, "test_%d", n);
   return buffer;
}

void stbds_unit_tests(void)
{
#if defined(_MSC_VER) && _MSC_VER <= 1200 && defined(__cplusplus)
  // VC6 C++ doesn't like the template<> trick on unnamed structures, so do nothing!
  STBDS_ASSERT(0);
#else
  const int testsize = 100000;
  int *arr=NULL;
  struct { int   key;        int value; } *intmap = NULL;
  struct { char *key;        int value; } *strmap = NULL;
  struct { stbds_struct key; int value; } *map    = NULL;
  stbds_struct                            *map2   = NULL;
  stbds_string_arena                       sa     = { 0 };

  int i,j;

  for (i=0; i < 20000; i += 50) {
    for (j=0; j < i; ++j)
      arrpush(arr,j);
    arrfree(arr);
  }

  for (i=0; i < 4; ++i) {
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    arrdel(arr,i);
    arrfree(arr);
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    arrdelswap(arr,i);
    arrfree(arr);
  }

  for (i=0; i < 5; ++i) {
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    stbds_arrins(arr,i,5);
    STBDS_ASSERT(arr[i] == 5);
    if (i < 4)
      STBDS_ASSERT(arr[4] == 4);
    arrfree(arr);
  }

  hmdefault(intmap, -1);
  i=1; STBDS_ASSERT(hmget(intmap, i) == -1);
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*5);
  for (i=0; i < testsize; i+=1)
    if (i & 1) STBDS_ASSERT(hmget(intmap, i) == -1 );
    else       STBDS_ASSERT(hmget(intmap, i) == i*5);
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*3);
  for (i=0; i < testsize; i+=1)
    if (i & 1) STBDS_ASSERT(hmget(intmap, i) == -1 );
    else       STBDS_ASSERT(hmget(intmap, i) == i*3);
  for (i=2; i < testsize; i+=4)
    hmdel(intmap, i); // delete half the entries
  for (i=0; i < testsize; i+=1)
    if (i & 3) STBDS_ASSERT(hmget(intmap, i) == -1 );
    else       STBDS_ASSERT(hmget(intmap, i) == i*3);
  for (i=0; i < testsize; i+=1)
    hmdel(intmap, i); // delete the rest of the entries    
  for (i=0; i < testsize; i+=1)
    STBDS_ASSERT(hmget(intmap, i) == -1 );
  hmfree(intmap);
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*3);
  hmfree(intmap);

  #if defined(__clang__) || defined(__GNUC__)
  #ifndef __cplusplus
  intmap = NULL;
  hmput(intmap, 15, 7);
  hmput(intmap, 11, 3);
  hmput(intmap,  9, 5);
  STBDS_ASSERT(hmget(intmap, 9) == 5);
  STBDS_ASSERT(hmget(intmap, 11) == 3);
  STBDS_ASSERT(hmget(intmap, 15) == 7);
  #endif
  #endif

  for (i=0; i < testsize; ++i)
    stralloc(&sa, strkey(i));
  strreset(&sa);

  for (j=0; j < 2; ++j) {
    if (j == 0)
      sh_new_strdup(strmap);
    else
      sh_new_arena(strmap);
    shdefault(strmap, -1);
    for (i=0; i < testsize; i+=2)
      shput(strmap, strkey(i), i*3);
    for (i=0; i < testsize; i+=1)
      if (i & 1) STBDS_ASSERT(shget(strmap, strkey(i)) == -1 );
      else       STBDS_ASSERT(shget(strmap, strkey(i)) == i*3);
    for (i=2; i < testsize; i+=4)
      shdel(strmap, strkey(i)); // delete half the entries
    for (i=0; i < testsize; i+=1)
      if (i & 3) STBDS_ASSERT(shget(strmap, strkey(i)) == -1 );
      else       STBDS_ASSERT(shget(strmap, strkey(i)) == i*3);
    for (i=0; i < testsize; i+=1)
      shdel(strmap, strkey(i)); // delete the rest of the entries    
    for (i=0; i < testsize; i+=1)
      STBDS_ASSERT(shget(strmap, strkey(i)) == -1 );
    shfree(strmap);
  }

  {
    struct { char *key; char value; } *hash = NULL;
    char name[4] = "jen";
    shput(hash, "bob"   , 'h');
    shput(hash, "sally" , 'e');
    shput(hash, "fred"  , 'l');
    shput(hash, "jen"   , 'x');
    shput(hash, "doug"  , 'o');

    shput(hash, name    , 'l');
    shfree(hash);
  }

  for (i=0; i < testsize; i += 2) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    hmput(map, s, i*5);
  }

  for (i=0; i < testsize; i += 1) {
    stbds_struct s = { i,i*2,i*3  ,i*4 };
    stbds_struct t = { i,i*2,i*3+1,i*4 };
    if (i & 1) STBDS_ASSERT(hmget(map, s) == 0);
    else       STBDS_ASSERT(hmget(map, s) == i*5);
    STBDS_ASSERT(hmget(map, t) == 0);
  }

  for (i=0; i < testsize; i += 2) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    hmputs(map2, s);
  }
  hmfree(map);

  for (i=0; i < testsize; i += 1) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    stbds_struct t = { i,i*2,i*3,i*4 };
    if (i & 1) STBDS_ASSERT(hmgets(map2, s.key).d == 0);
    else       STBDS_ASSERT(hmgets(map2, s.key).d == i*4);
  }
  hmfree(map2);
#endif
}
#endif


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2019 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
