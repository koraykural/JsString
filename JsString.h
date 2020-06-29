#ifndef JSSTRING_H
#define JSSTRING_H

#include <iostream>
#include <vector>

class String
{
private:
  char *str;
  unsigned int length;
public:
  String();
  String(char);
  String(char const *);
  String(int);
  String(double);
  String(const String &);
  String(String &&);
  ~String();

  char operator[](unsigned int) const;
  String operator+(const String &) const;
  String& operator+=(const String &);
  String& operator=(String &&);
  // void operator=(const String &);
  int operator==(const String &) const;
  int operator!=(const String &) const;
  int operator>(const String &) const;
  int operator>=(const String &) const;
  int operator<(const String &) const;
  int operator<=(const String &) const;
  friend std::ostream& operator<<(std::ostream &, const String& );
  friend std::istream& operator>>(std::istream &, String & );

  int get_length() const;
  void trim_front();
  void trim_back();
  void trim();
  int to_int() const;
  double to_double() const;
  String substring(unsigned int indexStart, unsigned int indexEnd) const;
  String substr(unsigned int start, unsigned int length) const;
  String substr(unsigned int start) const;
  void to_lower_case();
  void to_upper_case();
  void to_camel_case();
  std::vector<String> split_by_space() const;
  std::vector<String> split(char delimeter) const;
  int c_split_by_space(String **&substrings) const;
  int c_split(String **&substrings, char delimeter) const;
  int first_index_of(String search_term, unsigned int from_index = 0) const;
  int last_index_of(String search_term, unsigned int from_index = 0) const;
  int includes(String search_term) const;
  String replace(String search_term, String new_value) const;
  String replace_all(String search_term, String new_value) const;
};

#endif
