#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>

class Graph {
 public:
  explicit Graph(int& n) {
    matrix_.resize(n, std::vector<int>(n));
    amount_ = n;
  }

  void Floyad() {
    for(size_t k = 0; k < amount_; ++k) {
      for (size_t x = 0; x < amount_; ++x) {
        for (size_t y = 0; y < amount_; ++y) {
          matrix_[x][y] = std::min(matrix_[x][y], (matrix_[x][k] + matrix_[k][y]));
        }
      }
    }
  }

  void Input() {
    for (size_t x = 0; x < amount_; ++x) {
      for (size_t y = 0; y < amount_; ++y) {
        std::cin >> matrix_[x][y];
      }
    }
  }

  void Print() {
    for(auto i : matrix_)  {
      for(auto k : i) {
        std::cout << k << ' ';
      }

      std::cout << '\n';
    }  
  }
 private:
  std::vector<std::vector<int>> matrix_;
  size_t amount_ = 0; 
};

int main() {
  int amount;
  std::cin >> amount;
  Graph g(amount);

  g.Input();
  g.Floyad();
  g.Print();
  return 0;
}