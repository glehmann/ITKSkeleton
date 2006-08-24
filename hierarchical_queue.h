#ifndef hierarchical_queue_h
#define hierarchical_queue_h

#include <queue>
#include <map>
#include <functional>

/**
 *  @brief Hierarchical queue.
 *
 *  The hierarchical queue can be seen as a multiple regular queue. Each
 *  element in the queue has a priority and a value. Elements of higher
 *  priority are served before those of lower priority. Elements of same
 *  priority are served in FIFO order.
 *
 *  The ``higher priority'' relation is not necessarily ``greater than'' : it
 *  depends on the given comparison criterion. The default behaviour is as such,
 *  but you could choose to use std::less<Priority> to have point with a lower
 *  priority value being served first.
 */
template<typename Priority, typename Value, typename Compare = std::greater<Priority> >
class hierarchical_queue
{
public:

    /**
     *  @brief Type of the queue's values.
     */
    typedef Value value_type;

    /**
     *  @brief Type of the queue's priority.
     */
    typedef Priority key_type;

    /**
     *  @brief Type of the queue's size (number of elements).
     */
    typedef unsigned long int size_type;

    /**
     *  @brief Create an empty hierarchical queue.
     */
    hierarchical_queue();
    
    /**
     *  @brief Copy constructor
     */
    hierarchical_queue(const hierarchical_queue<Priority, Value, Compare> & src);
    
    /** 
     *  @brief Destructor
     */
    ~hierarchical_queue();
    
    /**
     *  @brief Add an element to the queue at given priority
     *  @param p : priority of the element to add
     *  @param v : value of the element
     */
    void push(key_type p, value_type v);
    
    /**
     *  @brief Remove the front element of the queue with the highest priority.
     *  @pre The queue must not be empty.
     */
    void pop();
    
    /**
     *  @brief Return whether the hierarchical queue is empty.
     */
    bool empty();
    
    /**
     *  @brief Number of elements in the hierarchical queue.
     */
    size_type size() const;
    
    /**
     *  @brief Front element of the queue with the highest priority.
     *  @pre The queue must not be empty.
     */
    value_type const & front() const;
    
    /**
     *  @brief Highest (current) priority in the queue.
     *  @pre The queue must not be empty.
     */
    key_type const priority() const;

private:
    /**
     *  @brief Container's type.
     */
    typedef std::map<Priority, std::queue<Value>, Compare>  Container;
    
    /**
     *  @brief Comparison criterion.
     */
    Compare compare_;
    
    /**
     *  @brief Internal representation of data.
     */
    Container container_;
    
    /**
     *  @brief Current priority.
     */
    key_type currentPriority_;
    
    /**
     *  @brief Size of the queue (number of elements).
     */
    size_type size_; 
};

#include "hierarchical_queue.txx"

#endif // hierarchical_queue_h
