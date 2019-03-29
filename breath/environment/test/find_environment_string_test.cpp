// =========================================================================
//                This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
#include "breath/environment/find_environment_string.hpp"
#include "breath/idiom/maybe.hpp"
#include <string>

/////////
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    using namespace breath ;

    maybe< std::string >
                        e = find_environment_string( "BREATH_ROOT" ) ;

    DO_TEST( e.is_valid() ) ;
}