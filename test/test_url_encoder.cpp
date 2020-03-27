#include "catch.hpp"
#include "url_encoder.hpp"

TEST_CASE("Url Encoding", "[url_encoder]") {
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
    SECTION("Unicode") {
        std::string example = R"(引き割り)";
        std::string result = R"(%E5%BC%95%E3%81%8D%E5%89%B2%E3%82%8A)";
        auto url_e = url_encoder::encode(example);
        REQUIRE(url_e == result);
        auto url_d = url_encoder::decode(url_e);
        REQUIRE(url_d == example);
    }
}