//what is itertor?
// iterator is pretty like pointer whose most important jobs are operator* and operator->

// Let us design a list iterator, assume that list and node's structure are listed below:
#include <iostream>
template<typename T>
class ListElem
{
    public:
    T value(){ return value_; }
    ListElem* next() const { return next_; }
    private:
    T value_;
    ListElem* next_;
};

template<typename T>
class SampleList
{
    public:
    void insert_front(T value);
    void insert_end(T value);
    void display(std::ostream& os = std::cout) const;
    ListElem<T>* front() const { return front_; }
    // ...
    private:
    ListElem<T>* end_;
    ListElem<T>* front_;
    long size_;
};

// A problem we are facing now is how to make SampleList work with std::find() function?
// one solution is to to create a pointer-alike hat for it, more specifically to say, an iterator.
// when we dereference this iterator, the ListElem object should be returned; 
// When we increment it, it should points out to the next ListEle object. 
// In order to make it work for any type of data more than ListElem, 
// we can treat it as a class template as shown below:

//! the Item represents the elem node in SampleList and only serve for SampleList
// due to its special operator++() method
template <typename Item>
struct ListIter
{
    Item* pointer_; //!< keep a reference to container
    ListIter(Item* pointer = nullptr) : pointer_(pointer) {} //!< default ctor

    // no need to implement copy ctor, default one is working well
    // no need to implement operator==, default one is working well

    Item& operator*() const
    {
        return *pointer_;
    }

    Item* operator->() const
    {
        return pointer_;
    }

    // the following two operator++  are std-conforming 
    // (1) pre-incre operator
    ListIter& operator++()
    {
        pointer_ = pointer_->next(); return *this;
    }
    // (2) post-incre operator
    ListIter operator++(int)
    {
        ListIter tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator== (const ListIter& i) const
    {
        return pointer_ == i->pointer_;
    }
    bool operator!=(const ListIter& i) const
    {
        return pointer_ != i->pointer_;
    }
};


// As we konw, std::find() uses *iter != value to find value. In our example, value's type is int, iter's type is ListElem<int>, and so we have to provide a glabal operator!=. the reason why not add operator!= in ListIter is that there is no way to fetch the type of int from ListIter.
template <typename value_type>
bool operator!=(const ListElem<value_type>& elem, value_type n)
{
    return elem.value() != n;
}

// now, we can let our SampleList work with std::find() with the help of ListIter:
void main()
{
    SampleList<int> myList;
    for (int i = 0; i < 5; ++i)
    {
        myList.insert_front(i);
        myList.insert_end(i + 2);
    }

    myList.display(); // 10 elements (4, 3, 2, 1, 0, 2, 3, 4, 5, 6)

    ListIter<ListElem<int>> begin(myList.front());
    ListIter<ListElem<int>> end; //!< default nullptr
    ListIter<ListElem<int>> iter; //!< default nullptr

    iter = std::find(begin, end, 3);

    if (iter == end)
    {
        std::cout << "not found" << std::endl;
    }
    else {
        std::cout << "found" << "value is " << iter->value() << std::endl;
    }

    // run result: not found
}

// based on above, in order to create a iterator for our list class, too many implementation details have been exposed: 
// in main() function, begain and end interators exposed ListElem class;
// in class ListIter, we expose ListElem's next() method in order to implement operator++. If this is the case, why not let the list designer people handle everything. If so, all the implementation details will be hidden from outside. This is why all stl containers have their own iterators.




