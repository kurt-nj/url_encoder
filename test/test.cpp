#include <iostream>

int hextob(unsigned char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    std::cout << "HUH?" << std::endl;
    return 0;
}

void run(std::string t) {
    std::string result;
    for(unsigned char c : t) {
        std::string output;

        static const char to_hex[17] = { "0123456789ABCDEF" };
        int first = c >> 4;
        int second = c & 0x0F;
        output.push_back('%');
        output.push_back(to_hex[first]);
        output.push_back(to_hex[second]);

        std::cout << output << std::endl;

        std::cout << output[1] << ":" << hextob(output[1]) << "-" << output[2] << ":" << hextob(output[2]) << std::endl;

        int val = (hextob(output[1]) << 4) + hextob(output[2]);
        result.push_back(static_cast<char>(val));
    }
    std::cout << "RESULT: " << result << std::endl;
}

int main(int argc, char *argv[])
{
    std::string first = "+";
    run(first);
    std::string second = "Ɣ";
    run(second);

}