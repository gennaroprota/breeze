// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <cstring>
#include <memory>

namespace breath {

template< typename To, typename From >
std::enable_if_t< sizeof( To ) == sizeof( From ) &&
                  std::is_trivially_copyable< To   >::value &&
                  std::is_trivially_copyable< From >::value,
To >
bit_cast( From const & from ) noexcept( noexcept( To() ) )
{
    //      Implementation rationale:
    //      -------------------------
    //
    //      We prefer to really construct an object of type To (this is
    //      the reason why our bit_cast is not unconditionally
    //      noexcept).
    //
    //      The author of the bit_cast proposal published an
    //      implementation which constructs just *storage* (suitably
    //      sized and aligned) for a To, then reinterpret_casts that
    //      storage to To &.
    //
    //      Fixing some minor mistakes in his implementation (and using
    //      alignas(), instead of std::aligned_storage), the idea is:
    //
    //        template< typename To, typename From >
    //        constexpr To
    //        bit_cast( From const & from ) noexcept
    //        {
    //            alignas( To ) unsigned char
    //                                storage[ sizeof( To ) ] ;
    //            std::memcpy( &storage[ 0 ], std::addressof( from ),
    //                         sizeof( To ) ) ;
    //        
    //            return *reinterpret_cast< To * >( &storage[ 0 ] ) ;
    //        }
    //
    //      But, here, we return a copy of an object of type To whose
    //      lifetime never started. Which seems UB to me. So I'm avoding
    //      such an implementation.
    // -----------------------------------------------------------------------
    std::remove_const_t< To >
                        t ;
    std::memcpy( std::addressof( t ), std::addressof( from ), sizeof t ) ;

    return t ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
