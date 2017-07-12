#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define BYTESIZE (8*8)*4

int test_png()
{
  int x, y, c;
  
  // Load reference image, do not flip
  stbi_set_flip_vertically_on_load(0);
  unsigned char *pngref_up = stbi_load("data/flipref_up.png", &x, &y, &c, 4);

  if(pngref_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }
  
  // Copy the data as flipping will flip the passed data
  unsigned char *pngref_up_c = (unsigned char*)malloc(BYTESIZE);
  memcpy(pngref_up_c, pngref_up, BYTESIZE);
  
  // Write reference image flipped (this modifies pngref_up_c)
  stbi_write_set_flip_vertically_on_save(1);
  if(stbi_write_png("data/flip_down.png", 8, 8, 4, pngref_up_c, 8*4) == 0)
  {
    printf("FAILED: stbi_write_png returned zero.\n");
    return 1;
  }
  
  // Free the copy
  free(pngref_up_c);
  
  // Load our previously saved flip_down, but flipped, and compare it to pngref_up
  stbi_set_flip_vertically_on_load(1);
  unsigned char *png_up = stbi_load("data/flip_down.png", &x, &y, &c, 4);
  
  if(png_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }
  
  if(memcmp(pngref_up, png_up, BYTESIZE) != 0)
  {
    printf("FAILED: memory mismatch.\n");
    return 1;
  }
 
  stbi_image_free(pngref_up);
  stbi_image_free(png_up);
  return 0;
}

int test_tga()
{
  int x, y, c;
  
  // Load reference image, do not flip
  stbi_set_flip_vertically_on_load(0);
  unsigned char *tgaref_up = stbi_load("data/flipref_up.tga", &x, &y, &c, 4);

  if(tgaref_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }
  
  // Copy the data as flipping will flip the passed data
  unsigned char *tgaref_up_c = (unsigned char*)malloc(BYTESIZE);
  memcpy(tgaref_up_c, tgaref_up, BYTESIZE);
  
  // Write reference image flipped (this modifies tgaref_up_c)
  stbi_write_set_flip_vertically_on_save(1);
  if(stbi_write_tga("data/flip_down.tga", 8, 8, 4, tgaref_up_c) == 0)
  {
    printf("FAILED: stbi_write_tga returned zero.\n");
    return 1;
  }
  
  // Free the copy
  free(tgaref_up_c);
  
  // Load our previously saved flip_down, but flipped, and compare it to tgaref_up
  stbi_set_flip_vertically_on_load(1);
  unsigned char *tga_up = stbi_load("data/flip_down.tga", &x, &y, &c, 4);
  
  if(tga_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }
  
  if(memcmp(tgaref_up, tga_up, BYTESIZE) != 0)
  {
    printf("FAILED: memory mismatch.\n");
    return 1;
  }
 
  stbi_image_free(tgaref_up);
  stbi_image_free(tga_up);
  return 0;
}

int test_bmp()
{
  int x, y, c;
  
  // Load reference image, do not flip
  stbi_set_flip_vertically_on_load(0);
  unsigned char *bmpref_up = stbi_load("data/flipref_up.bmp", &x, &y, &c, 4);
  
  if(bmpref_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }

  // Copy the data as flipping will flip the passed data
  unsigned char *bmpref_up_c = (unsigned char*)malloc(BYTESIZE);
  memcpy(bmpref_up_c, bmpref_up, BYTESIZE);
  
  // Write reference image flipped (this modifies bmpref_up_c)
  stbi_write_set_flip_vertically_on_save(1);
  if(stbi_write_bmp("data/flip_down.bmp", 8, 8, 4, bmpref_up_c) == 0)
  {
    printf("FAILED: stbi_write_bmp returned zero.\n");
    return 1;
  }
  
  // Free the copy
  free(bmpref_up_c);
  
  // Load our previously saved flip_down, but flipped, and compare it to bmpref_up
  stbi_set_flip_vertically_on_load(1);
  unsigned char *bmp_up = stbi_load("data/flip_down.bmp", &x, &y, &c, 4);
  
  if(bmp_up == NULL)
  {
    printf("FAILED: %s\n", stbi_failure_reason());
    return 1;
  }
  
  if(memcmp(bmpref_up, bmp_up, BYTESIZE) != 0)
  {
    printf("FAILED: memory mismatch.\n");
    return 1;
  }
 
  stbi_image_free(bmpref_up);
  stbi_image_free(bmp_up);
  
  return 0;
}

int main(int argc, char** argv)
{
  int err = 0;
  
  printf("testing png\n");
  err += test_png();
  
  printf("testing tga\n");
  err += test_tga();
  
  printf("testing bmp\n");
  err += test_bmp();
  
  if(err > 0)
  {
    printf("%i tests failed!", err);
  }
  else
  {
    printf("All tests successfull!\n");
  }
  
  return 0;
}
