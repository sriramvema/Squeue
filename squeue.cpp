// UMBC - CMSC 341 - Spring 2022 - Proj2
// Author: Sriram Vema
// Date: 4/19/2022
// Section:5
// File: squeue.cpp
// Description: squeue file that holds squeue class functions
#include "squeue.h"
SQueue::SQueue(prifn_t priFn, HEAPTYPE heapType)
{
  m_priorFunc = priFn;      // Sets the default variables for private members
  m_heapType = heapType;
  m_heap = nullptr;
  m_size = 0;
  
}

SQueue::~SQueue()
{
  clear(); // Destructor calls clear function
}

SQueue::SQueue(const SQueue& rhs)
{
  m_heapType = rhs.m_heapType;        // Copies Private members
  m_priorFunc = rhs.m_priorFunc;
  m_size = rhs.m_size;
  m_heap = copy(rhs.m_heap); // Copies heap
}

SQueue& SQueue::operator=(const SQueue& rhs)
{
  if (this != &rhs) {
    clear();                     // clears the heap first
    m_heapType = rhs.m_heapType;     // Copies the private members
    m_priorFunc = rhs.m_priorFunc;
    m_size = rhs.m_size;
    m_heap = copy(rhs.m_heap);  // Copies heap
  }
  return *this;
}

Node* SQueue::copy(Node* aNode) {
  if (aNode != nullptr) {
    Post post = aNode->m_post;         //Copies the post at current node
    Node* heap = new Node(post);          // adds it the heap
    heap->m_left = copy(aNode->m_left);  // copies left and right children
    heap->m_right = copy(aNode->m_right);
    return heap;
  }
  return nullptr;
}

bool SQueue::findPost(Node* aNode, Post post) {
  if (aNode != nullptr) {
    Post post1 = aNode->getPost();
    if (post1.m_postID == post.m_postID) {     // Checks if the post id exists in the heap
      return true;
    } 
    if (findPost(aNode->m_left, post)) {   // Checks the children as well
      return true;
    }
    if (findPost(aNode->m_right, post)) {
      return true;
    }    
  }

  return false;
}

void SQueue::insertPost(const Post& post) {
  Node* insert = new Node(post);        // Creates node to be added
  if (m_heap == nullptr) {
    m_heap = insert; // if m_heap is null then add it to m_heap
    m_size ++;
  } else {
    SQueue rhs(m_priorFunc, m_heapType); // Create an empty queue and add the single node to it
    rhs.m_heap = insert;
    mergeWithQueue(rhs);  // merge that queue with current queue
    m_size ++; //Increase size of heap
  }    
}

Post SQueue::getNextPost() {
    if (m_heap != nullptr) {
      Node* temp1 = m_heap->m_left;        // copies the left and right children of the 
      Node* temp2 = m_heap->m_right;
      m_heap->m_left = nullptr;       // Disconnect the m_heap from the rest of the heap
      m_heap->m_right = nullptr;
      Node* curr = m_heap;
      Post post = m_heap->m_post;    // Copy the post at m_heap
      delete curr;                        // Delete the memory at m_heap     
      m_size--;
      if (m_heapType == MAXHEAP) {        // Merge the heaps at left and right together
        m_heap = mergeMAX(temp1, temp2);
      } else {
        m_heap = mergeMIN(temp1, temp2);
      }
      return post;
    } else {
      throw out_of_range("Nullptr");     // Throw out of range error if m_heap is nullptr
    }
}

void SQueue::mergeWithQueue(SQueue& rhs) {
  if (this != &rhs) {                             // Make sure the queue isn't being merged with itself
    if (rhs.m_heap != nullptr) {                  // Make sure rhs isn't empty
      if (m_priorFunc == rhs.m_priorFunc) {        // Only merge if priority functions match
        if (m_heapType == MINHEAP) {             // Merge based on MIN or MAX heap
          m_heap = mergeMIN(m_heap, rhs.m_heap);
        } else {
          m_heap = mergeMAX(m_heap, rhs.m_heap);
        }
        rhs.m_heap = nullptr;
      } else {
        throw domain_error("PRIORITY FUNCTIONS DO NOT MATCH");     
      }
    }
  }

}

Node* SQueue::mergeMIN(Node* node1, Node* node2) {
  if (node1 == nullptr) {
    return node2;
  } else if (node2 == nullptr) {
    return node1;
  } else if (m_priorFunc(node1->m_post) <= m_priorFunc(node2->m_post)) {    //Merge so that the least of the two posts is at the top
    Node* temp = node1->m_right;
    node1->m_right = node1->m_left;               // Merge the children of both nodes
    node1->m_left = mergeMIN(node2, temp);
    return node1;
  } else {
    return mergeMIN(node2, node1);          // Merge with the nodes switched in case node1 is greater than node2
  }
}

Node* SQueue::mergeMAX(Node* node1, Node* node2) {
  if (node1 == nullptr) {
    return node2;
  } else if (node2 == nullptr) {
    return node1;
  } else if (m_priorFunc(node1->m_post) >= m_priorFunc(node2->m_post)) {    // Merge so that the greatest of the two posts is at the top
    Node* temp = node1->m_right;
    node1->m_right = node1->m_left;                       // Merge the children of both nodes
    node1->m_left = mergeMAX(node2, temp);
    return node1;
  } else {
    return mergeMAX(node2, node1);      // Merge with the nodes switched in case node1 is greater than node2
  }
}

void SQueue::clear() {
  clear(m_heap);          // Call recursive destructor
}

void SQueue::clear(Node* aNode) {
  if (aNode != nullptr) {        // Delete the children of the node first and then delete the parent
    clear(aNode->m_left);
    clear(aNode->m_right);
    delete aNode;
  }
}

int SQueue::numPosts() const
{
  return m_size;       // Return the size of the heap
}

void SQueue::printPostsQueue() const {
  printPostsQueue(m_heap);       // Call
}
void SQueue::printPostsQueue(Node* aNode) const{
  if (aNode) {
    cout << "[" << m_priorFunc(aNode->m_post) << "] " << aNode->m_post << endl;     // Print the post info with pre order traversal
    printPostsQueue(aNode->m_left);
    printPostsQueue(aNode->m_right);
  }
}

prifn_t SQueue::getPriorityFn() const {
  return m_priorFunc;      // Return the priority function
}

HEAPTYPE SQueue::getHeapType() const {
  return m_heapType;      // return the function
}

void SQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  int size = m_size;         //Copy the new priority and heaptype
  m_priorFunc = priFn;
  m_heapType = heapType;   
  rebuild(size);       // rebuild the heap with the new heaptype
}

void SQueue::rebuild(const int size) {
  Post array[size];
  for (int i = 0; i < size; i++) {     // Copy the posts in the heap into the array while also deleting from the heap
    array[i] = getNextPost();
  }
  for (int n = 0; n < size; n++) {
    insertPost(array[n]);             // re insert the posts with the new heaptype
  }
}


void SQueue::dump() const
{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
  }
}

void SQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_post) << ":" << pos->m_post.getPostID();
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Post& post) {
  sout << "Post ID: " << post.getPostID() 
        << ", number of likes: " << post.getNumLikes()
        << ", interest level: " << post.getInterestLevel() 
        << ", connection level: " << post.getConnectLevel()
        << ", post time: " << post.getPostTime();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPost();
  return sout;
}

