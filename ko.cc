#include "ko.hh"

static const char32_t tbl[26] = {
    /*a: ㅁ*/ 12609,
    /*b: ㅠ*/ 12640,
    /*c: ㅊ*/ 12618,
    /*d: ㅇ*/ 12615,
    /*e: ㄷ*/ 12599,
    /*f: ㄹ*/ 12601,
    /*g: ㅎ*/ 12622,
    /*h: ㅗ*/ 12631,
    /*i: ㅑ*/ 12625,
    /*j: ㅓ*/ 12627,
    /*k: ㅏ*/ 12623,
    /*l: ㅣ*/ 12643,
    /*m: ㅡ*/ 12641,
    /*n: ㅜ*/ 12636,
    /*o: ㅐ*/ 12624,
    /*p: ㅔ*/ 12628,
    /*q: ㅂ*/ 12610,
    /*r: ㄱ*/ 12593,
    /*s: ㄴ*/ 12596,
    /*t: ㅅ*/ 12613,
    /*u: ㅕ*/ 12629,
    /*v: ㅍ*/ 12621,
    /*w: ㅈ*/ 12616,
    /*x: ㅌ*/ 12620,
    /*y: ㅛ*/ 12635,
    /*z: ㅋ*/ 12619,
};

static const char32_t tblShift[26] = {
    /*A: ㅁ*/ 12609,
    /*B: ㅠ*/ 12640,
    /*C: ㅊ*/ 12618,
    /*D: ㅇ*/ 12615,
    /*E: ㄸ*/ 12600,
    /*F: ㄹ*/ 12601,
    /*G: ㅎ*/ 12622,
    /*H: ㅗ*/ 12631,
    /*I: ㅑ*/ 12625,
    /*J: ㅓ*/ 12627,
    /*K: ㅏ*/ 12623,
    /*L: ㅣ*/ 12643,
    /*M: ㅡ*/ 12641,
    /*N: ㅜ*/ 12636,
    /*O: ㅒ*/ 12626,
    /*P: ㅖ*/ 12630,
    /*Q: ㅃ*/ 12611,
    /*R: ㄲ*/ 12594,
    /*S: ㄴ*/ 12596,
    /*T: ㅆ*/ 12614,
    /*U: ㅕ*/ 12629,
    /*V: ㅍ*/ 12621,
    /*W: ㅉ*/ 12617,
    /*X: ㅌ*/ 12620,
    /*Y: ㅛ*/ 12635,
    /*Z: ㅋ*/ 12619,
};

/*
 * ㄱㄲㄳㄴㄵㄶㄷㄸㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅃㅄㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ
 * ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ
 * 가까나다따라마바빠사싸아자짜차카타파하
 * 가개갸걔거게겨계고과괘괴교구궈궤귀규그긔기
 * 가각갂갃간갅갆갇갈갉갊갋갌갍갎갏감갑값갓갔강갖갗갘같갚갛
 */

static const char32_t nCho = 19, nJung = 21, nJong = 28, nJa = 30;
static const char32_t ga = 44032, giyeok = 12593, ah = 12623;

static const char32_t tblJaFirst[nJa] = {
    /*ㄱ: ㄱ*/ 12593,
    /*ㄲ: ㄲ*/ 12594,
    /*ㄳ: ㄱ*/ 12593,
    /*ㄴ: ㄴ*/ 12596,
    /*ㄵ: ㄴ*/ 12596,
    /*ㄶ: ㄴ*/ 12596,
    /*ㄷ: ㄷ*/ 12599,
    /*ㄸ: ㄸ*/ 12600,
    /*ㄹ: ㄹ*/ 12601,
    /*ㄺ: ㄹ*/ 12601,
    /*ㄻ: ㄹ*/ 12601,
    /*ㄼ: ㄹ*/ 12601,
    /*ㄽ: ㄹ*/ 12601,
    /*ㄾ: ㄹ*/ 12601,
    /*ㄿ: ㄹ*/ 12601,
    /*ㅀ: ㄹ*/ 12601,
    /*ㅁ: ㅁ*/ 12609,
    /*ㅂ: ㅂ*/ 12610,
    /*ㅃ: ㅃ*/ 12611,
    /*ㅄ: ㅂ*/ 12610,
    /*ㅅ: ㅅ*/ 12613,
    /*ㅆ: ㅆ*/ 12614,
    /*ㅇ: ㅇ*/ 12615,
    /*ㅈ: ㅈ*/ 12616,
    /*ㅉ: ㅉ*/ 12617,
    /*ㅊ: ㅊ*/ 12618,
    /*ㅋ: ㅋ*/ 12619,
    /*ㅌ: ㅌ*/ 12620,
    /*ㅍ: ㅍ*/ 12621,
    /*ㅎ: ㅎ*/ 12622,
};

