// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief CRC-32, as used by Ethernet, Serial ATA, PKZIP, Gzip,
//!            Bzip2, PNG.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_K46CqplQJyZFGjsXe5vROIAJbKonAZ10
#define BREATH_GUARD_K46CqplQJyZFGjsXe5vROIAJbKonAZ10

#include <cstdint>

namespace breath {

//      crc32():
//      ========
//
//!     \return
//!         The CRC-32 of the sequence identified by <code>
//!         [ begin, end )</code>.
// -------------------------------------------------------------------------
template< typename InputIterator >
std::uint_fast32_t  crc32( InputIterator begin, InputIterator end ) ;

}

#include "brt/crc32.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
