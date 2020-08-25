@echo off
rem ==========================================================================
rem                        Copyright 2013 Gennaro Prota
rem
rem                  Licensed under the 3-Clause BSD License.
rem             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
rem              <https://opensource.org/licenses/BSD-3-Clause>.)
rem __________________________________________________________________________
rem
rem     A quick tool to invoke before compiling with Cygwin, on Windows.
rem
rem     The only important thing that this does is putting /usr/bin at
rem     the *end* of %PATH%, so that Cygwin's `link' isn't found before
rem     the homonym Microsoft linker.
rem
rem     Usage: see the top-level read_me.
rem --------------------------------------------------------------------------

setlocal

set CYGWIN_ROOT=C:\cygwin64
%CYGWIN_ROOT%\bin\mintty.exe --icon /Cygwin-Terminal.ico    ^
                             --exec "./append_to_path.sh"

endlocal

rem Local Variables:
rem mode: bat
rem indent-tabs-mode: nil
rem batch-indent-level: 4
rem End:
rem vim: set ft=dosbatch et sts=4 sw=4:
