#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 public:
  using pair = std::pair<std::pair<int, int>, int>;
  explicit Graph(int n) {
    rank_ = std::vector<int>(n, 0);
    parents_ = std::vector<int>(n);

    for (int i = 0; i < n; ++i) {
        parents_[i] = i;
    }
  }
  
  int FindSet(int v) {
    if (v == parents_[v]) {
        return v;
    }

    return parents_[v] = FindSet(parents_[v]);
  }

  void Union(int v1, int v2) {
    v1 = FindSet(v1);
    v2 = FindSet(v2);
    
    if (rank_[v1] < rank_[v2]) {
      parents_[v1] = v2;
    } else if (rank_[v1] > rank_[v2]) {
      parents_[v2] = v1;
    } else {
      parents_[v1] = v2;
      rank_[v2]++;
    }
  }


  void Kraskal() {
    std::sort(weight_.begin(), weight_.end(), [](pair& first, pair& second) {
      return first.second < second.second;
    });

    for (auto vertex : weight_) {
      if (FindSet(vertex.first.first) != FindSet(vertex.first.second)) {
        Union(vertex.first.first, vertex.first.second);
        result_ += vertex.second;
      }
    }

  }

  int PrintResult() {
    return result_;
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

 private:
  std::vector<int> parents_;
  std::vector<int> rank_;
  std::vector<pair> weight_;
  int result_ = 0;
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end, weight;
  is >> begin >> end >> weight;
  --begin;
  --end;
  g.weight_.push_back({{begin, end}, weight});
  return is;
}

int main() {
  int amount_vertexes, amount_edges;
  std::cin >> amount_vertexes >> amount_edges;
  Graph g{amount_vertexes};

  for(int i = 0; i < amount_edges; ++i) {
    std::cin >> g;
  }

  g.Kraskal();
  std::cout << g.PrintResult();
  return 0;
}