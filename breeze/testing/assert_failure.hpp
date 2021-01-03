// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An exception class representing an assertion failure.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_d9dt4Uehn6MQi2IQwM3KigBOfFpQWbVT
#define BREEZE_GUARD_d9dt4Uehn6MQi2IQwM3KigBOfFpQWbVT

#include "breeze/top_level_namespace.hpp"
#include <exception>

namespace breeze_ns {

class assert_failure
    :   public std::exception
{
public:
    virtual char const *what() const noexcept override ;
} ;

}

#endif
