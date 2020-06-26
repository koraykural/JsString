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
  // Constructers
  String();
  String(char);
  String(char const *);
  String(int);
  String(double);
  String(const String &);
  String(String &&);

  ~String();

  // Operators
  char operator[](unsigned int) const;
  String operator+(const String &) const;
  String operator+(const char*) const;
  String operator+(char) const;
  String& operator+=(const String &);
  String& operator+=(const char*);
  String& operator+=(char);
  String& operator=(String &&);
  void operator=(const String &);
  void operator=(const char*);
  void operator=(char);
  int operator==(const String &) const;
  int operator==(const char*) const;
  int operator==(char) const;
  int operator!=(const String &) const;
  int operator!=(const char*) const;
  int operator!=(char) const;
  int operator>(const String &) const;
  int operator>(const char *) const;
  int operator>(char) const;
  int operator>=(const String &) const;
  int operator>=(const char *) const;
  int operator>=(char) const;
  int operator<(const String &) const;
  int operator<(const char *) const;
  int operator<(char) const;
  int operator<=(const String &) const;
  int operator<=(const char *) const;
  int operator<=(char) const;
  friend std::ostream& operator<<(std::ostream &, const String& );
  friend std::istream& operator>>(std::istream &, String & );

  // Methods
  int getLength() const;
  void trim();
  int toInt() const;
  double toDouble() const;
  String substring(int indexStart, int indexEnd) const;
  String substr(int start, int length) const;
  String substr(int start) const;
  void toLowerCase();
  void toUpperCase();
  void toCamelCase();
  std::vector<String> splitBySpace() const;
  std::vector<String> split(char delimeter) const;
};

#endif
