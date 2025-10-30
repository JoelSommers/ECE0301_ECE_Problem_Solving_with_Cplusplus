#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "Database.hpp"

const double THRESHOLD = 1e-9;

/* Provided test cases */

TEST_CASE("Test default construction", "[database]")
{
    Database db;
    REQUIRE(db.is_empty());
    REQUIRE(db.size() == 0);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 0);
}

TEST_CASE("Test construction with one Entry", "[database]")
{
    // 7400 NAND data
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    Entry test_entry = {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30};
    Database db(test_entry);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == 1);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 1);
    REQUIRE(test[0].id == test_entry.id);
    REQUIRE(test[0].name == test_entry.name);
    REQUIRE(test[0].units == test_entry.units);
    REQUIRE(test[0].pins == test_entry.pins);
    REQUIRE(test[0].transistors == test_entry.transistors);
    REQUIRE(std::abs(test[0].max_delay - test_entry.max_delay) <= THRESHOLD);
    REQUIRE(std::abs(test[0].power_per_unit - test_entry.power_per_unit) <= THRESHOLD);
    REQUIRE(std::abs(test[0].bulk_price - test_entry.bulk_price) <= THRESHOLD);
}

TEST_CASE("Test construction with vector", "[database]")
{
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    std::vector<Entry> entries = {
        // quad 2-input NAND gates
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // quad 2-input AND gates
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single 8-input NAND gate
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        // single BCD to 7-segment display
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // dual JK Flip-Flops
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 4-bit Adder with carry
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 8-bit Shift Register
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}};
    Database db(entries);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == entries.size());

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == entries.size());
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE(test[i].id == entries[i].id);
        REQUIRE(test[i].name == entries[i].name);
        REQUIRE(test[i].units == entries[i].units);
        REQUIRE(test[i].pins == entries[i].pins);
        REQUIRE(test[i].transistors == entries[i].transistors);
        REQUIRE(std::abs(test[i].max_delay - entries[i].max_delay) <= THRESHOLD);
        REQUIRE(std::abs(test[i].power_per_unit - entries[i].power_per_unit) <= THRESHOLD);
        REQUIRE(std::abs(test[i].bulk_price - entries[i].bulk_price) <= THRESHOLD);
    }
}

TEST_CASE("Test search", "[database]")
{
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    std::vector<Entry> entries = {
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}};

    Database dbdefault;
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE_FALSE(dbdefault.search(entries[i].id));
    }

    Database dbentry(entries[0]);
    REQUIRE(dbentry.search(entries[0].id));

    Database db(entries);
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE(db.search(entries[i].id));
    }
}

TEST_CASE("Test add and size", "[database]")
{
    // add entry to default class
    Database db;
    Entry test_entry = {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30};
    REQUIRE(db.add(test_entry));
    REQUIRE(db.size() == 1);

    // add duplicate
    REQUIRE_FALSE(db.add(test_entry));
    REQUIRE(db.size() == 1);

    // add another entry
    Entry test_entry2 = {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30};
    REQUIRE(db.add(test_entry2));
    REQUIRE(db.size() == 2);
}

TEST_CASE("Test remove, search, size, and is_empty", "[database]")
{
    // remove an entry from data
    std::vector<Entry> entries = {
        // quad 2-input NAND gates
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // quad 2-input AND gates
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single 8-input NAND gate
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        // single BCD to 7-segment display
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // dual JK Flip-Flops
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 4-bit Adder with carry
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 8-bit Shift Register
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}};
    Database db(entries);
    REQUIRE(db.remove(7430));
    REQUIRE_FALSE(db.search(7430));
    REQUIRE(db.size() == 6);

    // remove a non-existing id
    REQUIRE_FALSE(db.remove(7402));

    // remove all data and check that data is empty
    REQUIRE(db.remove(7400));
    REQUIRE(db.remove(7408));
    REQUIRE(db.remove(7447));
    REQUIRE(db.remove(7473));
    REQUIRE(db.remove(7483));
    REQUIRE(db.remove(7491));
    REQUIRE(db.is_empty());
}

TEST_CASE("Test sort_by_id", "[database]")
{
    // create out of order entries
    std::vector<Entry> entries = {
        // quad 2-input NAND gates
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // quad 2-input AND gates
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60},
        // single 8-input NAND gate
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single BCD to 7-segment display
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // dual JK Flip-Flops
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 4-bit Adder with carry
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 8-bit Shift Register
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40}};
    Database db(entries);
    // add each entry one by one to data
    for (int i = 0; i < entries.size(); i++)
    {
        db.add(entries[i]);
    }

    // sort id by ascending order
    db.sort_by_id(true);

    // test that the data is in ascending order
    // create entry in ascending order
    std::vector<Entry> ascending = {
        // quad 2-input NAND gates
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // quad 2-input AND gates
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single 8-input NAND gate
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        // single BCD to 7-segment display
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // dual JK Flip-Flops
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 4-bit Adder with carry
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 8-bit Shift Register
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}};
    // get the entries of the db database
    std::vector<Entry> test = db.get_all_entries();

    // test that both vectors are identical
    for (int i = 0; i < test.size(); i++)
    {
        REQUIRE(ascending[i].id == test[i].id);
    }

    // sort id by descending order
    db.sort_by_id(false);

    // test that the data is in descending order
    // create entry in descedning order
    std::vector<Entry> descending = {
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60},
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30}};
    // get the entries of the db database
    std::vector<Entry> test2 = db.get_all_entries();

    // test that both vectors are identical
    for (int i = 0; i < test.size(); i++)
    {
        REQUIRE(descending[i].id == test2[i].id);
    }
}

TEST_CASE("Test sort_by_name", "[database]")
{
    // create out of order entries
    std::vector<Entry> entries = {
        // quad 2-input NAND gates
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // quad 2-input AND gates
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60},
        // single 8-input NAND gate
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single BCD to 7-segment display
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // dual JK Flip-Flops
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 4-bit Adder with carry
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 8-bit Shift Register
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40}};
    Database db(entries);
    // add each entry one by one to data
    for (int i = 0; i < entries.size(); i++)
    {
        db.add(entries[i]);
    }

    // sort name by alphabetical order
    db.sort_by_name();

    // test that the data is in alphabetical order
    // create entry in alphabetical order
    std::vector<Entry> alphabetical = {
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}};
    // get the entries of the db database
    std::vector<Entry> test = db.get_all_entries();

    // test that both vectors are identical
    for (int i = 0; i < test.size(); i++)
    {
        REQUIRE(alphabetical[i].name == test[i].name);
    }
}