static const char32_t tblMoFirst[nJung] = {
    /*ㅏ: ㅏ*/ 12623,
    /*ㅐ: ㅐ*/ 12624,
    /*ㅑ: ㅑ*/ 12625,
    /*ㅒ: ㅒ*/ 12626,
    /*ㅓ: ㅓ*/ 12627,
    /*ㅔ: ㅔ*/ 12628,
    /*ㅕ: ㅕ*/ 12629,
    /*ㅖ: ㅖ*/ 12630,
    /*ㅗ: ㅗ*/ 12631,
    /*ㅘ: ㅗ*/ 12631,
    /*ㅙ: ㅗ*/ 12631,
    /*ㅚ: ㅗ*/ 12631,
    /*ㅛ: ㅛ*/ 12635,
    /*ㅜ: ㅜ*/ 12636,
    /*ㅝ: ㅜ*/ 12636,
    /*ㅞ: ㅜ*/ 12636,
    /*ㅟ: ㅜ*/ 12636,
    /*ㅠ: ㅠ*/ 12640,
    /*ㅡ: ㅡ*/ 12641,
    /*ㅢ: ㅡ*/ 12641,
    /*ㅣ: ㅣ*/ 12643,
};

static const char32_t tblCho[nJa] = {
    /*ㄱ*/ ga + 0 * nJung * nJong,
    /*ㄲ*/ ga + 1 * nJung *nJong,
    /*ㄳ*/ ga + 9 * nJung *nJong,
    /*ㄴ*/ ga + 2 * nJung *nJong,
    /*ㄵ*/ ga + 12 * nJung *nJong,
    /*ㄶ*/ ga + 18 * nJung *nJong,
    /*ㄷ*/ ga + 3 * nJung *nJong,
    /*ㄸ*/ ga + 4 * nJung *nJong,
    /*ㄹ*/ ga + 5 * nJung *nJong,
    /*ㄺ*/ ga + 0 * nJung *nJong,
    /*ㄻ*/ ga + 6 * nJung *nJong,
    /*ㄼ*/ ga + 7 * nJung *nJong,
    /*ㄽ*/ ga + 9 * nJung *nJong,
    /*ㄾ*/ ga + 16 * nJung *nJong,
    /*ㄿ*/ ga + 17 * nJung *nJong,
    /*ㅀ*/ ga + 18 * nJung *nJong,
    /*ㅁ*/ ga + 6 * nJung *nJong,
    /*ㅂ*/ ga + 7 * nJung *nJong,
    /*ㅃ*/ ga + 8 * nJung *nJong,
    /*ㅄ*/ ga + 9 * nJung *nJong,
    /*ㅅ*/ ga + 9 * nJung *nJong,
    /*ㅆ*/ ga + 10 * nJung *nJong,
    /*ㅇ*/ ga + 11 * nJung *nJong,
    /*ㅈ*/ ga + 12 * nJung *nJong,
    /*ㅉ*/ ga + 13 * nJung *nJong,
    /*ㅊ*/ ga + 14 * nJung *nJong,
    /*ㅋ*/ ga + 15 * nJung *nJong,
    /*ㅌ*/ ga + 16 * nJung *nJong,
    /*ㅍ*/ ga + 17 * nJung *nJong,
    /*ㅎ*/ ga + 18 * nJung *nJong,
};

static char32_t composeJa(char32_t a, char32_t b) {
  switch (((a - giyeok) << 8) | (b - giyeok)) {
  case 0x0014:
    return a + 2; // ㄳ
  case 0x0317:
    return a + 1; // ㄵ
  case 0x031d:
    return a + 2; // ㄶ
  case 0x0800:
    return a + 1; // ㄺ
  case 0x0810:
    return a + 2; // ㄻ
  case 0x0811:
    return a + 3; // ㄼ
  case 0x0814:
    return a + 4; // ㄽ
  case 0x081b:
    return a + 5; // ㄾ
  case 0x081c:
    return a + 6; // ㄿ
  case 0x081d:
    return a + 7; // ㅀ
  case 0x1114:
    return a + 2; // ㅄ
  default:
    return 0;
  }
}

static char32_t composeMo(char32_t a, char32_t b) {
  switch (((a - ah) << 8) | (b - ah)) {
  case 0x0800:
    return a + 1; // ㅘ
  case 0x0801:
    return a + 2; // ㅙ
  case 0x0814:
    return a + 3; // ㅚ
  case 0x0d04:
    return a + 1; // ㅝ
  case 0x0d05:
    return a + 2; // ㅞ
  case 0x0d14:
    return a + 3; // ㅟ
  case 0x1214:
    return a + 1; // ㅢ
  default:
    return 0;
  }
}

