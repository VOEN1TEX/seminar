#include <iostream>
#include <vector>

struct Node {
  int key = 0;
  int priority = 0;

  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  Node(int key, int priority) : key(key), priority(priority) {
  }
};

std::pair<Node*, Node*> Split(Node* root, int key);
Node* Merge(Node* left, Node* right);
Node* Insert(Node* root, int key, int value);
Node* Build(std::vector<std::pair<int, int>>& values, Node** nodes);

void PrintResult(Node* element);
void Clear(Node** nodes, int size);
std::ostream& operator<<(std::ostream& out, Node* element);

int main() {
  int amount;
  std::cin >> amount;
  std::vector<std::pair<int, int>> values;
  auto nodes = new Node*[amount];

  for (int i = 0; i < amount; ++i) {
    int key, priority;
    std::cin >> key >> priority;
    values.push_back({i + 1, priority});
  }

  std::cout << "YES" << '\n';
  Node* tree = Build(values, nodes);
  PrintResult(tree);
  Clear(nodes, amount);
  delete[] nodes;
  return 0;
}

std::ostream& operator<<(std::ostream& out, Node* element) {
  if (element != nullptr) {
    out << (element->parent == nullptr ? 0 : element->parent->key) << ' ';
    out << (element->left == nullptr ? 0 : element->left->key) << ' ';
    out << (element->right == nullptr ? 0 : element->right->key) << '\n';
  }

  return out;
}

std::pair<Node*, Node*> Split(Node* root, int key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }

  if (root->key < key) {
    std::pair<Node*, Node*> res = Split(root->right, key);
    root->right = res.first;
    res.first->parent = root;
    res.second->parent = nullptr;
    root->parent = nullptr;
    return {root, res.second};
  }

  std::pair<Node*, Node*> res = Split(root->left, key);
  root->left = res.second;
  res.second->parent = root;
  res.first->parent = nullptr;
  root->parent = nullptr;
  return {res.first, root};
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }

  if (right == nullptr) {
    return left;
  }

  if (left->priority > right->priority) {
    Node* res = left->right = Merge(left->right, right);
    res->parent = res;
    return left;
  }

  Node* res = right->left = Merge(left, right->left);
  res->parent = res;
  return right;
}

Node* Insert(Node* root, int key, int value) {
  Node* node = new Node{key, value};
  std::pair<Node*, Node*> splited = Split(root, root->key);
  Node* res = Merge(node, splited.second);
  return Merge(splited.first, res);
}

Node* Build(std::vector<std::pair<int, int>>& values, Node** nodes) {
  Node* root = nullptr;
  Node* last_inserted = nullptr;

  size_t i = 0;
  for (auto value : values) {
    Node* new_elem = new Node{value.first, value.second};
    nodes[i++] = new_elem;

    Node* curr = last_inserted;

    while (curr != nullptr && value.second < curr->priority) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      new_elem->left = root;

      if (root != nullptr) {
        root->parent = new_elem;
      }

      root = new_elem;
    } else {
      new_elem->left = curr->right;

      if (curr->right != nullptr) {
        curr->right->parent = new_elem;
      }

      curr->right = new_elem;
      new_elem->parent = curr;
    }

    last_inserted = new_elem;
  }

  return root;
}

void PrintResult(Node* element) {
  if (element != nullptr) {
    PrintResult(element->left);
    std::cout << element;
    PrintResult(element->right);
  }
}

void Clear(Node** nodes, int size) {
  for (int i = 0; i < size; ++i) {
    delete nodes[i];
  }
}