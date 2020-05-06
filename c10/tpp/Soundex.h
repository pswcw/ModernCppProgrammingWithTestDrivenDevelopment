#ifndef Soundex_h
#define Soundex_h

#include <string>

class Soundex {
public:
   std::string encode(const std::string& word) const {
      std::string code("");
      code += word[0];
      if (word[1])
         code += "100";
      else
         code += "000";
      return code;
   }
};
#endif
