template<typename T>
T& Iterator<T>::operator*()
{ 
    return current->object;
}

template<typename T>
T* Iterator<T>::operator->()
{
    return &current->object;
}

// сравнение
template<typename T>
bool Iterator<T>::operator==(const Iterator& other) const
{
    return current == other.current;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator& other) const
{
    return current != other.current;
}

// prefix ++
template<typename T>
Iterator<T>& Iterator<T>::operator++ ()
{
    if (current)
    {
        current = current->next;
    }
    return *this;
}

// postfix ++
template<typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

// prefix -- (медленная реализация для однонаправленного списка)
template<typename T>
Iterator<T>& Iterator<T>::operator--()
{
    if (!owner || !current || current == owner->getFront())
    {
        return *this;
    }

    Unit<T>* node = owner->getFront();
    Unit<T>* prev = nullptr;

    while (node && node != current)
    {
        prev = node;
        node = node->next;
    }

    if (prev)
    {
        current = prev;
    }

    return *this;
}

// postfix --
template<typename T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator temp = *this;
    --(*this);
    return temp;
}


template<typename T>
Unit<T>* Iterator<T>::getNode() const
{ 
    return current;
}

