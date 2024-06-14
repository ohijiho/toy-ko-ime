#include <string>

std::string encodeChar(char32_t c) {
  if (c < 0x80)
    return std::string({(char)c});
  else if (c < 0x800)
    return std::string({
        (char)(0xc0 | (c >> 6)),
        (char)(0x80 | (c & 0x3f)),
    });
  else if (c < 0x10000)
    return std::string({
        (char)(0xe0 | (c >> 12)),
        (char)(0x80 | ((c >> 6) & 0x3f)),
        (char)(0x80 | (c & 0x3f)),
    });
  else if (c < 0x200000)
    return std::string({
        (char)(0xf0 | (c >> 18)),
        (char)(0x80 | ((c >> 12) & 0x3f)),
        (char)(0x80 | ((c >> 6) & 0x3f)),
        (char)(0x80 | (c & 0x3f)),
    });
  else if (c < 0x4000000)
    return std::string({
        (char)(0xf8 | (c >> 24)),
        (char)(0x80 | ((c >> 18) & 0x3f)),
        (char)(0x80 | ((c >> 12) & 0x3f)),
        (char)(0x80 | ((c >> 6) & 0x3f)),
        (char)(0x80 | (c & 0x3f)),
    });
  else if (c < 0x80000000)
    return std::string({
        (char)(0xfc | (c >> 30)),
        (char)(0x80 | ((c >> 24) & 0x3f)),
        (char)(0x80 | ((c >> 18) & 0x3f)),
        (char)(0x80 | ((c >> 12) & 0x3f)),
        (char)(0x80 | ((c >> 6) & 0x3f)),
        (char)(0x80 | (c & 0x3f)),
    });
  abort();
}
