<!---   THIS FILE IS AUTOMATICALLY GENERATED, DO NOT CHANGE IT BY HAND   --->

stb
===

single-file public domain (or MIT licensed) libraries for C/C++

Noteworthy:

* image loader: [stb_image.h](stb_image.h)
* image writer: [stb_image_write.h](stb_image_write.h)
* image resizer: [stb_image_resize.h](stb_image_resize.h)
* font text rasterizer: [stb_truetype.h](stb_truetype.h)
* typesafe containers: [stb_ds.h](stb_ds.h)
* dll: for those who would like to create a wrapper, implementation in other Languages (Windows, 64/32 bit) [stbDLL_x64](stbDLL_x64) [stbDLL_x86](stbDLL_x86) 
  (use "dumpbin /EXPORTS dll_name.dll" with msvc terminal in order to see the functions built in).

Most libraries by stb, except: stb_dxt by Fabian "ryg" Giesen, stb_image_resize
by Jorge L. "VinoBS" Rodriguez, and stb_sprintf by Jeff Roberts.

<a name="stb_libs"></a>

library    | lastest version | category | LoC | description
--------------------- | ---- | -------- | --- | --------------------------------
**[stb_vorbis.c](stb_vorbis.c)** | 1.20 | audio | 5563 | decode ogg vorbis files from file/memory to float/16-bit signed output
**[stb_image.h](stb_image.h)** | 2.26 | graphics | 7762 | image loading/decoding from file/memory: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
**[stb_truetype.h](stb_truetype.h)** | 1.24 | graphics | 5011 | parse, decode, and rasterize characters from truetype fonts
**[stb_image_write.h](stb_image_write.h)** | 1.15 | graphics | 1690 | image writing to disk: PNG, TGA, BMP
**[stb_image_resize.h](stb_image_resize.h)** | 0.96 | graphics | 2631 | resize images larger/smaller with good quality
**[stb_rect_pack.h](stb_rect_pack.h)** | 1.00 | graphics | 628 | simple 2D rectangle packer with decent quality
**[stb_ds.h](stb_ds.h)** | 0.65 | utility | 1880 | typesafe dynamic array and hash tables for C, will compile in C++
**[stb_sprintf.h](stb_sprintf.h)** | 1.09 | utility | 1879 | fast sprintf, snprintf for C/C++
**[stretchy_buffer.h](stretchy_buffer.h)** | 1.04 | utility | 263 | typesafe dynamic array for C (i.e. approximation to vector<>), doesn't compile as C++
**[stb_textedit.h](stb_textedit.h)** | 1.13 | user&nbsp;interface | 1404 | guts of a text editor for games etc implementing them from scratch
**[stb_voxel_render.h](stb_voxel_render.h)** | 0.89 | 3D&nbsp;graphics | 3807 | Minecraft-esque voxel rendering "engine" with many more features
**[stb_dxt.h](stb_dxt.h)** | 1.10 | 3D&nbsp;graphics | 753 | Fabian "ryg" Giesen's real-time DXT compressor
**[stb_perlin.h](stb_perlin.h)** | 0.5 | 3D&nbsp;graphics | 428 | revised Perlin noise (3D input, 1D output)
**[stb_easy_font.h](stb_easy_font.h)** | 1.1 | 3D&nbsp;graphics | 305 | quick-and-dirty easy-to-deploy bitmap font for printing frame rate, etc
**[stb_tilemap_editor.h](stb_tilemap_editor.h)** | 0.41 | game&nbsp;dev | 4161 | embeddable tilemap editor
**[stb_herringbone_wa...](stb_herringbone_wang_tile.h)** | 0.7 | game&nbsp;dev | 1221 | herringbone Wang tile map generator
**[stb_c_lexer.h](stb_c_lexer.h)** | 0.11 | parsing | 966 | simplify writing parsers for C-like languages
**[stb_divide.h](stb_divide.h)** | 0.93 | math | 430 | more useful 32-bit modulus e.g. "euclidean divide"
**[stb_connected_comp...](stb_connected_components.h)** | 0.96 | misc | 1049 | incrementally compute reachability on grids
**[stb.h](stb.h)** | 2.37 | misc | 14454 | helper functions for C, mostly redundant in C++; basically author's personal stuff
**[stb_leakcheck.h](stb_leakcheck.h)** | 0.6 | misc | 194 | quick-and-dirty malloc/free leak-checking
**[stb_include.h](stb_include.h)** | 0.02 | misc | 295 | implement recursive #include support, particularly for GLSL

