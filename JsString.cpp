#include "JsString.h"

#include "JsString.h"

String::String()
{
  length = 0;
  str = nullptr;
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
  if(val == nullptr)
  {
    length = 0;
    str = nullptr;
    return;
  }
  
  // Calculate length
  length = 0;
  while(val[length] != '\0')
  {
    length++;
  }

  // Allocate memory
  str = new char[length+1];

  // Copy char array
  for (unsigned int i = 0; i < length+1; i++)
  {
    str[i] = val[i];  
  }
}

String::String(int num)
{
  std::string tmp = std::to_string(num);
  length = 0;
  while(tmp[length] != '\0')
  {
    length++;
  }
  str = new char[length+1];
  for (unsigned int i = 0; i < length+1; i++)
  {
    str[i] = tmp[i];
  }
}

String::String(double num)
{
  std::string tmp = std::to_string(num);
  length = 0;
  while(tmp[length] != '\0')
  {
    length++;
  }
  str = new char[length+1];
  for (unsigned int i = 0; i < length+1; i++)
  {
    str[i] = tmp[i];
  }
}

String::String(const String &src)
{
  length = src.length;

  // Allocate new memory
  str = new char[length+1];

  // Copy char array
  for (unsigned int i = 0; i < length+1; i++)
  {
    str[i] = src.str[i];  
  }
}

String::String(String &&src)
{
  str = src.str;
  length = src.length;
  src.str = nullptr;
  src.length = 0;
}

String::~String()
{
  delete [] str;
}

#include "JsString.h"

