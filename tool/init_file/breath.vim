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
"       See "Editor Support" in the Breath documentation for more
"       details.
"
"       Maintainance:
"           keep in sync with the corresponding Emacs facilities
" ----------------------------------------------------------------------------

"       Rationale:
"       ----------
"
"       For some file types we set Unix line endings, even under
"       Windows, which makes Cygwin and other toolsets work smoothly
"       in their most common (recommended) configuration. We don't do
"       so directly in response to BufNewFile because at that time the
"       modelines we have inserted haven't been applied yet (it may
"       just seem that they are, sometimes, because of the file name
"       extension used :-)) and I couldn't find a function akin to
"       Emacs' hack-local-variables(). We use BufWinEnter, instead,
"       taking care to not modify anything if it isn't the first enter
"       on a buffer we have filled ourselves (so if, for instance, the
"       user sets ff to the Windows style we don't revert it: he/she
"       must have had a good reason to do so).
"
"       Note, too, the usage of an explicit 'sh -c' to invoke our
"       script: Vim uses the value of the 'shell' option as name of
"       the shell (command language interpreter) to use for ! and :!
"       commands, and that is an important setting we don't want to
"       interfere with. An idea would be to set it to 'sh' and restore
"       it when we are done, but I couldn't find any synchronization
"       mechanism in the Vim docs (nor a guarantee that it would work
"       without locking). So, we simply use whatever shell is
"       configured in the editor to launch our 'sh'; for this we rely
"       on 'sh' to be on the PATH (which must be set anyway, even
"       under Windows, to have sed, awk and the other utilities work).
" ----------------------------------------------------------------------------
augroup             breath
    autocmd!
    autocmd BufNewFile  $BREATH_ROOT/*  call s:InitPhaseOne()
    autocmd BufWinEnter $BREATH_ROOT/*  call s:InitPhaseTwo()
augroup end


function            s:InitPhaseOne()
    " intentionally renouncing to full-proof escaping of <afile>
    " (unnecessary, given the Breath file naming guidelines)
    :1,$!   sh -c --
                \ "\"$BREATH_ROOT/tool/init_file/init_file.sh\" \"<afile>\""
    if v:shell_error == 0
        let b:breath_initializing = 1
    endif
    set nomodified
endfunction

function            s:InitPhaseTwo()
    if exists( "b:breath_initializing" )
        for x in [ "sh", "awk" ]
            if &filetype == x
                let oldm = &modified
                set ff=unix
                if ! oldm
                    set nomodified
                endif
                break
            endif
        endfor
        call cursor( 1, 1, 0 )
        set nomodified
        unlet b:breath_initializing
    endif
endfunction

"       Support for the gf command ("go to file"). Unfortunately, this
"       won't work on our dependent #includes.
" ----------------------------------------------------------------------------
set path +=$BREATH_ROOT,.
set suffixesadd +=.hpp,.tpp

" Local Variables:
" indent-tabs-mode: nil
" End:
" vim: set ft=vim et sts=4 sw=4:
