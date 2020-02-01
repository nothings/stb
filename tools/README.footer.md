
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



