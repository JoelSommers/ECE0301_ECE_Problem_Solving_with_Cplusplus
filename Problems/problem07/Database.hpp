#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <string>
#include <vector>
#include <cmath>

struct Entry
{
    int id;
    std::string name;
    int units, pins, transistors;
    double max_delay, power_per_unit, bulk_price;
};

// Database class declaration below
class Database
{
private:
    int num_entries;
    std::vector<Entry> data;

public:
    // default constructor
    Database();

    // constructor that takes an argument of type Entry
    Database(Entry d);

    // A constructor that takes std::vector<Entry> as an argument
    Database(std::vector<Entry> d);

    // A method add that takes an argument of type Entry and returns a bool
    bool add(Entry d);

    // A method remove that takes an argument of type int (the id) and returns a bool
    bool remove(int id);

    // A const method size that takes no arguments and returns an int that indicates the number of entries in the database
    int size() const;

    // A const method is_empty that takes no arguments and returns a bool that indicates whether the database is empty (no entries)
    bool is_empty() const;

    // A const method search that takes an argument of type int (the id) and returns a bool that indicates whether an entry with the specified ID exists in the database
    bool search(int id) const;

    // A const method get_all_entries that takes no arguments and returns a std::vector<Entry>
    std::vector<Entry> get_all_entries() const;

    // A method sort_by_id that takes an argument of type bool (called ascending) and returns nothing. The bool argument should be true by default (use a default argument value).
    void sort_by_id(bool ascending = true);

    // A method sort_by_name that takes no arguments and also returns nothing...
    void sort_by_name();

    // A const method search_criteria that takes an argument of an array of double of size 3 and returns an int that indicates the ID of the first entry that satisfies the criteria...
    int search_criteria(double upper[3]) const;
};

#endif
