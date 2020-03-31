#ifndef URL_ENCODER_HPP
#define URL_ENCODER_HPP

/// Url Encoder
/// Simple percent encoding utilty compliant with RFC 3986.

#include <string>

namespace {
// Check if a character is unreserved
// https://tools.ietf.org/html/rfc3986#section-2.3
bool unreserve_char(char c) {
    switch(c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
        case '-': case '.': case '_': case '~':
            return true;
        default:
            return false;
    }
}

// Convert hex character integer
int hexc_to_int(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return -1;
}

// Convert integer to single hex character
// Only goes from 0 to 16
char int_to_hexc(int value) {
    static const char to_hex[17] =
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    return (value >= 0 && value < 16) ? to_hex[value] : 0;
}
} // anonymous namespace

namespace url_encoder {

/// URL Encode the input text and returns the encoded string
inline std::string encode(std::string const& input) {
    std::string output;
    for (char c : input) {
        // unreserved characters can be copied straight
        if (unreserve_char(c)) {
            output.push_back(c);
        }
        else {
            unsigned char uc = static_cast<unsigned char>(c);
            int first = uc >> 4;
            int second = uc & 0x0F;
            output.push_back('%');
            output.push_back(int_to_hexc(first));
            output.push_back(int_to_hexc(second));
        }
    }
    return output;
}

/// URL Decode the input text and returns the decoded string
inline std::string decode(std::string const& input) {
    std::string output;
    for(size_t x=0; x<input.size(); ++x) {
        char next = input[x];
        // if we find our encode char
        if (input[x] == '%' && x+2 < input.size()) {
            auto first = hexc_to_int(input[x+1]);
            auto second = hexc_to_int(input[x+2]);
            // if the next two values can be decoded, convert it and then move two spots
            if (first >= 0 && second >= 0) {
                int val = (first << 4) + second;
                output.push_back(static_cast<char>(val));
                x+=2;
            }
            // otherwise we have to skip this decoding
            else {
                output.push_back(next);
            }
        }
        else {
            output.push_back(next);
        }
    }
    return output;
}

} // url_encoder namespace

#endif // URL_ENCODER_HPP