char String::operator[](unsigned int i) const
{
  if(str == nullptr)
  {
    return '\0';
  }
  else if(i >= length)
  {
    return str[i%length];
  }
  else if(i < 0)
  {
    return str[length - (i % length)];
  }
  else
  {
    return str[i];
  }
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
String& String::operator+=(const String &right) 
{
  // Store old string in temp
  char tmp[length];
  for(unsigned int i = 0; i < length; i++)
  {
    tmp[i] = str[i];
  }

  // Delete old string
  delete [] str;

  // Create new size string
  str = new char[length + right.length];
  
  for(unsigned int i = 0; i < length; i++)
  {
    str[i] = tmp[i];
  }
 
  for(unsigned int i = length; i < length + right.length + 1; i++)
  {
    str[i] = right.str[i - length];
  }

  length += right.length;
  
  return *this;
}

String& String::operator=(String &&right)
{
  if(this != &right)
  {
    delete [] str;

    str = right.str;
    length = right.length;

    right.str = nullptr;
    right.length = 0;
  }
  return *this;
}

// void String::operator=(const String &right)
// {
//   // Delete old values
//   delete [] str;
//   length = right.length;

//   // Allocate memory
//   str = new char[length+1];

//   for(unsigned int i = 0; i < right.length + 1; i++)
//     str[i] = right.str[i];
// }

int String::operator==(const String &right) const
{
  // If lengths does not match, return false
  if(length != right.length)
  {
    return 0;
  }

  // If there is unmatching char, return false
  for (unsigned int i = 0; i < length; i++)
  {
    if(str[i] != right.str[i])
    {
      return 0;
    }
  }
  
  // Passes all, return true
  return 1;
}

int String::operator!=(const String &right) const
{
  return !(String::operator==(right));
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
    {
      return 1;
    }
    else if(str[i] >= 'a' && str[i] <= 'z' && right.str[i] >= 'A' && right.str[i] <= 'Z')
    {
      return 0;
    }
    else if(str[i] > right.str[i])
    {
      return 1;
    }
    else if(right.str[i] > str[i])
    {
      return 0;
    }
    i++;
  }

  if(str[i] == '\0' && right.str[i] != '\0')
  {
    return 1;
  }
  else
  {
    return 0;
  }
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

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator<(const String &right) const
{
  return !String::operator>(right) && !String::operator==(right);
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

std::ostream& operator<<(std::ostream& os, const String& src)
{
  if(src.length > 0)
  {
    os << src.str;
  }
  return os;
}

std::istream& operator>>(std::istream  &os, String &src )
{
  // Free old memory
  delete [] src.str;
  src.length = 0;

  // Read input
  std::string tmp;
  std::getline(os, tmp);

  // Calculate length
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

char String::operator[](unsigned int i) const
{
  if(str == nullptr)
  {
    return '\0';
  }
  else if(i >= length)
  {
    return str[i%length];
  }
  else if(i < 0)
  {
    return str[length - (i % length)];
  }
  else
  {
    return str[i];
  }
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
String& String::operator+=(const String &right) 
{
  // Store old string in temp
  char tmp[length];
  for(unsigned int i = 0; i < length; i++)
  {
    tmp[i] = str[i];
  }

  // Delete old string
  delete [] str;

  // Create new size string
  str = new char[length + right.length];
  
  for(unsigned int i = 0; i < length; i++)
  {
    str[i] = tmp[i];
  }
 
  for(unsigned int i = length; i < length + right.length + 1; i++)
  {
    str[i] = right.str[i - length];
  }

  length += right.length;
  
  return *this;
}

String& String::operator=(String &&right)
{
  if(this != &right)
  {
    delete [] str;

    str = right.str;
    length = right.length;

    right.str = nullptr;
    right.length = 0;
  }
  return *this;
}

// void String::operator=(const String &right)
// {
//   // Delete old values
//   delete [] str;
//   length = right.length;

//   // Allocate memory
//   str = new char[length+1];

//   for(unsigned int i = 0; i < right.length + 1; i++)
//     str[i] = right.str[i];
// }

int String::operator==(const String &right) const
{
  // If lengths does not match, return false
  if(length != right.length)
  {
    return 0;
  }

  // If there is unmatching char, return false
  for (unsigned int i = 0; i < length; i++)
  {
    if(str[i] != right.str[i])
    {
      return 0;
    }
  }
  
  // Passes all, return true
  return 1;
}

int String::operator!=(const String &right) const
{
  return !(String::operator==(right));
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
    {
      return 1;
    }
    else if(str[i] >= 'a' && str[i] <= 'z' && right.str[i] >= 'A' && right.str[i] <= 'Z')
    {
      return 0;
    }
    else if(str[i] > right.str[i])
    {
      return 1;
    }
    else if(right.str[i] > str[i])
    {
      return 0;
    }
    i++;
  }

  if(str[i] == '\0' && right.str[i] != '\0')
  {
    return 1;
  }
  else
  {
    return 0;
  }
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

/**
 * Comparison by lexicographical order of the leftmost characthers.
 * Case sensitive ("Ab" > "ab" == true).
 * If both strings goes identical, shorter string is greater ("ab" > "ab..." == true).
 */
int String::operator<(const String &right) const
{
  return !String::operator>(right) && !String::operator==(right);
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

std::ostream& operator<<(std::ostream& os, const String& src)
{
  if(src.length > 0)
  {
    os << src.str;
  }
  return os;
}

std::istream& operator>>(std::istream  &os, String &src )
{
  // Free old memory
  delete [] src.str;
  src.length = 0;

  // Read input
  std::string tmp;
  std::getline(os, tmp);

  // Calculate length
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
int String::get_length() const
{
  return length;
}

/**
 * Removes whitespaces from starting side of the string
 */
void String::trim_front()
{
  // Count whitespaces
  int wf = 0;
  for(unsigned int i = 0; isspace(str[i]); i++)
  {
    wf++;
  }

  // Copy trimmed to temporary
  int newLength = length - wf;
  char tmp[newLength];
  for (unsigned int i = wf; i < length + 1; i++)
  {
    tmp[i-wf] = str[i];
  }

  // Delete old string
  delete [] str;

  // Copy back from temporary to str
  length = newLength;
  str = new char[newLength+1];
  for(unsigned int i = 0; i < length; i++)
  {
    str[i] = tmp[i];
  }
  str[length] = '\0';
}

/**
 * Removes whitespaces from ending side of the string
 */
void String::trim_back()
{
  int wb = 0;
  // Count whitespaces
  for(unsigned int i = length-1; isspace(str[i]); i--)
  {
    wb++;
  }

  // Copy trimmed to temporary
  int newLength = length - wb;
  char tmp[newLength];
  for (unsigned int i = 0; i < length - wb + 1; i++)
  {
    tmp[i] = str[i];
  }
  
  // Delete old string
  delete [] str;

  // Copy back from temporary to str
  length = newLength;
  str = new char[newLength+1];
  for(unsigned int i = 0; i < length; i++)
    str[i] = tmp[i];
  str[length] = '\0';
}

/**
 * Removes whitespaces from both sides of the string.
 * Use trimFront() or trimBack() for single side trim.
 */
void String::trim()
{
  String::trim_front();
  String::trim_back();
}

/**
 * Converts string to integer and returns it.
 * std::stoi() call.
 * 
 * @return {int}
 */
int String::to_int() const
{
  return std::stoi(str);
}

/**
 * Converts string to double and returns it.
 * std::stod() call.
 * 
 * @return {double}
 */
double String::to_double() const
{
  return std::stod(str);
}

/**
 * Returns a new string containing characters of the calling string
 * from (or between) the specified index (or indeces).
 * 
 * @param index_start {unsigned int} The index of the first character to include in the substring.
 * @param index_end {unsigned int} The index of the first character to exclude from the substring.
 * @return {JsString} A new JsString object containing the specified part of the given string.
 */
String String::substring(unsigned int index_start, unsigned int index_end) const
{
  // Create temporary string length of the requested substring
  char tmp[index_end-index_start+1];

  // Copy to temporary
  for (int i = index_start; i < index_end; i++)
  {
    tmp[i-index_start] = str[i];
  }
  tmp[index_end-index_start] = '\0';

  return String(tmp);
}

/**
 * Returns the characters in a string beginning at the
 * specified location through the specified number of characters.
 * 
 * @param start {unsigned int} The index of the first character to include in the substring.
 * @param length {unsigned int} Optional. The number of characters to extract.
 * If length is omitted, substr() extracts characters to the end of the string.
 * @return {JsString} A new JsString object containing the specified part of the given string.
 */
String String::substr(unsigned int start, unsigned int inLength) const
{
  // Create temporary string length of the requested substring
  char tmp[inLength+1];

  // Copy to temporary
  for (int i = start; i < start+inLength; i++)
  {
    tmp[i-start] = str[i];
  }
  tmp[inLength] = '\0';

  return String(tmp);
}

String String::substr(unsigned int start) const
{
  return String::substr(start, length);
}

/**
 * Converts the string to lower case.
 * ('I like JsString' -> 'i like jsstring')
 */
void String::to_lower_case()
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
 * ('I like JsString' -> 'I LIKE JSSTRING')
 */
void String::to_upper_case()
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
 * ('I like JsString' -> 'I Like Jsstring')
 */
void String::to_camel_case()
{
  int isPreviousSpace = 1;
  for (unsigned int i = 0; i < length; i++)
  {
    // Capitalize or decapitalize if necessary
    if(str[i] >= 'a' && str[i] <= 'z' && isPreviousSpace)
    {
      str[i] = str[i] - 'a' + 'A';
    }
    else if(str[i] >= 'A' && str[i] <= 'Z' && !isPreviousSpace)
    {
      str[i] = str[i] - 'A' + 'a';
    }

    // Check space for the next characther
    if(isspace(str[i]))
    {
      isPreviousSpace = 1;
    }
    else
    {
      isPreviousSpace = 0;
    }
  }
}

/**
 * Divides string by space characthers into an ordered array of substrings.
 * Could be used to extract array of words from a sentence.
 * 
 * @return {std::vector<String>}
 */
std::vector<String> String::split_by_space() const
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

  // Extract substrings and push to vector
  int size = ptr;
  for (int i = 0; i < size; i++)
  {
    substrings.push_back(String::substring(starts[i], ends[i]));
  }

  return substrings;
}

/**
 * Divides string by space characthers into an ordered array of substrings.
 * Could be used to extract array of words from a sentence.
 * 
 * @param substrings {JsString**} Will allocate memory for an array of JsString objects.
 * @return {int} Number of substrings found. Also size of the allocated substrings array.
 * 
 * Important! Memory should be deallocated by user.
 * 
 * Usage example:
 * String my_string = "I like JsString.";
 * String **substrings = nullptr;
 * int size = my_string.c_split_by_space(substrings);
 * for (int i = 0; i < size; i++)
 * { std::cout << i << *substrings[i] << std::endl; }
 * for (int i = 0; i < size; i++)
 * { delete substrings[i]; }
 * delete [] substrings;
 */
int String::c_split_by_space(String **&substrings) const
{
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

  // Extract substrings and push them dynamically to array
  int size = ptr;
  substrings = new String*[size];
  for (int i = 0; i < size; i++)
  {
    substrings[i] = new String(String::substring(starts[i], ends[i]));
  }

  return size;
}

/**
 * Divides string by given delimeter into an ordered array of substrings.
 * 
 * @param delimeter {char} A characther which will be used to split string by.
 * Delimeter characther won't exist in newyl created substrings.
 * @return {std::vector<String>}
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

  // Extract substrings and push to vector
  int size = ptr;
  for (int i = 0; i < size; i++)
  {
    substrings.push_back(String::substring(starts[i], ends[i]));
  }
  return substrings;
}

/**
 * Divides string by given delimeter into an ordered array of substrings.
 * 
 * @param substrings {JsString**} Will allocate memory for an array of JsString objects.
 * @param delimeter {char} A characther which will be used to split string by.
 * Delimeter characther won't exist in newyl created substrings.
 * @return {int} Number of substrings found. Also size of the allocated substrings array.
 * 
 * Important! Memory should be deallocated by user.
 * 
 * Usage example:
 * String my_string = "I like JsString.";
 * String **substrings = nullptr;
 * int size = my_string.c_split(substrings, 'i');
 * for (int i = 0; i < size; i++)
 * { std::cout << i << *substrings[i] << std::endl; }
 * for (int i = 0; i < size; i++)
 * { delete substrings[i]; }
 * delete [] substrings;
 */
int String::c_split(String **&substrings, char delimeter) const
{
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

  // Extract substrings and push them dynamically to array
  int size = ptr;
  substrings = new String*[size];
  for (int i = 0; i < size; i++)
  {
    substrings[i] = new String(String::substring(starts[i], ends[i]));
  }
  return size;
}

/**
 * Searches for the given search term within the calling JsString and
 * returns the starting index of the first occurance.
 * 
 * @param search_term {JsString} Substring that needs to be found inside the calling string.
 * @param from_index {unsigned int} Optional.
 * An integer representing theindex at which to start the search. Defaults to 0.
 * @return {int} The index of the first occurrence of search term, or -1 if not found.
 */
int String::first_index_of(String search_term, unsigned int from_index) const
{
  for (unsigned int i = from_index; i <= length - search_term.length; i++)
  {
    // If first char matches
    if ((search_term[0] == str[i]))
    {
      // Check for the whole search term with substring method
      if (search_term == this->substring(i, i + search_term.length))
      {
        // Found
        return i;
      }
    }
  }

  // If not returned until here, search term doesn't exist on calling string
  return -1;
}

/**
 * Searches for the given search term within the calling JsString and
 * returns the starting index of the last occurance.
 * 
 * @param search_term {JsString} Substring that needs to be found inside the calling string.
 * @param from_index {unsigned int} Optional.
 * The index of the last character in the string to be considered as the beginning of a match.
 * Defaults to infinity. 0 also casts to infinity.
 * @return {int} The index of the last occurrence of search term, or -1 if not found.
 */
int String::last_index_of(String search_term, unsigned int from_index) const
{
  // Change from_index to length if default value is given.
  if (from_index == 0 || from_index > length - 1)
  {
    from_index = length - 1;
  }

  for (unsigned int i = from_index; search_term.length - 1 <= i; i--)
  {
    // If last char matches
    if ((search_term[search_term.length - 1] == str[i]))
    {
      // Check for the whole search term with substring method
      if (search_term == this->substring(i - search_term.length + 1, i + 1)) // 3,7 6
      {
        // Found
        return i - search_term.length + 1;
      }
    }
  }

  // If not returned until here, search term doesn't exist on calling string
  return -1;
}

/**
 * Checks if given string exists in the calling string.
 * 
 * @param search_term {JsString} A string to be searched for within calling string.
 * @return {int} true or false.
 */
int String::includes(String search_term) const
{
  return String::first_index_of(search_term) >= 0 ? 1 : 0;
}

/**
 * Replaces the first* substring that matches the search_term
 * with the new_value and returns a new JsString.
 * 
 * *Use replace_all for changing all occurances of search_term with the new_Value.
 * 
 * @param search_term {JsString} Substring value that needs to be changed.
 * @param new_value {JsString} A string to replace the substring specified by search_term.
 * @return {JsString} A new string, with first match of a pattern replaced by a new string.
 */
String String::replace(String search_term, String new_value) const
{
  const int index = this->first_index_of(search_term);

  // Search term does not exist in string
  if(index < 0)
  {
    return String();
  }

  // String before the match + replacing value + string after the match
  String before = String::substring(0, index);
  String after = String::substr(index + search_term.length);
  return String(before + new_value + after);
}

/**
 * Replaces all substrings that match the search_term
 * with the new_value and returns a new JsString.
 * 
 * @param search_term {JsString} Substring value that needs to be changed.
 * @param new_value {JsString} A string to replace the substring specified by search_term.
 * @return {JsString} A new string, with all the matches of a pattern replaced by a new string.
 */
String String::replace_all(String search_term, String new_value) const
{
  const int index = this->first_index_of(search_term);
  if(index < 0)
  {
    return String();
  }
  return String(String::substring(0, index) + new_value + String::substr(index + search_term.length));
}