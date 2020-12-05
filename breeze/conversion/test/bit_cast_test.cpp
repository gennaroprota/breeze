// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/conversion/bit_cast.hpp"
#include "breeze/testing/testing.hpp"
#include <cstring>

int                 test_bit_cast() ;

namespace {

void
set_to_true( bool & b )
{
    b = true ;
}

void
struct_casts_to_struct()
{
    //      Note the removal of the initializer of dest::a, and the use
    //      of a later assignment, instead. This is to avoid a
    //      -Wclass-memaccess warning from GCC >= 8.1. This is the same
    //      situation reported at:
    //
    //        <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=87427>
    //
    //      and it is a "won't fix".
    // -----------------------------------------------------------------------
    struct dest   { int a /* = 50 */ ; void operator &() = delete ; } ;
    struct source { int b    = 100   ; void operator &() = delete ; } ;

    source const        s ;
    dest                d ;
    d.a = 50 ;

    d = breeze::bit_cast< dest >( s ) ;

    BREEZE_CHECK( d.a == 100 ) ;
}

void
pointer_to_object_casts_to_pointer_to_object()
{
    void const * const  pv = "test" ;

    //      Note that the bit_cast is not "casting away constness",
    //      here.
    // -----------------------------------------------------------------------
    char const * const  pc = breeze::bit_cast< char * const >( pv ) ;

    BREEZE_CHECK( pc == pv ) ;

    //      The comparison with nullptr is redundant if the previous
    //      test succeeds; but it deals with Microsoft Code Analysis
    //      warning C6387: 'pc' could be '0':  this does not adhere to
    //      the specification for the function 'strcmp'. Note that
    //      PVS-Studio detects that the comparison is redundant, so we
    //      suppress the corresponding diagnostic (together with the one
    //      emitted for the use of std::strcmp()).
    // -----------------------------------------------------------------------
    BREEZE_CHECK( pc != nullptr &&         //-V560 // -V2513 (for PVS-Studio)
        std::strcmp( pc, "test" ) == 0 ) ;
}

void
pointer_to_void_casts_to_pointer_to_function()
{
    bool                is_ok = false ;

    //      See comment above about "casting away constness".
    // -----------------------------------------------------------------------
    void const * const  pv = breeze::bit_cast< void * >( &set_to_true ) ;

    typedef void ( *    pointer_to_function_type )( bool & ) ;
    pointer_to_function_type const
                        pf = breeze::bit_cast< pointer_to_function_type >( pv )
                        ;
    pf( is_ok ) ;

    BREEZE_CHECK( is_ok ) ;
}

void
bit_cast_is_noexcept_if_and_only_if_dest_default_ctor_is()
{
    struct not_noexcept_dest
          { [[ noreturn ]] not_noexcept_dest() { throw 1 ; } } ;
    struct     noexcept_dest { noexcept_dest() noexcept {} } ;

    struct source { };

    static_assert(  noexcept( breeze::bit_cast<     noexcept_dest >( source() )
                 ), "" ) ;
    static_assert(! noexcept( breeze::bit_cast< not_noexcept_dest >( source() )
                 ), "" ) ;
}

}

int
test_bit_cast()
{
    return breeze::test_runner::instance().run(
        "bit_cast()",
        { struct_casts_to_struct,
          pointer_to_object_casts_to_pointer_to_object,
          pointer_to_void_casts_to_pointer_to_function,
          bit_cast_is_noexcept_if_and_only_if_dest_default_ctor_is } ) ;
}
