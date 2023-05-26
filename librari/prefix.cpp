#include <iostream>
#include <cstring>

int* Prefix(const char* str, int& len) {
  auto answer = new int[len]{};

  for (int i = 1; i < len; ++i) {
    int k = answer[i - 1];

    while (str[i] != str[k] && k > 0) {
      k = answer[k - 1];
    }

    if (str[i] == str[k]) {
      answer[i] = k + 1;
    }
  }

  return answer;
}

int main() {
  char str[1000001];
  std::cin >> str;
  int len = std::strlen(str);
  auto answer = Prefix(str, len);

  for (int i = 0; i < len; ++i) {
    std::cout << answer[i] << ' ';
  }

  delete[] answer;
  return 0;
}