
FAQ
---

#### What's the license?

These libraries are in the public domain (or the equivalent where that is not
possible). You can do anything you want with them. You have no legal obligation
to do anything else, although I appreciate attribution.

#### Are there other single-file public-domain libraries out there? <a name="other_libs"></a>

Yes. I'll even tell you about some. However, I haven't used most of these libraries
and can't comment on their quality. (If you use them and aren't their author, feel
free to tell me about their quality.)

- [jo_gif.cpp](http://www.jonolick.com/home/gif-writer): tiny GIF writer (public domain)
- [gif.h](https://github.com/ginsweater/gif-h): animated GIF writer (public domain)
- [tiny_jpeg.h](https://github.com/serge-rgb/TinyJPEG/blob/master/tiny_jpeg.h): JPEG encoder (public domain)
- [lodepng](http://lodev.org/lodepng/): PNG encoder/decoder (zlib license)
- [nanoSVG](https://github.com/memononen/nanosvg): 1-file SVG parser; 1-file SVG rasterizer (zlib license)
- [tinyobjloader](https://github.com/syoyo/tinyobjloader): wavefront OBJ file loader (BSD license)
- [sdf.h](https://github.com/memononen/SDF): compute signed-distance field from antialiased image (MIT license)
- [nv_voronoi.h](http://www.icculus.org/~mordred/nvlib/): find voronoi regions on lattice w/ integer inputs (public domain)
- [nanoflann](https://github.com/jlblancoc/nanoflann): build KD trees for point clouds (BSD license)
- [SLRE](https://github.com/cesanta/slre): regular expression matcher (GPL v2)
- [DG_misc.h](https://github.com/DanielGibson/Snippets/): Daniel Gibson's stb.h-esque cross-platform helpers: path/file, strings (public domain)
- [MakeID.h](http://www.humus.name/3D/MakeID.h): allocate/deallocate small integer IDs efficiently (public domain)
- [utest](https://github.com/evolutional/utest): unit testing (MIT license)
- [catch](https://github.com/philsquared/Catch): unit testing (Boost license)
- [zed_net](https://github.com/ZedZull/zed_net): cross-platform socket wrapper (public domain)

There are some that have a source file and require a separate header file (which they may
not even supply). That's twice as many files, and we at nothings/stb cannot condone
this! But you might like them anyway:

- [pempek_assert.cpp](https://github.com/gpakosz/Assert/tree/master/src): C++ flexible assertions in C++ (WTFPL v2 license)
- [whereami](https://github.com/gpakosz/whereami): get path/filename of executable (WTFPL v2 license)
- [picopng.cpp](http://lodev.org/lodepng/picopng.cpp): tiny PNG loader (zlib license)
- [jpeg-compressor](https://github.com/richgel999/jpeg-compressor): 2-file jpeg compress, 2-file jpeg decompress (public domain)
- [lz4](https://github.com/Cyan4973/lz4): fast but larger LZ compression (BSD license)
- [fastlz](https://code.google.com/p/fastlz/source/browse/#svn%2Ftrunk): fast but larger LZ compression (MIT license)
- [tinyexr](https://github.com/syoyo/tinyexr): EXR image read/write, uses miniz internally (BSD license)
- [miniz.c](https://github.com/richgel999/miniz): zlib compression,decompression, zip file, png writing (public domain)
- [Remotery](https://github.com/Celtoys/Remotery): CPU/GPU profiler Win/Mac/Linux, using web browser for viewer (Apache 2.0 license)
- [MicroProfile](https://bitbucket.org/jonasmeyer/microprofile): CPU (and GPU?) profiler, 1-3 header files (unlicense)
- [Clipper](http://www.angusj.com/delphi/clipper.php): line & polygon clipping & offsetting (Boost license)
- [json.h](https://github.com/sheredom/json.h): JSON parser (public domain)
- [Zange](https://github.com/vurtun/zange/blob/master/json.c): another JSON parser (MIT license)
- [yocto](https://github.com/tom-seddon/yhs): non-production-use http server (public domain)
- [happyhttp](http://scumways.com/happyhttp/happyhttp.html): http client requests (zlib license)
- [tigr](https://bitbucket.org/rmitton/tigr/src): quick-n-dirty window text/graphics for Windows (public domain)

There is also this XML library, but if you're using XML, shame on you:

- [tinyxml2](https://github.com/leethomason/tinyxml2): XML (zlib license)

#### If I wrap an stb library in a new library, does the new library have to be public domain?

No.

#### A lot of these libraries seem redundant to existing open source libraries. Are they better somehow?

Generally they're only better in that they're easier to integrate,
easier to use, and easier to release (single file; good API; no
attribution requirement). They may be less featureful, slower,
and/or use more memory. If you're already using an equivalent
library, there's probably no good reason to switch.

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

#### Will you add more image types to stb_image.c?

If people submit them, I generally add them, but the goal of stb_image
is less for applications like image viewer apps (which need to support
every type of image under the sun) and more for things like games which
can choose what images to use, so I may decline to add them if they're
too rare or if the size of implementation vs. apparent benefit is too low.

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



