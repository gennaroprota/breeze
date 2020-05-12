<!--
 =============================================================================
                      Copyright 2019-2020 Gennaro Prota

                   Licensed under the 3-Clause BSD License.
              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
               <https://opensource.org/licenses/BSD-3-Clause>.)
 _____________________________________________________________________________
-->

# Overview


[![Build Status](https://travis-ci.com/gennaroprota/breath.svg?branch=master)
](https://travis-ci.com/gennaroprota/breath)

Welcome to *Breath*, my personal toolkit of C++ components. The components range
from cryptography (MD5, SHA-1, SHA-2) to string utilities, operating system
identification and much more. You'll get a precise idea by exploring the breath/
subdirectory of the source tree or the full documentation (see below).

The library has been developed, in my spare time, over a period of about 16
years (as of June 2019) and I don't claim that all of it is of production
quality.

Some components don't take full advantage of the latest standards (e.g. they
don't use `noexcept`) and some are or will be superseded by standard components
or features (e.g. those in the path/ subdirectory). But, generally, the library
is up-to-date to C++14.

The test/ subdirectories can be a good place to look at if you need to see usage
examples (but, please, let me know if you feel that the usage of a component
should be documented better).

# Getting started

The library requires a Unix toolkit, with GNU Make and, for the x86_64 builds
only, the GNU Assembler. On Microsoft Windows, you'll need Cygwin. (If I had to
redo it today, most things would probably use Python.)

Note that only Cygwin 64-bit is supported.

For the editor support, and for some tests, you need to define the environment
variable `BREATH_ROOT` to the full path of the source tree. Use forward slashes,
even on Windows; omit the trailing slash.

The bin/ subdirectory of the Cygwin installation must be in the `PATH`.

To build the library:

 - if you are on Windows and you want to use Visual Studio, run the Visual
   Studio Command Prompt, issue the command `cd /D
   "%BREATH_ROOT%/tool/use_cygwin/"` (the `/D` option is for the case in which
   `%BREATH_ROOT%` is on a different drive) and launch `use_cygwin.bat`; then
   use the resulting Cygwin window

 - `cd` to `$BREATH_ROOT`

 - issue a command like this:

   ```
   architecture=x86_64 compiler=gcc system=windows make
   ```

The `architecture` part can be omitted for x86_64 (that's the default).

The `clean` target is also supported (you still need to provide `compiler` and
`system`: when you clean, only the files generated for a given
architecture/compiler/system triplet are removed).

At the moment, `compiler` must be set to one of the following:

 - gcc, clang, msvc

while `system` must be set to one of:

 - unix, windows

Finally, `architecture` can be anything, because it is currently only used to
include or exclude a component (get_cpuid_info()) which is x86_64-specific.

# A note about the documentation

The documentation is contained in the source files, in the form of Doxygen
comments. This keeps the code and the documentation together, and that's about
the only advantage of it. For the rest, Doxygen is one of the most disappointing
tools available, but I don't have time to migrate to something else.

Given the quality of the Doxygen output, I unwillingly recommend to mostly read
the documentation directly from the source files. In any case, to generate
separate documents, please see the `read_me` in `doc/source/`.

# Editor support and Git commit message template

The source tree contains a `.editorconfig` (https://editorconfig.org/). This
support was added just recently. Before that, only Emacs and Vim were supported.

If you plan to contribute, please use `tool/init_file/init_file.sh` to
initialize your source files. You should define the environment variable
`BREATH_CONTRIBUTOR` to the name you wish to appear in your copyright notices.
Also, you should build the `include_guard` tool (which is automatically built
with the library: see Getting started), and copy it to `BREATH_ROOT/bin/`.

If you use Vim, just source `breath.vim` from your `.vimrc` and that will take
care of running the initialization script on any file you create in
`BREATH_ROOT` or in any subdirectory.

If you use Emacs, please contribute something analogous to `breath.vim` for that
editor.

To enable the Git commit message template provided with the library:

 - `cd` to `BREATH_ROOT`

 - run: `git config --local commit.template ./.git_commit_message_template.txt`

For better or for worse, the library uses the Git commit message guidelines
outlined at https://chris.beams.io/posts/git-commit/, except that the subject
line:

 - can reach 72 characters, just like the body (50 is really too little)

 - is worded in the imperative mood, but doesn't necessarily complete the
   sentence "this commit will...", e.g. it may begin with "Don't" (I believe
   that, in fact, this is the intent of the guidelines)

Please, have a look at the guidelines if you are not familiar with them.

# License

Breath is made available subject to the terms of the 3-Clause BSD License,
reproduced in the file `3_CLAUSE_BSD_LICENSE.txt`, at the root of the source
tree.

# Issues

I can't guarantee any kind of support, but if you have issues with the library,
please send me a mail describing the problem (*name.surname*@gmail.com) and I
will try to address it as soon as possible.

# Acknowledgments

My most heartfelt *thank you* goes to James Kanze, without whom I wouldn't be
the programmer I am.

[//]: # (
 Local Variables:
 mode: markdown
 indent-tabs-mode: nil
 coding: utf-8
 End:
 vim: set ft=markdown et sts=4 sw=4:
 vim: set fenc=utf-8 nobomb:
)
