#ifndef Corrade_Utility_String_h
#define Corrade_Utility_String_h
/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class @ref Corrade::Utility::String
 */

#include <string>
#include <vector>

#include "Corrade/Containers/Array.h"
#include "Corrade/Utility/visibility.h"

#ifdef CORRADE_BUILD_DEPRECATED
#include "Corrade/Utility/Macros.h"
#endif

namespace Corrade { namespace Utility {

/** @brief %String utilities */
class CORRADE_UTILITY_EXPORT String {
    public:
        /**
         * @brief Whitespace characters
         *
         * Characters for which `std::isspace()` returns `true`. Equals to
         * <tt>" \t\f\v\r\n"</tt>.
         */
        static const std::string Whitespace;

        /**
         * @brief Byte-order marker (UTF-8)
         *
         * Equals to <tt>"\xEF\xBB\xBF"</tt>.
         */
        static const std::string Bom;

        String() = delete;

        /**
         * @brief Safely construct string from char array
         *
         * If @p string is `nullptr`, returns empty string.
         */
        static std::string fromArray(const char* string) {
            return string ? std::string{string} : std::string{};
        }

        /**
         * @brief Safely construct string from char array
         *
         * If @p string is `nullptr`, returns empty string. Otherwise takes
         * also @p length into account.
         */
        static std::string fromArray(const char* string, std::size_t length) {
            return string ? std::string{string, length} : std::string{};
        }

        /**
         * @brief Trim leading whitespace from string
         * @param string        %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * @see @ref rtrim(), @ref trim()
         */
        static std::string ltrim(std::string string, const std::string& characters = Whitespace);

        /**
         * @brief Trim trailing whitespace from string
         * @param string        %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * @see @ref ltrim(), @ref trim()
         */
        static std::string rtrim(std::string string, const std::string& characters = Whitespace);

        /**
         * @brief Trim leading and trailing whitespace from string
         * @param string        %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * Equivalent to `ltrim(rtrim(string))`.
         */
        static std::string trim(std::string string, const std::string& characters = Whitespace);

        /**
         * @brief Split string on given character
         * @param string            %String to split
         * @param delimiter         Delimiter
         */
        static std::vector<std::string> split(const std::string& string, char delimiter);

        /**
         * @brief Split string on given character and remove empty parts
         * @param string            %String to split
         * @param delimiter         Delimiter
         */
        static std::vector<std::string> splitWithoutEmptyParts(const std::string& string, char delimiter);

        #ifdef CORRADE_BUILD_DEPRECATED
        /** @copybrief splitWithoutEmptyParts()
         * @deprecated Use @ref Corrade::Utility::String::splitWithoutEmptyParts() "splitWithoutEmptyParts()"
         *      instead.
         */
        static CORRADE_DEPRECATED("use splitWithoutEmptyParts() instead") std::vector<std::string> split(const std::string& string, char delim, bool keepEmptyParts) {
            return keepEmptyParts ? split(string, delim) : splitWithoutEmptyParts(string, delim);
        }
        #endif

        /**
         * @brief Join strings with given character
         * @param strings           Strings to join
         * @param delimiter         Delimiter
         */
        static std::string join(const std::vector<std::string>& strings, char delimiter);

        /**
         * @brief Join strings with given character and remove empty parts
         * @param strings           Strings to join
         * @param delimiter         Delimiter
         */
        static std::string joinWithoutEmptyParts(const std::vector<std::string>& strings, char delimiter);

        /**
         * @brief Convert string to lowercase
         *
         * @attention Doesn't work with UTF-8.
         */
        static std::string lowercase(std::string string);

        /**
         * @brief Convert string to uppercase
         *
         * @attention Doesn't work with UTF-8.
         */
        static std::string uppercase(std::string string);

        /** @brief Whether the string has given prefix */
        static bool beginsWith(const std::string& string, const std::string& prefix) {
            return beginsWithInternal(string, {prefix.data(), prefix.size()});
        }

        /** @overload */
        template<std::size_t size> static bool beginsWith(const std::string& string, const char(&prefix)[size]) {
            return beginsWithInternal(string, {prefix, size - 1});
        }

        /** @brief Whether the string has given suffix */
        static bool endsWith(const std::string& string, const std::string& suffix) {
            return endsWithInternal(string, {suffix.data(), suffix.size()});
        }

        /** @overload */
        template<std::size_t size> static bool endsWith(const std::string& string, const char(&suffix)[size]) {
            return endsWithInternal(string, {suffix, size - 1});
        }

    private:
        static bool beginsWithInternal(const std::string& string, Containers::ArrayReference<const char> prefix);
        static bool endsWithInternal(const std::string& string, Containers::ArrayReference<const char> suffix);
};

}}

#endif
