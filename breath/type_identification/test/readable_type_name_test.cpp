// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2017-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/type_identification/readable_type_name.hpp"
#include "breath/testing/testing.hpp"

#include <memory>
#include <string>

int                 test_readable_type_name() ;

template< typename T >
class my_template
{
} ;

class incomplete_type ;

class my_base
{
public:
    virtual void        f() {}
    virtual             ~my_base() noexcept = default ;
} ;

class my_derived
    :   public my_base
{
} ;

namespace {

void do_tests()
{
    std::string const   s = breath::readable_type_name< incomplete_type >() ;
    BREATH_CHECK( s == "incomplete_type" || s == "class incomplete_type" ) ;

    BREATH_CHECK( breath::readable_type_name< int >() == "int" ) ;

    BREATH_CHECK( breath::readable_type_name< unsigned long >() ==
                                                             "unsigned long" ) ;

    std::string const   s2 = breath::readable_type_name< int const & >() ;
    BREATH_CHECK( s2 == "int const&" || s2 == "int const &" ||
                  s2 == "int const & __ptr64" ) ;

    std::string const   s3 = breath::readable_type_name< int volatile && >() ;
    BREATH_CHECK( s3 == "int volatile&&" || s3 == "int volatile &&" ||
                  s3 == "int volatile && __ptr64" ) ;

    std::string const   s4 = breath::readable_type_name< int ( & )[ 10 ] >() ;
    BREATH_CHECK( s4 == "int (&) [10]" || s4 == "int (&)[10]" ||
                  s4 == "int (& __ptr64)[10]" ) ;

    std::string const   s5 = breath::readable_type_name< double ( * )( long )
                                                       >() ;
    BREATH_CHECK( s5 == "double (*)(long)" || s5 == "double (__cdecl*)(long)") ;

    std::string const   s6 = breath::readable_type_name< my_template< int >
                                                       >() ;

    BREATH_CHECK( s6 == "my_template<int>" || s6 == "class my_template<int>") ;
}

void
test_with_polymorphic_type()
{
    std::unique_ptr< my_base const > const
                        u( std::make_unique< my_derived const >() ) ;
    std::string const   s = breath::readable_type_name( *u ) ;
    BREATH_CHECK( s == "my_derived" || s == "class my_derived" ) ;
}

}

int
test_readable_type_name()
{
    using namespace breath ;

    return test_runner::instance().run( "readable_type_name()",
                                        { do_tests,
                                          test_with_polymorphic_type } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
