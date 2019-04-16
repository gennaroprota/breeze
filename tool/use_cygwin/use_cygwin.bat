@echo off
REM ==========================================================================
REM                        Copyright 2013 Gennaro Prota
REM
REM                  Licensed under the 3-Clause BSD License.
REM             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
REM              <https://opensource.org/licenses/BSD-3-Clause>.)
REM __________________________________________________________________________
REM
REM     A quick tool to invoke before compiling with Cygwin, on
REM     Windows.
REM
REM     The only important thing that this does is putting /usr/bin
REM     at the *end* of %PATH%, so that Cygwin's `link' isn't found
REM     before the homonym Microsoft linker.
REM
REM     Usage:
REM         1. invoke the Visual Studio Command Prompt of your choice
REM            (x86, x64, etc.)
REM         2. run this batch file.
REM --------------------------------------------------------------------------

@echo on
setlocal

set CYGWIN_ROOT=C:\cygwin64
%CYGWIN_ROOT%\bin\mintty.exe -i /Cygwin-Terminal.ico --exec "./append_to_path.sh"

endlocal

REM Local Variables:
REM mode: bat
REM indent-tabs-mode: nil
REM batch-indent-level: 4
REM End:
REM vim: set ft=dosbatch et sts=4 sw=4:
