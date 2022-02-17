[33mcommit c529ebed3e81ca50bed77392fbc4ad097033ee97[m[33m ([m[1;36mHEAD -> [m[1;32mmaster[m[33m, [m[1;31morigin/master[m[33m, [m[1;31morigin/HEAD[m[33m)[m
Author: Weston McNamara <westonfmcnamara@gmail.com>
Date:   Thu Feb 17 10:01:17 2022 -0500

    added fallthrough macro to suppress warning

[33mcommit af1a5bc352164740c1cc1354942b1c6b72eacb8a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 10 00:48:29 2021 -0700

    Update bug_report.md

[33mcommit 37e21f17b2269fdc49cb0de83064d3af5f2962f6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 10 00:47:35 2021 -0700

    Update bug_report.md

[33mcommit b9e1d86edc4e526e494855bcb46d02f3269d58aa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 10 00:43:51 2021 -0700

    Create config.yml

[33mcommit b1826c9894c048e18cce45a289ee1db3fde7f40b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 10 00:41:32 2021 -0700

    Update issue templates

[33mcommit c0c982601f40183e74d84a61237e968dca08380e[m[33m ([m[1;31morigin/dev[m[33m)[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sat Aug 28 04:52:41 2021 -0700

    stb_truetype 1.26: fix rendering glitches

[33mcommit ef861421e2bc467e01eafc3d13864d931cf5014d[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sat Aug 28 03:20:04 2021 -0700

    stb.h: stb_splitpath correctly handles relative paths with explicit drive specifiers

[33mcommit 59e7dec3e8bb0a8d4050d03c2dc32cf71ffa87c6[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Aug 13 13:57:23 2021 -0700

    delete file covered by patents

[33mcommit 08e89524f693651819c4de2a29685b36301a08b1[m
Merge: be90195 5ba0baa
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Aug 13 13:57:07 2021 -0700

    Merge branch 'dev' of https://github.com/nothings/stb into dev

[33mcommit 5ba0baaa269b3fd681828e0e3b3ac0f1472eaf40[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 25 20:24:10 2021 -0700

    stb_image: Reject fractional JPEG component subsampling ratios
    
    The component resamplers are not written to support this and I've
    never seen it happen in a real (non-crafted) JPEG file so I'm
    fine rejecting this as outright corrupt.
    
    Fixes issue #1178.

[33mcommit c404b789ca01a00cd244240484f7eccdd639ef06[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 23:47:20 2021 -0700

    stb_truetype: fix sample code drawing characters upside-down

[33mcommit 1401f2257d1c8b6417b442bdf59e7c185be7f9d9[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 15:58:08 2021 -0700

    clean up project file

[33mcommit 7c65d5621f00c3304a3d4dcc8c036b37cf8fec9b[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 15:57:39 2021 -0700

    fix compiling with NO_HDR NO_LINEAR

[33mcommit be901954b254b020b0b99d0e7ff95c2cbdb08df0[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 23:47:20 2021 -0700

    stb_truetype: fix sample code drawing characters upside-down

[33mcommit 7de8f7999b564d588ef6be12b1a763fdacd5a66e[m
Merge: 4adb57a 3a11740
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 23:47:13 2021 -0700

    Merge branch 'master' into dev

[33mcommit 3a1174060a7dd4eb652d4e6854bc4cd98c159200[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 21:27:12 2021 -0700

    opengl stb_truetype demo app

[33mcommit 4adb57af424cbdd1a27937995a11509cc65e0217[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 15:58:08 2021 -0700

    clean up project file

[33mcommit cd6b6f70ec2be6ee80e142c6b7388d0d00d41b2f[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 15:57:39 2021 -0700

    fix compiling with NO_HDR NO_LINEAR

[33mcommit a0a939058c579ddefd4c5671b046f29d12aeae01[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 01:50:47 2021 -0700

    update README

[33mcommit 5a0bb8b1c1b1ca3f4e2485f4114c1c8ea021b781[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 01:39:27 2021 -0700

    update readme

[33mcommit c4ef8e1fdcc67d5c60501760e0068b9f83f53ca7[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 12 01:23:29 2021 -0700

    fix version date

[33mcommit 7023e273f1513b68b8d4086077c6faca555d50df[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sun Jul 11 18:06:46 2021 -0700

    fix stb_dxt version

[33mcommit 5324597dcb80510f71db05246b3932cb9876b9e4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 11 17:58:19 2021 -0700

    README: update stb_dxt version for fix

[33mcommit 3cfb892cf3144eb0bd4d85f84695193fb6f007c0[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 11 17:56:55 2021 -0700

    stb_dxt: Fix bug in table generator
    
    Forgot to put the *100 back, oops.

[33mcommit 1ee679ca2ef753a528db5ba6801e1067b40481b8[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sun Jul 11 17:07:54 2021 -0700

    update version numbers

[33mcommit fd7807e92d8ba5740615362b453bab2d9ecbc8a4[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sun Jul 11 16:37:34 2021 -0700

    stb_c_lexer: allow including stb_c_lexer.h without defining overrides (all tokens are always defined; token values have changed)

[33mcommit 0be82e4814eaad3b9af6261ee1355608a0d04b0e[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sun Jul 11 16:26:02 2021 -0700

    stb_truetype: fix incorrect antialiasing computation in v2 rasterizer, and handle certain cases where math blew up

[33mcommit e05ecc05ee556773f67c51fbf8a52b2a63cb91d2[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Sun Jul 11 15:26:16 2021 -0700

    Fix compiling-as-C-pre-C99 issues

[33mcommit 38c15ee7cf8dfe0c166ddb74456ac4c8eccd032f[m
Merge: 818ac26 af4c673
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jul 11 13:28:24 2021 -0700

    Merge pull request #1165 from randy408/dev-fix
    
    Fix CIFuzz integration

[33mcommit af4c6731749c0b4a940d0055d254b5fd2f911062[m
Author: Randy <randy408@protonmail.com>
Date:   Sat Jul 10 15:51:11 2021 +0200

    change directory for seed corpus downloads

[33mcommit a0a8653a7d33a2d43966d46601b20af0bfe00cf6[m
Author: Randy <randy408@protonmail.com>
Date:   Sat Jul 10 15:29:39 2021 +0200

    attempt to fix issue with CIFuzz

[33mcommit 818ac26785a77cd011403a21eeedc5725abdd591[m
Author: ocornut <omarcornut@gmail.com>
Date:   Fri Jul 9 13:17:06 2021 +0200

    stb_rect_pack: making functions cdecl for msvc qsort

[33mcommit c8e3d3086dd86e5abeb548e8b4f54ec82d627739[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 9 18:49:15 2021 -0700

    stb_truetype: Small tweaks to make PVS Studio happy
    
    No actual bugs as far as I can tell.
    
    Fixes issue #1162.

[33mcommit 5bf78b8f231cea48b6d7030aa86f910f6dd37d6b[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 9 05:37:56 2021 -0700

    stb_truetype: fix bad declaration

[33mcommit 99e13217cef36ff06fa29153df088d0b83e2d775[m
Merge: 4bb337d 2b667e4
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 9 05:37:19 2021 -0700

    Merge branch 'dev' of https://github.com/nothings/stb into dev

[33mcommit 4bb337ddf0a4122bc1547a17f13f1932e228c1ad[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 9 05:36:53 2021 -0700

    test including stb_c_lexer header independnet of implementation

[33mcommit 2b667e4d30e8fd04aebec170763a2c118f635652[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 8 00:32:38 2021 -0700

    stb_rect_pack: Several minor fixes
    
    1. Always use large rects mode to avoid definition of stbrp_coord
       in header file depending on implementation #defines
    2. Expose STBRP__MAXVAL to users
    3. Fix value of STBRP__MAXVAL for large rect mode (stbrp_coord
       is a 32-bit int, so needs to be <=0x7fffffff, 0xffffffff
       doesn't work)
    4. Add comment at the top about which #define to set to get the
       implementation.
    
    Fixes issue #1143, or rather, replaces that pull request.

[33mcommit 1e1efbdc75487a6c29d76314eb174a6a346a4d8e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 8 00:24:00 2021 -0700

    stb_image_write: Make globals extern "C" in C++
    
    Fixes issue #921

[33mcommit d2476c384527020cf145d359e8a2a5689e1c51cd[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 8 00:21:08 2021 -0700

    stb_sprintf: GCC compilation fix
    
    Fixes issue #1010.

[33mcommit 06b6009e3be9985a47829976c3c00711bb51d4f3[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 15:51:56 2021 -0700

    stb_sprintf: Fix unused variable warning with STB_SPRINTF_NOFLOAT
    
    Fixes issue #986.

[33mcommit 3be65f1c0c5e605bcc3d75a6466328ddb9e68945[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 15:43:47 2021 -0700

    stb_sprintf: Small simplification
    
    This was intentional but we might as well just set cs=0
    directly here.
    
    Fixes issue #997.

[33mcommit 013884b53b3e346c8d497ca65b438857ffefbad9[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 15:38:42 2021 -0700

    stb_sprintf: Fix string length calc
    
    Factor out string length computation into helper func, comment
    it a bit more, always use a limit to avoid 32b unsigned overflow,
    and avoid reading past the bounds of non-0-terminated strings given
    with specified precision.
    
    Fixes issue #966.

[33mcommit 2af2e692197267092f737db562817231feb3b5be[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 14:59:13 2021 -0700

    stb_ds: Fix addn when n=0
    
    In this case, the array pointer may still be 0 even after the
    maybegrow.
    
    Fixes issue #1015.

[33mcommit b14a80784c689979b75f6e8929a7d7b4b4a86678[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 14:35:46 2021 -0700

    stb_image_write: Support writing BMPs with alpha
    
    Fixes issue #1159.

[33mcommit 315e979f34a1f8479bfc82481fb60fd22965fd1d[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 04:10:52 2021 -0700

    stb_truetype: Add protoype for stbtt_FindSVGDoc
    
    Fixes issue #979.

[33mcommit 8af4d40950e38301d3ce8c6cda380aa28ba8c710[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 03:58:30 2021 -0700

    stb_c_lexer: Move token enum defn to header portion
    
    Required some tinkering, hope I didn't mess the logic up.
    
    This now requires the config section to be set for the header
    file, and different sites that include it should agree on what
    the values are. This is kind of iffy but hard to avoid.
    
    Fixes issue #647.

[33mcommit afc9c16bfd5be9ce81e0e0e1255b47d38218c773[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 03:43:15 2021 -0700

    stb_truetype: Change spelling of fallthrough comment
    
    To pacify GCC warnings at -Wimplicit-fallthrough=4. Why the
    all-caps version works and the others don't, I'm not sure; the
    GCC manual page lists regular expressions that GCC is checking for
    but does not say which regular expression syntax variant it's using,
    whether it's looking for a substring match or a full match for
    the comment, and what exactly the text being matched against is
    for a single-line comment. Sigh.
    
    Fixes issue #507.

[33mcommit 46c259ff903a4951f1acf0e129b9648a54eb8b75[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 03:32:04 2021 -0700

    stb_sprintf: PUBLICDEC on declarations, as intended
    
    The code was using PUBLICDEF on both declarations and
    definitions.
    
    Fixes issue #458.

[33mcommit 9fe3b4bb52ff671809d72afa7e5dead88d292cb1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 03:12:33 2021 -0700

    stb_truetype: GPOS handling formatting changes
    
    Was using 4-character spaces and otherwise formatted unlike the
    rest of the code, fix this. Also get rid of the outer switch in
    GetGlyphGPOSInfoAdvance with just one case; just use an if.
    No behavioral changes.

[33mcommit 1252a3e6415353bb8f82cc52fc392c4073634eca[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 02:58:28 2021 -0700

    stb_truetype: GPOS parsing fixes
    
    Glyphs not assigned a glyph class should default to class 0 as
    per the OpenType spec. Also, change the code to treat malformed
    data as an error to be handled, not an assert, and change the
    way the version checking works.
    
    Fixes the issue mentioned in PR #1035. Also, this part of the
    code is indented incorrectly; will fix that in a subsequent
    commit.

[33mcommit e59050549285deb717d8a2245586c0b8c2a3d38a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 02:45:41 2021 -0700

    stb_truetype: GCC warning fix
    
    GCC warns about a potentially uninitialized variable here. It's
    not (or at least I don't see how), but fix it anyway.

[33mcommit db6e91b7d867f33eb5e9c5012324e2702a1eeedd[m
Author: Andrew Kensler <andrew@eastfarthing.com>
Date:   Sat Jul 3 23:39:43 2021 -0700

    Store uncompressed if compression was worse
    
    If the data was uncompressible and this deflate implementation expanded
    by more than the overhead of simply storing it uncompressed, fall back
    to deflate's uncompressed storage mode.  This bounds the maximum deflated
    size at the original size plus an overhead of 6 fixed bytes with another
    5 bytes per 32767 byte block.
    
    Fixes issue #948.

[33mcommit 14c224c84e51af5b4932f2a410e66a06f20c8cf7[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 01:45:29 2021 -0700

    stb_image_resize: Remove ill-advised asserts.
    
    These mostly add very little and have caused problems for people,
    nor does it make sense to require this when the underlying
    computations are performed in floating-point arithmetic depending
    on ratios of user-passed in image dimensions.
    
    Arbitrary absolute epsilons here would just be garbage; we could
    try and compute desired relative error bounds based on the
    determined scale values, but this still leaves the questions of
    what purpose this would even serve, which is unclear.
    
    Leave the filter kernel asserts as comment for documentation
    of what the behavior would be with exact math, but don't actually
    bother asserting here.
    
    Fixes issue #736.

[33mcommit e7f9f92c9d466fac3b42a2b4a3e6849df7bea51c[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 01:33:35 2021 -0700

    stb_divide: Update changelog

[33mcommit ab69a04d0a222eac2c08e79c3f3236de23e60355[m
Merge: c38ec91 fc5b791
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 01:30:58 2021 -0700

    Merge branch 'dev' of github.com:nothings/stb into dev

[33mcommit c38ec91d229cbe56167f8af865c05b3d92db705f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Jul 7 01:27:15 2021 -0700

    stb_divide: Fix integer overflow issues
    
    We've established the signs of values before so we can carefully
    jiggle the expressions to be guaranteed overflow-free; the tests
    for <0 here were meant to check if the value was "still negative",
    i.e. if the sum did not underflow below INT_MIN, and we can
    rewrite that using algebra to be overflow-free.
    
    We need an extra case in the Euclidean dvision for
    INT_MIN / INT_MIN which is a bit annoying but trivial; finally,
    for two's complement platforms, note that abs(x) = (x > 0) ? x : -x
    does not work (since for x=INT_MIN, -x still gives INT_MIN),
    but the equivalent formulation for _negative_ absolute value
    (x < 0) ? x : -x is always in range and overflow-free, so
    rewrite the relevant expressions using that negative absolute
    value instead.
    
    Fixes issue #741.

[33mcommit fc5b791228c85cae0a4652254b78e35846504fe1[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 01:21:37 2021 -0700

    stb_truetype: fix SDF handling of multiple move_to commands in a row

[33mcommit ca0e6d06d8ae055823a5b11fe64a0b05cb6ae3e3[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 00:57:43 2021 -0700

    stb_c_lexer: don't define default macro definitions on non-implementation includes

[33mcommit 84e7a4ae24fdea454c29ae629abf17d41bc4d697[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 00:43:40 2021 -0700

    stb_c_lexer: fix NUL eof test so it compiles

[33mcommit 08e4b186504bf5ffd869de886b966a361dd97217[m
Merge: a32aeef dcb1116
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 00:39:10 2021 -0700

    Merge branch 'dev' of https://github.com/nothings/stb into dev

[33mcommit a32aeefd6bc270231b0000573699dabc05321c5a[m
Merge: 95372dc 2d82cd1
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 00:34:43 2021 -0700

    Merge branch 'patch-1' of https://github.com/t-mw/stb into dev

[33mcommit 95372dc4f881900e51284f85c63312d75aee8f17[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Wed Jul 7 00:29:19 2021 -0700

    stb.h: fix bug in stb_readdir caused by change to stb_strncpy

[33mcommit dcb1116f1351bc8edad059d9ca432e8f322ba922[m
Author: Randy <randy408@protonmail.com>
Date:   Thu Nov 26 02:18:13 2020 +0100

    ossfuzz: improve code coverage
    
    fix .gif pattern matching
    add netpbm test images derived from the public domain pngsuite
    added more image types (downloaded in Dockerfile)

[33mcommit b77192742d5ae5746131f379da8157443128be6d[m
Author: Randy <randy408@protonmail.com>
Date:   Wed Nov 25 14:04:52 2020 +0100

    oss-fuzz: integrate with CIFuzz

[33mcommit 9f985460226d7939d7fd71f81b5e38dda4b06651[m
Author: Devendranath Thadi <devendranath.thadi3@gmail.com>
Date:   Wed Nov 25 06:48:14 2020 +0000

    Travis-ci: added support for ppc64le

[33mcommit 6ca560c9afba1bb850e07683988583a045c8dc78[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 21:40:31 2021 -0700

    stb_image: Update documentation for de-iPhone flag
    
    It's default off, not default on.
    
    Fixes issue #651.

[33mcommit 15d2dc5c5159e0e48b06287d123961256ab67c27[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 21:25:41 2021 -0700

    stb_tilemap_editor: Update contributors

[33mcommit 77eedd4fcfb6d25eb8fd2f306384fdaf733103ad[m
Author: Werner Stoop <wstoop@gmail.com>
Date:   Fri Apr 9 20:03:01 2021 +0200

    stb_tilemap_editor: Several fixes.
    
    Re-added calls to `stbte__hittest()`, fixed some compiler errors.
    Also fixed some GCC warnings about unused variables when
    STBTE__COLORPICKER and STBTE_ALLOW_LINK is not defined.

[33mcommit 21bfcbbc3dfb3ed8a9c8f86d68de9dbb93eb5768[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 21:07:34 2021 -0700

    stb_tilemap_editor: Update version, credits

[33mcommit b18c989dc2c7c2d3852b819271a848d8159dc749[m
Author: Rob Loach <robloach@gmail.com>
Date:   Fri Apr 16 04:21:42 2021 -0400

    stb_tilemap_editor: Fix variable usage

[33mcommit 7e10880f53572ad2c1a949a9311f813a41bedbdd[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:47:30 2021 -0700

    stb_image: Update credits

[33mcommit 2c8cd33e2eb331f94c27c0cbe79694216f434339[m
Author: Vladimír Vondruš <mosra@centrum.cz>
Date:   Mon Apr 6 18:06:34 2020 +0200

    stb_image: make unpremultiply and de-iPhone flags thread_local.
    
    Follows the change done for vertical flipping in
    eb48fbdcede98f93dab3a5e42ce5b0072b739cf1 for these two options as well.

[33mcommit b691fc430594cbe3a99b32e53bf8a20decc89d97[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:39:35 2021 -0700

    stb_truetype: Remove dead assignments
    
    Confirmed from the OpenType spec that there's nothing missing
    here. (These were just annotations listing the total sizes of
    the tables, but this is not used for anything here.)
    
    Fixes issue #704.

[33mcommit 44f046af0c6f1d79ef6f189d69ac670bbfba4ac4[m
Author: ocornut <omarcornut@gmail.com>
Date:   Mon Jul 5 17:22:24 2021 +0200

    stb_textedit: Fix paste failure handling breaking undo stack
    
    Could lead to freezes.
    
    Fixes issue #734.

[33mcommit eb677dda6e6a495c903cd5428ec7ebc840674f49[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:25:16 2021 -0700

    stb_textedit: Update credit, version history

[33mcommit 85bc8060be3f517477f2e785c31851c6214376f2[m
Author: Louis Schnellbach <xipiryon@gmail.com>
Date:   Thu Nov 19 15:59:51 2020 +0100

    Support for Page Up/Down
    (changes from ocornut/imgui/commit/ec945f44)

[33mcommit 76a0a00874a5075bf590d1fd2f40de1836aea567[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:19:51 2021 -0700

    stb.h: _MSC_VER in readdir_raw -> _WIN32
    
    For MinGW.

[33mcommit e817b4a998abdd7dfdacab5d76384b310f54f4f0[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:17:12 2021 -0700

    stb_ds: Fix typos in docs.

[33mcommit ba5cc43d33fd06875c254d46a301ec188aa441a7[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:10:22 2021 -0700

    stb_truetype: Fix stbtt__solve_cubic comment

[33mcommit a5d989c358a47e1f0245e11040904a9d7fbf9786[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Jul 6 20:07:12 2021 -0700

    stb_truetype: Tabs->spaces
    
    Whitespace only.

[33mcommit 1e82fd4a4ebe9ccc70dd86776a47a24ff02769fd[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 22:17:57 2021 -0700

    stb_image: BMP v4/v5 header parsing fixes
    
    As per MS's own docs, should ignore the r/g/b bitmasks in the
    header unless BI_BITFIELDS compression is selected. Factor out
    setting the default masks since that now exists in two branches.
    
    Add some more checking for unsupported compression formats and
    illegal bpp/compression combinations while I'm at it.
    
    Fixes issue #783.

[33mcommit 17bc84e15dfb7c5c7ebcc5246e929678478b15a4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 21:47:13 2021 -0700

    stb_image: stbi__bmp_info only rewind stream on error
    
    To be consistent with the other info functions.
    
    Fixes issue #892.

[33mcommit ab18d9b250494249a433068cc3583129d809b322[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 21:42:44 2021 -0700

    stb_image: Fix two bugs found via VC++ /analyze
    
    Also fixes issue #366.

[33mcommit e5fd7f6ce0a187bfdded1d6c1123152b7995dd39[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 21:09:20 2021 -0700

    stb: Remove stua entirely
    
    As per issue 634, Stua "will be deleted from stb.h" soonish. That
    was 3 years ago, which should be plenty of warning, and the
    language has been de-facto orphaned and undocumented for a
    good while longer than that.
    
    Fixes issue #634.

[33mcommit 70136cd5f1f0f40fc5df529689797f67c3a79c07[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 20:54:18 2021 -0700

    stb_vorbis: Change imdct_step3_inner_s_loop_ld654
    
    Released Clang 12 generates bad code for the original loop in here.
    While this is a compiler bug plain and simple, we still have to deal
    with it.
    
    This is related to the SLP vectorizer, and in particular the two
    reverse subtracts in the butterflies for the second half to avoid
    unary negates.
    
    Use the more regular dataflow that has the unary negates in it
    (we can at least fold one of them into a constant, namely for A2)
    and introduce a few temporaries that also make alias analysis (and
    possible block-level vectorization) a whole let easier while I'm at
    it.
    
    This fixes the codegen issues on Clang 12, which now produces a
    working decoder, and I expect the single unary negate that we
    actually gain per iteration of this loop is not a significant
    perf concern. (There are bigger fish to fry here regardless.)
    
    Fixes issue #1152.

[33mcommit 0d47d17002a532fa6dc118b4c95c95e557ac7ef3[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 19:26:31 2021 -0700

    stb_vorbis: Set error on open_memory with NULL data
    
    "Unexpected EOF" seems like the closest match from the error
    codes we have.
    
    Fixes issue #1123.

[33mcommit 0def11ae179ea2ef7216ac1c4e0d42ee9e019892[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 16:35:45 2021 -0700

    stb_vorbis: Fix some unused variables.
    
    Fixes issue #817.

[33mcommit 39a06413859a8a3f9613145e69ae9494e34b6ff4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 16:25:33 2021 -0700

    stb_vorbis: Clarify lifetime of pushdata *output buffers
    
    Fixes issue #929.

[33mcommit d5613c9511d23b7f0573cfe53b70fa9984d2dd29[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 16:19:46 2021 -0700

    stb_vorbis: A few UB fixes.
    
    Fixes issue #1018.

[33mcommit c817c9621ee306b0360cda5191e1054e1cb70daa[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 16:12:32 2021 -0700

    stb_vorbis: Add missing cast to uint to avoid UB
    
    Fixes issue #574.

[33mcommit e31da438e84db1d9285ba4933d43db1ec73a9a1b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 16:08:30 2021 -0700

    stb_vorbis: Fix unused parameter warnings.
    
    Some parameters do not get used, or only when certain config
    defines are set. Explicitly mark them as unused to make compilers
    happy.
    
    Fixes issue #396.

[33mcommit 904ecbfc37cfdd0aa86c4cf280ac3f05f52465e3[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 03:15:43 2021 -0700

    stb_vorbis: Remove spurious assignment to val
    
    This is definitely unnecessary, or at least I can't find anything
    in the Vorbis spec that would indicate anything special happening
    here.
    
    Fixes issue #816.

[33mcommit 5300d55277cbe1304f7c0d2eb180700e531e698a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 03:00:17 2021 -0700

    stb_vorbis: Include alloca.h on Sun targets
    
    See PR #1006.

[33mcommit 6fe053614c6973ae7edf92ef5f9c5bd901adfeeb[m
Author: morlad (iLeitgeb) <morlad@morlad.at>
Date:   Fri Mar 12 14:30:06 2021 +0000

    stb_vorbis: Fix memory leak in stb_vorbis
    
    When start_decoder() fails it may already have allocated memory
    for .vendor and/or .comment_list. Call vorbis_deinit() to free
    any allocated memory.
    
    Fixes issue #1051.

[33mcommit 2e3a6e82228164171b1a4d5b703c40c8d2d42b69[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 02:43:00 2021 -0700

    stb_vorbis: Move asserts around a bit
    
    Not an actual bug, it just looked wonky, but this code runs
    with code lengths that are verified to be in range (<32) by
    the length-reading code. Anyway.
    
    Fixes issue #901.

[33mcommit 3f671b870ff2f25b439ba36d8490c201c8b2c2bd[m
Author: Johannes Schultz <git42@sagagames.de>
Date:   Sat Jan 16 15:04:26 2021 +0100

    stb_vorbis: rename BUFFER_SIZE macro to STB_BUFFER_SIZE
    
    Fixes issue #1076.

[33mcommit a5e40739ac096711e6640babdf3038c8203f9978[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 01:33:53 2021 -0700

    stb_image_write: Fix define tested for sprintf_s
    
    Fixes issue 744.

[33mcommit ba3ba9b78c85abd4ed8ff5d432196f84160bd2b4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 00:23:38 2021 -0700

    stb_image_write: Disable HDR writer completely in NO_STDIO build
    
    Fixes issue #793, hopefully.

[33mcommit 76f55ac210f76592aa73b226c63dff022bd9060b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 4 00:16:14 2021 -0700

    stb_image_write: STBI_WINDOWS_UTF8 -> STBIW_WINDOWS_UTF8
    
    Fixes issue #925.

[33mcommit 81bcfa9043546dcb0ff5de710002470ac6bb342b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 23:55:14 2021 -0700

    stb_image_write: Remove tabs
    
    Whitespace-only change.

[33mcommit 82f9950cea9194f731c42ebbc0678c19c85972af[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 01:00:46 2021 -0700

    stb_image: Update credits

[33mcommit db864a1e309e3e785d1b58879cec83c66444fb2b[m
Author: Eugene Golushkov <e.golushkov@nospam-gmail.com>
Date:   Thu Oct 1 03:20:30 2020 +0300

    stb_image: fix building by MSVC for Windows 10 on ARM

[33mcommit 2506215e8ab4095d791e95658b26dd708bb13857[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 00:46:04 2021 -0700

    stb_image: Key Win32 UTF-8 support off _WIN32 not _MSC_VER
    
    So that it also works on MinGW.
    
    Fixes issue #729.

[33mcommit 991f1f6419aeba2b69c26aa26befe3ae93259a15[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 00:38:30 2021 -0700

    stb_image: Fix wrong buffer sizes passed to MultiByteToWideChar
    
    Fixes issue #772.

[33mcommit 56a7113cd0d0cb3c5be401436de10d7d5e96df6e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 23:06:44 2021 -0700

    stb_image: Reorder format test sequence
    
    Put the formats that start with a clear magic number first,
    the dodgy ones that don't have much of a distinctive header
    should be tested for later after we've ruled out the clearer
    ones.
    
    Fixes issue #787, hopefully. (Never got a clean repro.)

[33mcommit 618dbd01c81bad6aeb8eb3f37fc3281548678d3c[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:52:15 2021 -0700

    stb_image: Document image size limits
    
    Both the buffer size limits and the image dimension limits.
    
    Fixes issue #672.

[33mcommit 55a180671c8be196dabde96baaa7219fc20ecd1f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:31:41 2021 -0700

    readme: Add "how to use these libs" section
    
    Try to be a bit more explicit still.
    
    Fixes issue #903, or so I hope.

[33mcommit 4d3b93f5891794a6986c9808fbaaba7ee5a27a10[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:01:23 2021 -0700

    stb_image: Erorr in BMP should error, not assert.
    
    There was both the assert and the error check; should just be
    the error check.
    
    Fixes issue #881 (or rather, part of it).

[33mcommit 31ba943e3fdff7aff00b55629f747121f802e8c1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:57:25 2021 -0700

    stb_image: UB fix in stbi__get32le
    
    Need to do the second-part shift on uint32 not int.

[33mcommit d6ab7faec08d6964856472f4ada6adbc0e33ae92[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:38:44 2021 -0700

    stb_image: Update comment
    
    As per recent patches, we do support 16-bit PNMs.

[33mcommit bb0931744529c218bfa50e9b367c811a31251b75[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:09:11 2021 -0700

    stb_image: Avoid left-shifts of signed values
    
    It's implementation-specified behavior. Writing this code and then
    relying on compiler strength reduction to turn it back into shifts
    feels extremely silly but it is what it is.
    
    Fixes issue #1097.

[33mcommit 43b32c7babcec25bf7c544220e55bc03b4fd37dc[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 20:59:22 2021 -0700

    stb_image: Avoid shift of signed values in extend_receive
    
    Use an equivalent formulation that has sgn=0 or 1, not 0 or -1.
    This avoids right-shifting signed values, at least in this place.
    
    Fixes issue #1061.

[33mcommit 6d857933d5a88633bc170fc982d1c0ebaed9faf9[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:42:01 2021 -0700

    stb_image, stb_image_write: Fix compare sign warnings
    
    For the stb_image fix, also replace the magic 288 with a more
    descriptive name while I'm at it.
    
    Fixes #1100

[33mcommit 265b73bb0baf5aa24f12d733c652086063d54a5d[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:28:41 2021 -0700

    stb_image: Fix lrot definition, small extend_receive tweak
    
    Define lrot in a way that doesn't involve UB when n==0.
    Also, the previous patch ensures that n <= 15 for all callers
    of stbi__extend_receive, so can remove the (less restrictive)
    bounds check for 0 <= n < 17 (the bounds of stbi__bmask)
    entirely.
    
    Fixes issue #1065.

[33mcommit 86b7570cfba845e8209c6aec2d15e487bb1d8bb4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:10:49 2021 -0700

    stb_image: Fix bug on JPEGs with malformed DC deltas
    
    extend_receive implicitly requires n <= 15 (code length);
    the maximum that actually makes sense for 8-bit baseline JPEG is
    11, but 15 is the natural limit for us because the AC coding path
    stores the number of magnitude bits in a nibble.
    
    Check that DC delta bits are in range before attempting to call
    extend_receive.
    
    Fixes issue #1108.

[33mcommit 6ab6303f98f1ee33abe93b730dbbb5b875abbddd[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 17:50:34 2021 -0700

    stb_image: Check results of all mallocs.
    
    A few were missing. Make sure to always report ouf-of-memory
    errors.
    
    Fixes issue #1056.

[33mcommit 6199b717bcae770e9bae75696cef6a55f1e22ef1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:49:11 2021 -0700

    README: updated supported stb_image and stb_image_write formats

[33mcommit 8e8f7d9b690bad933333cc57d05871ab5ca35917[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:35:40 2021 -0700

    stb_image: Update credits, change log

[33mcommit 8c15cc9c79bf6f180d74808657046caf2ec0b445[m
Author: Simon Breuss <simon.breuss@gmail.com>
Date:   Tue May 18 23:51:25 2021 +0200

    Adds 16-bit support for pnm files.

[33mcommit c62af8565795222df95f548f31027ec0afb59bb1[m
Author: Jacko Dirks <jacko.dirks@gmail.com>
Date:   Sat Aug 15 17:19:02 2020 +0200

    stb_image.h: Suppress warnings about out_size, delay_size
    
    These two variables are unused on some targets, resulting in
    warnings. Add STBI_NOTUSED around them to suppress those
    warnings.

[33mcommit 448bb137e3717bf015b410ca25ed83cc48353050[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:18:51 2021 -0700

    stb_image: Better docs for stbi_info.
    
    Fixes #1026.

[33mcommit 1203eb554b7229cdcdc9fde3826f95a675a0287f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:11:25 2021 -0700

    stb_image: Fix issue #994.
    
    Accidentally introduced during a merge.

[33mcommit a49749a57d993e8d3bcc933f83266d7461435cfa[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:08:20 2021 -0700

    stb_textedit: Docs fix.
    
    Fixes issue #1041.

[33mcommit 0afc39f59a96113af1f911f67bdb057785965875[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:03:51 2021 -0700

    stb_truetype: Turn codepoint assert into error check
    
    Fixes the bug covered by PR #1066, but with a slightly different
    fix that's hopefully a bit clearer.

[33mcommit 067655993a3d0a631e03cd7692607308bd9e1865[m
Author: Doj <vitek03@gmail.com>
Date:   Wed Jan 27 20:39:02 2021 +0300

    stb_sprintf: fix stbsp_ddtoS64 macro
    
    Should use xh argument not ph (which is the name of the
    variable that it actually gets instantiated with the
    one time it is used).

[33mcommit 04007a071cf0ecdeab853186be98617920f324ad[m
Author: Jan CW Kroeze <jcwkroeze@pm.me>
Date:   Thu Mar 11 21:13:25 2021 +0100

    Note GL blend state for stb_truetype

[33mcommit 02578923d324babc429ad4115e2a22d997f84d74[m
Author: Rafael Sachetto <rsachetto@gmail.com>
Date:   Wed Jan 27 15:05:48 2021 -0300

    Fix compilation warnings in the s390x architeture. Fixes #1082.

[33mcommit 2de22bde0ae1de14ad2d7f098a4643e340b96dd8[m
Author: Valentin Lenhart <vlaube-de@users.noreply.github.com>
Date:   Wed Oct 28 14:13:17 2020 +0100

    stb_sprintf.h: stdlib.h is not needed
    
    va_arg() is in stdarg.h, which is already being included

[33mcommit dc2aa370c07219cd7f29d901d1168f2ff448c789[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 16:37:35 2021 -0700

    stb_dxt: Remove dithering support.
    
    Keep STB_DXT_DITHER so as not to break existing code that tries
    to enable it, but just leave it permanently off. I originally
    introduced it somewhat superstitiously because of the RGB565
    endpoint resolution but it never improved either perceptual quality
    or objective quality metrics, and the code is appreciably simpler
    without it.

[33mcommit ae3ed90b0c9548a69e2da4e3fa0f5e77fd00c4d0[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 16:24:09 2021 -0700

    stb_dxt: Better error calc for single-color table
    
    Don't truncate error as aggressively; easily done, but wanted
    to keep it separate from the previous change.

[33mcommit 98623b957763afb62fbe7b533762de7b3b23bbb2[m
Author: Alan Hickman <f.alan.hickman@gmail.com>
Date:   Sat Apr 24 13:08:03 2021 -0700

    stb_dxt: Initialize tables at compile time
    
    Also fix a "potentially uninitialized variable" warning.
    
    This is a modified version of Alan's original PR that keeps the
    table generator in the file (in case there's interest) and also
    replaces the expand[] tables with math, since it's trivial.
    
    Fixes issue #1117.

[33mcommit 696cb038a35f0196a6f28d7cdd06749a9536d38b[m
Author: Michael Aganier <michaelaganier@gmail.com>
Date:   Mon Jun 14 14:38:26 2021 -0400

    stb_sprintf: add attribute format to variadic functions
    
    This allows for compiler verification of the format string
    just like printf.

[33mcommit 6294c6cfa2144d52e78b1f545070bbb5a40cf504[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 15:29:17 2021 -0700

    Move stb.h to deprecated.
    
    It was never designed to be used by anyone but Sean and has
    numerous problems; new code should definitely not be using
    this.

[33mcommit 5c0cc31fb027993fabf9e9b448a31488e5dc47e4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 01:00:46 2021 -0700

    stb_image: Update credits

[33mcommit 69a7dd32a81fc290822c24a19efc4d36d7f2607c[m
Author: Eugene Golushkov <e.golushkov@nospam-gmail.com>
Date:   Thu Oct 1 03:20:30 2020 +0300

    stb_image: fix building by MSVC for Windows 10 on ARM

[33mcommit a0231a9e949e4407de63999f860a29f5d87e5181[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 00:46:04 2021 -0700

    stb_image: Key Win32 UTF-8 support off _WIN32 not _MSC_VER
    
    So that it also works on MinGW.
    
    Fixes issue #729.

[33mcommit e3a63f37934514ad08174f2194c3bf0e6b6e4720[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 3 00:38:30 2021 -0700

    stb_image: Fix wrong buffer sizes passed to MultiByteToWideChar
    
    Fixes issue #772.

[33mcommit 3870fb6a937d39c640ee5e8a12e36ac3efb94722[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 23:06:44 2021 -0700

    stb_image: Reorder format test sequence
    
    Put the formats that start with a clear magic number first,
    the dodgy ones that don't have much of a distinctive header
    should be tested for later after we've ruled out the clearer
    ones.
    
    Fixes issue #787, hopefully. (Never got a clean repro.)

[33mcommit e795306bbc866c51323e0172d3079c2abf5a7d24[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:52:15 2021 -0700

    stb_image: Document image size limits
    
    Both the buffer size limits and the image dimension limits.
    
    Fixes issue #672.

[33mcommit ba739e54edea02c807cf6bd93e1b19bad5bfa726[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:31:41 2021 -0700

    readme: Add "how to use these libs" section
    
    Try to be a bit more explicit still.
    
    Fixes issue #903, or so I hope.

[33mcommit d343a29fe6513e02cd4e1cba6a13f6f848515dcd[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 22:01:23 2021 -0700

    stb_image: Erorr in BMP should error, not assert.
    
    There was both the assert and the error check; should just be
    the error check.
    
    Fixes issue #881 (or rather, part of it).

[33mcommit 41e93836d957fe4eca5a59de466d5cbcdbf43713[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:57:25 2021 -0700

    stb_image: UB fix in stbi__get32le
    
    Need to do the second-part shift on uint32 not int.

[33mcommit cf00c67c5724b92343a1af3637a067aa31cc4531[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:38:44 2021 -0700

    stb_image: Update comment
    
    As per recent patches, we do support 16-bit PNMs.

[33mcommit 48632c175231eb0289f0cf3c83e8d2d68dec5bd9[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 21:09:11 2021 -0700

    stb_image: Avoid left-shifts of signed values
    
    It's implementation-specified behavior. Writing this code and then
    relying on compiler strength reduction to turn it back into shifts
    feels extremely silly but it is what it is.
    
    Fixes issue #1097.

[33mcommit 026013546cd889986b8395deae43b9793f4471f6[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 20:59:22 2021 -0700

    stb_image: Avoid shift of signed values in extend_receive
    
    Use an equivalent formulation that has sgn=0 or 1, not 0 or -1.
    This avoids right-shifting signed values, at least in this place.
    
    Fixes issue #1061.

[33mcommit 4d067e8b2bbf5eb5b3d0715e55f38634b9a1f36b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:42:01 2021 -0700

    stb_image, stb_image_write: Fix compare sign warnings
    
    For the stb_image fix, also replace the magic 288 with a more
    descriptive name while I'm at it.
    
    Fixes #1100

[33mcommit 1d7bf858778f816d233de8d1e4ecb81b5ca840ea[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:28:41 2021 -0700

    stb_image: Fix lrot definition, small extend_receive tweak
    
    Define lrot in a way that doesn't involve UB when n==0.
    Also, the previous patch ensures that n <= 15 for all callers
    of stbi__extend_receive, so can remove the (less restrictive)
    bounds check for 0 <= n < 17 (the bounds of stbi__bmask)
    entirely.
    
    Fixes issue #1065.

[33mcommit a3f2897b85760d1e98fedbe31fcf2ddf089c169e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 18:10:49 2021 -0700

    stb_image: Fix bug on JPEGs with malformed DC deltas
    
    extend_receive implicitly requires n <= 15 (code length);
    the maximum that actually makes sense for 8-bit baseline JPEG is
    11, but 15 is the natural limit for us because the AC coding path
    stores the number of magnitude bits in a nibble.
    
    Check that DC delta bits are in range before attempting to call
    extend_receive.
    
    Fixes issue #1108.

[33mcommit 50072f66589f52f51eb5b3f56b9272ea8ec1fdac[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 2 17:50:34 2021 -0700

    stb_image: Check results of all mallocs.
    
    A few were missing. Make sure to always report ouf-of-memory
    errors.
    
    Fixes issue #1056.

[33mcommit 8e51be04dc7dcee462e1f09e410faceab52cc6d2[m
Merge: 52ad6bd 80c8f6a
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 2 06:57:02 2021 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 52ad6bd4c920e008c6895901948fc95dd09488a1[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 2 06:56:34 2021 -0700

    update stb_vorbis version

[33mcommit 99e905e50bb79e791447fddba09057fe056e02c0[m
Merge: ea2f937 b7b2aaa
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jul 2 06:49:03 2021 -0700

    Merge branch 'pull_req' of https://github.com/anthofoxo/stb into working

[33mcommit 67b247ba4966081c1506e4d7ff2daf99cf0f8fe4[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:49:11 2021 -0700

    README: updated supported stb_image and stb_image_write formats

[33mcommit b4891baa6c307dda99846f465b4c0daf73c77771[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:35:40 2021 -0700

    stb_image: Update credits, change log

[33mcommit 8befa752b005da174b2429c1ffaafffe452b2997[m
Author: Simon Breuss <simon.breuss@gmail.com>
Date:   Tue May 18 23:51:25 2021 +0200

    Adds 16-bit support for pnm files.

[33mcommit 655b2b1f06438bbbaa4b4ae24dcb3a81195faa53[m
Author: Jacko Dirks <jacko.dirks@gmail.com>
Date:   Sat Aug 15 17:19:02 2020 +0200

    stb_image.h: Suppress warnings about out_size, delay_size
    
    These two variables are unused on some targets, resulting in
    warnings. Add STBI_NOTUSED around them to suppress those
    warnings.

[33mcommit 3a7dcdd2696ed7b85f892f951b0801e382b81778[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:18:51 2021 -0700

    stb_image: Better docs for stbi_info.
    
    Fixes #1026.

[33mcommit bc4e96b5a7beede4403980bc4d32d0a65ee1a53d[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:11:25 2021 -0700

    stb_image: Fix issue #994.
    
    Accidentally introduced during a merge.

[33mcommit 1cacac09edf46c6db7c2ebd58da8b3b44b3e1693[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:08:20 2021 -0700

    stb_textedit: Docs fix.
    
    Fixes issue #1041.

[33mcommit 309322ae4af2ed5f2614bae761e27ba9547930a1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 17:03:51 2021 -0700

    stb_truetype: Turn codepoint assert into error check
    
    Fixes the bug covered by PR #1066, but with a slightly different
    fix that's hopefully a bit clearer.

[33mcommit 0755e6a76fa3a32e6c9f46a396b437bacf09236c[m
Author: Doj <vitek03@gmail.com>
Date:   Wed Jan 27 20:39:02 2021 +0300

    stb_sprintf: fix stbsp_ddtoS64 macro
    
    Should use xh argument not ph (which is the name of the
    variable that it actually gets instantiated with the
    one time it is used).

[33mcommit 6931571861960f0393aebb3a688c13b5a81bd8b0[m
Author: Jan CW Kroeze <jcwkroeze@pm.me>
Date:   Thu Mar 11 21:13:25 2021 +0100

    Note GL blend state for stb_truetype

[33mcommit 0cc6060b77bf6312c730952644ddb46fa07dbffc[m
Author: Rafael Sachetto <rsachetto@gmail.com>
Date:   Wed Jan 27 15:05:48 2021 -0300

    Fix compilation warnings in the s390x architeture. Fixes #1082.

[33mcommit 073114d1114e0cdea1b4d9eefa7c4f774b90195c[m
Author: Valentin Lenhart <vlaube-de@users.noreply.github.com>
Date:   Wed Oct 28 14:13:17 2020 +0100

    stb_sprintf.h: stdlib.h is not needed
    
    va_arg() is in stdarg.h, which is already being included

[33mcommit 9a9c937f68dc60a022c9e8398cb65c5b3413789f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 16:37:35 2021 -0700

    stb_dxt: Remove dithering support.
    
    Keep STB_DXT_DITHER so as not to break existing code that tries
    to enable it, but just leave it permanently off. I originally
    introduced it somewhat superstitiously because of the RGB565
    endpoint resolution but it never improved either perceptual quality
    or objective quality metrics, and the code is appreciably simpler
    without it.

[33mcommit 425c4d8b3179a55a21c7c631db7bcdf27f6d459b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 16:24:09 2021 -0700

    stb_dxt: Better error calc for single-color table
    
    Don't truncate error as aggressively; easily done, but wanted
    to keep it separate from the previous change.

[33mcommit d84beeeff32fe401accd51f16ff9f669f516538a[m
Author: Alan Hickman <f.alan.hickman@gmail.com>
Date:   Sat Apr 24 13:08:03 2021 -0700

    stb_dxt: Initialize tables at compile time
    
    Also fix a "potentially uninitialized variable" warning.
    
    This is a modified version of Alan's original PR that keeps the
    table generator in the file (in case there's interest) and also
    replaces the expand[] tables with math, since it's trivial.
    
    Fixes issue #1117.

[33mcommit 40d7e478969c3732d5f07fca3bd943a2713255c4[m
Author: Michael Aganier <michaelaganier@gmail.com>
Date:   Mon Jun 14 14:38:26 2021 -0400

    stb_sprintf: add attribute format to variadic functions
    
    This allows for compiler verification of the format string
    just like printf.

[33mcommit 05e1efab3d81a9783679d27bdbcd30ea567e134e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Jul 1 15:29:17 2021 -0700

    Move stb.h to deprecated.
    
    It was never designed to be used by anyone but Sean and has
    numerous problems; new code should definitely not be using
    this.

[33mcommit 80c8f6af0304588b9d780a41015472013b705194[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 20 05:42:03 2021 -0700

    Update why_public_domain.md

[33mcommit ea2f937a01ce39795ab02b6c6e30173b4f1ed46c[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jun 4 11:42:16 2021 -0700

    increment stb_ds version, update README

[33mcommit 0188581ff01551d1631643d39e375852a915c58b[m
Merge: 6b647c0 579ace2
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jun 4 11:38:01 2021 -0700

    Merge branch 'stbds_custom_free_fix' of https://github.com/avennstrom/stb into foo

[33mcommit 6b647c02579f6c9efee2a0c5f7561c8dd64068be[m
Merge: 781609b e97a95c
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jun 4 11:18:16 2021 -0700

    Merge branch 'working'

[33mcommit 781609b7e9f79e2d9092afb2cdf6364a1f853b31[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Fri Jun 4 11:02:23 2021 -0700

    stb_ds: fix arrisn, shgetp_null

[33mcommit e97a95c0c1a5a134f60d43dd0ac4c3152a0a40ca[m
Author: Macoy Madson <macoy@macoy.me>
Date:   Mon May 31 19:53:09 2021 -0700

    Added Macoy Madson to contributors

[33mcommit 63e4ada98c0e7feff1eb00d55a4399599ae13d7b[m
Author: Macoy Madson <macoy@macoy.me>
Date:   Mon May 31 19:51:39 2021 -0700

    Fix temp_key being stale on key re-insert
    
    See issue #992 and pull request #993.

[33mcommit 579ace225f2fda79f98e72bc25dfe2b43434bbd0[m
Author: Andreas Vennström <6706447+avennstrom@users.noreply.github.com>
Date:   Tue May 11 22:56:27 2021 +0200

    fix indentation

[33mcommit fcd86e8f576dab10a25bdbe9cf813751f565769e[m
Author: Andreas Vennström <6706447+avennstrom@users.noreply.github.com>
Date:   Tue May 11 22:50:11 2021 +0200

    credits

[33mcommit 89762b9934a7c78b9b28784860638e904d02609e[m
Author: Andreas Vennström <6706447+avennstrom@users.noreply.github.com>
Date:   Tue May 11 22:44:08 2021 +0200

    Fix stb_ds custom allocator

[33mcommit b7b2aaa587977f19bc23c853371c72e4fdd8404c[m
Author: AnthoFoxo <anthofoxo@gmail.com>
Date:   Tue Apr 13 09:43:41 2021 -0400

    fixed vorbis comments causing outofmem

[33mcommit c9064e317699d2e495f36ba4f9ac037e88ee371a[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Thu Apr 1 10:31:43 2021 -0700

    stb_hexwave tweak comment

[33mcommit 997d3c421e9794dc540f11fdb41352124fddc25f[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Thu Apr 1 10:27:54 2021 -0700

    stb_hexwave: add full license text

[33mcommit 559d759c2c02f61993a71870e8ca2476379c62e5[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Thu Apr 1 01:53:09 2021 -0700

    stb_hexwave added, stretchy_buffer.h deprecated

[33mcommit 2d82cd1a2c0b8c8db1eac55d84f736a3aed9bb0e[m
Author: t-mw <t-mw@users.noreply.github.com>
Date:   Tue Mar 2 13:53:31 2021 +0100

    Rename arraddnoff -> arraddnindex
    
    Fixes #1011.
    As intended according to https://github.com/nothings/stb/pull/932#issuecomment-657524197.

[33mcommit 4882970b1c9be1c6b4d721fb18cec235093102e2[m
Author: AnthoFoxo <anthofoxo@gmail.com>
Date:   Mon Jan 25 20:01:42 2021 -0500

    vorbis comment list setup_malloc call is guarded

[33mcommit b038c11bd5039c5c1acae1a8231ffd412fa2e9b3[m
Author: AnthoFoxo <anthofoxo@gmail.com>
Date:   Wed Dec 16 18:25:11 2020 -0500

    updated contributor list

[33mcommit f0f253375415d500165ae59fe81d190f028bcd1c[m
Author: AnthoFoxo <anthofoxo@gmail.com>
Date:   Wed Dec 16 18:19:03 2020 -0500

    closes #1063; Fixed files with no comments emitting outofmemory errors

[33mcommit b42009b3b9d4ca35bc703f5310eedc74f584be58[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:46:06 2020 -0700

    fix readme linebreaks

[33mcommit e140649ccf40818781b7e408f6228a486f6d254b[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:40:31 2020 -0700

    remove trailign whitespace

[33mcommit 314d0a6f9af5af27e585336eecea333e95c5a2d8[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:36:03 2020 -0700

    update version numbers

[33mcommit 59f06c1a9764a85a8449b10b358b8ff197147aca[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:25:34 2020 -0700

    stb_ds: move temp_key added by PR into hash_table structure instead of main header struct

[33mcommit ef23148510370f7b1573cd78a47e4d52a326193d[m
Merge: 580fc1a 1e400e2
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:16:38 2020 -0700

    Merge branch 'master' of https://github.com/srdjanstipic/stb into working

[33mcommit 580fc1ab9b1f1ec89b27f1926b1ff99d59f289b1[m
Merge: db2acff c24de24
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:15:48 2020 -0700

    Merge branch 'stb_vorbis-fix-comment-read-oom' of https://github.com/akien-mga/stb into working

[33mcommit db2acff8b178b413bbc8294b7d1f62ac4dae30a7[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:12:21 2020 -0700

    stb_vorbis: fix bug in computing end of temp alloc buffer if it's not a multiple of 8

[33mcommit 3152efaa974e63653ff78d33f58ee682803f37ea[m
Merge: f308577 3b14b5a
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:08:36 2020 -0700

    Merge branch 'fuzzer_updates' of https://github.com/randy408/stb into working

[33mcommit f3085776a49ace1172ce7e98488b90b4cf49e998[m
Merge: 589a678 9e292f0
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:07:16 2020 -0700

    Merge branch 'patch-1' of https://github.com/coltongit/stb into working

[33mcommit 589a678b65dd35d4aae297ffd9623c034347057a[m
Merge: a9df364 ec89898
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:06:19 2020 -0700

    Merge branch 'master' of https://github.com/recp/stb into working

[33mcommit a9df364a7c32d53a7401b533500ed890108c16f7[m
Merge: bfaccab 2d0faa4
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 04:00:41 2020 -0700

    Merge branch 'fix_stb_vorbis_alignment' of https://github.com/RandomShaper/stb into working

[33mcommit bfaccab17a648b315543d366c63aee575a0756b7[m
Merge: 58b2e14 c29138b
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:53:53 2020 -0700

    Merge branch 'stb-image-fuzzing-fixes' of https://github.com/rcgordon/stb into working

[33mcommit 58b2e1490dd2b71e3274a83575019481993a6058[m
Merge: ce54bbc d8df5e9
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:33:18 2020 -0700

    Merge branch 'fix_alloca' of https://github.com/Clownacy/stb into working

[33mcommit ce54bbc454be6e9fc822ba75ae19baa45f26fdb7[m
Merge: 0ccb4f0 fdec118
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:29:47 2020 -0700

    Merge branch 'master' of https://github.com/AdamKorcz/stb into working

[33mcommit 0ccb4f0071043dcbff66b1ad76e384b9d1551f32[m
Merge: 5a87025 c7cf85f
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:27:22 2020 -0700

    Merge branch 'rg-matchcolors' of https://github.com/castano/stb into working

[33mcommit 5a8702567aaea06712f1b3a7693a5a6836e2dd68[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:11:47 2020 -0700

    credit for PR

[33mcommit da888065bf89dead84a467cf73f5a1ffaad35d82[m
Merge: fb1cea0 385b65d
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:11:13 2020 -0700

    Merge branch 'master' of https://github.com/Vawx/stb into working

[33mcommit fb1cea02f854b1af35ae065bebf58fad0e62c323[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:06:50 2020 -0700

    tweak PR

[33mcommit add7adc3eaef7f70d977cec7990a965b3d46bab2[m
Merge: fd9c3ea 2e78eb6
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:05:44 2020 -0700

    Merge branch 'patch-1' of https://github.com/vickit144/stb into working

[33mcommit fd9c3ea4af47e880f65415fdb0f09b6239348a30[m
Merge: 6f7420a e919bcd
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 03:01:52 2020 -0700

    Merge branch 'bmp-assert' of https://github.com/zturtleman/stb into working

[33mcommit 6f7420a8257fce547b79a855c11bafc163f0088a[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:59:10 2020 -0700

    add credits for last few PR merges

[33mcommit 67881b61ab19520f6c6bbac6e200b21d10849f01[m
Merge: 1c81674 b67dabe
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:52:03 2020 -0700

    Merge branch 'stbds-arraddn' of https://github.com/HeroicKatora/stb into working

[33mcommit 1c816743b684495f54fed934cf74a0851a13bcc0[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:49:46 2020 -0700

    make PR compile in MSVC6

[33mcommit cae8e852f648a75e49b9e2ab9223eb79a4c58905[m
Merge: cae97bd 254e1c9
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:48:11 2020 -0700

    Merge branch 'perfect-endpoint-quantization' of https://github.com/castano/stb into test

[33mcommit cae97bdb17895e12a4c316ecf6c63c2d69c59d07[m
Merge: fdafd1a 1d35dc8
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:47:41 2020 -0700

    Merge branch 'alloca-fix' of https://github.com/mackron/stb into test

[33mcommit fdafd1aab45162805b0f4c03781b6d78bb982021[m
Merge: b3a74a5 c5102ec
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:45:13 2020 -0700

    Merge branch 'loadgif-realloc-sized' of https://github.com/SasLuca/stb into test

[33mcommit b3a74a5c8aa023c97e66621ca9226c761a1feb35[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:43:26 2020 -0700

    fix PR to work on VC6

[33mcommit 206529e08eded85a1ae2106e8b05a339f2ae44e1[m
Merge: dfdb7d9 2e8b2d7
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:42:57 2020 -0700

    Merge branch 'unused#801' of https://github.com/hashitaku/stb into test

[33mcommit dfdb7d9c144bb2462c21787a71b2750fb42796e9[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:42:37 2020 -0700

    stb_ds: use keyoffset in key comparison

[33mcommit 523a14f3e1e131b0650d7d6918f581b2f8d8c538[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:20:59 2020 -0700

    stb_image_write: small buffer to avoid calling fwrite on every pixel

[33mcommit 802a1df278c7aa379b2b93989bcf89d0cb73cac6[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:20:37 2020 -0700

    tweak indentation

[33mcommit c5b527aa016f5bf5bff2cd7f5303681227399867[m
Author: Sean Barrett <seanb@radgametools.com>
Date:   Mon Jul 13 02:20:07 2020 -0700

    modern seeding of mersenne twister

[33mcommit 1e400e21d2a816550fe3c14c2a304c7ed89da956[m
Author: Srđan Stipić <srdjan.stipic@gmail.com>
Date:   Sun Jul 12 15:57:05 2020 +0200

    stb_ds: fix shputs() for strdup and arena hash table

[33mcommit c24de24aa85597846ed8d70a6b70c4b6d953c725[m
Author: Rémi Verschelde <rverschelde@gmail.com>
Date:   Tue Jul 7 11:38:04 2020 +0200

    stb_vorbis: Add missing error checks in comment reading mallocs
    
    Fixes #988.

[33mcommit 3b14b5afa6348d756d7cf49f53cc3a3fe5f30cac[m
Author: Randy <randy408@protonmail.com>
Date:   Mon Jun 1 06:22:44 2020 +0200

    Update Makefile

[33mcommit c8303509fa8d1236846637b8fc7bdbe0b829cc6e[m
Author: Randy <randy408@protonmail.com>
Date:   Mon Jun 1 06:18:13 2020 +0200

    make fuzz target compilable as c++ code

[33mcommit 9cd6cdc0e55ec3d4c002313fd5f0e6b255e8e06c[m
Author: Randy <randy408@protonmail.com>
Date:   Mon Jun 1 06:09:16 2020 +0200

    add ossfuzz build script

[33mcommit a6b384358f53c43fdc9f6dd06970389bedaaafa6[m
Merge: a7fed59 d1d0e9f
Author: Randy <randy408@protonmail.com>
Date:   Mon Jun 1 06:03:50 2020 +0200

    Merge branch 'fuzzer_updates' of https://github.com/randy408/stb into fuzzer_updates

[33mcommit a7fed59fe42b8157b8711d73e38cd79ff86e7ee5[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 08:59:07 2020 +0200

    add fuzz target to Makefile

[33mcommit 9e292f07319aa5ea8c6eb1f3cbb51ba31a0eee32[m
Author: Colton G. Rushton <colton51919@gmail.com>
Date:   Sat May 30 17:41:25 2020 -0300

    Fix minor typo in comment on line 6532

[33mcommit ec898982b0f1815cc660ece28d655677d2286626[m
Author: Recep Aslantas <info@recp.me>
Date:   Tue May 26 00:22:12 2020 +0300

    stbi: use __thread if GCC can't use _Thread_local

[33mcommit 8cb98357dec364739926b52f20fdd1e3b91c61c8[m
Author: Recep Aslantas <info@recp.me>
Date:   Tue May 26 00:03:46 2020 +0300

    stbi: fix thread local selector
    
    * GCC < 5 supports __thread and GCC >= 5 supports C11 with _Thread_local
    * Skip _Thread_local for MSVC because it may not be supported

[33mcommit d1d0e9fdb078cbc27f406607dcee775645270e2b[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 08:59:07 2020 +0200

    add fuzz target to Makefile

[33mcommit 5a7af50fa5ca6f2e75bac7e0e02ab64354df160a[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 08:47:45 2020 +0200

    remove stb_png_read_fuzzer.options

[33mcommit 88062723ff0d589360164a8a94ff4c90c777d6e9[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 08:18:56 2020 +0200

    rename fuzz target

[33mcommit b75413f8a4acd25bf1a26eb2ec818d2797c3f348[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 08:18:15 2020 +0200

    do not define STBI_ONLY_PNG in fuzz target

[33mcommit 4bafa5689952251fccee9b88ae4758a33a199faf[m
Author: Randy <randy408@protonmail.com>
Date:   Mon May 11 05:48:25 2020 +0200

    rename fuzz target, add entry point

[33mcommit 2d0faa4d264f44028bd4397b9822bad4a92471b4[m
Author: Pedro J. Estébanez <pedrojrulez@gmail.com>
Date:   Sun May 3 02:27:35 2020 +0200

    stb_vorbis.c: Fix missing update to 64-bit alignment

[33mcommit c29138ba598c323296679879eac3b3c4b56770ed[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Wed Apr 29 14:20:33 2020 -0400

    Add randy408 to the "Bug warnings & fixes" list.

[33mcommit 29d639546da9647a48d822ae128090e4f1047dea[m
Author: Randy <randy408@protonmail.com>
Date:   Wed Apr 29 14:19:01 2020 -0400

    fix integer arithmetic in stbi__zexpand()

[33mcommit b09cb2c6f583e7e813c0da53743dd93183943926[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Mon Apr 27 15:16:27 2020 -0400

    Add Ryan C. Gordon to "Bug & warning fixes" contribution list.

[33mcommit 89f3f35c9fb82f215e2f765ab4aeb05c245fcb8e[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 11:56:30 2020 -0400

    stbi__skip should return immediately if skipping zero bytes.
    
    Otherwise we might waste time or throw away state in the i/o callbacks.

[33mcommit d60594847ecca4553b18e7607d01328c58d95a42[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 11:54:22 2020 -0400

    Reject images that are too large (as defined by the application).
    
    The BMP loader already had this hardcoded to (1 << 24) pixels, so this seems
    like a good default to apply to all formats, but many apps will want to clamp
    this much much lower.
    
    It's possible to craft malicious but valid images that are enormous, causing
    stb_image to allocate tons of memory and eat a ton of CPU, so locking these
    to a maximum permitted size can save a lot of headaches in the wild.

[33mcommit 98ca24b8c7a69e1fc80e3d6a1e014b0e113980b8[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 10:41:39 2020 -0400

    Turn several asserts into formal checks.
    
    There are several places where stb_image protects itself from bad data with
    STBI_ASSERT macros, but if these are compiled out in release builds the code
    will overflow buffers, etc, without warning. If they are left enabled, the
    process will crash from assertion failures.
    
    This patch attempts to leave the assertions in place that are meant to verify
    the correctness of the interfaces (if the calling function was meant to pass
    only 8 or 16 for bit depth, it's reasonable to assert that is accurate), but
    changes asserts that are triggered by corrupt or malicious image file data.
    
    Failed asserts were the majority of crashes during fuzzing; now all of these
    cases safely report an error back to the calling app.

[33mcommit 95560bc6cf980d1a0bfe49f413a1108f83f7ec8a[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 10:39:47 2020 -0400

    Be more aggressive about unexpected EOF conditions.
    
    Fixes several hangs in the presence of bad input data.

[33mcommit eb4b057f0d559add365417a6b44e4f998cdfe589[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 10:37:30 2020 -0400

    Check a return value for errors.
    
    Catches bad input data found during fuzzing.

[33mcommit b5d2296d5d3788861550aa37d9fa3ab1d9d6bad6[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Tue Apr 28 10:35:02 2020 -0400

    Check for some obviously bad inputs from corrupt/malicious data.
    
    These all caused crashes during fuzzing.

[33mcommit 385b5d3cda7099bebbdbae9f31bcb10834439c4f[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Mon Apr 27 15:03:25 2020 -0400

    stbi__stdio_eof() should check ferror(), too.
    
    Otherwise with filesystem errors, you might end up with a short read but
    believe there's still more to read from the file, causing infinite loops.

[33mcommit 00f3f01be387fa7cba07eabec6f01441ccfa30a5[m
Author: Ryan C. Gordon <icculus@icculus.org>
Date:   Mon Apr 27 14:54:58 2020 -0400

    fseek() resets the EOF flag, even if seeking past the end of a read-only file.
    
    This causes problems when stb_image tries to do this with stdio callbacks with
    a maliciously crafted file (or just an unfortunately corrupt one)...
    
        // calls fread(), sets EOF flag, sets s->read_from_callbacks = 0
        stbi__refill_buffer(s);
    
        // calls fseek(), which resets the stream's EOF flag
        stbi__skip(some value we just read)
    
        // calls feof(), which always returns false because EOF flag was reset.
        while (!stbi__at_eof(s)) {
            // never calls fread() because s->read_from_callbacks==0
            stbi__refill_buffer(s);
            // loop forever
        }
    
    To work around this, after seeking, we call fgetc(), which will set the EOF
    flag as appropriate, and if not at EOF, we ungetc the byte so future reads
    are correct. This fixes the infinite loop.

[33mcommit d8df5e99748307e2f4f774f79142372b07b4c406[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Fri Apr 24 18:46:28 2020 +0100

    Add myself to the list of contributors
    
    The pull-request template says to do so.

[33mcommit 47a3c4f5b5153a361b73a008770dc57c064d2502[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Fri Apr 24 18:34:59 2020 +0100

    stb_vorbis.c - Detect `__NEWLIB__` for `alloca.h`
    
    This is needed for `stb_vorbis.c` to compile for the Wii U using
    devkitPro.
    
    This should theoretically also fix compilation for the Nintendo
    Switch, 3DS, and Wii (with devkitPro, that is) as they all also use
    Newlib.
    
    Newlib is also used by Cygwin:
    https://cygwin.com/git/?p=newlib-cygwin.git;a=blob;f=newlib/libc/include/alloca.h;h=5d36318914282280b353aed457e1b1f64947b584;hb=HEAD
    
    And the Google Native Client:
    https://chromium.googlesource.com/native_client/nacl-newlib/+/refs/heads/master/newlib/libc/include/alloca.h
    
    As you can see from these links, these both provide `alloca.h` as
    well, so it appears to be a safe guarantee that `alloca.h` is
    available on Newlib.

[33mcommit fdec1183124a7654fc486af690b856c30fb1ba0a[m
Author: Adam Korczynski <adam@adalogics.com>
Date:   Thu Apr 9 16:21:56 2020 +0100

    Added fuzzer for stb_c_lexer

[33mcommit c7cf85ffce89be66cd4edb6a6e2aa1b35481ea52[m
Author: Ignacio Castano <castano@gmail.com>
Date:   Sun Apr 5 20:37:29 2020 -0700

    Integrate more accurate index selection by Rich Geldreich.

[33mcommit 385b65da007e12e7a76bf5842c99553e2892d032[m
Author: Kyle Langley <altck8@gmail.com>
Date:   Mon Mar 30 22:18:40 2020 -0400

    remove + 1 from stb_strscpy and offset of -1 (n--) in readdir_raw
    
    Fix to buffer issue where stb_strscpy would use + 1 for buffer length when stb_p_strcpy_s is called, causing a stack variable corrupted issue.
    Fix to readdir_raw to no longer account for stb_strscpy having + 1 in buffer length.

[33mcommit b67dabed2a7f1390e55dde473ef9bf20911431be[m
Author: Andreas Molzer <andreas.molzer@gmx.de>
Date:   Wed Mar 25 20:58:01 2020 +0100

    Add arraddn back with void return and deprecated

[33mcommit e485c7d35380d995a4943639b0d103ee8db68a20[m
Author: Andreas Molzer <andreas.molzer@gmx.de>
Date:   Wed Mar 25 20:12:21 2020 +0100

    Split arraddn into pointer and index return

[33mcommit e919bcd32e504c7878b2898ac41725dc5abe78b2[m
Author: Zack Middleton <zack@cloemail.com>
Date:   Sun Mar 22 00:17:25 2020 -0400

    stb_image: fix assert failing when loading BMP
    
    This fixes two issues with an assert failing. I tested that the
    first part fixes #909 and the second fixes #897.
    
    1. Loading 16/24/32-bit BMP from memory caused an assert to fail
    (excluding 16-bit BMP with hsz 12).
    
    img_buffer offset was always compared with the buffer for
    stbi_load_from_file() but stbi_load_from_memory() uses an external
    buffer.
    
    Resolution: Change s->buffer_start to s->img_buffer_original.
    
    2. Loading BMP with large header from file caused assert to fail.
    
    img_buffer points to stbi_uc buffer_start[128] but the largest BMP
    supported has a 138 byte header (hsz 124) causing img_buffer to wrap
    around to an offset of 10. The assert fails because 138 (header size)
    != 10 (offset in temp read buffer).
    
    Resolution: Add the previously read bytes to the offset in temp read
    buffer to get the absolute offset.
    
    The issues were introduced by the commit c440a53d06
    ("stb_image: fix reading BMP with explicit masks").

[33mcommit 2e78eb603b1be816deb4a9701452bfe9905714c2[m
Author: wph612 <43688928+vickit144@users.noreply.github.com>
Date:   Tue Mar 24 20:49:40 2020 -0400

    Added debugging check on line 1604
    
    I added the code assert(f->valid_bits >= n);  instead of removing if (f->valid_bits < 0) return 0; to improve code with checking and debugging instead.

[33mcommit fcd0a0bfaa14d941f913cc522ecc5a3e7ebd8c76[m
Author: wph612 <43688928+vickit144@users.noreply.github.com>
Date:   Tue Mar 24 19:47:18 2020 -0400

    Remove if (f->valid_bits < 0) return 0;  on line 1603
    
    I propose to remove this line because  f->valid_bits will never be less than zero since, in the while loop, you're adding 8 to it. Therefore, it will always evaluate to false. This is to help remove redundant code.

[33mcommit e423b41e74e24ec6d4bf971715dc819d3da5fa42[m
Author: Andreas Molzer <andreas.molzer@gmx.de>
Date:   Tue Mar 24 15:30:20 2020 +0100

    Fix arraddn returning index instead of pointer
    
    The documentation of that operation already said:
    > Returns a pointer to the first uninitialized item added.
    
    This also makes a lot of sense, allowing easy initialization. But the
    implementation returned the index of the first uninitialized element
    instead.

[33mcommit 254e1c99759a018bc0932a088b00d4c2740f1399[m
Author: Ignacio Castano <castano@gmail.com>
Date:   Thu Mar 19 23:23:36 2020 -0700

    Perfect quantization of DXT endpoints
    
    A small change to quantize floating point endpoints to RGB565 as expanded in the DXT spec. For more info see: https://gist.github.com/castano/c92c7626f288f9e99e158520b14a61cf

[33mcommit 1d35dc8609adecc3bc91ac22cc7331b66e81380c[m
Author: David Reid <mackron@gmail.com>
Date:   Sat Feb 15 07:23:22 2020 +1000

    stb_vorbis: Fix macro redefinition warning on MinGW.

[33mcommit c5102ecc4df7fab0bdc882c22af5aa88c123b27f[m
Author: Luca Sas <sas.luca.alex@gmail.com>
Date:   Thu Feb 13 13:05:12 2020 +0000

    Refactored stbi__load_gif_main to use STBI_REALLOC_SIZED instead of STBI_REALLOC.

[33mcommit 2e8b2d7f58edbf275ee409093cbe4a236d90b705[m
Author: hashitaku <s317062@ed.sus.ac.jp>
Date:   Sat Feb 8 10:11:40 2020 +0900

    stb_ds.h: fix unused parameter warning

[33mcommit a2c91804a3c9876879997c30c43d73e2dd42dfc0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 6 05:36:53 2020 -0800

    stb_sprintf: avoid clang -O3 misaligned access

[33mcommit f54acd4e13430c5122cab4ca657705c84aa61b08[m
Merge: 95671cc 828e6cf
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 04:32:20 2020 -0800

    Merge branch 'working'

[33mcommit 828e6cfdf7099e43acfd5a0026dae614f09eb7fc[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 04:31:55 2020 -0800

    update test

[33mcommit 95671cca5796d908858bdffce025ff4689e40c0c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:41:17 2020 -0800

    update version number

[33mcommit cd742941e6d70859919ec7f07226be1a06fc7eb8[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:40:17 2020 -0800

    stb_truetype: fix warning

[33mcommit 37b9b20fdec06c75a0493e0bb59e2d0f288bfb51[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:19:08 2020 -0800

    update version numbers

[33mcommit efdaadcb4a80c0c3d60c94e537657e33bfcc6c8e[m
Merge: 2805fe3 41a6bb5
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:16:46 2020 -0800

    Merge branch 'master' of https://github.com/MarcoLizza/stb into working

[33mcommit 2805fe39ab4ee28e837e91f334ed4b1cbb9104ce[m
Merge: cb9d4e9 3366d1e
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:15:56 2020 -0800

    Merge branch 'fix_ub_shift' of https://github.com/wojdyr/stb into working

[33mcommit cb9d4e9547a59fc0ef89e2a9a9a688dddc6e735a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:15:41 2020 -0800

    sprintf: warning fixes

[33mcommit 6b38abed1f8a86693b01f94d33d58f417a84ebae[m
Merge: f06f586 3bb12a1
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:10:20 2020 -0800

    Merge branch 'mine/avoid_warning' of https://github.com/wojdyr/stb into working

[33mcommit f06f586d186ef674c92b6e5dd2c841a9afb17c66[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Feb 5 03:10:07 2020 -0800

    sprintf warnings

[33mcommit 41a6bb58d114d5943235aa6d0410eafd07a2c642[m
Author: Marco Lizza <marco.lizza@gmail.com>
Date:   Tue Feb 4 17:03:48 2020 +0100

    Other (pedantic) warnings for possible uninitialized variables.

[33mcommit 43c6bd4e0e10af838285744c08710711d585adaf[m
Author: Marco Lizza <marco.lizza@gmail.com>
Date:   Tue Feb 4 17:03:23 2020 +0100

    Fixing (pedantic) cast warnings.

[33mcommit 6e8c31685f6b75b3e7c38f39f4f6984f093665c9[m
Author: Marco Lizza <marco.lizza@gmail.com>
Date:   Tue Feb 4 16:59:47 2020 +0100

    Fixing fall-trough (pedantic) warnings.

[33mcommit 3366d1e79773c39ff74d98373508c71c0e0e84eb[m
Author: Marcin Wojdyr <wojdyr@gmail.com>
Date:   Mon Feb 3 20:17:03 2020 +0100

    stb_sprintf: avoid left shift of negative value
    
    fix undefined behaviour reported by UBSan:
      runtime error: left shift of negative value -9223372036854775808
    and add a test case.
    
    fixes #800

[33mcommit 3bb12a14e954f626a9c65bb77d49d92a89488438[m
Author: Marcin Wojdyr <wojdyr@gmail.com>
Date:   Mon Feb 3 14:42:35 2020 +0100

    stb_sprintf.h: fix unused-parameter warning

[33mcommit 498bd3e01719448abca314153f38e36fe8b5043e[m
Author: Nerd <metab0t@users.noreply.github.com>
Date:   Mon Feb 3 16:17:42 2020 +0800

    Fix typo in stbds_hmget_key_ts_wrapper

[33mcommit 0224a44a10564a214595797b4c88323f79a5f934[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 20:30:25 2020 -0800

    stb_image: fix new warnings

[33mcommit 0cbdb25d2ba3b89367fdf280096cab7bccec38f8[m
Merge: dc664b1 ceddd74
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:32:55 2020 -0800

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit dc664b12899d698c4364e0d6b0f01f93cd4935b4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:32:21 2020 -0800

    update readme

[33mcommit 2bb4a0accd4003c1db4c24533981e01b1adfd656[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:30:27 2020 -0800

    Fix trailing whitespace

[33mcommit 7a69424f1577decb2467a3e3595dff11f5379b26[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:26:50 2020 -0800

    update version numbers

[33mcommit 17c301817b5240bcf61c9e91f395ed470d9e7f4c[m
Merge: 50dc480 8ee3bea
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:16:16 2020 -0800

    Merge branch 'working'

[33mcommit 8ee3beabbaeeeabdfb7302d7eba903a4b273ef6a[m
Merge: d79349d f298fb8
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:16:06 2020 -0800

    Merge branch 'master' of https://github.com/BSVino/stb into working

[33mcommit 50dc48013b8f477e1feae4271d698fed987c62da[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:12:27 2020 -0800

    test stb_include.h

[33mcommit 5e4a0617b72fd4db2e1fc4d5c2d8b483d948d573[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 11:12:13 2020 -0800

    udpate version numbers

[33mcommit d79349d0b72e3efc8f429c1297a4aebbafb63090[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:54:29 2020 -0800

    stb_vorbis: update credits

[33mcommit 95ce2523057da00631cf20a0f0ba8fdc96b04a2a[m
Merge: 49cbedf 2a0cff1
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:51:14 2020 -0800

    Merge branch 'OggComment' of https://github.com/audinowho/stb into work2

[33mcommit 49cbedfab6623f38a8fa65b32d10ab4b2fefd872[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:36:08 2020 -0800

    LICENSE: remove trailign spaces

[33mcommit bd79d89de2c5b4f53a0fe1bf3636352f48922736[m
Merge: 1ced9fa cf1cb80
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:11:53 2020 -0800

    Merge branch 'patch-1' of https://github.com/Croydon/stb into work2

[33mcommit 1ced9faea1c88f9c2640c7cb496608c41d99757c[m
Merge: d256911 e2b8524
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:11:43 2020 -0800

    Merge branch 'unused-function-warnings' of https://github.com/BradleyMarie/stb into work2

[33mcommit d2569111cd78b09fcd311621df50974075b4014f[m
Merge: aad77ec d5d052c
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:06:31 2020 -0800

    Merge branch 'splitpath_raw_fix' of https://github.com/bcollins526/stb into work2

[33mcommit aad77ec74eacd1194addefe92defb9195efac143[m
Merge: a6726a3 2f18c96
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:04:39 2020 -0800

    Merge branch 'issue-799' of https://github.com/pwaller/stb into work2

[33mcommit a6726a3d289bfbe98c727fdad40cf2bee11a3102[m
Merge: 24fdc35 a6945cb
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:03:31 2020 -0800

    Merge branch 'patch-1' of https://github.com/cshesse/stb into work2

[33mcommit 24fdc35c90194f66d2077c6a58810406c9fd70a9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:02:53 2020 -0800

    stb_image_write: fix jpeg to work on non-C99 compilers

[33mcommit 4067b6d28beab873d95d9ada6194c6d3788114a2[m
Merge: 6a6e028 58e0c44
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:02:25 2020 -0800

    Merge branch 'kc/fix-coverity-issues-1' of https://github.com/krcroft/stb into work2

[33mcommit 6a6e028e26451b2054ff79ed110ce4c42d79918f[m
Merge: 454da53 4306eea
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:01:51 2020 -0800

    Merge branch 'fix-vs2019-warning' of https://github.com/Reedbeta/stb into work2

[33mcommit 454da539a22c45a3766f690fc9f376e26d887e08[m
Merge: 1586318 1551619
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 10:01:04 2020 -0800

    Merge branch 'stbiw_update_jpeg' of https://github.com/DanielGibson/stb into work2

[33mcommit 1586318a005f47538422f0758c538d8e02f6bb00[m
Merge: cc99be2 4148eb4
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:53:28 2020 -0800

    Merge branch 'master' of https://github.com/Try/stb into work2

[33mcommit cc99be2a9f088d3c465631799d787c75248854b4[m
Merge: fad1aa5 57b9ea6
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:51:34 2020 -0800

    Merge branch 'quell-clang-wcast-align' of https://github.com/a-e-k/stb into work2

[33mcommit fad1aa50c90cb4f650204e89073a7161ec97217d[m
Merge: ca1b581 221a9ef
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:46:48 2020 -0800

    Merge branch 'fix-stb_include_strings' of https://github.com/sp0lsh/stb into work2

[33mcommit ca1b58154d31162fecd413cfc4ce5df1f6567e3d[m
Merge: acd1c66 15ae70a
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:45:56 2020 -0800

    Merge branch 'working' into work2

[33mcommit acd1c66aa4f444a81e36cf3812838f4a9dfb0c1b[m
Merge: d882f54 117e174
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:45:35 2020 -0800

    Merge branch 'fix806' of https://github.com/kolbma/stb into work2

[33mcommit d882f542e9f06fd2b66a6d06c2bfa8d1034bb1ed[m
Merge: fd4f1f7 da79a21
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:44:21 2020 -0800

    Merge branch 'vorbis_seek_fixes' of https://github.com/dougallj/stb into work2

[33mcommit fd4f1f702e42a2badf91da45ad7ae2f3a1d9c4e1[m
Merge: 95dc062 905d05a
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:42:24 2020 -0800

    Merge branch 'master' of https://github.com/haferburg/stb into work2

[33mcommit 95dc062d3fd3910e7807b15de79e9b475cc01efa[m
Merge: 69a39c1 e615214
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:41:43 2020 -0800

    Merge branch 'cnlohr-fix-stb-include-newline' of https://github.com/cnlohr/stb into work2

[33mcommit 15ae70a3711b1cbc05ec280a51c5eb269d704681[m
Merge: e80419c 69a39c1
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:40:38 2020 -0800

    Merge branch 'work2' into working

[33mcommit 69a39c14cc529808b46c74b5ccfbfbc14b305a4b[m
Merge: 5a3f1eb da12942
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:40:26 2020 -0800

    Merge branch 'fix-clang-warning' of https://github.com/zanshi/stb into work2

[33mcommit 5a3f1ebd5465b627fa440848e1225540faae3ec5[m
Merge: 6877b1a 58c5141
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 09:34:23 2020 -0800

    Merge branch 'master' of https://github.com/Kelimion/stb into work2

[33mcommit 6877b1afd3f26e8f4c13c98790e43b358c7e5815[m
Merge: a0245ff 01b2d76
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:52:48 2020 -0800

    Merge branch 'fix_issue_746' of https://github.com/BlackMATov/stb into work2

[33mcommit a0245ff8036b9c710696bf09cb2e54fac67a6cca[m
Merge: 6479067 791a907
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:44:27 2020 -0800

    Merge branch 'stderr' of https://github.com/dimkr/stb into work2

[33mcommit e80419cd29d5d9faba37df71a85945f218fecb6e[m
Merge: cffff7c 6479067
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:26:07 2020 -0800

    Merge branch 'work2' into working

[33mcommit 647906759cd3e4659ec7bbf34cf4aa9738f6b274[m
Merge: f2dd751 a82e742
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:25:48 2020 -0800

    Merge branch 'master' of https://github.com/fluffrabbit/stb into work2

[33mcommit f2dd751a347727803a4c2cefeb00bbe547ea5ccf[m
Merge: 81d1537 5ac55a3
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:24:40 2020 -0800

    Merge branch 'stb-easy-font-fix-multiple-definition-errors' of https://github.com/podsvirov/stb into work2

[33mcommit 81d153757941da2c6589fc9c2ee3808dbe2c6be9[m
Merge: 28cc61a 4a4c9de
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:21:46 2020 -0800

    Merge branch 'fix_issue_745' of https://github.com/BlackMATov/stb into work2

[33mcommit cffff7c90ac99fce012ff247f8ca6792d8130fd0[m
Merge: e943476 28cc61a
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:17:09 2020 -0800

    Merge branch 'work2' into working

[33mcommit 28cc61a1ff9c65bab78b278b1185dc4fc3359826[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:16:58 2020 -0800

    stb_image: fix previous fix

[33mcommit 770e4dbe50b4a74fbcbb3df2ff0bdfcfee5ad288[m
Merge: f9ec936 f7d1cd5
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:16:26 2020 -0800

    Merge branch 'patch-2' of https://github.com/Brotcrunsher/stb into work2

[33mcommit ceddd7462210fc15d1aec4f18bf47929f492930f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 2 08:15:40 2020 -0800

    Update CONTRIBUTING.md

[33mcommit f9ec936e7e46234c65778106057834d330f543d5[m
Merge: fe6bef2 4e0c494
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:14:23 2020 -0800

    Merge branch 'patch-1' of https://github.com/GMacharadze/stb into work2

[33mcommit fe6bef23075aaf72a4fd264f25cc9e2cffcb62b5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:14:00 2020 -0800

    stb_truetype: clean up svg support

[33mcommit ade80f4609d25e9409bbacc171f11e71bb4a0319[m
Merge: d487122 0a10163
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:07:01 2020 -0800

    Merge branch 'svg' of https://github.com/chris-y/stb into work2

[33mcommit e943476f7f095146cfec8c607267c2222c3a6ced[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:04:34 2020 -0800

    stb_sprintf: support hh

[33mcommit d4871226e4daa6046b99c6590330734972f264c8[m
Merge: ecf2a56 5db48d3
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:04:09 2020 -0800

    Merge branch 'upstream' of https://github.com/yangfl/stb into work2

[33mcommit ecf2a56f6d9f80e73cbb43f63842dfc8bf7c7edf[m
Merge: c046a25 48ffc6b
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:03:06 2020 -0800

    Merge branch 'patch-1' of https://github.com/StylishTriangles/stb into work2

[33mcommit c046a25fd7ec46788f51bd772a8fa98ff18b500f[m
Merge: 3f5db89 0637408
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 08:00:39 2020 -0800

    Merge branch 'fuzz' of https://github.com/randy408/stb into work2

[33mcommit 3f5db89bafb6668f60a51ad3d3bbf97b4cceb4dc[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:49:41 2020 -0800

    stb_sprintf: redo ASAN fixes after problematic merge

[33mcommit e802821e4d62ee2c53849e031706ed45fa843a1d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:47:53 2020 -0800

    stb_sprintf: PR 613

[33mcommit 81b4fd734237506ff249a856d4b4a515b8b4ea0b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:37:20 2020 -0800

    test_sprintf: clean up for MSVC6 & integration to codebase

[33mcommit 5a2c8901b25d9ba32eb411c465cf87bdb91c401b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:37:10 2020 -0800

    stb_dxt: documentation change for constant alpha

[33mcommit 3223673e86c80265994f31783ad8934bf6256c20[m
Merge: f792c3b e0a0328
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:21:45 2020 -0800

    Merge branch 'test_sprintf' of https://github.com/wojdyr/stb into work2

[33mcommit f792c3b982147c7179db0572bd74c72b6ccdceda[m
Merge: 57de42c c716696
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:12:14 2020 -0800

    Merge branch 'work2' into working

[33mcommit c716696e2873e0b40cb627dda2760e403bdfa542[m
Merge: 052dce1 9835483
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:11:57 2020 -0800

    Merge branch 'stb_sprintf-asan' of https://github.com/h-s-c/stb into work2

[33mcommit 57de42c23f02f286c9559ea35c28c35addaec955[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:06:27 2020 -0800

    disable broken tilemap editor build

[33mcommit eb48fbdcede98f93dab3a5e42ce5b0072b739cf1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 2 07:06:05 2020 -0800

    stb_image: use thread-locals for vertically_flip flag and g_failure_reason

[33mcommit cf1cb80c8ee12f47cac8ae90bbc0451b69c80704[m
Author: Michael "Croydon" Keck <git@cr0ydon.com>
Date:   Sun Feb 2 02:11:35 2020 +0100

    Create LICENSE
    
    Copied from stb.h

[33mcommit e2b8524aa271fc03fec3740a5b396df10428562e[m
Author: Brad Weinberger <1484541+BradleyMarie@users.noreply.github.com>
Date:   Sat Feb 1 11:41:47 2020 -0800

    Fix clang unused function compile warnings

[33mcommit 7cce4c3ad9a147c67258c5966f676d8436140939[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Feb 1 08:15:04 2020 -0800

    stb_ds: remove accidental #include

[33mcommit 2f870b3c07e477a5424bc5cc7dc15f90e484ce8f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Feb 1 06:19:59 2020 -0800

    Update CONTRIBUTING.md

[33mcommit a909108b4509af30659e7b783c22102ed50350c5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Feb 1 06:17:14 2020 -0800

    fix #820

[33mcommit 4a7a434c2d059513aeba1afc0142bef6bd9db8ea[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Feb 1 04:21:41 2020 -0800

    various tests and infrastructure fixes

[33mcommit c440a53d0666af2052bcadf3f565a6bcfa015b5f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Feb 1 04:19:28 2020 -0800

    stb_image: fix reading BMP with explicit masks

[33mcommit d693c6103afbbe155d4187f1f37e0ce781d20cc8[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Feb 1 04:18:23 2020 -0800

    stb_ds.h: thread-safe functions; pointer-returning functions; change return value of arraddn

[33mcommit aa482fc4a1de94a1105f0b8f47c48f446efe2591[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Feb 1 03:43:33 2020 -0800

    stb.h: perfect hashing functions requires opting-in with "#define STB_PERFECT_HASH"; fix some missing parenthesis in stb_arr macros

[33mcommit d5d052c806eee2ca1f858cb58b2f062d9fa25b90[m
Author: Brian Collins <60075820+bcollins526@users.noreply.github.com>
Date:   Sun Jan 26 15:06:32 2020 -0800

    casting to int to remove ptrdiff_t <-> int comparison warnings

[33mcommit 8fca192660f66f284017e74eca7ffcb8bbf7bbe3[m
Author: Brian Collins <60075820+bcollins526@users.noreply.github.com>
Date:   Sun Jan 19 14:38:09 2020 -0800

    better to just use stb_strncpy inside stb__splitpath_raw, also fixed an indexing bug in stb_strncpy itself.

[33mcommit 7c44b159039c3fb1bba2947f411f4bf10885e729[m
Author: Brian Collins <60075820+bcollins526@users.noreply.github.com>
Date:   Sun Jan 19 13:43:43 2020 -0800

    forgot to update fixes list

[33mcommit 41d1dcc0299ffe54da1913fa232d4a87b01ef3c8[m
Author: Brian Collins <60075820+bcollins526@users.noreply.github.com>
Date:   Sun Jan 19 13:06:11 2020 -0800

    changed buffer to path for STB_EXT_NO_PERIOD, and specified appropriate buffer size for the copy (sizeof(buffer) referred to the size of the buffer pointer, which was incorrect)

[33mcommit 2f18c96cfb914ed30503b1554a7875a847f99293[m
Author: Peter Waller <p@pwaller.net>
Date:   Sun Dec 29 22:58:47 2019 +0000

    Pad allocations in setup_{,temp_}malloc for 8-byte alignment
    
    4-byte alignment triggered warnings with clang and -fsanitize=undefined.
    
    Fix #799.
    
    Signed-off-by: Peter Waller <p@pwaller.net>

[33mcommit a6945cb85228820394b5f6ae9c8db224cf5d23f3[m
Author: cshesse <48501609+cshesse@users.noreply.github.com>
Date:   Sun Dec 22 20:39:23 2019 -0800

    fix possible bug in uniform sample code

[33mcommit 58e0c4438db5e77b0ad90d3a8c057bb04999bcdc[m
Author: Kevin Croft <krcroft@gmail.com>
Date:   Wed Dec 4 21:48:21 2019 -0800

    STB Vorbis: eliminate inaccessible branch
    
    The eliminated code removes the (ch == 1) branch, which is scoped
    within this if condition: `if (rtype == 2 && ch != 1)`, therefore
    the (ch == 1) branch will never be taken.
    
    Fixes #842.

[33mcommit 3b491aa07c2c704b724921b1ef514c45d0153b89[m
Author: Kevin Croft <krcroft@gmail.com>
Date:   Wed Dec 4 20:00:45 2019 -0800

    STB Vorbis: prevent division by zero in decode_resign if ch == 0
    
    In the call to decode_residue:
      decode_residue(f, residue_buffers, ch, n2, r, do_not_decode);
    
    The channel count is previously intialized as zero and incremented
    based on a for-loop (f->channels) plus a conditional,
    if (map->chan[j].mux == i).  If this doesn't happen then 'ch'
    remains zero.
    
    Once inside decode_residue(..), the code has three branches based
    on channel count: stereo (ch == 2), mono (ch == 1), and then the
    exception if it's neither of those (simple 'else').  It's in here
    where a zero-valued 'ch' can be used as the denominator in these
    calculations:
        int c_inter = z % ch
        p_inter = z/ch;
    
    Obviously this 'else' branch is meant for channel counts greater
    than two an not for zero channels; so this change simply makes
    that branch only valid if (ch > 2).

[33mcommit 15516199e5a2559900055fb13088604afd093040[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sun Dec 1 09:41:49 2019 -0100

    stb_image_write: Update JPEG code to jo_jpeg 1.60
    
    For quality <= 90, it now supports subsampling U and V
    so it encodes smaller files.
    
    See https://www.jonolick.com/home/jo_jpeg-release-160 for more info
    about jo_jpeg 1.60

[33mcommit 4306eea3cb61a565669ddff32899366bbea8922c[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Sat Nov 30 14:36:51 2019 -0800

    Fix VS2019 warning
    
    - VS2019 on /W4 warns about applying '*' to enums. Fixed by casting to int.

[33mcommit 4148eb4d909460b1db3baea7821336165845f1af[m
Author: Try <try9998@gmail.com>
Date:   Mon Nov 18 19:25:38 2019 +0100

    stb_image: fix CRC reading at the end of IEND chunk in png file

[33mcommit 57b9ea6510750b9374bd8c690db54e6055990f8d[m
Author: Andrew Kensler <andrew@eastfarthing.com>
Date:   Fri Nov 15 23:51:00 2019 -0800

    Quell -Wcast-align warnings from Clang
    
    The stbi__sbraw() macro in stb_image_write.h causes Clang to spew about 24
    warnings complaining that "cast from 'unsigned char *' to 'int *' increases
    required alignment from 1 to 4" when compiled with the -Wcast-align option.
    
    In practice, this is spurious so long as STBIW_MALLOC() and STBIW_REALLOC()
    follow the usual alignment semantics for malloc() and realloc() in that they
    align sufficiently for any built-in type.
    
    To quell the warning, we can cast through a void pointer as an intermediary.

[33mcommit 221a9efcfe8a7ae15b7e982c2a2b41172719f8d1[m
Author: Michal Klos <michal.m.klos@gmail.com>
Date:   Mon Nov 11 14:21:41 2019 +0100

    added credits according to contributor guide

[33mcommit cdf3ef15366cb00b7fd0662cb7417b34c8fad25b[m
Author: Michal Klos <michal.m.klos@gmail.com>
Date:   Mon Nov 11 13:59:19 2019 +0100

    stb_include: fix stb_include_string iteration. Upper bound was incremented each loop instead of iterator causing endless loop when called

[33mcommit 117e1741a22fb0ad9f553b005d5e4c4f1d99734c[m
Author: arlecchino <kolbma@users.noreply.github.com>
Date:   Tue Nov 5 17:43:20 2019 +0100

    stb_printf - added contributor

[33mcommit b97d06e0fae0a40fab79a5b6eeedd4d8ba7d3df4[m
Author: arlecchino <kolbma@users.noreply.github.com>
Date:   Tue Nov 5 17:39:22 2019 +0100

    fix: stb_sprintf - gcc defines __powerpc64__
    
    Fix for stb_sprintf https://github.com/nothings/stb/issues/806
    fixes #806

[33mcommit f67165c2bb2af3060ecae7d20d6f731173485ad0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Oct 28 09:30:02 2019 -0700

    Update README.md

[33mcommit da79a214efa2a8c94ff76aa60f678be12f9dfa3e[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Mon Oct 21 20:39:31 2019 +1100

    stb_vorbis: improve fix for theoretical seek performance problem

[33mcommit c3298670d028a7f4381ad5f4a9f8d27266a9422b[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Mon Oct 21 15:37:04 2019 +1100

    stb_vorbis: fix a couple asserts that fail on invalid files

[33mcommit 057914d959243e51b8399155d34968f1bbb151ba[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Sun Oct 20 14:42:28 2019 +1100

    stb_vorbis: fix pushdata for files with audio packets in header pages
    
    Fixes #259, #597

[33mcommit 905d05a1d0b6583b35eeabf6886da5ff04cf380a[m
Author: Andreas Haferburg <andreas.haferburg@stryker.com>
Date:   Mon Oct 14 14:24:47 2019 +0200

    Fixed whitespace

[33mcommit c70479c47b60060cd9ea82470f1e0cd1637d696f[m
Author: Andreas Haferburg <andreas.haferburg@stryker.com>
Date:   Mon Oct 14 14:23:36 2019 +0200

    Revert "Fixed whitespace"
    
    This reverts commit 72646ac4aed8bbbe09e39d08029f5643b98eba5a.

[33mcommit 72646ac4aed8bbbe09e39d08029f5643b98eba5a[m
Author: Andreas Haferburg <andreas.haferburg@stryker.com>
Date:   Mon Oct 14 14:16:11 2019 +0200

    Fixed whitespace

[33mcommit df0c8e92d40a01c5909f6102054abc2d471a89c7[m
Author: Andreas Haferburg <andreas.haferburg@stryker.com>
Date:   Mon Oct 14 14:05:36 2019 +0200

    Fixed compiler warnings C4244 conversion from 'int' to 'unsigned char'/'unsigned short'.

[33mcommit e61521448834628dd50715b0cb38371b194b2624[m
Author: cnlohr <lohr85@gmail.com>
Date:   Wed Oct 9 02:38:08 2019 -0400

    Fix bare backslash n as being a valid whitespace character.

[33mcommit da1294295760ce04ce261cbdd3ee889be45373f7[m
Author: Niclas Olmenius <niclas@voysys.se>
Date:   Thu Oct 3 12:50:23 2019 +0200

    stb_image_write: fix clang warning
    
    fix -Wmissing-variable-declarations clang warning
    
    `stbi__flip_vertically_on_write` is now static like
    `stbi__vertically_flip_on_load` in `stb_image.h`

[33mcommit 7c4eb44a636ab398b1aea872e4f5792ad66d7706[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Tue Oct 1 20:47:29 2019 +1000

    stb_vorbis: fix seeking in files with audio packets in header pages
    
    Fixes #682, #580

[33mcommit 2abc5c6ced37e2d70a5e7401dbbb9cfc5700995e[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Tue Oct 1 16:37:22 2019 +1000

    stb_vorbis: fix seek_to_sample_coarse failure near page end

[33mcommit 6ca87a9e0ec90ace080f172ecda3e1850c8b4beb[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Tue Oct 1 16:36:41 2019 +1000

    stb_vorbis: fix theoretical seek performance problem

[33mcommit 2a0cff12880c6978767f93fc50d4dc6a8941f761[m
Author: Audino <Audino>
Date:   Thu Sep 12 16:51:44 2019 -0700

    Add comment support to stb_vorbis

[33mcommit 01b2d76baf23fbb251bb8dad784abbebcf734410[m
Author: BlackMATov <blackmatov@gmail.com>
Date:   Thu Aug 22 10:25:09 2019 +0700

    stb_image.h: fix warning about unused function 'stbi__err'
    
    Fixes issue #746.

[33mcommit 052dce117ed989848a950308bd99eef55525dfb1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 17 09:53:02 2019 -0700

    more fixing

[33mcommit 657be5c6548b6adb3d94bed8de7cf3501f83330e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 17 09:52:07 2019 -0700

    fix README.md "noteworthy" links

[33mcommit 791a907faafddb0838212c446ae37d8cf22c4fd4[m
Author: Dima Krasner <dima@dimakrasner.com>
Date:   Tue Aug 13 13:09:56 2019 +0300

    stb_leakcheck: add support for output to stderr

[33mcommit bcb2815ab394486b1d735eb228fb1dbdf407436b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 17:03:05 2019 -0700

    stb_ds: add documentation for STBDS_UNIT_TESTS, -std=c++0x

[33mcommit c7343d42638bc1920ba4befa2591023e17a0dcc7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 16:45:14 2019 -0700

    more Travis fixing

[33mcommit 897c33133fd4a53292e1a1e6fc09bc77ca5663c6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 16:42:27 2019 -0700

    more travis testing

[33mcommit 5037e236ed61813ecefe87d3ec334a6068a18d9c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 15:55:39 2019 -0700

    try to work around Travis old GCC errors

[33mcommit 76254f7758dd97a1022534307b478068b12a69ec[m
Merge: be594f1 4136af1
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 14:39:51 2019 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit be594f1e0b1d3a15591dfdf2182bfdb02fef3408[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 14:37:45 2019 -0700

    stb_ds: maybe avoid problem with inferring template type from enum with gcc

[33mcommit 4136af1b230998dca5483cc8e3f4d421b6dd5584[m
Merge: 787f1d6 0cff58e
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 11 14:08:32 2019 -0700

    Merge pull request #789 from sjml/patch-2
    
    typo in credit comment

[33mcommit 0cff58ecf856ca6a9eb2975521398c22ca4fc89c[m
Author: Shane Liesegang <sjml@users.noreply.github.com>
Date:   Sun Aug 11 23:02:34 2019 +0200

    very minor, non-urgent :)

[33mcommit 787f1d646a981523297fa97f30986284dd245290[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 05:38:37 2019 -0700

    Update version numbers

[33mcommit 5072185467c002bd4229ee2418341db3639df95e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 05:19:33 2019 -0700

    stb_image: fix static analyzer warnings

[33mcommit a895aec68686582c9e41d23dc29bf71e0b5d603e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 05:19:00 2019 -0700

    stb_c_lexer: fix a static analysis warning

[33mcommit a2d540a68955c059854458560c1f7a1c8f220dab[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 05:18:24 2019 -0700

    stb.h: fix clang compile

[33mcommit b26a31072d413b4b6d7da1bc98f095455240c3f0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 05:17:42 2019 -0700

    test.sbm: tweak tests so all pass

[33mcommit 846d15c102b33b1cab702fedd9a442fcee1f2e82[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:58:48 2019 -0700

    image_test: tweak testing to open image in more modes

[33mcommit bd8d9a88bc5250b78bc3edf6ae41bda09827e7a3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:57:39 2019 -0700

    test.sbm: add clang compilation

[33mcommit 8ca86ee1a14b474f9af3e9ed4e1b07b7fb020332[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:56:12 2019 -0700

    stb_perlin: add non-power-of-two wrapping noise

[33mcommit 26a02f81ca72ce74ccfc59da823f63a63f8bdaea[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:54:52 2019 -0700

    stb_image: fix bug where bmp claimed to be 24-bit but also claimed to have an alpha bitfield

[33mcommit 61be29d1612b83b80fca3073f39fb4091db0f4aa[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:53:51 2019 -0700

    stb_ds: fix bug with shgeti not returning correct value

[33mcommit a5cbacd1c0712ebed42ce64201abc0dde43069f6[m
Merge: a5071ad 6bde006
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:33:11 2019 -0700

    Merge branch 'fix-textedit-typo' of https://github.com/mastensg/stb into working

[33mcommit a5071ad702706023c54430e69c8044bc6f26ee8c[m
Merge: 70bd711 a5b663f
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:32:14 2019 -0700

    Merge branch 'master' of https://github.com/rgriege/stb into working

[33mcommit 70bd71183175625b28cde867e8548576670eceb1[m
Merge: 5c98e65 f3ca0dd
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:26:55 2019 -0700

    Merge branch 'pull-request' of https://github.com/kaesve/stb into working

[33mcommit 5c98e6564ba74d5a6e97004dd8730a69e9e7b6e6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 11 04:26:23 2019 -0700

    stb_vorbis: fix typo in CVE number in docs

[33mcommit 130f28df68c3fdbf043c4275260ba1c870495b5b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Aug 9 12:37:57 2019 -0700

    update readme

[33mcommit 1b2fa11055e6a4361ac75a8091f5a916747f8d43[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Aug 9 04:13:24 2019 -0700

    stb_vorbis: bump version number

[33mcommit 98fdfc6df88b1e34a736d5e126e6c8139c8de1a6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Aug 9 04:05:22 2019 -0700

    Fix seven bugs discovered and fixed by ForAllSecure:
    
    CVE-2019-13217: heap buffer overflow in start_decoder()
    CVE-2019-13218: stack buffer overflow in compute_codewords()
    CVE-2019-13219: uninitialized memory in vorbis_decode_packet_rest()
    CVE-2019-13220: out-of-range read in draw_line()
    CVE-2019-13221: issue with large 1D codebooks in lookup1_values()
    CVE-2019-13222: unchecked NULL returned by get_window()
    CVE-2019-13223: division by zero in predict_point()

[33mcommit a82e7424d20623c7fdf64051e5c3bf62b1f0ae80[m
Author: fluffrabbit <fluffrabbit@aol.com>
Date:   Sat Aug 3 19:15:41 2019 -0600

    extern stb_perlin_noise3_seed

[33mcommit 5ac55a3359a6c5dacd26d32c13d2f1e43aa8a42d[m
Author: Konstantin Podsvirov <konstantin@podsvirov.pro>
Date:   Tue Jul 9 22:27:35 2019 +0300

    stb_easy_font: fix multiple definition errors
    
    There changes fix posible multiple definition errors when
    include stb_easy_font.h header to more then one source file.
    
    Closes #777

[33mcommit 5db48d36043ca55ba2ba1986bbdd4699f4941778[m
Author: yangfl <yangfl@users.noreply.github.com>
Date:   Thu Apr 4 11:38:56 2019 +0800

    stb_divide: use return value to indicate errors

[33mcommit c72a95d766b8cbf5514e68d3ddbf6437ac9425b1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:44:12 2019 -0700

    update README

[33mcommit 9f1836f0b19fd9112c41b97f336ab9933edd1d07[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:43:52 2019 -0700

    update version

[33mcommit f9910f1f9a2ee8c778a5fc21527efb67ff84fbe2[m
Merge: 8f0bade fad8903
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:26:21 2019 -0700

    Merge branch 'hmlen-null' of https://github.com/phoekz/stb into working

[33mcommit 8f0bade4ae386686d41ea72ce7ec162c25985aa3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:25:44 2019 -0700

    tweak STBDS_REALLOC/STBDS_FREE change

[33mcommit 258c6e1f50e5f1aaad57823072da95a7e5f11e88[m
Merge: eddae8c 2cddbc9
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:17:36 2019 -0700

    Merge branch 'use-free' of https://github.com/adurdin/stb into working

[33mcommit eddae8cc9830413b6beb603deddbedda6d995f3e[m
Merge: 7638200 1034f5e
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jun 17 05:15:18 2019 -0700

    Merge branch 'master' into working

[33mcommit fad8903fe87fc5614e005f2a09899138b2917bca[m
Author: Vinh Truong <vinhphuc.truong@gmail.com>
Date:   Sat Jun 1 12:08:59 2019 +0300

    Credits

[33mcommit 96021689c87ea2f05a44fc2cd07e69ba0e8f42f8[m
Author: Vinh Truong <vinhphuc.truong@gmail.com>
Date:   Sat Jun 1 12:07:19 2019 +0300

    hmlen and hmlenu now returns 0 on NULL pointer

[33mcommit 2cddbc934d4eb607e5421b2cbd0778c3dae764ab[m
Author: Andy Durdin <me@andy.durdin.net>
Date:   Mon May 27 11:14:17 2019 +0200

    stb_ds: STBDS_REALLOC and STBDS_FREE only need to be defined for the implementation.

[33mcommit 6b2fb7702f9e0ec87f1842c8d28ad5a522f842bc[m
Author: Andy Durdin <me@andy.durdin.net>
Date:   Mon May 27 11:07:30 2019 +0200

    stb_ds: Allow STBDS_REALLOC and STBDS_FREE defines to customize memory management.

[33mcommit 5a2a8e882fc317b43005f403c38a3b176585d99d[m
Author: Andy Durdin <me@andy.durdin.net>
Date:   Mon May 27 11:04:28 2019 +0200

    stb_ds: Use free() instead of realloc(x,0). Fixes #768

[33mcommit 4a4c9deaac011fd307e15e7efc4a4debccdcdbe7[m
Author: BlackMATov <blackmatov@gmail.com>
Date:   Wed May 15 14:12:52 2019 +0700

    stb_image: fix warning (unused parameter ‘bpc’)
    
    Fixes issue #745.

[33mcommit 6bde00651c05fb95f3d1880cd419fc127f233fbf[m
Author: Martin Stensgård <mastensg@mastensg.net>
Date:   Sat May 4 23:11:35 2019 +0200

    stb_textedit: fix typo: STB_TEXTED_K_RIGHT

[33mcommit 1034f5e5c4809ea0a7f4387e0cd37c5184de3cdd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 4 08:19:18 2019 -0700

    add stb_include.h

[33mcommit f7d1cd581e09fc559cf6d400ec707ab3bc70e0b0[m
Author: Brotcrunsher <brotcrunsher@hotmail.de>
Date:   Tue Apr 30 16:30:03 2019 +0200

    Allowing Compound Glyphs with `numberOfContours < -1`
    
    While it is recommended that the numberOfContours are set to -1 for compound glyphs, it is allowed to have any negative value. Source: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6glyf.html
    
    However, I don't know if this happens in practice.

[33mcommit 4e0c494515f6cbe202b7357e6fd2de3f8bc9da62[m
Author: Georgy Macharadze <gmacharadze@elvees.com>
Date:   Mon Apr 22 14:06:05 2019 +0300

    stb_image: fixed 'out' nulled but not freed upon failure
    
    If realloc fails it returns NULL and out pointer becomes invalid. To
    fix this it is necessary to store realloc return value in temporary
    pointer and then compare it with NULL. If it equals NULL then return
    error and source pointer will still valid.
    
    This error was caught by cppcheck:
    Common realloc mistake: 'out' nulled but not freed upon failure.

[33mcommit 0a1016331c20944cec1634bd8b615240f93e41dc[m
Author: Chris Young <chris@unsatisfactorysoftware.co.uk>
Date:   Tue Apr 9 15:40:04 2019 +0100

    Add functions to extract SVG glyphs from font.
    The fucntions are:
    stbtt_GetCodepointSVG - provides a pointer to the SVG data in the supplied argument, and returns the length of this data
    stbtt_GetGlyphSVG - As above but takes the glyph index instead of the codepoint
    Note that the returned data may be deflate compressed.

[33mcommit 48ffc6bc5576a716c5c105f7fb4f8b8d7ea45357[m
Author: Łukasz Ptak <StylishTriangles@users.noreply.github.com>
Date:   Sat Mar 16 23:00:14 2019 +0100

    Fix gcc warning: expression always true
    
    stb_image.h:5113:18: warning: comparison of unsigned expression >= 0 is always true [-Wtype-limits]
        STBI_ASSERT(v >= 0 && v < 256);

[33mcommit 06374082843275af71e1ccc4ca28e13fe3e51ed7[m
Author: Randy <randy408@protonmail.com>
Date:   Tue Mar 12 00:59:20 2019 +0100

    fuzz: fix error handling

[33mcommit af516b99ffdd3b01c7a77b1673a871aa7503d761[m
Author: Randy <randy408@protonmail.com>
Date:   Tue Mar 12 00:14:16 2019 +0100

    fuzz: remove some chunk identifiers from stb_png.dict
    
    these chunks are not parsed

[33mcommit cd797f81167b6b1b1229577d5764b0ca1fb0b039[m
Author: Randy <randy408@protonmail.com>
Date:   Mon Mar 11 23:56:45 2019 +0100

    add fuzz target, dictionary, iphone png's

[33mcommit a5b663f1b0c28dd513b00ed5d0f0463308ff6dfc[m
Author: rgriege <rgriege@sbcglobal.net>
Date:   Thu Mar 7 19:48:23 2019 -0600

    stb_truetype: update contributors list

[33mcommit 8ac257b00f93861aa6357b8aa288f0e7eaaeece8[m
Author: rgriege <rgriege@sbcglobal.net>
Date:   Thu Mar 7 19:32:19 2019 -0600

    stb_truetype: limit to 1 missing glyph in texture
    
    When calling stbtt_PackFontRanges, multiple missing glyphs in the range
    of codepoints will create multiple copies of the font's missing glyph to
    be added to the pixel buffer.  Instead, the first codepoint that maps to the missing glyph will add it to the pixel buffer, and all subsequent glyphs will simply copy the stbtt_packedchar data to reference the same region of the buffer.
    
    This does NOT prevent duplication in multiple calls to stbtt_PackFontRange(s) - that would require modifying the packing context, which could be nice but is a bit more intrusive.

[33mcommit f3ca0dd5ae37f53287f99e75b4dedce2ea74a99b[m
Author: kaesve <mail@kaesve.nl>
Date:   Wed Mar 6 18:14:03 2019 +0100

    Remove redundant scale check in stbtt_GetGlyphSDF

[33mcommit 7638200f0bf1939360c4ab957358b2329abc4e3b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 23:22:06 2019 -0800

    Remove old documentation re: SECURE_CRT

[33mcommit 2c2908f50515dcd939f24be261c3ccbcd277bb49[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 15:08:53 2019 -0800

    update version numbers

[33mcommit d940053a01e0e0c634da4189ed85aef801c62ba1[m
Merge: 8cf9f5a a0b521f
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 14:56:00 2019 -0800

    Merge branch 'master' into working

[33mcommit 8cf9f5adb49aa4d2a229b5fbeb3d60db35ce865d[m
Merge: 1737c34 caf9608
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 14:52:49 2019 -0800

    Merge branch 'master' of https://github.com/rsachetto/stb into working

[33mcommit 1737c342e2a8d1371ec06d46664d2eab2875f1f6[m
Merge: 3b5ffbe 6570d6a
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 14:52:20 2019 -0800

    Merge branch 'fix_issue-656' of https://github.com/rygorous/stb into working

[33mcommit 3b5ffbe31c8c4d4e1754380f6086bbeb4884477b[m
Merge: a2cd79b d6a5981
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 14:51:34 2019 -0800

    Merge branch 'fix_issue-608' of https://github.com/rygorous/stb into working

[33mcommit a0b521fcf2bfbc88cf188a5d0af1a1cf47fe4d99[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Mar 4 14:45:06 2019 -0800

    no warnings when compiling /W3
       compiling all test cases and compilers in test.sbm
       Compilers:
         32-bit:
           VS2015
           VS2013
           VS2008
           VC6 (1998)
           clang-cl 9.0.1
         64-bit
           VS2015
           clang-cl 9.0.1

[33mcommit 96b4748d57b1509748ca43c71d18b158df6ebdb0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Mar 3 21:40:18 2019 -0800

    update test_ds.c

[33mcommit 30496e22d72d1024706f0f7a5702e729c034debc[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Mar 3 21:39:46 2019 -0800

    add new test files

[33mcommit b8960f32b807ad2404d4f09256dc86e00a5c6fdb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Mar 3 21:36:15 2019 -0800

    stb_ds: major string hash fix, minor other changes
      - arena and strdup string hashes were badly broken due to not setting up default slot correctly
      - tweak use of seed in 4-byte and 8-byte hash functions to hopefully be slightly stronger
      - a few internal #ifdefs for performance tuning

[33mcommit a2cd79b8ffc3fd8b7fb3bcfd1235f5166e5d550a[m
Author: kroko <code@kroko.me>
Date:   Sun Mar 3 18:48:32 2019 +0200

    fix comma warnings when building with -Wcomma

[33mcommit d6a598186cd226a77c0c63acf85487966b7bd2a9[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Mar 1 19:56:53 2019 -0800

    stb_image: Pacify some MSVC warnings.
    
    Convince the compiler's dataflow analysis that yes, we are not
    reading uninitialized values of coutput.
    
    Fixes issue #608.

[33mcommit 6570d6a825e2982a4f1c9ae7173a737eed4dd6f0[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Mar 1 19:47:59 2019 -0800

    stb_image: Make GIF reader validate image size.
    
    I must've missed it when I did this for the other image loaders.
    Either way, combined with the previous checkin, this should fix
    issue #614 properly.
    
    Fixes issue #614.

[33mcommit 50b1bfba583b12ceb23ef949567bdd914461e524[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Mar 1 19:22:44 2019 -0800

    stb_image: Fix multiple bugs in GIF decoder.
    
    1. Check not just g->out allocation for failure.
    2. If an image descriptor specified a 0-width image, this could be
       used to produce an out-of-bounds write.
    3. Fix memory leak in case an error occurs during decoding.
    
    Fixes issue #656.

[33mcommit caf960882650c77c3ebc59ea7739f5e9dc947420[m
Author: Rafael Sachetto <rsachetto@gmail.com>
Date:   Fri Mar 1 14:04:31 2019 -0300

    Adding arrpop macro to stb_ds.h

[33mcommit 89bccdd5676b2c6c718868cef98b8c6a1f9a577e[m
Author: Rafael Sachetto <rsachetto@gmail.com>
Date:   Tue Feb 26 09:37:16 2019 -0300

    Small documentation correction

[33mcommit 72990efc3e4e27fbd4b1130bb11353ef7ea2e2e6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 13:49:37 2019 -0800

    test updates for test_ds unit testing

[33mcommit f9133c36771b2ea7358951a25ecd27d70cbb90ea[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 13:48:41 2019 -0800

    stb_ds v0.3: fixes for compiling client code in C++
       add missing _wrapper suffixes
       disable clang rvalue support in C++
       disable unit tests in VC6 C++
       other tweaks

[33mcommit 39c05598a9eded170e39f2bb4a75b132897d976a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 12:05:38 2019 -0800

    Update stb.h version number

[33mcommit 0f9254357c08efdca57950a3d136ee45c283d3dd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:49:12 2019 -0800

    update version numbers

[33mcommit c963e40972825ca2165464dfba32dae44b59a45c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:48:42 2019 -0800

    update version numbers

[33mcommit a4111af960a8b23167f9ccee241e329229adade9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:41:58 2019 -0800

    update readme

[33mcommit 1aeb8ec201afa5f7e89c7527c0b1b31756f8796c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:40:33 2019 -0800

    stb_ds: fix shift warnings in later VS compilers

[33mcommit e704ed0efb7ce18c59087e7dacbd7b57014597dd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:17:27 2019 -0800

    update tests and project files for stb_ds

[33mcommit 477471d9a872d46e0c85cffcddf48ad179c9e5f1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:16:35 2019 -0800

    add stb_ds.h and tests

[33mcommit aeec66c6ec0abe22a420ec13af49086b1697e8f6[m
Merge: 9d8a9e7 0666554
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:13:03 2019 -0800

    Merge branch 'randlong' of https://github.com/flibitijibibo/stb into working

[33mcommit 9d8a9e7f162f82383fcaf1729901ece6a9dd871e[m
Merge: 742056d ae431d7
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:11:37 2019 -0800

    Merge branch 'fix_issue-701' of https://github.com/rygorous/stb into working

[33mcommit 742056dee952d92dd92c6ec906975b59febded74[m
Merge: 5fe7fb5 bbbdc1e
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:11:14 2019 -0800

    Merge branch 'fix_issue-705' of https://github.com/rygorous/stb into working

[33mcommit 5fe7fb52f246279073b1a6edc87d4585decf77cc[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Feb 25 11:10:54 2019 -0800

    various fixes for clang
    also fix a comment typo

[33mcommit 5715e6faafffd823171a7af150b6cc7538e6b2d1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 24 04:37:37 2019 -0800

    Makefile: update how to build image_write_test

[33mcommit 2ce93bf1d8341b78a4269a3e5df5cb07f33b64c6[m
Merge: 57c7029 af43e6b
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 24 04:27:18 2019 -0800

    Merge branch 'fix_issue-707' of https://github.com/rygorous/stb into working

[33mcommit 57c7029166d3c2d94f2905bd3371d5307435f927[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 24 04:22:47 2019 -0800

    test_image_write.c: change from standalone to integrated with image_test.c

[33mcommit ae431d75e0b306ff47c2a165e9740585a32571fa[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Feb 23 05:46:14 2019 -0800

    stb_rect_pack: Fix two bugs.
    
    stbrp__skyline_find_best_pos didn't correctly handle rects too
    large to ever fit inside the context. Since that function also
    pads the width up to a multiple of the alignment, it makes the
    most sense to do that check right after (but before entering
    the main packing loop).
    
    While we're here, also fix an off-by-1 bug in the best-fit
    heuristic where it didn't want to use the last row in
    certain cases.
    
    Fixes issue #701.

[33mcommit af43e6b00688648072c29442320a016f49d29a5a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Feb 23 05:32:27 2019 -0800

    stb_truetype: Fix warning in comment.
    
    Replace ASCII art with slightly crappier ASCII art that is not
    going to make compilers complain about trailing backslashes.
    
    Fixes issue #707.

[33mcommit bbbdc1e811bc55061978615724affaab97919d3a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Feb 23 05:25:47 2019 -0800

    stb_image: Fix typo in comment.
    
    Fixes issue #705.

[33mcommit e0ee0de26cfb142cb113f90948d05a8d2e9f69c0[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Feb 23 05:18:14 2019 -0800

    tests: Add simple image_write_test smoke test

[33mcommit 980add97251091ec5b527aa343673b30a77022be[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Feb 23 05:17:37 2019 -0800

    stb_image_write: Fix JPEG writer bug.

[33mcommit 0666554276aa23bcd9b7fe5592da64b68b924a25[m
Author: Ethan Lee <flibitijibibo@gmail.com>
Date:   Mon Feb 18 10:53:26 2019 -0500

    stb.h rand: A few more long->int fixes

[33mcommit 59e9702be5bfc0061e756c7beab7dcd3d363400d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 10:24:27 2019 -0800

    update readme

[33mcommit 63b59b46b03c7de310009383dbdf9c9d54f3ef3e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 10:03:00 2019 -0800

    update version numbers

[33mcommit a23f466de022f07441beaa3440abff46cd147bfa[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:49:08 2019 -0800

    "long int" => "long"

[33mcommit 6244febf5f0c9b6147ba682d44a7115f38829fd9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:33:54 2019 -0800

    stb_truetype: tweaks to codepoint-missing packing

[33mcommit f11f1e801a9f6de7783715b3e0ad4b04156e33ba[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:23:01 2019 -0800

    stb_sprintf: credits

[33mcommit 08759eb405e9c2704d16e05f70374814b4b56353[m
Merge: 8cf07e8 eccee04
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:22:06 2019 -0800

    Merge branch 'fix-sprintf-int-size-1' of https://github.com/account-login/stb into working

[33mcommit 8cf07e85c8b64841981e35cd005e2fcb0762eec7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:21:17 2019 -0800

    rename stbtt_PackSetSkipMissingGlyphs to stbtt_PackSetSkipMissingCodepoints

[33mcommit c35d1dd8ad932b2b4dc68ba5b933048addaf99d9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:20:11 2019 -0800

    stb_truetype: runtime selection of skipping missing codepoints

[33mcommit eaf78c10b61740d73757a2c4ac78992df0355537[m
Merge: 9092c04 886cca8
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:04:23 2019 -0800

    Merge branch 'truetype-skip_missing_glyphs' of https://github.com/ocornut/stb into working

[33mcommit 9092c0487de6fef52719cef3094f94caf85d10ad[m
Merge: feb9de3 7463635
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:04:00 2019 -0800

    Merge branch 'working'

[33mcommit feb9de355d52eb90abda31cd6883d944e6fe06ca[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 09:03:27 2019 -0800

    stb_image_write: add missing 'static' on internal functions

[33mcommit 7463635e52b19ae3a7c7880dbb31dc135f8f249a[m
Merge: 9643f6b d156642
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:53:19 2019 -0800

    Merge branch 'patch-3' of https://github.com/NuklearBomb/stb into working

[33mcommit 9643f6bd98be22e11cfcb82866edc60827b6c17d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:45:19 2019 -0800

    stb_sprintf: fix unaligned digitpair[], fix some signed-right-shifts

[33mcommit 82310cc5ff4317bf2bbc4eaaa30ebbe213d32f2f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:44:39 2019 -0800

    stb_sprintf: fix unaligned digitpair[], fix some signed-right-shifts

[33mcommit d1dc3fe89c35508db224ed4155ecd56a78d2e2ab[m
Author: Kevin Croft <krcroft@gmail.com>
Date:   Sun Nov 18 19:07:55 2018 -0800

    Fix return typo, disambiguate else, and check for the complete fishead identifier

[33mcommit 604b9367ee7a77aeff916a6bb5a9ee9601d72c02[m
Author: Kevin Croft <krcroft@gmail.com>
Date:   Sat Nov 17 21:42:30 2018 -0800

    Add detection for Ogg skeleton metadata

[33mcommit 38f86fc4618e6a45b34fb78e1ae1816e3ce73991[m
Merge: ddccc72 610a976
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:34:39 2019 -0800

    Merge branch 'fix-leakcheck' of https://github.com/Clownacy/stb into working

[33mcommit ddccc72c5bb5325ecadcb96b6b5b70bed2d72508[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:13:56 2019 -0800

    stb_image_write: optimize other PNG loops besides previous merge

[33mcommit d27796b5855f7e8e7cf2b938f2266d27d1a74e4e[m
Merge: 619cdb6 60a5755
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 08:11:38 2019 -0800

    Merge branch 'stb_image_write_optimization' of https://github.com/jarnoh/stb into working

[33mcommit 619cdb6a3bf317f296d7314e12965cf9aa0558d0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:53:28 2019 -0800

    stb_sprintf: fix 32 vs 64-bit sizes for format widts j/z/t

[33mcommit 6e7e5c5787892ae3b17dedf6076e29ef90dcb71d[m
Merge: 694b61f 05b45da
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:41:53 2019 -0800

    Merge branch 'fix-unaligned' of https://github.com/stefano-zanotti-88/stb into working

[33mcommit 694b61fcb105a3d2206bfe31fedae0ca74184f77[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:39:46 2019 -0800

    stb_image: remove non-ASCII character from credits

[33mcommit 0aa5984b6adcfe98afa64c466d76543b52e0e259[m
Merge: f9d9a41 f65ed67
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:39:03 2019 -0800

    Merge branch 'remove-assert' of https://github.com/rombankzero/stb into working

[33mcommit f9d9a419a9e2610f3fc29a3eba1acde2c8e4e290[m
Merge: db691f0 e64d4f8
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:33:00 2019 -0800

    Merge branch 'optimize_stbi__ldr_to_hdr' of https://github.com/technik/stb into working

[33mcommit db691f0c6909781e86db5ac5bacde9a6bef87da6[m
Merge: 5428c40 5d90a83
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:30:39 2019 -0800

    Merge branch 'fix_1bit_bmp' of https://github.com/plzombie/stb into working

[33mcommit 5428c408704d73e3e43e22c63a47d30bd5070b4e[m
Merge: 9bb4bc1 94e418b
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:28:41 2019 -0800

    Merge branch 'textedit-undo_char_position_type' of https://github.com/ocornut/stb into working

[33mcommit 9bb4bc1db4aaf515b843f64e8a10b345bc7e888c[m
Merge: 79a7719 05a8de3
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:27:42 2019 -0800

    Merge branch 'patch-1' of https://github.com/sherjilozair/stb into working

[33mcommit 79a7719c37387a4f8e775bb9471966c4dd89319e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:20:58 2019 -0800

    stb_image: fix d1252e1bb9fe6bdfad9f75ae626f9abdef5b4be1 for building in C

[33mcommit 7056eae4ae5302ff2b9e913b2dd684704cc5730d[m
Merge: d1252e1 a66dd42
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:19:18 2019 -0800

    Merge branch 'issue-609' of https://github.com/dp304/stb into working

[33mcommit d1252e1bb9fe6bdfad9f75ae626f9abdef5b4be1[m
Merge: 476c1f8 eee50c0
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:17:05 2019 -0800

    Merge branch 'master' of https://github.com/ab-cpp/stb into working

[33mcommit 476c1f89a237871571471edbf38d7b6fbb590b33[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:01:23 2019 -0800

    stb_image_write: fix the previous fix (incorrectly labelled as stb_image)

[33mcommit aa223d96934efb85cfe6fae46d9a639b15988840[m
Merge: ba5fc49 ebcae5b
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 07:00:59 2019 -0800

    Merge branch 'patch-1' of https://github.com/mastensg/stb into working

[33mcommit ba5fc494b486e8f78ead0eb958bf341956edcef1[m
Merge: e5d4d6f 756166e
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:58:18 2019 -0800

    Merge branch 'master' of https://github.com/WARP-LAB/stb into working

[33mcommit e5d4d6fcce00ba8c4ec2ca0dec4c0d0b804d89fb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:58:00 2019 -0800

    stb_image; optimize row computation in PR

[33mcommit b2bde485a2b1367450a5fe007038de6073cb75c3[m
Merge: 09998eb 1ad30e4
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:48:44 2019 -0800

    Merge branch 'stbiw-fix-jpeg-flipping' of https://github.com/DanielGibson/stb into working

[33mcommit 09998eb596a1a618b69ecf2acb1a2de4f6aeab7c[m
Merge: ff1eb8b cc99df4
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:05:47 2019 -0800

    Merge branch 'truetype-comment' of https://github.com/ocornut/stb into working

[33mcommit ff1eb8b8d47e82b4a558874c53322342d709e802[m
Merge: 94f93a8 f685ee4
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:03:48 2019 -0800

    Merge branch 'fix_stbi_write_hdr_core' of https://github.com/poppolopoppo/stb into working

[33mcommit 94f93a86e7bae24015ae1ae335a74b3fdb08908a[m
Merge: f82dbd6 4716080
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 06:02:51 2019 -0800

    Merge branch 'truetype-warnings' of https://github.com/ocornut/stb into working

[33mcommit f82dbd638c6867a3815f92275d2343c32f8297a0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 05:55:03 2019 -0800

    windows unicode: don't malloc buffers, add explicit STBI_WINDOWS_UTF8 #define

[33mcommit ae773aa438830e9bf389b090cd105864e7904d8a[m
Merge: 841c8b0 d0ae424
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 05:07:14 2019 -0800

    Merge branch 'unicode-file-support' of https://github.com/jrsmith17/stb into temp

[33mcommit 841c8b0f55348c2f1b7ab88c26d3a13ef251bd08[m
Merge: 3005bcf eb3c5db
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 05:01:35 2019 -0800

    Merge branch 'rectpack-warnings' of https://github.com/ocornut/stb into working

[33mcommit 3005bcfe87ed94036584bcd42742fd794edd40a4[m
Merge: cc53512 622b3ad
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 05:00:12 2019 -0800

    Merge branch 'misc-typos' of https://github.com/luzpaz/stb into working

[33mcommit cc53512cb95bf99dd6bebf30c549474d7de926c4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:59:05 2019 -0800

    added integer seed to noise function, use it in multi-octave noises

[33mcommit ca980dd2dce7329c6fc0b546d258dfab235edfeb[m
Merge: a28a6b1 15685cc
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:54:14 2019 -0800

    Merge branch 'perlin' of https://github.com/Auburns/stb into working

[33mcommit a28a6b126b4917c9ca8f47d2ad27aa6f71cebcef[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:42:32 2019 -0800

    tests: 64-bit fixes, fix typo in image tests

[33mcommit 27460c23a6b9d2bb9da472b10f288d92f27ce150[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:41:26 2019 -0800

    stb_truetype: allow getting font metrics without explicitly opening file

[33mcommit 9f1ef73e9622c7c2490d73e96520e5feef9ee530[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:40:32 2019 -0800

    stb_sprintf: minor reformatting

[33mcommit 061422f5808b1e577be711304ece8c28bc50275e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:39:51 2019 -0800

    fix non-fastpath BMP pixels with bit 31 set when asserts are on

[33mcommit d85e5946540fca54a3c6bb4d2633817d489e58e7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 7 04:33:18 2019 -0800

    various fixes:
      add stb_intcmprev
      add stb_uidict
      fixes to stb__dirtree_scandir
      change rand functions from unsigned long to unsigned int so they're 32-bit on Linux as well

[33mcommit eee50c079da05052ee5ba5d08057d5a86c9aac27[m
Author: Andrew Beatty <abeatty@facegen.com>
Date:   Thu Feb 7 07:30:42 2019 -0500

    Update to STB conventions

[33mcommit d156642036d80349426b9e189a09213aa72da864[m
Author: NuklearBomb <33639078+NuklearBomb@users.noreply.github.com>
Date:   Tue Jan 29 01:43:31 2019 -0500

    Silence warning 'tc' may be used uninitialized in this function

[33mcommit ccc4b3716af627eb490eeeb5a371b413385aabad[m
Author: Andrew Beatty <abeatty@facegen.com>
Date:   Tue Jan 22 19:31:46 2019 -0500

    fix compiler warnings and const error

[33mcommit eccee04e5a6cc125b24d2d0a2dd6c8d46bc1d51d[m
Author: root <account-login@users.noreply.github.com>
Date:   Fri Nov 9 22:49:33 2018 +0800

    stb_sprintf: fix integer size for %ld

[33mcommit 610a976b83d38fb17d57bc895d57b91a1c2bb422[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Fri Nov 2 00:20:31 2018 +0000

    Removed redundant check

[33mcommit 3e6370720e4811d5fc10fb09f1f0efd67ec04a69[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Fri Nov 2 00:13:40 2018 +0000

    Fixed STB_LEAKCHECK_SHOWALL
    
    5a5cf7f9ba936bb931ecde8df9465e250132fb75 derped

[33mcommit 359bb10d3cfd72f9bb2b308b65b022b4a0a6c3a5[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Thu Nov 1 23:55:07 2018 +0000

    Try to clean up stblkck_internal_print a little
    
    No need to pass all those parameters. Also long longs aren't 8 digits
    long. I don't know how to find out the length of a size_t at
    compile-time in a way I can use with a format specifier.

[33mcommit 79dc50bb79bfa0caeeef62dfb8b2c4fe09926d29[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Thu Nov 1 23:49:17 2018 +0000

    ...Actually, I don't think these are meant to be here
    
    Looking at 501812f307cd4b7609a1c6226f26bb7780cf08b8, the entire point
    was to *replace* these lines. That explains why they lacked braces
    earlier.

[33mcommit f7d9426f8e3f56a2384a4ced1c2f051cb7699383[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Thu Nov 1 23:25:47 2018 +0000

    Add a way to use %zd on MinGW(-w64)
    
    This is suggested here:
    https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/
    
    Compared to using __USE_MINGW_ANSI_STDIO, this prevents those annoying
    warning about "unsupported" format specifiers.

[33mcommit 248604ffbcd050259024e145428d8345da1769f3[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Thu Oct 18 13:29:55 2018 +0100

    Shut up GCC -pedantic warnings

[33mcommit 80b89cf6c8a6581245d65bc8d3fe67412c0f1bf7[m
Author: Clownacy <Clownacy@users.noreply.github.com>
Date:   Fri Oct 12 11:37:06 2018 +0100

    Fixes for stb_leakcheck.h
    
    I ran into a couple of problems while trying to use this with my
    program:
    
    My compiler (MinGW-w64 GCC 8.2.0) complained about not recognising %lld
    format specifiers.
    
    The compiler also warned about non-guarding 'if's. I ignored it at
    first, but then I noticed my program crashed when it ran
    stb_leakcheck_dumpmem. Making the 'if's guard fixed that.
    
    After that, the lib worked until I changed how it was included: instead
    of tacking a debug-only #include at the start of every file, I switched
    to using GCC's '-include' option to force-include it in every file. But
    doing that gave me errors about size_t not being defined. And after
    fixing that, I instead got errors about the #defines messing with
    stdlib.h. So to fix those I made the declaration-only part of the header
    include stdlib.h.

[33mcommit 60a5755478b4a8a564e20948daf926a1bb0a1d74[m
Author: jarnoh <jarnoh@komplex.org>
Date:   Thu Jul 26 17:37:50 2018 +0300

    use simple memcpy if png filter=0

[33mcommit 7a02732eb3cb59d9d255455a1fde92e5038052fa[m
Author: jarnoh <jarnoh@komplex.org>
Date:   Thu Jul 26 17:10:40 2018 +0300

    allow STBIW_CRC32 override default crc32

[33mcommit 05b45da6291e3ccd1320454ea469fd335a373f8c[m
Author: Stefano Zanotti <7887495+stefano-zanotti-88@users.noreply.github.com>
Date:   Wed Jun 27 10:37:00 2018 +0200

    stb_sprintf: fix unaligned access
    
    Fix an unaligned 32-bit access even if STB_SPRINTF_NOUNALIGNED was defined.

[33mcommit f65ed67e89531c9ff6b36cf8974b0d9908a782cd[m
Author: rombankzero <bogomancer@gmail.com>
Date:   Thu Jun 21 16:51:30 2018 +0300

    stb_rect_pack: Remove always-true assert

[33mcommit 5d90a8375a1393abc0dc5f8cc9f1ac9fd9ae6530[m
Author: Mikhail Morozov <misha1294@rambler.ru>
Date:   Fri Jun 8 07:29:00 2018 +0300

    stb_image: fix 1-bit bmp

[33mcommit e64d4f89eb25b9f4fbf3121bb43c0fca225fbdbc[m
Author: Carmelo Fernandez Aguera <carferna@microsoft.com>
Date:   Thu Jun 7 17:10:00 2018 +0100

    Added myself to the list of contributors.

[33mcommit f1f077b2722f55e158cba020f0312ee2d13c463a[m
Author: Carmelo Fernandez Aguera <carferna@microsoft.com>
Date:   Thu Jun 7 16:18:23 2018 +0100

    Break a for loop into two parts and get an if out of the loop.

[33mcommit 94e418bb7b9120e330c199798eb0fd0c272b0e4f[m
Author: Omar <omar@miracleworld.net>
Date:   Tue Jun 5 22:38:04 2018 +0200

    stb_textedit: fixed undo/redo after pasting large amount of text (over 32 kb). Redo will still fail when undo buffers are exhausted, but text won't be corrupted. Fix #620.

[33mcommit 05a8de3b86812d9e5849e69f04e19e5df91cdc0c[m
Author: Sherjil Ozair <sherjilozair@gmail.com>
Date:   Sat May 26 05:37:55 2018 -0400

    Update stb_tilemap_editor.h

[33mcommit a20ccd4a7d975a80db748c621d173a2f059f1fd7[m
Author: Sherjil Ozair <sherjilozair@gmail.com>
Date:   Fri May 25 22:46:47 2018 -0400

    Update stb_tilemap_editor.h

[33mcommit a66dd42d4cc3a41d1ff491bbf3555d650f5e7e7a[m
Author: Dobe Peter <dobe@iit.bme.hu>
Date:   Wed May 9 23:24:41 2018 +0200

    stb_image: fix three unused function warnings

[33mcommit 886cca8f154288f47941b5aa2c58c9dae0d004ef[m
Author: Omar <omar@miracleworld.net>
Date:   Mon May 7 16:29:36 2018 +0200

    stb_truetype: stbtt_PackFontRanges skip missing glyphs.

[33mcommit ebcae5b13073f8946827353028d628c0298e5af9[m
Author: Martin Stensgård <mastensg@users.noreply.github.com>
Date:   Sun May 6 12:38:11 2018 +0200

    stb_textedit: remove double initialization
    
    `clang-scan` found this

[33mcommit e0a0328b43afb8a19da7dbacf302b66a8dfdbd6d[m
Author: Marcin Wojdyr <wojdyr@gmail.com>
Date:   Sun Apr 29 16:50:25 2018 +0100

    add tests to tests/test_sprintf.c

[33mcommit e5254a7fdef59b0f02a4f3984d887bdcadf09f8e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Apr 27 04:47:03 2018 -0700

    whoops, makefile for travis was no longer testing most libraries compiling

[33mcommit 756166e853a1d16a14fbc132384b98512cfce117[m
Author: kroko / Reinis Adovičs <code@kroko.me>
Date:   Wed Apr 25 15:19:29 2018 +0300

    fix comma warnings when building with -Wcomma
    
    Happens on standard Xcode Version 9.2 (9C40b) configuration (using Apple LLVM version 9.0.0 (clang-900.0.39.2)). Addresses https://github.com/nothings/stb/issues/515

[33mcommit 1ad30e4e7724ca8afc126b2c1088425d57a423bc[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Mon Apr 9 01:24:17 2018 +0200

    stb_image_write.h: Fix jpg flipping for non-multiple-of-8 sizes
    
    JPG always encodes 8x8 pixel blocks. If the input image does not have
    a width or height that's a multiple of 8, the last column or row is just
    used multiple times for the remaining pixels of the block.
    The original code first calculated p (the index into the pixel data)
    with the "imaginary" row/colum (that might be up to 7 pixels too far
    into each direction) and then subtracted the necessary amount of bytes
    it if row >= height or col >= width.
    That was a bit cryptic (IMHO), and didn't get more readable/obvious when
    vertical flipping was added - which introduced a bug, by not taking
    stbi__flip_vertically_on_write into account when adjusting p for
    row >= height...
    
    The code should be more obvious (and less buggy) now.
    
    This fixes bug #592

[33mcommit cc99df4b4879dd8db7d4a5ec3aa878c56c59d61e[m
Author: Omar Cornut <omarcornut@gmail.com>
Date:   Thu Mar 8 17:13:18 2018 +0100

    stb_truetype: added comment about stbtt_FindGlyphIndex() return value.

[33mcommit f685ee4e58cb8c611b2f9c5cc1e6422106cc2906[m
Author: PopPoLoPoPpo <frostiebek@gmail.com>
Date:   Tue Feb 27 00:08:45 2018 +0100

    Fix overflow in stbi_write_hdr_core()
    
    b056850ea9118b69325d973f8aef7f843527e299 left an additional multiplication by x,
    leading to overflow.

[33mcommit 4716080627fd982806bba06c1f53625f8db68a9a[m
Author: Omar Cornut <omarcornut@gmail.com>
Date:   Fri Feb 23 11:10:51 2018 +0100

    stb_truetype: fix unused variable warning when asserts are disabled.

[33mcommit d0ae4240610a63bf8367a19b59142ea6e28ab7d3[m
Author: JR <jrsmith17@gmail.com>
Date:   Tue Feb 20 21:38:00 2018 -0500

    Re added unicode filename support for stb_image and stb_image_write with whitespace issues fixed.

[33mcommit fa8fe305328f914d78719b60d17b8b8a664784d8[m
Merge: 9d9f75e e6afb9c
Author: Mikhail Morozov <misha1294@rambler.ru>
Date:   Tue Feb 13 18:01:46 2018 +0300

    Merge pull request #1 from nothings/master
    
    Update stb

[33mcommit eb3c5db96c7ace614533c095b835c1c9e18aced2[m
Author: Omar Cornut <omarcornut@gmail.com>
Date:   Tue Feb 13 11:21:10 2018 +0100

    stb_reck_pack: Removed unused assigned variables (under #ifdef _DEBUG wrap)

[33mcommit 622b3adad3c041885d5a37f47c49746ffdc0ee69[m
Author: luz.paz <luzpaz@users.noreply.github.com>
Date:   Mon Feb 12 14:54:17 2018 -0500

    Misc. comment typos
    
    Found via `codespell -q 3`

[33mcommit e6afb9cbae4064da8c3e69af3ff5c4629579c1d2[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:57:53 2018 -0800

    update readme

[33mcommit fa2a1d9b3be0733b222fc14a7428e81ce940c2a7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:57:40 2018 -0800

    stb_image version number

[33mcommit 0707304469dafff6d33c0502991f7470594e0267[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:56:13 2018 -0800

    update readme

[33mcommit 19850aa29abb0442434072552d34710e857d6272[m
Merge: af786f9 0c11c4f
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:56:08 2018 -0800

    Merge branch 'working'

[33mcommit af786f98833f478cdbf26e527c8e288db8cb1fa6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:55:27 2018 -0800

    update readme

[33mcommit 0c11c4f1b607cc4e189be8cc59337aba4e7bb4a4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:53:29 2018 -0800

    rework GPOS support for old non-declare-anywhere C

[33mcommit 6d59a4913ff20bdfcac6df3dd402800b2350cd54[m
Merge: cd62aa9 e460d1a
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:44:27 2018 -0800

    Merge branch 'stb-truetype-gpos-request' of https://github.com/danielmaciel/stb into working

[33mcommit cd62aa97143f00e47a0ef47968ae9071fdd69d56[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:42:05 2018 -0800

    docs

[33mcommit ac66307576973693366a6200c036801e6269d97b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:41:20 2018 -0800

    docs

[33mcommit b79c8458d3bc81d89b41a247caf09f07af64f81c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:29:53 2018 -0800

    stb_vorbis: avoid NaN due to uninitialized variable

[33mcommit 543ad0c11294051a51775d346bf660e2d87ba36e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:29:32 2018 -0800

    stb_image_write: tweak handling of STB_IMAGE_WRITE_STATIC

[33mcommit aeb2b4b64de878ce76447ad4481ea6ef682ab4d4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:19:45 2018 -0800

    tweak handling of STBIWDEF

[33mcommit dbf0fab1c73c9b983bc07025fc137e4e9a942b7b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:11:39 2018 -0800

    stb_image_write: credits

[33mcommit 2886b67f7f551f44cdc1251c49618a632d823563[m
Merge: 6382814 34f087c
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:09:07 2018 -0800

    Merge branch 'stb_image_write_png_filters_fix' of https://github.com/kosua20/stb into working

[33mcommit 6382814b8cfbd05fd0d53e182fd23a943430dec0[m
Merge: 4eef034 6ab920b
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:05:58 2018 -0800

    Merge branch 'image_write_variable_typos' of https://github.com/cap/stb into working

[33mcommit 4eef034d52d2f3e1c9b681e288436724ddc74aab[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Feb 11 11:05:20 2018 -0800

    stb_write_image: fix typos

[33mcommit 6ab920bb6aec30490ea68ab86fbdfb9f2aed9e24[m
Author: Cap Petschulat <zfcd21@gmail.com>
Date:   Mon Feb 5 15:28:04 2018 +0900

    stb_image_write: fix png compression level typos

[33mcommit 34f087ce4c5a0d7cb82db75ec504efdca73c48c2[m
Author: Simon Rodriguez <kosua20@gmail.com>
Date:   Sun Feb 4 20:12:20 2018 +0100

    stb_image_write: fix indexing error when computing PNG filters with the stbi__flip_vertically_on_write on.
    
    The PNG filters of the pixels row N are computed using row N-1 of the final image. If the image should be flipped when saving, this corresponds to row N+1 of the initial image.

[33mcommit a77d9213e4a9f670c5c5ea381152067ba3a63c60[m
Author: Sean Barrett <sean@nothings.org>
Date:   Thu Feb 1 03:53:17 2018 -0800

    stb_vorbis: no dealloca

[33mcommit a6796aee404108f185c2cf33f3db120849d479e2[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jan 31 10:46:31 2018 -0800

    test stb_lib

[33mcommit 0ba9ff6599083d0d482cb215886a7efd21fe0791[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jan 31 07:50:07 2018 -0800

    stb_image: fix unused variable warning

[33mcommit 15685cc4d4b51c9484d909a84c1273b19e0ed9b2[m
Author: Jordan Peck <jordan.me2@gmail.com>
Date:   Wed Jan 31 12:33:35 2018 +0000

    Removed seed from documentation

[33mcommit 6ba21df503354f447c900b188f71450be694f7ad[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 17:33:17 2018 -0800

    update dsp with new compile tests

[33mcommit 48168170a12e2a2f222f8df869bd8c6ce5305a51[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 17:05:57 2018 -0800

    stb_truetype: add STBTT_fmod

[33mcommit ca6548c30a35f5be87e35037f63fe1371422bbf6[m
Author: Jordan <jordan.me2@gmail.com>
Date:   Tue Jan 30 21:03:35 2018 +0000

    Changed gradient idx table to match previous implementation, removed seeds from public API

[33mcommit 73990fefe7e44fb12986173fdbd9e5b60ab6bb5e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:48:45 2018 -0800

    update readme

[33mcommit a9672961c96f2a985867db1905bafb378057fd4e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:45:59 2018 -0800

    more cases of STB_NO_HDR and STB_NO_LINEAR interfering

[33mcommit 40f43afe5609389fe581ff020ad733a070bf5564[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:40:17 2018 -0800

    tweak tests

[33mcommit 602e986824b90c4bb17605f4976985c2f5601f08[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:39:29 2018 -0800

    fix STBI_NO_HDR and STBI_NO_LINEAR to compile correctly even if you don't #include <math.h>

[33mcommit 085ba4b627a13f259dcb84f856768f605e4ac0aa[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:31:18 2018 -0800

    add compilation tests that have no other includes to avoid accidental dependencies

[33mcommit 01daa3a244d57b97993d2a9711943c09c0dc18af[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:29:31 2018 -0800

    stb_sprintf: fix size-only snprintf query

[33mcommit ccee11ad79f08f85af9444659529b8ba4c6d51d1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:28:37 2018 -0800

    stb_image: fix warnings

[33mcommit 3ac351f39dd7b5d46a6047705e48d57ed4ba3583[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 05:16:47 2018 -0800

    break out stb_lib.h

[33mcommit 06fedddb4d8610383a1d1df9a6bcfac92dc85a94[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Jan 30 02:56:16 2018 -0800

    fix stb_dxt.h; fix misspelled STB_DXT_IMPLEMENTATION in test jig

[33mcommit e460d1a8d8cce54eadcf585241d8c12fd14cd59c[m
Author: Daniel Ribeiro Maciel <daniel.maciel@gmail.com>
Date:   Thu Aug 24 15:22:52 2017 -0300

    Add basic GPOS kerning

[33mcommit f2974f6c1c579abd7f54f4a3271effb18c3996a8[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 15:21:12 2018 -0800

    update readme version number

[33mcommit 663deb3a43219c764c87a3591a55f5163c06230a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 15:20:54 2018 -0800

    redo lost stb_vorbis fixes

[33mcommit 7855d2dc8719d91da0ef7aa3d8053c35931d1d81[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 14:52:14 2018 -0800

    version numbers in readme

[33mcommit 67f588cbb5ceebbc136b21c0495e36f9d06908c5[m
Author: Jordan <jordan.me2@gmail.com>
Date:   Mon Jan 29 22:50:45 2018 +0000

    Added seed to perlin and fractals
    Removed broken wrap from fractals
    Used varied seeds for fractal octaves to remove artifact at origin
    Removed indicies table in favour of mod12 permutation table, this reduces gradient bias and gives 3% performance increase

[33mcommit dfff6f5e7cd412876fe6282f157c1928b99d1de9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 13:15:10 2018 -0800

    stb_image: fix assert macro usage; stb_vorbis: changelog

[33mcommit 476b4c7a72ef2c9e2b0f36a95171c735bdcba0cf[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 08:22:21 2018 -0800

    update readme

[33mcommit 037926ab74b0d420a1f760b6377aae7656b6dca5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 08:18:19 2018 -0800

    fix warnings, bad error handling

[33mcommit b2c2419b1bf03ec350b07fd2f122e7768252a30e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 08:14:53 2018 -0800

    stb_image: avoid arithmetic overflow in png case

[33mcommit 445473bdb5f7813487b6f8f808d3ae84801937da[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 08:03:56 2018 -0800

    stb_image_write: handle malloc failure in zlib

[33mcommit 4fd9019c0fd9088d1e288649372babc8e3ab6e16[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:57:23 2018 -0800

    stb_image: avoid signed left shifts

[33mcommit 74a21dc6158b7688bac8e1f375eef519b6401708[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:52:21 2018 -0800

    fix compiler warnings

[33mcommit 9b2522c3d53b16cefa99af660e1d0079cbaf4a9e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:48:12 2018 -0800

    stbi_is_hdr_from_file needs to reset file position

[33mcommit 87352fdcb55489b0e143e035942222dcf058e6c0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:44:54 2018 -0800

    stb_truetype: fix bug in handling of stbtt_hheap that could cause severe badness

[33mcommit db4d92891c78cdf32753b022b7081dd9a32d8aa6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:44:04 2018 -0800

    fix stb_sdict_for()

[33mcommit 3025377f4a465055e8359dc0513151331edff7c1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 07:23:54 2018 -0800

    fix stb_textedit redo, from omar cornut

[33mcommit b969dc38f38dead9a4492713c2158419056ac39d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 06:06:29 2018 -0800

    stb_image_write: fix for fopen_s failure case

[33mcommit 3f01acced4de5a3983ae590b0bea2de08f4eea3b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 05:39:48 2018 -0800

    stb_textedit: allow overriding key-input typedef

[33mcommit d808adb77f40c83c71a65981b61f1e8ec69fcbcb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 05:17:07 2018 -0800

    stb_dxt: fix bug with constant color & varying alpha

[33mcommit 76ec599c684b9028887095e5da34384b934718d9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 05:03:38 2018 -0800

    stb_truetype - remove duplicate definition

[33mcommit ee0ebfc79b8a8abe9cf7a63375c128d06b84c8df[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 04:59:32 2018 -0800

    version numbers

[33mcommit 5db03ef592ee32d861bd395f337a14bd7f180e5c[m
Merge: d74530c 094cb31
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 04:04:28 2018 -0800

    Merge branch 'master' into working
    
    Conflicts:
            stb_image.h

[33mcommit 094cb31ec8a84962654a89002825e69dde43b805[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 04:03:18 2018 -0800

    stb_image: compile as C; stb_image_write: credits

[33mcommit faf08e00183a9c7c13b0fbbde5091213f9223f21[m
Merge: 4254a9f 76d9e05
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 04:01:29 2018 -0800

    Merge branch 'stb_image_write_mscrt_errors' of https://github.com/xeekworx/stb

[33mcommit 4254a9f23798800c912608636ac94acd18cc7bb6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:59:48 2018 -0800

    stb_truetype credits

[33mcommit 8732cff6c455f321a56ffd2272e53dfccae35ee8[m
Merge: da4a7a1 5c2c826
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:59:17 2018 -0800

    Merge branch 'winding-lengths-warning' of https://github.com/RobLoach/stb

[33mcommit da4a7a1d6f762d73c13476281d5bedcafff846ff[m
Merge: ae00f3a 3a969eb
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:51:23 2018 -0800

    Merge branch 'patch-2' of https://github.com/wojdyr/stb

[33mcommit ae00f3a5f0253e553fc03beb7427a2dad6b1fdfa[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:50:42 2018 -0800

    stb_image credits

[33mcommit 1b9689cf77b94010951ba81a0e834902b642bdb9[m
Merge: f9d78c0 de75509
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:50:03 2018 -0800

    Merge branch 'feature/gif_frames' of https://github.com/tocchan/stb

[33mcommit f9d78c05a928a7a036da685615fb1f0768e06788[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:49:53 2018 -0800

    stb_image credits

[33mcommit edf35ad14cf93f0acd131fdad4a50b0d2ea2d487[m
Merge: 0bd0d04 4bffebc
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:43:08 2018 -0800

    Merge branch 'master' of https://github.com/jlnr/stb

[33mcommit 0bd0d049e77ee8f589f8068f62e5391509abc233[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:42:34 2018 -0800

    stb_image docs

[33mcommit ead2b3fe2c4551aae6b98b219099f930181a4697[m
Merge: 501e29b fcf0b99
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:38:04 2018 -0800

    Merge branch 'stbi_is_16' of https://github.com/anael-seghezzi/stb

[33mcommit 501e29b2451e514b60b1b7eea2535edbd6e39be7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:36:23 2018 -0800

    stb_truetype.h docs

[33mcommit 986a5eeeb1a3acdc71d65927177e731436f46c78[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:35:03 2018 -0800

    fix stb_truetype test file

[33mcommit 0b8b3f287657cdb02249d95feb517a367f699550[m
Merge: f228574 6e50ac7
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:32:11 2018 -0800

    Merge branch 'stb_truetype_fixes_20171104' of https://github.com/kphillisjr/stb

[33mcommit f22857495b546ee005f3bfc321637cbee07808df[m
Merge: 0b81a54 a981af5
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:29:59 2018 -0800

    Merge branch 'compile' of https://github.com/alculquicondor/stb

[33mcommit 0b81a543541a5c8ace96fc00075b8d5d261c84a4[m
Merge: 72ef9dc 1f2b427
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:29:01 2018 -0800

    Merge branch 'cff-type2-fixes' of https://github.com/dougallj/stb

[33mcommit 72ef9dcbadd37562cfe75f5ca3e0346954f129f1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:27:58 2018 -0800

    fix fall-through case warning, add credit

[33mcommit 8cc624142b260c069db2a10f586b30a79dd19f5e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:25:02 2018 -0800

    credits

[33mcommit 82f1929de5a76f70def29999ebd23c4f7fdf253c[m
Merge: da4b342 b6b43df
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:23:53 2018 -0800

    Merge branch 'patch-1' of https://github.com/darealshinji/stb

[33mcommit da4b342213b62d34d81e510f866cb43845ecdf3a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:23:45 2018 -0800

    credits

[33mcommit ab4fb5c38a4bb733d6b15c59d647374e86c39944[m
Merge: b0383fa 3501730
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:22:12 2018 -0800

    Merge branch '1bit_bmp' of https://github.com/plzombie/stb

[33mcommit b0383facf8f51bb03db3fa6daf79fc64f1e79564[m
Merge: 41cd8bb c06c9fe
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:20:21 2018 -0800

    Merge branch 'master' of https://github.com/lieff/stb

[33mcommit 41cd8bb527cc8a288b34fdea5b28d518db6a34f2[m
Merge: 5f1a73f c8245bb
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:19:34 2018 -0800

    Merge branch 'patch-1' of https://github.com/twoscomplement/stb

[33mcommit 5f1a73fe4e169a65e73657b1c302d43df98ef490[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:18:40 2018 -0800

    credits, tests

[33mcommit 9eb0e729500457bad24a61881c8966914ea42b11[m
Merge: e594652 2545eee
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:17:50 2018 -0800

    Merge branch 'must_make_clang_happy_as_clam' of https://github.com/croepha/stb

[33mcommit e5946524d73d9eb9fdb9e1174328836f6cb96b65[m
Merge: 3d7b425 7d80a8b
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:15:17 2018 -0800

    Merge branch 'patch-1' of https://github.com/wojdyr/stb

[33mcommit 3d7b4251f9c9a5f85c42b466232006364320a6b3[m
Merge: b48101c 2c7b00a
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 03:14:31 2018 -0800

    Merge branch 'png-ext-write' of https://github.com/akx/stb
    
    Conflicts:
            stb_image_write.h

[33mcommit b48101c971a5c564caf467481cd43d7be6b9f3b0[m
Merge: f541fa1 923c9c3
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:57:46 2018 -0800

    Merge branch 'update_stbi_jpg_dcoumentation' of https://github.com/Benjins/stb

[33mcommit f541fa17107c2ea51685182523445033c6abaf6c[m
Merge: 35a3bf4 747b8d8
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:56:43 2018 -0800

    Merge branch 'valgrind-fix' of https://github.com/rohit-n/stb

[33mcommit 35a3bf41e8f4436c601c4b57030f947fc6a33449[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:55:56 2018 -0800

    Integrate ZLIB changed from Daniel Gibson, fixup credits

[33mcommit 9de22e5a700d7d33b2cafc7055b7370fa317466f[m
Merge: 39241e4 be21113
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:53:25 2018 -0800

    Merge branch 'stbiw-png-compr' of https://github.com/DanielGibson/stb

[33mcommit 39241e492831b1e05aa1bafacbc937b189896251[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:53:14 2018 -0800

    update version number

[33mcommit b056850ea9118b69325d973f8aef7f843527e299[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:52:49 2018 -0800

    stb_image_write can flip images vertically

[33mcommit e371bd83f2dd641d7d8ef107622b4bbc9a2f8b88[m
Merge: 593c9b7 1394234
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:47:36 2018 -0800

    Merge branch 'sb_cpluscplus' of https://github.com/ZenToad/stb

[33mcommit 593c9b7192e81970caeefcd4d4868c524e8f0c32[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:30:34 2018 -0800

    rewrite stbi__shiftsigned to use a different, faster algorithm
    to avoid probelm with clang -O2 to outputting buggy code

[33mcommit 68f857727cd602e636ebf825ec3a47e42dc42b44[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:24:05 2018 -0800

    add stb_ucharcmp to stb.h

[33mcommit 244d83bc3d859293f55812d48b3db168e581f6ab[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 29 02:23:18 2018 -0800

    fix unchecked length in stb_vorbis that could crash on corrupt/invalid files

[33mcommit 76d9e05b2f0365786930350d1eadbffd4d5716b0[m
Merge: 841862a eb17d8a
Author: John Tullos <xeek@xeekworx.com>
Date:   Mon Jan 1 19:02:00 2018 -0600

    Merge branch 'stb_image_write_mscrt_errors' of https://github.com/xeekworx/stb into stb_image_write_mscrt_errors

[33mcommit 841862a6225c891d32d194267ba4b81f1499755a[m
Author: John Tullos <xeek@xeekworx.com>
Date:   Mon Jan 1 18:56:36 2018 -0600

    Fixed grammar, spelling issues in comments
    issue #533

[33mcommit eb17d8a6dd32a7b6ce8f345c75505df423be071a[m
Author: John Tullos <xeek@xeekworx.com>
Date:   Mon Jan 1 18:56:36 2018 -0600

    Fixed grammar, spelling issues in comments

[33mcommit 32a7d5ab68bd35455b24aa852d6d6b7d0f55b494[m
Author: John Tullos <xeek@xeekworx.com>
Date:   Mon Jan 1 18:54:26 2018 -0600

    Added STBI_MSC_SECURE_CRT to support newer MSVC compilers as optional
    For issue #533

[33mcommit 5e844ffe70ca88fe56777e73c4fe50b24cb722bd[m
Author: John Tullos <xeek@xeekworx.com>
Date:   Mon Jan 1 18:08:30 2018 -0600

    Using secure versions of CRT calls to avoid Microsoft Visual C/C++ compiler errors/warnings.

[33mcommit 5c2c826df9d8cc50df4eae1b6c807ef8d194848c[m
Author: Rob Loach <robloach@gmail.com>
Date:   Sun Dec 24 13:57:03 2017 -0500

    stb_truetype: Silence warnings of winding_lengths
    
    Coverty scan shows potential warnings of winding_lengths. Forcing it to be a NULL fixes the issue.

[33mcommit 3a969eb64c46326490f7307b834c71b601204b99[m
Author: Marcin Wojdyr <wojdyr@gmail.com>
Date:   Thu Dec 7 15:30:43 2017 +0000

    remove duplicated `pr = 0`
    
    avoid warning:
    Variable 'pr' is reassigned a value before the old one has been used
    caused by:
    
        fw = pr = fl = 0;
        ...
        pr = 0;

[33mcommit de75509b1c35f6d8a03c341364600922391d6b94[m
Author: Chris Forseth <christopher.forseth@gmail.com>
Date:   Mon Nov 27 23:42:13 2017 -0600

    Remove a nullptr

[33mcommit 03b4bbc5d2d51831baf6359c9527a1733de74cdd[m
Author: Chris Forseth <christopher.forseth@gmail.com>
Date:   Mon Nov 27 23:32:44 2017 -0600

    Fix a disposal flag mistype.
    Only clear to background color if index is non-zero.
    Fixed a the disposal test gif I was using - now renders properly (gif has no transparent set, but all renderers still considered it transparent.  Spec says 0 should be ignored if 0, but was confusing by saying it only in the context of the pal not existing.. but seems to be the case always.

[33mcommit 28c28b0bd23534f405938e29505fb47780fadd3d[m
Author: Chris Forseth <christopher.forseth@gmail.com>
Date:   Mon Nov 27 23:06:53 2017 -0600

    Per the contributor doc - added my name.   Noticed urraka also did some work here, so hopefully didn't step on any toes.
    
    - Fix an issue where the spec of the gif for restore to previous uses code 3, not 4.
    - To get results that worked - made an assumption that "clear to background" meant "revert back to what was there before I drew", where mode 1 would revert back to the previous frame [slightly different].  If I clear to background color instead, I ended up with large opaque squares in gifs that changes their transparent colour each frame.
    - Background color is supposed to be used only for pixels not rendered by the image, so took that to mean it only really affected the previous frame, or potentially any frame that used full disposal.  Since background color is allowed to be unspecified this is what lead me to believe I shouldn't use it for disposal.
    - Oh, also upped the codes table to 8192 as 4096 ended up being too small for a few of my test cases.
    
    Full disclaimer - I only read through the GIF format for this contribution, so competly could be misinterpreting the spec - but this gave me reuslts that matched Chrome.

[33mcommit 87a3143fb4ca2111d77b27edda2b91ae493cc9a5[m
Author: Chris Forseth <christopher.forseth@gmail.com>
Date:   Mon Nov 27 22:41:51 2017 -0600

    GIF Loading - multiple frames;
    - Allow loading a gif as multiple frames into a single buffer.  Each frame is a full image seperated by a (w * h * comp) stride.
    - Optionally, can pass in a pointer to a int, which will be filled with an array layers long contain ms for each frame.
    - Fix gif's not loading the initial transparent background
    - I believe also fix disposal rules for subsequent frames (though being somewhat inefficient with memory to do so)
    - Add a flip_vertical that takes into account slices as well.
    
    Compiled using VS2017, but nothing else as I'm not really setup for it.  Apologies.

[33mcommit 4bffebc5f0f1b69e1ce579cfffc24cc62c07dd08[m
Author: Julian Raschke <julian@raschke.de>
Date:   Sat Nov 25 17:23:33 2017 +0800

    Avoid warning about unused stbi__float_postprocess

[33mcommit fcf0b9960197e83a73d32c4931239bf558125d6b[m
Author: Anaël Seghezzi <anael@maratis3d.com>
Date:   Fri Nov 24 14:36:37 2017 +0100

    add stbi_is_16

[33mcommit 4c1a786455523f9805816dfc9b40df4133988f19[m
Author: Anaël Seghezzi <anael@maratis3d.com>
Date:   Fri Nov 24 14:35:14 2017 +0100

    Revert "return comp info in bytes (support for 16 bit images)"
    
    This reverts commit 9dfa8c7f31032644db68e5c756667d41ef5e904a.

[33mcommit 9dfa8c7f31032644db68e5c756667d41ef5e904a[m
Author: Anaël Seghezzi <anael@maratis3d.com>
Date:   Fri Nov 24 13:44:39 2017 +0100

    return comp info in bytes (support for 16 bit images)

[33mcommit 6e50ac78602bf441dd6136ecf6a5004e309d5109[m
Author: Kenney Phillis Jr <kphillisjr@gmail.com>
Date:   Sat Nov 4 03:35:02 2017 -0500

    stb_truetype: Fix undefined function warning
    
    This fixes the error in bug report #516. This should work as intended
    since the function definitions line up.

[33mcommit 5182622b1442c4e21e5e9b921a3a7b474ca3f9b1[m
Author: Kenney Phillis Jr <kphillisjr@gmail.com>
Date:   Sat Nov 4 03:28:03 2017 -0500

    tests: fix test_trutype.c on msvc 2015
    
    This is 3 short fixes for the file test_truetype.c.
    
    1. Fix the Visual Studio Secure CRT Errors by defining
     _CRT_SECURE_NO_WARNINGS
    
    2. Fix signed/unsigned Character conversion warning/error.
    
    3. Fix the Definitions for the Image packer.
    This now works as intended generating usable png files.

[33mcommit a981af59c5af476c2784ee101f9522a2c51272ae[m
Author: Aldo Culquicondor <alculquicondor@gmail.com>
Date:   Mon Oct 16 12:30:27 2017 -0500

    Fix tests compilation

[33mcommit 1f2b4271e3d6c4abc143d15ae4be6a47685f230b[m
Author: Dougall Johnson <a@dou.gl>
Date:   Sat Oct 14 11:59:09 2017 +1100

    stb_truetype: Fix CFF GetGlyphBox optional params
    
    Fixes #404

[33mcommit 84fd09ea5383262c1993ab52981ad3a3186ee15b[m
Author: Dougall Johnson <a@dou.gl>
Date:   Sat Oct 14 11:58:03 2017 +1100

    stb_truetype: Fix sign error in CFF push immediate

[33mcommit b6b43df18635ccdb128f5c3708d2ae640f647ef4[m
Author: darealshinji <djcj@gmx.de>
Date:   Mon Sep 4 14:01:43 2017 +0200

    Use stbi__mad4sizes_valid() only if STBI_NO_LINEAR or STBI_NO_HDR are defined

[33mcommit 350173026a2b5296656d158267c81ee2a38ed90c[m
Author: Mikhail Morozov <misha1294@rambler.ru>
Date:   Fri Sep 1 02:06:06 2017 +0300

    stb_image: support for 1-bit BMP

[33mcommit c06c9fe6bc907d58cb252be781373393999613ba[m
Author: lieff <lieff@users.noreply.github.com>
Date:   Thu Aug 31 19:33:28 2017 +0300

    place const tables to protected .rdata section

[33mcommit c8245bbf22aa2cf9056b346ab56ab4ee525a2905[m
Author: Jonathan Adamczewski <jonathan.adamczewski@gmail.com>
Date:   Mon Aug 28 23:13:39 2017 -0700

    Remove arg from memset macro
    
    My clang doesn't like the macro defined this way, choking at the callsite on line 195 with "too many arguments provided to function-like macro invocation"
    
    This change matches what is done for STBTT_memset in stb_truetype.h

[33mcommit 2545eee3efcc6ebb6c81857664559f1cf2ba262a[m
Author: Dave Butler <croepha@gmail.com>
Date:   Fri Aug 25 08:24:58 2017 -0900

    Added myself as a contributor for the pull request

[33mcommit f57bc38ff6e6af67bb7725a030cfa646180d305e[m
Author: Dave Butler <croepha@gmail.com>
Date:   Fri Aug 25 08:02:35 2017 -0900

    Made some changes to make Clang Happy
    
    Someone should double check that that I didn't change
    the behavior of any of the code.  I'm not using most (if any)
    of the code I touched, just wanted it to compile...

[33mcommit 7d80a8b44d5a25a922885c84e97bdcaf093195a5[m
Author: Marcin Wojdyr <wojdyr@gmail.com>
Date:   Fri Aug 11 00:19:18 2017 +0100

    avoid GCC7 implicit-fallthrough warning
    
    (GCC recognizes certain strings in comments)

[33mcommit 2c7b00ac21c8936572c2b036695fc91063c01bb1[m
Author: Aarni Koskela <akx@iki.fi>
Date:   Mon Aug 7 14:52:53 2017 +0300

    Add force_filter and compression_level parameters to (new) `stbi_write_png_to_mem_ex`
    
    * `force_filter` being < 0 means the original behavior (i.e. figure out
      the best-performing filter per scanline); any other values 0 <= x <= 4 correspond
      to PNG filters (0 = none, 1 = sub, 2 = up, 3 = average, 4 = Paeth).
    * `compression_level` being < 0 equals `compression_level` 8 (the previous value).
      The higher this is, the better the compression should be (though it will use
      more memory).
    
    These new parameters are not (yet) exposed for the higher-level API functions.

[33mcommit 923c9c3debf0283c8a025f56174c6305c70392ee[m
Author: Benji Smith <smith.benj@husky.neu.edu>
Date:   Mon Jul 31 22:22:56 2017 -0700

    Correct function signature in stbi_write_jpg usage documentation.

[33mcommit 747b8d8f71ed5b557234feffa44ff1ed98bed39b[m
Author: Rohit Nirmal <rohitnirmal9@gmail.com>
Date:   Thu Jul 27 23:51:36 2017 -0500

    stb_sprintf.h: Don't compare uninitialized value when using zero.
    This prevents a "Conditional jump or move depends on uninitialised
    value(s)" error from valgrind when using zero as an argument in line
    1045.

[33mcommit 9d9f75eb682dd98b34de08bb5c489c6c561c9fa6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jul 24 03:32:32 2017 -0700

    update readme

[33mcommit 961923b5a380037afa2743f21b6c32d446636435[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jul 24 03:32:20 2017 -0700

    fix documentation

[33mcommit dd039e8cc5227babbe6f3007943f3ac294f89b92[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jul 23 14:13:07 2017 -0700

    credits for mingw fixes in #444

[33mcommit 3b232a3ff79afa3efc1c36fd5a8dc362c75658e7[m
Merge: 555efbe 4963448
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jul 23 14:10:17 2017 -0700

    Merge branch 'master' of https://github.com/Infatum/stb into dev

[33mcommit 555efbedfc00f038c882bf6097e139864a3580e2[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jul 23 14:09:39 2017 -0700

    Update version numbers

[33mcommit 0fbbda56fa829c226b425c51cc784cb425daee4d[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 23 01:41:12 2017 -0700

    stb_image: Account for tRNS chunk in non-paletted images.
    
    So we report channels_in_file correctly.
    
    Fixes #329.

[33mcommit 7725f8b9cd8ca1eedd10600e40a87b6ac79bb1f3[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Jul 23 01:33:21 2017 -0700

    stb_leakcheck: Derp, I should free the right thing.
    
    Fixes #307, this time for real.

[33mcommit 5a5cf7f9ba936bb931ecde8df9465e250132fb75[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 20:44:27 2017 -0700

    stb_leakcheck: Make stb_leakcheck_free actually free.
    
    Fixes issue #307.

[33mcommit 5ebeb38edb3a1aceff44c142ab9eac832d6c6943[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 20:25:57 2017 -0700

    stb_rect_pack: Remove unused rect_width_compare().
    
    Fixes #416.

[33mcommit c59cb96874766ca550ae6266e64bb95abb0035d5[m
Merge: fedf03e 2da81a6
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:44:05 2017 -0700

    Merge branch 'fix-issue-461' of https://github.com/rygorous/stb into dev

[33mcommit fedf03e77497ad1fcd8c83b085c58e2b8c55fc75[m
Merge: 282576f cc7f1d1
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:42:52 2017 -0700

    Merge branch 'fix-issue-466' of https://github.com/rygorous/stb into dev

[33mcommit 282576fbfb3257b91a418538aed5d68551b4d5fa[m
Merge: 9b6652f 0674660
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:42:23 2017 -0700

    Merge branch 'rygorous-fix-issue-276' into dev

[33mcommit 9b6652fe3af23302d9de48138d1a8959bcdc87bd[m
Merge: b1d058e 481db75
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:41:40 2017 -0700

    Merge branch 'rygorous-sprintf_reformat' into dev

[33mcommit b1d058e5c766671fc805143fc6b2c4d73519e063[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:37:03 2017 -0700

    stb_truetype: Fix typo, as pointed out by oyvindjam.
    
    Fixes #471.

[33mcommit 30c7c6b5832fca322319b04a55eb7a6181683f5f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 19:24:41 2017 -0700

    stb_truetype: Support reading OS/2 vertical metrics
    
    ...as present in MS TrueType files. Since this table is optional,
    the new stbtt_GetFontVMetricsOS2 has a return value and can fail.
    This is a replacement for pull request #463.
    
    Fixes #463.

[33mcommit 49c7f1b397507d1af08073713673a7cda8eb954b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 18:43:36 2017 -0700

    stb_image: Optimise vertical flip.
    
    This incorporates #462, but also factors everything into one
    function that is shared between 8-bit integer, 16-bit integer, and
    float pixels (vertical flip operates on rows of bytes and doesn't
    really care), and finally always uses a 2k on-stack buffer without
    dynamic memory allocation, doing multiple memcpys per row if
    necessary. Not only does this remove an out-of-memory failure mode,
    it is also preferable for large images, since it's more
    L1-cache-firendly this way.
    
    Fixes #462.

[33mcommit 501812f307cd4b7609a1c6226f26bb7780cf08b8[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 18:03:52 2017 -0700

    stb_leakcheck: Fix warnings.
    
    1. const char* for __FILE__ (string literals are const)
    2. Use %zd to print size_t where available; the only real problem
       here is Visual C++. Use long long on the VC++ vers that support
       64-bit targets but not %zd, int on the even older 32-bit-only
       VC++ vers that don't support "long long" either.
    
    Fixes #459. I think. (It's hard to be sure since the issue doesn't
    state the exact warning message.)

[33mcommit 931662ae6ed9957be812a0bac134d9d856bcc0cf[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 16:04:07 2017 -0700

    stb_image_write: Warning fix.

[33mcommit 25a2596b2fee5041f8a55fd7317d0ffe90abc198[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:59:41 2017 -0700

    stb_image: Fix rounding during unpremultiply.
    
    This is the same method as in pull request #455, but using integer
    arithmetic instead of converting to float.
    
    Fixes #455.

[33mcommit 463dd85f1fa9e97e8f5d7d39d6171f97dd6b6097[m
Merge: 69ef103 3ef1cb1
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:51:28 2017 -0700

    Merge branch 'Reedbeta-fix-vs2015-warnings' into dev

[33mcommit 3ef1cb174ef6846eb0235ae158664519ca7f677d[m
Merge: 423298e cbca86d
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:51:14 2017 -0700

    Merge branch 'fix-vs2015-warnings' of https://github.com/Reedbeta/stb into Reedbeta-fix-vs2015-warnings

[33mcommit 69ef103721ae5493b48e6db0927f48bca8c4586b[m
Merge: 4868b52 316571b
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:42:58 2017 -0700

    Merge branch 'poppolopoppo-load_16_variants' into dev

[33mcommit 4868b5283bdd8f8f572ef7dc5a13a5c274af7348[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:40:27 2017 -0700

    stb_dxt: Update contributors list.

[33mcommit 316571b3951e99fc46483d65aa3a2f5c5dd1204b[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:38:56 2017 -0700

    stb_image: 3-char indent and other minor formatting issues.

[33mcommit b226e71ce6b9c56a27db620da4131305f6c6478e[m
Merge: 423298e 9bcda8b
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:35:32 2017 -0700

    Merge branch 'load_16_variants' of https://github.com/poppolopoppo/stb into poppolopoppo-load_16_variants

[33mcommit 31f8c2109be08cdf0efeeec21a694908b9c27331[m
Merge: 14c2993 e9b8f7e
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:29:50 2017 -0700

    Merge branch 'ppiastucki-bc4' into dev

[33mcommit e9b8f7ea3538fc97463d2cedb3921bc8b55be01c[m
Merge: 423298e 8a55e1e
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:28:27 2017 -0700

    Merge branch 'bc4' of https://github.com/ppiastucki/stb into ppiastucki-bc4

[33mcommit 14c29933104f046b2fd42d60aa7ef57cd4182a9a[m
Merge: 7a62516 b534571
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:23:14 2017 -0700

    Merge branch 'realitix-robustify' into dev

[33mcommit b53457130d91f4080e39e89488fbdcf5ac12a54b[m
Merge: 423298e d8796f0
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:22:57 2017 -0700

    Merge branch 'robustify' of https://github.com/realitix/stb into realitix-robustify

[33mcommit 7a6251689f1f458b1a2ea603deb408695fb9c36f[m
Merge: 897e6e8 99df133
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:13:13 2017 -0700

    Merge branch 'h-s-c-stb_dxt_static' into dev

[33mcommit 99df133ae4717afc3bcfb88a051ae29b1b964abf[m
Merge: 423298e 96e1f04
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:12:10 2017 -0700

    Merge branch 'stb_dxt_static' of https://github.com/h-s-c/stb into h-s-c-stb_dxt_static

[33mcommit 897e6e83141acd8ea305c6ebd2034251edcdce70[m
Merge: 24f2522 b119e6d
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:11:03 2017 -0700

    Merge branch 'h-s-c-stbi_no_stdio-fix' into dev

[33mcommit b119e6d1d20860a9b7555294b482b9cef4963b15[m
Merge: 423298e 97ae5fb
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:10:44 2017 -0700

    Merge branch 'stbi_no_stdio-fix' of https://github.com/h-s-c/stb into h-s-c-stbi_no_stdio-fix

[33mcommit 24f2522e00a35fbc2b1b808ca0d80090984cb25d[m
Merge: aaa7933 e1f17c3
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:08:40 2017 -0700

    Merge branch 'h-s-c-stb_dxt-freestanding' into dev

[33mcommit e1f17c3c6cae046a71576b14fc40def634e155db[m
Merge: 423298e 50e6be0
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:08:33 2017 -0700

    Merge branch 'stb_dxt-freestanding' of https://github.com/h-s-c/stb into h-s-c-stb_dxt-freestanding

[33mcommit aaa793350e6ce7eee9a5bda72a6c0fa766037170[m
Merge: 3870b2f 530c05e
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:06:09 2017 -0700

    Merge branch 'cdwfs-stbtt_const_fontdata' into dev

[33mcommit 530c05ee618912205465439a80f2d63cd2c0c714[m
Merge: 423298e f3d8e52
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:05:56 2017 -0700

    Merge branch 'stbtt_const_fontdata' of https://github.com/cdwfs/stb into cdwfs-stbtt_const_fontdata

[33mcommit 3870b2fe3b3c50de8996ba20be27fb806712a305[m
Merge: 423298e 526ed46
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:04:22 2017 -0700

    Merge branch 'DanielGibson-write-jpg' into dev

[33mcommit 526ed469e2da527e5ce0db33b7a35474af6d8b9c[m
Merge: 423298e f0baa0c
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 15:03:35 2017 -0700

    Merge branch 'write-jpg' of https://github.com/DanielGibson/stb into DanielGibson-write-jpg

[33mcommit 2da81a64339386bb1cb1548d2ebcbd3e997f0bbf[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Jul 22 14:39:52 2017 -0700

    stb_vorbis: MinGW has alloca defined in malloc.h.
    
    Fixes issue #461.

[33mcommit cc7f1d1e6d734e9d4b982be924f72504c4f0195e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 21 22:35:01 2017 -0700

    stb_image: Documentation fixes.
    
    req_comp is now desired_channels and *comp is *channels_in_file.
    
    Fixes issue #466.

[33mcommit 067466045187a40f16534b7a1f35cf4fba82a76e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 21 21:55:37 2017 -0700

    stb_image: Relax raw_len validation for non-interlaced PNGs.
    
    We used to require exact match between img_len and raw_len for
    non-interlaced PNGs, but the PNG in issue #276 has extra bytes
    (all zeros) at the end of the compressed DEFLATE stream.
    
    The PNG spec doesn't have anything to say about it (that I
    can tell), and if libpng accepts this, who are we to judge.
    
    Fixes issue #276.

[33mcommit 481db7501ce7938ee79771acf4f4a83f548fd4d1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 21 20:31:58 2017 -0700

    stb_sprintf: Remove some gratuitous gotos

[33mcommit 7b8955bfaa8c681628a50e34eec0c4995e0adbbe[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 21 20:23:50 2017 -0700

    stb_sprintf: More whitespace cleanups post clang-format

[33mcommit cccbc3f5a93f465c96e245f01f51fda8a90ae310[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Jul 21 20:17:34 2017 -0700

    stb_sprintf: Clean up the mess with clang-format

[33mcommit 423298e07169bced18a82c2d0e6a6341a19db65c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 12 09:27:04 2017 -0700

    fix SDF documentation and add example code

[33mcommit 38479bc58c9097802f45459553200accda76dffd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 12 07:25:20 2017 -0700

    stb_truetype version number

[33mcommit 9a2e92e81803d11163f769da78f0c6062e73eda7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 12 07:10:13 2017 -0700

    SDF documentation

[33mcommit fa98e4f6cf551945b72099ab9b82c90e66fd802e[m
Merge: 5defc65 c711058
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 12 06:42:02 2017 -0700

    Merge branch 'master' into sdf
    
    Conflicts:
            stb_truetype.h

[33mcommit 5defc65c233b640dad83f5cebf481d91ebcf2f8a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 12 06:34:52 2017 -0700

    Initial SDF support

[33mcommit d74530cd10680debdd5a9765644f5e366a01aebb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Wed Jul 5 18:01:53 2017 -0700

    fix stb_fclose to do a better job of preserving content

[33mcommit be21113512b4c1ab8a9fce23d5ad9ca4184bc25e[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Tue Jul 4 19:34:31 2017 +0200

    stb_image_write.h: Allow setting custom zlib compress function for PNG
    
    The builtin stbi_zlib_compress does not compress as well as zlib or
    miniz (which is not too surprising as it's <200 LOC), thus PNGs created
    by stb_image_write are about 20-50% bigger than PNGs compressed with
    libpng.
    This change lets the user supply a custom deflate/zlib-style compress
    function, which improves compression a lot. This was requested in #113.
    
    Example for zlib:
    
    #include <zlib.h>
    unsigned char* compress_for_stbiw(unsigned char *data, int data_len,
                                      int *out_len, int quality)
    {
      uLongf bufSize = compressBound(data_len);
      // note that buf will be free'd by stb_image_write.h
      // with STBIW_FREE() (plain free() by default)
      unsigned char* buf = malloc(bufSize);
      if(buf == NULL)  return NULL;
      if(compress2(buf, &bufSize, data, data_len, quality) != Z_OK)
      {
        free(buf);
        return NULL;
      }
      *out_len = bufSize;
    
      return buf;
    }
    #define STBIW_ZLIB_COMPRESS compress_for_stbiw
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "stb_image_write.h"
    // ...

[33mcommit e6bbecd3a9c73be061aeb51d6e4fe19317bc4d89[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Tue Jul 4 18:07:33 2017 +0200

    stb_image_write.h: Set PNG compress lvl via stbi_write_png_level
    
    This allows the user to change the deflate/zlib compress level used for
    PNG compression by changing a global variable.

[33mcommit f0baa0c287feeaa01c332fa786ac30285a0b65e7[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Tue Jul 4 16:55:50 2017 +0200

    stb_image_write.h: Fix compilation in C++11 mode
    
    clang says:
    error: non-constant-expression cannot be narrowed from type 'int'
          to 'unsigned char' in initializer list [-Wc++11-narrowing]
    
    so I explicitly cast affected stuff to unsigned char.

[33mcommit cbca86de6560d7953a7cd3860e6f221ae3fd2a1b[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu May 11 22:59:43 2017 -0700

    Add myself to contributors list

[33mcommit de080e6d0bfa41475e6afa71f2e32359403304f9[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu May 11 22:53:03 2017 -0700

    Fix warning about unreachable code

[33mcommit fb524e67685d6f17063e5c16942df688d9f7a987[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu May 11 22:51:19 2017 -0700

    Fix warning about context parameter being unused when STBIR_MALLOC and STBIR_FREE have their default definitions.

[33mcommit 76a1a1c408c29ff39d0d98af1f7e55b099b10052[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu May 11 22:49:19 2017 -0700

    Fix variable-shadowing warnings

[33mcommit 7091cb6ed65f6bfbdacf3ffcc23dc61bed59831f[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu May 11 22:48:46 2017 -0700

    Fix integer conversion warning

[33mcommit 9bcda8bb1c19191ef10dec0cf1bb09908c97e769[m
Author: PopPoLoPoPpo <frostiebek@gmail.com>
Date:   Fri May 5 00:39:08 2017 +0200

    Add stbi_load_16() variants to load from memory or callbacks

[33mcommit 84e42c2e8d2a94f936ebcf7ce14a8e02d2e8be6e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Apr 28 23:35:37 2017 -0700

    fix stbi_shiftsigned to be shifting a value that's unsigned

[33mcommit 8a55e1e5a54794b42f0398e37d9057eaed738831[m
Author: ppiastucki <piotr@jtilia.org>
Date:   Wed Apr 26 22:32:37 2017 +0200

    Add support for BC4

[33mcommit d8796f05bfea3f286ea5b95bba4a0a275d639e63[m
Author: Jean-Sebastien Bevilacqua <realitix@gmail.com>
Date:   Tue Apr 25 21:02:48 2017 +0200

    Robustify stbi__sse2_available in stb_image.h
    
    Function `stbi__sse2_available` takes no argument,
    we should be explicit by passing `void` as argument.
    It will remove warnings from 'some' compilers.

[33mcommit 4963448726f8cc4d1ad3d83fe3be862199f4f1e1[m
Author: Infatum <qwertty459@gmail.com>
Date:   Thu Apr 20 15:49:36 2017 +0300

    fix: Build on MinGW32

[33mcommit 13942348e08e1b68fa439a5fabf8baf108466bb0[m
Author: Tim Wright <timothy.wright.software@gmail.com>
Date:   Tue Apr 18 19:54:57 2017 -0600

    Fixing void * compile error for C++

[33mcommit 50e6be0de6a2211f7ec6d6d82eacb34e583fd1c0[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 18:31:15 2017 +0200

    Edit contributor list.

[33mcommit 9b3358fec13d0847886672e4ccd6e6aa6408a229[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 18:28:02 2017 +0200

    Add feature to replace abs/fabs and memset with your own.

[33mcommit 96e1f0474c4dec5a8a17a20a0fa1efc3040ed436[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 17:42:41 2017 +0200

    Edit contributor list.

[33mcommit 9835483187b1d0bf0ff2cae7d6fd76b1d262b64d[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 17:39:28 2017 +0200

    Edit contributor list.

[33mcommit 97ae5fb3db20acaf76fa9e6e31234848678292c1[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 17:36:48 2017 +0200

    Edit contributor list.

[33mcommit 1dfdf5558df6123b445851722d3560ae7c52081b[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 16:01:44 2017 +0200

    Fix STBI_NO_STDIO.

[33mcommit dda7d72841f6ce976c2b83948b0f1c7341088302[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 15:57:24 2017 +0200

    Add STB_DXT_STATIC option.

[33mcommit 8926141719396b299d9249e0ca7f02c8e7ccda47[m
Author: Kevin Schmidt <kevin.patrick.schmidt@googlemail.com>
Date:   Tue Apr 18 16:16:22 2017 +0200

    Improve stb_sprintf asan workaround.
    
    Adds support for more versions of clang and gcc.

[33mcommit f3d8e52ddc2e0790689821be4fc8dd08b78b9f14[m
Author: Cort <github@dangerware.org>
Date:   Tue Mar 28 21:36:54 2017 -0700

    stb_truetype: fontdata can be const in stbtt_PackFontRange[s]()

[33mcommit c7110588a4d24c4bb5155c184fbb77dd90b3116e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Mar 19 17:51:43 2017 -0700

    update README with info about SSE2 on GCC

[33mcommit e88fff69bf2348dbea0314a261c7e3b03428e7e3[m
Merge: 2549ffc f1417ef
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:55:43 2017 -0700

    Merge branch 'working'

[33mcommit f1417efd36ef00b457b83d032936eb48c4658b37[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:55:29 2017 -0700

    update README

[33mcommit 2549ffcd822b7a615bd6ef7b1e7603ca06525f4e[m
Merge: d459039 c0539b4
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:55:20 2017 -0700

    Merge branch 'working'

[33mcommit c0539b4ea5c168bc91dceea2c0d1431b60794c04[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:55:13 2017 -0700

    version; tweak docs

[33mcommit bc58f37f06929fa68b21a4a2f40b48a2545026a2[m
Merge: d795785 72e0f6c
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:50:25 2017 -0700

    Merge branch 'stbir_warnings' of https://github.com/BSVino/stb into working

[33mcommit d459039f8b126816832a99488cef18626a8f647c[m
Merge: b577583 d795785
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:50:20 2017 -0700

    Merge branch 'working'

[33mcommit d795785f3dc9f0ae09909554bc1f645368f7d448[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:50:06 2017 -0700

    docs

[33mcommit b577583fb9a2c4b490314b3a51c0df5a41139516[m
Merge: 37d767c 56a61e1
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:48:40 2017 -0700

    Merge branch 'working'

[33mcommit 56a61e178f8b4e30fd1a148dd94ef81b7b921287[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:48:09 2017 -0700

    reorganize contributor list (removing one redundant name and adding one new one as well)

[33mcommit c79fa78ee8e4ee82bf887218ec82c9aa10a98308[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:42:54 2017 -0700

    tweaks to previous merge

[33mcommit 351489803fbd1d5a9ad62d6bb0c86f2726072314[m
Merge: 2de9961 667f355
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:41:15 2017 -0700

    Merge branch 'phprus-patch-1' of https://github.com/phprus/stb into working

[33mcommit 37d767c0fc44949d6c954cdb5c894f5197ceb7ab[m
Merge: 22ace34 2de9961
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:39:23 2017 -0700

    Merge branch 'working'

[33mcommit 2de9961443d443c7c3e13a7c0c6577881d4295f7[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:39:06 2017 -0700

    docs

[33mcommit 90e8658d802bf5ca82562200ce84dd1bae6fc7ef[m
Merge: d9e7c55 22c72a0
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:37:20 2017 -0700

    Merge branch 'fix_stbimage_pnm_load' of https://github.com/rygorous/stb into working

[33mcommit 22ace34bf8c375b5adb575c76c68073d956c06ba[m
Merge: eaed281 d9e7c55
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:35:51 2017 -0700

    Merge branch 'working'

[33mcommit d9e7c55bd7ddefa31e6b8e44b053083b260d3b65[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:35:30 2017 -0700

    minor docs for last merge

[33mcommit 97c58e3891cba697f4e748cbbafc0adbe4dca6f1[m
Merge: 24fa816 3e17544
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:34:17 2017 -0700

    Merge branch 'fix_stbimage_gcc_sse2' of https://github.com/rygorous/stb into working

[33mcommit eaed281d9db7895b617ffd9a0aeed77f96c9d032[m
Merge: 3234410 24fa816
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:33:20 2017 -0700

    Merge branch 'working'

[33mcommit 24fa8161166327af9f9d35cabf520d69d233a04e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:31:06 2017 -0700

    merge https://github.com/nothings/stb/pull/427 but I messed up the merge
    so you don't get the automatic info you normally do

[33mcommit 32344103dfa2d82e0478ec9f3355570c1e453db1[m
Merge: 690ad3f 6d60610
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:17:49 2017 -0700

    Merge branch 'working'

[33mcommit 6d606103482631d4cf6cebd1a2d48602aa8c7b6b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:15:41 2017 -0700

    tweaks to previous merge

[33mcommit 00c25455107f46c42378245c2cc0e21fd3a5ce7d[m
Merge: 8fe4809 9e76bb5
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:08:00 2017 -0700

    Merge branch 'rgb-detect' of https://github.com/jeremysawicki/stb into working

[33mcommit 8fe48099cced44033981ac4114abbd983638645c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:07:51 2017 -0700

    add comment for next fix prematurely

[33mcommit 690ad3f9ddfa904ec3d3221d8faafc5561672303[m
Merge: 30a34d6 5bbe1d8
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:03:47 2017 -0700

    Merge branch 'working'

[33mcommit 5bbe1d8c2a22ad7833dd40c82ed2d3df0aa44e1b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 18:03:34 2017 -0700

    fixes to that PR

[33mcommit 55112399e65e5b639f5b30eecb74b7da4d58e3af[m
Merge: be6d13c 16c83cd
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 17:47:54 2017 -0700

    Merge branch 'master' of https://github.com/uTox/stb into working

[33mcommit 30a34d6168dc2529bafb08ecde03a208d9d8499d[m
Merge: 6f6e11f be6d13c
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 17:46:07 2017 -0700

    Merge branch 'working'

[33mcommit be6d13cd6df7d1e2e842ccc4b271b9d8d7c852ef[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Mar 18 10:54:22 2017 -0700

    fix bug in png decoding with 1,2,4-bpp images using filter that samples previous line

[33mcommit 72e0f6c971b668b8b7a3ac31b33614f7edecd35b[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Mar 14 19:35:51 2017 -0700

    Fix whitespace to how Sean likes it

[33mcommit 1adb98f1425115d821d26aee8f92a4efa1ac7734[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Mar 14 19:13:00 2017 -0700

    Fix some MSVC /W4 warnings

[33mcommit f298fb8a4cfbc6daee42e871b15cf36bf367d860[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Feb 9 19:40:18 2016 -0800

    Add support for obtaining the entire kerning table from a font all at once, for use in rendering packed textures offline.

[33mcommit e5144a3996188a58668bec528e7d7f09a091ef7a[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sat Mar 11 18:58:02 2017 +0100

    stb_image_write.h: Consistently use STBIWDEF for stbi_write_*
    
    Some functions were missing that in the definition, others weren't,
    all had it in the declarations.
    
    Added mention of JPG and HDR formats at the top of the file

[33mcommit 721c788fdb56dc98ccbc7cc4b6434d1ca2d8cef3[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sat Mar 11 18:42:47 2017 +0100

    stb_image_write: JPEG writer based on jo_jpeg.cpp
    
    jo_jpeg.cpp is a Public Domain JPEG writer written by Jon Olick in 2012
    http://www.jonolick.com/code.html
    
    My changes to jo_jpeg:
    * port to plain C89 (+ // comments, as supported by MSVC6)
    * support for 2 comp input (Greyscale+Alpha, Alpha is ignored)
    * use stbi__write_context abstraction instead of stdio for writing
    * adjust names to stbiw-style

[33mcommit a99bc0ca326299e65ed5a929996efaf1431e8dd1[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Sat Mar 11 09:34:26 2017 -0800

    Fix a bunch of warnings under Apple's clang-800.0.42.1

[33mcommit 667f35578b4cb6950ec381235fd41c0c5bd56aba[m
Author: Vladislav <phprus@gmail.com>
Date:   Wed Mar 8 21:16:50 2017 +0500

    statically initialize

[33mcommit 22c72a069c8e8ef666374e07db3657ba721a7943[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Mar 4 21:17:09 2017 -0800

    stb_image: Support optional args consistently.
    
    My guideline for the rules is the PNG loader (which I consider
    "canonical"). In the _load functions, x and y are required but
    comp is optional; in the _info functions, all three are optional.
    
    Fixes issue #411 (and other related, unreported issues).

[33mcommit 3e1754487307572b81a51350efe99f4d31fb52e3[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Mar 4 20:49:14 2017 -0800

    stb_image: Give up trying to runtime-detect SSE2 on GCC.
    
    We tried but it was nothing but trouble. New rule: with
    GCC/Clang, if you're compiling with -msse2, you get always-on
    SSE2 code, otherwise you don't get any. Trying to ship
    anything with proper runtime dispatch requires both working
    around certain bugs and some fiddling with build settings,
    which runs contrary to the intent of a one-file library,
    so bail on it entirely.
    
    Fixes issue #280.
    Fixes issue #410.

[33mcommit 9e76bb5108cca5c7e853d6a8bbadcd3dfa54b64b[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Fri Mar 3 16:24:21 2017 -0800

    stb_image: JPEG: Improved detection of RGB images

[33mcommit 6f6e11f85fd5c14bc9e9eb5edafb1b5dabd515d0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:49:55 2017 -0800

    readme

[33mcommit a4635779882a5350e0a4ae89e307a417cd1a30cd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:47:36 2017 -0800

    update README w/ MIT info

[33mcommit 16c83cd5fc4c18954c1b6e3de16c37ba590324a7[m
Author: Gregory Mullen (grayhatter) <greg@grayhatter.com>
Date:   Fri Mar 3 11:16:03 2017 -0800

    Fix a pair of warnings in stb_image.h

[33mcommit be931882efadd4eb49e73786c8cc1f044d94e708[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:22:36 2017 -0800

    update README

[33mcommit ee19531f68a6626dfb0f3fd8bd09563de8464304[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:12:41 2017 -0800

    fix to new bc5 path

[33mcommit def6a1898cbd6dfd6b0f2856f6104cf11ad88c83[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:09:36 2017 -0800

    version number

[33mcommit bee6e9fc2e544f868aa4fd73f067bc264a2b06a1[m
Merge: bd2cb59 847d288
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:02:17 2017 -0800

    Merge branch 'textedit-line_start_end_handlers' of https://github.com/ocornut/stb into working

[33mcommit bd2cb593e077151d3a42a328c12adb77636d0096[m
Merge: b1a0089 d052909
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 11:01:31 2017 -0800

    Merge branch 'old_textedit' into working
    
    Conflicts:
            stb_textedit.h

[33mcommit d052909923d04fa4ff47fdf571e5a57b2d349185[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:57:43 2017 -0800

    better handle dragging mouse in single-line mode

[33mcommit b1a0089c4bf7c7012a918550d7dd078b3e674ba1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:45:59 2017 -0800

    stb.h swprintf fix

[33mcommit a81422cd802622051a5305d48f526c68f08d99a8[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:41:11 2017 -0800

    version number

[33mcommit 98e825ac6761da13dd072c30227e293bcebc4628[m
Merge: 07c6c6b a2bc1ea
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:39:27 2017 -0800

    Merge branch 'master' into working

[33mcommit 07c6c6bc88a2f2ac94320ba21b2e2b29d561d71d[m
Merge: e895f6d 638267b
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:39:09 2017 -0800

    Merge branch 'stbir_patch' of https://github.com/BSVino/stb into working

[33mcommit a2bc1eabec827e47c669159e635326fa34c50e0f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:37:20 2017 -0800

    perlin noise function pull request by Jack Mott but deleted before I could pull it

[33mcommit 03611a369e1a1d8c9241104f83d2e39419059484[m
Merge: fab4c61 e895f6d
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:07:49 2017 -0800

    Merge branch 'working'

[33mcommit e895f6d3afd840ff29bfbac0d3917fe6ce32a5fc[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:07:16 2017 -0800

    tweak previous PR merge

[33mcommit 9009ae042ec1c45ec4c9feb073d993001e436dc1[m
Merge: c918a6b 07fefa3
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:04:44 2017 -0800

    Merge branch 'rect-pack-fail' of https://github.com/IntellectualKitty/stb into working

[33mcommit fab4c61d459ae94972fa2671e1110cb710b9a45d[m
Merge: 335565a c918a6b
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:03:23 2017 -0800

    Merge branch 'working'

[33mcommit c918a6b801e6d2c4720c5fc5fd54720a5cc1999f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 10:02:54 2017 -0800

    tweak previous PR merge

[33mcommit 2be620d2bbc622c3a1f07c57c91b62c9bdf2b88e[m
Merge: 324be64 13927ac
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:57:58 2017 -0800

    Merge branch 'lead_sign' of https://github.com/rohit-n/stb into working

[33mcommit 324be64e8082384aca1f3ef305075bb647ae4cdf[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:57:09 2017 -0800

    version number

[33mcommit 3841bc619803e079679d1c88800b5e731eb1e1dc[m
Merge: fd912b5 0e63382
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:56:11 2017 -0800

    Merge branch 'master' of https://github.com/jarikomppa/stb into working

[33mcommit 335565a86f904d6f625d8388e473373c59bac5b5[m
Merge: d79487a fd912b5
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:53:08 2017 -0800

    Merge branch 'working'

[33mcommit fd912b5d936c98b6087c768d4473662803b4590b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:52:42 2017 -0800

    version number, doc tweaks

[33mcommit 98537b70915b9c4e4c0ea943265ec286f85411ea[m
Merge: 0c1232f 6a29bcf
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:41:01 2017 -0800

    Merge branch 'master' of https://github.com/guitarfreak/stb into working

[33mcommit d79487a0ba7d959135b28feee934e69688295f64[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:38:25 2017 -0800

    readme

[33mcommit 0c1232f576e9fb92586bb983f03e8b7c8b2c1b2a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:37:50 2017 -0800

    version number

[33mcommit b280541e6a778798ce40e88e53d351056db76815[m
Merge: 3afc3de f5519a8
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:35:11 2017 -0800

    Merge branch 'stbtt_const_chardata' of https://github.com/cdwfs/stb into working

[33mcommit 3afc3de41da4ccd917e5079f4b1271c6c25c587b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:31:25 2017 -0800

    version number

[33mcommit 83a2489d5b3104c4ea67cd003c8cfd10a2493d5d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:22:07 2017 -0800

    fix compilation on non-C99 compilers

[33mcommit ed05048323655b2e165cd0c559da227146d9bc9d[m
Merge: e77673f 49d3871
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:15:17 2017 -0800

    Merge branch 'master' of https://github.com/fahickman/stb into working

[33mcommit e77673f4aaf74c24d53ae7f4bac74aa34cb19c91[m
Merge: 2d05188 8eebc09
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 09:07:37 2017 -0800

    Merge branch 'patch-1' of https://github.com/bryongloden/stb into working

[33mcommit 2d0518833b3df0881d8d9549fad8fd0f81fd0f51[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:59:52 2017 -0800

    readme

[33mcommit eab4930cc41728f5572fc76d4ad40d5bfa64661d[m
Merge: 8879908 6ba52a3
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:57:49 2017 -0800

    Merge branch 'working'

[33mcommit 6ba52a370c27e024bb451f2f28ad3f58c4007190[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:57:34 2017 -0800

    stb_dxt: extern "C"

[33mcommit 4ce23da44aeca01bc70a87b4913bd986383f05c9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:54:44 2017 -0800

    rename 3dc to bc5, tweaks to clean stuff up

[33mcommit a217948c16b939b1491ae1776da5440c9230d1fa[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:49:08 2017 -0800

    change 3dc name to bc5

[33mcommit c39063727dea8926ff3e42c5b73002732bd0100c[m
Merge: 6a3d478 cd93a5d
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:44:52 2017 -0800

    Merge branch 'master' of https://github.com/snake5/stb into working

[33mcommit 8879908f7879c2526533323bc85130142e87677d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:41:01 2017 -0800

    update readme

[33mcommit 6a3d4786c9258d87960552b50ca8cb56a371b469[m
Merge: 7e389e8 f5f7dc0
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:40:07 2017 -0800

    Merge branch 'unknown-marker' of https://github.com/jeremysawicki/stb into working

[33mcommit 7e389e85c10c9dc5b9ea1d72694c94ec743cb209[m
Merge: 15c7e06 2219a6d
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:39:31 2017 -0800

    Merge branch 'dnl-segment' of https://github.com/jeremysawicki/stb into working

[33mcommit 15c7e06dc8926fbb9aa4d68e72b2c10c459cbbde[m
Merge: dc6089f 6f56779
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:38:06 2017 -0800

    Merge branch 'junk-before-marker' of https://github.com/jeremysawicki/stb into working

[33mcommit dc6089f05bc04915dca6801aa49dd6bef997b68a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:37:30 2017 -0800

    tweak fill byte PR

[33mcommit 50ae79d811a99a11359da9b8057bbbe17d2b96ca[m
Merge: a6dc061 344c3f7
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:36:03 2017 -0800

    Merge branch 'fill-bytes' of https://github.com/jeremysawicki/stb into working

[33mcommit a6dc061137a4dbd5c83fbcb355cd854add1154ce[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:35:14 2017 -0800

    tweak 16-bit quantization for clarity

[33mcommit 0befbc3d78516029b22a8a8d7d340593a475a1fe[m
Merge: 014af7b e08d398
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:31:57 2017 -0800

    Merge branch 'dequant-16-bits' of https://github.com/jeremysawicki/stb into working

[33mcommit 014af7b78ad4bf94402e541bcba72cc7db8777d6[m
Merge: 786ac92 34fa37b
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:30:57 2017 -0800

    Merge branch 'component-ids' of https://github.com/jeremysawicki/stb into working

[33mcommit 786ac92daaac10307d3116e1c12ed454d398a69f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:30:49 2017 -0800

    tweak RGB-to-Y conversion

[33mcommit 64e1799f24710baacb870b943b4c71b454c31875[m
Merge: 8905cb9 cb7ffb2
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:25:29 2017 -0800

    Merge branch 'rgb-grayscale' of https://github.com/jeremysawicki/stb into working

[33mcommit 8905cb9a8efbd4ee0c25f958ab5edfca7d6c25d9[m
Merge: 47685c5 f07727a
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:21:46 2017 -0800

    Merge branch 'patch-1' of https://github.com/RufUsul/stb into working

[33mcommit 47685c5f84900b7a70fb7e3a7b6b58b585c852b0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:19:09 2017 -0800

    remove deprecated old-precision jpg path from stb_image.h
    tweak license reference wording

[33mcommit 51a5368deea553f119984975e6f8b64e8c6b519c[m
Merge: e248e30 734576e
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 08:02:39 2017 -0800

    Merge branch 'master' of https://github.com/pboettch/stb into working

[33mcommit e248e309546e546314115637fd6516b3e326a1c9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 07:53:07 2017 -0800

    change license to public-domain AND mit (based on twitter vote)

[33mcommit f88e2a8e7ba48c963f82dec86094a6cfa1e1556c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 06:58:14 2017 -0800

    update version

[33mcommit 46046238b8097abfd1905bc39c9222b3d4b5fb13[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 06:54:11 2017 -0800

    rename Point data structure as suggested in pull request

[33mcommit c88489549d47d4ba0900640dc7cc9622990080df[m
Merge: f9a83c0 a055654
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 06:51:37 2017 -0800

    Merge branch 'avoid-name-clash' of https://github.com/jlnr/stb into working

[33mcommit f9a83c0ae1217ec3ca0ef4bd0353ab1c557a04a3[m
Merge: 66fdbaa 3f36b29
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 06:50:32 2017 -0800

    Merge branch 'master' of https://github.com/alxprd/stb into working

[33mcommit 66fdbaaa878d0b4efe0532b0f111c58c03c84e29[m
Merge: d2de2be f32854c
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 06:48:48 2017 -0800

    Merge branch 'fix_vorbis_ilog' of https://github.com/rygorous/stb into working

[33mcommit d2de2be10fdb1cf459e194b40302af8f6a8a0c7b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Mar 3 05:48:37 2017 -0800

    vorbis: propagate errors better on seek failure (e.g. when coarse seek fails)

[33mcommit f5f7dc02a1308817e94f43f783bd3abef8706271[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Fri Mar 3 01:11:34 2017 -0800

    stb_image: JPEG: Provide failure reason for unknown marker

[33mcommit 2219a6da29b978e783ff0d155433ec95eedd56ce[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Fri Mar 3 00:13:27 2017 -0800

    stb_image: JPEG: Accept DNL segment

[33mcommit 6f5677946c9853be9ea87bfa13facc205d27fe05[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 23:48:02 2017 -0800

    stb_image: JPEG: Accept non-zero junk bytes at the end of image data

[33mcommit 344c3f73d59c159f939ebdf01f2d89654727499d[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 23:10:03 2017 -0800

    stb_image: JPEG: Accept fill bytes in stbi__grow_buffer_unsafe

[33mcommit e08d39867195b9e18367a2d90d98784b618340d8[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 22:32:30 2017 -0800

    stb_image: JPEG: Accept 16-bit quantization tables

[33mcommit 34fa37bbb4d690843b1d51c311c1f240a5d0570e[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 21:40:40 2017 -0800

    stb_image: JPEG: Accept any component IDs

[33mcommit cb7ffb2408ca11fd05a13f9dff658911e7aaa050[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 18:19:21 2017 -0800

    stb_image: Update contributors

[33mcommit 552c548a0e6b978ba329e2702d7713327b40fd74[m
Author: Jeremy Sawicki <jeremysawicki>
Date:   Thu Mar 2 18:06:10 2017 -0800

    stb_image: JPEG: Convert RGB to grayscale properly

[33mcommit f5519a8f85389ed1c063fab3a459581d10ef4aa8[m
Author: Cort <github@dangerware.org>
Date:   Mon Feb 13 18:23:53 2017 -0800

    stbtt: chardata can be const in GetBakedQuad() and GetPackedQuad()

[33mcommit 7ef6ac1b351b7335489daba2bd69d18c149db911[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 29 18:16:38 2017 -0800

    added redundant pg_test.c just in case

[33mcommit 638267b6d5e2dde6ef5747e43fa4a27bd7927ad0[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Sun Jan 29 12:30:38 2017 -0800

    Floating point rounding causes stbir__calculate_sample_range_upsample to sometimes think it needs one more scanline than it really does. This patch adds one extra entry to the ringbuffer to avoid the problem.

[33mcommit 59a5a155b463c2adb8ce6d7eca348c097062430a[m
Merge: 52920a2 7e989db
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 16 06:17:55 2017 -0500

    Merge pull request #401 from themanagainstthetank/patch-1
    
    update stb_image.h

[33mcommit 52920a2d5e15bc440b867919b4776c8c439b35e0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 03:01:57 2017 -0800

    update version numbers

[33mcommit 84e2fc0a9e57d6736c800d5948f583b51f5ceeed[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 03:01:40 2017 -0800

    makefile

[33mcommit 4d19411acdde789a29cde137b8db897c64ec3c9f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 02:58:05 2017 -0800

    makefile

[33mcommit 1dd1b6c191df8d666b19a8a7e8dbd482619ddf99[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 02:53:36 2017 -0800

    makefile

[33mcommit c09f1eebe793797dc1ef39b5947992d7481640e5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 02:47:27 2017 -0800

    makefile

[33mcommit 1b7aa1af87448e74dc9045e180a65238fbe37265[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 02:39:18 2017 -0800

    makefile

[33mcommit 7e989db555e3acba73db2dc162856ff6dcb9b7b9[m
Author: themanagainstthetank <2011301000007@whu.edu.cn>
Date:   Mon Jan 16 18:12:31 2017 +0800

    update stb_image.h
    
    int raw_data[4] to 0, or the compiler bugs

[33mcommit d71aea034b78a65b307b64dee4dee6453640f791[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:41:23 2017 -0800

    makefile

[33mcommit a235b6cd4443ceb3d1f09f02ba8f52259b34da68[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:36:58 2017 -0800

    makefile

[33mcommit cf6d17cd74f0bd6792cb40fea421598b28713638[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:28:11 2017 -0800

    makefile

[33mcommit e29e2bfb129845eff3043199bb8295b366aa1f59[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:22:16 2017 -0800

    makefile

[33mcommit ea2b06976cd4be66df2940fe2f50c72a930e70f0[m
Merge: 21913be e6268b5
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:15:04 2017 -0800

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 21913be792ec40f386c955a47fb6f9c50676f0b6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:14:08 2017 -0800

    makefile

[33mcommit e6268b555883e9ab9fdd38fad172a7da757393d0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 16 01:10:59 2017 -0800

    Delete release_notes.md

[33mcommit fc5668cdaceb4cdfdbe19a94f56d494fc3064eeb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 01:09:50 2017 -0800

    makefile for tests

[33mcommit 96620a3a5427de86813b2fc523d535b1ade605c4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 00:51:24 2017 -0800

    update version numbers

[33mcommit 0bd0a9abc44957d79cbc6cfdf49565b7e95a463d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 00:11:58 2017 -0800

    stb_truetype: comment typo
    stb_c_lexer: end-of-array wrapped overflow bug

[33mcommit dead3815e2bebee051eb49b8f6c288245d68e11e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 16 00:05:58 2017 -0800

    credits

[33mcommit 28c24f7b8345c4b3ae92b70d686be34d43cfcd2b[m
Merge: 4871023 ec9db6f
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 23:58:26 2017 -0800

    Merge branch 'fix-truncation' of https://github.com/sammyhw/stb into working

[33mcommit 48710234f283ec106d429a28d53436133734d121[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 23:57:53 2017 -0800

    credits; 1/2/4-bit png fix; easy font spacing; NO_STDIO in image_write

[33mcommit 96714b2a13657efe66ee861a52525626ab46578a[m
Merge: 80a39f9 19d0376
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 23:46:26 2017 -0800

    Merge branch 'fix_stbi_write_hdr_scope' of https://github.com/poppolopoppo/stb into working

[33mcommit 80a39f958fcc6c861377936572fe29a5335094bb[m
Merge: 7bb64aa 4338a0e
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 23:43:53 2017 -0800

    Merge branch 'fix-percent-check' of https://github.com/d26435/stb into working

[33mcommit 7bb64aa86784be49c6cef202009434b7264f1d39[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:51:47 2017 -0800

    pull request template

[33mcommit dcdf02a59f9f67b6efd46797cbdec1d9f038cf0b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:50:31 2017 -0800

    pull request template

[33mcommit 73b511b1a31227be972a4a7d07c694da85db81c5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:49:11 2017 -0800

    pull request template

[33mcommit 2db6897d48e7bbc0877986a38e4ae3ff77a9e052[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:44:34 2017 -0800

    contributing

[33mcommit d36c43f337501c0d07808166b03bffa7d72ee8ea[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:41:31 2017 -0800

    contributing.md

[33mcommit fc682ec2ded274c2d8c65b17e7aabbaa01810634[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Jan 15 21:26:26 2017 -0800

    update readme

[33mcommit f5c9aaacd26ec7ebad86204142e1d0c316c83477[m
Merge: 94374c9 9bb7f80
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 2 21:15:08 2017 -0500

    Merge pull request #395 from dougallj/patch-1
    
    stb_truetype: Fix a couple of CFF bugs

[33mcommit 9bb7f80cb8caf128032ce628cf573e7098b45a29[m
Author: Dougall Johnson <dougallj@gmail.com>
Date:   Tue Jan 3 13:08:05 2017 +1100

    stb_truetype: Fix a couple of CFF bugs
    
    The CFF/Type 2 changes broke including without STB_TRUETYPE_IMPLEMENTATION defined, and had a typo. Sorry!

[33mcommit 19d03764b5d9a603a8cc12372d0746b76c3954ac[m
Author: PopPoLoPoPpo <frostiebek@gmail.com>
Date:   Sun Dec 4 21:14:24 2016 +0100

    Fix #ifndef STBI_WRITE_NO_STDIO scioe for stbi_write_hdr()
    
    stbi_write_hdr_to_func() should still be available even without STBI_WRITE_NO_STDIO,
    just like other formats.

[33mcommit 94374c99c81cd412a00702cbdcc5a78bc4706961[m
Merge: 4f2324c 53e4334
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:22:48 2017 -0800

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 4f2324c6ad1b034172db164d4237137f4875a27f[m
Merge: cca943e 99fd236
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:22:16 2017 -0800

    Merge branch 'num-fonts' of https://github.com/IntellectualKitty/stb into working
    
    Conflicts:
            stb_truetype.h

[33mcommit cca943e78a1f1e38ce36352eae011ce91543f912[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:18:52 2017 -0800

    version history

[33mcommit 834199151ec7e1f7567d5b9d84274768ff00b9bc[m
Merge: 3d1c790 7fa573c
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:16:33 2017 -0800

    Merge branch 'is-apple-font' of https://github.com/IntellectualKitty/stb into working

[33mcommit 3d1c790e96c9f35eeabdff5b33c8fc21b81277c5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:16:22 2017 -0800

    version history

[33mcommit 53e4334bf76e43edece330c5de7a1f3b3f3e645d[m
Merge: 3e7f2d6 4a60c54
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 2 18:15:16 2017 -0500

    Merge pull request #363 from mgerhardy/patch-1
    
    Shouldn't this be 6?

[33mcommit d0b576c47446a0ca549aa8aa6c98d66fcc9a06d8[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:12:18 2017 -0800

    update stb_truetype version

[33mcommit ad6614ad9f462e2147630c4614ded00a846dc17e[m
Merge: d5ec778 0181b37
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 15:10:20 2017 -0800

    Merge branch 'cff-type2' of https://github.com/dougallj/stb into type2
    
    Conflicts:
            stb_truetype.h

[33mcommit d5ec7789bd69f77080b232039aaf95852f3380e2[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 14:08:58 2017 -0800

    stb_image_resize update

[33mcommit f882db0c80ae5fc3ae2da462b632de33f4bddc0a[m
Merge: 3e7f2d6 21ea548
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Jan 2 14:07:06 2017 -0800

    Merge https://github.com/aras-p/stb into working

[33mcommit f07727a28a5321c4a2e57215334a3a38ed773a33[m
Author: Thomas Ruf <mail@rufusul.de>
Date:   Wed Dec 28 14:16:45 2016 +0100

    stb_image.h: large structures on the stack
    
    more of "allocate large structures on the stack", this time in the forgotten stbi__jpeg_test
    -> avoids the infamous _chkstk() when working with CRT

[33mcommit a055654ee34f60072d953ee621639928b266424f[m
Author: Julian Raschke <julian@raschke.de>
Date:   Tue Dec 27 11:18:26 2016 +0100

    Rename Point to stbv__point

[33mcommit 3f36b29589870d98eb1dc9945d3726eba6746728[m
Author: Alejandro Pereda <atk1005@gmail.com>
Date:   Mon Dec 26 16:01:50 2016 +0100

    Overwrites error parameter in stb_vorbis_open_memory when there is no error. This avoid confusion due to previous values.

[33mcommit 99fd236287c124fb9426901f106a591fb0a41f88[m
Merge: 75a8fd9 3e7f2d6
Author: Christopher Hansen <hansenc@Christophers-MacBook-Pro-Late-2011.local>
Date:   Mon Dec 19 18:33:49 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb into num-fonts

[33mcommit ec9db6f84b39988a6a3375058e97598fe63fca4e[m
Author: sammyhw <samuel.h.woodward@gmail.com>
Date:   Thu Dec 15 23:49:19 2016 -0500

    allow for all 16 bits

[33mcommit 13927ac386d02815f139d29f12d60382a3c33b01[m
Author: Rohit Nirmal <rohitnirmal9@gmail.com>
Date:   Mon Dec 5 18:18:20 2016 -0600

    stb_printf.h: Reuse code for assigning lead sign.

[33mcommit 4338a0e55e9c62eb7469f7b99dcafeeb97eb53cd[m
Author: Daniel <d26435@gmail.com>
Date:   Mon Dec 5 21:03:05 2016 +0000

    Fix the check for a percent character
    
    It was matching everything less than 0x26, so could cause a minor
    performance loss. Also made the second if statement superfluous.

[33mcommit 58c51413f633c73914e24fb90b7ad484f58cb421[m
Author: Jeroen van Rijn <jeroen@handmadedev.org>
Date:   Mon Dec 5 17:08:10 2016 +0100

    Fix comments where rr* functions hadn't been renamed yet.

[33mcommit 0e63382be0f569f080698174a25d59f40a4d69f3[m
Author: jarikomppa <jari.komppa@gmail.com>
Date:   Mon Dec 5 17:23:01 2016 +0200

    A bit more involved change: support for both 1000 and 1024 divisors, and SI and JEDEC suffixes, as well as removing the space between number and suffix.

[33mcommit 3e7f2d6ebddfe54bd9a9491db1349513a357bfe5[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 06:58:30 2016 -0800

    fix missing renames

[33mcommit bec0b26d1e53823320e78fa6fbe6cc17264c4a75[m
Merge: 554e072 0c6bd72
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 06:53:53 2016 -0800

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 554e0727429cc65e187b740a484d83c7216ccce0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 06:53:36 2016 -0800

    fix #ifdef mistake in stb_sprintf

[33mcommit 0c6bd72ccb186306eafe93d6c199a76ff9f3f0e8[m
Merge: ca3b8d7 e6e20b4
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Dec 5 05:58:30 2016 -0800

    Merge pull request #377 from aras-p/patch-1
    
    stb_sprintf: seperators -> separators typo in comment

[33mcommit 9a3f9dff13cc07752cfa95b7fcce0a50004f9c30[m
Author: jarikomppa <jari.komppa@gmail.com>
Date:   Mon Dec 5 15:08:54 2016 +0200

    More proper fix for the prefixes (defaults to Ki style, with define for using K style instead)

[33mcommit a27e577c3eb38a2f40d4c55f37c8a58d6a750397[m
Author: jarikomppa <jari.komppa@gmail.com>
Date:   Mon Dec 5 14:56:35 2016 +0200

    The Si prefixes for mega, giga and tera are upper case (lower case m is not mega but milli)

[33mcommit e6e20b43dbc26ee838c45b740f4f47159a2f6b2d[m
Author: Aras Pranckevičius <nearaz@gmail.com>
Date:   Mon Dec 5 14:49:39 2016 +0200

    stb_sprintf: seperators -> separators typo in comment

[33mcommit ca3b8d74263aae9d6299166b3f4b6864df95f79a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 04:19:53 2016 -0800

    add credits to readme

[33mcommit 9953803d0cacba488c4ede50fe9d757a8da36d51[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 03:53:54 2016 -0800

    fix bad search-replace in comment

[33mcommit 3f2716ace46a46e50960dfbd2ad96a71ceda4837[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 03:50:06 2016 -0800

    add stb_sprintf to readme

[33mcommit c9fe5bac480e666fab8fd10f899f4700bc3fb3dd[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 03:48:37 2016 -0800

    rename all stb_sprintf identifiers to follow stb conventions

[33mcommit fd23d7097d8ef8a0060d3096729e5ca4906d1f35[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 02:58:16 2016 -0800

    rename rrsprintf to stb_sprintf

[33mcommit 454ed822a7a3c278cfc63bd0168bc54d1015b120[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 02:57:49 2016 -0800

    deprecate rrsprintf

[33mcommit a468fbda725c014af5ca2cef3b57ba271d1fb685[m
Author: Sean Barrett <sean@nothings.org>
Date:   Mon Dec 5 02:57:06 2016 -0800

    readme, add rrsprintf.h

[33mcommit 75a8fd9d41939a4b7712151254d1473f84d39197[m
Author: IntellectualKitty <IntellectualKitty@gmx.com>
Date:   Sun Dec 4 17:06:17 2016 -0700

    Add function to get the number of fonts in a TrueType file

[33mcommit 7fa573cd619cd1e6ddbecf500e6d3009694cc97d[m
Author: IntellectualKitty <IntellectualKitty@gmx.com>
Date:   Sun Dec 4 16:06:34 2016 -0700

    Update stb_truetype.h

[33mcommit b61b7a74fa050db0679d69ac584312bc0300914c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:40:21 2016 -0800

    update version info

[33mcommit b9be4fd8dfaed829e73614a653c5c7ecd1e49b81[m
Merge: 4a1523f 0b2c06a
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:39:52 2016 -0800

    Merge branch 'merging' into working

[33mcommit 0b2c06a7e17da43283c872c67f4679b92dcebbb6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:39:35 2016 -0800

    more STB_IMAGE_STATIC fixes

[33mcommit 7bcaa93a767e54633eb5e6357e64d64f754ef987[m
Merge: 7759a2a 2a170da
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:38:47 2016 -0800

    Merge branch 'master' of https://github.com/Zelex/stb into merging
    Also add more credits
    Also fix linking multiple copies with STB_IMAGE_STATIC
    
    Conflicts:
            stb_image.h

[33mcommit 4a1523f60ab0b1a707e147c41dcfc2a421007a8c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:28:26 2016 -0800

    make tga load function static to avoid link errors on multiple instances

[33mcommit 7759a2a93d192951b00804be1466b5e7296ca7c0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:25:24 2016 -0800

    fix "misleading indentation" gcc warning

[33mcommit ae241feec469aa170de1a2523f9773c8f8ef0b81[m
Merge: 7736399 6b66033
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:20:57 2016 -0800

    Merge branch 'stb_img_overflows' of https://github.com/rygorous/stb into working
    
    Conflicts:
            stb_image.h

[33mcommit 77363995175908b304525f2cc2b17180f2fdad96[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Dec 4 05:13:58 2016 -0800

    return 16-bit PSDs through 16-bit API (untested)

[33mcommit 07fefa384a55bda00039454a5e164f3f20093668[m
Author: IntellectualKitty <IntellectualKitty@gmx.com>
Date:   Wed Nov 30 13:24:38 2016 -0700

    Return all_rects_packed status from stbrp_pack_rects.

[33mcommit e0700d8e2c1f2a8c8666f9776063e5f956b38230[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Nov 29 04:13:17 2016 -0800

    16-bit png changes

[33mcommit 239a6718e185d3ecbf3da6329db0c0d94ee6d7ec[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Nov 29 03:03:07 2016 -0800

    rename stbi_load parameters to reduce confusion

[33mcommit 2a170daee5dd339bc8f3f81024a97710935c360f[m
Author: jon <jon@jon-Lemur>
Date:   Mon Nov 28 16:24:11 2016 -0600

    warning fixes, more RGBE fix

[33mcommit a2defc3d7a273416b306ce2cf2bee49431957f31[m
Author: jon <jon@jon-Lemur>
Date:   Mon Nov 28 16:05:39 2016 -0600

    added support for RGBE header HDR files

[33mcommit cd93a5de110c2045278606cee37829304ed36689[m
Author: snake5 <snake5creator@gmail.com>
Date:   Sat Nov 26 16:45:40 2016 +0200

    added basic 3Dc support

[33mcommit 996ccf21590a79f3efb17dab7093614b58c7187c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Oct 25 08:53:48 2016 -0700

    update version numbers

[33mcommit 5d9423f8fd91744269c7413b7352778324f627bb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Tue Oct 25 08:50:44 2016 -0700

    fix -Wcast-qual in stb_rect_pack, stb_textedit, stb_truetype

[33mcommit 6b66033e18c22de830b9ea599bf448843fd104cf[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Aug 12 17:46:43 2016 -0700

    stb_image: Fix memory leak and missing out-of-mem check.
    
    stbi__process_frame_header had two bugs when dealing with progressive
    JPEGs:
    1. when malloc failed allocating raw_data, previous components'
       raw_coeff didn't get freed
    2. no out-of-memory check in raw_coeff allocation
    
    Fix both and share a bit more cleanup code in general.

[33mcommit 62f372754f8dfb1bc5ae9e25fdc3f0c75fb08001[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Aug 12 17:31:53 2016 -0700

    stb_image: Fix HDR/PSD RLE decoders.
    
    Runs need to be bounds checked.
    
    Fixes issues #315, #317.

[33mcommit 02190634c2ff6e3b68fcd99b84cf4acabb70ea2e[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Aug 12 17:22:46 2016 -0700

    stb_image: Overflow checking for image allocs.
    
    Adds some helpers that check whether a product of multiple
    factors (that need to be non-negative: this is enforced)
    summed with another non-negative value overflows when
    performed as int. Since stb_image mostly works in ints,
    this seems like the safest route. Limits size of images
    to 2GB but several of the decoders already enforce this
    limit (or even lower ones).
    
    Also adds wrappers for malloc that combine a mul-add-with-
    overflow-check with the actual malloc, and return NULL
    on failure. Then use them when allocating something that
    is the product of multiple factors.
    
    For image formats, also add a top-level "is this too big?"
    check that gives a more useful error message; otherwise,
    the failed mallocs result in an "out of memory" error.
    The idea is that the top-level checks should be the primary
    way to catch these bugs (and produce a useful error message).
    But a misleading error message is still vastly preferable to
    a buffer overflow exploit.
    
    Fixes issues #310, #313, #314, #318. (Verified with the
    provided test images)
    
    Along the way, this fixes a previously unnoticed bug in
    ldr_to_hdr / hdr_to_ldr (missing NULL check); these functions
    are called with the result of an image decoder, so NULLs can
    definitely happen.
    
    Another bug noticed along the way is that handling of
    interlaced 16-bit PNGs was incorrect. Fixing this (along
    with the previous modifications) fixes issue #311.
    
    Yet another bug noticed during this change is that reduce_png
    did not check the right pointer during its out of memory
    check. Fix that too.

[33mcommit 8c8d735eb7c610811da2cd6efc7a8d59420b4b37[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Fri Aug 12 13:44:11 2016 -0700

    stb_image: More input validation in deflate decoder
    
    Fixes issue #312.

[33mcommit f32854c809ab261c07f09f5f27435daadccc2728[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Tue Sep 6 11:58:00 2016 -0700

    stb_vorbis: Fix handling of negative numbers in ilog.
    
    For negative n, the original code went down the "n < (1<<4)"
    path and performed an out-of-bounds array access. Fix the code
    to agree with section 9.2.1 of the Vorbis spec. (Verified by
    exhaustive testing of all 32-bit ints.)
    
    Fixes issue #355.

[33mcommit 2f4166e91d1e81c8775a2878820187b8b316baf0[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Oct 16 07:59:57 2016 -0700

    stb_connected_components

[33mcommit 7d0099ecc95ca3b123221bd8bf3228c4197124ff[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Oct 16 07:58:59 2016 -0700

    fix bug in stb_connected_components adjacency list updating incorrectly handling avoiding adding the same connection twice

[33mcommit 847d288152a2a8cb26b3ae7b68b643eb01cedb0a[m
Author: ocornut <omarcornut@gmail.com>
Date:   Sun Oct 16 13:33:21 2016 +0200

    stb_textedit: fix LINESTART when cursor is at end of buffer and no trailing newline. Stopped using find_charpos(), simpler and faster.

[33mcommit 6a29bcf2a1c00b100558d6b0366fa64f4c0929c7[m
Author: guitarfreak <der_jacker@yahoo.de>
Date:   Sat Oct 8 04:23:52 2016 +0200

    Update stb_voxel_render.h

[33mcommit 5fcd181fae6d5e318bf897473a2ee5a9e2259a51[m
Author: guitarfreak <der_jacker@yahoo.de>
Date:   Sat Oct 8 04:10:23 2016 +0200

    Update stb_voxel_render.h

[33mcommit dca0a37ff492200451b4a489276fcd9a065afc2d[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 17:36:21 2016 -0700

    other_libs points to new location

[33mcommit 1a31473db826af86ddf8ce8a2cf224fe9a43d406[m
Author: guitarfreak <der_jacker@yahoo.de>
Date:   Sat Oct 8 01:59:11 2016 +0200

    Added block_selector

[33mcommit bf1dd132450ccc54c2b27ba69325fa6bda98d7b2[m
Merge: d9e0dfc 5ecb2d8
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:56:45 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit d9e0dfcd631a870abc7ef88ac4f592f2095c759a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:56:29 2016 -0700

    readme change link to other_libs

[33mcommit 5ecb2d86b89985072d6621c11919d87eaa79fc4d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Oct 7 08:55:48 2016 -0700

    Delete other_libs.md

[33mcommit 33ac18a7fbaa3bc039b0ac38e5ec5a877bd4dd2f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:43:38 2016 -0700

    tinyfiledialogs

[33mcommit 3dabed0208061e1df4abc814aa5bc930610635bb[m
Merge: f2847a5 9730553
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:38:30 2016 -0700

    Merge branch 'working'
    
    Conflicts:
            docs/other_libs.md

[33mcommit 97305532a9f8d2d4281a37154f38244ca552524e[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:37:42 2016 -0700

    tweak genann

[33mcommit f05f8c334857866478c960e41311de5197d94432[m
Merge: a117f37 365441b
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:34:59 2016 -0700

    Merge branch 'codeplea-genann' of https://github.com/codeplea/stb into working

[33mcommit f2847a5493ffa5461831b3d052061f822865a9b8[m
Merge: a117f37 f814cd7
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:31:19 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit a117f374b2aabe6717b4a90e9f1c9173a7ffe6fb[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:30:52 2016 -0700

    update readme with links

[33mcommit 3df89264432809fbdaf73d742d44e7d6d694a4a0[m
Merge: c36e8ae 94dd6fe
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:27:40 2016 -0700

    Merge branch 'feature/add-link' of https://github.com/1ace/stb into working

[33mcommit c36e8ae082ee1e835fe26e7cc4ff566a1e1b47b6[m
Merge: 7fa4f12 cf51044
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:27:26 2016 -0700

    Merge branch 'master' into working

[33mcommit 7fa4f1204803641a3f46a1d2182c492ccf939f45[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:25:24 2016 -0700

    tweak doctest

[33mcommit 51e136aad72e99059cbc365d7f10e8e55c2f362d[m
Merge: e3d8042 a2bf759
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:24:16 2016 -0700

    Merge branch 'patch-1' of https://github.com/onqtam/stb into working

[33mcommit cf51044bc6b24e7a86216f75b4918d83f097ea62[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri Oct 7 08:23:24 2016 -0700

    update stb_pg project

[33mcommit 0181b37188698d0921d6df2d3a4cce5228f2fb13[m
Author: Dougall Johnson <a@dou.gl>
Date:   Sat Sep 24 20:38:13 2016 +1000

    CFF and Type 2 charstream parsing in stb_truetype
    
    This is a partial implementation of the CFF and Type 2 charstring
    specifications. It allows stb_truetype to read most OTF files.

[33mcommit 4a60c547109bd40d1879e479adac3f24c2f77b6e[m
Author: Martin Gerhardy <martin.gerhardy@gmail.com>
Date:   Fri Sep 30 10:13:05 2016 +0200

    Shouldn't this be 6?

[33mcommit f814cd757773d67da209b744e834f00292c04ec7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 25 17:10:51 2016 -0700

    Update other_libs.md

[33mcommit 4f51089d1db168a5cc931a2f2e49d1bf8d8ba11b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 25 15:09:45 2016 -0700

    Update other_libs.md

[33mcommit 49d3871d867e463cc622b1a5b0fb28fbe3ba18ab[m
Author: Alan Hickman <f.alan.hickman@gmail.com>
Date:   Sun Aug 14 18:35:17 2016 -0700

    stb_c_lexer.h: C99 hex float literals
    
    * Add support for C99 hex float literals
    * + is acceptable in a floating-point exponent
    * log(n) implementation of pow for stb__clex_parse_float
    * Add hex int and float test cases

[33mcommit c6b6239357e72b91e83ab2f4d6e474e27dbf11c1[m
Author: Alan Hickman <f.alan.hickman@gmail.com>
Date:   Sun Aug 14 18:34:35 2016 -0700

    stb_c_lexer.h: Compile fixes when not using CRT

[33mcommit e713a69f1ea6ee1e0d55725ed0731520045a5993[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 28 14:10:03 2016 -0700

    Update other_libs.md

[33mcommit fa775881d6f85fdd9d6705aaed615f5244f780c9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 28 11:04:38 2016 -0700

    Update other_libs.md

[33mcommit 973ad3611c4ce63fad89082cd0192f1ad163e60a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sun Aug 28 10:42:22 2016 -0700

    other_libs updates

[33mcommit fa3db1eb89b3b9257b3402f71796ffc507af104f[m
Merge: ac646fd e3d8042
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:55:06 2016 -0700

    Merge branch 'working'

[33mcommit e3d804279a8f8951889e7900f3ed1a736734f435[m
Merge: a1b466a 33b92ca
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:54:59 2016 -0700

    Merge branch 'patch-1' of https://github.com/terrehbyte/stb into working
    
    Conflicts:
            docs/other_libs.md

[33mcommit ac646fdc2792204696688f0dfb3512205fcd1c23[m
Merge: 2c105e4 a1b466a
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:54:03 2016 -0700

    Merge branch 'working'

[33mcommit a1b466ab2fa0efea0448d09bc84b2651a65ba0bf[m
Merge: 5e596c8 e1970fe
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:53:59 2016 -0700

    Merge branch 'patch-1' of https://github.com/dbohdan/stb into working

[33mcommit 2c105e40fc646188fdb888f2e316b21e446c3769[m
Merge: 1e87fa4 5e596c8
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:53:27 2016 -0700

    Merge branch 'working'

[33mcommit 5e596c8c2d550c94a32b9cb2b51d92b0ba251af3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:52:28 2016 -0700

    other_libs: fix indentation

[33mcommit 5b3957a546ad36ab774279061cabb655b7e36c1a[m
Merge: 1976e1a 67e149f
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:45:35 2016 -0700

    Merge branch 'master' of https://github.com/xelatihy/stb into working

[33mcommit 1e87fa472f09185f51701eb57b6d08a2c40bfd9a[m
Merge: 6704bc4 1976e1a
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:44:53 2016 -0700

    Merge branch 'working'

[33mcommit 1976e1aee5430d8286ad5c0cf0c970457c8e969b[m
Merge: 7a02596 cc1f71c
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:44:45 2016 -0700

    Merge branch 'master' of https://github.com/jobtalle/stb into working
    
    Conflicts:
            docs/other_libs.md

[33mcommit 6704bc4023595f59c613d9e10b7858e9989a4fd6[m
Merge: 01dc6ab 7a02596
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:41:51 2016 -0700

    Merge branch 'working'

[33mcommit 7a02596aaeb15cdbacfc01cb2ac060bea023dbc4[m
Merge: 5db1194 0a5cb57
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:41:24 2016 -0700

    Merge branch 'otherlibs-dg_dynarr' of https://github.com/DanielGibson/stb into working

[33mcommit 01dc6abdcf37237863770872491e815f0261e94b[m
Merge: 6f72440 5db1194
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:40:31 2016 -0700

    Merge branch 'working'

[33mcommit 5db11942d1de86f11adc6f8c6925e0102553011e[m
Merge: 19c9615 5038c23
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:39:42 2016 -0700

    Merge branch 'master' of https://github.com/kieselsteini/stb into working

[33mcommit 6f72440159851b6057f4fc0c2e7dbbf5beab7235[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:38:09 2016 -0700

    bump version numbers

[33mcommit 19c9615e9048fa7f1b9e144ef847d12b093289f4[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:36:26 2016 -0700

    rect_pack patch;
    fix typo in stb_textedit

[33mcommit 5ad14faf388db09f1ecd70fa2aea19ee180460ad[m
Merge: 4e75868 2c71a43
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:35:29 2016 -0700

    Merge branch 'master' into working

[33mcommit 4e758682b006b9d527e70532d3e71ae77acbbd44[m
Author: cosmy1 <cosmy_rulezz@hotmail.it>
Date:   Tue May 3 23:37:49 2016 +0200

    Minor fixes.

[33mcommit 2c71a432066be3da2c8a9e818243b3dd6e3e2a3c[m
Merge: 50ec402 bde8f7c
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:33:04 2016 -0700

    Merge branch 'working'

[33mcommit bde8f7c102ffb7d1020302f585e775d8e1f7021a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:32:45 2016 -0700

    tweaks to stb_textedit custom-move-by-word patch

[33mcommit 841930cca4d7c04164684ded58f7f6d338e07c89[m
Merge: 094e8e9 75ce29f
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:25:29 2016 -0700

    Merge branch 'textedit-moveright-moveleft' of https://github.com/ocornut/stb into working

[33mcommit 50ec40269ded922164e9d0b1a89d8d40e68dabb4[m
Merge: f4d348d 094e8e9
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:24:05 2016 -0700

    Merge branch 'working'

[33mcommit 094e8e923bd4cb5b92a2a4c8a9b14ce22dfb65fe[m
Merge: 14e6a98 f710c23
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:23:37 2016 -0700

    Merge branch 'master' of https://github.com/kritzikratzi/stb into working

[33mcommit f4d348de8ed97669260dbe73a914454d638fc3bb[m
Merge: a2f50a1 14e6a98
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:17:05 2016 -0700

    Merge branch 'working'

[33mcommit 14e6a98469d8f378e5f6a1d77d166244fe452d6c[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:10:46 2016 -0700

    clarify alloca #include whitelists

[33mcommit f4938bfa4d81abf59c89fb0d0c4c942df10754e3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:09:01 2016 -0700

    Whitelist the compilers that need malloc.h for alloca

[33mcommit a2f50a1b6a9cb0dbb20d226b38a8103a7e6d6715[m
Merge: ec6e5e4 4806aca
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:03:10 2016 -0700

    Merge branch 'working'

[33mcommit 4806aca183000a472e621388f15cc907f4caeac3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat Aug 27 12:02:26 2016 -0700

    windows fwrite doesn't handle arbitrarily large writes (!);
    add a bunch of stuff used by my backup program 'smir';

[33mcommit ec6e5e40543c0c7d2dd6ddff6dc101011af10a67[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 27 09:48:58 2016 -0700

    Update other_libs.md

[33mcommit f9a04924af87a5566f7979c81b8c404b99d249ef[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 20 21:36:01 2016 -0700

    Update other_libs.md

[33mcommit 00c6078f9d78ea7fdd87f8a3c972f9aca24b2106[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 20 21:35:01 2016 -0700

    Handmade Math

[33mcommit 33b92cab0f9e96be74a552eda9e0b9c5dacdf1aa[m
Author: Terry Nguyen <terreh@terrehbyte.com>
Date:   Thu Aug 11 12:40:49 2016 -0700

    Fix link to tinyobjloader-c
    
    The repository has been been relocated by syoyo from tinyobjloader_c to tinyobjloader-c (note the dash)

[33mcommit 8eebc0915072ed988754d15d5e0b14ca6d6206b9[m
Author: Bryon Gloden, CISSP® <cissp@bryongloden.com>
Date:   Thu Aug 4 16:39:39 2016 -0400

    Update stb_c_lexer.h
    
    [stb_c_lexer.h:801]: (error) Memory leak: text
    [stb_c_lexer.h:801]: (error) Resource leak: f
    
    Found by https://github.com/bryongloden/cppcheck

[33mcommit e75ca4234e22aa8eb6d0c3dc767f9c521bda193e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jul 16 23:14:12 2016 -0700

    Update other_libs.md

[33mcommit 21ea5487ffef64de297672b9e6589507ba226d7a[m
Author: Aras Pranckevicius <aras@unity3d.com>
Date:   Thu Jun 30 21:46:17 2016 +0300

    Fix crash when resizing large images (signed integer overflow, e.g. at image size of 24000x24000)

[33mcommit 734576e6be5ace1eb1064a95d3d25fb783ed237e[m
Author: Patrick Boettcher <patrick.boettcher@posteo.de>
Date:   Wed Jun 15 10:36:39 2016 +0200

    image-write: fix monochrome bitmap writing from 8-bit-buffers
    
    Now writing out monochrome bitmaps from 8-bit arrays works
    as it does when using PNG.
    
    Bitmaps need 3 bytes per pixel.

[33mcommit e1970fe45621022ac1267392c5ec5d6e6c3fff42[m
Author: Danyil Bohdan <danyil.bohdan@gmail.com>
Date:   Sat Jun 4 11:44:17 2016 +0300

    other_libs.md: Update link for LIL

[33mcommit 94dd6fe796464890e53d0f2db0b5aab04ed7091e[m
Author: Eric Engestrom <eric@engestrom.ch>
Date:   Thu May 26 22:48:01 2016 +0100

    README.md: add direct links to files

[33mcommit a2bf7592b6e7a70ef5b0ff8896894d232ebb67f5[m
Author: Viktor Kirilov <vik.kirilov@gmail.com>
Date:   Sun May 22 16:18:07 2016 +0300

    added doctest to the list with testing frameworks

[33mcommit cc1f71c0d16a2a436aef158645cb0da2de69bb88[m
Author: Job Talle <jobtalle@hotmail.com>
Date:   Thu May 19 13:50:31 2016 +0200

    Changed license to public domain

[33mcommit 365441bc7dc5b7bab64fc0221f8b1466766a0a3d[m
Author: Lewis Van Winkle <lv@codeplea.com>
Date:   Wed May 18 11:54:11 2016 -0500

    Added Genann (neural networks)

[33mcommit c9ead07188b342350530e92e14542222c3ad9abe[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat May 14 21:59:06 2016 -0700

    Update other_libs.md

[33mcommit 67e149fe18ce9b6b5c1397c9751e6734913ebf61[m
Author: Fabio Pellacini <fabio.pellacini@gmail.com>
Date:   Sun May 8 19:07:29 2016 +0200

    Update other_libs.md

[33mcommit d38d37c4ef8f41656d44d535b2066b0da0cb6faa[m
Author: jobtalle <jobtalle@hotmail.com>
Date:   Sat May 7 11:25:54 2016 +0200

    Made link bold

[33mcommit be5bf3213023b488fc8be62b18062bc868b57e4b[m
Author: jobtalle <jobtalle@hotmail.com>
Date:   Sat May 7 11:24:32 2016 +0200

    Added ccVector reference

[33mcommit 0a5cb5770605a9d46503ac723ed3dff600a56638[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Fri May 6 01:07:45 2016 +0200

    other_libs.md: Add DG_dynarr.h

[33mcommit 2c047c7a2713d45f119f4724844ef25108aca067[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu May 5 14:53:42 2016 -0700

    Update other_libs.md

[33mcommit 5038c23d8f719be5b904955e07f6bfe743c89037[m
Author: Sebastian Steinhauer <s.steinhauer@yahoo.de>
Date:   Thu May 5 20:44:49 2016 +0200

    Added sts_net / sts_mixer to other libraries list

[33mcommit b9c23b5e8c74ad25931397649acd2ba94111ff7e[m
Merge: daecce0 6427092
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu May 5 00:01:30 2016 -0700

    Merge pull request #296 from jimon/patch-1
    
    tigr now supports osx

[33mcommit 64270925155c3d40ee8c3cbd54b1affd91594847[m
Author: Dmytro Ivanov <jimon.j1m0n@gmail.com>
Date:   Thu May 5 01:08:04 2016 +0200

    tigr now supports osx

[33mcommit daecce07d52a6a6759df63826f19afa5b2a893a5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 3 13:51:46 2016 -0700

    Update other_libs.md

[33mcommit f710c23bf7f6b6482e555405f72403a3c3c03167[m
Author: Hansi Raber <super@superduper.org>
Date:   Fri Apr 29 04:45:55 2016 +0200

    stb_textedit/stb_text_locate_coord:
    fix cursor position in the "shouldn't happen, but if it does, fall through to end-of-line case" case (`i=0` causes problems with the return values in this case)

[33mcommit e2505ba00c5c0bb1b4c39174052cb78c6202dac8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 19 09:32:23 2016 -0700

    Update other_libs.md

[33mcommit 25b476af56be1e11a5af059e963ca29cb19a0fad[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 19 07:58:48 2016 -0700

    Update other_libs.md

[33mcommit d529e0455502132acdb3d4ee1433b58a00b9329f[m
Merge: aa1041b 72e10c7
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 19 07:57:08 2016 -0700

    Merge pull request #286 from tversteeg/master
    
    Add @vurtun his nuklear library to Other Libraries

[33mcommit 72e10c7e210799ea96d684256445ad687ea50839[m
Author: Thomas Versteeg <thomasversteeg@gmx.com>
Date:   Tue Apr 19 16:01:10 2016 +0200

    Fix the nuklear library in other_libs.md
    
    Change the usable language from C to C/C++

[33mcommit 376774cb354ced932c10e23705544dbd9d2d88bf[m
Author: Thomas Versteeg <thomasversteeg@gmx.com>
Date:   Tue Apr 19 13:24:18 2016 +0200

    Add @vurtin his nuklear library to other_libs

[33mcommit aa1041bae807d58894b2fa95947d2c01dd591d17[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 17 09:16:54 2016 -0700

    stbcc 0.94

[33mcommit 25b1f563d1bfc77750b33ae06cdeb905ae482dbf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 17 09:16:26 2016 -0700

    stbcc 0.94

[33mcommit 51393c0a7a0dcc44e547ce9b774efc6c4c9e0103[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 17 08:45:06 2016 -0700

    remove dead code after previous optimizations

[33mcommit d1eba3330529205c33fee6a8ac5242f8d87f0ccc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 17 08:12:52 2016 -0700

    fix bug w/ large clumps per cluster;
    reduce time spent on global union-find by skipping clumps that don't touch edges

[33mcommit 484605343fa12cf83532d3261a14b56fb1060e86[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 14:14:04 2016 -0700

    memory usage clarification

[33mcommit 5ebbfd02e96779112569a0ac7ee74e4b74512ac3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 14:08:03 2016 -0700

    update readme

[33mcommit ad55a9b383dd7dc9846a303c2e0a56a719fab2b7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 14:05:40 2016 -0700

    version 0.93
    assign surplus adjacency storage only to clumps that touch edge
    document timings and memory usage

[33mcommit 0b50f1e8d6843efff9046d45a0727c6e91844335[m
Merge: a719308 667f795
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 13:13:00 2016 -0700

    Merge branch 'working' into test

[33mcommit 667f79589a2475a97839dbd0f5c1c2a4392c22b1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 12:58:37 2016 -0700

    forgot to include stb_connected_components test source file

[33mcommit a7193080f786bb8057d7540c4294cbe531bce00e[m
Merge: 1d6e55a e585dad
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 12:39:46 2016 -0700

    Merge branch 'working' into test

[33mcommit 1d6e55ab1e2b39f9fcca194022dd98875b07d967[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 12:32:40 2016 -0700

    reduce storage for stb_connected_components.h

[33mcommit e585dad291c07afe6dd955d4c605fe57c69243b3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 11:21:59 2016 -0700

    change map image formats to workaround stb_image bug

[33mcommit 0214a3c71f33ea798921c425578ef5455c2d7fe8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 10:04:03 2016 -0700

    untested simple batching;
    document algorithm;
    automatically use sqrt(N) instead of 32 as cluster size

[33mcommit 1392344cdde1529b1ea1163e258e721b0f3d13b3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 16 09:14:39 2016 -0700

    include stb_connected_components.h in main stb compile tests, add test app

[33mcommit 435e0c757ce93c7238de1fc2e2518f9aef48dec6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 15 21:41:08 2016 -0700

    update stbcc

[33mcommit d32dc9f43a35ad23f81f422109b7e2b6a3690e27[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 15 21:40:37 2016 -0700

    add todo list, try to compile as C++ (untested), tweak data structure

[33mcommit 31bc5d1ecc91bfb91acd639516147a63e8c425c1[m
Merge: 1c5a924 133a565
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 15 19:22:42 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 1c5a92440d7850a551a53d19c5183c982a4b1230[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 15 19:22:22 2016 -0700

    stb_connected_components added

[33mcommit 133a5656246de5a6ab202d5317c02a1d27fc3e37[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 14 07:30:23 2016 -0700

    yocto stuff

[33mcommit 4c519106a7c3862524100f907736c1c74412725d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 4 18:39:30 2016 -0700

    back out previous change to stb_vorbis (truncation of last frame in corrupt file)

[33mcommit 75ce29fe0b1d17c05b56a447a78831a9cf585f2e[m
Author: ocornut <omarcornut@gmail.com>
Date:   Sat Apr 2 23:55:01 2016 +0200

    stb_textedit: Add support for custom move word left/right handlers

[33mcommit 5aef2b50aa230eafb34e6ddd0ff6d13dbfd4ad2f[m
Merge: 62d773d fdca443
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 13:46:39 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 62d773db5db889e5a5000627625173ec9affd7a6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 13:46:11 2016 -0700

    updat versions

[33mcommit a1a918a4877c6831e48ee69f8026f2f810257c24[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 13:45:32 2016 -0700

    fix unused variable warning

[33mcommit fdca443892d0ce3c8680e6f38f196c61e95c7de3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 07:29:34 2016 -0700

    fix crash in 2.11

[33mcommit 136455df6db9d5868411d3136ae8b70fe11ed081[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 04:55:44 2016 -0700

    clarify

[33mcommit fcdf5c682ebfc4a0a89d1fb801ac59d483bdd9d3[m
Merge: 6e41547 b7603b0
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 04:52:02 2016 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 6e4154737c51c1298e35cc6fc387dd365cc32ac9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 04:51:26 2016 -0700

    update version numbers, documentation, and contributors

[33mcommit b03133000a7f7d49aa3ce57bb5fa1975dd41db21[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 04:20:36 2016 -0700

    avoid dropping final frame of audio data due to wrong test

[33mcommit 7a694bdccafb2995936a81dd1ab27065da514019[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 04:01:59 2016 -0700

    re-enable SSE2 code on x64 except with gcc

[33mcommit 92bd7a49a8b899c56db45976afb338bc4bd2c65a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:57:17 2016 -0700

    emscripten needs explicit alloca as well

[33mcommit 56e8fd063ce8105ba05884a540763068b744bf2f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:55:03 2016 -0700

    don't leak vertex data if text is scaled to 0

[33mcommit 538b96d6e2fe72ce1627dbcb2df0f891d03732ef[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:52:47 2016 -0700

    remove claims of supporting C++ in stretchy_buffer

[33mcommit 5990ff8a476ad890a42649179b346355daa0133f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:51:19 2016 -0700

    remove duplicate typedef of stbtt_fontinfo

[33mcommit 201af99d9fd26bae939ad7f2395920476f78d7f1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:49:46 2016 -0700

    return correct # of channels for PNG

[33mcommit 65edb64dd81785a8e5a28c1935c8938089dced24[m
Merge: 8420e20 75c5908
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:45:01 2016 -0700

    Merge branch 'master' into working

[33mcommit 75c5908f951513bdc619fd7c9cb3b96283d4f397[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:41:26 2016 -0700

    fix includes for linux alloca

[33mcommit 591c7f8cb348a3915a4afa64e102e7b225119cd6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:40:55 2016 -0700

    remove white matting when loading transparent PSD

[33mcommit a8876b884d6a916497e534d0b241734a79f46db9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:40:42 2016 -0700

    fix _WIN32 if STB_THREADS

[33mcommit aeba55604a52690921ea3e94543d017906c6aa21[m
Author: Jörn Heusipp <osmanx@problemloesungsmaschine.de>
Date:   Thu Mar 24 18:20:39 2016 +0100

    stb_vorbis: Fix memory leak in start_decoder().

[33mcommit b7603b0ca6245ea6ff61b8bfb713dda0c5261f88[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 03:34:51 2016 -0700

    dr_flac

[33mcommit 8420e20af62c25fc58eb8b44c2b0d4fa1cc81979[m
Merge: ba1277e 0e3506d
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:59:53 2016 -0700

    Merge branch 'for-upstream-fix-stbvorbis-startdecoder-memleak' of https://github.com/manxorist/stb into working

[33mcommit 8f368799e16f14f84cf694396c5244bbffa8f688[m
Merge: c03f4b3 0985e89
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:58:19 2016 -0700

    Merge branch 'for-upstream-stbvorbis-fix-memleaks' of https://github.com/manxorist/stb

[33mcommit c03f4b3c2f45653219643098a2ebb747fa0eb17a[m
Merge: 097a70a 94f2cea
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:57:34 2016 -0700

    Merge branch 'patch-1' of https://github.com/kinetiknz/stb

[33mcommit 097a70ae3844f8691562f2c6aebcffa9e558421b[m
Merge: ba1277e 7e1ee2d
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:56:39 2016 -0700

    Merge branch 'master' of https://github.com/tulrich/stb

[33mcommit ba1277e39cd9b6b961a5ff9603fc122ff4ffb2e1[m
Merge: a013c03 5a00ce3
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:54:53 2016 -0700

    Merge branch 'fix_warnings' of https://github.com/tgoulart/stb into working

[33mcommit a013c036f3edc80c67ddb9556dd1d9a986cd6af7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:54:25 2016 -0700

    initialize bmp mr/mg/mb/ma properly

[33mcommit 218ecd17a407e353124af4e29282049df22ea896[m
Merge: 406d537 d4f552b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:42:17 2016 -0700

    Merge branch 'patch-1' of https://github.com/looki/stb

[33mcommit 406d537b41942bd668bb2b49832b6ff4e6e17bd1[m
Merge: 275d120 eb84b21
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:41:16 2016 -0700

    Merge branch 'initial_png_16bpc' of https://github.com/socks-the-fox/stb into working

[33mcommit 275d1204b1280659bf1cd7053917d641bd328388[m
Merge: 814bb9b 4be8fa9
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:38:07 2016 -0700

    Merge branch 'working'

[33mcommit 4be8fa919f193090b34bee2346f05b14309e04f9[m
Merge: 878e8ca 4ef7d07
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:37:51 2016 -0700

    Merge branch 'pull-request-fabs2' of https://github.com/sglass68/stb into working

[33mcommit 814bb9b5dcda1942d20d96e8d97505fde96b73a0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:36:24 2016 -0700

    remove STBIR__DEBUG_ASSERT because it requires defining/not-defining assert() in a warning-free way on all platforms independent of #include <assert.h>, which is too hard

[33mcommit d514035d70c8f5d68684587ffb1e6d1a700d7f21[m
Merge: 878e8ca 9dc860b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:32:51 2016 -0700

    Merge branch 'textedit-drag-while-typing' of https://github.com/ocornut/stb

[33mcommit 878e8caaa6743a02699778960835e420df8aab7b[m
Merge: cbc1e7c d113bea
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:31:12 2016 -0700

    Merge branch 'patch-1' of https://github.com/saolsen/stb into working

[33mcommit cbc1e7c8978f22de15502d4dcff766546b4445f0[m
Merge: efdfbb3 4ff6723
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:13:41 2016 -0700

    Merge branch 'test' into working

[33mcommit 4ff6723a6d7099b32a8bca2c0fc9438109476b17[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 02:13:20 2016 -0700

    make resample_test work in VC6

[33mcommit c238cebe6a435986596ed1830302f5c69382c212[m
Merge: a222dc5 5e2d0fd
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 2 01:46:09 2016 -0700

    Merge branch 'master' of https://github.com/BSVino/stb into test

[33mcommit 86bff62371351e6d17f4cd20a11168d6616a1a09[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 1 22:15:47 2016 -0700

    greatest; munit; parg

[33mcommit c66b565cb31454533a031df09fe4bef03e344120[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 1 22:06:19 2016 -0700

    cro_mipmap

[33mcommit b79fa5b08c3f3f1bc232a9c75a43e7ac2fd6b1df[m
Merge: a222dc5 46b64eb
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 1 21:46:42 2016 -0700

    Merge pull request #255 from corporateshark/master
    
    Added PoissonGenerator.h

[33mcommit efdfbb3c7c70afe57f22de5abc323c6fab1f3097[m
Merge: 50479cb a222dc5
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Apr 1 21:43:22 2016 -0700

    Merge branch 'master' into working

[33mcommit a222dc519ec51b8e6810648a86e471ab7e53aa0c[m
Merge: 8aa9afb 20f2eec
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Mar 26 15:49:33 2016 -0700

    Merge branch 'license' of https://github.com/oon3m0oo/stb into work2

[33mcommit 50479cb07c765229e78420feb126f9fd218d1357[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Mar 26 15:46:59 2016 -0700

    stb_image: allow jpegs that are rgb not YCrCb

[33mcommit 0e3506d7d187a12413cac1c6fc7f5055e76f7bd8[m
Author: Jörn Heusipp <osmanx@problemloesungsmaschine.de>
Date:   Thu Mar 24 18:20:39 2016 +0100

    stb_vorbis: Fix memory leak in start_decoder().

[33mcommit 0985e893350d4a599d36de7da94e6bf4101ecdd0[m
Author: Jörn Heusipp <osmanx@problemloesungsmaschine.de>
Date:   Thu Mar 17 09:23:45 2016 +0100

    stb_vorbis: Fix memory leak in decode_residue() and inverse_mdct() when redefining temp_alloc() and temp_free()
    
    temp_alloc() and temp_free() are documented as customization points in section "MEMORY ALLOCATION" (stb_vorbis.c:81).
    However, in decode_residue() and inverse_mdct() (via temp_block_array() and temp_alloc() respectively), stb_vorbis allocates temporary memory but does not call temp_free() when finished. It does call temp_alloc_restore() though, but there is no sane way to provide an implementation thereof when using a malloc()/free()-like allocation backend.
    
    Adding calls to temp_free() before the respective calls to temp_alloc_restore() is safe, because in case of a non-empty temp_alloc_restore() implementation, temp_free() would simply be implemented empty (the current implementation of temp_*() is fine in this regard). That way, all possible temporary memory allocation schemes (i.e. alloca(), custom provided alloc_buffer, malloc()) are handled properly.
    
    Add the appropriate temp_free() calls.

[33mcommit 94f2ceac1595d7297d76a734fcd1bc111622f6dd[m
Author: Matthew Gregan <kinetik@flim.org>
Date:   Sat Mar 12 01:55:59 2016 +1300

    Fix typo in stbi__parse_uncompressed_block

[33mcommit 46b64eb878e7cb8c953dafc021fe5d036b4f6101[m
Author: Sergey Kosarevsky <sk@linderdaum.com>
Date:   Thu Mar 10 19:49:38 2016 +0100

    Added PoissonGenerator.h

[33mcommit 8aa9afb30e6aeb129235829c5e0ed41b6562ea37[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Mar 7 20:44:59 2016 -0800

    typo

[33mcommit b9bc6148d4c00da9b6a99a825ca6cf3b19cd06b6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Mar 7 20:44:29 2016 -0800

    linalg.h

[33mcommit 7e1ee2d386b7ec334cf01660ced88426e5188a40[m
Author: Thatcher Ulrich <tulrich@tulrich-macbookpro2.roam.corp.google.com>
Date:   Wed Mar 2 15:56:53 2016 -0500

    Allocate large structure using malloc instead of stack.

[33mcommit 291ad22e84d18bea400873adc991b2d324bc7cda[m
Author: Thatcher Ulrich <tulrich@tulrich-macbookpro2.roam.corp.google.com>
Date:   Wed Mar 2 15:31:07 2016 -0500

    Replace large stack allocations with dynamic allocations.

[33mcommit 5a00ce39eb97c6323bf69a3e5fb0b7411607dc6d[m
Author: Thiago Goulart <thiago@pocketgems.com>
Date:   Wed Mar 2 00:50:40 2016 -0800

    Fix a few warnings when building std_vorbis using Xcode 7.2.1

[33mcommit 20f2eec0241301b89db070149570a334651643d2[m
Merge: ee6978c 49b65c0
Author: Craig Donner <cdonner@google.com>
Date:   Thu Feb 25 13:02:58 2016 -0800

    Update license with a few more tweaks and better English grammar.

[33mcommit ee6978cb6891632e3fe84264f832140e590b43f0[m
Author: Craig Donner <cdonner@google.com>
Date:   Wed Feb 10 14:48:59 2016 -0800

    Slightly modify the public domain license to keep it in the public domain, but make it clear that even when dedications might not be recognized that the code is still usable.  Given that this isn't dual-licensing under a different license, I'm hoping this will be acceptable.

[33mcommit a83ab31335f8b223908a9b38c6ba3febbc1debd8[m
Merge: a4c0a5e c0774cc
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Feb 22 14:07:57 2016 -0800

    Merge pull request #248 from ReadmeCritic/patch-1
    
    Update links for par_shapes, fastlz

[33mcommit c0774cc7ebe2c55cd5bc2a38cd2e5fd4f5c085c8[m
Author: ReadmeCritic <frankensteinbot@gmail.com>
Date:   Mon Feb 22 08:50:47 2016 -0800

    Update links for par_shapes, fastlz

[33mcommit a4c0a5e88204d799a2db43213c859b36c74850bf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Feb 22 06:26:21 2016 -0800

    Update other_libs.md

[33mcommit 32b19a6c8b25ef621f9efe23d03d5a552975dce3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Feb 20 02:15:04 2016 -0800

    Update other_libs.md

[33mcommit 49b65c08734500f5ebabaae9f758ed272e28e18e[m
Author: Craig Donner <cdonner@google.com>
Date:   Wed Feb 10 14:48:59 2016 -0800

    Slightly modify the public domain license to keep it in the public domain, but make it clear that even when dedications might not be recognized that the code is still usable.  Given that this isn't dual-licensing under a different license, I'm hoping this will be acceptable.

[33mcommit 5e2d0fd777964e05ac4c8a466b6f507dda6a4483[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Feb 9 19:40:18 2016 -0800

    Add support for obtaining the entire kerning table from a font all at once, for use in rendering packed textures offline.

[33mcommit ff862a2a461edec60c9d0a9d521a5ab381ccc84d[m
Merge: 831b2d2 955dfe9
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Feb 9 19:37:07 2016 -0800

    Merge https://github.com/nothings/stb

[33mcommit 955dfe991b26f6fb1287ec0093f606843487b099[m
Merge: a78bc16 d35dbc4
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jan 28 13:07:09 2016 -0800

    Merge pull request #238 from dbohdan/master
    
    other_libs.md: Update Picol

[33mcommit d35dbc4368b0a341b24ac6e40a0f62cc2cf15310[m
Author: Danyil Bohdan <danyil.bohdan@gmail.com>
Date:   Thu Jan 28 16:42:13 2016 +0200

    other_libs.md: Update Picol

[33mcommit a78bc165b971f123314896ecda957b82688eb2a7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:29:13 2016 -0800

    Update other_libs.md

[33mcommit 124669a8f5eb7a32248845f4b2e731f86c45864d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:28:23 2016 -0800

    Update other_libs.md

[33mcommit 6fb227061759ae591f14bcb6460deb6d8a942775[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:27:51 2016 -0800

    Update other_libs.md

[33mcommit 1d95d24ae92622e18bef53010ff08b157d87f302[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:26:47 2016 -0800

    Update other_libs.md

[33mcommit b8a9e19f867eed1457817db0ea65335271e5119e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:23:45 2016 -0800

    Update other_libs.md

[33mcommit a1169d90d07df9b7cffba977d366a36d79862ead[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:22:16 2016 -0800

    Update other_libs.md

[33mcommit 6e556fe7572e2ab342a2b4dfbd2fa2f91df64569[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 12:08:20 2016 -0800

    Update other_libs.md

[33mcommit c63e60849705c1be1e676e2f69588b3570e53d73[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 11:42:11 2016 -0800

    Update other_libs.md

[33mcommit b9504633b9cae7d7dc5f3256cd07cbb5d98d3656[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 10:23:34 2016 -0800

    Update other_libs.md

[33mcommit ccfca5a5dacb56b6c02698b510bc382be42f566b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:45:05 2016 -0800

    Update other_libs.md

[33mcommit 547c951091eff1495a1d5b4108ce00242b3364a4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:43:34 2016 -0800

    Update other_libs.md

[33mcommit f4a878dbf9c38eff173dff2159a808a80636bc79[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:40:04 2016 -0800

    Update other_libs.md

[33mcommit 49f971110f9f2414a472a666e186b01dfcd27800[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:39:30 2016 -0800

    Update other_libs.md

[33mcommit a4a27ea3cdb09a507b39dcf2b405f333b01757ac[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:36:59 2016 -0800

    Update other_libs.md

[33mcommit 47796836b6e45a020e3948f47b5f87491712cf35[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 08:02:05 2016 -0800

    Update other_libs.md

[33mcommit 229ebfa4ffb102ce41a9626f1edb4fa6a96f88e5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 07:15:03 2016 -0800

    Update other_libs.md

[33mcommit 78befd33e91f18ce8bff7d9aa8a5f59bd6797779[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 06:57:37 2016 -0800

    Update other_libs.md

[33mcommit 4dd8cf9ae83a8b88edb2ec85809b0194d07fa6ce[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 06:25:38 2016 -0800

    Update other_libs.md

[33mcommit 7a889d272a65322ed5dd514018ff645507918b4d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 06:16:48 2016 -0800

    Update other_libs.md

[33mcommit 420c68ac83e806c3b58dff3606613426c15b91b3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 06:07:23 2016 -0800

    Update other_libs.md

[33mcommit 983630e7b0e18efe07fb125294e2fc17d8a03bf3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:59:25 2016 -0800

    Update other_libs.md

[33mcommit bb7355f4b1ed1560994d14f0987950af6f80b7d4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:50:38 2016 -0800

    Update other_libs.md

[33mcommit e1bc6029b97ca6f4e3c8f84b6ab83af660aa9e9f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:48:34 2016 -0800

    Update other_libs.md

[33mcommit cbbd2d053f36c3de26a124b6433810c398319585[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:47:02 2016 -0800

    Update other_libs.md

[33mcommit 94106a8fdd8938f0ab11794cf597ff41102a015a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:38:05 2016 -0800

    Update other_libs.md

[33mcommit 91402d1a0de83d66a4bb6f82d4cac9dca528be84[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:36:11 2016 -0800

    Update other_libs.md

[33mcommit fc5009027d76e5f8bfa57375835a4001879db311[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 26 05:31:12 2016 -0800

    Update other_libs.md

[33mcommit 1de24920028909bd18f6a0952d225fa1dccce5c3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 23:44:21 2016 -0800

    Update other_libs.md

[33mcommit b0b3c2633d58c2b01d084afd5cc7fb8686079079[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 14:39:54 2016 -0800

    Update other_libs.md

[33mcommit 0e76e2ca8400333027f6439cd71ab2e758a0db39[m
Merge: a327849 02b90e8
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 14:38:29 2016 -0800

    Merge pull request #235 from dbohdan/master
    
    other_libs.md: Add Picol

[33mcommit 02b90e8fb5730d34e19f78f27be2e8ce2173e5e6[m
Author: Danyil Bohdan <danyil.bohdan@gmail.com>
Date:   Sat Jan 23 23:02:10 2016 +0200

    other_libs.md: Add Picol

[33mcommit a3278496a838f324f1af142c6213b94b5b49460e[m
Merge: 6a5590e 97a7c1b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 10:19:51 2016 -0800

    Merge pull request #234 from dbohdan/master
    
    other_libs.md: Add LIL

[33mcommit 6a5590e11e5331c6f218a82f212f54469fac4e0b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 10:16:34 2016 -0800

    Update other_libs.md

[33mcommit 97a7c1ba9b70ccf0175c28e3097ee584c07f2f86[m
Author: Danyil Bohdan <danyil.bohdan@gmail.com>
Date:   Sat Jan 23 20:14:44 2016 +0200

    other_libs.md: Add LIL

[33mcommit 97b614a080a4345f99fe65afd2cdeeb7662edb64[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 10:14:43 2016 -0800

    Update other_libs.md

[33mcommit c2a4ff554d45209511f5102f29c8d7fa5b8a2236[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:40:42 2016 -0800

    Update other_libs.md

[33mcommit 3a4e6485b45f35a86f783d3db0320624c4dd2d6c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:39:51 2016 -0800

    Update other_libs.md

[33mcommit 143834ed420400514d706e6eaecc78a52f55d372[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:38:32 2016 -0800

    Update other_libs.md

[33mcommit 4aff4632f3ab811e71c44301d94f4e75f4707cfe[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:37:32 2016 -0800

    Update other_libs.md

[33mcommit 9fe0dc93a425defcc4e09be6e0bcff68ba8cb983[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:30:37 2016 -0800

    other_libs gets more guidelines

[33mcommit d1770130614dc4106f40fec168877147d61fe966[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 09:21:29 2016 -0800

    add submission notes, cleanup easyexif

[33mcommit d9552a9c510629f178454b3175f847def5316457[m
Author: Mayank Lahiri <mlahiri@gmail.com>
Date:   Sat Jan 23 09:11:31 2016 -0800

    Add easy_exif to other_libs.md
    
    EasyEXIF is a tiny, lightweight C++ library that parses basic information out of JPEG files. It uses only the std::string library and is otherwise pure C++. You pass it the binary contents of a JPEG file, and it parses out a few of the most important EXIF fields for you.

[33mcommit 6308d725f40132a4278edf15a8a50dd270adab51[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 08:55:28 2016 -0800

    update other_libs.md

[33mcommit 32b07e331f1c3e0bfc58dc8bb72ada74b0d015f7[m
Merge: 5de39a0 c26f400
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 08:48:02 2016 -0800

    Merge branch 'master' of https://github.com/codeplea/stb
    
    Conflicts:
            docs/other_libs.md

[33mcommit 5de39a0365896fcf6b0eaf65cd6ce36bb571261a[m
Merge: 9c8762a 825e97b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 08:45:50 2016 -0800

    Merge branch 'master' of https://github.com/nothings/stb
    
    Conflicts:
            docs/other_libs.md

[33mcommit 9c8762a1565b50dedbf2fec3834d91e6adc9a2c9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 08:44:27 2016 -0800

    update other_libs.md

[33mcommit c26f400e6f8e62154cd99d0663d68bb821ddc272[m
Author: Lewis Van Winkle <lv@codeplea.com>
Date:   Sat Jan 23 10:25:23 2016 -0600

    Added minctest and tinyexpr.

[33mcommit 825e97b680e837d206e95611ca1b677889038a71[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 06:49:31 2016 -0800

    Update other_libs.md

[33mcommit 448275b1945da68ae6e42ed6155574ecf6877119[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 05:58:11 2016 -0800

    Update other_libs.md

[33mcommit 9bbc3ae812417ffec9c1b860458b2e455223b96b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 05:25:35 2016 -0800

    other_libs: indicate whether libraries are usable from C or C++

[33mcommit 99dc799f2a241af62da754418a6b240a6c267561[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 05:09:04 2016 -0800

    reformat other_libs source to prepare for new columns

[33mcommit 90fe6b1c0f4475b1adc8aab8ba3a9f1a3bbe7339[m
Merge: 32c2bfa 5bcfa00
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 23 04:08:13 2016 -0800

    Merge pull request #229 from kgabis/patch-1
    
    Adds parson to other_libs.md

[33mcommit 5bcfa002429b7397396ae620ced51199d0b7ff9b[m
Author: Krzysztof Gabis <kgabis@gmail.com>
Date:   Sat Jan 23 10:05:57 2016 +0000

    Adds parson to other_libs.md
    
    Parson is a 2-file (.h and .c) JSON parser and serializer written in C.

[33mcommit d4f552b39377d9bce44e492ef972f5ab1203ef97[m
Author: Lukas Meller <mmflooki@gmail.com>
Date:   Sat Jan 23 03:41:03 2016 +0100

    Fixed typo

[33mcommit 32c2bfad333f75e8b8dc002581bd0c33d8b41b26[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 12:41:46 2016 -0800

    Update other_libs.md

[33mcommit ff51a1bd6b9699fb20fa5c495e835e6742b23a08[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 12:40:13 2016 -0800

    Update other_libs.md

[33mcommit 43e845d7109bc26ae81bed1a5737198c6544025b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 12:38:35 2016 -0800

    Update other_libs.md

[33mcommit b373cf536a48723e19ea30e0ae336680345c1325[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 12:37:11 2016 -0800

    Update other_libs.md

[33mcommit eb84b2179b059aef3a0ceb5fc9a8b66b9de81234[m
Author: Socks the Fox <jade@socksthefox.net>
Date:   Mon Jan 18 10:42:41 2016 -0600

    Initial 16 bit per channel PNG support

[33mcommit d712fafeb1ea72c73e0747dc1db40d7ef3696645[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 07:01:56 2016 -0800

    fix last check-in

[33mcommit 19223d2f0a2164e731f77cce327450708825f673[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 07:01:14 2016 -0800

    avoid line-break in "public domain"

[33mcommit b9a29d9b5be7a6d5c6d8253c06317c5baa2fb727[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 06:59:09 2016 -0800

    reorganize other_libs by category

[33mcommit bb5917fa9362bf01de14c0865266345b1d549cb3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 06:58:57 2016 -0800

    update readme

[33mcommit ec3fecd27f5d4cb916c2f02cae92a49b9d36f537[m
Merge: e0dafae 820f63b
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 05:17:55 2016 -0800

    Merge branch 'stb_h_fix'

[33mcommit e0dafae042fce60939ea5a6de991e37e85db140b[m
Merge: 8f9be5a 8b144eb
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 05:17:46 2016 -0800

    Merge branch 'working'

[33mcommit 820f63be441101bbb255d5b583a1495a0884c91a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 05:17:12 2016 -0800

    stb_tilemap_editor: fix typo in docuemtnation, update version & credits

[33mcommit a33e40b1d4d01648238ef4522f16b3e9bdc33a07[m
Merge: 7d4f7c5 412e1ec
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 05:05:30 2016 -0800

    Merge branch 'master' of https://github.com/timsjostrand/stb into stb_h_fix
    
    Conflicts:
            stb.h

[33mcommit 7d4f7c566ebfdbf5bc47dbf9775a50310de30d25[m
Merge: c41629f a5bbc93
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 05:00:03 2016 -0800

    Merge branch 'master' of https://github.com/eugeneopalev/stb into stb_h_fix

[33mcommit c41629f2626f8305bb75d7acb80653d2dff8ffd6[m
Merge: 8c5a442 a4ab8c0
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 04:58:41 2016 -0800

    Merge branch 'master' of https://github.com/blackpawn/stb into stb_h_fix

[33mcommit 8c5a442960368c98e4f9d34b0b64540bd6a4fac1[m
Merge: e27cb7f 8d9302a
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 04:57:38 2016 -0800

    Merge branch 'readdir_raw' of https://github.com/mikesart/stb into stb_h_fix

[33mcommit e27cb7fcbf1606315f259ed7c2622a2a1e7aa328[m
Merge: 8b144eb ba40683
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 04:57:25 2016 -0800

    Merge branch 'master' of https://github.com/mikesart/stb into stb_h_fix

[33mcommit 8b144eb536598ea51310be0c3c97523fd5b79d49[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 04:27:47 2016 -0800

    stb_easy_font: support '\n' in _width(), add _height() [untested]

[33mcommit 30015ef46442b58d42f223d8a4fbc42a961a7afe[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jan 22 04:06:28 2016 -0800

    attempt to fix unused var warnings in stb_image 2.09

[33mcommit 8f9be5adfc6e948dae79303dfab8fcd642658c39[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jan 21 06:35:48 2016 -0800

    Update other_libs.md

[33mcommit a5bbc93087575e82f927cbf9e9e3e2a5c1e2c4d9[m
Author: Eugene Opalev <eugeneopalev@gmail.com>
Date:   Mon Jan 18 22:41:17 2016 -0800

    Warning C4005 fix

[33mcommit bc1b1f6cc993d87aff438cfd1fb550a36fe2780d[m
Author: Eugene Opalev <eugeneopalev@gmail.com>
Date:   Mon Jan 18 19:38:07 2016 -0800

    Warning C4703 fix

[33mcommit 3364990ac3b858c38976bb24dee277a7c61f8ff8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 18 13:24:17 2016 -0800

    Update other_libs.md

[33mcommit 4ef7d07a442cb7b3277a3f3405a12042e1feb2c4[m
Author: Simon Glass <sjg@chromium.org>
Date:   Sun Jan 10 19:58:23 2016 -0700

    ttf: Correct direct use of fabs()
    
    Add a macro to allow fabs() to be provided by the user, as with the other
    maths functions. Update the implementation code to use it instead of fasb().
    
    Signed-off-by: Simon Glass <sjg@chromium.org>

[33mcommit 48ec72ac12383a8bbfa567c41b85184b60ad2f4a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:26:36 2016 -0800

    Update stbtt_fontinfo.userdata field on paths where user never has access to it.

[33mcommit ad9a570e271a8b00ac9574415feee6cc9dd597fb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:20:54 2016 -0800

    stb_truetype version history; update README

[33mcommit 667d84086049f9a9b8c3dda82635729704e78cd4[m
Merge: 418d21f f1d2002
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:17:15 2016 -0800

    Merge branch 'working'

[33mcommit f1d2002a1db72294478943146052de7fac452327[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:16:23 2016 -0800

    update contributor list

[33mcommit 58484eb73d0e1780dc7c507a3631c46d5dcd94fd[m
Merge: 9f081b6 8cea009
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:11:54 2016 -0800

    Merge branch 'implicit_cast_fix' of https://github.com/filipwasil/stb into working

[33mcommit 9f081b62a4c85ebc79e7482f1038a068859a70c6[m
Merge: 099cd5a 22dd50f
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:11:00 2016 -0800

    Merge branch 'stbiw_documentation_typo' of https://github.com/karjonas/stb into working

[33mcommit 099cd5a279487884a14b2bf6281a6ea44639b67a[m
Merge: 8521c38 b95858a
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:10:07 2016 -0800

    Merge branch 'msvc_runtime_cast_fixes' of https://github.com/karjonas/stb into working

[33mcommit 8521c38956577468acc4c942348fb563ee0f2646[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:09:35 2016 -0800

    tweak previous crc commit

[33mcommit 89aaa77b5f381971002a8a2ffbd554fb2fe1fc4b[m
Merge: 20aca08 f1d4018
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:04:45 2016 -0800

    Merge branch 'image_write_parallel' of https://github.com/karjonas/stb into working

[33mcommit 20aca08f864920ecd99d51e61ed5d40d0caed4f6[m
Merge: b9216dd 007c850
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:02:56 2016 -0800

    Merge branch 'master' of https://github.com/zerhacken/stb into working

[33mcommit b9216ddb3671b53abdaee1d9d4fe66d4472950cd[m
Merge: 472c4c8 b372a1f
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:02:30 2016 -0800

    Merge branch 'master' of https://github.com/serge-rgb/stb into working
    
    Conflicts:
            stb_image_write.h

[33mcommit 472c4c82a44378b64245b1fbeaa9849f2cd0c51b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 10:00:19 2016 -0800

    update version history

[33mcommit ac748cba9bd9751bd5b219d0eca4c73ca94b583d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 09:57:04 2016 -0800

    update contributor list, version history, version number

[33mcommit 79f29bafffdbf33cb566102b1635c144beba0f28[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 09:48:01 2016 -0800

    fix previous stb_vorbis check-in that didn't actually compile;
    make stb_vorbis_alloc* parameter in APIs be const

[33mcommit 82ca643ef3b1af0840f4069d691e2c2871fc127e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 09:47:22 2016 -0800

    change previous explicitly-sized realloc support to be new API and unbreak old API

[33mcommit 853fda613236b9cb20520d0dd2b224f0feda0a85[m
Merge: c8e5012 7e741ff
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 09:38:13 2016 -0800

    Merge branch 'alt_realloc' of https://github.com/romigrou/stb into working

[33mcommit c8e50127c553ee578d76797adfca2f7825d25016[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 09:37:34 2016 -0800

    contributor list

[33mcommit 32d5e7ca7ff427f37c68800d901765ca496706a9[m
Merge: 9cb29b6 87a0396
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:15:58 2016 -0800

    Merge branch '16bit-tga' of https://github.com/DanielGibson/stb into working

[33mcommit 9cb29b6b39c1c2cd52843da6fef922852ee020aa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:13:55 2016 -0800

    update and reorganize contributor list

[33mcommit 5746aa023a8eda585346148fd8cbb7280bb024ba[m
Merge: e30b75a 4337345
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:05:51 2016 -0800

    Merge branch 'stbi_hdr_info_overread' of https://github.com/baldurk/stb into working

[33mcommit e30b75af8bfe864e77664b3b1e8c22b211f406b1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:05:40 2016 -0800

    update contributor list

[33mcommit c7e24f4c4caa892fabe05af5c09f8410f8e5f4b2[m
Merge: 1964d53 9f1a587
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:03:22 2016 -0800

    Merge branch 'master' of https://github.com/svdijk/stb into working

[33mcommit 1964d53d70507f26a82286208afb5a54a2208392[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 08:01:42 2016 -0800

    update version number and version history with everything committed to date

[33mcommit 418d21f2e28cdda9044330827c844dbed89676ee[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:52:15 2016 -0800

    bump the version number and add version hisoty

[33mcommit 79641c7ad43c0aa3f39cc086ccf9577e9ad0c061[m
Merge: 31eff2d cd750ab
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:43:09 2016 -0800

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 3560e553e89f054a70d46ba447fbe9323600e4c9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:42:24 2016 -0800

    stb_vorbis version history and contributor info

[33mcommit e9e5dd94b831041cd8634d6d6cf0042b2ab7d1d1[m
Merge: 95e954c 35fcd08
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:35:10 2016 -0800

    Merge branch 'vorbis-pedantic' of https://github.com/rohit-n/stb into working

[33mcommit 95e954c822042edb24d49e836d8ad294edb849fc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:26:16 2016 -0800

    const correctness for pushdata API;
    minor tweak to get_samples_interleaved documentation

[33mcommit 0860860af60659d5803cbc5ecc6a932029b435c2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 16 07:19:27 2016 -0800

    avoid __forceinline in mingw since their definition for C is broken;
    dummy definitions for malloc et al (note you have to modify source to make this work though anyway);
    tweak credits change;

[33mcommit cd750ab2c352ab1f720f0963f2d172ac22fd1b30[m
Merge: 1ec8a8c f5e3afa
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jan 14 15:19:35 2016 -0800

    Merge pull request #216 from corporateshark/master
    
    Added LUrlParser

[33mcommit 7e741ffc1e78c2ec9dfe8725f8fa52ca8bc393cc[m
Author: Romain Bailly <rom175-github@yahoo.com>
Date:   Thu Jan 14 10:34:30 2016 +0100

    Added the old size as argument to the STBI_REALLOC() and STBIW_REALLOC() macros

[33mcommit 1ec8a8c4a44f3d1b0a2e9b06458a6172d5349d7c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 12 09:26:47 2016 -0800

    Update other_libs.md

[33mcommit 5b6d11e9e8b9ffdd4c3468bb003e8ec780142faf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jan 12 09:26:10 2016 -0800

    Update other_libs.md

[33mcommit fc8b6494661167788bd0fef36106f9a492d92704[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jan 3 13:38:34 2016 -0800

    Update other_libs.md

[33mcommit f5e3afa5c666c570ef9a27f862155c473f272704[m
Author: Sergey Kosarevsky <sk@linderdaum.com>
Date:   Sun Jan 3 02:23:19 2016 +0300

    Added LUrlParser

[33mcommit ac8adfdcb3710892809e3d9cbc6998a5ec52818e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Dec 16 08:22:58 2015 -0800

    Update other_libs.md

[33mcommit bb39bd44bbf2b028e05d87ff56db2944760515cf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Dec 16 03:14:03 2015 -0800

    Update other_libs.md

[33mcommit 9dc860b7ccf9164471b2892a7055dede1ad48279[m
Author: ocornut <omarcornut@gmail.com>
Date:   Fri Dec 11 22:55:42 2015 +0000

    stb_textedit: better support for keying while holding mouse drag button

[33mcommit 87a0396922d2b49ea46d519bd69378761cf9d941[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sun Dec 6 05:47:47 2015 +0100

    stb_image.h: 16 bit TGAs don't really have an alpha channel
    
    I claimed that if the most significant bit of a 16bit pixel is set,
    it should be opaque (as is suggested by some sources on the internet),
    but implemented the opposite.
    If implemented "correctly", lots of 16bit TGAs become invisible.. so I
    guess 16bit TGAs aren't really supposed to have an alpha-channel, or at
    least most 16bit TGAs (despite having set an "alpha-bit" in the "image
    descriptor byte") in the wild don't seem to work like that.
    
    So just assume 16bit non-greyscale TGAs are always STBI_rgb without
    an alpha channel.

[33mcommit d23504932293f7a7b8bb13eae033eff5a03a68df[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sun Dec 6 04:33:37 2015 +0100

    stb_image.h: Fix TGA colormap support
    
    * Calculate correct stb format (incl. proper 16bit support) also when
      using a colormap (palette)
    * Create colormap with tga_comp, to correctly support 16bit RGB
      (instead of using tga_palette_bits/8 and just copying the data)
    * For TGAs with colormap, the TGA bits per pixel field specifies the
      size of an index to the colormap - the "real" color depth
      of the image is saved in the color map specification's bits per pixel
      field. I think only 8 and 16bit indices make sense (16 should be
      supported, otherwise the colormap length could be u8 instead of u16),
      so I added support for both.
    * Helper functions stbi__tga_get_comp() to calculate stb pixelformat and
      stbi__tga_read_rgb16() to read one 16bit pixel and convert it to
      24/32bit RGB(A) - for less duplicate code

[33mcommit 57409c3d159af0bb72dac2411fa3183d39202674[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sun Dec 6 00:30:16 2015 +0100

    stb_image.h: Improve stbi__tga_info() and stbi__tga_test()
    
    * for paletted images, .._info()'s comp should be based on the palette's
      bits per pixel, not the images bits per pixel (which describes the
      size of an index into the palette and is also checked now)
    * make sure the color (map) type and the image type fields of the header
      are consistent (=> if TGA color type is 1 for paletted, the TGA image
      type must be 1 or 9)
    * .._test() does some more checks and uses stbi__get16le() instead of
      stbi__get16be() - TGA is little endian.
    * .._test() now always rewinds (sometimes it used to do only return 0;
      without rewinding)
    * remove "error check" at the beginning of stbi__tga_load(), because
      all that is already tested in stbi__tga_test()

[33mcommit 7453e1bfa417453db9b57091b71ad428ba0a6462[m
Author: Daniel Gibson <metalcaedes@gmail.com>
Date:   Sat Dec 5 23:23:12 2015 +0100

    stb_image.h: Support 15/16bit per pixel RGB(A) TGAs
    
    stbi__tga_* assumed that 16bit TGAs were Grayscale + Alpha.
    However, if the TGA imagetype is not one of the gray ones, it's 16Bit
    RGB data, with 5 Bits per channel. If the TGA image descriptor field
    has alpha bits (the 3 least significant ones) set, the pixel's most
    significant bit is for alpha: 1 for opaque and 0 for translucent.
    Furthermore people claim that TGAs can also pretend to have 15bpp,
    which is the same as 16bpp but definitely without alpha.
    
    So 15/16bpp TGAs are now decoded to STBI_rgb(_alpha).

[33mcommit a4ab8c08eb4bd74dc22d98e0b1bb70372121fa36[m
Author: blackpawn <jim@blackpawn.com>
Date:   Wed Dec 2 23:12:12 2015 -0600

    Corrected fix for stb_insertn
    
    On insert the memmove length wasn't incorrect but the addlen call was.

[33mcommit 28f1b0f5698fe4e05410250895ee7f75d0db4559[m
Author: blackpawn <jim@blackpawn.com>
Date:   Wed Dec 2 22:34:04 2015 -0600

    Fix for stb_arr_insert

[33mcommit cbfa0c44184748728a600fd69e14c5937497618c[m
Author: blackpawn <jim@blackpawn.com>
Date:   Wed Dec 2 01:16:29 2015 -0600

    Fix stb_arr_insertn and stb_arr_deleten memmove lengths
    
    They were moving memory beyond the array bounds.

[33mcommit 64fa9a3d95efdea727cef159fb6768c046d0a3ba[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 30 01:01:42 2015 -0800

    Update other_libs.md

[33mcommit 2161d1e12a411e74b6893a262f7cf9025cb0d737[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 30 01:01:28 2015 -0800

    Update other_libs.md

[33mcommit 657eda21550bda493439f153730e4a00334e31ec[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Nov 21 03:29:15 2015 -0800

    Update other_libs.md

[33mcommit 63849198b9ba4a6b464edb70527058a53865a302[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Nov 21 03:22:21 2015 -0800

    Update other_libs.md

[33mcommit 4337345c5ddd636bcdee65439e5a9f4451114e88[m
Author: baldurk <baldurk@baldurk.org>
Date:   Sat Nov 14 13:14:26 2015 +0100

    Prevent HDR info function from trashing stbi context by over-reading

[33mcommit 5809508de3329c992d4d8dea03a8be7e1a0d0f35[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 12 06:12:24 2015 -0800

    Update other_libs.md

[33mcommit 4e691f5917140f9dc6d01974a8195cd8b2edc823[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 12 06:12:06 2015 -0800

    Update other_libs.md

[33mcommit 831b2d2fa63ee50ceee2d7d59c2face439f17670[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Nov 10 13:41:53 2015 -0800

    Fix a merge gone wrong, add some more test cases.

[33mcommit c81f0c62bc127e8a7ce092ad51f6b61ec9891f41[m
Merge: a1ef3a1 cf6f69c
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Nov 10 11:29:16 2015 -0800

    Fix the calculation of the input image shift when using subpixel regions

[33mcommit a1ef3a1060a819aa48fd3fbf7547f0839fda4938[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Tue Nov 10 11:25:59 2015 -0800

    Fix the calculation of the input image shift when using subpixel regions

[33mcommit 2b57ea95da349555469e5fd75c5c35e49d6060db[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 19:16:25 2015 -0800

    fixed version of removed support for CODEBOOK_SHORTS

[33mcommit fe74a8c2232c76ee4e34328ea585846460218483[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 19:13:32 2015 -0800

    broken attempt at removign STB_VORBIS_CODEBOOK_FLOAT option

[33mcommit cf6f69cdc9ea4d0cc7f1fb86e724a31b1e61926b[m
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Sun Nov 8 16:40:32 2015 -0800

    Fix the calculation of the input image shift when using subpixel regions. Includes some more tests which had incorrect results before and now work fine.

[33mcommit bc2219e1b3cfcaf511242f009186d13f78c8885d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 16:22:07 2015 -0800

    fix multiple crashes on invalid files

[33mcommit bdac1d2ab43823725fcd701e6310fbc0efd942de[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 16:01:40 2015 -0800

    fix two crashes in invalid files

[33mcommit 70b33e99f0487d7d8665b483aff3cf2e70a4148f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 14:04:56 2015 -0800

    fix crash from invalid file

[33mcommit ea88e59b5dd48bc2179dd7db537923f9edbba707[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 13:45:33 2015 -0800

    fix invalid handling of truncated end-of-file indicator

[33mcommit 69a318bdb3bbaf7327a87bd18ec7d9b223091fe6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 13:20:55 2015 -0800

    fix two invalid-file crashes found by fuzz testing

[33mcommit 2073403a5f54eda44090bc62d0907e07ba73bde5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 13:09:30 2015 -0800

    fix two setup crashes found by fuzz testing

[33mcommit 297ff6285909c510c27752785083d497ee1dbf7c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 13:09:16 2015 -0800

    change bmp info to use common header parser

[33mcommit 876aea3dbe0e56984f7336e55698c06c9346c8e8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 01:22:30 2015 -0800

    refactor bmp header parser for sharing with stbi_info

[33mcommit 16fc63404d5b9256564feb54bcb44f255a6efdda[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 01:03:37 2015 -0800

    suppress bogus static analysis warning

[33mcommit 6382e49063dd302785bf1d0055fdf15bc65f6359[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 00:54:49 2015 -0800

    don't crash if out of memory allocating a new active edge (assert in debug)

[33mcommit 0615df6c9b1eadfcbd0e65a6ca1f4ae3947919ee[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 00:45:17 2015 -0800

    allows comments in pgm/ppm headers

[33mcommit a0f850421d8f2029337a989525d2721b1cb050e4[m
Merge: 2329276 31eff2d
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 00:41:01 2015 -0800

    Merge branch 'master' into working

[33mcommit 31eff2dcaf568aec77112d27e772e2f1223de2ae[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Nov 8 00:37:52 2015 -0800

    fix bug in integer parsing

[33mcommit 9f1a587d22e8a11f7ce2b00dcc9699520343daf3[m
Author: svdijk <svdijk@users.sourceforge.net>
Date:   Thu Nov 5 23:34:44 2015 +0100

    stb_image.h: Fix/add some comments.

[33mcommit 8603c6e8095e1a10a2855c6029ba4bf65d77e827[m
Author: svdijk <svdijk@users.sourceforge.net>
Date:   Thu Nov 5 23:32:40 2015 +0100

    stb_image.h: Only define stbi__l2h_{gamme,scale} when needed.
    
    This fixes a (well, actually the only) compiler warning.

[33mcommit 3f73dfd7ce055de51fae53c21b7887cc90d86f4d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 06:49:02 2015 -0800

    Update other_libs.md

[33mcommit fa9a6e4e0a99bda20688d4df9d1d1588a790e35e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 06:48:42 2015 -0800

    Update other_libs.md

[33mcommit d4cea6123a0fa8638acef6ea28d99336fed9d174[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 05:13:00 2015 -0800

    Update other_libs.md

[33mcommit 20eea21e0114a79bfa179f0cf7db5242ca31f220[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 05:11:34 2015 -0800

    Update other_libs.md

[33mcommit a44e950d9a0626d16da0622cc4bb63fd58ccef6d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 04:58:42 2015 -0800

    Update other_libs.md

[33mcommit b6602ab0850f378154da3395c621862acbed16be[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 04:51:38 2015 -0800

    Update other_libs.md

[33mcommit 450db24449ace1f50f29642b4955acecbe418744[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 04:47:49 2015 -0800

    Update other_libs.md

[33mcommit 76b8ff0051194f554413a791dde0be7974ef12ee[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Nov 5 04:47:36 2015 -0800

    Update other_libs.md

[33mcommit d113bea69a84b1440227db923a4a5fc7c1456e1b[m
Author: Stephen Olsen <steve.olsen@gmail.com>
Date:   Wed Nov 4 14:02:33 2015 -0600

    typo in shader
    
    Should be mat4 or mat4x4, not mat44

[33mcommit 702c5bfee860946b1c9c513a7259a74e0e61f999[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Nov 3 15:10:58 2015 -0800

    Update other_libs.md

[33mcommit 8d9302ab05294b5fecc4bd445651521b8cc7fc38[m
Author: Michael Sartain <mikesart@gmail.com>
Date:   Sun Nov 1 17:47:11 2015 -0800

    readdir_raw buffer overrun fixes.
    - Add stb_vsnprintf, stb_snprintf functions.
    - stb snprintf routines should return -1 on buffer truncation on all platforms.
    - Add stb_strscpy string copy function which should behave the same as Linux kernel strscpy.
    - Bump readdir_raw buffer sizes up to 4k, add checks for path truncations.
    - Use d_type to check for directory instead of opendir/closedir. This
      should be faster and fix recursive symlnk death.

[33mcommit ba406835155888c048da2c41eeb909fe204123cf[m
Author: Michael Sartain <mikesart@gmail.com>
Date:   Fri Oct 30 19:10:03 2015 -0700

    readdir_raw was skipping all dirnames starting with dots. Only skip . and ..

[33mcommit 06ae60645efc713362fef70ef6d9c69516ddd425[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Oct 31 11:17:02 2015 -0700

    Update other_libs.md

[33mcommit 8cea0090b2fcb193b32d9c33a5ee0155f23dfa64[m
Author: Filip Wasil <filip.wasil@gmail.com>
Date:   Thu Oct 29 16:09:21 2015 +0100

    Removie implicit cast to float
    
    When compiling with more restrictive compiler options
    such casting from double to float will cause a warning.
    
    Ex. GCC -Wdouble-promotion
    
    Signed-off-by: Filip Wasil <filip.wasil@gmail.com>

[33mcommit b95858a2f772c83421f02ef2e3352d737f78178e[m
Author: Jonas Karlsson <jonaskarlsson@fripost.org>
Date:   Tue Oct 20 23:22:27 2015 +0200

    Add bitmask to unsigned char casts to fix MSVC runtime checks

[33mcommit 22dd50f25653944863898601ee66bdef121fd51a[m
Author: Jonas Karlsson <jonaskarlsson@fripost.org>
Date:   Tue Oct 20 22:03:50 2015 +0200

    Fix documentation error

[33mcommit f1d401845ff937207772b10917713abfac25e911[m
Author: Jonas Karlsson <jonaskarlsson@fripost.org>
Date:   Sat Oct 17 17:33:00 2015 +0200

    Fix race condition in static crc_table
    
    If calling stbi_write_png concurrently the static array crc_table would be shared between threads causing data-races.

[33mcommit 385927fb4b8a06d72402fb3971acea1d67142ec4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Oct 15 17:59:40 2015 -0700

    Update other_libs.md

[33mcommit 35fcd0817fe192941a8840365bb783314b435667[m
Author: Rohit Nirmal <rohitnirmal9@gmail.com>
Date:   Fri Oct 9 20:46:59 2015 -0500

    stb_vorbis.c: Silence -pedantic warning.

[33mcommit c4082cfb890946a0c37df6b4c97f57b52042969e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Oct 9 15:31:50 2015 -0700

    Update other_libs.md

[33mcommit ff085b88f49935a43aec1828f7e64e371b7fa980[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Oct 9 02:11:28 2015 -0700

    Update other_libs.md

[33mcommit 6a9cdd1c83630f4f27af8e0c6b8b6ba427354975[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Oct 9 02:03:44 2015 -0700

    other_libs: add a few libraries

[33mcommit 3e404042c5b1f02bd64d3430a5b79434aa95584a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Oct 7 21:53:40 2015 -0700

    other_libs: added TweetNaCl

[33mcommit 0b79b3bfe1cf790ef783e1b9df4a8a9dd58fb91e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Oct 5 09:43:46 2015 -0700

    Update other_libs.md

[33mcommit cc3bb7c45828e6db4d441e68f6af02f1d60d6109[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Oct 5 09:43:27 2015 -0700

    Update other_libs.md

[33mcommit bdcc1535d6b5e2c8386f5126d267ab2bfeb9c8cb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 11:04:06 2015 -0700

    Update other_libs.md

[33mcommit dc92c6c4c455e6c32222309e52978a55071c9c1c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:30:16 2015 -0700

    Update other_libs.md

[33mcommit bbdb4f65efad46b47be8ddfd8f7cf198beb46d0c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:23:56 2015 -0700

    Update other_libs.md

[33mcommit cd9c6d7b436f643ac612bd3bc18025226974fc47[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:21:39 2015 -0700

    Update other_libs.md

[33mcommit 8d0ae2d39ffa973230bc33ee4c35d221f046e42b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:16:33 2015 -0700

    move other_libs list to its own file

[33mcommit 2bd2e571a22db8a3c48f5b4314d0d95f18a1f3cb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:16:13 2015 -0700

    Update other_libs.md

[33mcommit f6d172d92be7db105184419f80ec25be7b14616a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:15:32 2015 -0700

    Update other_libs.md

[33mcommit 4b587a409ab26b0e471c021863e5dd82ad101b97[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:14:48 2015 -0700

    Update other_libs.md

[33mcommit 847fb2c230859aa91eae47bba3b6fbb86fe91f84[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:13:09 2015 -0700

    put other_libs list in its own file

[33mcommit 6464d059ab09e012a4e7f00fcbbbb91212d08d9c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:11:09 2015 -0700

    fix typo

[33mcommit 37a493ae21b7dec3c339ac0a4d73c1d0db7158c7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:11:02 2015 -0700

    fix typo

[33mcommit b1160eb7e9df9e639551e6004affdd9a84b54a0e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 27 08:09:25 2015 -0700

    update other_libs

[33mcommit 60e3ecac85065955d5cd1fc1038e762fe78375e6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 26 12:14:37 2015 -0700

    added ImGui to other_libs

[33mcommit 3eb363c193c9ebe88e3c554caa1d3004ae668fc9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 26 12:03:24 2015 -0700

    italicize more recent others' libs

[33mcommit 616633b557a792c1059883e6041e83e63b7898d0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 26 12:03:09 2015 -0700

    italicize most recent others' libs

[33mcommit 6998a8e064eeac13bbce69bda25c2fea8a7ccfbf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 26 11:51:23 2015 -0700

    add gb_string.h

[33mcommit 007c850b485823cd66439133f9a79ad295464198[m
Author: Rasmus Christian Pedersen <zerhacken@yahoo.com>
Date:   Fri Sep 25 19:46:27 2015 +0200

    nobug: removed unused variable 'k'

[33mcommit 232927699c692be310af8252e64c43a73fcd0c17[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 23 05:03:26 2015 -0700

    Vita warning fix

[33mcommit 34d6c2ca873b51428d12804fb0305ce4cf0e3583[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 23 05:01:16 2015 -0700

    update tinyexr's list position

[33mcommit b372a1f86c7cf11a9b0023c06a51b90037781c70[m
Author: Sergio Gonzalez <bigmonachus@gmail.com>
Date:   Mon Sep 21 12:18:18 2015 -0500

    Avoid macro redefinition in Win32

[33mcommit 412e1ecc1620fd842b0d3ade2238c8918f5fb373[m
Author: Tim Sjöstrand <tim.sjostrand@gmail.com>
Date:   Tue Sep 15 19:17:42 2015 +0200

    compile fix for MinGW

[33mcommit 5378a965369b5870dff58b11e187688f83623a8c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 07:07:20 2015 -0700

    clarify that olick's GIF also does animated

[33mcommit ac7daffc276b6845f203f2adecf48a1e01cba909[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 05:58:09 2015 -0700

    update readme

[33mcommit 93b2b829963f637e9c90218da5e501d71c9a255b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 05:57:42 2015 -0700

    get rid of unused return value from write callback

[33mcommit b4477803cb9a2038fb9f4fc65b50d553395544c7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 05:48:24 2015 -0700

    fix public function names;
    fix internal names to be namspaced properly;

[33mcommit 78fe0bfc2495e4fad2ae4a1fe4f1792f662ef09a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 05:40:12 2015 -0700

    handle fopen() failing

[33mcommit ad63a8d3166b2686cc7d4e588b676ca1f478f0b9[m
Merge: 955bd17 529d816
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 05:38:07 2015 -0700

    Merge branch 'master' of https://github.com/ejulien/stb into working
    
    Conflicts:
            stb_image_write.h

[33mcommit 955bd174a2796dd41461b57a52704c470c21acb2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 04:53:31 2015 -0700

    update list

[33mcommit c2978ae79f73030b27475e57538a1d9af25d70cc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 02:36:57 2015 -0700

    move anchor to *beginning* of question so links look better

[33mcommit 99c7e64b6274b6a223f4e25846a9bb8d9a836206[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 02:35:47 2015 -0700

    rebuild README

[33mcommit 996f0b0a6b1067edd16e7afe7b9c6fa69e4c348b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 02:35:31 2015 -0700

    fix spelling of SQLite

[33mcommit 5c9c75fcbdab2d0a98666bd178742757546e7055[m
Merge: a2291e3 1fa899a
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 02:33:07 2015 -0700

    Merge branch 'master' of https://github.com/nothings/stb
    
    Conflicts:
            README.md

[33mcommit a2291e3e5dc81c41b4a79991e96663f8e8bd335d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 14 02:32:03 2015 -0700

    update single-file-libs list

[33mcommit 1fa899a101ce13a9b13256732f039dc432e8f111[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 18:36:51 2015 -0700

    Update README.md

[33mcommit be1c75efa91c434d39d1d0321548a407dab270f9[m
Merge: 2722cfc 054d340
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 18:24:53 2015 -0700

    Merge pull request #176 from triplefox/patch-2
    
    fix spelling of "Hofmann" -- doh

[33mcommit 054d340c8c6e459b5e42d12334799b59a6921864[m
Author: James Hofmann <jhofmann@321f.net>
Date:   Sun Sep 13 18:20:06 2015 -0700

    fix spelling of "Hofmann"
    
    Interesting factoid: my last name has four valid spellings. In Germany, the one I use is apparently the most common, while the other spellings are typical in the United States.

[33mcommit 2722cfc3a0e0c11d3a4f5a98f242f39f1af2ed8c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 17:01:26 2015 -0700

    fix last

[33mcommit b30a97930e22d808e6efd0fce8b385b73e176d5b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 17:00:20 2015 -0700

    include URL with anchor so other people can find it

[33mcommit 288ef363581f5ca2f1af99d8cb196b0a9aacd544[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 16:56:07 2015 -0700

    anchor for external links to list

[33mcommit 43789d11d9c0ab310e32ad5c81907c6373f700b3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 16:54:35 2015 -0700

    add tigr to single-file libs FAQ

[33mcommit a0d064edaed4b2bc7af0fcbfaa67c7ed105ef7c7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 16:13:57 2015 -0700

    update readme

[33mcommit 8b7b845c4e8fa8955760e5f51661f9d9b24809bc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 16:13:16 2015 -0700

    bump version number

[33mcommit b74da797af656330628d359876959cbb5aa12b26[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 16:07:49 2015 -0700

    properly fix stb_rect_pack;
    tweak formatting of FAQ list

[33mcommit e847954d2742dcc243ef6aeb1fd02f1a6f38567a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 14:53:34 2015 -0700

    update readme

[33mcommit 55eefc5739525a7a843faf9cf714060f9d29e530[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 14:51:49 2015 -0700

    add list of single-file libs

[33mcommit 4de75eb0cc129bbfd7fa29cbc7381476305523d9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 13:35:51 2015 -0700

    stb_textedit: better support for baseline at bottom
    stb_textedit: end-of-line handling places cursor before newline
    stb_truetype: avoid compiler warning due to local vars hiding local vars
    readme: add list of one-file libs

[33mcommit ff116a4fe85e68689fe492890f57efc7bf5622d1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 11:42:54 2015 -0700

    allow font ranges with first_char = 0;
    fix divide by 0 for exactly-vertical edges;
    fix possible divide by 0 for exactly-horizontal edges
    add documentation for stbtt_Rasterize;

[33mcommit 54b187972533fbe2bb6b2d350358fce4ef19add1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 11:23:33 2015 -0700

    document stbtt_Rasterize

[33mcommit 83d36fd28a2f25bbcbf887832d896203957f8b92[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 11:17:13 2015 -0700

    fix bug in handling rectangle with width or height of 0

[33mcommit 6b8938124e79a8dce343e77ee905ab5adc07a68b[m
Merge: d5b8af1 3657418
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 11:09:23 2015 -0700

    Merge branch 'fix-vs2015-warnings' of https://github.com/Reedbeta/stb into working

[33mcommit d5b8af12cbeeb9d7f4734ebfef8af93e0de74451[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 11:08:40 2015 -0700

    fix missing "defined" in #if defined(STBI_NO_foo);
    fix incorrect initialization of alpha channel for RGB PSD

[33mcommit 36574182c0e39469315583d151c3ad2b42c7ab92[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Sun Sep 13 11:00:46 2015 -0700

    Fix new VS2015 warnings in stb_image 2.07
    - conversion from int to stbi_uc
    - unused parameter

[33mcommit 023ff3ffd2d62ed3e4a654001c7a6b0d081dddf2[m
Merge: 5bcce36 be8284d
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 07:01:02 2015 -0700

    Merge pull request #140 from ocornut/stb-wingraph-static
    
    stb_wingraph.h: missing lib pragmas for completeness

[33mcommit 5bcce366386ff1e8faf0852083cc6c5147a93bd5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:58:45 2015 -0700

    rle tweaks, credits

[33mcommit 40ace6b0ef0214efeb72ea35d5b224f893dce2fc[m
Merge: a84daa6 80a0e90
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:51:14 2015 -0700

    Merge branch 'master' of https://github.com/fahickman/stb into working

[33mcommit a84daa614e119d27a4aebded8f451cd492f4f255[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:46:43 2015 -0700

    a few more stb_image_write fixes

[33mcommit 9bf98d619f0962d00ae3f47811b0764a2603247e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:41:30 2015 -0700

    update readme

[33mcommit 2a1716cc8ff8b7f7a76eea162281e14f01c1b50c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:41:16 2015 -0700

    credits

[33mcommit 23b21a7c1f4115a0cc76b255c4fbf9380ab05524[m
Merge: 5f54e04 d1d5f4c
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:39:20 2015 -0700

    Merge branch 'master' of https://github.com/guillaumechereau/stb into working

[33mcommit 5f54e044ed2a7717a1294d52f83fd2f010148a6b[m
Merge: 264bc57 d993ce7
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:37:51 2015 -0700

    Merge branch 'master' into working

[33mcommit d993ce7a5b197875a39af98fe3dff55892c2441d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:37:36 2015 -0700

    update readme

[33mcommit 264bc5725fa3f0a29829918aef979ebfc86dc2c4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:37:24 2015 -0700

    credits

[33mcommit 92e9519db399bcf59cbe67d9d188fced0e1d90ba[m
Merge: 7b24469 f24f92b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:35:11 2015 -0700

    Merge branch 'master' of https://github.com/Sergobot/stb into working

[33mcommit 7b24469bf14510c3d8de32ac5f0cf0634d4d81a0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:33:49 2015 -0700

    update version / credits

[33mcommit 5863a4efe1a6022403d9f65f1ef4204082853237[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:28:46 2015 -0700

    delete stb_vorbis.h which leaked in from somebody's pull request

[33mcommit 39522da245d1faa56a89e5c41a0a1caa476b54cd[m
Merge: 33c9010 f026837
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:18:47 2015 -0700

    Merge branch 'working'

[33mcommit f0268375da05b26fdba1cac61650997a0aaf5b1a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:16:52 2015 -0700

    credit

[33mcommit ef21612364bb67476241cb66d367d442b98afc62[m
Merge: b0852b7 09e1972
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:11:09 2015 -0700

    Merge branch 'fix-clang-warnings' of https://github.com/vincentisambart/stb into working

[33mcommit b0852b766a5b5be1d2ed22fa7fd48ecea589f76c[m
Merge: 97dfb12 0c0a619
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:10:16 2015 -0700

    Merge branch 'master' of https://github.com/rwhitworth/stb into working
    
    Conflicts:
            stb.h

[33mcommit 97dfb12f71e1308c669c55d8f5ffb1eb5ece3516[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:06:37 2015 -0700

    credits

[33mcommit 9438a74f83cb403e546caa3a39fe798ba7bd7149[m
Merge: 5583b62 65ebe75
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:05:38 2015 -0700

    Merge branch 'master' of https://github.com/Mojofreem/stb into working

[33mcommit 5583b62a70ca7d6740e152dddd343add7d8ec2ca[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:05:24 2015 -0700

    credits

[33mcommit d422a247e0817b6404a9ecd346893761bf33c28d[m
Merge: 2adf6d2 693772e
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:00:32 2015 -0700

    Merge branch 'master' of https://github.com/blackpawn/stb into working

[33mcommit 2adf6d29aa44bd3bc9d9116bd171ab76ebee4c40[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 06:00:06 2015 -0700

    credits

[33mcommit a96eb0479548c729d097627bfa4fcb819545a65c[m
Merge: c6f33a1 8702dce
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:58:57 2015 -0700

    Merge branch 'master' of https://github.com/r-lyeh/stb into working
    
    Conflicts:
            stb.h

[33mcommit c6f33a1ff093aa9ffb4503975c9a7ccf36947ff9[m
Merge: 24602db 51415de
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:57:10 2015 -0700

    Merge branch '64bit' of https://github.com/Mischanix/stb into working

[33mcommit 24602db4a540150dea93a6e6fdeeffa2ce8629bb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:53:56 2015 -0700

    credits for previous patch

[33mcommit 8ca1cdfe4c676bc865dd19ba1e6851b031ee3d50[m
Merge: 90dc93a b3653cc
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:52:59 2015 -0700

    Merge branch 'fix-double-free' of https://github.com/philippwiesemann/stb into working

[33mcommit 33c9010223f34ad5f4f033d8bf0baf0cdccec60b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:51:16 2015 -0700

    update version & version history

[33mcommit 27d5d61f0875dc7c47ff0f5b6a203c7b063adf45[m
Merge: 90dc93a 5305ffb
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:47:02 2015 -0700

    Merge branch 'master' of https://github.com/jsheard/stb

[33mcommit 90dc93a1ccbf63df53d3136c6e1b6225840814cf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:41:21 2015 -0700

    fix bug where we couldn't rewind a file that reached EOF, which can happen with < 92-byte PIC,PNM,HDR,TGA

[33mcommit 28a29dd0f1ffd4a64719851cb37f1665b2f286d0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:15:09 2015 -0700

    credit for michaelangel007 patch

[33mcommit ddd05479e9f6996905e7293f6f0e17bae934c32a[m
Merge: 0eb5da5 c11532b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:13:57 2015 -0700

    Merge branch 'master' of https://github.com/Michaelangel007/stb into working

[33mcommit 0eb5da55a71a6f4cac56882764ebcdf0b2f6089d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:12:53 2015 -0700

    er, fix typo in the fix-rmitton checkin

[33mcommit 082289b52813f71803a43a21c4917a1a2260bcb6[m
Merge: 5607c25 fcfa17b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:12:35 2015 -0700

    Merge branch 'master' of https://github.com/rmitton/stb into working

[33mcommit 5607c25cf49f65fa43bd204b29ee83fb30e679dc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 05:11:51 2015 -0700

    tweak rmitton 16-bit psd patch;
    adjust credits

[33mcommit 69d6fd573cead77340233bdabbc4d5a00295d96a[m
Merge: 1ea670e 6645ea5
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:58:48 2015 -0700

    Merge branch 'psd16' of https://github.com/rmitton/stb into working

[33mcommit 1ea670e0a5a95b2197109e43320534012cdf85cf[m
Merge: 52d4007 23dfb8c
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:49:04 2015 -0700

    Merge branch 'urraka-gif-patch' of https://github.com/urraka/stb into working

[33mcommit 52d400741c93a3638b3fbc133fad4eaa5796d7fc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:46:50 2015 -0700

    detect all 0-alpha bmp and replace with all-255;
    fix bug in reedbeta patch

[33mcommit fee80f3d83c5600a6c2b58d4940a46ac57cd22fa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:27:24 2015 -0700

    tweaks to patch from reedbeta

[33mcommit 492e6e303d1729c55ace7fc4516fe3265eae28e7[m
Merge: 9c3e9d6 26c9826
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:20:29 2015 -0700

    Merge branch 'fix-vs2015-warnings' of https://github.com/Reedbeta/stb into working

[33mcommit 9c3e9d63ea700cec6b88df3ea32404050d0d7d4e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:20:00 2015 -0700

    add to contributor list

[33mcommit 6fe9dae224d201f3f38390a0dd39a6b6b50445fa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:19:17 2015 -0700

    bump stb_voxel_render version number

[33mcommit 6a45a88e0ff1c33deb95a9108bf118c878705094[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 13 04:14:02 2015 -0700

    update "DMC doesn't accept struct initializer" patch to be VC6 compliant

[33mcommit b0d162d8294d222ff64dd7bcaf49c5a6f548d953[m
Author: James Hofmann <jhofmann@321f.net>
Date:   Sat Sep 12 05:45:39 2015 -0700

    DMC doesn't accept struct initializer syntax
    
    It expects constants. The long way compiles (but I haven't actually called this function yet)

[33mcommit 26c98260b66b36c5256f9e51aabaad49220bd5d0[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu Sep 10 01:20:35 2015 -0700

    Fix warnings about "conversion to a greater size" that appear in VS2015 in x64 with /W4.
    
    The warning concerns the return value of stbi_err, which is an int, being converted to a pointer. In VS2015 it seems casting directly from a 32-bit int to a 64-bit pointer triggers this warning. Worked around by first converting to a 64-bit int (here size_t) and then to a pointer.

[33mcommit 6d613ed8ce46f1f142a9ecbc341423655140f2ee[m
Author: Nathan Reed <nathaniel.reed@gmail.com>
Date:   Thu Sep 10 01:13:54 2015 -0700

    Fix variable-shadowing warnings that appear in VS2015 on /W4

[33mcommit 7ac0f9c9b0cc72549f85716b1c3dcd178b4f668d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 22:55:01 2015 -0700

    fix typo in accidentally-checked-in stb_image.h

[33mcommit 4743a1a6e60c61bf25e3483688f0205118134972[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 11:20:24 2015 -0700

    update stb_vorbis

[33mcommit 60939ec6536ecf85ec30e304e31d85c33dbf8787[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 11:18:40 2015 -0700

    fix some more signed shifts

[33mcommit a3d62dfec1153b56f657e5d8f7e43b13f12f0ab2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 11:16:19 2015 -0700

    fix a few crash bugs with invalid stb_vorbis files (reported by Philip Bennefall, found using a fuzz tester)

[33mcommit 76706563229f13370be2265d31fa853e75bdbc2e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 10:24:01 2015 -0700

    fix some signed shifts that should have been unsigned for C spec reasons

[33mcommit 0e24ec5feb2e1ac70bb35c25faa1fa4b8b7cda3f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 3 07:11:02 2015 -0700

    fix some cases that didn't return outofmem error properly and would crash instead

[33mcommit a009673856f0de13d5af47654d28e03e07f8f128[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 31 12:49:03 2015 -0700

    update stb_vorbis version

[33mcommit c15190373c9a40ef7a7e6cad4f8324ec14bf8bf4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 30 19:31:36 2015 -0700

    add missing changes to project file

[33mcommit ebb54fd7a33f900b6cb4ae0c951e4b2727ae93aa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 30 19:29:35 2015 -0700

    seeking in stb_vorbis (Dougall Johnson)
    test program for seeking (stb)

[33mcommit f24f92bcc764713bc265867e741adcadb94f7000[m
Author: Sergey Popov <sergobot@vivaldi.net>
Date:   Wed Aug 19 14:36:09 2015 +0300

    Fix -Wextra warning in stb_truetype.h

[33mcommit 09e1972fed4e4b63302bd9bd12baa2c6ccf3f67c[m
Author: Vincent Isambart <vincent.isambart@gmail.com>
Date:   Sat Aug 8 10:45:26 2015 +0900

    fix clang warnings

[33mcommit 0c0a619ca489d121e83bd08b406492c5de67b191[m
Author: rwhitworth <me@ryanwhitworth.com>
Date:   Wed Aug 5 22:27:53 2015 -0400

    Updated to compile with Visual Studio 2015

[33mcommit 23dfb8c06b31cdf746561b727e3f2db43b57eb13[m
Author: urraka <perroazul64@gmail.com>
Date:   Mon Aug 3 22:59:16 2015 -0300

    GIF loading improvements.
    
    - Fixed possible memory leak.
    - Fix for transparent backgrounds.
    - Adapted internal function to allow proper animation loading.

[33mcommit c9859afcf9dde9edd85e05dd1feb27aaaa92fb03[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 23:53:49 2015 -0700

    reverse some of the public-domain-license changes that I didn't
    actually want

[33mcommit 594502e5fabe1081f9df6e33ece157104c80145f[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:59:39 2015 -0400

    Added public domain license text

[33mcommit 85d0adda25cc0133879144b066148a38575e7206[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:59:03 2015 -0400

    Added public domain license text

[33mcommit f844b2dbd28ac47537b14b3b55396b1c019df346[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:57:53 2015 -0400

    Added public domain license text

[33mcommit 4727cdd8c018a3f4b107f46292653142e7ae027c[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:56:45 2015 -0400

    Added public domain license text

[33mcommit 76edb4ec4eae1999a9dde4d9d92bc664a9570c97[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:56:04 2015 -0400

    Added public domain license text

[33mcommit 7effe64e456f8d7eb21881fa1568e9174d04832d[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:55:35 2015 -0400

    Added public domain license text

[33mcommit 35e2f7e7399104696c52189b59b2c7bf975fa622[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:54:57 2015 -0400

    Added public domain license text

[33mcommit 5a7d524fd8aa342a4bd65753ba13de2fa21e40e6[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:54:27 2015 -0400

    Added public domain license text

[33mcommit 45b27d8a9ccd0393ef1be39dbd98e993a8eef313[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:54:05 2015 -0400

    Added public domain license text

[33mcommit 1d48782e1d441fb7f4c7b960b7198dd1d7adc4a4[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:53:00 2015 -0400

    Added public domain license text

[33mcommit f0e456b809660f487b9f053ff5c0835800df6068[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:52:12 2015 -0400

    Added public domain license text

[33mcommit 6695bc4e180a4aac7721a54f1a51d06f53f2679e[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:50:51 2015 -0400

    Added public domain license text

[33mcommit fa464b33acda9d81b44b0b2c1cc470209b520f4d[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:49:15 2015 -0400

    Added public domain license text

[33mcommit 55ff60818ed701946e6b3897ffa29e3dba746ec3[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:48:37 2015 -0400

    Added public domain license text

[33mcommit 242b1fe37a23b446913a16c829a5793cb5456b9c[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:48:08 2015 -0400

    Added public domain license text

[33mcommit 4ab69f3b2c294b8d1117a71cca0e1c57ac368c3b[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:46:52 2015 -0400

    Added public domain license text

[33mcommit 9e9ce0ab918b38f609472ef98fa11a3955c29b92[m
Author: Ryan Whitworth <me@ryanwhitworth.com>
Date:   Sat Aug 1 14:46:04 2015 -0400

    Added public domain license text

[33mcommit 59c353962ace3a47bbd782a0cbb00f122c23d127[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:18:27 2015 -0700

    update readme version numbers

[33mcommit c1cb414bc6dd8e009c2d2e23665e742cfe017b4f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:17:38 2015 -0700

    stb_voxel_render.h version 0.82

[33mcommit ad57cd038b0a70e38944039ac89d37b2c8652597[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:16:19 2015 -0700

    fix assert() to be STBTT_assert()

[33mcommit 4ea7744980e3a181ff3a8bd6a9ee7f12bd55de05[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:15:55 2015 -0700

    fix incorrect tex_overlay2 handling

[33mcommit 2afb8155090711652500cac7388e5c66edb431e9[m
Merge: cb52812 9f23eb3
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:08:21 2015 -0700

    Merge branch 'add_up_down_checks_to_geometry' of https://github.com/friesencr/stb

[33mcommit cb528122e5b3e8b746dc4bcb28f2baf9d0009702[m
Merge: c6ee732 3159971
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:05:43 2015 -0700

    Merge branch 'master' of https://github.com/cjxgm/stb into working

[33mcommit c6ee732c791eb89ed59f8686631e28403585bf63[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:04:54 2015 -0700

    allow finer-grained PackFontRanges with Gather & Render;
    allow discontinuous codepoints in PackFontRanges;
    fix bug in GetFontOffsetForIndex (non-0 index never worked?);
    tweak public domain license

[33mcommit e6378348651899159bb4a3e7b04d26f334614c9c[m
Merge: a200fab 5284588
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:03:19 2015 -0700

    Merge branch 'master' of https://github.com/ocornut/stb into working

[33mcommit a200fab163d92fd55d1b434eef2e8703c2247805[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:02:21 2015 -0700

    add some minor comments

[33mcommit d821fd83f323559af61bfb515541346a732d3454[m
Merge: 1384715 93fb372
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 1 04:02:00 2015 -0700

    Merge branch 'master' into working
    
    Conflicts:
            stb_voxel_render.h

[33mcommit 5305ffbe49b3b993f33b6251b07a116ceafeddac[m
Author: Joshua Sheard <mail@jsheard.com>
Date:   Wed Jul 29 17:00:44 2015 +0000

    Include math.h for ceil()

[33mcommit 6645ea5915833f6a89f51c3d95fcb8f50948c7fa[m
Author: rmitton <richard@codersnotes.com>
Date:   Fri Jul 24 12:00:09 2015 -0700

    Fixed stupid endianness bug.
    
    Incorrect endianness hilariously doesn't manifest _if_ the original
    image was upconverted from 8-bit to 16-bit.

[33mcommit 3159971d851c9aab7cae0c766e352d26964794e1[m
Author: Giumo X. Clanjor (哆啦比猫/兰威举) <cjxgm@126.com>
Date:   Mon Jul 20 23:18:47 2015 +0800

    stb_truetype: fix wrong result returned by stbtt_GetFontOffsetForIndex
    
    fixed the typo in stbtt_GetFontOffsetForIndex, where the field size should be 4 instead of 14.

[33mcommit 52845885c47982bda1ff2888e7e171e6dc389d7b[m
Merge: 34ed8ff 93fb372
Author: ocornut <omarcornut@gmail.com>
Date:   Wed Jul 15 12:08:29 2015 -0600

    Merge remote-tracking branch 'upstream/master'

[33mcommit 34ed8ff096bf93f7e4829793df80943684198342[m
Merge: 1b157be b53c08a
Author: ocornut <omarcornut@gmail.com>
Date:   Wed Jul 15 12:01:27 2015 -0600

    Merge branch 'nothings/master'

[33mcommit 93fb3720284ad368bb3ee97faed093b507cc2450[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 14 18:23:46 2015 -0700

    update stb_truetype version

[33mcommit 20b04f4aa90836d087396e6e5b1540935df8b47f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 14 18:23:12 2015 -0700

    stb_truetype version 1.06
    
    - switch from qsort() to built-in quicksort (about 2x as fast a sort, ~10% faster overall)
    - use pool allocator for active-edge allocations (~10% faster overall)
    - use new rasterizer (about 30% faster, ~10% faster overall)

[33mcommit 608cbec1f59a72fcd2b6862a98daaabe9c001f28[m
Author: rmitton <richard@codersnotes.com>
Date:   Tue Jul 7 15:47:37 2015 -0700

    Fixed overflow for high values.
    
    0xffff would accidentally round to 0x10000.

[33mcommit a371b204f57e49d3799630b7f2074eb99eedb5ef[m
Author: rmitton <richard@codersnotes.com>
Date:   Tue Jul 7 15:15:38 2015 -0700

    Added support for 16-bit PSD loading.
    
    This extends the current PSD loader to add support for 16-bit images, by
    quantizing them down to 8-bit upon load.

[33mcommit 9f23eb30be8c333ad8d6f4224ee9ab1a26afe6be[m
Author: Chris Friesen <friesencr@gmail.com>
Date:   Mon Jul 6 21:37:05 2015 -0500

    Adds up and down checks to voxel render input.geometry

[33mcommit fcfa17b847061d379893d083ef02ea743bb62c6d[m
Author: rmitton <richard@codersnotes.com>
Date:   Mon Jul 6 13:32:40 2015 -0700

    Fixed double-free in JPEG allocation
    
    It was incorrectly setting the wrong field to NULL, causing it to get
    freed again later.

[33mcommit 80a0e90d53abf30d71fe6f40e243253cbb2aadba[m
Author: fahickman <f.alan.hickman@gmail.com>
Date:   Fri Jul 3 14:27:29 2015 -0700

    TGA RLE flag and regression fix
    
    Add requested flag for controlling TGA RLE compression and fix a
    regression when writing monochrome TGAs.

[33mcommit 65ebe75124a69193748021fa96eaa6cf660db9b9[m
Author: Liam Chasteen <liam.chasteen@gmail.com>
Date:   Thu Jul 2 11:50:32 2015 -0700

    Tweaked to enable compilation under MinGW.

[33mcommit be8284de7e5cc560185daa35d92f7ea691a041b8[m
Author: ocornut <omarcornut@gmail.com>
Date:   Tue Jun 30 20:02:41 2015 -0600

    stb_wingraph.h: missing lib pragmas for completeness

[33mcommit c11532b8723d548a2444d67691b2cd27a1111152[m
Author: Michaelangel007 <testcraft@sharedcraft.com>
Date:   Tue Jun 30 08:54:14 2015 -0600

    Cleanup unused functions

[33mcommit 2762b410fed870cc5db29a4e34e4eedaaf84f368[m
Author: Michaelangel007 <testcraft@sharedcraft.com>
Date:   Tue Jun 30 08:02:24 2015 -0600

    Fix unused vars warning in stbi_is_hdr_from_file stbi_is_hdr_from_callbacks

[33mcommit 693772ed02dac18c6ff740e6957bd95dd4bd34c2[m
Author: blackpawn <jim@blackpawn.com>
Date:   Mon Jun 22 19:45:35 2015 -0700

    OSX 64bit fixes
    
    Check for __LP64__ preprocessor define for 64bit. Allocator fix for 64bit.

[33mcommit 8702dce4d646ca80e50c33e9e190b210a77cac14[m
Author: r-lyeh <r-lyeh>
Date:   Sat Jun 13 13:50:31 2015 +0200

    msvc 64-bit fixes

[33mcommit b53c08a14808ba911a0ffa81a26a00615026a702[m
Merge: aa89970 3787e1c
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 10 12:05:29 2015 -0700

    Merge pull request #127 from mikesart/master
    
    Fix relative path check for non-Windows platforms in stb_fullpath.

[33mcommit 3787e1c143715ccedd14e552c6ec7c895773f662[m
Author: Michael Sartain <mikesart@gmail.com>
Date:   Tue Jun 9 16:52:39 2015 -0700

    Fix relative path check for non-Windows platforms in stb_fullpath.

[33mcommit 51415dea6e790741076857b03a19532619149abf[m
Author: Robert Nix <mischanix@gmail.com>
Date:   Tue Jun 9 12:47:50 2015 -0500

    Fix 64-bit compile for pointer set

[33mcommit 0fbc8bec6f613bd91ec07ffc67ab0dae8a458b50[m
Author: Robert Nix <mischanix@gmail.com>
Date:   Tue Jun 9 12:46:31 2015 -0500

    Don't truncate pointers to 4 bytes on 64-bit

[33mcommit b639b6a4680fef7595af4c639fcc1bfa91624bf8[m
Author: Robert Nix <mischanix@gmail.com>
Date:   Tue Jun 9 12:44:50 2015 -0500

    Don't use __asm int 3; on 64-bit platforms

[33mcommit 126ec22867c88917ab3da278e0e126b104f55b00[m
Author: fahickman <f.alan.hickman@gmail.com>
Date:   Thu Jun 4 14:04:02 2015 -0700

    add missing consts

[33mcommit aa89970d6be59d6cc0f18f49f392b3f58f145c7d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu May 28 22:11:45 2015 -0700

    stb_image.h: fix *comp value when loading PSDs
    stb_voxel_render.h: fix STBVOX_CONFIG_OPTIMIZED_VHEIGHT

[33mcommit 1b157be513e3f48a8bf4605a73fc5cb59cbd6e37[m
Merge: 2c13513 947bdcd
Author: ocornut <omarcornut@gmail.com>
Date:   Thu May 28 08:55:13 2015 +0100

    Merge remote-tracking branch 'nothings/master'
    
    Conflicts:
            stb_truetype.h

[33mcommit e0e4bd4d861b90282e48bd467865f8c7bb389779[m
Author: fahickman <f.alan.hickman@gmail.com>
Date:   Mon May 11 21:38:55 2015 -0700

    write TGAs with RLE compression

[33mcommit d1d5f4ca96c09b0b2dca82247fa301a3e77f5f6a[m
Author: Guillaume Chereau <guillaume@noctua-software.com>
Date:   Mon Apr 20 23:18:42 2015 +0800

    add STB_IMAGE_WRITE_STATIC macro
    
    This is the same thing than STB_IMAGE_STATIC of stb_image.h.

[33mcommit 347e7838be93e60aecb319cea83d3e15f2abef75[m
Author: Guillaume Chereau <guillaume@noctua-software.com>
Date:   Mon Apr 20 22:59:24 2015 +0800

    fix compilation of stb_image_write.h with gcc -O3
    
    When compiling with -O3, gcc would complain that 'linear' might not be
    initialized if comp is superior to 4.
    
    In fact passing a value > 4 is an error anyway, but gcc does not know
    that.  I changed the switch case to support comp > 4.  I don't think it
    should affect the performances.

[33mcommit 947bdcd02716b6bb9f365710b23493ae1564f990[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 19 04:19:55 2015 -0700

    update version numbers & docs

[33mcommit 8f9c8b682d3cd9bfd819859a4a0fcbef60225148[m
Merge: b4b196a 1894bed
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 19 04:17:21 2015 -0700

    Merge branch 'master' of https://github.com/nguillemot/stb

[33mcommit b4b196af1c02acef15b8e1b9fd205b30393f1a37[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 19 04:16:11 2015 -0700

    update version numbers

[33mcommit ac5e25ae01b82018adca7fbcf8e5e58dbc322e07[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 19 04:15:33 2015 -0700

    bump stb_image to version 2.05, tweak docs

[33mcommit f224bc2cdbbcf603a2d36e275a277a1969635aee[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Apr 19 01:49:16 2015 -0700

    stb_image: Progressive AC decoding - fix ZRL code.
    
    The original AC decoding logic handled ZRL (runs of 16 zeros)
    incorrectly.
    
    The problem is that the original flow set r=16 and skipped the
    final coeff write when s=0. This is not actually correct. The
    problem is the intervening "refinement" bits.
    
    With the original logic, even once we decrement r to 0, we keep
    reading more refinement bits for subsequent coefficients until
    we find the next currently-unsent AC in the current scan. That is,
    it works as if it was trying to place 17 new AC values, and only
    bails at the last minute from actually setting that 17th value.
    
    This is wrong. Once we've found the 16th previously-unsent AC, we
    need to stop reading refinement bits, otherwise we get out of sync
    with the bit stream (which expects us to read a huffman code next).
    
    The easiest fix is to just do what the JPEG standard implicitly
    assumes anyway: treat ZRL as a run of 15 zeros followed by an
    explicit magnitude-zero AC coeff. (That is, leave s=0 and actually
    write s). So this is what this fix does.

[33mcommit 1894bede3f88007b78aca6130af7ff556e8929c5[m
Author: Nicolas Guillemot <nlguillemot@gmail.com>
Date:   Sat Apr 18 21:23:34 2015 -0700

    fix signed/unsignted compare warning

[33mcommit fda335609f25d717d84f1e08026d5cb728764bd9[m
Author: Nicolas Guillemot <nlguillemot@gmail.com>
Date:   Sat Apr 18 20:39:46 2015 -0700

    don't redefine __forceinline with mingw
    
    mingw redefines __forceinline (though I don't think this applies to all
    versions of mingw.) Therefore, don't redefine it if mingw has already
    defined it.

[33mcommit e4be8fae2c3688094fbc6e4721fdab5495712234[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 16:06:46 2015 -0700

    fix misplaced STBTT_DEF definition

[33mcommit 294340b25d8b0cc2ec74ea03a445da49c67db30a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:59:17 2015 -0700

    update version numbers

[33mcommit e927c3a07aa3533486b0bbc3510b08192c15c6eb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:58:00 2015 -0700

    rename to STBRP_SORT for STBRP_ASSERT consistency;
    version number, credits

[33mcommit e536701585419f3b7d24c714c709a34b88428be6[m
Merge: 9487a59 8bfd635
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:54:01 2015 -0700

    Merge branch 'rectpack-allow-to-replace-qsort' of https://github.com/mmozeiko/stb into work2

[33mcommit 9487a59c14a798022d0b8aa787c9757b6cd5ef83[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:52:25 2015 -0700

    STB_TEXTEDIT_memmove

[33mcommit d5251d527b820022fa3511c1f503562db2acac13[m
Merge: 1acf56b 198ee82
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:49:58 2015 -0700

    Merge branch 'textedit-allow-to-replace-memmove' of https://github.com/mmozeiko/stb into work2

[33mcommit 1acf56b8fb9e087e46c89b21873c9be3b73073cd[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:40:15 2015 -0700

    tweak credits

[33mcommit b92b225f61a35c90bf7a202d5cc8b88afdb620ae[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:35:55 2015 -0700

    note that README is auto-generated so submitters don't need to change it

[33mcommit d710ada2f9d6f7ffcc9ee21a379c41482bbeae5e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:31:12 2015 -0700

    try to re-enable SSE2 support by default on mingw 64-bit

[33mcommit 457679209b7dc2214637ddbb7b893039bc4a3398[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:22:19 2015 -0700

    update truetype version #

[33mcommit a51c2d4ab02d1e835850f70a1f154f318d26e03f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:21:59 2015 -0700

    update version number etc

[33mcommit 6231981a47a6d19fd1e546a049d9ff385a8494ec[m
Merge: 9d4da3f 63550ae
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:20:42 2015 -0700

    Merge pull request #106 from g-pechorin/patch-1
    
    Update stb_truetype.h

[33mcommit 9d4da3f7ccf1fd7cee0c74720bcf875b0300f24d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:18:48 2015 -0700

    update readme

[33mcommit 85c836f33c07cdb8593072c8e89b0ebef73521d0[m
Merge: 0d7f3bb 6cb8c1b
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:18:42 2015 -0700

    Merge branch 'work2'

[33mcommit 6cb8c1b624a15f4266c16ef2898b63a1db6a963f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:17:44 2015 -0700

    make compile as C

[33mcommit 0d076c08b35917fc4d8c7b9b502e2c2c2eeefdba[m
Merge: 53011a3 3f418bf
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:12:13 2015 -0700

    Merge branch 'working_stbte' of https://github.com/machinamentum/stb into work2
    
    Conflicts:
            README.md
            stb_tilemap_editor.h
    
    tweak revision history, backout README change since that's auto-generated

[33mcommit 53011a3d96761196a09ef74ac872fdb8bf9cbd91[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 15 02:10:02 2015 -0700

    fix declaration of stbte_create_map

[33mcommit 63550ae9edefffece9b4b50cdb47353b5d9ee534[m
Author: Peter LaValle <peter.lavalle@gmail.com>
Date:   Tue Apr 14 13:03:05 2015 +0100

    Update stb_truetype.h
    
    trivial typo

[33mcommit 0d7f3bb60b68c606eb4b75cf1d2bfc8b750f6d88[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:53:57 2015 -0700

    update version numbers for minor libraries that have been made C++-compatible

[33mcommit 3f17b24d9062f30973f217d3799691ddedc4b04c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:53:26 2015 -0700

    make sure all libs compile as C++

[33mcommit cbcbaff851d2406f086d29f90d8bda3f5e9b5189[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:38:40 2015 -0700

    replace public-domain rationale with link to longer public domain rationale document

[33mcommit e105a19be99fc28088a78618be59a4b0ced5b304[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:33:54 2015 -0700

    add summary statistics

[33mcommit f982f5ae1e0f723762c5bf0bc10a04843a5aa848[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:25:12 2015 -0700

    restore lines-of-code to original size

[33mcommit dda1519da8f3d87d7e09bc9f104fe66595902bb7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:19:54 2015 -0700

    shrink font for LoC to layout table better

[33mcommit 977cce8cc75075c74141033ca8b588010eca207e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:13:45 2015 -0700

    expand explanation of why single file

[33mcommit 3db3e566968a207eac6c67fbad5e07c74259bc98[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:10:36 2015 -0700

    consistent capitalization

[33mcommit c1ad6b09def878d275d4ee52af61ed1d5af375fc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:09:01 2015 -0700

    make table more readable by shrinking some columns horizontally

[33mcommit 3c2090565db9c91b560349a35eb8642d815d87b4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:04:32 2015 -0700

    fix reversed column headers

[33mcommit e5a2c3cf865053c32be133bd4ecaa667f8f5ec9c[m
Merge: ede1ebd 8f4958e
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:03:37 2015 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit ede1ebdaa966f98fadc67bfbb2f9b35a8adf1f09[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 03:03:11 2015 -0700

    add "lines of code" to README.md

[33mcommit 8f4958e1f0e85cd6274cb37f2789f039d2512c9b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 02:05:54 2015 -0700

    Update why_public_domain.md

[33mcommit 0a3b6adb32ad1f65aa8fb3cea7f3acb474d9b6e6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 02:05:18 2015 -0700

    Update why_public_domain.md

[33mcommit 8fece213ee9a00f6037852a0fd50e4fcb02897f0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 02:04:44 2015 -0700

    Update why_public_domain.md

[33mcommit d44e52d3638b8dd3eaaa7958c5352976f4ffaa12[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 02:03:22 2015 -0700

    Update why_public_domain.md

[33mcommit 31461003c7d89fa6a814d5d741477719c84a5fa7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 02:00:59 2015 -0700

    Update why_public_domain.md

[33mcommit 2f17f1a93b9ee14f6f096f0b10070233b73417e0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 01:58:25 2015 -0700

    Update why_public_domain.md

[33mcommit 80744251282f86faa0e0812fe796a34af5799d8c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Apr 14 01:56:56 2015 -0700

    standalone public-domain rationale document

[33mcommit 1384715b11ce74ea43908782bda237cd2b0545a2[m
Merge: 9534eb2 07a598c
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:58:26 2015 -0700

    Merge branch 'master' into working

[33mcommit 07a598cb2ffe8f567955039dd1f78038a9eee652[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:58:04 2015 -0700

    update stb_image_write version

[33mcommit 6dc6304d89ebeab6e385ffa75c155ebde6914bb9[m
Merge: 8a0a882 00b1797
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:56:42 2015 -0700

    Merge branch 'work2'

[33mcommit 00b1797a2398c8b7a92b195f30224efbf247bdf8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:55:24 2015 -0700

    switch memcpy to memmove for simplicity;
    rename all STBI_ config macros to STBIW_ to avoid conflict with stb_image.h

[33mcommit 019236a624835d37717786e99f5691948c342627[m
Merge: 533cf5c 8b1d835
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:48:26 2015 -0700

    Merge branch 'stb-image-writer-memory' of https://github.com/callidus/stb into work2

[33mcommit 533cf5cc4fad8270c4889238bf044f0be7586adb[m
Merge: a7ee207 80176ae
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Apr 13 11:47:57 2015 -0700

    Merge branch 'patch-1' of https://github.com/jorgenpt/stb into work2

[33mcommit 8a0a882f53d18cb34416ac04d848a08484832378[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 12:46:36 2015 -0700

    stb_truetype version update

[33mcommit a7ee207475f59a4db0786d96158e13bca29312dd[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 12:45:23 2015 -0700

    fix missing free in the new rectangle packing
    remove unneeded (but harmless) statements

[33mcommit ab6aaa85bee044ece66631f45630b44b55788d9b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 12:36:06 2015 -0700

    credits, STBTT_STATIC docs

[33mcommit 025ca3f15721427cd4f17c52f3027057b268b4aa[m
Merge: 1e57bcd 45fec17
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 11:49:00 2015 -0700

    Merge branch 'stb-truetype-static' of https://github.com/ocornut/stb into work2

[33mcommit 1e57bcd5445b959f85025be114bb8d38dcc113fd[m
Merge: 25e9e1e 7579b8a
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 11:48:39 2015 -0700

    Merge branch 'master' of https://github.com/cap/stb into work2

[33mcommit 25e9e1e72bef08872e6d3734f9bea34f0f1b9e66[m
Merge: 24bcc44 30eb437
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 11:48:11 2015 -0700

    Merge branch 'no-double-literals' of https://github.com/mmozeiko/stb into work2

[33mcommit 24bcc4432b23a419ad37a294081aa9d263e41ba7[m
Merge: 24a2545 ffe4476
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 11:47:55 2015 -0700

    Merge branch 'truetype-memset-defines' of https://github.com/mmozeiko/stb into work2

[33mcommit 24a25458e329908b82d8c2d39d9d3d0618208c88[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:36:44 2015 -0700

    update version number

[33mcommit 66a75195dc02ce3c2434d0f4d970777e689ed05d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:36:01 2015 -0700

    rename STBI_X86_TARGET to STBI__X86_TARGET

[33mcommit c83abb051a8040d5514664ab211c2519b3428c81[m
Merge: e5fde30 4b0c6f6
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:33:26 2015 -0700

    Merge branch 'mingwfix' of https://github.com/rygorous/stb into work2
    
    Conflicts:
            stb_image.h

[33mcommit e5fde30800e4f57f7d1b46d7d7891b4fce8273d5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:30:05 2015 -0700

    merge two x86/x64 tests into one; update credits

[33mcommit c8852111cca5b32111f2d948f13c477fbc27ef1c[m
Merge: f22efc6 abe8100
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:26:25 2015 -0700

    Merge branch 'master' of https://github.com/pmj/stb into work2

[33mcommit f22efc6151e4855b03b739845d34ab28f62483a0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:26:16 2015 -0700

    update credits/docs

[33mcommit 9d7499bca6ca1ea38ac95a465f1ab4e41cb200a3[m
Merge: 040df96 a60912f
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:23:07 2015 -0700

    Merge branch 'master' of https://github.com/hpesoj/stb into work2

[33mcommit 040df963c8c483c52f2d68b173d2fda899a213eb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:20:31 2015 -0700

    modifications to vertical flip API:
     more consistent name,
     refactor stbi_load_main to preserve old code,
     support float HDR path,
     minor bugfix

[33mcommit e3214d7ff7925e1274a26ce9bd483869d52c9ccf[m
Merge: 24e50cb c500a90
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:07:32 2015 -0700

    Merge branch 'master' of https://github.com/nguillemot/stb into work2

[33mcommit 24e50cbd5d8b4e895eed57fe37fa9b67d2405dff[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 09:04:43 2015 -0700

    remove asserts that are now run-time checks;
    bump version and update credits;
    minor whitespace changes;

[33mcommit 7b726511345ccb1ef5044efa8a1cdd42be872547[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 08:59:49 2015 -0700

    add stb_voxel_render to standard compilation tests

[33mcommit 9534eb2e080ef1d8b0108d6d84976e950244203f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Apr 12 01:23:18 2015 -0700

    added input.packed_compact for storing most of the major 2/3-bit values in one byte

[33mcommit b2d440cfb5f01e1c454e1b5d722245b24b046d19[m
Author: Martins Mozeiko <martins.mozeiko@gmail.com>
Date:   Sat Apr 11 15:49:56 2015 -0700

    Fixing various crashes when loading jpg, png and tga images.

[33mcommit 75f69ce5ed0892f641200f83d7223af29bb727f4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 11 01:13:46 2015 -0700

    clarify what "largest memory usage" case of vheight is

[33mcommit 3629a60ec384bd1f6db0076d951d0bb9a9ed6fb5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 11 01:06:38 2015 -0700

    stb_voxel_render version update

[33mcommit 668525656035c5ac64a29558375b8fedf4137a60[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 11 01:05:55 2015 -0700

    change STBVOX_MAKE_LIGHTING to STBVOX_MAKE_LIGHTING_EXT so header file
    doesn't have to see the config variables (although this way is actually
    more bug prone since you can now use the wrong macro)

[33mcommit e2b645e4d75fd247f127fd36b4cf786c63a8179a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Apr 11 01:01:57 2015 -0700

    Add vheight documentation;
    Add a missing vheight case;
    Add STBVOX_CONFIG_VHEIGHT_IN_LIGHTING;
    Fix broken STBVOX_CONFIG_ROTATION_IN_LIGHTING that was broken when I incompletely refactored the #define

[33mcommit 8b1d835e16c8600a913ec56864b0e66369db9f37[m
Author: Tim Kelsey <tim.kelsey@hp.com>
Date:   Wed Apr 8 15:24:46 2015 +0100

    Adding memory and assert defines to stb_image_write

[33mcommit b7570147f725d1bb822ef381dfcb448ec03e38f4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 15:37:14 2015 -0700

    version number

[33mcommit 5cc48593d4074ce3f3cd8a87d71f7d5a19adbb02[m
Merge: 5c4ce8f fbdaca8
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 15:35:41 2015 -0700

    Merge branch 'master' of https://github.com/Sofahamster/stb into working
    Fix missing types to be 'unsigned char' not 'int'
    Fix handling of string constants which are const-char-* on modern compilers
    
    Conflicts:
            stb_voxel_render.h

[33mcommit 5c4ce8fdf7b0d8385c920d2eb4601f264d0f80c9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 15:23:00 2015 -0700

    add missing types to allow compiling as C++, and use less cache

[33mcommit 62e732bfaba132b43b67b17e5cfa1430769d3815[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 12:45:17 2015 -0700

    disambiguate

[33mcommit fbdaca8d2c8f305a7fffe01a55c8462974644093[m
Author: Thomas Frase <github@hamstersofa.de>
Date:   Thu Apr 2 20:18:24 2015 +0200

    Added some missing ints to make the code compile as C++ with GCC.
    Added a few missing consts to remove GCC warnings about deprecated
    conversion from string constant to 'char*'

[33mcommit c5261f41d791e2c6b1f78aca9c499dc8db4c72a1[m
Merge: cd1d05b 49865c7
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 07:09:23 2015 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit cd1d05b3898b61db123a5a4143aa28677e097ce4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 07:08:27 2015 -0700

    voxel render 0.78; compile as C++, fix bad #else

[33mcommit 49865c703a759d0f15a00b3086b970b44bda89a4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 06:22:39 2015 -0700

    disambiguate

[33mcommit edda820d4f09a3aede5d91a1dc86b406eb5a2c36[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 02:56:36 2015 -0700

    whoops fix last fix

[33mcommit 5e7c226b34afa5597339662bc7595cd09900db9e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 02:50:41 2015 -0700

    disambiguate

[33mcommit 01540789bbee329d03b9fe08dc9178a81b7e9a40[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Apr 2 02:48:12 2015 -0700

    Update stb_voxel_render_interview.md
    
    Removed unnecessary parenthetical.

[33mcommit abf217de52a53f05ca754e88d7a9063042c25302[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:58:49 2015 -0700

    stb_voxel_render version 0.77

[33mcommit fd62364d96d13428edd3f8fa86fedc156b16cfe6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:57:46 2015 -0700

    rename static-implementation define to STB_VOXEL_RENDER_STATIC for consistency

[33mcommit a1f1010fad9443c7bf81ad08263f738bc6008247[m
Merge: 0b05bde a1f8eb3
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:47:02 2015 -0700

    Merge branch 'master' into working

[33mcommit a1f8eb30c10b9a9f2489b4f305a608f432d73b0f[m
Merge: 26a342b 70eaad4
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:46:38 2015 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 26a342ba2e330c081774e89f4151fe7ce0bba895[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:46:30 2015 -0700

    documentation tweaks

[33mcommit 70eaad4a88962a8cfcc61e89540aefcca9196f28[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 16:46:00 2015 -0700

    improve config macro documentation
    
    clarify which config macros are required and which are optional

[33mcommit 90d58e577e94816073a3f74c57ab6b622c73bc98[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 13:52:03 2015 -0700

    Update README.md

[33mcommit d768440ce7c84f0a8dda34c304bb4914841e86c0[m
Merge: 089b3e4 feae54a
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 13:42:25 2015 -0700

    Merge pull request #99 from Mischanix/depth
    
    Request a 24-bit depth buffer

[33mcommit feae54a2d91c7123329bf9ed4c9c1dbbd64ae054[m
Author: Mischanix <mischanix@gmail.com>
Date:   Wed Apr 1 12:41:49 2015 -0500

    Request a 24-bit depth buffer

[33mcommit 089b3e4395216198334699f5ca02fc6ab9594705[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 06:11:13 2015 -0700

    version number

[33mcommit 081fd6945c8413cdf4afd05a8180816e3df7b6f1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 06:08:36 2015 -0700

    comment tweaks

[33mcommit 2cbeaa3001ac7f96c8bed2e7b1f57cf5ecc031cf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 05:47:36 2015 -0700

    bump to version 0.76; documentation, minor changes to texlerp, other input tweaks

[33mcommit 5690ff7c6044f8e79d78a67fbc3f9dcdce2607d7[m
Merge: e115ae3 ebb3b47
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 03:06:06 2015 -0700

    Merge pull request #96 from jsfdez/patch-1
    
    Build fix

[33mcommit ebb3b475d7acd46d95c11edcc0cbfd1f7dd2174e[m
Author: Jesus Fernandez <jsfdez@gmail.com>
Date:   Wed Apr 1 11:35:54 2015 +0200

    Build fix
    
    x, y, z members not found because stbvox_default_normals contains arrays not structs.

[33mcommit e115ae38f23be24af4a86bfc74a9ff20c9c75420[m
Merge: 0f52f6a 0ef28d6
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 01:19:52 2015 -0700

    Merge pull request #95 from debiatan/master
    
    I like the word 'implementation'

[33mcommit 0ef28d6bb5e4e4394601fe6c9432be2d0fca494b[m
Author: Miguel Lechón <miguel.lechon@gmail.com>
Date:   Wed Apr 1 10:04:38 2015 +0200

    I like the word 'implementation'.

[33mcommit 0f52f6accc3eac785c21461af6d07d4257288287[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 00:44:05 2015 -0700

    note documentation failure; update README.md

[33mcommit 92de5ecbb2a0690815049dea82cd8cbeaee7f09a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 00:28:17 2015 -0700

    youtube link

[33mcommit 3bb829574d0b9cbcb654cc9c530d6c730a00b62e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Apr 1 00:24:46 2015 -0700

    mostly documented

[33mcommit 9e5e19f5a34fb7f9b170a635b682c42579f6cb79[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Mar 31 02:32:17 2015 -0700

    various fixes

[33mcommit 28630fb25360dcdf1f4070c547d21341f1029729[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Mar 30 13:19:06 2015 -0700

    various fixes

[33mcommit c500a9037565053f7763eadf3d7b3806072fb8d4[m
Author: Nicolas Guillemot <nlguillemot@gmail.com>
Date:   Sun Mar 29 03:03:09 2015 -0700

    added stbi_vertically_flip_on_load

[33mcommit 0f8e471f7bb2328e3367dcab7b5a5464228ede56[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Mar 28 17:36:09 2015 -0700

    various voxel/caveview improvements

[33mcommit 80176ae4a144d142756aae3176eb8372da3bcb6c[m
Author: Jørgen P. Tjernø <jorgenpt@gmail.com>
Date:   Tue Mar 24 11:22:20 2015 -0700

    Remove unused variables in write_hdr_scanline.
    
    Fixes #90.

[33mcommit 8bfd635220544916a93020686e88186eb681ed63[m
Author: unknown <martins.mozeiko@gmail.com>
Date:   Fri Mar 20 15:01:53 2015 -0700

    Allow to replace qsort function with custom implementation

[33mcommit 198ee828caf8ebf8b5051361785ffd709850ac87[m
Author: unknown <martins.mozeiko@gmail.com>
Date:   Fri Mar 20 14:58:38 2015 -0700

    Allow to replace memmove function with custom implementation

[33mcommit ffe447630d177c4f262407e4b47482ccb21adc84[m
Author: unknown <martins.mozeiko@gmail.com>
Date:   Fri Mar 20 14:54:47 2015 -0700

    Couple of places should be using STBTT_memset instead of memset

[33mcommit 30eb4371c82a8d9bbf97e75abe8467981856ea20[m
Author: unknown <martins.mozeiko@gmail.com>
Date:   Fri Mar 20 14:49:58 2015 -0700

    Change double literals 0.5 to float type

[33mcommit 0669a6659a4dc3efd4b905fbd79a65c889cb3838[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Mar 17 02:21:17 2015 -0700

    fixes for premultiplied alpha

[33mcommit ba49d37e6a8396623d8c171c145ab1f1a5e5e0d4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Mar 17 02:10:58 2015 -0700

    premultiplied alpha support

[33mcommit f49c90c03d3a0f3331c9f07201af1b33115e0bc5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Mar 15 11:17:14 2015 -0700

    beginnings of mode support;
    reconstruct full table of bit allocations per mode

[33mcommit c588d29e955150f72bbd157ef66df4a47db6d3ea[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Mar 15 10:18:13 2015 -0700

    switch shader variation from runtime-with-tags to dynamic with #ifdefs;
    support making all definitions static so you can have multiple copies of file (with different #ifdefs);
    move all tables to end of file (this will have to be undone later because IIRC it's not compatible with C++ or with some compilers or something, but it'll make my life easier in the interim);

[33mcommit 3a2c54d4a0c6eb42f2eaa81b610085decc4a8288[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Mar 14 19:50:32 2015 -0700

    check off todo-list item for previous check-in

[33mcommit 00810b7d118a04d3d4eff3a556e7859ba1690125[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Mar 14 15:02:51 2015 -0700

    correct normals for vheight floors

[33mcommit c10b3fefae6a4a3c6d98960afab306b04ecb7d90[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 19:00:34 2015 -0700

    correct normals for upwards slope (and dummy lighting to test it)

[33mcommit 177498673e82cd9a54237f2335872427d7d8db3c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 12:39:30 2015 -0700

    update readme with wood type status

[33mcommit 6509e1d1e717247dd479bc6b5b30303252c0f2e3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 12:45:49 2015 -0700

    minecraft wood types (only for solid blocks)

[33mcommit 5a8064bad22f3ac9f6f0956cd35cfe4bc1901458[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 12:04:45 2015 -0700

    fix texture coords to not be reflected on north & south walls

[33mcommit c2ee843df3c08c722b472f3cec7c0226c9e13caa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 12:00:50 2015 -0700

    update todo for previous checkin

[33mcommit f02b0d700f8541399ebbe7501dc00da291096a1e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Mar 13 12:00:00 2015 -0700

    if vertex buffer is full, mesh builder stops gracefully and remembers where to continue

[33mcommit efcd76c9abfe9d56dc3a70de2b1518f60de5ae72[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Mar 12 19:03:49 2015 -0700

    support texture rotation; better interaction of mouse centering & VC6 debugger; fix in-place conversion when mca blocks are written in different order

[33mcommit 3d4f545fd79aeb833fd649ec690acce89600cfd9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Mar 12 11:38:10 2015 -0700

    remove unused gl_fragColor support

[33mcommit 673cbb1ee48ad953f1fbf568a7710aac4d3461f9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Mar 12 00:07:50 2015 -0700

    remove unused code from cave_main

[33mcommit 0cd5465f5216a2c5fc8b2be3a0fe4a2fbdca907b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Mar 12 00:00:10 2015 -0700

    re-add README.md that was in a different branch

[33mcommit c27a6c6c36a7b3be9a93ea6f8335a12ebd43d596[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Mar 11 23:54:45 2015 -0700

    restore old q&a

[33mcommit 14b203571a4b2fb17478ea39ee77e9676e2c3c0b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 18:27:17 2015 -0800

    forgot to check in .dsp file after the renames

[33mcommit f9c24c20fc44b989909ffb0085fbd16f2c22f036[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 17:42:46 2015 -0800

    various cleanup; vheight works (only one path tested)

[33mcommit 1d18b23ea1b5b5d345232a90834978245a13ed52[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 15:52:03 2015 -0800

    replace main.c & game.c with cave_main.c

[33mcommit 7add4d09b9804edc79982ce7a274bf7a073b75fb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 15:42:24 2015 -0800

    delete game.h

[33mcommit 0e2583041db908311ce46cb7b65cf2864c9c394a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 15:25:54 2015 -0800

    minor cleanup

[33mcommit 5a0dcc90d6f65b1674067c905ee7beaee88acdf9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 15:09:22 2015 -0800

    initialize cache mutexes in right file

[33mcommit cd17050ca45bdabd684692ddc9b08107f8460342[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 15:03:04 2015 -0800

    split render.c into cave_mesher.c and cave_render.c

[33mcommit 2770c92148f876fe1786b1764cf9db4cb48713f9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 14:34:05 2015 -0800

    initial stb_voxel_render version with working minecraft viewer

[33mcommit 0b05bde303cefc8aab945eccc4866b374c73fecd[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 22 14:26:21 2015 -0800

    quick fixes w/o version updates

[33mcommit 7579b8a177271db84be9081faec7ac3586397edd[m
Author: Cap Petschulat <zfcd21@gmail.com>
Date:   Sun Feb 22 10:36:26 2015 -0800

    Fix the simple truetype example

[33mcommit a60912f145eee98164750e35991ee7e3e8fccfde[m
Author: Joseph Thomson <joseph.thomson@gmail.com>
Date:   Fri Feb 20 10:12:50 2015 +0000

    Avoid GCC sign-compare warning.
    
    GCC 4.7 gave the warning "signed and unsigned type in conditional
    expression" because the ternary operator mixes signed and unsigned
    integers. Fixed by casting to unsigned inside the "if" branch instead
    of casting the result of the entire conditional.

[33mcommit 4b0c6f6634b62aada5426ea556574717d1095a45[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Feb 17 01:21:40 2015 -0800

    stb_image: NEON and SSE2 SIMD detection fixes.
    
    This fixes two things. First, the logic to disable SSE2 on
    GCC unless "-msse2" was not specific enough, and ended up
    disabling SIMD support on NEON targets entirely. Shuffle
    the detection logic around to make that bit x86-specific.
    
    Second, 32-bit MinGW assumes 16-byte aligned stacks, but this is
    not in the Windows ABI and hence DLLs and callbacks don't
    necessarily provide it. This caused a crash.
    
    This can be fixed by providing the right command-line option,
    which we have no control over. As a compromise, disable the SSE2
    path on MinGW unless a specific #define explained in the comments
    is set. That way, we default to safe (never-crashing) behavior
    unless the user explicitly signals they know what they're doing.

[33mcommit abe81006dbde19dd280eb2d02152d9aae5904d7d[m
Author: Laura Dennis-Jordan <laura@ssdcache.com>
Date:   Thu Feb 5 20:49:04 2015 +0100

    Fixed bug where NEON code was #ifdef’d out on GCC/clang even where explicitly requested.

[33mcommit bdef693b7cc89efb0c450b96a8ae4aecf27785c8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 1 02:49:36 2015 -0800

    add FAQ about single-header-file libs

[33mcommit 4b518bb2b609efe62244d9d9fee85b0f36d88299[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 1 02:45:11 2015 -0800

    whoops, didn't mean to check in those changes for this file, but did for the other files

[33mcommit a3e84e25dd6974688810fa66dc8152ef7add3b87[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Feb 1 01:49:17 2015 -0800

    added stb_easy_font.h

[33mcommit 3f418bfe6e4db5dd93fe93b35b55c7af7b4a745c[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 21:59:01 2015 -0500

    stbte: fix; prop button now draws 't' in default
    
    prop button didn’t draw the ’t’ when the panel is expanded

[33mcommit 6cc48214ac02181d3c771ad3dd47abd647b2517e[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 21:17:24 2015 -0500

    stbte: removed redundant conditional

[33mcommit e62a54ee0bdf88aa5c42b71790d58b95e6203b99[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 18:58:59 2015 -0500

    stbte: fix number rendering when no layernames set

[33mcommit ba38019c9585af63fd9759879f11f764cfb26210[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 18:46:57 2015 -0500

    stbte: fix layername button growing for both sides

[33mcommit 87faf06b5d195462a2c9b66ecc86b69febd908a2[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 18:06:40 2015 -0500

    stbte: update documentation/version 0.31
    
    Changed REVISION HISTORY, TODO, CREDITS, and README

[33mcommit f82fbb2e36bcacc781561e6034813f808df1648f[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 17:55:03 2015 -0500

    stbte: layername button grows/shrinks
    
    Layer name buttons grow to fill box

[33mcommit 7a0b46075ca5fcd46fc6b161f84c13e4cb7d8cf4[m
Author: joshhuelsman <joshuahuelsman@yahoo.com>
Date:   Fri Jan 30 17:07:57 2015 -0500

    Fix stbte_create_map declaration

[33mcommit 45fec171488b1bbf3f602d8ffd269a78e9eaa49c[m
Author: ocornut <omarcornut@gmail.com>
Date:   Wed Jan 21 23:38:29 2015 +0100

    stb_truetype: added STBTT_STATIC to make all implementation static
    
    Followed the structure used by stb_rectpack.
    Functions that had neither extern neither static got STBTT_DEF  as well.

[33mcommit 2c13513a956dd8e22f2c775100276777a5a6c5ce[m
Author: ocornut <omarcornut@gmail.com>
Date:   Wed Jan 21 23:21:19 2015 +0100

    stb_truetype: fix for if stb_rect_pack .h wasn't included.

[33mcommit 0d840ab3303aa645ae09dc9338a931fce754a8b5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jan 21 07:46:54 2015 -0800

    quick & dirty leak checker

[33mcommit ec2158386c877a2388038d0587f22b129a2cc03e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 19 05:20:56 2015 -0800

    update version number

[33mcommit 5bad08171111452c10f3badd9e6e7ab06ab1c12b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jan 19 05:18:37 2015 -0800

    fix incorrectly-named assert, attempt to fix (char) cast warning (tricky since char's signedness is unknown)

[33mcommit b3653cc3f17a02fe249671624d950d716a4b0806[m
Author: Philipp Wiesemann <philipp.wiesemann@arcor.de>
Date:   Sun Jan 18 21:17:49 2015 +0100

    fix double free (found by cppcheck)

[33mcommit 22fa9a467ad26e9f214a078bc827f0c2f7acc15a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jan 18 10:43:42 2015 -0800

    rewrite HDR rle logic

[33mcommit 90c18fd41a4f4f6c47e4b7600f798a91b97f4513[m
Author: ocornut <omarcornut@gmail.com>
Date:   Sun Jan 18 15:24:33 2015 +0000

    stb_truetype: split stbtt_PackFontRanges() into 3 functions for advanced uses, allow stbtt_PackBegin() to take NULL pixels

[33mcommit 80d5c4be4818f3a0ccf28c93aaf1f04b29a6f5b9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 09:16:48 2015 -0800

    fix bug introduced when doing hdr cleanup

[33mcommit c315b164b711b28ecad14051dce06928fadf5c15[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:41:54 2015 -0800

    update version numbers

[33mcommit 5ad4169ed1df7c283e042dc1fd34954e8f3aaf68[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:39:41 2015 -0800

    update version number

[33mcommit 50edcdb972feb0a1b62777c40da987d3e751c93a[m
Merge: 4ae1bc4 933a1fd
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:37:50 2015 -0800

    Merge branch 'master' of https://github.com/scullion/stb

[33mcommit 4ae1bc417bae72b7d56913086b50083ada9bf106[m
Merge: 5c121a9 83c5588
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:36:22 2015 -0800

    Merge branch 'kg' of https://github.com/krig/stb

[33mcommit 5c121a9921afdc87263c4447e88914f7581a8853[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:32:57 2015 -0800

    don't use SIMD on gcc if it's going to fail anyway

[33mcommit 77f816ce735a75891cbf5e4865c639df2c8e266d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:25:30 2015 -0800

    version number

[33mcommit 6f3bda396d0e17a713876f636539e8a9a7061d50[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:25:08 2015 -0800

    credits, version number

[33mcommit 68c8e4851ac4ea7fc032ec16805de1dd8ee7dd56[m
Merge: d673e85 50c5c8e
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:22:28 2015 -0800

    Merge branch 'master' of https://github.com/enginmanap/stb

[33mcommit d673e85e94aa5b1f5076e6e1beecdc71888bad66[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:22:19 2015 -0800

    update credits

[33mcommit 974ca12fb8ceaae811baf424c6f62d1bd4b36c85[m
Merge: 4c9e8dd a2df517
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:19:22 2015 -0800

    Merge branch 'master' of https://github.com/bigmonachus/stb

[33mcommit 4c9e8dd359e0e2cbd4c82ac0891fccdc80a0391d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 08:17:31 2015 -0800

    version numbers

[33mcommit d91cbdf662420b729c87e2c4b78e1964160b5677[m
Merge: f392ec7 edd5e67
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 07:47:52 2015 -0800

    Merge branch 'test'

[33mcommit f392ec7d36f19d67310306d1872cfd86500dee15[m
Merge: a7c8694 6639ef6
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 07:47:45 2015 -0800

    Merge branch 'working'

[33mcommit edd5e6700dfe6e409683e2927c2e4bc5c29c87c5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 07:46:22 2015 -0800

    tweak baldurk's hdr implementation

[33mcommit 258fb153408317de4b70cd1a619e5399f53dda7b[m
Merge: a7c8694 fb8eabd
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 07:23:47 2015 -0800

    Merge branch 'master' of http://github.com/baldurk/stb into test

[33mcommit 6639ef6d5ad6112a56fb46709b0ad96add4d8771[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jan 17 07:15:50 2015 -0800

    fix monochrome bmp support

[33mcommit 529d8163b236e526dccb8640727a71b438febc8f[m
Author: Emmanuel Julien <ejulien@owloh.com>
Date:   Tue Jan 13 17:43:14 2015 +0100

    Add support for writing through callback functions in stb_image_write.h.

[33mcommit 50c5c8e8ca0fa947bd5d4ecb4ab7e0636286848b[m
Author: engin manap <enginmanap@gmail.com>
Date:   Mon Jan 12 11:41:00 2015 +0200

    remove unused variable "ha"
    
    this variable was causing a warning while compiling with gcc.

[33mcommit 1a9be15c1eead2349a332b9d4e371710366dda13[m
Author: engin manap <enginmanap@gmail.com>
Date:   Mon Jan 12 11:34:48 2015 +0200

    Fix dangling else warnings

[33mcommit a2df517a1a1fd8b0d4d6be0e29dfaaece9202a83[m
Author: Sergio Gonzalez <bigmonachus@gmail.com>
Date:   Mon Dec 29 18:43:57 2014 -0600

    Fix for warning 4244. Cast to short

[33mcommit a7c8694d69da57b6d427efddd15992e257f0c179[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Dec 25 11:11:59 2014 -0800

    fix missing STBI_MALLOC

[33mcommit 6e0ae49f878cef64d7b3900637723cb278325b60[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Dec 25 01:40:04 2014 -0800

    update version number, minor docs

[33mcommit febbc34a168bfa50d8bab390b73f55812f50f137[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Dec 24 10:53:31 2014 +0100

    stb_image: Rename SSE2/NEON IDCTs to idct_simd.

[33mcommit d92ab86c65448e10991f9807f038438bd924ed30[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Dec 24 10:15:28 2014 +0100

    stb_image: Fix PNG initial size guess for 1/2/4 bpc.

[33mcommit fb109abeaf4ccd698a8737f773b05dd254f6f33c[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Dec 24 10:07:52 2014 +0100

    stb_image: Update comments.

[33mcommit 7f94e7e5913d7ee1cd021ba5dcdc8ba35e416de8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 23 21:36:20 2014 -0800

    add #defines to allow disabling decoders for unwanted formats

[33mcommit 53ca163e85a153a8bb90ecb663e3db287a4f22fc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 23 20:58:22 2014 -0800

    cleanup merge of ARM NEON support
    tweak docs

[33mcommit de385bb6bb702220440b671a6b00721fbc4610d1[m
Merge: 5b53d20 fd98752
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 23 20:24:46 2014 -0800

    Merge branch 'fastjpeg' into working

[33mcommit fd987527f1b47ba0b1a6e8f6c210cc6e950c89a5[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Dec 24 01:38:59 2014 +0100

    stb_image: NEON YCbCr->RGB kernel.
    
    Also ran a bunch of test cases to make sure the IDCT and H2V2
    resamplers were correct.

[33mcommit 7d32f74d8abad4d2b5233150ffc8a3c82c0a0df9[m
Merge: a32d73d 16d9ed7
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Tue Dec 23 23:52:12 2014 +0100

    Merge branch 'fastjpeg' of https://github.com/nothings/stb into fastjpeg
    
    Conflicts:
            stb_image.h

[33mcommit 5b53d20c685c1cdd251c86f54629d6b3aded4399[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 23 05:11:36 2014 -0800

    Put progressive JPEG AC decode logic back the way I wrote it originally (I changed it to match jpgd when I was trying to figure out why it didn't work);
    add STBI__ prefixes to internal SCAN_ enum;
    strip unused function arguments for progressive funcs;
    tweak release notes;
    forget to git commit frequently so these would all be in their own commits;

[33mcommit 16d9ed721161338f0f701d044fbdb0efcc600f56[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 08:32:09 2014 -0800

    return truetype test code to old path

[33mcommit 6403f319f79fef0e9eccbcc079e7dfb4416fe02c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 08:30:27 2014 -0800

    tweak documentation
    stbi__ prefix on two functions that were missing it

[33mcommit 53008c0922f17026ed65ac7b1cf569b78e24dca5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 08:25:13 2014 -0800

    default tests

[33mcommit e4fb737f6686ddc2f17f81c5be1d5585a478ebc9[m
Merge: 49d4d31 9ad85cc
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 08:23:34 2014 -0800

    Merge branch 'ppm' into working
    
    Conflicts:
            stb_image.h

[33mcommit 49d4d3193f54525b177d75d62560c6cf4b7302a7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 08:21:17 2014 -0800

    fix non-progressive jpegs (had commented out a line accidentally);
    fix long-standing bug where gifs were just broken AFAICT

[33mcommit 33e24eafa0c6465390428af6a9b5d905996e3ba3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 21 07:53:05 2014 -0800

    in progress progressive stuff

[33mcommit a32d73dc3b211cb521b3f673fb6641b6b957ea36[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Dec 21 12:55:50 2014 +0100

    stb_image: NEON integer IDCT (not yet tested!)

[33mcommit 0f3bf1564b36154cd8eb879c57e493667386bab7[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Dec 21 12:46:57 2014 +0100

    stb_image: JPEG resampler func for NEON

[33mcommit 9ad85cc8d2f7ecf7b7afb331248e7e821df3fadc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 20 06:22:17 2014 -0800

    tweak release docs
    tweak credits
    tweak revision history
    remove trailing whitespace

[33mcommit b4e526d7cff9dc8471038a30838f722a6d097711[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 20 06:09:23 2014 -0800

    PNM cleanup
    fix a few old error messages

[33mcommit 97949493fbdbf00e7daacb43f01c5a45304d466e[m
Merge: ba5e333 bdc9187
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 20 05:49:19 2014 -0800

    Merge branch 'master' of https://github.com/kennethdmiller3/stb into ppm

[33mcommit ba5e333fafdbff36feacf1ff5ac41833d8f37677[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 20 05:46:13 2014 -0800

    STBI_MALLOC etc.
    some documentation cleanup

[33mcommit bd6b78f2680dd95320a6658851586164d7b0ff7b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 20 05:13:25 2014 -0800

    finalize scalar YCbCr conversion back-ported from SSE version;
    add missing STBIDEFs to a few functions;
    update documentation with full 1.49 info even though most isn't implemented yet

[33mcommit f259bf27e9e465737d346ad188a62245bb71bd0b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Dec 19 04:39:04 2014 -0800

    VC6:
      support using inline asm for cpuid
    
    YCbCr:
      switch SSE code to constants that match old C;
      create C version that is same as SSE;
      tiny optimization(?) of SSE

[33mcommit 933a1fdd8d3e96e33ce3565ba6db382b982b24ec[m
Author: T. J. Moran <thomasjamesmoran@gmail.com>
Date:   Thu Dec 18 23:17:47 2014 +0000

    Add explicit wchar_t casts in stb.h

[33mcommit b082091bcb1f71c852ec46760d5985098ec9c7f8[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 08:31:03 2014 -0800

    stb_image: GCC fix for new SIMD stuff.

[33mcommit 42bb08b10bc5bf09908d5cfba6518371a11384a7[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 08:11:05 2014 -0800

    stb_image: Add SSE2 h2v2 resampling kernel.

[33mcommit c625d241976220c3370cbbbf3c02c0ca01ac3dcf[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 07:52:44 2014 -0800

    stb_image: First-pass stbi__sse2_available for GCC

[33mcommit aabf2c5c4991f72b661681d6d19edb4e144836e6[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 07:41:41 2014 -0800

    stb_image: SSE2 YCbCr->RGB kernel

[33mcommit d95f7acb32fedffddfb208ee3747b2f8fbbcde9c[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 07:25:41 2014 -0800

    stb_image: Remove old installable IDCT path.

[33mcommit e5db25f637055e28b1fabffd793cc4aac6097c11[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 07:22:42 2014 -0800

    stb_image: Add SSE2 IDCT for JPEG decoder.
    
    Also add SSE2 detection for MSVC++. Detection on GCC will follow
    later.

[33mcommit fb2c841bb8b554f4ca3307921f9f3d8c484313e1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 07:03:21 2014 -0800

    stb_image: Add more of the SSE2 skeleton.

[33mcommit c6a323599519f6b0a542bdf5bfac211e3baeba14[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Thu Dec 18 06:49:41 2014 -0800

    stb_image: IDCT kernel func ptr in stbi__jpeg
    
    I want to support SSE2 kernels that auto-detect. If implemented
    using globals, this would trigger thread race checkers if stb_image
    was used in multiple threads. Just make the kernels be explicitly
    per-stbi__jpeg to avoid this.
    
    (This commit is the first step in replacing existing STBI_SIMD
    functionality.)

[33mcommit 518306517c4b5b0e7d7077781ac974828fb907a1[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Dec 14 01:23:42 2014 -0800

    stb_image: JPEG dequant in decode_block not IDCT.
    
    Inside decode_block, we're still sparse, and we can use that
    sparsity pattern without doing extra work to discover it.

[33mcommit 1d5652044d7b0ecb67b29339df35910d336aac3f[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Dec 14 01:08:47 2014 -0800

    stb_image: JPEG fast_ac table - decode entire AC at once.

[33mcommit a1bd1f7f1f08edfba0207a0e51ab8e45b15969eb[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sun Dec 14 00:38:17 2014 -0800

    stb_image: Faster stbi__extend_receive.

[33mcommit bdc918751d4ac4548dfa2e20270a8a4256044073[m
Merge: c37efd3 f547761
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Mon Dec 15 01:09:59 2014 -0600

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit f547761c1581d757b5151319c6b718de6d4f30e1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 14 18:14:14 2014 -0800

    Fix assert() that should be STBI_ASSERT()

[33mcommit 91255cb1cdfe6a11d411d9ae09d46aa2a3462d04[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 14 02:06:33 2014 -0800

    update stb_image version & changelog

[33mcommit f9e593c25c416148aed7bc88354602f964520c80[m
Merge: 8ac015c 1996a01
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 14 01:57:22 2014 -0800

    Merge branch 'optimize' of https://github.com/rygorous/stb into working
    
    Conflicts:
            stb_image.h
    
    Also disable VC6 automatic precompiled headers which were enabled in some projects.

[33mcommit 8ac015c03fc427eed8e9d5fed0a66620881d9f91[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 14 01:43:23 2014 -0800

    fix 1/2/4-bit png to filter bytes before decoding to pixels;
    rename pngsuite/part1 to pngsuite/primary;
    check in pngsuite

[33mcommit 01d2c9d957dbca3ca2899ebc0677cbfe62a73c99[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Dec 14 00:01:50 2014 -0800

    test program now verifies pngsuite tests against refererence versions

[33mcommit 8679ce08b78c96a74f0e0d7efb54b9abac24dda2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 13 23:35:55 2014 -0800

    fix incorrect img_n variable for interlaced files, caused files to be totally incorrect if forcing channel count

[33mcommit ff2d5473c59c20337b044842f3fdef34d2050bac[m
Merge: 0096551 1be86b3
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 13 23:05:49 2014 -0800

    Merge branch 'master' of https://github.com/ocornut/stb into working

[33mcommit 1996a019ac13abe20b1010a23c24502a3547b67d[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 19:15:38 2014 -0800

    stb_image: Guess decoded image size before zlib decode to avoid unnecessary reallocs.

[33mcommit 3d6dccf0c40d81f9d637f2b81d7f9274454bee44[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 18:48:37 2014 -0800

    stb_image: Make 'fast' table contain code size and value directly.

[33mcommit 007de5eb6e22f9a239d5fa25ed3e5a1cecf88d4a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 18:18:36 2014 -0800

    stb_image: Extract zhuffman_decode slow path into own function.

[33mcommit cdc230598e795cd53c5b976402901efe0de268e9[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 18:07:00 2014 -0800

    stb_image: Fast path for matches with dist=1 (runs) in stbi__parse_huffman_block.

[33mcommit 92b9e262b79dbc27e04487c57f0dfc6335bc993a[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 17:58:36 2014 -0800

    stb_image: Keep zout in a local var during stbi__parse_huffman_block.

[33mcommit 8188e842e26236bbf1f33ff20f5bd8c3d6f6e6be[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 17:31:51 2014 -0800

    stb_image: Add 'static' for some internal funcs, STBIDEF for external ones.

[33mcommit 61428d4526bccce3e268ac3b1aebce27397b2f42[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Sat Dec 13 17:22:57 2014 -0800

    stb_image: Trivial optimizations for filter path when img_n==out_n.

[33mcommit 00965512d703a5c068d115c1c96e581a0ec28614[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Dec 10 00:29:25 2014 -0800

    update version number

[33mcommit 26439254e81b8a27f84fca911820f4a8ca1f6a02[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Dec 10 00:27:11 2014 -0800

    fix use of stbrp_coord if no stb_rect_pack;
    fix a few assert()s that weren't STBTT_asserts();
    fix missing cast for C++
    fix typo in C++ test compilation that prevented it from trying to compile stb_truetype

[33mcommit 34eec7cc5ded4dfb01dcd126d14518fac4c02b1f[m
Merge: d1c85ea d9e121f
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Dec 8 20:00:18 2014 -0800

    Merge branch 'oversample_shift' of https://github.com/rygorous/stb

[33mcommit d1c85eac78c878109b366d6ef1d9c06a9fa8ad38[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Dec 8 19:58:51 2014 -0800

    update version numbers

[33mcommit 97037461d9dce859f0be5985d17203db96867844[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Dec 8 19:56:39 2014 -0800

    stb_truetype:
       STBTT_POINT_SIZE
       documentation for above
    
    stb_rect_pack:
       STBRP_ASSERT

[33mcommit d9e121f4c73e34ec1f9b7dd6dac19a11c1cd1ee1[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Mon Dec 8 19:53:12 2014 -0800

    stb_rect_pack: Fix implicit conversion warnings.

[33mcommit 82677e551820b74eb366ca60060d18acb3a12f69[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Mon Dec 8 19:51:39 2014 -0800

    stb_truetype: Fix implicit conversion warnings.

[33mcommit 27974c42f956886ec810e2b6130b1ccb11858b59[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Mon Dec 8 19:43:27 2014 -0800

    stb_truetype: Negative size = pixels for EM square.

[33mcommit ffbea74703c902a12390e10a869e605a4b3bebe6[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Mon Dec 8 19:39:49 2014 -0800

    stb_rect_pack.h: Impl must include assert.h

[33mcommit 5f674fc7e58206ba458b2c407d15dd76a813744d[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Mon Dec 8 19:20:41 2014 -0800

    stb_truetype: Cancel out phase offset from box filter correctly.

[33mcommit 8ac41a413d397a91056f97f6d50932b6b479888c[m
Author: nothings <sean2@nothings.org>
Date:   Mon Dec 8 11:42:47 2014 -0800

    fix typo

[33mcommit 3a5caacaaeb520184f7d8a2b392fc2589780c678[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:50:34 2014 -0800

    Update README.md

[33mcommit 49d5456de9b8771975456ec325db873d9ff73279[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:49:29 2014 -0800

    Update README.md

[33mcommit 916800aae5bcdb55226449d3a93f9889ec393d12[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:48:10 2014 -0800

    Update README.md

[33mcommit cd5b5a56848ba7e5258cb2c678f6a8707c08e4f3[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:46:40 2014 -0800

    Update README.md

[33mcommit b62bc08c340d2983c2daec6b4e97ade61c78d6d9[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:31:12 2014 -0800

    Update README.md

[33mcommit ae5bc8dfe9e881a073537debf8a9fe46b8d7b5df[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:30:46 2014 -0800

    Update README.md

[33mcommit 9b1e1c50c0027eb0c0574de471e9bfd415fc7206[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:28:28 2014 -0800

    Update README.md

[33mcommit 7d0cec62c887103d986db1f62daa7ceb3f5c23ae[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:28:04 2014 -0800

    Update README.md

[33mcommit 4b87ba76fe2dd24b4fcbfdee216f0da3d60b7c0c[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:22:14 2014 -0800

    Update README.md

[33mcommit 539dc3996bc9a8f575373067d77e03a83fc2b4e9[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:21:11 2014 -0800

    Update README.md

[33mcommit 19b24bba1a02d617443e7316c324c93b56cd042d[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:19:25 2014 -0800

    Update README.md

[33mcommit c6e1ec0cecf14a64d7047530bd41b8bd7b8c0d32[m
Author: nothings <sean2@nothings.org>
Date:   Sat Dec 6 23:17:44 2014 -0800

    Create README.md

[33mcommit 0a1d82f9e327e796792a5886448ed6e42746fad1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 6 23:02:10 2014 -0800

    readme

[33mcommit 22dbcffef714461ca29694bf71deeff38bf5522d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 6 23:00:59 2014 -0800

    stbtt_Pack* documentation
    oversample test tweaks

[33mcommit f03e35209306fe5348330ce968f9282df88cca1b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Dec 6 12:28:46 2014 -0800

    stb_rect_pack: fix LARGE_RECT bug
    stb_truetype: oversampling, including oversampling demo app

[33mcommit b6f8358f47a814055d04a4de09fdc336d94d5d3c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 2 03:00:08 2014 -0800

    various fixes for compilation test

[33mcommit 0a3dd5aff36e7265d1a439bed3dfc80c3f7e31b8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 2 02:59:44 2014 -0800

    new font bitmap baking API

[33mcommit 37c95d8d55f495b15a51dba2170b3a865e463110[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 2 02:59:05 2014 -0800

    add internal version number for use by stb_truetype

[33mcommit 5f81a92cdd432e7785026f26bb760338725e5c86[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Dec 2 02:58:08 2014 -0800

    use explicit float constants to avoid warnings in some compilers

[33mcommit c37efd3142e0c6bcf59db1a9bcc986c70299d140[m
Merge: ff4a8a0 ff22b6c
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sat Nov 29 15:21:02 2014 -0600

    Merge branch 'master' of https://github.com/kennethdmiller3/stb

[33mcommit ff4a8a00a91bd24ab91c3a9342e3576cc452132c[m
Merge: 66c312d 99198d0
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sat Nov 29 15:20:45 2014 -0600

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit ff22b6cb565fa1c27e0856cf106f2ebb5576002e[m
Merge: af98245 99198d0
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Thu Nov 27 22:11:54 2014 -0600

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit af982450f1390f625cbe429eb35c7ae920f1f992[m
Merge: 66c312d 2c56e11
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Thu Nov 27 22:11:17 2014 -0600

    Merge branch 'working' of https://github.com/nothings/stb

[33mcommit 99198d044f07a2160a25cbf5b309d1a17654ab38[m
Merge: 36ef8be e915158
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Nov 25 15:32:43 2014 -0800

    Merge branch 'working'

[33mcommit e9151589ca70ed88335534c5670d5c4d80e19e4f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Nov 25 15:06:27 2014 -0800

    duh, best-fit should tiebreak using waste, not prioritize waste (which makes bizarre towers)

[33mcommit 36ef8be0be7dbefa2f4dbdc3bab90a5d5fa649ae[m
Author: nothings <sean2@nothings.org>
Date:   Mon Nov 24 18:56:56 2014 -0800

    fix typo

[33mcommit ece0883f3c578459f00e803cdf4fef7fd282e80a[m
Merge: be3d9cd 2c56e11
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 18:22:14 2014 -0800

    Merge branch 'working'

[33mcommit 2c56e11c59c8373b81b0bb49562fe88cba088d4e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 18:21:36 2014 -0800

    doc tweaks

[33mcommit a9e1f96765d6cd335af26c14b379470f6d23c0e5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 18:20:13 2014 -0800

    rename 'stbrp_init_packer' to 'stbrp_init_target' since it must be called for every target;
    clean up docs

[33mcommit 8d3ef72e3ce083ae7471e29115af9d41852f77c8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 18:12:46 2014 -0800

    fixed bugs related to the best-fit heuristic

[33mcommit 0c10e7c40eab2af30b2b3964630a526e52cb2c4e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 17:47:06 2014 -0800

    tested & debugged on two cases (both heuristics); unknown if BF is *correct*.

[33mcommit b09f8186dcb7003774f07c99ab013fb6537bcf22[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Nov 24 16:06:46 2014 -0800

    non-working rectangle packer

[33mcommit 83c5588584a6ce56fceece3c4bf7a0e314f6bb0f[m
Author: Kristoffer Grönlund <krig@koru.se>
Date:   Mon Oct 27 10:02:27 2014 +0100

    Remove unused variables and ambiguous dangling else

[33mcommit f298f7dabeea1a86e92d67a824d212ec59da6951[m
Author: Kristoffer Grönlund <krig@koru.se>
Date:   Mon Oct 27 09:05:40 2014 +0100

    Ensure GCC that p is not used uninitialized

[33mcommit 3202fb6a55083b7b118d364565ff84c9d5773137[m
Author: Kristoffer Grönlund <krig@koru.se>
Date:   Mon Oct 27 09:03:31 2014 +0100

    Remove stb_readdir_size which was written (on windows) but never read

[33mcommit ce9b680784956d8b55649bd5e10dd9490305e465[m
Author: Kristoffer Grönlund <krig@koru.se>
Date:   Mon Oct 27 09:01:12 2014 +0100

    Add missing return type declaration

[33mcommit 3b1480ff10b6581dfe995ae1934a563b6ef95094[m
Author: Kristoffer Grönlund <krig@koru.se>
Date:   Mon Oct 27 08:56:56 2014 +0100

    Don't read uninitialized memory

[33mcommit 66c312dd9ea8cbe40e503704fc182869495cecc5[m
Merge: 55e153a be3d9cd
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Mon Oct 20 21:23:12 2014 -0500

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit be3d9cd9659e64f19c43072b54824e712d874fd8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Oct 20 08:57:14 2014 -0700

    added a few more FAQ questions

[33mcommit d97c160e4abff4dc073599a75da0044c6d19b5a6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Oct 19 21:18:07 2014 -0700

    tilemap editor 0.30

[33mcommit 2b5d5d9cf44b5853d41a2e05a61bb1f942f1386a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Oct 19 20:43:18 2014 -0700

    various updates

[33mcommit c6c767f7aad02a33b20a30d1ce1328cd26fdfb71[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Oct 18 18:21:34 2014 -0700

    properties and links

[33mcommit 55e153af7507c366c2716ec8cbdca364465136d7[m
Merge: a44cec8 c8705be
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Tue Oct 7 21:46:46 2014 -0500

    Merge branch 'master' of https://github.com/kennethdmiller3/stb

[33mcommit a44cec873a0df398fe950fe7c49aaaaff1488b50[m
Merge: 316beb9 283bc54
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Tue Oct 7 21:46:34 2014 -0500

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit c8705bef4e2998ebadba8754d11ff6d1a23f1b95[m
Merge: 2834d9d 283bc54
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sat Oct 4 22:27:06 2014 -0500

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 283bc54c900b4e5cf916587635b3b8db8486bec9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 27 13:43:27 2014 -0700

    update version number

[33mcommit b46b49d93577e2ac5d8ba85f8d71a1ac93a22422[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 27 13:42:50 2014 -0700

    colorpicker;
    new color scheme

[33mcommit 3ab22d37501611ec7f4617882bd0c8f903e4cda7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 26 23:23:55 2014 -0700

    fix bug in paste to protected layer;
    add eraser tool

[33mcommit 1be86b37d66b7675ad90bd81e22db417f6beef08[m
Author: ocornut <omarcornut@gmail.com>
Date:   Fri Sep 26 00:06:30 2014 +0100

    Documentation

[33mcommit 50d975261296fd7be2849f98defdc3f3f8f389c6[m
Author: ocornut <omarcornut@gmail.com>
Date:   Fri Sep 26 00:01:45 2014 +0100

    Removing tabs and using 3-spaces indents to match local coding style

[33mcommit 09a1ab87a0af969b99f325577520033667a83f1a[m
Author: ocornut <omarcornut@gmail.com>
Date:   Thu Sep 25 23:52:24 2014 +0100

    Fix for interlaced and small images + cleanup

[33mcommit 3b3e2996e7a1a2b312cb9b891e7db347c02e7a68[m
Author: ocornut <omarcornut@gmail.com>
Date:   Thu Sep 25 21:59:50 2014 +0100

    Unpack 1/2/4 bpp into 8 bpp scanline buffer + support grayscale 1/2/4 bpp

[33mcommit f2b3ebd47008d1c3675d85ca0b7a72eeb15fd392[m
Author: ocornut <omarcornut@gmail.com>
Date:   Thu Sep 25 19:30:47 2014 +0100

    Support for 1/2/4-bit palettized PNG

[33mcommit 2834d9da0856de3de104fc369ec7a24602f59c04[m
Merge: 316beb9 655d245
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Thu Sep 25 00:32:23 2014 -0500

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 655d24552afbd8897ac2a53142d9f8416d9ec74a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Sep 23 18:02:49 2014 -0700

    tiny bit of documentation

[33mcommit 17647014b32e68459874bab23a42b9a5ba9d9d91[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Sep 23 17:56:03 2014 -0700

    fix c++ compilation

[33mcommit 43fb9942deb11f7600d5d9d3495a7fd943ddba5a[m
Merge: 8252a94 891f6d7
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Sep 23 17:22:52 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 8252a94f02dbaeb96d9b8890294a5701abda2110[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Sep 23 17:19:25 2014 -0700

    add stb_tilemap_editor.h

[33mcommit 891f6d772070ee7ee49386c50952191072250044[m
Author: nothings <sean2@nothings.org>
Date:   Thu Sep 18 12:52:11 2014 -0700

    Removing bitpacking warning for srgb conversion

[33mcommit 941ace7f22148288988d4073e1ae0baa33b3b87c[m
Author: nothings <sean2@nothings.org>
Date:   Thu Sep 18 08:34:57 2014 -0700

    Delete stb_resample_ideas.txt

[33mcommit b49d5180cacb7bbcd44b197d33a6a17f3f80d45b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 18 07:14:33 2014 -0700

    version numbers

[33mcommit c32d5c40d285248eac3f9cfac00b12b4a1db07ef[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 18 07:13:57 2014 -0700

    update version number & contributors

[33mcommit 69d4c6738b681a75f50a8629ae9bd5c09f7bb334[m
Merge: 17e82a4 f36b711
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 18 07:10:43 2014 -0700

    Merge branch 'master' of http://github.com/rygorous/stb into working

[33mcommit 17e82a4080806d5b2aa6a3dbc98be3ac2e4fc483[m
Merge: 671f04b dea604b
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 18 07:10:18 2014 -0700

    Merge branch 'master' into working

[33mcommit f36b7116e265444c371abd70e5807ce29708f4eb[m
Author: Fabian Giesen <rygorous@gmail.com>
Date:   Wed Sep 17 22:54:16 2014 -0700

    Fix a few bugs with subpixel shifts, shift_y in particular.
    
    1. In the presence of nonzero shift_x / shift_y,
       stbtt_GetGlyphBitmapBoxSubpixel would return a nonzero-sized bounding
       box for empty glyphs (e.g. spaces). Since such glyphs don't have any
       outlines, the rasterizer wouldn't do anything, resulting in a 1x1-pixel
       image with uninitialized memory.
    2. GetGlyphBitmapBoxSubpixel added shift_y then flipped the y axis,
       whereas the rasterizer flipped the y axis then added shift_y.
       Consistently flip-then-add in both places. This also makes the pattern
       of floors/ceils in GetGlyphBitmapBoxSubpixel simpler.
    3. The rasterizer added shift_y after multiplying by the vertical
       oversampling factor, instead of before.
    
    Vertical shifts now work much better, in my tests anyway.

[33mcommit dea604b8966c278e3275161d5a99d7e851e6d523[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 17 07:11:56 2014 -0700

    add stb_image_resize

[33mcommit 37faf29f6957656fe27953fe4d3b7018ad6d97e8[m
Merge: 057f29f 7c0ae19
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 17 07:10:40 2014 -0700

    Merge branch 'resample'

[33mcommit 7c0ae19a42527e4011b6a59a03e7443f99d3f909[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 17 07:10:21 2014 -0700

    documentation, release data

[33mcommit 0fc13e997b5d34da16cb055b4cb18cd4ff527da7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 17 06:24:40 2014 -0700

    optimization attempts, no meaningful changes

[33mcommit 80246734611209bfd4334f079c01fc2b0e3f20ac[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 17 06:07:16 2014 -0700

    switch srgb convert to second ryg method, which is a bit faster (8% total speedup on upsampling test);
    remove extra table in slowpath

[33mcommit a12d3dedf02d2505a1138ec34c4931641e8caef6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 16 10:50:41 2014 -0700

    Some todo notes.

[33mcommit cbf5ebbd3591789cccd0be4c037e43c28e9af5ea[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 16 10:36:19 2014 -0700

    Install ryg's float -> uint8 sRGB conversion code, which is much faster.

[33mcommit 600d80387e47840f91f42787603575dd4d1978db[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Sep 15 14:01:11 2014 -0700

    Make a guess at the value before doing the binary search, cuts the number of conditionals by half. Not as much gain as I hoped but something.

[33mcommit 7602c99e779fd4bbed9e108d531308e9917427da[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Sep 15 11:29:40 2014 -0700

    Quick formatting fix.

[33mcommit dd28033b34dd94fd5209636497c0a34f03203991[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 15 07:23:22 2014 -0700

    don't encode alpha channel twice when alpha is different colorspace from other channels

[33mcommit bdbf1e0ef41565f6c1d4a1e865e807a0c45ded56[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 14 15:01:10 2014 -0700

    uint32 images need to round with uint32 cast, not int cast

[33mcommit 9f66b441bd7013c9ad8c87f3baad314432fffd93[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 14 14:55:23 2014 -0700

    new quickstart docs;
    reformat docs;
    new simple uint32 test

[33mcommit 3c261481a6d59e0dc4f14d432dc80a7c71b9cb76[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 13 14:33:13 2014 -0700

    Add a very quick guide.

[33mcommit f0ba7f5f7eebd279d29b639dceb775ac46a21810[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 13 13:42:50 2014 -0700

    Get rid of old perf tests.

[33mcommit a0d4f79074eef23f512f8481423cdadd6d524b02[m
Merge: 29b36b3 385d7a4
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Sat Sep 13 12:31:18 2014 -0700

    Merge pull request #7 from nothings/resample
    
    Resample

[33mcommit 385d7a417c70c1e17e0a37dbb6d72f4c05c34116[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 08:50:10 2014 -0700

    delete some unused functions;
    get rid of stbir__inline for some functions that don't need it

[33mcommit f711fdcb0f019fdaacc24c9315e5bffd115a9ed3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 08:22:15 2014 -0700

    disable performance test in test code, back to regression test path

[33mcommit 8849501a3f2251068921d338f999019312906cad[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 08:21:14 2014 -0700

    add documentation explaining why even a 64K table for srgb_to_uint8 would be inaccurate

[33mcommit 9a6af9a8d3fea77932563813cf37a7a193b95d5e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 08:12:37 2014 -0700

    replace int(floor()) with int(), since that produces same results for non-negative values and is much faster on 32-bit x86

[33mcommit 1dcca19ae0503fdf57f285028c5ec04beb272c6b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 08:06:39 2014 -0700

    because of we divide by /255 not /256, we lose numerical precision, so can't guarantee that box filter results round to same results as naive

[33mcommit adbbe8dabd14f32d2c7052f5a72bf8f04613c6d1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 07:46:09 2014 -0700

    move x loop inside switch in horizontal_downsample

[33mcommit 7a8c9196d1980c51f4618cfb79bc047ca22fc8db[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 07:41:39 2014 -0700

    unroll vertical_upsample inner loop, and reverse loop nesting to minimize work

[33mcommit 9c2ae9bdb865fac93dcb6a6ff3af91a479e7a2f3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 07:29:04 2014 -0700

    cache filter-width derived computations that use floor/ceil because those were showing up like crazy on VC6 profile despite only being per-scanline-ish?!?
    unroll inner loop in horizontal_resample

[33mcommit 972456cb6363aed88677bc7ddf68f633cb529cdf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 06:53:53 2014 -0700

    explicit performance tests variants

[33mcommit c9600c012f63310d6f19e06bc4404d08c4d601b1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 06:23:07 2014 -0700

    unroll channel loops in downsampler

[33mcommit 3ee97c221f8e433a129f13e9739a201b9cff9e51[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 06:12:40 2014 -0700

    compile as C

[33mcommit 59898db41159a10f11de2bd60c2d8e7ae99c0a0e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 06:05:00 2014 -0700

    tweak grammar

[33mcommit a2f1cadde87b58d348aca1caceae7dfe6e0e90e3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 06:03:48 2014 -0700

    convert tabs to spaces so it's consistent with other stb libs

[33mcommit 60064f980357b621e1f4988039ca066735eddd43[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 05:56:06 2014 -0700

    add stb_image_resize.h to readme

[33mcommit 0fa5b5c66f0d38956a0726c92b4efca23cf5c6fd[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 13 05:52:19 2014 -0700

    rename cubic to cubicbspline;
    tweak filter type documentation

[33mcommit 316beb987dd771256c1135740590c3cb91d8c0b4[m
Merge: 057f29f 8e91cb2
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sat Sep 13 00:38:04 2014 -0500

    Merge branch 'master' of https://github.com/kennethdmiller3/stb

[33mcommit 29b36b3dea91a3df743b54bbe196f98eeb4ec071[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 12 05:28:24 2014 -0700

    rename filters, document them

[33mcommit da2aa8f6b77006105af174b9911161ac059d5501[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 12 05:04:38 2014 -0700

    checkboard test to verify srgb

[33mcommit a9778b8dbd2313ec67bc41bdb1d8268d11c9f588[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 12 04:46:41 2014 -0700

    tweak docs; fix compile error in UNUSED_PARAM stuff

[33mcommit 99f3b78bbde03472b75d220d369e48cac0261433[m
Merge: df128b7 ca88b6f
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 12 03:54:17 2014 -0700

    Merge branch 'resample' of http://github.com/bsvino/stb into resample

[33mcommit df128b7995a3117a4b357b989eb325955d5e7a38[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Sep 12 03:53:36 2014 -0700

    update STBIR__UNUSED_PARAM to match stb_image.h version

[33mcommit ca88b6fba6845077eb801179d5a43712afceba0e[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Sep 11 12:45:18 2014 -0700

    Calculate and store vertical contributors first so that they can be normalized and optimized.

[33mcommit a25c1d2bbd278be422818ff3066043307f4658e3[m
Merge: 36b417f 27f26f8
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Sep 11 10:00:57 2014 -0700

    Merge remote-tracking branch 'remotes/nothings/resample' into resample

[33mcommit 36b417f6b4cd3da9abd3b66a1448b9dbccebd329[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Sep 11 09:39:03 2014 -0700

    Optimizations: Skip zero-coefficient contributions. Reduce the size of the coefficients array when downsampling.

[33mcommit 27f26f8337714c6d038554e40b3f31478b9c4054[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 11 03:02:20 2014 -0700

    Documentation;
    rename STBIR_FLAG_PREMULTIPLED_ALPHA to STBIR_FLAG_ALPHA_PREMULTIPLIED so that both flags have "ALPHA" first

[33mcommit 7a4f1f4665585ce3c8da1ba0320b9e77aaf3a24c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 11 02:10:37 2014 -0700

    update with new tests for srgb conversion

[33mcommit 16d68d14f81e79779b5239239f5ee5df9d0c7340[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 11 02:05:53 2014 -0700

    fix stbir__linear_to_srgb_uchar:
        1. table stored threshhold of transition from i to i+1, but wants to be i-1 to i
        2. table was computed by dividing uchar by 256.0 instead of 255.0, causing it to be 100% wrong

[33mcommit 30c7a981ec335c2267b3cec2955cde42376b8fd9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 11 01:47:50 2014 -0700

    compile as C;
    fix some unsigned/signed comparisons;
    avoid round() since it's not in pre-C99 C;
    remove MAX_CHANNELS since I never ended up needing it;
    rename STBIR_EPSILON to STBIR_ALPHA_EPSILON;
    don't use STBIR_ALPHA_EPSILON on float input (can't remove it properly due to numeric precision, and they can do it themselves);
    optimize subtraction of STBIR_ALPHA_EPSILON;
    sorry i forgot to commit these separately!;

[33mcommit 1208730e1efd658bb71c957efaa2ed9ec8d3157e[m
Merge: 4e580cf 46dc8f8
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Sep 11 01:15:09 2014 -0700

    Merge branch 'resample' of http://github.com/bsvino/stb into resample

[33mcommit 793818d1af46128c6b987a0c3bdb8424a00b2377[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Sep 10 20:26:14 2014 -0700

    Skip zero-coefficient contributors, a fairly decent speedup.

[33mcommit 46dc8f84fb2fbc2c95b4cd8aa73daf1c9297ac39[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Sep 10 20:12:38 2014 -0700

    Use vertical pixel width for the ring buffer.

[33mcommit 953a6378417da760544c7e4ca2bfdebaeffe3fcf[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Sep 10 19:08:11 2014 -0700

    Use a carefully shaped trapezoid instead of a box filter to avoid jumps between pixel values.

[33mcommit 671f04bd7e93dcdd91147bd33e19e476f5cc6247[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 10 15:35:06 2014 -0700

    debugging truetype crash

[33mcommit 4e580cf9edb2213635fb6dff9295c6975ca98d6e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Sep 10 15:11:35 2014 -0700

    fix compile

[33mcommit 69226281065025ded2a831907432af7139694f83[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Sep 10 15:03:55 2014 -0700

    Use an even smaller epsilon. Allow the user to avoid the epsilon business if they want to preserve their alpha values.

[33mcommit 057f29f813307c4eb4201c3cc4520bf7b8b486e8[m
Author: nothings <sean2@nothings.org>
Date:   Wed Sep 10 11:03:49 2014 -0700

    update version number

[33mcommit 87b7e3db41371af6149af4c288077fbafa68b063[m
Author: nothings <sean2@nothings.org>
Date:   Wed Sep 10 11:03:26 2014 -0700

    update version number

[33mcommit 5db8a8bc3619831d1d1335160a7f7005a430c6ab[m
Merge: 2572f31 40cc1c5
Author: nothings <sean2@nothings.org>
Date:   Wed Sep 10 11:02:04 2014 -0700

    Merge pull request #42 from rygorous/master
    
    stb_textedit: Add support for alternative keyboard shortcuts for text/line start/end.

[33mcommit 40cc1c59b2288317de766754d025faebe61064f5[m
Author: Fabian Giesen <fabiang@radgametools.com>
Date:   Wed Sep 10 10:54:22 2014 -0700

    Add support for alternative keyboard shortcuts for text/line start/end.

[33mcommit c9d67446d27742ca561a1c95fa1cddb6970604a6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 22:57:15 2014 -0700

    Reverse allocation routines parameter order so that the context is at the back.

[33mcommit 17b931047c908f8f9e7c96ec17aef2b5611f81c2[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 22:47:53 2014 -0700

    Add the epsilon value into the alpha instead of using an if statement. It's a tiny bit faster and it can be removed afterwards.

[33mcommit 1d5c902e2e486511a86916f13726b6963c832077[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 22:07:40 2014 -0700

    These minor optimizations were probably already done by the compiler but they can't hurt.

[33mcommit 41e6aad693d1e23dcb06a3a09dc82cf0897c2582[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 21:57:46 2014 -0700

    Avoid repeated adds and ensure correct round-trip result.

[33mcommit f2102d906fd749e85367afec1a6aa7b9486bf804[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 20:58:19 2014 -0700

    Use the info structure to keep track of our memory block sizes to reduce duplicated code and cut down on errors.

[33mcommit 969ff7c850d34869cdf5e789abfd8a17dbf8e206[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 20:51:29 2014 -0700

    Make sure calculate_memory matches with the allocations. Fix some errant asserts.

[33mcommit 8355ea1184dbbf24fb9fe845dad5afb814a1c673[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 18:41:28 2014 -0700

    Use height, not width, for correct progress report.

[33mcommit 4b69c0637eff6ed3741a9ed89ce3a4a4ee16af23[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 17:03:20 2014 -0700

    If alpha is zero then sneakily replace it with a very small nonzero so that the color data is preserved.
    
    Pre-process n1 so that we don't have to do it later on. Can't do n0 since it's used to find the coefficient index.

[33mcommit d510d70b6a156039f49dbb39d2e080ff28103309[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 16:35:00 2014 -0700

    Report downsample progress by when we empty the ring buffer, it's more accurate that way.

[33mcommit 084baed15ce302aac4bca4949f9533a259c1c54b[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 16:30:06 2014 -0700

    Replace premul test with better premul test that doesn't require visual inspection.

[33mcommit 497eab8339be92ab1762592ae9b388cd4be7e24d[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 15:22:29 2014 -0700

    Normalize downsample coefficients.

[33mcommit 43fbc1d5e36d001ce6ee093228e27c638d249275[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 14:10:14 2014 -0700

    Rearrange the algebra on two of the filters to avoid repeating decimals which cause precision loss. Use int32 to test filters because it's more accurate.

[33mcommit ca241daefaa9eace0053843bb28e0ae806837db1[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 12:16:23 2014 -0700

    Use rounding to try to preserve the original value. Fix test case.

[33mcommit 145690788c1c2b34af9a595d39203330a06abe8f[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Sep 9 10:58:01 2014 -0700

    Use input_h + pixel_margin * 2 to prevent progress report from ever going above 1. Always report a 0 before and a 1 at the end of each resize.

[33mcommit fb8eabd6b8e3fc672fac9df5c54f33c8c0d9a437[m
Author: baldurk <baldurk@baldurk.org>
Date:   Tue Sep 9 08:33:25 2014 +0100

    Add .hdr file writing support

[33mcommit 118f28557e7bf55de8dd58d026971260c2c43fc9[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Sep 7 16:47:02 2014 -0700

    Tests to ensure images of a solid color stay the same solid color after resampling.

[33mcommit e6c47ec657e81e72c387e10225f7e5770885c3e6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Sep 7 11:56:11 2014 -0700

    Fix kernel lookup for downsampling.

[33mcommit 8cc6a3abfcff77abd14fb64bad095b0d1a6682af[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Sep 7 10:02:51 2014 -0700

    If there's no context we're using the simple API functions - fall back to malloc and free.

[33mcommit 36db03f3902943fdb27fa54f930baf6ad642426d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 7 05:31:40 2014 -0700

    tighten bounds on filter normalization test

[33mcommit 7f8ac35e4224a7209eae1cd466236093bcf3c019[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 7 05:29:43 2014 -0700

    check whether filter kernels are normalized

[33mcommit 7da729bfce662e9c8a69beb2a5024a33a0af694f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 7 04:07:07 2014 -0700

    restore correct definition of box

[33mcommit 08ca345839b4012a3cd1f5e4be0481be75e4fd2d[m
Merge: cd1fbac 586e840
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 7 03:36:16 2014 -0700

    Merge branch 'resample2' into resample

[33mcommit cd1fbacbb60fa97215e165fc1ac14f1b99b1b1a6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Sep 7 03:19:18 2014 -0700

    rename NEAREST to BOX
    write test for BOX

[33mcommit 8e91cb2b7df2ab3ee6f2be97fbde1433e2c6ac0c[m
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sun Sep 7 00:48:48 2014 -0500

    treat vertical tab and form feed characters as whitespace

[33mcommit e003c66498c7929032d185448fd92719abc1792c[m
Author: Ken Miller <kennethdmiller3@gmail.com>
Date:   Sun Sep 7 00:38:18 2014 -0500

    support PGM and PPM formats

[33mcommit 586e84087c54a3eb48ef0fc593bc71019329bc06[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 6 21:50:28 2014 -0700

    Correctly specify alpha channels.

[33mcommit 38ce5494bc895ee75b07da918cd73358a4db96d3[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 6 20:17:19 2014 -0700

    Clarify some comments. Make stbir__resize_arbitrary an internal function. Update test cases to use actual API functions.

[33mcommit 41555b5d53a72fa076aefe525f87de72fe9f981a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Sep 6 14:58:32 2014 -0700

    update test cases to work on things other than barbara.png

[33mcommit fb059fcece709d67c1fe910b04da5fda92a64dca[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 6 10:57:21 2014 -0700

    Progress report.

[33mcommit 75bdd2da83f30bf95f71d8ba6f1d65a4bd5ca980[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Sep 6 08:48:46 2014 -0700

    Fix malloc context and whitespace.

[33mcommit ce7aed0fb7796654da7e815e78aef23ab0468cff[m
Merge: b75eff3 952c26e
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Fri Sep 5 16:52:49 2014 -0700

    Merge pull request #3 from nothings/resample
    
    Resample

[33mcommit 2572f3177ab0c7b89fb5900fb225159c8b6105a0[m
Merge: 067a1d1 a5f1cb5
Author: nothings <sean2@nothings.org>
Date:   Fri Sep 5 09:14:53 2014 -0700

    Merge pull request #38 from lgvz/comments
    
    Fix comments that got search-and-replaced incorrectly

[33mcommit a5f1cb5657b8d0ed7d002a46c003a1c1a1510583[m
Author: Tero Hänninen <nomail@invalid>
Date:   Fri Sep 5 18:38:39 2014 +0300

    Fix comments

[33mcommit 952c26e626144aef43ae052503fcd1c5d979230c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 1 19:29:28 2014 -0700

    inline stbir__encode_pixel into stbir__encode_scanline

[33mcommit aee30095c717eae57b9d559538062d8451a4dd0b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Sep 1 16:52:04 2014 -0700

    refactor internal interfaces to avoid passing things multiple times;
    finish prepping 'stbir__info' even before calculate_memory;
    get rid of 'noinfo' functions since now calculate_memory doesn't need 'em;
    add new binary-searched sRGB function (untested)

[33mcommit 24c540e1b0bddcfe0753640df365b8a1a564491a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 10:00:54 2014 -0700

    rename alpha gamma flag

[33mcommit 07c35180f79380c8341d91755242456c7f146e7b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 09:45:29 2014 -0700

    tweak new API

[33mcommit 84520de6c47b13b9faa8e4f6b566375d36f22954[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 09:32:17 2014 -0700

    finish STBI_EDGE_ZERO, untested

[33mcommit 9a1d34843e524b80fad39d50267b07b064415e23[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 09:10:49 2014 -0700

    STBIR_EDGE_ZERO

[33mcommit 732fec68ee8e4e85251a37f2881d9bae0c003ac1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 08:55:41 2014 -0700

    tweak new API, get it partly working

[33mcommit 664d8961f54d490f877d996495150bd2fba4fc06[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 08:34:05 2014 -0700

    new API partially in-use

[33mcommit bbd4e2ee9ac48d51fec23141b268d076059011b7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 07:32:10 2014 -0700

    new API "finished" but untested

[33mcommit 2549d8156e8e38977dbbe4f8ac06db5327d72ad9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 07:23:34 2014 -0700

    in-progress refactoring

[33mcommit 034674c1425ea24cf0644de85c81752c1b93416f[m
Merge: c1b8767 1bd9770
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 07:23:22 2014 -0700

    Merge branch 'resample2' into resample
    
    Conflicts:
            stb_image_resize.h

[33mcommit 1bd9770e75e666155d9759e27db7a3ad25bfb8c2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 06:47:45 2014 -0700

    separate filter for horizontal and vertical

[33mcommit c1b876768e27990357da2bb0965eb2c4c903984f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 31 06:31:50 2014 -0700

    in progress new API

[33mcommit 067a1d1be15c5a43458d5196c91a65f48826ccb1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Aug 27 22:01:50 2014 -0700

    update readme version #s

[33mcommit b8e0530fdfbe6f9b820811942f7c6c46b31c0fdb[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Aug 27 22:01:37 2014 -0700

    update contributor list & version number

[33mcommit 33d621ca48e5fc1b3b2e1e4182f34c002c16b732[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Aug 27 22:00:07 2014 -0700

    tweaks to const-correct API change

[33mcommit 93c02695e309b3137683403fd86958ca4f71d87e[m
Author: Alejandro Pereda <atk1005@gmail.com>
Date:   Thu Aug 28 06:53:13 2014 +0800

    Const in decode/open memory.
    
    "const" added in stb_vorbis_decode_memory and stb_vorbis_open_memory to
    allow to read from const buffers.

[33mcommit 6bb8eb36957a3adb29dfcdc91e166007323e5650[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Aug 26 13:41:04 2014 -0700

    update version number

[33mcommit 578b4e18b4969e77800dea80c1e68667afa46907[m
Merge: a14339a 9b6c354
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Aug 26 13:40:54 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit a14339a01960c0028a5a3df6d1f27545d22e4aed[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Aug 26 13:39:53 2014 -0700

    fix handling of tRNS chunk in PNG (used wrong variable for output channels)

[33mcommit b75eff36f8ae03dff8cfbd03e07da59988813fa2[m
Merge: fc09a5d 5dfa79f
Author: Jorge Rodriguez <bs.vino@gmail.com>
Date:   Mon Aug 18 11:29:19 2014 -0700

    Merge pull request #1 from nothings/resample
    
    stb_resample updates

[33mcommit 5dfa79fb31bd35509679333047f88c069742d6a5[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 10:18:59 2014 -0700

    stride doesn't have to be multiples of pixels

[33mcommit 32b626859db82681d23106bab602d516d84b4d71[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 10:02:00 2014 -0700

    remove most per-pixel switches, beginnings of removing encode_pixel switch

[33mcommit 5eb0236d9de248cbbf2f7dafacbb5b87ee4bd807[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 09:33:01 2014 -0700

    reverse default behavior of linear/gamma for alpha

[33mcommit b9bb05b81cc826836a7118701d4118d6bf4e5866[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 09:14:11 2014 -0700

    minor cleanups

[33mcommit 6ef563d08950fc9b405ee85b7c4f5aec64b82926[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 09:12:59 2014 -0700

    rename to stb_image_resize.h

[33mcommit eb0781fda0bc31c5397a8a4fff3ce45fa4a8aef2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 09:01:33 2014 -0700

    add comments describing the purpose of the s,t-rectangle tests

[33mcommit 9ba3dc1fc5609df72e990cb832e22c15a1a2a202[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 18 08:56:44 2014 -0700

    make resample tests work in VC6

[33mcommit 9b6c354fe61c4535776c2c61a1f37248838ecb6e[m
Author: nothings <sean2@nothings.org>
Date:   Sun Aug 17 21:16:18 2014 -0700

    Update stb_howto.txt

[33mcommit 492e3f3463a2183496282a0e442405c6aae5b0c3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 17 21:12:16 2014 -0700

    update version numbers

[33mcommit 14e8b66119a17ecb126368ee9efb02e4dead63ce[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 17 21:08:43 2014 -0700

    fix broken map generation

[33mcommit 45469cfa275f41c118e0da1d12f7a2cac371d282[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Aug 17 16:47:55 2014 -0700

    fix warnings

[33mcommit 7e079c670d5d097c6d9418da197deeef6fcbe070[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 16 13:52:47 2014 -0700

    tweak TGA monochrome support

[33mcommit caf6d08f2b7781278da92d113934253d85a80b2f[m
Merge: b36f990 ebc2d23
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 16 13:50:16 2014 -0700

    Merge branch 'master' of https://github.com/Skylark13/stb into working

[33mcommit b36f9908ce5235364311b40175afe2a097f3f06c[m
Merge: aaea13b 10def9b
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Aug 16 13:45:32 2014 -0700

    Merge branch 'master' of https://github.com/thedmd/stb into working
    
    Conflicts:
            stb_image.h

[33mcommit fc09a5d1984aab9c509667e5e164fbf39c56b383[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 14:15:05 2014 -0700

    Don't saturate floats.

[33mcommit c9caec11239717787151f642a96faad4bdcba90e[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 13:50:17 2014 -0700

    Refactoring to reduce duplicated code.

[33mcommit 1353909477a9c824be4c8c47976bc94ad007dc7d[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 13:37:06 2014 -0700

    Allow user to force the alpha channel to be handled as a linear value even if the color channels are sRGB.

[33mcommit bbc340d4816b3091494050d23e6ba895745308ce[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 12:22:38 2014 -0700

    Support different edge behavior on vertical and horizontal axis.

[33mcommit 6ae729d61ad819e46535ba5626502d271553194c[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 12:15:12 2014 -0700

    Four new tests of subpixel stuff.

[33mcommit 419a5ba10fc8a9bb34cb911fd2289b1b1c1c33a6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Aug 12 11:55:27 2014 -0700

    Fix stbr__type_size for updated stbr_type

[33mcommit 45fa6ec900031eb29dddf8c7253008bc244acafb[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Aug 11 12:37:10 2014 -0700

    Update test cases for premul channel -1 meaning don't do any premul handling, fix another no-more-advanced.

[33mcommit e75ed1d38161f6d67a5aaf44e2eb5bebcc705f18[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Aug 11 12:21:55 2014 -0700

    Update test cases for no more advanced API.

[33mcommit 6ade66182c68a17bc83dcc2a3b348be309c6d516[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:34:50 2014 -0700

    allow alpha channel to be channel #0

[33mcommit f502cae91a1a49debe567fa4ad5ca0034b8fd7fe[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:32:07 2014 -0700

    rename everything to do with premultiplied alpha since the whole
    point is that this is for handling *non*-premultiplied alpha (since
    correct handling of premultiplied alpha requires doing nothing)

[33mcommit 42556fec82f03f9061dc574e7ab542c28d22486e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:26:17 2014 -0700

    don't require manual synchronization of STBR_MAX_COLORSPACES/MAX_TYPES

[33mcommit 392585130c509182059bffab95494510a0ff266c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:23:39 2014 -0700

    Get rid of "advanced" API with explicit temp memory because the STBR_MALLOC interface is sufficient

[33mcommit 259c92b550d780bfd382ddb7ed00877da3719d4c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:17:40 2014 -0700

    replace "texel" with "pixel" in identifiers

[33mcommit fc4ca11a52d8a65187f88cece15a69bdfdbfe0e1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:16:23 2014 -0700

    Fix places in previous commits where tabs got replaced with spaces

[33mcommit 25fae8c67c9b9a9b2f181b0433b7cb35fddf3019[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 02:13:26 2014 -0700

    Avoid divides in encode_scanline if not doing unpremultiply.
    Rename stb__encode_scanline to stb__encode_pixel

[33mcommit a0537bfd04a04def4d49da1652a7dcbcdfdb10c0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 01:56:47 2014 -0700

    Allow compiling as C pre-C99 (don't rely on declare-anywhere)

[33mcommit 3077bf5023de69d74c738e04172153db86850b10[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 01:50:16 2014 -0700

    wrap long data lines

[33mcommit 94ecd81abe2da71e734eca5d252df9e6737b3642[m
Merge: aaea13b e05ebdb
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Aug 11 01:47:12 2014 -0700

    Merge branch 'master' of http://github.com/BSVino/stb into resample

[33mcommit ebc2d23d474f63579803e5598864329a935aecd1[m
Author: Jean-S�bastien Guay <jean-sebastien.guay@cm-labs.com>
Date:   Sat Aug 9 09:16:57 2014 -0400

    realized the 2 colorbytes case is impossible.
    also updated the comment at the top of the file to reflect stbi_write_tga's new capabilities.

[33mcommit 26a71f67feefd19f2a8622d54207c3e6a2e21176[m
Author: Jean-S�bastien Guay <jean-sebastien.guay@cm-labs.com>
Date:   Sat Aug 9 01:08:43 2014 -0400

    comment was wrong way around... code was right.

[33mcommit b8b364c301625401cd64eeb2cb0ed74cc89754ce[m
Author: Jean-S�bastien Guay <jean-sebastien.guay@cm-labs.com>
Date:   Sat Aug 9 00:34:49 2014 -0400

    stbi_write_tga can now write 1 and 2 channel (grayscale and grayscale-alpha) images.

[33mcommit 10def9b15019e117d6f8015b04d653ca8420b94e[m
Author: Michał Cichoń <michcic@gmail.com>
Date:   Fri Aug 8 00:46:45 2014 +0200

    fix MSVC-ARM internal compiler error by wrapping malloc
    
    For some reason Microsoft CL compiler for ARM is unable to compile malloc when parameter is an expression. malloc(x * y) will cause internal compiler error, malloc(x) is however fine.

[33mcommit aaea13b71c7c810893f4c8d2396ceb48413eaed3[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:46:29 2014 -0700

    version numbers

[33mcommit c8a3522a5fe64f863363eee8a7fafd25d569b8aa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:46:13 2014 -0700

    version number

[33mcommit 29f59c0460a4cbf2f53187793d8e8e2b21788452[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:44:17 2014 -0700

    update version number

[33mcommit d26beed67dd2cd133805ffa7637e08d7912acb08[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:41:02 2014 -0700

    comments/ version update for platformID = Unicode

[33mcommit 0adfac0abea6ca4b5bf747c6b88abbf0420d840b[m
Merge: 85c39da 8c83fc2
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:35:51 2014 -0700

    Merge branch 'master' of https://github.com/HouQiming/stb into working

[33mcommit 85c39da6250634b154b5c6fd60834a2a1a522dc9[m
Merge: 2119c17 c28e92e
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:25:12 2014 -0700

    Merge branch 'rc/const' of https://github.com/ronnychevalier/stb into working

[33mcommit 2119c17ae956ad239c8fd0b1ef7ca357ac7af78f[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Thu Jul 17 14:53:42 2014 +0200

    stb_vorbis: fix unused variables
    
    Conflicts:
            stb_vorbis.c

[33mcommit 260741ed3343adb45ba234b92b49073b35c5a321[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Aug 7 04:20:58 2014 -0700

    vorbis warnings from ronny chevalier
    
    I manually made these changes because they
    disabled some substantial amounts of code,
    and I wanted to make sure this wasn't due to
    original code having bugs or deviating from
    the specification

[33mcommit 758c165d2c7f462a62d88cd86f471b9433f96947[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Thu Jul 17 14:49:48 2014 +0200

    stb_vorbis: fix unused functions

[33mcommit b8b6e7c31a0a8826108124a5ec1ef0664199a16c[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Thu Jul 17 14:44:11 2014 +0200

    stb_image: fix unused parameter

[33mcommit 422e29017c00a74cd74970c4d0c326bb1c102250[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Thu Jul 17 14:43:29 2014 +0200

    stb_vorbis: fix signed/unsigned comparison

[33mcommit 893ef013b27bbc3706ab02074de40eb1c2c0b73e[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Thu Jul 17 14:43:08 2014 +0200

    stb_image: fix undefined preprocessor definition

[33mcommit c28e92e856782bd2e40db7de9c32347ccd65397e[m
Author: Ronny Chevalier <chevalier.ronny@gmail.com>
Date:   Sun Aug 3 23:43:54 2014 +0200

    stb_vorbis: use const char* when appropriate

[33mcommit e05ebdbf1ef1153cfd73ba290f0498a5be4016c0[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 19:37:42 2014 -0700

    My guess is people who care about premultiply also care about color space.

[33mcommit d75488b0e88137ea969c29aa74c2860dbb402950[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 19:00:48 2014 -0700

    Do the multiply inline, it should be a tad faster and not corrupt our data.

[33mcommit 13acfca8298989ef23b08224fdc11080461bd3f8[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 18:46:00 2014 -0700

    I had the whole premultiply thing backwards.

[33mcommit 21c7c8f5d909ad09e85b1cee545872764fd813d9[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 18:04:57 2014 -0700

    Another stab at the api, offering classes of functions for different common tasks.

[33mcommit 8063ea0952a495cce33bb14a8198cb738a953a01[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 17:20:00 2014 -0700

    Specify a channel as having premultiplied alpha and use it to un-premultiply all other channels before resampling.

[33mcommit a32fa8b4dfd90b86bcd53d463a6e16757cbfa4a1[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 16:36:09 2014 -0700

    This to-do item done.

[33mcommit daf325dc0303783750b98d7bf68053df9864ffe4[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 16:31:45 2014 -0700

    Sub pixel source area test cases. No problems.

[33mcommit aae1c7ca414b17c0bb4b7feff678c462a57606e0[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 15:16:36 2014 -0700

    ZOOM AND ENHANCE!

[33mcommit 1b2d104e0077f58e5d191a9ff98a5aa64a03f4f4[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 00:52:03 2014 -0700

    Some error conditions.

[33mcommit 35cb95b8031442979a34203ba371a2328f6367f6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 31 00:39:33 2014 -0700

    Allow for specifying a sub-region of the source image to use. Downsampling only, currently.

[33mcommit 52ac93225abe1855dbe05f5fb228a9ffc5dd5b8f[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 17:33:47 2014 -0700

    C<99 ports

[33mcommit fdc979e48b67369204a23230f4b0881c7e3a460c[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 17:30:25 2014 -0700

    Some minor ports for Linux. No idea how it worked at all in Windows with STB_RESIZE_IMPLEMENTATION instead of STB_RESAMPLE_IMPLEMENTATION.

[33mcommit c5de2f32981ca05876f2d2d09aa82a2ee881ac01[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 09:41:41 2014 -0700

    Test channels.

[33mcommit 985ac752510db2871edd5ab81afac42a02c13e68[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 09:27:42 2014 -0700

    When doing a perfect po2 nearest neighbor downsample don't allow -0.5 and 0.5 to both contribute to a texel or you'll get a double tap.

[33mcommit c2449acc3eb1e1ada60933c4b8f9fba77ecc27d6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 09:14:38 2014 -0700

    Tests for edge behavior

[33mcommit 59cb71ea182a37453f781eb2aff99c6faf63e4cd[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 08:47:55 2014 -0700

    Fix float conversion.

[33mcommit 6625259959e99299562b826a4276d7a2ce3fb2c8[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 01:18:23 2014 -0700

    Try to keep integer precision by briefly casting to double while decoding and encoding.

[33mcommit 11897fbf9698ad0c992a401f161b0f08bd967790[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 00:34:25 2014 -0700

    More fixing shorts.

[33mcommit 1fcbe0daaf0bc54d22910d7efe01320bcc8421fa[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 30 00:16:13 2014 -0700

    Fix shorts. Add test cases for shorts.

[33mcommit 7ead9a748d46057ad6ad8236aeab224f64a57de7[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 23:09:41 2014 -0700

    Fix. Ring buffers are a height value.

[33mcommit 043fa28c111b9bf2bc7799193e5a879c121b5aff[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 23:02:56 2014 -0700

    Same deal with height.

[33mcommit ebe0473d8be0088faa8d22cc18d9b0f105abc54a[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 22:50:06 2014 -0700

    Add a test suite to do a bunch of different resizes to find problems. One problem found was an incorrect calculation of texel support how many margin texels needed when downsampling. When downsampling we need to spread out the support of each contributing texel, so to compensate you need more margin texels.

[33mcommit 68f93b72d5de533b2a873f3b586521a02d0fdc2f[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 20:18:28 2014 -0700

    Update documentation and add helper functions.

[33mcommit 5b4090627162d4a57778fa09840b8de782369eed[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 17:44:45 2014 -0700

    My perf testing code.

[33mcommit d96c97298cbc25a4e113c718eb0eb69706178f5d[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 16:22:22 2014 -0700

    This is still faster than the function pointer solution, and neater.

[33mcommit 3a3e06029e4836d86ea7e5e7b7e5da413a78a843[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 12:11:03 2014 -0700

    This is definitely faster than the function pointer solution.

[33mcommit 9bd5abb52dc2e8ae79d4d6debaf4676d8605d2d2[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 11:44:32 2014 -0700

    Both versions run within the margin of error on my machine so we'll go with the simpler one.

[33mcommit 5dff80ed313028d61d84393dfb3c87e11b0fc61c[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 11:39:42 2014 -0700

    Trying some different strategies for optimizing the decoder. The code in #ifdef 1 is slightly faster by my measurements, but a whole lot uglier.

[33mcommit 05f775e97746b33638c1a7f536807e0a3dca6702[m
Merge: 1fcf30a e2ac4f6
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 00:33:54 2014 -0700

    Merge branch 'master' of https://github.com/BSVino/stb

[33mcommit 1fcf30ada021e5bbd7f1ed7deff39dbfb91895f5[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Tue Jul 29 00:33:29 2014 -0700

    Fix a math error.

[33mcommit e2ac4f65050143777476893a0e21bb4aad4b9bdb[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Jul 27 12:05:17 2014 -0700

    More resample ideas

[33mcommit ef3a460ec41af11278c1a4bd6021f610e8423e59[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Jul 27 00:55:47 2014 -0700

    Some better looking horners save another multiplication.

[33mcommit 7d475825785703ca81264d0ac5662a46940589fd[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sun Jul 27 00:09:22 2014 -0700

    Support for 16 and 32 bit integer images, and float images.

[33mcommit 6c8cac0a66f2fa9d489c325ec4f26736ede54747[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 23:44:45 2014 -0700

    Support for sRGB color space.

[33mcommit 41dc4c476ccbb3b896ffa59d128b8f518e3a550d[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 22:49:56 2014 -0700

    In some situations with certain filter kernels with negative values it's possible to generate valid results > 1.0, so saturate it before we write it to make sure it doesn't overflow. Also fix incorrect filter radius while downsampling.

[33mcommit af1ed58f513a4d5bfbad9cf1e8807ad8999264a0[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 19:30:13 2014 -0700

    Add wrap, fix reflect so it doesn't wrap.

[33mcommit 87235674394d5ba57e36dddf977434a57a531f71[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 19:11:02 2014 -0700

    Add edge reflect mode.

[33mcommit 6cd81d4dd5032d046b007a9d7124cbb9c98549ff[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 15:36:15 2014 -0700

    Put the polynomials in horner form to save a multiplication.

[33mcommit fb2f8df5cce0580b08da784c94420f55a33b0836[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 15:06:31 2014 -0700

    Add mitchell filter.

[33mcommit 69af963c4201ca477c0d48fca13806ccb06f34de[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 14:52:28 2014 -0700

    Add catmull rom filter. Also, move the debug asserts for values <= 1 to the very end of the process. This will make these bugs a lot harder to find, but because some filter kernels have negative values it's possible for the buffers to have values > 1 up until the point where it's converted back to an int.

[33mcommit 12acf87eec18380dfa4d5cc37bf1e56a621746f7[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 13:56:23 2014 -0700

    When downsampling start the buffer loop at -filter_texel_margin to make sure that all contributors get their taps in at the ring buffer.

[33mcommit 155c71fb90a0868fed1f6a49863a8d5f5e1d0d88[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 13:12:48 2014 -0700

    Reorder these loops because I think we get a cache win if we write the entire ring buffer entry at once.

[33mcommit 01fb58d6b447d2714f015e9adc09658152a2c2a7[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 13:07:04 2014 -0700

    Add a bicubic filter.

[33mcommit a95da9ee1d76702d0e5f43f24339b964937a30e9[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 12:04:39 2014 -0700

    Unroll the multiply-add loops. At the cost of a function pointer dereference we get a whole lot of conditionals eliminated. Should be a solid win once the debug asserts are gone.

[33mcommit 7abd4ccf3445fab20df58f6ca79f22d9f4e49cc9[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Sat Jul 26 11:51:02 2014 -0700

    Support for filters with larger support. Initial support for edge behavior.

[33mcommit 62ff271c7a66a64ee41e28ee7c46a65f416b40a1[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Fri Jul 25 00:08:23 2014 -0700

    I put it in the to do list and now I can close my browser tab.

[33mcommit 81c1ddf110efb97f58b58193caa235af164ffe15[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Fri Jul 25 00:00:40 2014 -0700

    Keeping a list of suggestions so I don't forget them.

[33mcommit 27926e78b808f98565eae2346dbe280cba797c6b[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 23:50:14 2014 -0700

    Make consistent tests for whether we're doing upsampling or downsampling of width and height. Don't request memory for horizontal buffer or encode buffer if we don't need it.

[33mcommit 666c025710c85ebada2762913169409a5ebefb0d[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 23:32:25 2014 -0700

    Fix non uniform scaling where out_w < in_w && out_h > in_h.

[33mcommit 736596ba093a81912e75d82eab3124a7af479579[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 23:27:29 2014 -0700

    Fix non uniform scaling where out_w > in_w && out_h < in_h.

[33mcommit 178e301ea4a5546825dc3d431e5f6ed20f0fa389[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 22:54:35 2014 -0700

    Fix upsampling, avoid dereferencing in an inner loop.

[33mcommit dbb7480f12a96cf480e59fe0be4778e63c936739[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 22:30:35 2014 -0700

    Fix nonuniform downsampling.

[33mcommit fa69bc8551a837e59098600493b2d2da9784cfef[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 22:09:08 2014 -0700

    Basic downsampling algorithm works for uniform sampling.

[33mcommit 297266b27bb5a4efbce6e5ad34e2c1bbab216d86[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 19:10:45 2014 -0700

    Starting to implement downsampling.

[33mcommit 7d8faf5727e4e70cccf5cbf0e783717d02db6328[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 15:02:54 2014 -0700

    Remove unused functions.

[33mcommit 8ac052ac8a8a9ac0dfbdabe77055509ba15fe20a[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 15:02:39 2014 -0700

    Avoid gaps between box filter kernels.

[33mcommit 9e726bb3e43b21d8b4b3a6412fd62490367401e6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 14:20:18 2014 -0700

    The vertical resampling pass. Now all elements of the upscale algorithm are in place.

[33mcommit 152965f3342d51973711e3cace0143640d712c13[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Thu Jul 24 00:47:00 2014 -0700

    Decode enough scanlines into a ring buffer to make sure that we have enough source scanlines to do a vertical sampling.

[33mcommit 158effb62ace68efc9223713c7e9d07e70363b95[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 23 23:08:06 2014 -0700

    More accurate names. Smaller size for contributors memory, more accurate to what's needed.

[33mcommit 855fb207be01ab04add15b01a7d61a16a2d979c3[m
Merge: 55c5f0b ee8e926
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 23 22:24:59 2014 -0700

    Merge remote-tracking branch 'remotes/nothings/master'

[33mcommit 55c5f0b3a0004a6591888e60a53cb92e53b6e18f[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Wed Jul 23 22:17:56 2014 -0700

    Beginning of a more sophisticated resample algorithm, starting with calculating filter contributions per scan line.

[33mcommit ee8e926317c034def978c6738d0c1145577f0ba4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 12:45:24 2014 -0700

    even more resampling notes

[33mcommit 92b08aa98aaadb3639030d3966bf1174aee27c8f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 12:39:29 2014 -0700

    more resampling notes

[33mcommit 6f779fb67a34c3dac69c624b547c57a8b941f0fe[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 12:17:43 2014 -0700

    whoops imageresampler link

[33mcommit 9c9a68787d1d2bfa2f216f80f0b22c32439f46e1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 12:16:11 2014 -0700

    imageresampler library reference

[33mcommit 3e8a89cad1186e074783259fbdd5d6d14e6e0832[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 11:57:46 2014 -0700

    more resampler notes

[33mcommit c27ccec43656e43965fb58e4a0ec78fe02ff2be8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 11:37:54 2014 -0700

    resampler prototypes

[33mcommit 63cce5c70aae03dc5114714a0be99499554201fa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 22 10:05:01 2014 -0700

    created stb_resample_ideas.txt

[33mcommit 0155bd3ab6e1bfadd05ae5477e0489a8f5147eec[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Jul 21 19:51:11 2014 -0700

    We are going to support SRGB.

[33mcommit ba861fa493de9a70746a8f5fbd3cab995058f1b8[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Jul 21 18:01:05 2014 -0700

    Allow specifying a stride.

[33mcommit 06b7b00696ad5ad20c8f672d5f1122a083ab7340[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Jul 21 16:14:32 2014 -0700

    It does nothing now but I want to support edge behavior in the future.

[33mcommit c27c5b6fbe4ecee488ae675ab1588342e341b5c6[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Jul 21 15:36:43 2014 -0700

    There's really no point in returning the output buffer.

[33mcommit d54e74092ed5c2d43d161b5bda88b9b4784b624e[m
Author: Jorge Rodriguez <jorge@lunarworkshop.com>
Date:   Mon Jul 21 00:16:03 2014 -0700

    stb_resample initial implementation

[33mcommit bcefca10f7e14096fa87513cc21e235c84d30452[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jul 15 22:26:01 2014 -0700

    fix bad fix in previous fix

[33mcommit 75b9e9cc1b5fa67b543fe01be4f6a7e7f1e13b24[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:45:58 2014 -0700

    update stb_image version number

[33mcommit b2cbed263492088a5ec3b71c6c33a36483873afd[m
Merge: 1eb6659 e0d86b0
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:44:48 2014 -0700

    Merge branch 'working'

[33mcommit 1eb665906ed76274c2ecc2f994aa6424f5759393[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:41:40 2014 -0700

    cdecl fixes

[33mcommit 68b5ec9392cd38b9ec5796965d0b442e4407e3a0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:39:00 2014 -0700

    fix cdecl

[33mcommit e0d86b0f5c229d0ee87cf6842078b8eca2ea4980[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:35:25 2014 -0700

    STBI_ASSERT

[33mcommit 3bf91543f4060602fee698b44c448fa87df8161b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:26:03 2014 -0700

    revert img_n=0 initialization to original location

[33mcommit a2b9aa8d06c6a59e59b489f61c882703c08ab657[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:23:48 2014 -0700

    modifiy jpeg img_n fix
    switch from fopen to fopen_s on later MSVCs

[33mcommit 70de0adb2871f5e9d45084380a7faa4c7a9805bb[m
Merge: 932d485 efd6b26
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:03:32 2014 -0700

    Merge branch 'master' of https://github.com/LysanderGG/stb into working

[33mcommit 932d485146e888d899b31e586b5b9e9f5faac5e8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jul 9 23:01:29 2014 -0700

    fix warnings in certain console compilers

[33mcommit efd6b2698f0b420ec06c79e0def961e6b4f1866b[m
Author: Lysander <lysandergc@gmail.com>
Date:   Wed Jul 9 22:41:22 2014 +0900

    Fix crash when trying to load progressive jpeg due to uninitialized s->img_n
    
    Proper pointer check before deleting

[33mcommit 2da2806d20c72fe78c19a03f920de669f7c49bc1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 16:24:11 2014 -0700

    update version numbers due to warnings/minor fixes

[33mcommit 0cc827fe2ac16e7d809f2609b7eb1e45f306e42c[m
Merge: a55eae2 816ea35
Author: nothings <sean2@nothings.org>
Date:   Mon Jul 7 16:20:34 2014 -0700

    Merge pull request #15 from nodj/master
    
    minor warn correction

[33mcommit a55eae20dc1fc14e151fa6847a809d04d174ce68[m
Merge: e454b82 72f06c2
Author: nothings <sean2@nothings.org>
Date:   Mon Jul 7 16:19:30 2014 -0700

    Merge pull request #17 from Gargaj/patch-1
    
    Explicit CDECL needed for qsort comparison function

[33mcommit 72f06c29966ff711a7b9fd21ab602c32cea2f060[m
Author: Gargaj <gargaj@conspiracy.hu>
Date:   Mon Jul 7 23:58:50 2014 +0200

    Explicit CDECL needed
    
    QSORT only takes CDECL, but project settings can define different defaults for calling conventions.

[33mcommit e454b82a786caa027a409836f49f3d63826f5b10[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 07:46:39 2014 -0700

    remove tabs

[33mcommit 1dcaa6059e49d4cc207847b591b54dda27aebb57[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 07:41:07 2014 -0700

    add stb_herringbone_wang_tile

[33mcommit 055137e3fa98a168281128b4c8731b84077a3c8c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 07:39:52 2014 -0700

    more useful URL

[33mcommit e8dbc6d9db15a04af180f389b6cbe9d01ee3e09a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 07:34:37 2014 -0700

    documentation & license

[33mcommit 6918b443e29d7c5a3e07f87c15140145b80baa5d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 07:13:45 2014 -0700

    stb_herringbone_wang_tile sample data

[33mcommit 816f31e9bc62a76b4195aaea297c350afd5cb43d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon Jul 7 04:54:52 2014 -0700

    fixes and tests

[33mcommit 4b590c0a6216d774f440ad16ce6674ea40c3e0a2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jul 4 09:34:57 2014 -0700

    first pass at stb-izing complete, now need to debug

[33mcommit 88c99e47fb12a5d71cfe5f3eb6f7601357924fd4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jul 4 08:06:36 2014 -0700

    initial commit

[33mcommit 8c83fc2bad7d97a641aea0e07bcd578910c3ede7[m
Author: HouQiming <hqm03ster@gmail.com>
Date:   Wed Jul 2 18:58:52 2014 +0800

    Added STBTT_PLATFORM_ID_UNICODE
    
    Added a STBTT_PLATFORM_ID_UNICODE clause to support iOS/Mac fonts

[33mcommit df29024046539a29d83172b202055a76379cc664[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 25 15:29:29 2014 -0700

    fix old stb_image.h search&replace that screwed up comments

[33mcommit 816ea354355bc5141aa4f2ff75fe93b71ee35c41[m
Author: johan <johan.duparc@gmail.com>
Date:   Mon Jun 23 01:17:43 2014 +0200

    warn correction
    
    gcc warning: unused parameter removed for macro STBTT_free

[33mcommit b000f920ac705a76fdb9a1a81e244b51e48328dd[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 22 11:21:11 2014 -0700

    update stb_image version number

[33mcommit 52f1a7614dbf21d45a42f8fc5ab695664e2659a6[m
Author: johan <johan.duparc@gmail.com>
Date:   Sun Jun 22 19:47:17 2014 +0200

    remove gcc4.9.0 / c++11 warnings
    
    corrected annoying warnings about 'missing initializer'. The memset
    version is not better, but gcc like it more.

[33mcommit 2452f0002f930ec6896277fa87ff4e268d0e75fb[m
Merge: b5336df d4d046b
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 20:21:32 2014 -0700

    Merge branch 'textedit'

[33mcommit d4d046be09121ab63682692f7c4626f53b94d9d8[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 20:21:08 2014 -0700

    update version number

[33mcommit b5336df11d723c26ef3efa547608cddf7b31b2bf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 20:03:33 2014 -0700

    update version numbers

[33mcommit 62e4ffe6c759a87baabf98c3d1c9865c93e5d135[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 20:03:22 2014 -0700

    fix bug in string parsing that was ignoring next character after the string

[33mcommit 44c37c51c05d076314df63f3ed837b52c14f0297[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 19:56:11 2014 -0700

    add testing project for stb_c_lexer.h

[33mcommit cd1f731f97753d9a0dada20a701c206990f52dde[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 19:45:06 2014 -0700

    update version numbers

[33mcommit e8b2939df9880a123f330eda800503f54ca9a7e2[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Thu Jun 19 19:44:34 2014 -0700

    fix bug in stb_vorbis_get_samples_float

[33mcommit b7be9848aeae89e71ccc0d0b8383b27fda1ef8cc[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:36:34 2014 -0700

    update version numbers

[33mcommit f5dfba0b8b42406c70e4301c44af50dcf9198899[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:17:04 2014 -0700

    Update stb_image test code to test loading with all channel counts (including 0),
    to avoid missing bugs like the recent TGA bug in the future. Doesn't check the
    *results*, but tests that it doesn't crash or fail.

[33mcommit 23a775cc1302878cada7186b4ee95feb8f24fb54[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:11:10 2014 -0700

    update release notes at end of file

[33mcommit 5753c13f25b5d18e2da3a3e537f078a1f7a1c631[m
Merge: fa30cdb 381ae02
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:08:12 2014 -0700

    Merge branch 'load-bmp-v5-header' of https://github.com/saitoha/stb into working
    Update version number

[33mcommit fa30cdba890c00e539d2ad9511bec3811e6100d4[m
Merge: d0c33a7 cd68193
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:01:11 2014 -0700

    Merge branch 'rewind-after-bmp-testing' of https://github.com/saitoha/stb into working

[33mcommit d0c33a77f962f770c5117733e5ced4a41c946eb4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 13:00:00 2014 -0700

    TGA loader fix to new optimized path by Jerry Jansson

[33mcommit 2fb6df190bdf29c00f232d86a217bc3004f5165e[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 12:49:32 2014 -0700

    fix accidental stb__skip renames in comments

[33mcommit 42ee04240783273528cdd08ddaaf4b53bcd8e85c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 15 12:47:14 2014 -0700

    Re-add lost fix to 'get_location' function as reported by Andreas Fredriksson.

[33mcommit cd6819374ce3b338ea935aa871660a981c4ca7e7[m
Author: Hayaki Saito <user@zuse.jp>
Date:   Sun Jun 15 13:57:03 2014 +0900

    Make sure to rewind after BMP test, to fix broken GIF test

[33mcommit 381ae02955e948bcd4ce7e4b879aa534b78286b2[m
Author: Hayaki Saito <user@zuse.jp>
Date:   Sun Jun 15 13:47:41 2014 +0900

    Add support for loading BMP v5 header

[33mcommit 79c0470c0c14ff5fac0d06d88d66d46cd1863e3e[m
Merge: 48234a1 339beaf
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 8 13:26:58 2014 -0700

    Merge branch 'click-half-character' of https://github.com/sgraham/stb into textedit

[33mcommit 339beafc12eaed3deee31f4af6f13fd8f9b4f1b6[m
Author: Scott Graham <scottmg@chromium.org>
Date:   Sun Jun 8 12:44:28 2014 -0700

    Clicking on left half of character selects before, and right half after

[33mcommit 48234a1644c133a6c53b7b90e0fd49eae87fc19c[m
Merge: 2684499 c453079
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat Jun 7 15:47:24 2014 -0700

    Merge branch 'shift-home-end-cursor' of https://github.com/sgraham/stb into working

[33mcommit c4530794fbae7f7ef5b30a0c7c781e164cb808f7[m
Author: Scott Graham <scottmg@chromium.org>
Date:   Sat Jun 7 14:36:04 2014 -0700

    cursor should move on shift-home and shift-end

[33mcommit 2684499fcea02900c331ecf1764795923a0703c6[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jun 6 23:59:38 2014 -0700

    tweak textedit sample fix

[33mcommit 885b1b7ded3d5ef5c78a6cf7a655897402e22c14[m
Author: Scott Graham <scottmg@chromium.org>
Date:   Fri Jun 6 23:08:51 2014 -0700

    fix textedit_sample a bit

[33mcommit 3557e66362458db4465d9bf6c08d6ea785d37306[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jun 6 12:17:39 2014 -0700

    fix accidental rename of 'skip'

[33mcommit 47a34c1723e6a8bdbb2eabad0b7ae94afd55b3bf[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jun 6 10:17:32 2014 -0700

    stb_image.h version number increase

[33mcommit c28ffbbf0dd033e030b06ea173ca8178aa6d5e87[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Fri Jun 6 10:15:30 2014 -0700

    Change byte casts in stb_image.h that intentionally truncate to do so explicitly for MSVC runtime check compatibility

[33mcommit f54bc09e4fca47ae747f81d65691a78dea6060ef[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 4 17:57:42 2014 -0700

    make header files visible in file list

[33mcommit 6f851e8c0f2d1b459e49041bfe0935cce85c879b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 4 17:57:25 2014 -0700

    update stb_image version number

[33mcommit d6fa4e14ee883602601c7ce5dbdeeeae2be92a5d[m
Merge: df3dcb5 41a3179
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 4 17:57:00 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit df3dcb5d0dd2bf41e3f16179e0d31188ade6c58c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed Jun 4 17:56:18 2014 -0700

    remove duplicate typedef of stbi_uc

[33mcommit 41a31793977b93b25484537e48ecdcca312c6b8b[m
Author: nothings <sean2@nothings.org>
Date:   Tue Jun 3 10:23:12 2014 -0700

    Note insecurity of stb_sprintf

[33mcommit b5230e06855a17e86ffed406cc89d905f64f8438[m
Author: nothings <sean2@nothings.org>
Date:   Tue Jun 3 10:21:39 2014 -0700

    Add comments describing all stb_ functions
    
    Added comments for all stb_ functions since I'm
    now using this program as an illustrative example
    of the value of something like stb_ functions.

[33mcommit 9e63c50707389889a7fcbbadf9dde6a1b7b2720c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jun 3 09:15:53 2014 -0700

    rename stb_image.c to stb_image.h

[33mcommit b96edc012cfec1755b5ef590b51b4d995d8db21a[m
Merge: b0d2481 334cec8
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jun 3 08:51:40 2014 -0700

    Merge branch 'headerify'
    
    Conflicts:
            tests/stretch_test.dsp

[33mcommit 334cec8d8c4d90db48bce9857cedd78badfbc76a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue Jun 3 08:45:34 2014 -0700

    Fix handling of iphone-procesed image to not accidentally appear corrupt (instead they just load wrong).
    Add a proper testing path to image test

[33mcommit b0d2481b49572adf1a9a1f375784c650540ba647[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 1 12:13:50 2014 -0700

    added a little more documentation to stretchy_buffer.h and bumped version number

[33mcommit 76dcd60fd4ca0d969ed452c20ab2991b7b160a06[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 1 08:24:08 2014 -0700

    update stretchy_buffer version number

[33mcommit 5dc4bbbdc4e055526883d9d3384ef7dca0fb1dd0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 1 08:05:01 2014 -0700

    minor README tweak

[33mcommit ca093eda56384ca2bdd9ad9e9665c21b17c2c55d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 1 08:04:07 2014 -0700

    add strict-aliasing warnings; update readme to include stretchy_buffer

[33mcommit a57dfc50fc37cc0a912084cf8c50eeb5482cb899[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun Jun 1 08:01:01 2014 -0700

    fix bugs in new stretchy buffer code, add stretchy buffer tests

[33mcommit 728d435591b7564250203f68c131149d66b5248f[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat May 31 23:48:58 2014 -0700

    move stb_howto this time

[33mcommit add9346eef2b9c5e0e5ee9a65683d549dbfae6ea[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat May 31 23:48:05 2014 -0700

    whoops, wrong file

[33mcommit 05a9cfe036b53b26bbcf5f92ff38b9a460e30a58[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat May 31 23:45:34 2014 -0700

    update readme with new stb_how.txt location

[33mcommit 037491ca452f1e642cb1f461b946e5647f18604c[m
Merge: 7ed3bb2 4e8cade
Author: Sean Barrett <sean2@nothings.org>
Date:   Sat May 31 23:43:47 2014 -0700

    Merge branch 'working'

[33mcommit 4e8cade2cf0732ec692d5c7ada15312307a4e34f[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 13:46:13 2014 -0700

    move image_test into main tests directory

[33mcommit 2bf4326350badbf345c618040f2815ab4b33cda6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 13:39:00 2014 -0700

    cleanup runtime output/error detection of stb.h unit tests

[33mcommit 509f9777e53086e0d4f566b5483084160b693b69[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 13:34:37 2014 -0700

    minor doc improvement

[33mcommit cf72af77885fc9b53b197c34f9e23532bcb557af[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 13:22:56 2014 -0700

    header guards, fix faux-null-ptr constant, tweak docs

[33mcommit 666596ed89a41be2ed45351c0d68407a465159c2[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 13:00:39 2014 -0700

    untested rewrite of stretchy_buffer relying on implicit cast from void*

[33mcommit 5576a5044f596fa7508f1cd0d20a7135772ac3e1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 12:12:34 2014 -0700

    initial check-in

[33mcommit 687985dbf9f9a5bed4dd2da9ccb12f8a719b835b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 12:10:35 2014 -0700

    move stb_image.c to deprecated since stb_image.h replaces it

[33mcommit 236004f5738e6f33270d2b61c6d94321305a831a[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 06:55:48 2014 -0700

    finished renaming all private functions & globals with stbi__ prefix

[33mcommit a7691e1510778b47fc638ca535d7c78eb48e7fc3[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 06:31:27 2014 -0700

    check-in missing project file updates for stb_image.h usage

[33mcommit d5272d32e4ecf1a393209405e8dbb73a979e4d39[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 06:27:37 2014 -0700

    renaming completed through png decoder

[33mcommit 7add5044e07d261652219645e68ecb4c6a43a8d1[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 06:27:09 2014 -0700

    bump version number

[33mcommit 9f251b6da1bc6c3a1f65b8a204b9ea9f6d87c46b[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 06:25:31 2014 -0700

    rename stb_image_write private functions to use stbiw__ not stbi__ to avoid conflict with stb_image.h

[33mcommit 9549e83e5d144264cff183078af974df75e1f016[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 05:40:05 2014 -0700

    renaming completed through jpeg decoder

[33mcommit 2514fbc2c7717ece44cf9b8bb69dc56d31649746[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 05:38:26 2014 -0700

    more renaming

[33mcommit 927b455d8552ec86721a441011841677b82f4827[m
Author: Sean Barrett <sean@nothings.org>
Date:   Sat May 31 04:49:43 2014 -0700

    start converting stb_image.c to a .h file

[33mcommit 7ed3bb26bb12bc5a36d366b632e33796fbd571f8[m
Merge: f9ab452 2d412f0
Author: Sean Barrett <sean@nothings.org>
Date:   Fri May 30 14:25:49 2014 -0700

    Merge branch 'working'

[33mcommit 2d412f0d6cb21171f89d2a4b5902fff4b0869af9[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri May 30 14:20:16 2014 -0700

    move stb_how.txt into docs directory

[33mcommit 5ecae715b0f8529610a34f34358d3695a0f8cf75[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri May 30 14:17:19 2014 -0700

    batch file to run make_readme

[33mcommit fcfcb9bb3f512b3eddfc3ad9f054f5de6b065fc6[m
Author: Sean Barrett <sean@nothings.org>
Date:   Fri May 30 14:15:51 2014 -0700

    generate README.md in part by parsing libraries so that version numbers are in sync

[33mcommit 9e566c8b31b302c60381f775f2dace290e7a9937[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Wed May 28 11:05:17 2014 -0700

    trailing newline

[33mcommit f9ab452e7db2388b12c45d12bc5ffa84f1315566[m
Merge: 42bd3e2 3e1d164
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 23:13:55 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 42bd3e253be2a22fc71ccf87b020f49a59046482[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 23:13:34 2014 -0700

    rename test files to be more meaningful

[33mcommit 3e1d164505c67cf852228468ec71a4792b0b7f80[m
Author: nothings <sean2@nothings.org>
Date:   Tue May 27 23:04:29 2014 -0700

    update version numbers

[33mcommit e63b3e0702b26902d9760b40cce431a9c3087cc1[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 22:56:57 2014 -0700

    fix some stuff that used RAD types and so were totally broken, add a compile test/sample

[33mcommit 1d2770394ad1e5b0aff366a03fc67df1527d6dc7[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 21:56:42 2014 -0700

    rest of image-test case

[33mcommit f0976fd3126eaf81387e12d9da2834a615f7d077[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 21:56:00 2014 -0700

    tga optimizations

[33mcommit fc0bfd1b714ed15f5dc597305c9910a3c80f2cab[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 21:38:43 2014 -0700

    fix some typos, add image test program

[33mcommit a31d50ab2918a5ac3d8a70506d483a4c79c32402[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 12:36:01 2014 -0700

    more warnings, use stdint.h if possible

[33mcommit 70df4966f0b6a84820b96087c4e8243590721e2d[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 12:14:26 2014 -0700

    various warning fixes, STBI_SIMD compile error, incorrect file-pointer state for one API

[33mcommit ecff8d5d42e88e636f6b2e15574d688b6b8880aa[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Tue May 27 09:23:06 2014 -0700

    rename integer types to avoid collisions

[33mcommit ab33a725b9f6826302bb828972eb419c5f169e6a[m
Author: nothings <sean2@nothings.org>
Date:   Mon May 26 10:46:57 2014 -0700

    fix vorbis description

[33mcommit db779b34ce4793e3b957d5698b74ea35fc4ad00f[m
Author: nothings <sean2@nothings.org>
Date:   Mon May 26 09:35:37 2014 -0700

    add version numbers

[33mcommit b4da2c643fb12a474cc0f7168ebf966b191303a9[m
Merge: 3442081 d676ead
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon May 26 09:31:04 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit 344208144d0fe5076703965d5f217b2488e6c66a[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Mon May 26 09:30:46 2014 -0700

    1.0 release (still no seeking, sorry)

[33mcommit d676ead0ed8f9eb4438fec6be819e8748103895e[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 21:58:53 2014 -0700

    add stb_divide

[33mcommit a8fbfd2cb3bba73a17dd33d2c87137f5cab4d06c[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 21:54:59 2014 -0700

    stb_divide.h

[33mcommit d06c9878107144113d70fc890c4016fbc46ace71[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 21:03:53 2014 -0700

    update version number

[33mcommit eb62c741ea611b7d63b7a0498d900233d81c16a4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 20:56:24 2014 -0700

    fixed warnings for stb_truetype (fixes all outstanding bug reports)

[33mcommit 31897dfd7ff8a49672b346e3c845b9c51d053db0[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 20:10:17 2014 -0700

    compile tests for everything except textedit, both C and C++

[33mcommit 6d0bc14a2519a8fe02c2a9feb1161b96ab04815c[m
Merge: dc6adca 9be02f2
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 13:36:26 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit dc6adca82f732ac9d7c92df829fb8e62faa6f203[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 13:35:50 2014 -0700

    vc6 project files for testing stb.h

[33mcommit 9be02f21e39e28ae3a9ebcfaf0cb707d3bdfd76b[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 13:01:00 2014 -0700

    typo, faq additions

[33mcommit d4f114adcc6ac17248805aa63aab0da1a05e0bec[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 12:58:10 2014 -0700

    advice for how to make your own stb-style library

[33mcommit 38c36fa0484e0e45543dae10453dd1c0b9b1166b[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:58:26 2014 -0700

    added library categories

[33mcommit 03eb096b74bc9779875b1b0652c8d28f760e0c3a[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:55:54 2014 -0700

    add stb_dxt.h

[33mcommit ba939f12f871e75725bbba59988046fb8e7919ba[m
Merge: bfef4c1 cdeef25
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 11:54:32 2014 -0700

    Merge branch 'master' of https://github.com/nothings/stb

[33mcommit bfef4c10e8a43c4b1a2121d1fadc19f5046148f9[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 11:54:10 2014 -0700

    added stb_dxt.h

[33mcommit cdeef25d28650d753ab9d68614e63176b2ad6da6[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:32:53 2014 -0700

    faq

[33mcommit bc854ecf144dff21758222f28885ccde42b0418c[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:31:31 2014 -0700

    Update README.md

[33mcommit 9b067cb69c271b5e9623c168be12ce45a884d67b[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 11:10:31 2014 -0700

    add stb_truetype

[33mcommit 58f31d335689c2c1c7a50f67671dde53cc599378[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:09:10 2014 -0700

    update description of libraries

[33mcommit bbd9bec0f120045def637fa0fc34afef8f5614b5[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 11:07:28 2014 -0700

    list of libraries

[33mcommit 01abb95cc30b3ff92f6cd46fb445189b7c495ce4[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 10:54:36 2014 -0700

    license in readme

[33mcommit e2caccb811d70af0dc359be5522e6b0d3b503e46[m
Author: Sean Barrett <sean2@nothings.org>
Date:   Sun May 25 10:18:03 2014 -0700

    initial checkin

[33mcommit 70171b8d2a6319f9179679d38fb645fa03533d71[m
Author: nothings <sean2@nothings.org>
Date:   Sun May 25 09:51:23 2014 -0700

    Initial commit
