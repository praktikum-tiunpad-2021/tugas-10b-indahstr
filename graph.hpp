#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace strukdat {

template <typename VertexType>
class graph {
  /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
  using list_type = std::unordered_set<VertexType>;
  using adj_list_type = std::unordered_map<VertexType, list_type>;

 public:
  /**
   * @brief Default constructor.
   *
   * @constructor
   */
  graph() {}

  /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
  void add_vertex(const VertexType &val) {
    // Contoh implementasi. (BOLEH DIUBAH)
    // inisialisasi _adj_list[val] dengan list kosong
    _adj_list.insert(std::make_pair(val, list_type()));
  }

  void remove_vertex(const VertexType &val) {
    // TODO: Implementasikan!
    _adj_list.erase(val);
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    // TODO: Implementasikan!
    list_type &adj1 = _adj_list.at(val1), &adj2 = _adj_list.at(val2);
    
    auto it = adj1.find(val2);
    if (it == adj1.end()) {
      adj1.insert(val2);
    }
    it = adj2.find(val1);
    if (it == adj2.end()) {
      adj2.insert(val1);
    }
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    // TODO: Implementasikan!
    list_type &adj1 = _adj_list.at(val1), &adj2 = _adj_list.at(val2);
    
    auto it = adj1.find(val2);
    if (it != adj1.end()) {
      adj1.erase(it);
    }
    it = adj2.find(val1);
    if (it != adj2.end()) {
      adj2.erase(it);
    }
  }

  /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
  size_t order() const {
    // TODO: Implementasikan!
    return _adj_list.size();
  }

  /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
  bool is_edge(const VertexType &val1, const VertexType &val2) const {
    // TODO: Implementasikan!
    adj_list_type adjHelp = _adj_list;
    if (adjHelp.at(val1).find(val2) == adjHelp.at(val1).end()) {
      return false;
    } 
    if (adjHelp.at(val2).find(val1) == adjHelp.at(val2).end()) {
      return false;
    }
    return true;
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    // TODO: Implementasikan!
    adj_list_type adjHelp = _adj_list;
    std::unordered_map<VertexType,bool> visit;

    for (auto i = adjHelp.begin(); i != adjHelp.end(); ++i) {
      visit.insert(std::make_pair(i->first, false));
    }
    
    std::vector<VertexType> q;
    VertexType vHelp = root;
    q.push_back(vHelp);
    visit[vHelp] = true;

    while(!q.empty()) {
      vHelp = q.front();
      q.erase(q.begin());
      func(vHelp);
      
      for(auto i = adjHelp[vHelp].begin(); i != adjHelp[vHelp].end(); ++i) {
        if(visit[*i] == false){
          visit[*i] = true;
          q.push_back(*i);
        }
      }
    }
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void dfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    // TODO: Implementasikan!
    std::unordered_map<VertexType, bool> visit;
    for (auto &i : _adj_list) {
      visit.insert(std::make_pair(i.first, false));
    }

    std::stack<VertexType> s;
    s.push(root);
    while (!s.empty()) {
      VertexType vHelp = s.top();
      s.pop();

      if(!visit[vHelp]) {
        func(vHelp);
        visit[vHelp] = true;
      }

      for (auto &i : _adj_list.at(vHelp)) {
        if (!visit[i]) {
          s.push(i);
        }
      }
    }
  }

 private:
  /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
  adj_list_type _adj_list;
};

}  // namespace strukdat