#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  void heapify(int parent);
  void trickle_up(int childIndex);
  int getChildIndex(int parent, int childNumber);
  int getParentIndex(int child);

  int m;
  PComparator c;

};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c): m(m), c(c) {};
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {};

template <typename T, typename PComparator>
int Heap<T, PComparator>::getChildIndex(int parent, int childNumber) {
  return m*parent + childNumber + 1;
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::getParentIndex(int childIndex) {
  return (childIndex - 1) / m;
}

// Add implementation of member functions here
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int parent) {
  T bestChild = data[parent];
  int bestChildIndex = -1;
  // find best child (which is also better than parent)
  for (int i = 0; i < m; i++) {
    size_t childIndex = getChildIndex(parent, i);
    if (childIndex >= size()) continue; // stay in bounds
    // if child is new best
    if (c(data[childIndex], data[parent]) && c(data[childIndex], bestChild)) {
      bestChildIndex = childIndex;
      bestChild = data[childIndex];
    }
  }

  // if we found somewhere to swap, swap and continue to swap down
  if (bestChildIndex != -1) {
    std::swap(data[parent], data[bestChildIndex]);
    heapify(bestChildIndex);
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickle_up(int childIndex) {
  if (childIndex == 0) return;
  int parentIndex = getParentIndex(childIndex);
  if (c(data[childIndex], data[parentIndex])){
    // cout << "Swapping " << data[childIndex] << "up with " << data[parentIndex] << endl;
    std::swap(data[parentIndex], data[childIndex]);
    trickle_up(parentIndex);
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  std::swap(data[0], data[this->size() - 1]);
  data.pop_back();
  if (!this->empty()) {
    heapify(0);
  }

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data.push_back(item);
  trickle_up(this->size() - 1);

}


#endif

