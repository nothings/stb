# Font character oversampling for rendering from atlas textures

TL,DR: Run oversample.exe on a windows machine to see the
benefits of oversampling. It will try to use arial.ttf from the
Windows font directory unless you type the name of a .ttf file as
a command-line argument.

## Benefits of oversampling

Oversampling is a mechanism for improving subpixel rendering of characters.

Improving subpixel has a few benefits:

* Text can remain sharper while still being sub-pixel positioned for better kerning
* Horizontally-oversampled text significantly reduces aliasing when text animates horizontally
* Vertically-oversampled text significantly reduces aliasing when text animates vertically
* Text oversampled in both directions significantly reduces aliasing when text rotates

## What text oversampling is

A common strategy for rendering text is to cache character bitmaps
and reuse them. For hinted characters, every instance of a given
character is always identical, so this works fine. However, stb_truetype
doesn't do hinting.

For anti-aliased characters, you can actually position the characters
with subpixel precision, and get different bitmaps based on that positioning
if you re-render the vector data.

However, if you simply cache a single version of the bitmap and
draw it at different subpixel positions with a GPU, you will get
either the exact same result (if you use point-sampling on the
texture) or linear filtering. Linear filtering will cause a sub-pixel
positioned bitmap to blur further, causing a visible de-sharpening
of the character. (And, since the character wasn't hinted, it was
already blurrier than a hinted one would be, and now it gets even
more blurry.)

You can avoid this by caching multiple variants of a character which
were rendered independently from the vector data. For example, you
might cache 3 versions of a char, at 0, 1/3, and 2/3rds of a pixel
horizontal offset, and always require characters to fall on integer
positions vertically.

When creating a texture atlas for use on GPUs, which support bilinear
filtering, there is a better approach than caching several independent
positions, which is to allow lerping between the versions to allow
finer subpixel positioning. You can achieve these by interleaving
each of the cached bitmaps, but this turns out to be mathematically
equivalent to a simpler operation: oversampling and prefiltering the
characters.

So, setting oversampling of 2x2 in stb_truetype is equivalent to caching
each character in 4 different variations, 1 for each subpixel position
in a 2x2 set.

An advantage of this formulation is that no changes are required to
the rendering code; the exact same quad-rendering code works, it just
uses different texture coordinates. (Note this does potentially increase
texture bandwidth for text rendering since we end up minifying the texture
without using mipmapping, but you probably are not going to be fill-bound
by your text rendering.)

