// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breeze_ns {

template< typename StreamBufferType >
StreamBufferType *
stream_buffer_wrapper< StreamBufferType >::stream_buffer()
{
    return &m_buffer;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
