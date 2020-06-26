#include "JsString.h"
#include <iostream>

String::String()
{
  length = 0;
  str = NULL;
}

String::String(char val)
{
  length = 1;
  str = new char[2];
  str[0] = val;
  str[1] = '\0';
}

String::String(char const *val)
{
  if(val == NULL)
  {
    length = 0;
    str = NULL;
    return;
  }
  
  // Calculate length
  length = 0;
  while(val[length] != '\0')
    length++;

  // Allocate memory
  str = new char[length+1];

  // Copy char array
  for (unsigned int i = 0; i < length+1; i++)
    str[i] = val[i];  
}

String::String(int num)
{
  std::string tmp = std::to_string(num);
  length = 0;
  while(tmp[length] != '\0')
    length++;
  str = new char[length+1];
  for (unsigned int i = 0; i < length+1; i++)
    str[i] = tmp[i];
}

String::String(double num)
{
  std::string tmp = std::to_string(num);
  length = 0;
  while(tmp[length] != '\0')
    length++;
  str = new char[length+1];
  for (unsigned int i = 0; i < length+1; i++)
    str[i] = tmp[i];
}

String::String(const String &src)
{
  // Delete old str
  delete [] str;

  // Change length
  length = src.length;

  // Allocate new memory
  str = new char[length+1];

  // Copy char array
  for (unsigned int i = 0; i < length; i++)
  {
    str[i] = src[i];  
  }
  str[length] = '\0';
  std::cout << "Copy called, " << *this << std::endl;
}

String::String(String &&src)
{
  str = src.str;
  length = src.length;
  src.str = NULL;
  std::cout << "Move called, " << *this << std::endl;
}

String::~String()
{
  delete [] str;
}

char String::operator[](unsigned int i) const
{
  if(str == NULL)
    return '\0';
  else if(i >= length)
    return str[i%length];
  else if(i < 0)
    return str[length - (i % length)];
  else
    return str[i];
}

// Concanates two strings
String String::operator+(const String &right) const
{
  int newLength = length + right.length;
  char newStr[newLength+1];
  for (unsigned int i = 0; i < length; i++)
  {
    newStr[i] = str[i];
  }
  for (int i = length; i < newLength; i++)
  {
    newStr[i] = right[i-length];
  }
  newStr[newLength] = '\0';
  
  return String(newStr);
}

// Concanates two strings
String String::operator+(const char *right) const
{
  return String::operator+(String(right));
}

// Concanates a string and a char
String String::operator+(char right) const
{
  return String::operator+(String(right));
}

// Concanates two strings
String& String::operator+=(const String &right) 
{
  // Store old string in temp
  char tmp[length];
  for(unsigned int i = 0; i < length; i++)
    tmp[i] = str[i];

  // Delete old string
  delete [] str;

  // Create new size string
  str = new char[length + right.length];
  
  for(unsigned int i = 0; i < length; i++)
    str[i] = tmp[i];
 
  for(unsigned int i = length; i < length + right.length + 1; i++)
    str[i] = right.str[i - length];

  length += right.length;
  
  return *this;
}

// Concanates two strings
String& String::operator+=(const char *right) 
{
  return String::operator+=(String(right));
}

// Concanates two strings
String& String::operator+=(char right) 
{
  return String::operator+=(String(right));
}

String& String::operator=(String &&right)
{
  if(this != &right)
  {
    delete [] str;

    std::cout << "Assignment called, " << right << std::endl;

    str = right.str;
    length = right.length;

    right.str = NULL;
  }
  return *this;
}

void String::operator=(const String &right)
{
  std::cout << "asignmnt called void" << right << std::endl;
  // Delete old values
  delete [] str;
  length = right.length;

  // Allocate memory
  str = new char[length+1];

  for(unsigned int i = 0; i < right.length + 1; i++)
    str[i] = right.str[i];
}

void String::operator=(const char *right)
{
  String::operator=(String(right));
}

void String::operator=(char right)
{
  String::operator=(String(right));
}

int String::operator==(const String &right) const
{
  // If lengths does not match, return false
  if(length != right.length)
    return 0;

  // If there is unmatching char, return false
  for (unsigned int i = 0; i < length; i++)
    if(str[i] != right.str[i])
      return 0;
  
  // Passes all, return true
  return 1;
}

int String::operator==(const char *right) const
{
  return String::operator==(String(right));
}
int String::operator==(char val) const
{
  return String::operator==(String(val));
}

