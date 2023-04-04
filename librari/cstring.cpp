#include <iostream>

std::size_t Strlen(const char* str) {
  std::size_t str_len = 0;
  const char* curr_str = str;
  while (*curr_str != 0) {
    ++str_len;
    ++curr_str;
  }
  return str_len;
}

int Strcmp(const char* first, const char* second) {
  while (*first != 0 && *second != 0 && *first == *second) {
    ++first;
    ++second;
  }
  return *first - *second;
}

int Strncmp(const char* first, const char* second, std::size_t count) {
  while (*second != 0 && *first != 0 && *first == *second && count > 0) {
    ++first;
    ++second;
    --count;
  }
  return (count == 0 ? 0 : *first - *second);
}

char* Strcpy(char* dest, const char* src) {
  char* curr_dest = dest;
  while (*src != 0) {
    *curr_dest = *src;
    ++curr_dest;
    ++src;
  }
  *curr_dest = '\0';
  return dest;
}

char* Strncpy(char* dest, const char* src, std::size_t count) {
  char* curr_dest = dest;
  while (*src != 0 && count > 0) {
    *curr_dest = *src;
    ++curr_dest;
    ++src;
    --count;
  }
  while (count > 0) {
    *curr_dest = '\0';
    ++curr_dest;
    --count;
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  char* curr_dest = dest;
  while (*curr_dest != 0) {
    ++curr_dest;
  }
  while (*src != 0) {
    *curr_dest = *src;
    ++curr_dest;
    ++src;
  }
  *curr_dest = '\0';
  return dest;
}

char* Strncat(char* dest, const char* src, std::size_t count) {
  char* curr_dest = dest;
  while (*curr_dest != 0) {
    ++curr_dest;
  }
  while (*src != 0 && count != 0) {
    *curr_dest = *src;
    ++curr_dest;
    ++src;
    --count;
  }
  while (count > 0) {
    *curr_dest = '\0';
    ++curr_dest;
    --count;
  }
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  while (*str != 0 && (*str != symbol)) {
    ++str;
  }
  return (*str == symbol ? str : nullptr);
}

const char* Strrchr(const char* str, char symbol) {
  const char* last = nullptr;
  while (*str != 0) {
    if (*str == symbol) {
      last = str;
    }
    ++str;
  }
  return (symbol == '\0' ? str : last);
}

std::size_t Strspn(const char* dest, const char* src) {
  std::size_t amount = 0;
  while (*dest != 0) {
    const char* curr_src = src;
    while (*curr_src != 0 && *dest != *curr_src) {
      ++curr_src;
    }
    if (*curr_src == 0) {
      return amount;
    }
    ++amount;
    ++dest;
  }
  return amount;
}

std::size_t Strcspn(const char* dest, const char* src) {
  const char* curr_dest = dest;
  const char* curr_src = src;
  std::size_t amount = 0;
  while (*curr_dest != 0) {
    while (*curr_src != 0 && *curr_dest != *curr_src) {
      ++curr_src;
    }
    if (*curr_src != 0) {
      return amount;
    }
    ++amount;
    curr_src = src;
    ++curr_dest;
  }
  return amount;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  const char* curr_dest = dest;
  const char* curr_breakset = breakset;
  while (*curr_dest != 0) {
    while (*curr_breakset != 0 && *curr_dest != *curr_breakset) {
      ++curr_breakset;
    }
    if (*curr_breakset != 0) {
      return curr_dest;
    }
    curr_breakset = breakset;
    ++curr_dest;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  if (Strlen(pattern) == 0) {
    return str;
  }
  if (Strlen(str) < Strlen(pattern)) {
    return nullptr;
  }
  while (*str != 0) {
    if (*str == *pattern) {
      const char* curr_str = str;
      const char* curr_pattern = pattern;
      while (*curr_str != 0) {
        if (*curr_pattern == 0) {
          return str;
        }
        if (*curr_str != *curr_pattern) {
          break;
        }
        ++curr_pattern;
        ++curr_str;
      }
      if (*curr_pattern == 0) {
        return str;
      }
    }
    ++str;
  }
  return nullptr;
}

int main() {
  char s[10] = "\0";
  std::cout << Strchr(s, '\0') - s;
  return 0;
} 