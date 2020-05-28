// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/memory/amount_of_physical_memory.hpp"
#include "breath/conversion/bit_cast.hpp"
#include "breath/diagnostics/last_api_error.hpp"

#define UNICODE
#include <Windows.h>

namespace breath {

unsigned long long
amount_of_physical_memory()
{
    //      This implementation uses GetPhysicallyInstalledSystemMemory(),
    //      if available, with a fallback to GlobalMemoryStatusEx().
    //      The fallback is to make the function work pre Vista SP1.
    //      However, only the first API gives an accurate value.
    // -----------------------------------------------------------------------
    HMODULE const       module = GetModuleHandle( L"kernel32" ) ;

    typedef BOOL ( WINAPI * fn_ptr_type )( ULONGLONG * ) ;

    fn_ptr_type const   get_physical_memory = module == NULL
                                ? nullptr
                                : breath::bit_cast< fn_ptr_type >(
             GetProcAddress( module, "GetPhysicallyInstalledSystemMemory" ) ) ;
    ULONGLONG           amount ;
    if ( get_physical_memory == nullptr
        || get_physical_memory( &amount ) == 0 ) {
        MEMORYSTATUSEX      status ;
        status.dwLength = sizeof status ;
        if ( GlobalMemoryStatusEx( &status ) == 0 ) {
            throw last_api_error( "GlobalMemoryStatusEx() failed" ) ;
        }
        amount = status.ullTotalPhys / 1024 ;
    }
    return amount ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
