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

#include "breath/diagnostics/last_api_error.hpp"
#include "breath/testing/testing.hpp"
#include "breath/text/begins_with.hpp"
#include "breath/text/ends_with.hpp"
#include <iostream>
#include <string>

int                 test_last_api_error() ;

namespace {

void
message_begins_with_user_message_if_and_only_if_one_is_provided()
{
    {
        std::string const   incipit( "Breath unit tests" ) ;
        breath::last_api_error
                            error( incipit.c_str() ) ;

        BREATH_CHECK(   breath::begins_with( error.what() , incipit + ": " ) ) ;
        BREATH_CHECK( ! breath::ends_with(   error.what() , incipit + ": " ) ) ;
    }

    {
        char const *    incipit = nullptr ;
        breath::last_api_error
                        error( incipit ) ;

        BREATH_CHECK( ! breath::begins_with( error.what(), ":" ) ) ;
    }

    {
        char const *    incipit = "" ;
        breath::last_api_error
                        error( incipit ) ;

        BREATH_CHECK( ! breath::begins_with( error.what(), ":" ) ) ;
    }
}

//      Of course, this test is really for Windows. But, since there
//      won't be a CRLF in Unix either, we execute it on both platforms
//      and don't bother with making distinctions.
// ---------------------------------------------------------------------------
void
message_does_not_end_with_cr_lf()
{
    breath::last_api_error
                        error( nullptr ) ;

    BREATH_CHECK( ! breath::ends_with( error.what(), "\r\n" ) ) ;
}

}

int
test_last_api_error()
{
    using namespace breath ;

    return test_runner::instance().run( "last_api_error",
        { message_begins_with_user_message_if_and_only_if_one_is_provided,
          message_does_not_end_with_cr_lf } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
