# Other single-file public-domain/open source libraries with minimal dependencies

In addition to all of [my libraries](https://github.com/nothings/stb), there are other, similar libraries.

People have told me about quite a few of these. However, I haven't used most of these libraries
and can't comment on their quality. (If you use them and aren't their author, feel
free to tell me about their quality.) _Newest additions are in italics._

- **images** [jo_gif.cpp](http://www.jonolick.com/home/gif-writer): animated GIF writer (public domain)
- **images** [gif.h](https://github.com/ginsweater/gif-h): animated GIF writer (public domain)
- **images** [tiny_jpeg.h](https://github.com/serge-rgb/TinyJPEG/blob/master/tiny_jpeg.h): JPEG encoder (public domain)
- **images** [miniexr](https://github.com/aras-p/miniexr): OpenEXR writer (public domain)
- **geometry** [nv_voronoi.h](http://www.icculus.org/~mordred/nvlib/): find voronoi regions on lattice w/ integer inputs (public domain)
- **geometry** [sobol.h](https://github.com/Marc-B-Reynolds/Stand-alone-junk/blob/master/src/SFH/Sobol.h): sobol & stratified sampling sequences (public domain)
- **network** [zed_net](https://github.com/ZedZull/zed_net): cross-platform socket wrapper (public domain)
- **strings**; **files & filenames** [DG_misc.h](https://github.com/DanielGibson/Snippets/): Daniel Gibson's stb.h-esque cross-platform helpers: path/file, strings (public domain)
- **strings** [utf8](https://github.com/sheredom/utf8.h): utf8 string library (public domain)
- **strings** [strpool.h](https://github.com/mattiasgustavsson/libs): string interning (public domain/MIT)
- **misc** [MakeID.h](http://www.humus.name/3D/MakeID.h): allocate/deallocate small integer IDs efficiently (public domain)
- **misc** [gb_string.h](https://github.com/gingerBill/gb): dynamic strings for C (public domain)
- **misc** [loguru](https://github.com/emilk/loguru): flexible logging for C++ (public domain)
- **hardware** [EasyTab](https://github.com/ApoorvaJ/EasyTab): multi-platform tablet input (public domain)

Not public domain:

- **images** [tinyexr](https://github.com/syoyo/tinyexr): EXR image read/write (BSD license)  *uses miniz internally*
- **images** [lodepng](http://lodev.org/lodepng/): PNG encoder/decoder (zlib license)
- **images** [nanoSVG](https://github.com/memononen/nanosvg): 1-file SVG parser; 1-file SVG rasterizer (zlib license)
- **3D** [tinyobjloader](https://github.com/syoyo/tinyobjloader): wavefront OBJ file loader (BSD license)
- **2D** [blendish](https://bitbucket.org/duangle/oui-blendish/src): blender-style widget rendering (MIT license)
- **math** [mm_vec.h](https://github.com/vurtun/mmx): vector math (BSD license)
- **geometry** [sdf.h](https://github.com/memononen/SDF): compute signed-distance field from antialiased image (MIT license)
- **geometry** [nanoflann](https://github.com/jlblancoc/nanoflann): build KD trees for point clouds (BSD license)
- **geometry** [jc_voronoi](https://github.com/JCash/voronoi): find voronoi regions on float/double data (MIT license)
- **geometry** [par_msquares](https://github.com/prideout/par): convert (binarized) image to triangles (MIT license)
- **geometry** [tk_objfile](https://github.com/joeld42/tk_objfile): OBJ file loader (MIT license)
- _**geometry** [par_shapes](http://github.prideout.net/shapes/): generate various 3d geometric shapes (MIT license)_
- **network** [mm_web.h](https://github.com/vurtun/mmx): lightweight webserver, fork of webby (BSD license)
- **network** [par_easycurl.h](https://github.com/prideout/par): curl wrapper (MIT license)
- **audio** [aw_ima.h](https://github.com/afterwise/aw-ima/blob/master/aw-ima.h): IMA-ADPCM audio decoder (MIT license)
- **multithreading** [mm_sched.h](https://github.com/vurtun/mmx): cross-platform multithreaded task scheduler (zlib license)
- **parsing** [SLRE](https://github.com/cesanta/slre): regular expression matcher (GPL v2)
- **parsing** [PicoJSON](https://github.com/kazuho/picojson): JSON parse/serializer for C++ (BSD license)
- **parsing** [mm_json.h](https://github.com/vurtun/mmx): JSON parser (zlib license)
- **parsing** [mm_lexer.h](https://github.com/vurtun/mmx): C-esque language lexer (zlib license)
- **tests** [utest](https://github.com/evolutional/utest): unit testing (MIT license)
- **tests** [catch](https://github.com/philsquared/Catch): unit testing (Boost license)
- **tests** [SPUT](http://www.lingua-systems.com/unit-testing/): unit testing (BSD license)
- **misc** [lualite](https://github.com/janezz55/lualite/): generate lua bindings in C++ (MIT license)
- **misc** [tinyformat](https://github.com/c42f/tinyformat): C++ typesafe printf (Boost license)

There are some that have a source file and require a separate header file (which they may
not even supply). That's twice as many files, and we at nothings/stb cannot condone
this! But you might like them anyway:

- **images** [picopng.cpp](http://lodev.org/lodepng/picopng.cpp): tiny PNG loader (zlib license)
- **images** [jpeg-compressor](https://github.com/richgel999/jpeg-compressor): 2-file jpeg compress, 2-file jpeg decompress (public domain)
- **3D** [mikktspace](https://svn.blender.org/svnroot/bf-blender/trunk/blender/intern/mikktspace/): compute tangent space for normal mapping (zlib)
- **2D** [tigr](https://bitbucket.org/rmitton/tigr/src): quick-n-dirty window text/graphics for Windows (public domain)
- **2D** [noc_turtle](https://github.com/guillaumechereau/noc): procedural graphics generator (public domain)
- **geometry** [Tomas Akenine-Moller snippets](http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/): various 3D intersection calculations, not lib-ified (public domain)
- **geometry** [Clipper](http://www.angusj.com/delphi/clipper.php): line & polygon clipping & offsetting (Boost license)
- **geometry** [PolyPartition](https://github.com/ivanfratric/polypartition): polygon triangulation, partitioning (MIT license)
- **network** [yocto](https://github.com/tom-seddon/yhs): non-production-use http server (public domain)
- **network** [happyhttp](http://scumways.com/happyhttp/happyhttp.html): http client requests (zlib license)
- **network** [mongoose](https://github.com/cesanta/mongoose): http server (GPL v2)
- _**network** [LUrlParser](https://github.com/corporateshark/LUrlParser): lightweight URL & URI parser RFC 1738, RFC 3986 (MIT license)_
- **crypto** [TweetNaCl](http://tweetnacl.cr.yp.to/software.html): high-quality tiny cryptography library (public domain)
- **AI** [micropather](http://www.grinninglizard.com/MicroPather/): pathfinding with A* (zlib license)
- **compression** [miniz.c](https://github.com/richgel999/miniz): zlib compression,decompression, zip file, png writing (public domain)
- **compression** [lz4](https://github.com/Cyan4973/lz4): fast but larger LZ compression (BSD license)
- **compression** [fastlz](https://code.google.com/p/fastlz/source/browse/#svn%2Ftrunk): fast but larger LZ compression (MIT license)
- **compression** [pithy](https://github.com/johnezang/pithy): fast but larger LZ compression (BSD license)
- **profiling** [Remotery](https://github.com/Celtoys/Remotery): CPU/GPU profiler Win/Mac/Linux, using web browser for viewer (Apache 2.0 license)
- **profiling** [MicroProfile](https://bitbucket.org/jonasmeyer/microprofile): CPU (and GPU?) profiler, 1-3 header files (unlicense) *uses miniz internally*
- **parsing** [json.h](https://github.com/sheredom/json.h): JSON parser (public domain)
- **parsing** [jzon.h](https://github.com/Zguy/Jzon): JSON parser, C++ (MIT license)
- **strings** [dfa](http://bjoern.hoehrmann.de/utf-8/decoder/dfa/): fast utf8 decoder (MIT license)
- **data structures** [klib](http://attractivechaos.github.io/klib/): many 2-file libs: hash, sort, b-tree, etc (MIT license)
- **data structures** [uthash](https://github.com/troydhanson/uthash): several 1-header, 1-license-file libs: generic hash, list, etc (BSD license)
- **data structures** [PackedArray](https://github.com/gpakosz/PackedArray): memory-efficient array of elements with non-pow2 bitcount (WTFPL v2 license)
- **data structures**; **algorithms** [minilibs](https://github.com/ccxvii/minilibs): two-file regex, binary tree (public domain)
- **files & filenames** [whereami](https://github.com/gpakosz/whereami): get path/filename of executable or module (WTFPL v2 license)
- **misc** [dbgtools](https://github.com/wc-duck/dbgtools): cross-platform debug util libraries (zlib license)
- **misc** [stmr](https://github.com/wooorm/stmr.c): extract English word stems (MIT license)
- **misc** [levenshtein](https://github.com/wooorm/levenshtein.c): compute edit distance between two strings (MIT license)
- **tests** [pempek_assert.cpp](https://github.com/gpakosz/Assert/tree/master/src): flexible assertions in C++ (WTFPL v2 license)

There is also these XML libraries, but if you're using XML, shame on you:

- **parsing** [tinyxml2](https://github.com/leethomason/tinyxml2): XML (zlib license)
- **parsing** [pugixml](http://pugixml.org/): XML (MIT license)

There are some libraries that are just _so_ awesome that even though they use more
than two files we're going to give them special dispensation to appear in their own
little list here. If you're a crazy purist, be warned, but otherwise, enjoy!

- **user interface** [dear imgui](https://github.com/ocornut/imgui): an immediate-mode GUI ("imgui") named "ImGui" (MIT license)

Also you might be interested in other related, but different lists:

- [clib](https://github.com/clibs/clib/wiki/Packages): list of (mostly) small single C functions (licenses not listed)

## *List FAQ*

### Can I link directly to this list?

Yes, you can just use this page. If you want a shorter, more readable link, you can use [this URL](https://github.com/nothings/stb#other_libs) to link to the FAQ question that links to this page.

### Why isn't library XXX which is made of 3 or more files on this list?

I draw the line arbitrarily at 2 files at most. (Note that some libraries that appear to
be two files require a separate LICENSE file, which made me leave them out). Some of these
libraries are still easy to drop into your project and build, so you might still be ok with them.
But since people come to stb for single-file public domain libraries, I feel that starts
to get too far from what we do here.

### Why isn't library XXX which is at most two files and has minimal other dependencies on this list?

Probably because I don't know about it, feel free to submit a pull request, issue, email, or tweet it at
me (it can be your own library or somebody else's). But I might not include it for various
other reasons, including subtleties of what is 'minimal other dependencies' and subtleties
about what is 'lightweight'.

### Why isn't SQLite's amalgamated build on this list?

Come on.

