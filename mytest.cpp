// UMBC - CMSC 341 - Spring 2022 - Proj2
// Author: Sriram Vema
// Date: 4/19/2022
// Section:5
// File: mytest.cpp
// Description: mytest file that holds Tester class functions
#include "squeue.h"
#include <random>
// the followings are sample priority functions to be used by SQueue class
// users can define their own priority functions
// Priority functions compute an integer priority for a post.  Internal
// computations may be floating point, but must return an integer.
int priorityFn1(const Post &post);// works with a MAXHEAP
int priorityFn2(const Post &post);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
    public:
    bool maxHeapProperty(Node* aNode, prifn_t priority);  // recursive function that iterates the heap to make sure it has heap type properties
    bool minHeapProperty(Node* aNode, prifn_t priority);
    bool normalInsertMAX();   // Normal insertion with maxheap
    bool normalInsertMIN();   // Normal insertion with minheap
    bool normalRemoveMIN();   // Normal removal with minheap
    bool normalRemoveMAX();   // Normal removal with maxheap
    bool setPrior();          // test for setting priority function
    bool mergeEdge();         // merging with an empty queue
    bool copyConsNormal();    // normal case for copy constructor
    bool copyConsEdge();      // Edge case for copy constructor
    bool assignNormal();      // Normal case for assignment operator
    bool assignEdge();        // edge case for assignment operator
    bool difPriorError();     // merging two queues with different priority
    bool dequeue();           // removing from an empty queue
    bool mergeWithItself();   // merging a queue with itself
};

int main(){
    Tester tester;
    cout << "Testing Normal Case for MAXHEAP InsertPost: " << endl;
    if (tester.normalInsertMAX()) {
        cout << "\tNormal case for InsertPost with MAXHEAP passed!" << endl;
    } else {
        cout << "\tNormal case for InsertPost with MAXHEAP failed!" << endl;
    }
    cout << endl;
    cout << "Testing Normal Case for MINHEAP InsertPost: " << endl;
    if (tester.normalInsertMIN()) {
        cout << "\tNormal case for InsertPost with MINHEAP passed!" << endl;
    } else {
        cout << "\tNormal case for InsertPost with MINHEAP failed!" << endl;
    }
    cout << endl;
    cout << "Testing Normal Case for MINHEAP Remove: " << endl;
    if (tester.normalRemoveMIN()) {
        cout << "\tNormal case for remove with MINHEAP passed!" << endl;
    } else {
        cout << "\tNormal case for remove with MINHEAP failed!" << endl;
    }
    cout << endl;
    cout << "Testing Normal Case for MAXHEAP Remove: " << endl;
    if (tester.normalRemoveMAX()) {
        cout << "\tNormal case for remove with MAXHEAP passed!" << endl;
    } else {
        cout << "\tNormal case for remove with MAXHEAP failed!" << endl;
    }
    cout << endl;
    cout << "Testing setPriorityFn: " << endl;
    if (tester.setPrior()) {
        cout << "\tSet priority function test passed!" << endl;
    } else {
        cout << "\tSet priority function test failed!" << endl;
    }
    cout << endl;
    cout << "Testing Edge Case for Merge: " << endl;
    if (tester.mergeEdge()) {
        cout << "\tEdge case for merge passed!" << endl;
    } else {
        cout << "\tEdge case for merge failed!" << endl;
    }
    cout << endl;
    cout << "Testing Normal Case for Copy Constructor: " << endl;
    if (tester.copyConsNormal()) {
        cout << "\tNormal case for copy constructor passed!" << endl;
    } else {
        cout << "\tNormal case for copy constructor failed!" << endl;
    }
    cout << endl;
    cout << "Testing Edge Case for Copy Constructor: " << endl;
    if (tester.copyConsEdge()) {
        cout << "\tEdge case for copy constructor passed!" << endl;
    } else {
        cout << "\tEdge case for copy constructor failed!" << endl;
    }
    cout << endl;
    cout << "Testing Normal Case for Assignment Operator: " << endl;
    if (tester.assignNormal()) {
        cout << "\tNormal case for assignment operator passed!" << endl;
    } else {
        cout << "\tNormal case for assignment operator failed!" << endl;
    }
    cout << endl;
    cout << "Testing Edge Case for Assignment Operator: " << endl;
    if (tester.assignEdge()) {
        cout << "\tEdge case for assignment operator passed!" << endl;
    } else {
        cout << "\tEdge case for assignment operator failed!" << endl;
    }
    cout << endl;
    cout << "Testing Merge with Different Priority: " << endl;
    if (tester.difPriorError()) {
        cout << "\tDifferent priority function merge test passed!" << endl;
    } else {
        cout << "\tDifferent priority function merge test failed!" << endl;
    }
    cout << endl;
    cout << "Testing Dequeue with Empty Queue: " << endl;
    if (tester.dequeue()) {
        cout << "\tEmpty dequeue test passed!" << endl;
    } else {
        cout << "\tEmpty dequeue test failed!" << endl;
    }
    cout << endl;
    cout << "Testing Error Case for Merge (merge with itself): " << endl;
    if (tester.mergeWithItself()) {
        cout << "\tError case for merge passed!" << endl;
    } else {
        cout << "\tError case for merge failed!" << endl;
    }
    return 0;
}

