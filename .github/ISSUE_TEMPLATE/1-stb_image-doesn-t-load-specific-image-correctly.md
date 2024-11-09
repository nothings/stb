---
name: stb_image Doesn't Load Specific Image Correctly
about: if an image displays wrong in your program, and you've verified stb_image is
  the problem
title: ''
labels: 1 stb_image
assignees: ''

---

1. **Confirm that, after loading the image with stbi_load, you've immediately written it out with stbi_write_png or similar, and that version of the image is also wrong.** If it is correct when written out, the problem is not in stb_image. If it displays wrong in a program you're writing, it's probably your display code. For example, people writing OpenGL programs frequently do not upload or display the image correctly and assume stb_image is at fault even though writing out the image demonstrates that it loads correctly.

2. *Provide an image that does not load correctly using stb_image* so we can reproduce the problem.

3. *Provide an image or description of what part of the image is incorrect and how* so we can be sure we've reproduced the problem correctly.
