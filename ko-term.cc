#include "ko.hh"
#include "unicode.hh"
#include <sys/termios.h>
#include <vector>

int main() {
  termios tio;
  tcgetattr(0, &tio);
  termios otio = tio;
  tio.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, TCSANOW, &tio);

  std::vector<char32_t> buf;
  KoComposer kc([&buf](char32_t c) { buf.push_back(c); });

  size_t psz = 0;

  for (;;) {
    int c = getchar();

    if (c < 27) {
      switch (c) {
      case EOF:
      case '\n':
      case '\t':
        break;
      case 4:
        c = EOF;
        break;
      default:
        continue;
      }
    }

    if (c == EOF || c == 27)
      kc.write(0);
    else
      kc.write(c);

    for (; psz; psz--)
      fputs("\b \b", stdout);

    for (auto x : buf) {
      if (x == 127)
        fputs("\b \b", stdout);
      else
        fputs(encodeChar(x).c_str(), stdout);
    }
    buf.clear();

    auto p = kc.pending();
    if (p != 0) {
      psz = 2;
      fputs(encodeChar(p).c_str(), stdout);
    }

    if (c == EOF)
      break;
  }

  tcsetattr(0, TCSANOW, &otio);

  return 0;
}
