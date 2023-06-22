#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>

class Graph {
 private:
  std::vector<std::unordered_set<int>> matrix_;
  std::vector<int> dist_;
  std::vector<int> parents_;

 public:
  explicit Graph(int n) {
    matrix_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  void BFS(int start) {
    --start;
    std::queue<int> queue;
    queue.push(start);
    dist_[start] = 0;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      for (auto neighbour : matrix_[curr]) {
        if (dist_[neighbour] > dist_[curr] + 1) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          queue.push(neighbour);
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  int Answer(int end) const noexcept {
    return dist_[end];
  }

  void Print(int index) const noexcept {
    if (dist_[index] != 0) {
      Print(parents_[index]);
    }
    std::cout << index + 1 << ' ';
  }

  bool Check(int end) const noexcept {
    return parents_[end] != -1 || dist_[end] == 0;
  }
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
  int start, end;
  std::cin >> start >> end;
  Graph g(amount_vertexes);

  for (int i = 0; i < amount_edges; ++i) {
    std::cin >> g;
  }

  g.BFS(start);
  if (g.Check(--end)) {
    std::cout << g.Answer(end) << '\n';
    g.Print(end);
  } else {
    std::cout << -1;
  }
  return 0;
}