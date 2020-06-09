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

#include "breath/conversion/bit_cast.hpp"
#include "breath/testing/testing.hpp"
#include <cstring>
#include <iostream>

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
    struct dest   { int a =  50 ; void operator &() = delete ; } ;
    struct source { int b = 100 ; void operator &() = delete ; } ;

    source const        s ;
    auto const &        d = breath::bit_cast< dest >( s ) ;

    BREATH_CHECK( d.a == 100 ) ;
}

void
pointer_to_object_casts_to_pointer_to_object()
{
    void const * const  pv = "test" ;

    //      Note that the bit_cast is not "casting away constness",
    //      here.
    // -----------------------------------------------------------------------
    char const * const  pc = breath::bit_cast< char * const >( pv ) ;

    BREATH_CHECK( pc == pv ) ;
    BREATH_CHECK( std::strcmp( pc, "test" ) == 0 ) ;
}

void
pointer_to_void_casts_to_pointer_to_function()
{
    bool                is_ok = false ;

    //      See comment above about "casting away constness".
    // -----------------------------------------------------------------------
    void const * const  pv = breath::bit_cast< void * >( &set_to_true ) ;

    typedef void ( *    pointer_to_function_type )( bool & ) ;
    pointer_to_function_type const
                        pf = breath::bit_cast< pointer_to_function_type >( pv )
                        ;
    pf( is_ok ) ;

    BREATH_CHECK( is_ok ) ;
}

void
bit_cast_is_noexcept_if_and_only_if_dest_default_ctor_is()
{
    struct not_noexcept_dest { not_noexcept_dest() {} } ;
    struct     noexcept_dest { noexcept_dest() noexcept {} } ;

    struct source { };

    static_assert(  noexcept( breath::bit_cast<     noexcept_dest >( source() )
                 ), "" ) ;
    static_assert(! noexcept( breath::bit_cast< not_noexcept_dest >( source() )
                 ), "" ) ;
}

}

int
test_bit_cast()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( {
                struct_casts_to_struct,
                pointer_to_object_casts_to_pointer_to_object,
                pointer_to_void_casts_to_pointer_to_function,
                bit_cast_is_noexcept_if_and_only_if_dest_default_ctor_is } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
