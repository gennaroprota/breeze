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

#include "breeze/cpu/get_cpuid_info.hpp"
#include "breeze/diagnostics/assert.hpp"
#include <cpuid.h>

namespace breeze_ns {

cpuid_result
get_cpuid_info( std::uint32_t eax, std::uint32_t ecx )
{
    cpuid_result        result ;
    bool is_supported = __get_cpuid_count( eax,
                                           ecx,
                                           &result.eax,
                                           &result.ebx,
                                           &result.ecx,
                                           &result.edx ) != 0 ;

    BREEZE_ASSERT( is_supported ) ;

    return result ;
}

}
