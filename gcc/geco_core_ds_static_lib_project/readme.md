1. simply drag include and src directories into the project
2. stick link to project
3. create new file under the newly created dir
4. that file will also appear in the real dir.
5. so good.

/**
 An iterator is an object that can iterate over elements
 (navigate from element to element).These elements may
 be all or a subset of the elements of an STL container.
 An iterator represents a certain position in a container.

 The following fundamental operations define the behavior
 of an iterator:
 • Operator * returns the element of the current position.
 If the elements have members, you can
 use operator -> to access those members directly from the iterator.
 • Operator ++ lets the iterator step forward to the next element.
 Most iterators also allow stepping backward by using operator --.
 • Operators == and != return whether two iterators
 represent the same position.
 • Operator = assigns an iterator (the position of the element
 to which it refers).

 The internal behavior of iterators depends on the data structure
 over which they iterate.Hence, each container type supplies its
 own kind of iterator. As a result, iterators share the same interface
 but have different types.

 This leads directly to the concept of generic programming:
 Operations use the same interface but different types,
 so you can use templates to formulate generic operations
 that work with arbitrary types that satisfy the interface.
 eg. all operations of algorism advance(), low_bund() such operations
 accept certain iterator types and use the the common interfaces
 of the iterators to connect container and algorism
 
 Operations of Output Iterators
 Expression                Effect
*iter = val                  Writes val to where the iterator refers
++iter                       Steps forward (returns new position)
iter++                       Steps forward (returns old position)
TYPE(iter)                  Copies iterator (copy constructor)

Input iterators can read elements only once. 
Thus, if you copy an input iterator and let the original
and the copy read forward, they might iterate over different values.

Unlike for input iterators, it is guaranteed that for two forward iterators 
that refer to the same element, operator == yields true and that they 
will refer to the same value after both are incremented.
 */