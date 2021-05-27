<!--
 =============================================================================
                      Copyright 2019-2020 Gennaro Prota

                   Licensed under the 3-Clause BSD License.
              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
               <https://opensource.org/licenses/BSD-3-Clause>.)
 _____________________________________________________________________________
-->

# Overview

*GitHub repo's master branch at a glance:*

<!--    Note: if you word-wrap these lines differently, make sure that
        everything appears correctly on <github.com>.
     -------------------------------------------------------------------------
-->
[![Builds and tests results](
https://img.shields.io/github/workflow/status/gennaroprota/breeze/builds_and_tests/master?label=builds%20%26%20tests)](
https://github.com/gennaroprota/breeze/actions)
![Lines of code counter](
https://tokei.rs/b1/github/gennaroprota/breeze?category=code)
![Lines of comment counter](
https://tokei.rs/b1/github/gennaroprota/breeze?category=comments)

*DocsForge documentation:*

[![DocsForge documentation](
https://img.shields.io/badge/breeze-on%20docsforge-blue)](https://breeze.docsforge.com)

Welcome to *Breeze*, my personal toolkit of C++ components. The components range
from cryptography (MD5, SHA-1, SHA-2) to checksums, string utilities, operating
system identification and much more. You'll get a precise idea by exploring the
breeze/ subdirectory of the source tree or the full documentation (see below).

The library has been developed, in my spare time, over a period of about 13
years (as of June 2019) and I don't claim that all of it is of production
quality.

Some components don't take full advantage of the latest standards and some are
or will be superseded by standard components or features (e.g. those in the
path/ subdirectory). But, generally, the library is up to date with C++14.

The test/ subdirectories can be a good place to look at if you need to see usage
examples (but, please, let me know if you feel that the usage of a component
should be documented better).

# Building the library

Breeze has been designed and implemented to be as portable as possible, without
a single usage of `#if`, `#ifdef` or `#ifndef` (the only conditional compilation
is for include guards), and the goal is that it can be compiled with any
conforming C++14 compiler.

The provided build system, however, requires a Unix toolkit, with Python 3 and
GNU Make. On Microsoft Windows, you'll need Cygwin. (Historically, I used `awk`
and other Unix tools for things that I'd now do in Python; long term, I'll
completely migrate to Python, but, for the moment, we need those tools, as
well.)

Note that only Cygwin 64-bit is supported.

For the editor support, and for some tests, you need to define the environment
variable `BREEZE_ROOT` to the full path of the source tree. Use forward slashes,
even on Windows, and omit the trailing slash.

The bin/ subdirectory of the Cygwin installation must be in the `PATH`.

To build the library:

 - if you are on Windows and you want to use MSVC, run a Visual Studio Command
   Prompt, issue the command `cd /D "%BREEZE_ROOT%/tool/use_cygwin/"` (the `/D`
   option is for the case in which `%BREEZE_ROOT%` is on a different drive) and
   launch `use_cygwin.bat`; then use the resulting Cygwin window

 - `cd` to `$BREEZE_ROOT` (add quotes if the value of `$BREEZE_ROOT` contains
   spaces)

 - issue a command like this:

   ```
   architecture=x86_64 system=windows compiler=gcc build_type=optimized make
   ```

   *Note: on some systems, you might need to use `gmake` instead of `make`.*

The `architecture` part can be omitted for x86_64 (that's the default).

The `clean` target is also supported (you still need to provide `system`,
`compiler` and `build_type`: when you clean, only the files generated for a
given architecture/system/compiler triplet and build type (debug/optimized) are
removed).

At the moment, `system` must be set to one of the following:

 - unix, windows, macos

while `compiler` must be set to one of:

 - clang, gcc, msvc

The value `unix` should work on all Linuxes and FreeBSD, while macOS needs its
own value.

Finally, `architecture` can be anything, because it is currently only used to
include or exclude a component (get_cpuid_info()) which is specific to x86 and
x86_64; and `build_type` must be one of:

 - debug, optimized

Under Cygwin, with both Clang and GCC, you can build with `system=windows` or
`system=unix`. In both cases, this will, by default, generate a library which
depends on the Cygwin DLL. To avoid this dependency when `system=windows`, you
can use the compilers provided by the *mingw\*gcc\** or *mingw\*clang* packages
(available in the Cygwin installer) and select one of them via the
`compiler_command` variable; e.g.:

```
system=windows compiler=gcc build_type=optimized compiler_command=x86_64-w64-mingw32-g++ make
```

**Warning:** you might want to also add

```
cpp_extra_options="-static -static-libgcc -static-libstdc++"
```

to the command line, but note that the `cpp_extra_options` variable is
experimental.

*Note: to get a list of the available Make targets, with a brief description for
each of them, launch the command `make help` (or `gmake help`).*

# A note about the documentation

The documentation is contained in the source files, in the form of Doxygen
comments. This keeps the code and the documentation together, and that's about
the only advantage of it. For the rest, Doxygen is one of the most disappointing
tools available, but I don't have time to migrate to something else.

Given the quality of the Doxygen output, I unwillingly recommend to mostly read
the documentation directly from the source files. In any case, to generate
separate documents, a `documentation` target is provided in the makefiles
(please, remember to `cd` to `BREEZE_ROOT`; the documentation entry point will
be `BREEZE_ROOT/doc/html/index.html`).

**Note on the note :-)**: I just registered the project with DocsForge; the
resulting documentation seems much better than the one generated by Doxygen,
although some interlinks are wrong. Unless you are without an Internet
connection, it might be a good alternative for you to use:
<https://breeze.docsforge.com>.

# Editor support

The source tree contains a `.editorconfig` (<https://editorconfig.org>). In
addition, files having name extensions that are not automatically recognized by
Emacs or Vim (e.g. .tpp) have simple trailers which make these editors recognize
the file type.

If you plan to contribute, please use `tool/init_file/init_file.sh` to
initialize your source files. You should define the environment variable
`BREEZE_CONTRIBUTOR` to the name you wish to appear in your copyright notices.
Also, you should build the `include_guard` tool (which is automatically built
with the library: see "Getting started"), and copy it to `BREEZE_ROOT/bin/`.

If you use Vim, just source `breeze.vim` from your `.vimrc` and that will take
care of running the initialization script on any file you create in
`BREEZE_ROOT` or in any subdirectory.

If you use another editor, please contribute something analogous to `breeze.vim`
for that editor.

# Git commit message template

To enable the Git commit message template provided with the library:

 - `cd` to `BREEZE_ROOT`

 - run: `git config --local commit.template ./.git_commit_message_template.txt`

For better or for worse, the library uses the Git commit message guidelines
outlined at <https://chris.beams.io/posts/git-commit/>, except that the subject
line:

 - can reach 72 characters, just like the body lines (50 is really too little)

 - is worded in the imperative mood, but doesn't necessarily complete the
   sentence "this commit will..."; e.g. it may begin with "Don't" (I believe
   that, in fact, this is the intent of the guidelines)

Please, have a look at the guidelines if you are not familiar with them.

# Supported compilers

Note that, as of August 24, 2020, if you need to use the library with MSVC 2015,
that's quite easy as long as you are willing to give up on `constexpr` for some
components (`BREEZE_ASSERT()`, `count_bits()` (now `population_count()`),
`gcd()`, `lcm()`).

Compiler | Minimum supported version
---------|----------------------------
Clang    | 5.0.1
GCC      | 6.1.0
MSVC     | 2017

# Future directions

We will soon add facilities for handling command line options.

# License

Breeze is made available subject to the terms of the 3-Clause BSD License,
reproduced in the file `3_CLAUSE_BSD_LICENSE.txt`, at the root of the source
tree.

# Reporting issues

I can't guarantee any kind of support, but if you have an issue with the
library, please send me a mail describing the problem (*name.surname*@gmail.com)
and I will try to address it as soon as possible.

# Acknowledgments

My most heartfelt *thank you* goes to James Kanze, without whom I wouldn't be
the programmer I am.
