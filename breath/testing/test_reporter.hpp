// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A test reporter base class.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX
#define BREATH_GUARD_I2oO3QRDodQiGPSBaYNHr4wsSe5AloUX

#include "breath/top_level_namespace.hpp"
#include <exception>

namespace breath_ns {

class test_exception ;

class test_reporter
{
protected:
                        test_reporter() ;

public:
    //      Polymorphic classes other than exception classes should be
    //      non-copyable. (We don't use BREATH_DECLARE_NON_COPYABLE()
    //      here, because we don't want the testing facilities to be
    //      dependent on other parts of the library, although the
    //      dependency on something as simple and self-contained as
    //      BREATH_DECLARE_NON_COPYABLE() would be acceptable.)
    // -----------------------------------------------------------------------
                        test_reporter( test_reporter const & ) = delete ;
    void                operator =( test_reporter const & ) = delete ;

    void                on_all_tests_begin( char const * group_description ) ;
    void                on_all_tests_end() ;
    void                on_test_begin( int test_number,
                                       char const * name = "" ) ;
    void                on_test_passed( int test_number ) ;
    void                on_test_failed( int test_number,
                                        test_exception const & ) ;
    void                on_unexpected_exception( int test_number ) ;
    void                on_unexpected_exception( int test_number,
                                                 std::exception const & ) ;

    virtual             ~test_reporter() noexcept {}

private:
    virtual void        do_on_all_tests_begin( char const * group_description )
                                                                          = 0 ;
    virtual void        do_on_all_tests_end()   = 0 ;
    virtual void        do_on_test_begin( int test_number,
                                          char const * name ) = 0 ;
    virtual void        do_on_test_passed( int test_number ) = 0 ;
    virtual void        do_on_test_failed( int test_number,
                                           test_exception const & ) = 0 ;
    virtual void        do_on_unexpected_exception( int test_number ) = 0 ;
    virtual void        do_on_unexpected_exception( int test_number,
                                                 std::exception const & ) = 0 ;

} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
