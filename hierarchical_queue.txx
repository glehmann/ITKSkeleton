#ifndef hierarchical_queue_txx
#define hierarchical_queue_txx

template<typename Priority, typename Value, typename Compare>
hierarchical_queue<Priority, Value, Compare>
::hierarchical_queue() : 
    compare_(), container_(), size_(0)
{
}


template<typename Priority, typename Value, typename Compare>
hierarchical_queue<Priority, Value, Compare>
::hierarchical_queue(const hierarchical_queue<Priority, Value, Compare> & src) :
    compare_(src.compare_), container_(src.container_),  
    currentPriority_(src.currentPriority_), size_(src.size_)
{
}


template<typename Priority, typename Value, typename Compare>
hierarchical_queue<Priority, Value, Compare>
::~hierarchical_queue()
{
}


template<typename Priority, typename Value, typename Compare>
void 
hierarchical_queue<Priority, Value, Compare>
::push(key_type p, value_type v)
{            
    if(size_ == 0)
    {
        currentPriority_ = p;
    }
    else if(compare_(p, currentPriority_))
    {
        currentPriority_ = p;
    }
    // else : don't change the current priority
    
    container_[p].push(v);
    ++size_;
}


template<typename Priority, typename Value, typename Compare>
void 
hierarchical_queue<Priority, Value, Compare>
::pop()
{
    container_.begin()->second.pop();
    --size_;
    if(container_.begin()->second.empty())
    {
        container_.erase(container_.begin());
        if(size_ != 0) currentPriority_ = container_.begin()->first;
    }
}


template<typename Priority, typename Value, typename Compare>
bool 
hierarchical_queue<Priority, Value, Compare>
::empty()
{
    return (size_ == 0);
}


template<typename Priority, typename Value, typename Compare>
typename hierarchical_queue<Priority, Value, Compare>::size_type 
hierarchical_queue<Priority, Value, Compare>
::size() const
{
    return size_;
}


template<typename Priority, typename Value, typename Compare>
typename hierarchical_queue<Priority, Value, Compare>::value_type const & 
hierarchical_queue<Priority, Value, Compare>
::front() const
{
    return container_.begin()->second.front();
}


template<typename Priority, typename Value, typename Compare>
typename hierarchical_queue<Priority, Value, Compare>::key_type const 
hierarchical_queue<Priority, Value, Compare>
::priority() const
{
    return currentPriority_;
}
    
    

#endif // hierarchical_queue_txx
