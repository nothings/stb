#include <windows.h>
#include <limits.h>

#pragma comment(lib, "advapi32")

#define STB_VORBIS_NO_PUSHDATA_API
#include "stb_vorbis.c"

#define STB_DEFINE
#include "stb.h"

// size of test slices
#define TEST_SIZE 32

// first sample to test from
#define TEST_WINDOW_START 0

// max sample to test, or 0 to test the whole file
#define TEST_WINDOW_END 736

// check if the seek has returned an offset sample, or just garbage
#define TEST_ERROR_TYPE 1

// check if the error remains consistent for the rest of the test slice
#define COMPARE_EVERY_SAMPLE_IN_ERROR 0

// stop testing on the nth test slice error
#define BAIL_ON_ERROR 4

#if BAIL_ON_ERROR
int ecount = 0;
#endif

uint32 seek_count = 0, seek_error_count = 0;

stb_vorbis * testVorb;
float * testFile = 0;
int testFileSampleCount = 0;

void empty_test_vorb();
int fill_test_vorb(const char* fname)
{ 
   printf("opening test file %s\n", fname);
   int n;
   int count = 0;
   testVorb = stb_vorbis_open_filename(fname, 0, 0);
   if (!testVorb) return 1;
   testFileSampleCount = stb_vorbis_stream_length_in_samples(testVorb);
   testFile = (float*)malloc(testVorb->channels * testFileSampleCount * sizeof(float*));
   
   n = stb_vorbis_get_samples_float_interleaved(testVorb, testVorb->channels, testFile, testFileSampleCount);
   if (n < testFileSampleCount) empty_test_vorb();

   return count;
}

int locate_test_match(float * sample, int startpos, int print) {
   int result = INT_MAX;
   int chan = testVorb->channels;
   int j;

   // search ahead first, since that's the direction of most of the offset bugs
   for (int i = startpos; i < testFileSampleCount; i++) {
      for (j = 0; j < chan; j++) {
         if (sample[j] != testFile[(i*chan) + j]) break;
      }
      if (j == chan) {
         if (i < result) result = i;
         if (print)
         printf("match found at %u (offset by %i)\n", i, (int)i - startpos);
         break;
      }
   }

   if (result == INT_MAX) {
      for (int i = 0; i < startpos; i++) {
         for (j = 0; j < chan; j++) {
            if (sample[j] != testFile[(i*chan) + j]) break;
         }
         if (j == chan) {
            if (i < result) result = i;
            if (print)
            printf("match found at %u (offset by %i)\n", i, (int)i - startpos);
            break;
         }
      }
   }

   if (result == INT_MAX && print)
      printf("no matching sample\n");
   return result;
}

void empty_test_vorb()
{
   printf("closing test file\n");
   stb_vorbis_close(testVorb);
   free(testFile);
   testFileSampleCount = 0;
}

int running = 1;

int test_seek(int seekpt, int seeklen){
   int test_seek_pt;
   if (!testVorb) return 0;
   float * comparison = (float*)malloc(seeklen * testVorb->channels * sizeof(float));
   test_seek_pt = seekpt * testVorb->channels;
   stb_vorbis_seek(testVorb, seekpt);
   stb_vorbis_get_samples_float_interleaved(testVorb, testVorb->channels, comparison, seeklen);
   seek_count++;

   int error_count = 0;
#if TEST_ERROR_TYPE
   int error_offset;
#if COMPARE_EVERY_SAMPLE_IN_ERROR
   int error_mismatch_count = 0;
#endif
#endif

   for (int i = 0; i < seeklen; i++) {
      for (int j = 0; j < testVorb->channels; j++) {
         if (testFile[test_seek_pt + j] != comparison[j]) {
            if (!error_count){
               printf("\nseeking to [%u - %u](%u samples)\n", seekpt, seekpt + seeklen, seeklen);
               printf("first error at %i: %f != %f\n",
                  j,
                  testFile[test_seek_pt + j],
                  comparison[j]);
#if TEST_ERROR_TYPE
               error_offset = locate_test_match(comparison + j, seekpt + i, 1);
#if COMPARE_EVERY_SAMPLE_IN_ERROR
            } else {
               if (error_offset != locate_test_match(comparison + j, seekpt + i, 0))
                  error_mismatch_count++;
#endif
#endif
            }
            error_count++;
         }
      }
   }

   if (error_count)
   {
#if TEST_ERROR_TYPE
#if COMPARE_EVERY_SAMPLE_IN_ERROR
      if (error_mismatch_count)
         printf("samples inconsistently offset: %i were different from first error\n", error_mismatch_count);
      else
         printf("samples all offset by same amount\n");
      printf("%i errors\n", error_count);
#endif
#endif

#if BAIL_ON_ERROR
      ecount++;
      if (ecount == BAIL_ON_ERROR) running = 0;
#endif
   seek_error_count++;
   }

   free(comparison);
   return seeklen;
}

int main(int argc, char **argv)
{
   fill_test_vorb("test.ogg");

   int cur_test = TEST_WINDOW_START/TEST_SIZE;
   
#if TEST_WINDOW_END > 0
   while (running && cur_test * TEST_SIZE < TEST_WINDOW_END ) {
#else
   while (running && cur_test * TEST_SIZE < testFileSampleCount ) {
#endif
      test_seek(cur_test * TEST_SIZE,
            TEST_SIZE);
      cur_test++;
   }

#if TEST_WINDOW_END
   test_seek(TEST_WINDOW_END, TEST_SIZE);
#endif

   printf("%u seeks failed of %u\n", seek_error_count, seek_count);

   empty_test_vorb();
   return 0;
}

