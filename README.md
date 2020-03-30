# url_encoder
[![Build Status](https://travis-ci.org/kurt-nj/url_encoder.svg?branch=master)](https://travis-ci.org/kurt-nj/url_encoder)
[![codecov](https://codecov.io/gh/kurt-nj/url_encoder/branch/master/graph/badge.svg)](https://codecov.io/gh/kurt-nj/url_encoder)

Simple header only library that performs percent encoding as defined by [RFC 3986](https://tools.ietf.org/html/rfc3986).

## Compatibility

This library attempts to behave the same way as [libcurl](https://curl.haxx.se/libcurl/c/curl_easy_escape.html). 
If libcurl is available then a comparison unit test will be run.

## Usage

```cpp
std::string encoded = url_encoder::encode(input_text);
std::string decoded = url_encoder::deocde(encoded);
```
