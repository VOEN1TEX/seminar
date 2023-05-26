#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <limits>

enum Color { White, Grey, Black };

class Graph {
 private:
  std::vector<std::unordered_set<int>> matrix_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::set<int> answer_;
  int time_ = 0;

 public:
  std::vector<Color> colors_;

  explicit Graph(int n) {
    matrix_ = std::vector<std::unordered_set<int>>(n);
    colors_ = std::vector<Color>(n, White);
    time_in_ = std::vector<int>(n, std::numeric_limits<int>::max());
    time_up_ = std::vector<int>(n, std::numeric_limits<int>::max());
  }

  void DFS(int v, bool is_root) {
    colors_[v] = Grey;
    time_in_[v] = time_up_[v] = ++time_;
    int amount_child = 0;

    for (auto neighbor : matrix_[v]) {
      if (colors_[neighbor] == Grey) {
        time_up_[v] = std::min(time_up_[v], time_in_[neighbor]);
      }

      if (colors_[neighbor] == White) {
        ++amount_child;
        DFS(neighbor, false);
        time_up_[v] = std::min(time_up_[v], time_up_[neighbor]);

        if (!is_root && time_in_[v] <= time_up_[neighbor]) {
          answer_.insert(v);
        }
      }
    }

    if (is_root && amount_child >= 2) {
      answer_.insert(v);
    }

    colors_[v] = Black;
  }

  void Print() {
    std::cout << answer_.size() << '\n';

    for (auto result : answer_) {
      std::cout << result + 1 << '\n';
    }
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;
  g.matrix_[begin].insert(end);
  g.matrix_[end].insert(begin);
  return is;
}

int main() {
  int amount_vertexes, amount_edges;
  std::cin >> amount_vertexes >> amount_edges;
  Graph g(amount_vertexes);

  for (int i = 0; i < amount_edges; ++i) {
    std::cin >> g;
  }

  for (int i = 0; i < amount_vertexes; ++i) {
    if (g.colors_[i] == White) {
      g.DFS(i, true);
    }
  }

  g.Print();

  return 0;
}