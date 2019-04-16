// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/cpu/cpuid.hpp"
#include "breath/diagnostics/assert.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

namespace {

bool
has_processor_brand_string()
{
    if ( ! is_cpuid_supported() ) {
        return false ;
    }

    unsigned const      mask = 0x8000'0000 ;
    cpuid_result const  r = get_cpuid_info( mask, 0 ) ;

    return (r.eax & mask) != 0 &&
        r.eax >= (mask + 4) ;
}

std::string
processor_brand_string()
{
    BREATH_ASSERT( is_cpuid_supported() ) ;

    // Reference: Intel Manual, 3-176, Vol. 2A
    //
    unsigned long const from = 0x8000'0002 ;
    unsigned long const to   = 0x8000'0004 ;

    std::size_t const   len = 16 * ( to - from + 1 ) ;
    char                s[ len ] ;
    for ( unsigned long i = from ; i <= to ; ++ i ) {
        cpuid_result const  info = get_cpuid_info( i, 0 ) ;
        char * const        p = s + 16 * ( i - from ) ;
        std::memcpy( p,      &info.eax, sizeof( info.eax ) ) ;
        std::memcpy( p + 4,  &info.ebx, sizeof( info.ebx ) ) ;
        std::memcpy( p + 8,  &info.ecx, sizeof( info.ecx ) ) ;
        std::memcpy( p + 12, &info.edx, sizeof( info.edx ) ) ;
    }
    return std::string( s ) ;
}

std::string
cpu_vendor_id_string()
{
    BREATH_ASSERT( is_cpuid_supported() ) ;

    cpuid_result const  r = get_cpuid_info( 0, 0 ) ;

    int const           len = 12 ;
    char                id_string[ len ] ;
    *reinterpret_cast< int * >( id_string + 0 ) = r.ebx ;
    *reinterpret_cast< int * >( id_string + 4 ) = r.edx ;
    *reinterpret_cast< int * >( id_string + 8 ) = r.ecx ;
    return std::string( id_string, len ) ;
}

}

int
main()
{
    if ( ! is_cpuid_supported() ) {
        std::cerr << "CPUID instruction not available" << std::endl ;
        return EXIT_FAILURE ;
    }

    std::cout << "CPU vendor ID string: " <<
                     cpu_vendor_id_string() << std::endl ;
    std::cout << "Processor brand string: " << ( has_processor_brand_string()
                                                    ? processor_brand_string()
                                                    : "<not available>" )
                                            << std::endl ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
