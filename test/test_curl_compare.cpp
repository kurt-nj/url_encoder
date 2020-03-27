#include "catch.hpp"

#include <iostream>
#include <curl/curl.h>
#include "url_encoder.hpp"

std::string easy_unescape(CURL* curl_ptr, std::string const& input)
{
    int outlength;
    char* decoded = curl_easy_unescape(curl_ptr, input.c_str(), static_cast<int>(input.length()), &outlength);
    auto unescaped_str = std::string(decoded, static_cast<size_t>(outlength));
    curl_free(decoded);
    return unescaped_str;
}

std::string easy_escape(CURL* curl_ptr, std::string const& input)
{
    char *escaped = curl_easy_escape(curl_ptr, input.c_str(), static_cast<int>(input.length()));
    std::string escaped_str = std::string(escaped);
    curl_free(escaped);
    return escaped_str;
}


// Test normal encodings to see that both libs respond the same way
TEST_CASE("normal curl comparison", "[curl.normal]") {
    CURL* curl_ptr = curl_easy_init();

    SECTION("no escape") {
        std::string example = "~no_chars-to.escape~";
        auto curl_e = easy_escape(curl_ptr, example);
        auto url_e = url_encoder::encode(example);
        REQUIRE(curl_e == url_e);
        REQUIRE(url_e == example);

        auto curl_d = easy_unescape(curl_ptr, curl_e);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(curl_d == url_d);
        REQUIRE(url_d == example);
    }

    SECTION("Hello Günter") {
        std::string example = "Hello Günter";
        auto curl_e = easy_escape(curl_ptr, example);
        auto url_e = url_encoder::encode(example);
        REQUIRE(curl_e == url_e);
        std::cout << curl_e << " :: " << url_e << std::endl;

        auto curl_d = easy_unescape(curl_ptr, curl_e);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(curl_d == url_d);
        REQUIRE(url_d == example);
    }

    SECTION("International URL") {
        std::string example = R"(http://example.com/引き割り.html?query=param#fragment)";
        auto curl_e = easy_escape(curl_ptr, example);
        auto url_e = url_encoder::encode(example);
        REQUIRE(curl_e == url_e);
        std::cout << curl_e << " :: " << url_e << std::endl;

        auto curl_d = easy_unescape(curl_ptr, curl_e);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(curl_d == url_d);
        REQUIRE(url_d == example);
    }

    SECTION("Special Characters") {
        std::string example = R"($ & < > ? ; # : = , " ' ~ + %)";
        auto curl_e = easy_escape(curl_ptr, example);
        auto url_e = url_encoder::encode(example);
        REQUIRE(curl_e == url_e);
        std::cout << curl_e << " :: " << url_e << std::endl;

        auto curl_d = easy_unescape(curl_ptr, curl_e);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(curl_d == url_d);
        REQUIRE(url_d == example);
    }
}

// Test non standard encodings to see that both libs respond the same way to input that they
// could not have created
TEST_CASE("curl special decode", "[curl.decode]") {
    CURL* curl_ptr = curl_easy_init();

    SECTION("Non hex encoding") {
        std::string example = R"(%27bad_char%XX)";
        auto curl_d = easy_unescape(curl_ptr, example);
        auto url_d = url_encoder::decode(example);
        std::cout << curl_d << " :: " << url_d << std::endl;
        REQUIRE(curl_d == url_d);
    }

    SECTION("partial encoding") {
        std::string example = R"(%25bad%2_char%3)";
        auto curl_d = easy_unescape(curl_ptr, example);
        auto url_d = url_encoder::decode(example);
        std::cout << curl_d << " :: " << url_d << std::endl;
        REQUIRE(curl_d == url_d);
    }

    // not an error but not what curl does by default
    SECTION("lower case") {
        std::string example = R"(lower%3f_%3d_%2f%e5)";
        auto curl_d = easy_unescape(curl_ptr, example);
        auto url_d = url_encoder::decode(example);
        std::cout << curl_d << " :: " << url_d << std::endl;
        REQUIRE(curl_d == url_d);
    }
}
