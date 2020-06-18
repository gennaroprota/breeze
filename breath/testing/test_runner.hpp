// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An object to run unit tests.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE
#define BREATH_GUARD_ljsq7ok4MwSNNxMyfe6xf8RevjbF8jrE

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/process/exit_code.hpp"
#include "breath/testing/test_descriptor.hpp"
#include "breath/testing/test_exception.hpp"
#include "breath/testing/test_reporter.hpp"
#include <initializer_list>

namespace breath {

class test_runner
{
public:
    BREATH_DECLARE_NON_COPYABLE( test_runner )

private:
                    test_runner() ;

public:
    static test_runner &
                    instance() ;
    void            attach_reporter( test_reporter & ) ;
    template< typename TestDescriptorIterator >
    int             run( char const * group_description,
                         TestDescriptorIterator begin,
                         TestDescriptorIterator end ) ;
    int             run( char const * group_description,
                         std::initializer_list< test_descriptor > list ) ;

private:
    test_reporter * m_reporter ;
} ;

template< typename TestDescriptorIterator >
int
test_runner::run( char const * group_description,
                  TestDescriptorIterator begin,
                  TestDescriptorIterator end )
{
    int                 exit_code = breath::exit_success ;
    int                 test_number = 1 ;
    m_reporter->on_all_tests_begin( group_description ) ;
    for ( ; begin != end ; ++ begin, ++ test_number ) {
        try {
            m_reporter->on_test_begin( test_number ) ;
            (begin->function())() ;
            m_reporter->on_test_passed( test_number ) ;
        } catch ( test_exception const & ex ) {
            exit_code = breath::exit_failure ;
            m_reporter->on_test_failed( test_number, ex ) ;
        } catch ( std::exception const & ex ) {
            exit_code = breath::exit_failure ;
            m_reporter->on_unexpected_exception( test_number, ex ) ;
        } catch ( ... ) {
            exit_code = breath::exit_failure ;
            m_reporter->on_unexpected_exception( test_number ) ;
        }
    }
    m_reporter->on_all_tests_end() ;
    return exit_code ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