static const char32_t tblJong[nJa] = {
    /*ㄱ*/ 1,
    /*ㄲ*/ 2,
    /*ㄳ*/ 3,
    /*ㄴ*/ 4,
    /*ㄵ*/ 5,
    /*ㄶ*/ 6,
    /*ㄷ*/ 7,
    /*ㄸ*/ 0,
    /*ㄹ*/ 8,
    /*ㄺ*/ 9,
    /*ㄻ*/ 10,
    /*ㄼ*/ 11,
    /*ㄽ*/ 12,
    /*ㄾ*/ 13,
    /*ㄿ*/ 14,
    /*ㅀ*/ 15,
    /*ㅁ*/ 16,
    /*ㅂ*/ 17,
    /*ㅃ*/ 0,
    /*ㅄ*/ 18,
    /*ㅅ*/ 19,
    /*ㅆ*/ 20,
    /*ㅇ*/ 21,
    /*ㅈ*/ 22,
    /*ㅉ*/ 0,
    /*ㅊ*/ 23,
    /*ㅋ*/ 24,
    /*ㅌ*/ 25,
    /*ㅍ*/ 26,
    /*ㅎ*/ 27,
};

static char32_t composeChoJung(char32_t a, char32_t b) {
  return tblCho[a - giyeok] + (b - ah) * nJong;
}

static char32_t composeChoJungJong(char32_t a, char32_t b) {
  return a + tblJong[b - giyeok];
}

static char32_t tblInvCho[nCho] = {
    /*ㄱ*/ 12593,
    /*ㄲ*/ 12594,
    /*ㄴ*/ 12596,
    /*ㄷ*/ 12599,
    /*ㄸ*/ 12600,
    /*ㄹ*/ 12601,
    /*ㅁ*/ 12609,
    /*ㅂ*/ 12610,
    /*ㅃ*/ 12611,
    /*ㅅ*/ 12613,
    /*ㅆ*/ 12614,
    /*ㅇ*/ 12615,
    /*ㅈ*/ 12616,
    /*ㅉ*/ 12617,
    /*ㅊ*/ 12618,
    /*ㅋ*/ 12619,
    /*ㅌ*/ 12620,
    /*ㅍ*/ 12621,
    /*ㅎ*/ 12622,
};

void KoComposer::write(int c) {
  if (c == 127) {
    if (buf == 0) {
      emit(127);
    } else if (buf < ga) {
      buf = 0;
    } else if (last >= ah) {
      char32_t first = tblMoFirst[last - ah];
      if (first == last) {
        buf = last =
            tblInvCho[(buf - (last - ah) * nJong - ga) / (nJung * nJong)];
      } else {
        buf += (first - last) * nJong;
        last = first;
      }
    } else {
      char32_t first = tblJaFirst[last - giyeok];
      if (first == last) {
        buf -= tblJong[last - giyeok];
        last = ah + (buf - ga) / nJong % nJung;
      } else {
        buf += tblJong[first - giyeok] - tblJong[last - giyeok];
        last = first;
      }
    }

    return;
  }

  if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
    if (buf != 0)
      emit(buf);
    buf = 0;
    if (c != 0)
      emit((char32_t)c);
    return;
  }

  char32_t x;
  if (c >= 'a')
    x = tbl[c - 'a'];
  else
    x = tblShift[c - 'A'];

  if (buf == 0) {
    buf = last = x;
    return;
  }

  char32_t com = 0;

  if ((last < ah) == (x < ah)) {
    com = (x < ah ? composeJa : composeMo)(last, x);

    if (com == 0) {
      emit(buf);
      buf = last = x;
      return;
    }

    if (buf < ga) {
      buf = com;
    } else if (x >= ah) {
      buf += (com - last) * nJong;
    } else {
      buf += tblJong[com - giyeok] - tblJong[last - giyeok];
    }

    last = com;
    return;
  }

  if (x < ah) {
    if (buf < ga) {
      emit(buf);
      buf = last = x;
      return;
    }
    char32_t jong = tblJong[x - giyeok];
    if (jong == 0) {
      emit(buf);
      buf = last = x;
      return;
    }
    buf += jong;
    last = x;
    return;
  }

  if (buf >= ga) {
    char32_t first = tblJaFirst[last - giyeok];
    buf -= tblJong[last - giyeok];
    if (first != last) {
      buf += tblJong[first - giyeok];
    }

    emit(buf);
  }

  buf = composeChoJung(last, x);
  last = x;
}
