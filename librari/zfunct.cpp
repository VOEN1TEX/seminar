#include <iostream>
#include <cstring>
#include <vector>

void ZFunct(std::string& str) noexcept {
  int len = str.size();
  std::vector<int> answer(len, 0);
  int right, left = right = 0;
  answer[0] = len;
  std::cout << answer[0] << ' ';

  for (int i = 1; i < len; ++i) {
    if (i <= right) {
      answer[i] = std::min(right - i, answer[i - left]);
    }

    while (i + answer[i] < len && str[answer[i]] == str[i + answer[i]]) {
      ++answer[i];
    }

    if (right < answer[i] + 1) {
      left = i;
      right = i + answer[i];
    }
    std::cout << answer[i] << ' ';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  ZFunct(str);
  return 0;
}