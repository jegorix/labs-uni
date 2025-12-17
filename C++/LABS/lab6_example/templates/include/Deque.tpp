template<typename T>
Deque<T>::Deque() {
    this->top = nullptr;
    this->bottom = nullptr;
}

template<typename T>
Deque<T>::Deque(const Deque& other) {
    this->top = nullptr;
    this->bottom = nullptr;
    DequeNode<T>* current = other.top;
    while (current != nullptr) {
        this->pushBack(current->value);
        current = current->next;
    }
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
    if (this != &other) {
        this->clearDeque();
        DequeNode<T>* current = other.top;
        while (current != nullptr) {
            this->pushBack(current->value);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
Deque<T>::~Deque() {
    while (!this->isEmpty()) {
        this->popFront();
    }
}

template<typename T>
void Deque<T>::pushFront(const T& value) {
    DequeNode<T>* newNode = new DequeNode<T>{value, nullptr, this->top};
    
    if (this->isEmpty()) {
        this->top = newNode;
        this->bottom = newNode;
    } else {
        this->top->prev = newNode;
        this->top = newNode;
    }
}

template<typename T>
void Deque<T>::pushBack(const T& value) {
    DequeNode<T>* newNode = new DequeNode<T>{value, this->bottom, nullptr};
    
    if (this->isEmpty()) {
        this->top = newNode;
        this->bottom = newNode;
    } else {
        this->bottom->next = newNode;
        this->bottom = newNode;
    }
}

template<typename T>
void Deque<T>::popFront() {
    if (this->isEmpty()) {
        return;
    }
    
    DequeNode<T>* temp = this->top;
    this->top = this->top->next;
    
    if (this->top != nullptr) {
        this->top->prev = nullptr;
    } else {
        this->bottom = nullptr;
    }
    
    delete temp;
}

template<typename T>
void Deque<T>::popBack() {
    if (this->isEmpty()) {
        return;
    }
    
    DequeNode<T>* temp = this->bottom;
    this->bottom = this->bottom->prev;
    
    if (this->bottom != nullptr) {
        this->bottom->next = nullptr;
    } else {
        this->top = nullptr;
    }
    
    delete temp;
}

template<typename T>
T& Deque<T>::peekFirst() {
    return this->top->value;
}
    
template<typename T>
T& Deque<T>::peekLast() {
    return this->bottom->value;
}

template<typename T>
bool Deque<T>::isEmpty() const {
    return this->top == nullptr;
}

template<typename T>
int Deque<T>::size() const {
    int count = 0;
    DequeNode<T>* current = this->top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template<typename T>
Deque<T> Deque<T>::find(const T& value) const {
    Deque<T> searchResults;
    DequeNode<T>* current = this->top;
    while (current != nullptr) {
        if (*(current->value) == *value) { 
            searchResults.pushBack(current->value);
        }
        current = current->next;
    }
    return searchResults;
}

template<typename T>
void Deque<T>::sort() {
    if (this->isEmpty() || this->top->next == nullptr) return;
    
    bool swapped;
    do {
        swapped = false;
        DequeNode<T>* current = this->top;
        while (current->next != nullptr) {
            if (*(current->next->value) < *(current->value)) {
                swap(current->value, current->next->value);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}
