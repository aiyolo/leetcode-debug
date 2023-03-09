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
#include <ostream>
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

template <typename T> struct function_traits;
// 普通函数
template <typename Ret, typename... Args> struct function_traits<Ret(Args...)> {
  enum { arity = sizeof...(Args) };
  using function_type = Ret(Args...);
  using return_type = Ret;
  using stl_function_type = std::function<function_type>;
  using pointer = Ret (*)(Args...);
  using tuple_type =
      std::tuple<std::decay_t<Args>...>; // 需要移除掉输入参数的引用类型
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

// lambda到function的变换
template <typename Function>
typename function_traits<Function>::stl_function_type
to_function(const Function &lambda) {
  return static_cast<typename function_traits<Function>::stl_function_type>(
      lambda);
}

// lambda到function的变换
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
constexpr std::variant<Args...> _tuple_index(std::tuple<Args...> &tp,
                                             size_t i) {
  if (n == i)
    return std::variant<Args...>{std::in_place_index<n>, std::get<n>(tp)};
  return _tuple_index < n < sizeof...(Args) - 1 ? n + 1 : 0 > (tp, i);
}
template <typename... Args>
constexpr std::variant<Args...> tuple_index(std::tuple<Args...> &tp, size_t i) {
  return _tuple_index<0>(tp, i);
}
template <typename T0, typename... Ts>
std::ostream &operator<<(std::ostream &os, std::variant<T0, Ts...> const &v) {
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

// 打印链表
inline void prettyPrintLinkedList(ListNode *node) {
  while (node && node->next) {
    std::cout << node->val << "->";
    node = node->next;
  }

  if (node) {
    std::cout << node->val << std::endl;
  } else {
    std::cout << "Empty LinkedList" << std::endl;
  }
}

inline void trimLeftTrailingSpaces(std::string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(),
                                     [](int ch) { return !isspace(ch); }));
}

inline void trimRightTrailingSpaces(std::string &input) {
  input.erase(
      find_if(input.rbegin(), input.rend(), [](int ch) { return !isspace(ch); })
          .base(),
      input.end());
}

inline std::string stringToString(std::string input) {
  assert(input.length() >= 2);
  std::string result;
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


inline std::vector<int> stringToIntegerVector(std::string input) {
  std::vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

inline std::vector<char> stringToCharVector(std::string input) {
  std::vector<char> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stringToString(item)[0]);
  }
  return output;
}

inline std::vector<std::vector<int>>
stringTo2dIntegerVector(std::string input) {
  std::vector<std::vector<int>> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(0, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ']';
  while (getline(ss, item, delim)) {
    item += ']';
    item = item.substr(1);
    output.emplace_back(stringToIntegerVector(item));
  }
  return output;
}

inline std::vector<std::vector<char>>
stringTo2dCharVector(std::string input) {
  std::vector<std::vector<char>> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(0, input.length() - 2);
  std::stringstream ss;
  ss.str(input);
  std::string item;
  char delim = ']';
  while (getline(ss, item, delim)) {
    item += ']';
    item = item.substr(1);
    output.emplace_back(stringToCharVector(item));
  }
  return output;
}

// inline vector<string> stringToStringVector(string input) {
//   vector<string> output;
//   trimLeftTrailingSpaces(input);
//   trimRightTrailingSpaces(input);
//   input = input.substr(1, input.length() - 2);
//   stringstream ss;
//   ss.str(input);
//   string item;
//   char delim = ',';
//   while (getline(ss, item, delim)) {
//     trimLeftTrailingSpaces(item);
//     trimRightTrailingSpaces(item);
//     output.push_back(stringToString(item));
//   }
//   return output;
// }

// 从string中解析
inline std::vector<std::string> splitByComma(std::string input) {
  std::vector<std::string> output;
  int cnt = 0;
  int i = 0, j = 0;
  while (i < input.size()) {
    while (j < input.size() && input[j] != ',') {
      if (input[j] == '[')
        cnt++;
      if (input[j] == ']')
        cnt--;
      j++;
    }
    if (cnt == 0) {
      output.push_back(stringToString(input.substr(i, j - i)));
      i = j + 1;
    }
    j++;
  }
  return output;
}

inline std::vector<std::string> stringToArguments(std::string str) {
  std::vector<std::string> output;
  int i = 0, j = 0;
  int cnt = 0;
  while (i < str.size()) {
    while (j < str.size() && str[j] != ',') {
      if (str[j] == '[')
        cnt++;
      if (str[j] == ']')
        cnt--;
      j++;
    }
    if (cnt == 0) {
      if (str[0] == '\"') {
        output.push_back(stringToString(str.substr(i, j - i)));
      } else {
        output.push_back(str.substr(i, j - i));
      }
      i = j + 1;
    }
    j++;
  }
  return output;
}

// 从cin中解析,首字符为"\"";
inline std::vector<std::string> stringToStringVector(std::string input) {
  std::vector<std::string> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2); // input = "\" ... \""
  output = splitByComma(input);
  return output;
}