Total libraries: 22
Total lines of C code: 56774


FAQ
---

#### What's the license?

These libraries are in the public domain. You can do anything you
want with them. You have no legal obligation
to do anything else, although I appreciate attribution.

They are also licensed under the MIT open source license, if you have lawyers
who are unhappy with public domain. Every source file includes an explicit
dual-license for you to choose from.

#### <a name="other_libs"></a> Are there other single-file public-domain/open source libraries with minimal dependencies out there?

[Yes.](https://github.com/nothings/single_file_libs)

#### If I wrap an stb library in a new library, does the new library have to be public domain/MIT?

No, because it's public domain you can freely relicense it to whatever license your new
library wants to be.

#### What's the deal with SSE support in GCC-based compilers?

stb_image will either use SSE2 (if you compile with -msse2) or
will not use any SIMD at all, rather than trying to detect the
processor at runtime and handle it correctly. As I understand it,
the approved path in GCC for runtime-detection require
you to use multiple source files, one for each CPU configuration.
Because stb_image is a header-file library that compiles in only
one source file, there's no approved way to build both an
SSE-enabled and a non-SSE-enabled variation.

While we've tried to work around it, we've had multiple issues over
the years due to specific versions of gcc breaking what we're doing,
so we've given up on it. See https://github.com/nothings/stb/issues/280
and https://github.com/nothings/stb/issues/410 for examples.

#### Some of these libraries seem redundant to existing open source libraries. Are they better somehow?

Generally they're only better in that they're easier to integrate,
easier to use, and easier to release (single file; good API; no
attribution requirement). They may be less featureful, slower,
and/or use more memory. If you're already using an equivalent
library, there's probably no good reason to switch.

#### Can I link directly to the table of stb libraries?

You can use [this URL](https://github.com/nothings/stb#stb_libs) to link directly to that list.

#### Why do you list "lines of code"? It's a terrible metric.

Just to give you some idea of the internal complexity of the library,
to help you manage your expectations, or to let you know what you're
getting into. While not all the libraries are written in the same
style, they're certainly similar styles, and so comparisons between
the libraries are probably still meaningful.

Note though that the lines do include both the implementation, the
part that corresponds to a header file, and the documentation.

#### Why single-file headers?

Windows doesn't have standard directories where libraries
live. That makes deploying libraries in Windows a lot more
painful than open source developers on Unix-derivates generally
realize. (It also makes library dependencies a lot worse in Windows.)

There's also a common problem in Windows where a library was built
against a different version of the runtime library, which causes
link conflicts and confusion. Shipping the libs as headers means
you normally just compile them straight into your project without
making libraries, thus sidestepping that problem.

Making them a single file makes it very easy to just
drop them into a project that needs them. (Of course you can
still put them in a proper shared library tree if you want.)

Why not two files, one a header and one an implementation?
The difference between 10 files and 9 files is not a big deal,
but the difference between 2 files and 1 file is a big deal.
You don't need to zip or tar the files up, you don't have to
remember to attach *two* files, etc.

#### Why "stb"? Is this something to do with Set-Top Boxes?

No, they are just the initials for my name, Sean T. Barrett.
This was not chosen out of egomania, but as a moderately sane
way of namespacing the filenames and source function names.

#### Will you add more image types to stb_image.h?

No. As stb_image use has grown, it has become more important
for us to focus on security of the codebase. Adding new image
formats increases the amount of code we need to secure, so it
is no longer worth adding new formats.

#### Do you have any advice on how to create my own single-file library?

Yes. https://github.com/nothings/stb/blob/master/docs/stb_howto.txt

#### Why public domain?

I prefer it over GPL, LGPL, BSD, zlib, etc. for many reasons.
Some of them are listed here:
https://github.com/nothings/stb/blob/master/docs/why_public_domain.md

#### Why C?

Primarily, because I use C, not C++. But it does also make it easier
for other people to use them from other languages.

#### Why not C99? stdint.h, declare-anywhere, etc.

I still use MSVC 6 (1998) as my IDE because it has better human factors
for me than later versions of MSVC.
