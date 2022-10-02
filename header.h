#include <algorithm>
#include <any>
#include <assert.h>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
// #include <bits/stdc++.h>
using namespace std;

template <typename T> struct function_traits;
// 普通函数
template <typename Ret, typename... Args> struct function_traits<Ret(Args...)> {
  enum { arity = sizeof...(Args) };
  // typedef Ret function_type(Args...);
  using function_type = Ret(Args...);
  typedef Ret return_type;
  using stl_function_type = std::function<function_type>;
  typedef Ret (*pointer)(Args...);
  using tuple_type = tuple<decay_t<Args>...>; // 需要移除掉输入参数的引用类型
  template <size_t I> struct args {
    static_assert(I < arity, "index out of range");
    using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
  };
};

// 函数指针
template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> : function_traits<Ret(Args...)> {};

// function
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>>
    : function_traits<Ret(Args...)> {};

// 类成员函数
#define FUNCTION_TRAITS(...)                                                   \
  template <typename Ret, typename ClassType, typename... Args>                \
  struct function_traits<Ret (ClassType::*)(Args...) __VA_ARGS__>              \
      : function_traits<Ret(Args...)> {};

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

// 函数对象
template <typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

template <typename Function>
typename function_traits<Function>::stl_function_type
to_function(const Function &lambda) {
  return static_cast<typename function_traits<Function>::stl_function_type>(
      lambda);
}

template <typename Function>
typename function_traits<Function>::stl_function_type
to_function(Function &&lambda) {
  return static_cast<typename function_traits<Function>::stl_function_type>(
      std::forward<Function>(lambda));
}

template <typename Function>
typename function_traits<Function>::pointer
to_function_pointer(const Function &lambda) {
  return static_cast<typename function_traits<Function>::pointer()>(lambda);
}

// 动态索引tuple
template <size_t n, typename... Args>
constexpr variant<Args...> _tuple_index(tuple<Args...> &tp, size_t i) {
  if (n == i)
    return variant<Args...>{in_place_index<n>, get<n>(tp)};
  return _tuple_index < n < sizeof...(Args) - 1 ? n + 1 : 0 > (tp, i);
}
template <typename... Args>
constexpr variant<Args...> tuple_index(tuple<Args...> &tp, size_t i) {
  return _tuple_index<0>(tp, i);
}
template <typename T0, typename... Ts>
ostream &operator<<(ostream &os, variant<T0, Ts...> const &v) {
  visit([&](auto &&x) { os << x; }, v);
  return os;
}

// 链表定义
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 二叉树
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// // 创建链表 array -> ListNode
// ListNode *createLinkedList(int arr[], int len){
//     if(len == 0) return nullptr;
//     ListNode *dummyHead = new ListNode();
//     ListNode *cur = dummyHead;
//     for(int i=0; i<len; i++){
//         ListNode* node = new ListNode(arr[i]);
//         cur->next = node;
//         cur = cur->next;
//     }
//     return dummyHead->next;
// }

// // 创建链表 vector -> ListNode
// ListNode *createLinkedList(vector<int> &arr){
//     if(arr.size() == 0) return nullptr;
//     ListNode *dummyHead = new ListNode();
//     ListNode *cur = dummyHead;
//     for(int i=0; i<arr.size(); i++){
//         ListNode* node = new ListNode(arr[i]);
//         cur->next = node;
//         cur = cur->next;
//     }
//     return dummyHead->next;
// }

// ListNode *createLinkedList(vector<int> &&arr){
//     if(arr.size() == 0) return nullptr;
//     ListNode *dummyHead = new ListNode();
//     ListNode *cur = dummyHead;
//     for(int i=0; i<arr.size(); i++){
//         ListNode* node = new ListNode(arr[i]);
//         cur->next = node;
//         cur = cur->next;
//     }
//     return dummyHead->next;
// }

// // 打印链表 ListNode -> void
// void printLinkedList(ListNode *head){
//     ListNode *cur = head;
//     while(cur != nullptr){
//         cout << cur->val << " ";
//         cur = cur->next;
//     }
//     cout << endl;
// }

