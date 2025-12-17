#ifndef RING_H
#define RING_H

#include "RingNote.h"
#include "Shkolnik.h"
#include <vector>
#include <functional>

class Ring {
private:
    RingNote<Shkolnik>* head;
    int size;

public:
    Ring();
    ~Ring();

    void add(const Shkolnik& data);
    bool remove(const Shkolnik& data);
    void display() const;
    RingNote<Shkolnik>* search(const Shkolnik& data) const;
    std::vector<Shkolnik> findAll(const std::function<bool(const Shkolnik&)>& pred) const;
    RingNote<Shkolnik>* findFirst(const std::function<bool(const Shkolnik&)>& pred) const;
    void sort();
    void sortWith(const std::function<bool(const Shkolnik&, const Shkolnik&)>& comp);
    int getSize() const;
    bool isEmpty() const;
    void clear();
    void forEach(const std::function<void(const Shkolnik&)>& fn) const;
    std::vector<Shkolnik> toVector() const;
};

#endif // RING_H