int String::operator!=(const String &right) const
{
  return !String::operator==(right);
}

int String::operator!=(const char *right) const
{
  return !String::operator==(right);
}

int String::operator!=(char val) const
{
  return !String::operator==(val);
}

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator>(const String &right) const
{
  int i = 0;
  while(str[i] != '\0' && right.str[i] != '\0')
  {
    if(str[i] >= 'A' && str[i] <= 'Z' && right.str[i] >= 'a' && right.str[i] <= 'z')
      return 1;
    else if(str[i] >= 'a' && str[i] <= 'z' && right.str[i] >= 'A' && right.str[i] <= 'Z')
      return 0;
    else if(str[i] > right.str[i])
      return 1;
    else if(right.str[i] > str[i])
      return 0;
    i++;
  }

  if(str[i] == '\0' && right.str[i] != '\0')
    return 1;
  else
    return 0;
}

int String::operator>(const char *right) const
{
  return String::operator>(String(right));
}

int String::operator>(char right) const
{
  return String::operator>(String(right));
}

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator>=(const String &right) const
{
  return String::operator>(right) || String::operator==(right);
}

int String::operator>=(const char *right) const
{
  return String::operator>=(String(right));
}

int String::operator>=(char right) const
{
  return String::operator>=(String(right));
}

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator<(const String &right) const
{
  return !String::operator>(right) && !String::operator==(right);
}

int String::operator<(const char *right) const
{
  return String::operator<(String(right));
}

int String::operator<(char right) const
{
  return String::operator<(String(right));
}

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator<=(const String &right) const
{
  return !String::operator>(right);
}

int String::operator<=(const char *right) const
{
  return String::operator<=(String(right));
}

int String::operator<=(char right) const
{
  return String::operator<=(String(right));
}

std::ostream& operator<<(std::ostream& os, const String& src)
{
  os << src.str;
  return os;
}

std::istream& operator>>(std::istream  &os, String &src )
{
  // Free old memory
  delete [] src.str;

  // Read input
  std::string tmp;
  std::getline(os, tmp);

  // Calculate length
  src.length = 0;
  while(tmp[src.length] != '\0')
  {
    src.length++;
  }

  // Copy values
  src.str = new char[src.length+1];
  for(unsigned int i = 0; i < src.length; i++)
  {
    src.str[i] = tmp[i];
  }
  src.str[src.length] = '\0';
  return os;
}

/**
 * @return Length of the string 
 */
int String::getLength() const
{
  return length;
}

/**
 * Removes whitespaces from both sides of the applied string
 */
void String::trim()
{
  int wf = 0, wb = 0;

  // Count whitespaces
  for(unsigned int i = 0; isspace(str[i]); i++)
    wf++;
  for(unsigned int i = length-1; isspace(str[i]); i--)
    wb++;
  
  // Copy trimmed to temporary
  int newLength = length-(wf+wb);
  char tmp[newLength];
  for (unsigned int i = wf; i < length - wb + 1; i++)
    tmp[i-wf] = str[i];
  
  // Copy back to str
  delete [] str;
  length = newLength;
  str = new char[newLength+1];
  for(unsigned int i = 0; i < length; i++)
    str[i] = tmp[i];
  str[length] = '\0';
}

/**
 * @return Converts string to integers and returns
 */
int String::toInt() const
{
  return std::stoi(str);
}

/**
 * @return Converts string to double and returns
 */
double String::toDouble() const
{
  return std::stod(str);
}

/**
 * Returns a new string containing characters of the calling string from (or between) the specified index (or indeces).
 * 
 * @param indexStart The index of the first character to include in the returned substring.
 * @param indexEnd The index of the first character to exclude from the returned substring.
 * @return A new JsString object containing the specified part of the given string.
 */
String String::substring(int indexStart, int indexEnd) const
{
  char tmp[indexEnd-indexStart+1];
  for (int i = indexStart; i < indexEnd; i++)
    tmp[i-indexStart] = str[i];
  tmp[indexEnd-indexStart] = '\0';
  return tmp;
}

/**
 * Returns the characters in a string beginning at the specified location through the specified number of characters.
 * 
 * @param start The index of the first character to include in the returned substring.
 * @param length Optional. The number of characters to extract.
 * If length is omitted, substr() extracts characters to the end of the string.
 * @return A new JsString object containing the specified part of the given string.
 */
String String::substr(int start, int inLength) const
{
  char tmp[inLength+1];
  for (int i = start; i < start+inLength; i++)
  {
    tmp[i-start] = str[i];
  }
  tmp[inLength] = '\0';
  return String(tmp);
}

