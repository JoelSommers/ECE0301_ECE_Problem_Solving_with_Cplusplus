#include "Database.hpp"

// initialize empty data
Database::Database() : num_entries(0) {}

// initialize with one row of Entry
Database::Database(Entry d)
{
  data.push_back(d);
  num_entries = 1;
}

// initialize with vector
Database::Database(std::vector<Entry> d)
{
  data = d;
  num_entries = d.size();
}

// add function
bool Database::add(Entry d)
{
  // check for duplicate
  for (int i = 0; i < data.size(); i++)
  {
    if (data[i].id == d.id)
      return false;
  }

  // add to the end of data
  data.push_back(d);
  num_entries += 1;
  return true;
}

// remove function
bool Database::remove(int id)
{
  // loop through data to find the index of the specified id
  int index = 0;
  bool found = false;
  for (int i = 0; i < data.size(); i++)
  {
    if (data[i].id == id)
    {
      found = true;
      break;
    }
    index++;
  }

  // return false if id isn't found
  if (found == false)
  {
    return false;
  }

  // remove entry
  data.erase(data.begin() + index);
  num_entries--;
  return true;
}

// size function
int Database::size() const
{
  return num_entries;
}

// is_empty function
bool Database::is_empty() const
{
  if (data.empty() && num_entries == 0)
    return true;
  else
    return false;
}

// search function
bool Database::search(int id) const
{
  // loop through data to search for id
  for (int i = 0; i < data.size(); i++)
  {
    if (data[i].id == id)
      return true;
  }
  return false;
}

// get_all_entries function
std::vector<Entry> Database::get_all_entries() const
{
  std::vector<Entry> copy = data;
  return copy;
}

// sort_by_id function
void Database::sort_by_id(bool ascending)
{
  if (ascending)
  {
    // bubble sort
    bool exchange;
    Entry temp;

    while (1)
    {
      exchange = false;
      for (int i = 0; i < data.size() - 1; i++)
      {
        if (data[i].id > data[i + 1].id)
        {
          temp = data[i];
          data[i] = data[i + 1];
          data[i + 1] = temp;
          exchange = true;
        }
      }
      if (exchange == false)
      {
        break;
      }
    }
  }

  else
  {
    // same implementation, but just change greater than to less than
    bool exchange;
    Entry temp;

    while (1)
    {
      exchange = false;
      for (int i = 0; i < data.size() - 1; i++)
      {
        if (data[i].id < data[i + 1].id)
        {
          temp = data[i];
          data[i] = data[i + 1];
          data[i + 1] = temp;
          exchange = true;
        }
      }
      if (exchange == false)
      {
        break;
      }
    }
  }
}

// sort_by_name function
void Database::sort_by_name()
{
  bool exchange = false;
  Entry temp;

  while (1)
  {
    exchange = false;
    // loop through entries
    for (int i = 0; i < data.size() - 1; i++)
    {
      // loop through each letter of the name
      for (int j = 0; j < data[i].name.length(); j++)
      {
        // if they are already in order than break out of loop
        if (data[i].name[j] < data[i + 1].name[j])
        {
          break;
        }
        // swap if the letter of name comes after the other entries letter of name in the alphabet
        if (data[i].name[j] > data[i + 1].name[j])
        {
          temp = data[i];
          data[i] = data[i + 1];
          data[i + 1] = temp;
          exchange = true;
          break;
        }
      }
    }
    if (exchange == false)
    {
      break;
    }
  }
}

// search_criteria function
int Database::search_criteria(double upper[3]) const
{
  // loop through the data
  for (int i = 0; i < data.size(); i++)
  {
    // re-read the decription for the function and realized that the values of upper were the capped values not the exact value (AFTER 2ND ATTEMPT)!!!
    if (data[i].max_delay <= upper[0] && data[i].power_per_unit <= upper[1] && data[i].bulk_price <= upper[2])
      return data[i].id;
  }
  return -1;
}
