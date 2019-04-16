// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath {

template< typename Device >
timer< Device >::timer( start_mode mode )
    : m_device()
{
    if ( mode == auto_start) {
        restart() ;
    }
}

template< typename Device >
void
timer< Device >::restart()
{
    return m_device.restart() ;
}

template< typename Device >
typename timer< Device >::duration_type
timer< Device>::elapsed() const
{
    return m_device.elapsed() ;
}

template< typename Device >
typename timer< Device >::duration_type
timer< Device >::resolution() const
{
    return m_device.resolution() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
