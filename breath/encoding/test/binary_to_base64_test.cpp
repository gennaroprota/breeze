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

#include "breath/encoding/binary_to_base64.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
#include <string>
#include <iterator>
#include <iostream>

void
check()
{
    //  A bunch of known Base64 encodings. Some from RFC 3548, some
    //  from RFC 4648 and some verified with:
    //      <https://www.base64encode.org/>.
    //  The latter is not an authoritative reference but I wanted some
    //  more test vectors.
    //  ----------------------------------------------------------------
    struct
    {
        std::string binary ;
        std::string b64 ;
    } const             known[] =
    {
        { "A", "QQ==" },
        { "b", "Yg==" },
        { "AB", "QUI=" },
        { "ABC", "QUJD" },
        { "Hello", "SGVsbG8=" },
        { "Hello, world",  "SGVsbG8sIHdvcmxk" },
        { "Hello, world!", "SGVsbG8sIHdvcmxkIQ==" },
        { "\x14\xfb\x9c\x03\xd9\x7e", "FPucA9l+" },// this example from RFC 3548
        { "\x14\xfb\x9c\x03\xd9",     "FPucA9k=" },//   "     "      "  RFC 3548
        { "\x14\xfb\x9c\x03",         "FPucAw==" },//   "     "      "  RFC 3548
        { "", "" },                                // this example from RFC 4648
        { "f", "Zg==" },                           //   "     "      "  RFC 4648
        { "fo", "Zm8=" },                          //   "     "      "  RFC 4648
        { "foo", "Zm9v" },                         //   "     "      "  RFC 4648
        { "foob", "Zm9vYg==" },                    //   "     "      "  RFC 4648
        { "fooba", "Zm9vYmE=" },                   //   "     "      "  RFC 4648
        { "foobar", "Zm9vYmFy" },                  //   "     "      "  RFC 4648
        { "Long string long string long string long string",
          "TG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmcgbG9uZyBzdHJpbmc=" },
        { "The quick brown fox jumps over the lazy dog",
          "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="},
        { "Pack my box with five dozen liquor jugs",
          "UGFjayBteSBib3ggd2l0aCBmaXZlIGRvemVuIGxpcXVvciBqdWdz" },
        { "The five boxing wizards jump quickly",
          "VGhlIGZpdmUgYm94aW5nIHdpemFyZHMganVtcCBxdWlja2x5" }
    } ;

    for ( auto it = breath::cbegin( known ) ; it != breath::cend( known ) ; ++ it ) {
        std::string         out ;
        breath::binary_to_base64( it->binary.cbegin(), it->binary.cend(),
                                    std::back_inserter( out ) ) ;
        BREATH_CHECK( out == it->b64 ) ;
    }
}

void
check_string_of_nuls()
{
    std::string const   s = { '\0', '\0' } ;
    std::string         out ;
    breath::binary_to_base64( s.cbegin(), s.cend(),
                              std::back_inserter( out ) ) ;
    // this one checked with base64 8.25 under Cygwin
    BREATH_CHECK( out == "AAA=" ) ;
}

void
check_line_wrap()
{
    std::string const   s =
        "Nel mezzo del cammin di nostra vita\n"
        "mi ritrovai per una selva oscura\n"
        "che' la diritta via era smarrita.\n"
          "Ahi quanto a dir qual era e' cosa dura\n"
        "esta selva selvaggia e aspra e forte\n"
        "che nel pensier rinova la paura!\n"
          "Tant'e' amara che poco e' piu' morte;\n"
        "ma per trattar del ben ch'i' vi trovai,\n"
        "diro' de l'altre cose ch'i' v'ho scorte.\n"
        "Io non so ben ridir com'i' v'intrai,\n"
        "tant'era pien di sonno a quel punto\n"
        "che la verace via abbandonai.\n"
          "Ma poi ch'i' fui al pie' d'un colle giunto,\n"
        "la' dove terminava quella valle\n"
        "che m'avea di paura il cor compunto,\n"
        "guardai in alto, e vidi le sue spalle\n"
        "vestite gia' de' raggi del pianeta\n"
        "che mena dritto altrui per ogne calle.\n"
          "Allor fu la paura un poco queta\n"
        "che nel lago del cor m'era durata\n"
        "la notte ch'i' passai con tanta pieta." ;

    std::string         out ;
    int const           wrap_column = 72 ;
    breath::binary_to_base64( s.cbegin(), s.cend(),
                              std::back_inserter( out ), wrap_column ) ;
    // This one self-verified
    //
    BREATH_CHECK( out ==
    "TmVsIG1lenpvIGRlbCBjYW1taW4gZGkgbm9zdHJhIHZpdGEKbWkgcml0cm92YWkgcGVyIHVu\n"
    "YSBzZWx2YSBvc2N1cmEKY2hlJyBsYSBkaXJpdHRhIHZpYSBlcmEgc21hcnJpdGEuCkFoaSBx\n"
    "dWFudG8gYSBkaXIgcXVhbCBlcmEgZScgY29zYSBkdXJhCmVzdGEgc2VsdmEgc2VsdmFnZ2lh\n"
    "IGUgYXNwcmEgZSBmb3J0ZQpjaGUgbmVsIHBlbnNpZXIgcmlub3ZhIGxhIHBhdXJhIQpUYW50\n"
    "J2UnIGFtYXJhIGNoZSBwb2NvIGUnIHBpdScgbW9ydGU7Cm1hIHBlciB0cmF0dGFyIGRlbCBi\n"
    "ZW4gY2gnaScgdmkgdHJvdmFpLApkaXJvJyBkZSBsJ2FsdHJlIGNvc2UgY2gnaScgdidobyBz\n"
    "Y29ydGUuCklvIG5vbiBzbyBiZW4gcmlkaXIgY29tJ2knIHYnaW50cmFpLAp0YW50J2VyYSBw\n"
    "aWVuIGRpIHNvbm5vIGEgcXVlbCBwdW50bwpjaGUgbGEgdmVyYWNlIHZpYSBhYmJhbmRvbmFp\n"
    "LgpNYSBwb2kgY2gnaScgZnVpIGFsIHBpZScgZCd1biBjb2xsZSBnaXVudG8sCmxhJyBkb3Zl\n"
    "IHRlcm1pbmF2YSBxdWVsbGEgdmFsbGUKY2hlIG0nYXZlYSBkaSBwYXVyYSBpbCBjb3IgY29t\n"
    "cHVudG8sCmd1YXJkYWkgaW4gYWx0bywgZSB2aWRpIGxlIHN1ZSBzcGFsbGUKdmVzdGl0ZSBn\n"
    "aWEnIGRlJyByYWdnaSBkZWwgcGlhbmV0YQpjaGUgbWVuYSBkcml0dG8gYWx0cnVpIHBlciBv\n"
    "Z25lIGNhbGxlLgpBbGxvciBmdSBsYSBwYXVyYSB1biBwb2NvIHF1ZXRhCmNoZSBuZWwgbGFn\n"
    "byBkZWwgY29yIG0nZXJhIGR1cmF0YQpsYSBub3R0ZSBjaCdpJyBwYXNzYWkgY29uIHRhbnRh\n"
    "IHBpZXRhLg==" ) ;
}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check,
                                          check_string_of_nuls,
                                          check_line_wrap } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
