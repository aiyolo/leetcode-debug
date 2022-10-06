
#include "header.h"
using namespace std;

class MyCircularDeque {
public:
  vector<int> arr;
  int front;
  int size;
  int capacity;
  MyCircularDeque(int k) {
    capacity = k;
    arr.resize(k);
    front = 0;
    size = 0;
  }

  bool insertFront(int value) {
    if (isFull()) {
      return false;
    }
    front = (front - 1 + capacity) % capacity;
    arr[front] = value;
    size++;
    return true;
  }

  bool insertLast(int value) {
    if (isFull()) {
      return false;
    }
    int back = (front + size) % capacity;
    arr[back] = value;
    size++;
    return true;
  }

  bool deleteFront() {
    if (isEmpty()) {
      return false;
    }
    front = (front + 1) % capacity;
    size--;
    return true;
  }

  bool deleteLast() {
    if (isEmpty()) {
      return false;
    }
    size--;
    return true;
  }

  int getFront() {
    if (isEmpty()) {
      return -1;
    }
    return arr[front];
  }

  int getRear() {
    if (isEmpty()) {
      return -1;
    }
    int back = (front + size - 1) % capacity;
    return arr[back];
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return size == capacity; }
};

int main() {
  Excecutor<MyCircularDeque, false> exc("../multiplefunction.txt");
  exc.instance = exc.createInstance<int>();
  exc.registerMemberFunction("insertFront", &MyCircularDeque::insertFront);
  exc.registerMemberFunction("insertLast", &MyCircularDeque::insertLast);
  exc.registerMemberFunction("deleteFront", &MyCircularDeque::deleteFront);
  exc.registerMemberFunction("deleteLast", &MyCircularDeque::deleteLast);

  exc.registerMemberFunction("getFront", &MyCircularDeque::getFront);
  exc.registerMemberFunction("getRear", &MyCircularDeque::getRear);
  exc.registerMemberFunction("isEmpty", &MyCircularDeque::isEmpty);
  exc.registerMemberFunction("isFull", &MyCircularDeque::isFull);
  exc.run();

  // inputs
  // ["MyCircularDeque","insertLast","insertLast","insertFront","insertFront","getRear","isFull","deleteLast","insertFront","getFront"]
  // [[3],[1],[2],[3],[4],[],[],[],[4],[]]
}