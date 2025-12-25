#include <iostream>
#include <cstddef>
#include <cctype>

void hi()
{
    std::cout << "<HI!>\n";
}

bool is_space(char c)
{
  return std::isspace(c);
}

std::istream& getword(std::istream& is, char* word, size_t k, bool(*c)(char))
{
  
}

size_t match(const char* word, const char* const* words, size_t k)
{
  
}

int main()
{
  const size_t cmds_count = 1;
  void(*cmds[1])() = {hi};
  const char* const cmds_text[] = {"hi"};
  constexpr size_t bsize = 255;
  char word[bsize + 1] = {};
  while (!(getword(std::cin, word, bsize, is_space).eof()))
  {
    if (std::cin.fail())
    {
      std::cerr << "< INVALID COMMAND >\n";
      return 1;
    }
    else if (size_t i = match(word, cmds_text, cmds_count) < cmds_count)
    {
      cmds[i]();
    }
    else
    {
      std::cerr << "< UNKNOWN COMMAND >\n";
    }
  }
}