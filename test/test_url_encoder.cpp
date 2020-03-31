#include "catch.hpp"
#include "url_encoder.hpp"

TEST_CASE("Url Encoding", "[url_encoder]") {

    SECTION("empty") {
        std::string example = "";
        auto url_e = url_encoder::encode(example);
        REQUIRE(url_e == example);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(url_d == example);
    }
    SECTION("No encoding") {
        std::string example = "~no_chars-to.escape~";
        auto url_e = url_encoder::encode(example);
        REQUIRE(url_e == example);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(url_d == example);
    }
    SECTION("Encoded URL") {
        std::string example = R"(http://example.com/path&q1=val?q2=val#fragment)";
        std::string result = R"(http%3A%2F%2Fexample.com%2Fpath%26q1%3Dval%3Fq2%3Dval%23fragment)";
        auto url_e = url_encoder::encode(example);
        REQUIRE(url_e == result);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(url_d == example);
    }
    SECTION("Lower Case") {
        std::string result = R"(http://example.com/path&q1=val?q2=val#fragment)";
        std::string example = R"(http%3a%2f%2fexample.com%2fpath%26q1%3dval%3fq2%3dval%23fragment)";
        auto res = url_encoder::decode(example);
        REQUIRE(res == result);
    }
    SECTION("Unicode") {
        std::string example = R"(引き割り)";
        std::string result = R"(%E5%BC%95%E3%81%8D%E5%89%B2%E3%82%8A)";
        auto url_e = url_encoder::encode(example);
        REQUIRE(url_e == result);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(url_d == example);
    }
    SECTION("Invalid Encoding") {
        // invalid percent encodings are ignored
        std::string example = R"(%GG)";
        auto result = url_encoder::decode(example);
        REQUIRE(result == example);
    }
}