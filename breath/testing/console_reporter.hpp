// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An object to report unit tests errors to a \c
//!            std::ostream.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB
#define BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB

#include "breath/testing/test_reporter.hpp"
#include <iosfwd>

namespace breath {

//      console_reporter:
//      =================
//
class console_reporter
    :   public test_reporter
{
public:
    //      Declare this explicitly to avoid Visual C++ C4626 (and
    //      C5027).
    // -----------------------------------------------------------------------
    void                operator =( console_reporter const & ) = delete ;

    explicit            console_reporter( std::ostream & os ) ;

    virtual void        on_all_tests_begin() override ;
    virtual void        on_all_tests_end() override ;
    virtual void        on_test_begin( int test_number,
                                        char const * name = "" ) override ;
    virtual void        on_test_passed( int test_number ) override ;
    virtual void        on_test_failed( int test_number,
                                        test_exception const & ) override ;
    virtual void        on_unexpected_exception( int test_number ) override ;
    virtual void        on_unexpected_exception( int test_number,
                                                  std::exception const & )
                                                                      override ;

private:
    std::ostream &      m_stream ;
    unsigned            m_passed ;
    unsigned            m_failed ;
    unsigned            m_unexpected_exceptions ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
