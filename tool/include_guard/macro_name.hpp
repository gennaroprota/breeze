// ===========================================================================
//                     Copyright 2008-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_6wcoEyV5QUsnWplOvviqZvbfmnCMU19g
#define BREATH_GUARD_6wcoEyV5QUsnWplOvviqZvbfmnCMU19g

#include <string>

class macro_name_creation // this could be a scoped enum in C++11
{
public:
    enum exit_status { ok, could_not_release_entropy_source } ;
} ;

std::string         make_macro_name( std::string const & prefix,
                                     int random_part_length,
                                     macro_name_creation::exit_status * ) ;

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
