// Position.h
#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <iostream>

class Position {
private:
    int id;
    std::string title;
    bool occupied;
    std::string employeeId;
    std::string timestamp;

public:
    Position();
    Position(int id, std::string title, bool occ, std::string empId, std::string ts);
    Position(const Position& other);
    ~Position();
    Position& operator=(const Position& other);
    void print(std::ostream&) const;
    void read(std::istream&);
    void serializeBinary(std::ostream&) const;
    void deserializeBinary(std::istream&);
    int getId() const;
    void setId(int);
    std::string getTitle() const;
    void setTitle(std::string);
    bool getOccupied() const;
    void setOccupied(bool);
    std::string getEmployeeId() const;
    void setEmployeeId(std::string);
    std::string getTimestamp() const;
    void setTimestamp(std::string);
    friend std::ostream& operator<<(std::ostream&, const Position&);
    friend std::istream& operator>>(std::istream&, Position&);
};

#endif // POSITION_H