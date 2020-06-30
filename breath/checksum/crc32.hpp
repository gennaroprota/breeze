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
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_K46CqplQJyZFGjsXe5vROIAJbKonAZ10
#define BREATH_GUARD_K46CqplQJyZFGjsXe5vROIAJbKonAZ10

#include "breath/top_level_namespace.hpp"
#include <cstdint>

namespace breath_ns {

//      crc32():
//      ========
//
//!     \return
//!         The CRC-32 of the sequence identified by <code>
//!         [begin, end)</code>.
//!
//!     \note
//!         I guess some applications might not have the whole sequence
//!         available, and need to calculate the CRC-32 in multiple
//!         steps. If so, I might add a third parameter, with a default
//!         to zero, for passing the CRC calculated in the previous
//!         step (thus "updating" it). Or I might transform this into a
//!         stateful functor.
// ---------------------------------------------------------------------------
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