inline void prettyPrintLinkedList(ListNode *node) {
  while (node && node->next) {
    cout << node->val << "->";
    node = node->next;
  }

  if (node) {
    cout << node->val << endl;
  } else {
    cout << "Empty LinkedList" << endl;
  }
}

inline void trimLeftTrailingSpaces(string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(),
                                     [](int ch) { return !isspace(ch); }));
}

inline void trimRightTrailingSpaces(string &input) {
  input.erase(
      find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
          .base(),
      input.end());
}

inline vector<int> stringToIntegerVector(string input) {
  vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

vector<vector<int>> stringTo2dIntegerVector(string input) {
  vector<vector<int>> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(0, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ']';
  while (getline(ss, item, delim)) {
    item += ']';
    item = item.substr(1);
    output.emplace_back(stringToIntegerVector(item));
  }
  return output;
}

string stringToString(string input) {
  assert(input.length() >= 2);
  string result;
  for (int i = 1; i < input.length() - 1; i++) {
    char currentChar = input[i];
    if (input[i] == '\\') {
      char nextChar = input[i + 1];
      switch (nextChar) {
      case '\"':
        result.push_back('\"');
        break;
      case '/':
        result.push_back('/');
        break;
      case '\\':
        result.push_back('\\');
        break;
      case 'b':
        result.push_back('\b');
        break;
      case 'f':
        result.push_back('\f');
        break;
      case 'r':
        result.push_back('\r');
        break;
      case 'n':
        result.push_back('\n');
        break;
      case 't':
        result.push_back('\t');
        break;
      default:
        break;
      }
      i++;
    } else {
      result.push_back(currentChar);
    }
  }
  return result;
}

vector<string> stringToStringVector(string input) {
  vector<string> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    trimLeftTrailingSpaces(item);
    trimRightTrailingSpaces(item);
    output.push_back(stringToString(item));
  }
  return output;
}

string integerVectorToString(vector<int> list, int length = -1) {
  if (length == -1) {
    length = list.size();
  }

  if (length == 0) {
    return "[]";
  }

  string result;
  for (int index = 0; index < length; index++) {
    int number = list[index];
    result += to_string(number) + ", ";
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

ListNode *stringToListNode(string input) {
  // Generate list from the input
  vector<int> list = stringToIntegerVector(input);

  // Now convert that list into linked list
  ListNode *dummyRoot = new ListNode(0);
  ListNode *ptr = dummyRoot;
  for (int item : list) {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
  }
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

string listNodeToString(ListNode *node) {
  if (node == nullptr) {
    return "[]";
  }

  string result;
  while (node) {
    result += to_string(node->val) + ", ";
    node = node->next;
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

int stringToInteger(string input) { return stoi(input); }

// // 创建环形链表 array -> ListNode
// ListNode * createCycleList(int arr[], int len, int k){
//     if(len == 0) return nullptr;
//     ListNode* dummyHead = new ListNode(0);
//     ListNode* entry = nullptr;
//     ListNode* cur = dummyHead;
//     for(int i=0; i<len; i++){
//         ListNode* node = new ListNode(arr[i]);
//         if(i==k) entry = node;
//         cur->next = node;
//         cur = cur->next;
//     }
//     cur->next = entry;
//     return dummyHead->next;
// }

string treeNodeToString(TreeNode *root) {
  if (root == nullptr) {
    return "[]";
  }

  string output = "";
  queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode *node = q.front();
    q.pop();

    if (node == nullptr) {
      output += "null, ";
      continue;
    }

    output += to_string(node->val) + ", ";
    q.push(node->left);
    q.push(node->right);
  }
  return "[" + output.substr(0, output.length() - 2) + "]";
}

// // 创建环形链表 vector -> ListNode
// ListNode *createCycleList(vector<int> arr, int k){
//     if(arr.size() == 0) return nullptr;
//     ListNode* dummyHead = new ListNode(0);
//     ListNode* entry = nullptr;
//     ListNode* cur = dummyHead;
//     for(int i=0; i<arr.size(); i++){
//         ListNode* node = new ListNode(arr[i]);
//         if(i==k) entry = node;
//         cur->next = node;
//         cur = cur->next;
//     }
//     cur->next = entry;
//     return dummyHead->next;
// }

// // 打印数组
// template<typename T>
// void printVector(vector<T> &arr){
//     for(int i=0; i<arr.size(); i++){
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }

// template<typename T>
// void printVector(vector<vector<T>> &arr){
//     for(int i=0; i<arr.size(); i++){
//         for(int j=0; j<arr[i].size(); j++){
//             cout << arr[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// 打印数组 重载cout
template <typename T> ostream &operator<<(ostream &os, const vector<T> &arr) {
  os << "[";
  for (int i = 0; i < arr.size(); i++) {
    os << arr[i];
    if (i != arr.size() - 1)
      os << ", ";
  }
  os << "]";
  return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &arr) {
  os << "[";
  for (int i = 0; i < arr.size(); i++) {
    os << "[";
    for (int j = 0; j < arr[i].size(); j++) {
      os << arr[i][j];
      if (j != arr[i].size() - 1)
        os << ", ";
    }
    os << "]";
    if (i != arr.size() - 1)
      os << endl;
  }
  os << "]";
  return os;
}

// TreeNode* null = nullptr;

// TreeNode* createTree(vector<any> &arr){
//     if(arr.size()==0) return nullptr;
//     queue<TreeNode*> que;
//     TreeNode* root;
//     if(arr[0].type()==typeid(int)){
//         int val = any_cast<int>(arr[0]);
//         root = new TreeNode(val);
//         que.push(root);
//     }
//     else return nullptr;
//     int i = 1;
//     while(que.size() && i<arr.size()){
//         TreeNode* node = que.front();
//         que.pop();
//         if(i<arr.size() && arr[i].type()==typeid(int)){
//             int val = any_cast<int>(arr[i]);
//             node->left = new TreeNode(val);
//             que.push(node->left);
//         }
//         i++;
//         if(i<arr.size() && arr[i].type()==typeid(int)){
//             int val = any_cast<int>(arr[i]);
//             node->right = new TreeNode(val);
//             que.push(node->right);
//         }
//         i++;

//     }
//     return root;

// }

// void buildNode(TreeNode* node, int idx, vector<int> &arr){
//     if(2*idx+1<arr.size() && arr[2*idx+1]!=-1){
//         node->left = new TreeNode(arr[2*idx+1]);
//         buildNode(node->left, 2*idx+1, arr);
//     }
//     if(2*idx+2<arr.size() && arr[2*idx+2]!=-1){
//         node->right = new TreeNode(arr[2*idx+2]);
//         buildNode(node->right, 2*idx+2, arr);
//     }
// }
// TreeNode* createTree(vector<int> &arr){
//     if(arr.size()==0) return nullptr;
//     TreeNode* root = new TreeNode(arr[0]);
//     buildNode(root, 0, arr);
//     return root;
// }

// // 打印二叉树
// void printTree(TreeNode* root){
//     if(root==nullptr) return;
//     queue<TreeNode*> que;
//     que.push(root);
//     while(!que.empty()){
//         int size = que.size();
//         while(size--){
//             TreeNode* node = que.front();
//             cout << node->val << " ";
//             que.pop();
//             if(node->left!=nullptr) que.push(node->left);
//             if(node->right!=nullptr) que.push(node->right);
//         }
//     }
//     cout << endl;
// }

void prettyPrintTree(TreeNode *node, string prefix = "", bool isLeft = true) {
  if (node == nullptr) {
    cout << "Empty tree";
    return;
  }

  if (node->right) {
    prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
  }

  cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

  if (node->left) {
    prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
  }
}

TreeNode *stringToTreeNode(string input) {
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  if (!input.size()) {
    return nullptr;
  }

  string item;
  stringstream ss;
  ss.str(input);

  getline(ss, item, ',');
  TreeNode *root = new TreeNode(stoi(item));
  queue<TreeNode *> nodeQueue;
  nodeQueue.push(root);

  while (true) {
    TreeNode *node = nodeQueue.front();
    nodeQueue.pop();

    if (!getline(ss, item, ',')) {
      break;
    }

    trimLeftTrailingSpaces(item);
    if (item != "null") {
      int leftNumber = stoi(item);
      node->left = new TreeNode(leftNumber);
      nodeQueue.push(node->left);
    }

    if (!getline(ss, item, ',')) {
      break;
    }

    trimLeftTrailingSpaces(item);
    if (item != "null") {
      int rightNumber = stoi(item);
      node->right = new TreeNode(rightNumber);
      nodeQueue.push(node->right);
    }
  }
  return root;
}

bool stringToBool(string input) {
  transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input == "true";
}

string boolToString(bool input) { return input ? "True" : "False"; }

double stringToDouble(string input) { return stod(input); }

// enable_if 重载
template <typename T>
typename enable_if<is_same<T, string>::value, void>::type transform(string &s,
                                                                    T &t) {
  t = stringToString(s);
}

template <typename T>
typename enable_if<is_same<T, double>::value, void>::type transform(string &s,
                                                                    T &t) {
  t = stringToString(s);
}

template <typename T>
typename enable_if<is_same<T, int>::value, void>::type transform(string s,
                                                                 T &t) {
  t = stringToInteger(s);
}

template <typename T>
typename enable_if<is_same<T, vector<int>>::value, void>::type
transform(string s, T &t) {
  t = stringToIntegerVector(s);
}

template <typename T>
typename enable_if<is_same<T, vector<vector<int>>>::value, void>::type
transform(string s, T &t) {
  t = stringTo2dIntegerVector(s);
}

template <typename T>
typename enable_if<is_same<T, vector<string>>::value, void>::type
transform(string s, T &t) {
  t = stringToStringVector(s);
}

template <typename T>
typename enable_if<is_same<T, ListNode *>::value, void>::type
transform(string s, T &t) {
  t = stringToListNode(s);
}

template <typename T>
typename enable_if<is_same<T, TreeNode *>::value, void>::type
transform(string s, T &t) {
  t = stringToTreeNode(s);
}

template <typename T0, typename... T>
void parse(ifstream &cin, T0 &t0, T &...t) {
  string s;
  getline(cin, s);
  transform(s, t0);
  if constexpr (sizeof...(t) > 0)
    parse(cin, t...); // c++ 17 requiered
}

template <typename T> class Excecutor {
public:
  template <typename... Args> static T *Instance(Args &&...args) {
    if (m_instance == nullptr) {
      m_instance = new T(forward<T>(args)...);
    }
    return m_instance;
  }

  template <typename F>
  decltype(auto) init(F &&f) {
    ifstream cin("../testcases.txt");
    vector<string> arr;
    string s;
    while (getline(cin, s)) {
      arr.push_back(s);
    }
    constexpr size_t I = function_traits<F>::arity;
    // using function_type = function_traits<F>::stl_function_type;
    // cout << I;
    using tuple_type = typename function_traits<F>::tuple_type;
    // vector<int> a ={2,5,1,3,4,7};
    // tuple_type tp= make_tuple(a, 3);
    tuple_type tp;
    trans(arr, tp);
    cout << get<0>(tp);
    // return (*m_instance.*f)(a, 3);
    // return apply((*m_instance.*f), tp);
    return call(f, make_index_sequence<I>{}, tp);
    // return 1;
  }
  template <size_t I = 0, typename... Args, class Container>
  typename enable_if<I == sizeof...(Args), void>::type
  trans(Container &arr, 
  tuple<Args...> &tp) {
    return;
  }
  template <size_t I = 0, typename... Args, class Container>
      typename enable_if < I<sizeof...(Args), void>::type
                           trans(Container& arr, tuple<Args...> &tp) {
    if constexpr (I == sizeof...(Args))
      return;
    transform(arr[I], get<I>(tp));
    trans<I + 1>(arr, tp);
  }
  template <typename F, class Tuple, size_t... I>
  constexpr decltype(auto) call(F &&f, index_sequence<I...>, Tuple &tp) {
    return invoke(f, m_instance, get<I>(tp)...);
  }
  // private:
  Excecutor() = default;
  ~Excecutor() = default;

public:
  int m_args;

private:
  static T *m_instance;
  // tuple<any> tp;
};
// 定义静态成员变量
template <typename T> T *Excecutor<T>::m_instance = nullptr;
