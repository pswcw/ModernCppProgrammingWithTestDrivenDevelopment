#ifndef Soundex_h
#define Soundex_h

#include <string>

class Soundex {
public:
   std::string encode(const std::string& word) const {
      std::string code("");
      code += head(word) + encodeTail(word);
      return zeroPad(code);
   }

   char head(const std::string& word) const {
      return word[0];
   }

   std::string encodeTail(const std::string& word) const {
      if (word[1] == 0) return "";
      return "1";
   }

   std::string zeroPad(const std::string& code) const {
      return code + (hasEncodedCharacters(code) ? "00" : "000");
   }

   bool hasEncodedCharacters(const std::string& code) const {
      return code[1] != 0;
   }
};
#endif
