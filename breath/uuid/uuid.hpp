// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Universally unique identifiers.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG
#define BREATH_GUARD_jjJFg8dCizQ6ClSYgT8Zsg2zo7zFYgfG

#include <cstdint>
#include <iosfwd>

namespace breath {

//      uuid:
//      =====
//
//!     A universally unique identifier.
// ---------------------------------------------------------------------------
class uuid
{
public:
    enum variant { reserved, rfc_4122, microsoft, future } ;
    enum version { time_based, dce_security, name_based_md5, pseudo_random,
                   name_based_sha1 } ;

                        uuid( variant, version ) ;

private:
    //      Note: the stream inserter assumes the largest type, here, is
    //      uint32_t. Keep in sync.
    // -----------------------------------------------------------------------
    uint32_t            m_time_low ;
    uint16_t            m_time_mid ;
    uint16_t            m_time_hi_and_version ;
    uint16_t            m_clock_seq ;
    uint8_t             m_node[ 6 ] ;

    //!     Outputs \c uu to the provided \c std::ostream, as prescribed
    //!     by RFC 4122 (in particular, the letters 'a' to 'f' are
    //!     output as lowercase).
    // -----------------------------------------------------------------------
    friend std::ostream & operator <<( std::ostream &, uuid const & uu ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
