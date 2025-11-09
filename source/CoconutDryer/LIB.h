// Splits a given string using a specified character or symbol and returns the substring at the specified index
String split(String val, char separator, int index) {
  int found = 0;                  // Counter for how many times the separator has been found
  int strIndex[] = { 0, -1 };     // Array to store start and end indices of the substring
  int maxIndex = val.length() - 1; // Maximum index of the input string

  // Iterate through the string to find occurrences of the separator
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (val.charAt(i) == separator || i == maxIndex) { // Check for the separator or end of string
      found++; // Increment the found count for each separator encountered
      strIndex[0] = strIndex[1] + 1; // Update the start index for the next substring
      strIndex[1] = (i == maxIndex) ? i + 1 : i; // Set the end index for the current substring
    }
  }

  // Return the substring if the specified index was found, otherwise return an empty string
  return found > index ? val.substring(strIndex[0], strIndex[1]) : "";
}