String String::substr(int start) const
{
  return String::substr(start, length);
}

/**
 * Converts the string to lower case.
 * ('I like JsString' to 'i like jsstring')
 */
void String::toLowerCase()
{
  for (unsigned int i = 0; i < length; i++)
  {
    if(str[i] >= 'A' && str[i] <= 'Z')
    {
      str[i] = str[i] - 'A' + 'a';
    }
  }
}

/**
 * Converts the string to upper case.
 * ('I like JsString' to 'I LIKE JSSTRING')
 */
void String::toUpperCase()
{
  for (unsigned int i = 0; i < length; i++)
  {
    if(str[i] >= 'a' && str[i] <= 'z')
    {
      str[i] = str[i] - 'a' + 'A';
    }
  }
}

/**
 * Converts the string to camel case. Each letter after a space characther will be capitalized.
 * ('I like JsString' to 'I Like Jsstring')
 */
void String::toCamelCase()
{
  int isPreviousSpace = 1;
  for (unsigned int i = 0; i < length; i++)
  {
    // Capitalize or decapitalize if necessary
    if(str[i] >= 'a' && str[i] <= 'z' && isPreviousSpace)
      str[i] = str[i] - 'a' + 'A';
    else if(str[i] >= 'A' && str[i] <= 'Z' && !isPreviousSpace)
      str[i] = str[i] - 'A' + 'a';

    // Check space for the next characther
    if(isspace(str[i]))
      isPreviousSpace = 1;
    else
      isPreviousSpace = 0;
  }
}

/**
 * Divides string by space characthers into an ordered array of substrings.
 * Could be used to extract array of words from a sentence.
 * 
 * @return std::vector<String>
 */
std::vector<String> String::splitBySpace() const
{
  std::vector<String> substrings;
  int starts[length], ends[length];
  int ptr = 0;
  int isSpace = 1;
  for (unsigned int i = 0; i < length; i++)
  {
    // Previous is space and current not -> Start of a new substring
    if(isSpace && !isspace(str[i]))
    {
      starts[ptr] = i;
      isSpace = 0;
    }

    // Previous char and current space -> End of a substring
    if(!isSpace && isspace(str[i]))
    {
      ends[ptr] = i;
      isSpace = 1;
      ptr++;
    }
  }

  // Check if ends with substring
  if(!isspace(str[length-1]))
  {
    ends[ptr] = length;
    ptr++;
  }

  for (int i = 0; i < ptr; i++)
    std::cout << starts[i] << "-" << ends[i] << std::endl;

  int size = ptr;
  for (int i = 0; i < size; i++)
  {
    std::cout << String::substring(starts[i], ends[i]) << std::endl;
    substrings.push_back(String::substring(starts[i], ends[i]));
    std::cout << substrings[i] << ", " << substrings.size() << std::endl;
  }
  return substrings;
}

/**
 * Divides string by given delimeter into an ordered array of substrings.
 * 
 * @param delimeter A characther which will be used to split string by.
 * Delimeter characther won't exist in newyl created substrings.
 * @return std::vector<String>
 * 
 * Use splitBySpace() for splitting by all space characthers '\n', ' ', '\t' etc.
 */
std::vector<String> String::split(char delimeter) const
{
  std::vector<String> substrings;
  int starts[length], ends[length];
  int ptr = 0;
  int isDelimeter = 1;
  for (unsigned int i = 0; i < length; i++)
  {
    // Previous is delimeter and current not -> Start of a new substring
    if(isDelimeter && str[i] != delimeter)
    {
      starts[ptr] = i;
      isDelimeter = 0;
    }

    // Current is delimeter and previous not -> End of a substring
    if(!isDelimeter && str[i] == delimeter)
    {
      ends[ptr] = i;
      isDelimeter = 1;
      ptr++;
    }
  }

  // Check if ends with substring
  if(str[length-1] != delimeter)
  {
    ends[ptr] = length;
    ptr++;
  }

  for (int i = 0; i < ptr; i++)
    std::cout << starts[i] << "-" << ends[i] << std::endl;

  int size = ptr;
  for (int i = 0; i < size; i++)
  {
    String tmp = String::substring(starts[i], ends[i]);
    std::cout << tmp << std::endl;
    substrings.push_back(tmp);
    std::cout << substrings[i] << ", " << substrings.size() << std::endl;
  }
  return substrings;
}