inline std::string integerVectorToString(std::vector<int> list,
                                         int length = -1) {
  if (length == -1) {
    length = list.size();
  }

  if (length == 0) {
    return "[]";
  }

  std::string result;
  for (int index = 0; index < length; index++) {
    int number = list[index];
    result += std::to_string(number) + ", ";
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

inline ListNode *stringToListNode(std::string input) {
  // Generate list from the input
  std::vector<int> list = stringToIntegerVector(input);

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

inline std::string listNodeToString(ListNode *node) {
  if (node == nullptr) {
    return "[]";
  }

  std::string result;
  while (node) {
    result += std::to_string(node->val) + ", ";
    node = node->next;
  }
  return "[" + result.substr(0, result.length() - 2) + "]";
}

inline int stringToInteger(std::string input) { return stoi(input); }

inline std::string treeNodeToString(TreeNode *root) {
  if (root == nullptr) {
    return "[]";
  }

  std::string output = "";
  std::queue<TreeNode *> q;
  q.push(root);
  while (!q.empty()) {
    TreeNode *node = q.front();
    q.pop();

    if (node == nullptr) {
      output += "null, ";
      continue;
    }

    output += std::to_string(node->val) + ", ";
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
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &arr) {
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
std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::vector<T>> &arr) {
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
      os << std::endl;
  }
  os << "]";
  return os;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::pair<T, U>> &arr) {
  os << "[";
  for (int i = 0; i < arr.size(); i++) {
    os << "[" << arr[i].first << ", " << arr[i].second << "]";
    if (i != arr.size() - 1)
      os << std::endl;
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

inline void prettyPrintTree(TreeNode *node, std::string prefix = "",
                            bool isLeft = true) {
  if (node == nullptr) {
    std::cout << "Empty tree";
    return;
  }
  if (node->right) {
    prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
  }
  std::cout << prefix + (isLeft ? "└── " : "┌── ") + std::to_string(node->val) +
                   "\n";
  if (node->left) {
    prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
  }
}

inline TreeNode *stringToTreeNode(std::string input) {
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  if (!input.size()) {
    return nullptr;
  }

  std::string item;
  std::stringstream ss;
  ss.str(input);

  getline(ss, item, ',');
  TreeNode *root = new TreeNode(stoi(item));
  std::queue<TreeNode *> nodeQueue;
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

inline std::ostream& operator<<(std::ostream &os, ListNode* head){
  prettyPrintLinkedList(head);
  return os;
}

inline std::ostream& operator<<(std::ostream& os, TreeNode* root){
  prettyPrintTree(root);
  return os;
}

inline bool stringToBool(std::string input) {
  transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input == "true";
}

inline std::string boolToString(bool input) { return input ? "True" : "False"; }

inline double stringToDouble(std::string input) { return stod(input); }

// enable_if 重载
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
stringToTarget(std::string &s, T &t) {
  t = stringToString(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, double>::value, void>::type
stringToTarget(std::string &s, T &t) {
  t = stringToDouble(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type
stringToTarget(std::string s, T &t) {
  t = stringToInteger(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<int>>::value, void>::type
stringToTarget(std::string s, T &t) {
  t = stringToIntegerVector(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<char>>::value, void>::type
stringToTarget(std::string s, T &t) {
  t = stringToCharVector(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<std::vector<int>>>::value,
                        void>::type
stringToTarget(std::string s, T &t) {
  t = stringTo2dIntegerVector(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<std::vector<char>>>::value,
                        void>::type
stringToTarget(std::string s, T &t) {
  t = stringTo2dCharVector(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<std::string>>::value,
                        void>::type
stringToTarget(std::string s, T &t) {
  t = stringToStringVector(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, ListNode *>::value, void>::type
stringToTarget(std::string s, T &t) {
  t = stringToListNode(s);
}

template <typename T>
typename std::enable_if<std::is_same<T, TreeNode *>::value, void>::type
stringToTarget(std::string s, T &t) {
  t = stringToTreeNode(s);
}

template <size_t I = 0, typename Tuple, typename Array>
void ArrayToTuple(Array &arr, Tuple &&tp) {
  if constexpr (I == std::tuple_size<std::decay_t<Tuple>>::value)
    return;
  else { // 必须加else
    stringToTarget(arr[I], std::get<I>(tp));
    ArrayToTuple<I + 1>(arr, std::forward<Tuple>(tp));
  }
}

template <typename T> struct MemberFunctionBase {
  virtual void operator()(T *obj, std::vector<std::string> &strArg) {
  } // 需要虚函数调用子类函数
  virtual ~MemberFunctionBase(){};
};

template <typename T, typename F>
struct MemberFunction : public MemberFunctionBase<T> {
  using tuple_type = typename function_traits<F>::tuple_type;
  using return_type = typename function_traits<F>::return_type;
  static constexpr size_t I = function_traits<F>::arity;
  F m_func;

  MemberFunction(F func) : m_func(func) {}
  ~MemberFunction() override{}

  // 输出位置
  template <size_t... Is>
  void exec(T *obj, std::vector<std::string> &strArg,
            std::index_sequence<Is...>) {
    // 将传入的string参数，转化为函数实际参数类型，存在tuple里
    tuple_type tpArg;
    ArrayToTuple(strArg, tpArg);
    // 如果成员函数返回值为void，那么直接执行函数
    if constexpr (std::is_void_v<return_type>) {
      (*obj.*m_func)(std::get<Is>(tpArg)...);
    } else { // 如果具有非空返回值，那么打印出来，前面已经对cout实现了重载
      std::cout << (*obj.*m_func)(std::get<Is>(tpArg)...);
    }
  }
  void operator()(T *obj, std::vector<std::string> &strArg) {
    // 为了展开参数，使用了index_sequence
    exec(obj, strArg, std::make_index_sequence<I>());
  }
};

template <typename T, bool simpleExcecutor = true> class Excecutor {
public:
  std::unordered_map<std::string, std::unique_ptr<MemberFunctionBase<T>>> funcMap;
  std::vector<std::string> inputs;
  std::vector<std::string> functionNameArray;
  std::vector<std::string> functionArgArray;
  T *instance;

public:
  Excecutor(std::string path) : instance(nullptr) { parsefromInputs(path); };
  ~Excecutor() {
    if (instance != nullptr) {
      delete instance;
    }
  }

  // 创建 Solution 的实例
  template <typename Args> T *createInstance() {
    if constexpr (simpleExcecutor) {
      instance = new T();
    } else {
        // 如果构造函数是无参的
        if constexpr (std::is_void_v<Args>){
          instance = new T();
        }
        else{
          Args args;
          stringToTarget(functionArgArray[0], args);
          if (instance == nullptr) {
            instance = new T(args);
          }
        }
    }
    return instance;
  }

  void parsefromInputs(std::string path) {
    std::ifstream cin(path);
    std::string str;
    while (getline(cin, str)) {
      inputs.push_back(str);
    }
    // 如果设计类leetcode题，那么第一行为函数名，第二行为函数参数
    if (!simpleExcecutor) {
      functionNameArray = stringToStringVector(inputs[0]);
      functionArgArray = stringToStringVector(inputs[1]);
    } else { // 如果是Solution类的题目，那么输入就是参数
      functionArgArray = inputs;
    }
  }

  void run() {
    if (simpleExcecutor) {
      (*(funcMap.begin()->second))(instance, functionArgArray);
    } else {
      for (int i = 1; i < functionArgArray.size(); i++) {
        std::vector<std::string> tmp = stringToArguments(functionArgArray[i]);
        (*funcMap[functionNameArray[i]])(instance, tmp);
      }
    }
  }

  template <typename F> void registerMemberFunction(std::string s, F &&func) {
    // 把它们先上行转化，存入到funcmap里
    // 在调用的时候，通过调用父类的虚函数operator()()方法，来调用到子类的成员函数
    auto pFuncBase = static_cast<MemberFunctionBase<T> *>(new MemberFunction<T, F>(std::forward<F>(func)));
    funcMap.emplace(s, pFuncBase);
  }
};