int priorityFn1(const Post &post) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [1-510]
    //the highest priority would be 500+10 = 510
    //the lowest priority would be 0+1 = 1
    //the larger value means the higher priority
    int priority = post.getNumLikes() + post.getInterestLevel();
    return priority;
}

int priorityFn2(const Post &post) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [2-55]
    //the highest priority would be 1+1 = 2
    //the lowest priority would be 5+50 = 55
    //the smaller value means the higher priority
    int priority = post.getPostTime() + post.getConnectLevel();
    return priority;
}
bool Tester::mergeWithItself() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){                 // Inserting 300 posts to the heap of queue1
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    int size = queue1.m_size;
    queue1.mergeWithQueue(queue1);  // merging queue with itself
    if (size != queue1.m_size) {    // see if the size of the heap changed after merge operation
        return false;
    }
    return true;
}
bool Tester::maxHeapProperty(Node* aNode, prifn_t priority) {
    if (aNode != nullptr) {
        if (aNode->m_left) {
            if (priority(aNode->m_post) < priority(aNode->m_left->m_post)) {   //make sure every parent is greater than its children
                return false;
            }
        }
        if (aNode->m_right) {
            if (priority(aNode->m_post) < priority(aNode->m_left->m_post)) {
                return false;
            }
        }
        if (maxHeapProperty(aNode->m_left, priority) == false) {
            return false;
        } 
        if (maxHeapProperty(aNode->m_right, priority) == false) {
            return false;
        }      
    }
    return true;
}
bool Tester::minHeapProperty(Node* aNode, prifn_t priority) {
    if (aNode != nullptr) {
        if (aNode->m_left) {
            if (priority(aNode->m_post) > priority(aNode->m_left->m_post)) {   // make sure every parent is less than its children
                return false;
            }
        }
        if (aNode->m_right) {
            if (priority(aNode->m_post) > priority(aNode->m_left->m_post)) {
                return false;
            }
        }
        if (minHeapProperty(aNode->m_left, priority) == false) {
            return false;
        } 
        if (minHeapProperty(aNode->m_right, priority) == false) {
            return false;
        }      
    }
    return true;
}
bool Tester::normalInsertMAX() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){             // Inserting 300 nodes with maxheap
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    if (queue1.m_size < 300) {   // Make sure every post was added
        return false;
    }
    return maxHeapProperty(queue1.m_heap, queue1.m_priorFunc);  // make sure heap retains heap properties
} 
bool Tester::normalInsertMIN() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<300;i++){ // Inserting 300 nodes with maxheap
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    if (queue1.m_size < 300) {   
        return false;            // Make sure every post was added
    }
    return minHeapProperty(queue1.m_heap, queue1.m_priorFunc);   // make sure heap retains heap properties
}
bool Tester::normalRemoveMIN() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    Post post;
    Post post2;
    SQueue queue1(priorityFn2, MINHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),         // add 300 posts to queue
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    post = queue1.getNextPost();                // make sure every post that gets returned is less than the next post in minheap
    for (int i=0;i<299;i++) {
        post2 = queue1.getNextPost();
        if (priorityFn2(post2) < priorityFn2(post)) {
            return false;
        }
        post = post2;
    }
    if (queue1.m_size != 0) {
        return false;
    }
    return true;
}
bool Tester::normalRemoveMAX() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    Post post;
    Post post2;
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    post = queue1.getNextPost();

    for (int i=0;i<299;i++) {
        post2 = queue1.getNextPost();                   // make sure every post that gets returned is greater than the next post in maxheap
        if (priorityFn2(post2) > priorityFn2(post)) {
            return false;
        }
        post = post2;
    }
    if (queue1.m_size != 0) {
        return false;
    }
    return true;
}
bool Tester::setPrior() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    Post array[300];
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        array[i] = aPost;
        queue1.insertPost(aPost);
    }
    queue1.setPriorityFn(priorityFn1, MINHEAP);      // set new priority and heaptype
    if (minHeapProperty(queue1.m_heap, queue1.m_priorFunc) == false) {     // make sure the rebuilt function has new heap properties
        return false;
    }
    for (int i=0;i<300;i++) {
        if (queue1.findPost(queue1.m_heap, array[1]) == false) {    // make sure heap has same posts as before
            return false;
        }
    }
    return true;
}
bool Tester::mergeEdge() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MAXHEAP);
    SQueue queue2(priorityFn2, MAXHEAP);
    int size;
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    size = queue1.m_size;
    queue1.mergeWithQueue(queue2);       // merge with an empty queue
    if (size != queue1.m_size) {        // make sure size didn;t change
        return false;
    }
    return true;
}

