#include <iostream>

std::size_t Strlen(const char* str) {
  std::size_t str_len = 0;

  while (str[str_len] != 0) {
    ++str_len;
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
  std::size_t curr = 0;

  for (; src[curr] != 0; ++curr) {
    dest[curr] = src[curr];
    ++curr;
  }

  dest[curr] = '\0';
  return dest;
}

char* Strncpy(char* dest, const char* src, std::size_t count) {
  std::size_t curr = 0;

  while (src[curr] != 0 && count > 0) {
    dest[curr] = src[curr];
    ++curr;
    --count;
  }

  while (count > 0) {
    dest[curr] = '\0';
    ++curr;
    --count;
  }

  return dest;
}

char* Strcat(char* dest, const char* src) {
  std::size_t curr = 0;

  while (dest[0] != 0) {
    ++curr;
  }

  while (*src != 0) {
    dest[curr] = *src;
    ++curr;
    ++src;
  }

  dest[curr] = '\0';
  return dest;
}

char* Strncat(char* dest, const char* src, std::size_t count) {
  std::size_t curr = 0;

  while (dest[curr] != 0) {
    ++curr;
  }

  while (*src != 0 && count != 0) {
    dest[curr] = *src;
    ++curr;
    ++src;
    --count;
  }

  while (count > 0) {
    dest[curr] = '\0';
    ++curr;
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
    std::size_t curr = 0;

    while (src[curr] != 0 && *dest != src[curr]) {
      ++curr;
    }

    if (src[curr] == 0) {
      return amount;
    }

    ++amount;
    ++dest;
  }

  return amount;
}

std::size_t Strcspn(const char* dest, const char* src) {
  std::size_t curr = 0;
  std::size_t amount = 0;

  while (dest[amount] != 0) {
    curr = 0;

    while (src[curr] != 0 && dest[amount] != src[curr]) {
      ++curr;
    }

    if (src[curr] != 0) {
      break;
    }

    ++amount;
  }

  return amount;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  std::size_t curr = 0;

  while (*dest != 0) {
    curr = 0;

    while (breakset[curr] != 0 && *dest != breakset[curr]) {
      ++curr;
    }

    if (breakset[curr] != 0) {
      break;
    }

    ++dest;
  }

  return (*dest == 0 ? nullptr : dest);
}

const char* Strstr(const char* str, const char* pattern) {
  while (*str != 0) {
    if (*str == *pattern) {
      std::size_t curr_str = 0;
      std::size_t curr_pattern = pattern - str;

      while (str[curr_str] != 0) {
        if (pattern[curr_pattern] == 0) {
          return str;
        }

        if (str[curr_str] != pattern[curr_pattern]) {
          break;
        }

        ++curr_pattern;
        ++curr_str;
      }

      if (str[curr_pattern] == 0) {
        return str;
      }

    }

    ++str;
  }

  return nullptr;
}