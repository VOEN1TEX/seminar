#include <iostream>
#include <vector>
#include <unordered_set>

enum Color { White, Grey, Black };

enum Condition { Cycle_is_not_find, Cycle_is_Find, Cycle_is_derived };

class Graph {
 private:
  std::vector<std::unordered_set<int>> matrix_;
  std::vector<Color> colors_;
  std::vector<int> cycle_;

 public:
  explicit Graph(int n) {
    matrix_ = std::vector<std::unordered_set<int>>(n);
    colors_ = std::vector<Color>(n, White);
  }

  void DFS(int v, Condition& condition_cycle) {
    if (colors_[v] == Black) {
      return;
    }
    colors_[v] = Grey;
    for (auto neighbor : matrix_[v]) {
      if (colors_[neighbor] == White) {
        DFS(neighbor, condition_cycle);
      } else if (colors_[neighbor] == Grey) {
        std::cout << "YES" << '\n';
        if (neighbor != v) {
          condition_cycle = Cycle_is_Find;
        } else {
          cycle_.push_back(v);
          condition_cycle = Cycle_is_derived;
        }
        colors_[neighbor] = White;
      }
      if (condition_cycle == Cycle_is_Find) {
        cycle_.push_back(v);
        condition_cycle = (colors_[v] != White ? Cycle_is_Find : Cycle_is_derived);
        break;
      }
      if (condition_cycle == Cycle_is_derived) {
        break;
      }
    }
    colors_[v] = Black;
  }

  void PrintCycle() {
    for (int i = cycle_.size() - 1; i >= 0; --i) {
      std::cout << cycle_[i] + 1 << ' ';
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
  return is;
}

int main() {
  int amount_vertexes, amount_edges;
  std::cin >> amount_vertexes >> amount_edges;
  Graph g(amount_vertexes);

  for (int i = 0; i < amount_edges; ++i) {
    std::cin >> g;
  }

  Condition cycle_condition = Cycle_is_not_find;
  for (int i = 0; !cycle_condition && i < amount_vertexes; ++i) {
    g.DFS(i, cycle_condition);
  }

  if (cycle_condition == Cycle_is_not_find) {
    std::cout << "NO";
  } else {
    g.PrintCycle();
  }
  return 0;
}