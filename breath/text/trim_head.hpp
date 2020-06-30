// ===========================================================================
//                     Copyright 2011-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer (head of string).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL
#define BREATH_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL

#include "breath/top_level_namespace.hpp"
#include "breath/text/set_of_chars.hpp"
#include <locale>
#include <string>

namespace breath_ns {

std::string         trim_head( std::string const & str,
                               std::locale const & loc = std::locale() ) ;

std::string         trim_head( std::string const &  str,
                               set_of_chars const & to_remove ) ;
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