bool Tester::copyConsNormal() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),         //insert 300 nodes
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    SQueue queue2(queue1);      // Make sure all properties and variables are copied over
    if (queue1.m_heap->m_post.getPostID() != queue2.m_heap->m_post.getPostID() || queue1.m_size != queue2.m_size || queue1.m_heapType != queue2.m_heapType || queue1.m_priorFunc != queue2.m_priorFunc) {
        return false;
    }
    return true;
}
bool Tester::copyConsEdge() {
    SQueue queue1(priorityFn2, MAXHEAP);
    SQueue queue2(queue1);
    if (queue2.m_heap != nullptr) {   // make sure queue stays empty when copying an empty queue
        return false;
    }
    return true;
}
bool Tester::assignNormal() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    SQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue2.insertPost(aPost);
    }
    queue2 = queue1; // Make sure all properties and variables are copied over
    if (queue1.m_heap->m_post.getPostID() != queue2.m_heap->m_post.getPostID() || queue1.m_size != queue2.m_size || queue1.m_heapType != queue2.m_heapType || queue1.m_priorFunc != queue2.m_priorFunc) {
        return false;
    }
    return true;
}
bool Tester::assignEdge() {
    SQueue queue1(priorityFn2, MAXHEAP);
    SQueue queue2(priorityFn1, MINHEAP);
    queue1 = queue2;
    if (queue2.m_heap != nullptr) {
        return false;
    }                     // Make sure all properties and variables are copied over
    if (queue1.m_size != queue2.m_size || queue1.m_heapType != queue2.m_heapType || queue1.m_priorFunc != queue2.m_priorFunc) {
        return false;
    }
    return true;
}
bool Tester::difPriorError() {
    Random idGen(MINPOSTID,MAXPOSTID);
    Random likesGen(MINLIKES,MAXLIKES);
    Random timeGen(MINTIME,MAXTIME);
    Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
    Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
    SQueue queue1(priorityFn1, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue1.insertPost(aPost);
    }
    SQueue queue2(priorityFn2, MAXHEAP);
    for (int i=0;i<300;i++){
        Post aPost(idGen.getRandNum(),
                    likesGen.getRandNum(),
                    conLevelGen.getRandNum(),
                    timeGen.getRandNum(),
                    interestGen.getRandNum());
        queue2.insertPost(aPost);
    }
    try {
        queue1.mergeWithQueue(queue2);    // merge two queues with different priority and see if domain_error is thrown
    } catch(domain_error) {
        return true;
    }
    return false;
}
bool Tester::dequeue() {
    SQueue queue1(priorityFn2, MAXHEAP);
    Post post;
    try {
        post = queue1.getNextPost();         // See if out of range error is thrown when dequeueing an empty heap
    } catch(out_of_range) {
        return true;
    }
    return false;
}