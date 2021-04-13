// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A test exception.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0
#define BREEZE_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0

#include "breeze/top_level_namespace.hpp"
#include <iosfwd>
#include <stdexcept>

namespace breeze_ns {

class test_failure
    :   public std::logic_error
{
public:
                        test_failure( std::string const & message,
                                      char const * file_name,
                                      long line_number ) ;
    char const *        file_name() const noexcept ;
    long                line_number() const noexcept ;

private:
    char const *        m_file_name ;
    long                m_line_number ;
} ;

std::ostream &      operator <<( std::ostream &, test_failure const & ) ;

}

#endif
