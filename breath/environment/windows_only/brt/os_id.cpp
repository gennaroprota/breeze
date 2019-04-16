// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2007-2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/environment/windows_only/os_id.hpp"
#include "breath/environment/windows_only/windows_version_info.hpp"

#include <ostream>

namespace breath {

namespace {

// Attention: keep in sync with the declaration in [note 1]
static char const * const
                    names[] =
{
    "Unknown Windows variant",
    "Win32s on Windows 3.1",

    "Windows 95",
    "Windows 98",
    "Windows Me",

    "Windows NT",
    "Windows 2000",
    "Windows XP",
    "Windows Server 2003",
    "Windows Home Server",
    "Windows Storage Server 2003",
    "Windows Server 2003 R2",
    "Windows XP Professional x64 Edition",
    "Windows Vista",
    "Windows Server 2008",
    "Windows Server 2008 R2",
    "Windows 7",
    "Windows 8",
    "Windows Server 2012",
    "Windows 8.1",
    "Windows Server 2012 R2",
    "Windows 10",
    "Windows Server 2016"
} ;

}
// [note 1] Attention: keep in sync with the array declaration above
//
//    * windows_xp_professional_x64_edition is the only case where the
//      word "edition" appears directly as a part of the OS name,
//      rather than in the edition name (as in "Web Edition", "Home
//      Edition" etc.) -- what should we do? leave "edition" or not?
// --------------------------------------------------------------------------
os_id const
        os_id::windows_unknown                    ( 0 ),
        //
        // The numbers 1 to 5 were used by Win32s, Win95,
        // Win98, Win Me and Win NT which are no longer
        // supported. Do not eliminate the room here or the
        // corresponding array of strings will not work.
        //
        os_id::windows_2000                       ( 6 ),
        os_id::windows_xp                         ( 7 ),
        os_id::windows_server_2003                ( 8 ),
        os_id::windows_home_server                ( 9 ),
        os_id::windows_storage_server_2003        ( 10 ),
        os_id::windows_server_2003_r2             ( 11 ),
        os_id::windows_xp_professional_x64_edition( 12 ),  // gps leave "edition"?
        os_id::windows_vista                      ( 13 ),
        os_id::windows_server_2008                ( 14 ),
        os_id::windows_server_2008_r2             ( 15 ),
        os_id::windows_7                          ( 16 ),
        os_id::windows_8                          ( 17 ),
        os_id::windows_server_2012                ( 18 ),
        os_id::windows_8_1                        ( 19 ),
        os_id::windows_server_2012_r2             ( 20 ),
        os_id::windows_10                         ( 21 ),
        os_id::windows_server_2016                ( 22 )
    ;


os_id::os_id( os_id::id_type n )
    : m_id( n )
{
}

bool
os_id::is_equal( os_id const & other ) const
{
    return m_id == other.m_id ;
}

std::ostream &
operator <<( std::ostream & dest, os_id const & id )
{
    dest << breath::names[ id.m_id ] ;

    windows_version_info const
                        info ;
    std::string const   edition = info.edition() ;
    if ( ! edition.empty() ) {
        dest << ' ' << edition ;
    }

    int const           sp = windows_version_info::service_pack_level() ;
    if ( sp != 0 ) {
        dest << "Service Pack " << sp ;
    }

    if ( windows_version_info::is_64_bit() ) {
        dest << ", 64-bit" ;
    }


    return dest << " (" << info.major_version() << '.' << info.minor_version()
                << ", build " << info.build_number() << ')' ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
