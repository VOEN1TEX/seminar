#include <iostream>
#include <memory>
#include <cstring>

enum Result { Random, Yes, No };

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

char* Reverse(char* str, int len) {
  for (int i = 0; i < len / 2; ++i) {
    std::swap(str[i], str[len - i - 1]);
  }

  return str;
}

int MaxPrefix(char* str, int len, int index) {
  if (str[0] == '#') {
    return 0;
  }

  auto pref = Prefix(str, len);
  while (index < len) {
    if (pref[index - 1] >= pref[index]) {
      int out = pref[index - 1];
      delete[] pref;
      pref = nullptr;
      return out;
    }

    ++index;
  }

  delete[] pref;
  return len - index;
}

Result Choose(int* answer, char* str, int& amount_ammo, int& len) {
  if (answer[len - 1] == amount_ammo - 1) {
    return Random;
  }

  int max_pref = MaxPrefix(str + answer[len - 1] + 1, len - answer[len - 1], amount_ammo - answer[len - 1] - 1);
  if (max_pref >= amount_ammo - answer[len - 1] - 2) {
    if (str[answer[len - 1]] == '1') {
      return Yes;
    }

    return No;
  }

  if (str[len - 1] == '1') {
    return Yes;
  }

  return No;
}

std::pair<int, int> Count(const char* str) {
  int units = 0;
  int nulls = 0;

  while (str[units + nulls] != 0) {
    if (str[units + nulls] == '1') {
      ++units;
    } else {
      ++nulls;
    }
  }
  return {units, nulls};
}

int main() {
  int amount_ammo;
  std::cin >> amount_ammo;

  auto str1 = new char[amount_ammo]{};
  auto str2 = new char[amount_ammo]{};

  std::cin >> str1;
  std::cin >> str2;

  std::pair<int, int> counter1 = Count(str1);
  std::pair<int, int> counter2 = Count(str2);

  if (counter1 != counter2) {
    std::cout << (counter1.first > counter2.first ? "Yes" : "No");
  } else {
    auto str = new char[amount_ammo * 2]{};
    std::strcat(str, str1);
    std::strcat(str, "#");
    std::strcat(str, str2);

    int len = amount_ammo * 2 - 1;
    auto answer = Prefix(str, len);
    Result result = Choose(answer, str, amount_ammo, len);

    if (result != Random) {
      delete[] answer;
      delete[] str;

      str = new char[amount_ammo * 2 + 2]{};
      std::strcat(str, Reverse(str1, amount_ammo - 1));
      std::strcat(str, "#");
      std::strcat(str, Reverse(str2, amount_ammo - 1));

      answer = Prefix(Reverse(str, len), len);
      result = (result == Choose(answer, str, amount_ammo, len) ? result : Random);
    }

    std::cout << (result == 0 ? "Random" : (result == 1 ? "Yes" : "No"));

    delete[] answer;
    delete[] str;
  }

  delete[] str1;
  delete[] str2;
  return 0;
}