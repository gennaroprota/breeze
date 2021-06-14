" ============================================================================
"                      Copyright 2007-2011 Gennaro Prota
"
"                   Licensed under the 3-Clause BSD License.
"              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
"               <https://opensource.org/licenses/BSD-3-Clause>.)
" ____________________________________________________________________________
"
"
"       Support for (g)Vim.
"
"       See "Editor support" in the top-level read_me for more details.
"
"       Maintainance:
"           keep in sync with the corresponding Emacs facilities
" ----------------------------------------------------------------------------

"       Rationale:
"       ----------
"
"       For some file types we set Unix line endings, even under
"       Windows, which makes Cygwin and other toolsets work smoothly in
"       their most common (recommended) configuration. We don't do so
"       directly in response to BufNewFile because at that time the
"       modelines we have inserted haven't been applied yet (it may just
"       seem that they are, sometimes, because of the file name
"       extension used :-)) and I couldn't find a function akin to
"       Emacs' hack-local-variables(). We use BufWinEnter, instead,
"       taking care to not modify anything if it isn't the first enter
"       on a buffer we have filled ourselves (so if, for instance, the
"       user sets ff to the Windows style we don't revert it: he/she
"       must have had a good reason to do so).
" ----------------------------------------------------------------------------
augroup             breeze
    autocmd!
    autocmd BufNewFile  $BREEZE_ROOT/*  call s:InitPhaseOne()
    autocmd BufWinEnter $BREEZE_ROOT/*  call s:InitPhaseTwo()
augroup end


function            s:InitPhaseOne()
    "       Intentionally renouncing to full-proof escaping of <afile>
    "       (unnecessary, given the Breeze file naming guidelines).
    " ------------------------------------------------------------------------
    :exe    "%! \"" . $BREEZE_ROOT . "/tool/init_file/init_file.py\"" "<afile>"
    if v:shell_error == 0
        let b:breeze_initializing = 1
    endif
    set nomodified
endfunction

function            s:InitPhaseTwo()
    if exists( "b:breeze_initializing" )
        for x in [ "sh", "awk" ]
            if &filetype == x
                set ff=unix
                break
            endif
        endfor
        call cursor( 1, 1, 0 )
        set nomodified
        unlet b:breeze_initializing
    endif
endfunction

"       Support for the gf command ("go to file"). Unfortunately, this
"       won't work on our dependent #includes.
" ----------------------------------------------------------------------------
set path +=$BREEZE_ROOT,.
set suffixesadd +=.hpp,.tpp
