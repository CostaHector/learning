#pragma once
#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
namespace StringHelper {
    using str = std::string;
    inline str& strip(str& input) {
        static constexpr char WHITE_CHARS_ARRAY[] {" \t\n\r"};
        size_t start = input.find_first_not_of(WHITE_CHARS_ARRAY);
        size_t end = input.find_last_not_of(WHITE_CHARS_ARRAY);
        if (start == str::npos || end == str::npos) {
            input.clear();
        } else {
            input = input.substr(start, end - start + 1);
        }
        return input;
    }

}

#endif