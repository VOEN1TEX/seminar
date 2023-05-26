#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class Edge {
 public:
  int vertex_ = 0;
  int weight_ = 0;

  Edge() = default;
  Edge(int vertex, int weight) : vertex_(vertex), weight_(weight) {  //NOLINT
  }
};

bool operator<(Edge& first, Edge& second) {
  return first.weight_ > second.weight_;
}

bool operator==(const Edge& first, const Edge& second) {
  return first.weight_ == second.weight_ && first.vertex_ == second.vertex_;
}

class Graph {
 private:
  std::vector<std::vector<Edge>> list_;
  std::vector<int> dist_;
  std::vector<Edge> prev_;
  int answer_ = 0;

 public:
  explicit Graph(int n) {
    list_ = std::vector<std::vector<Edge>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    prev_ = std::vector<Edge>(n, {-1, -1});
  }

  void Prim() {
    std::vector<Edge> heap;
    heap.emplace_back(Edge{0, 0});

    while (!heap.empty()) {
      std::pop_heap(heap.begin(), heap.end());
      Edge v = heap.back();
      heap.pop_back();

      if (prev_[v.vertex_] == Edge{-1, -1}) {
        answer_ += v.weight_;
        prev_[v.vertex_] = v;
      }

      for (auto neighbor : list_[v.vertex_]) {
        if (prev_[neighbor.vertex_] == Edge{-1, -1} && neighbor.weight_ < dist_[neighbor.vertex_]) {
          dist_[neighbor.vertex_] = neighbor.weight_;
          heap.emplace_back(neighbor);
          std::push_heap(heap.begin(), heap.end());
        }
      }
    }
  }

  int Print() {
    return answer_;
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end, weight;
  is >> begin >> end >> weight;
  --begin;
  --end;
  g.list_[begin].emplace_back(Edge{end, weight});
  g.list_[end].emplace_back(Edge{begin, weight});
  return is;
}

int main() {
  int amount_vertexes, amount_edges;
  std::cin >> amount_vertexes >> amount_edges;

  Graph g(amount_vertexes);

  for (int i = 0; i < amount_edges; ++i) {
    std::cin >> g;
  }

  g.Prim();
  std::cout << g.Print();
  return 0;
}