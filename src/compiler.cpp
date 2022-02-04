#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  string beepOutPut = "";
  // print arc and argv
  for (int i = 1; i < argc; i++)
  {
    // try read the file at argv[i]
    string fileName = argv[i];
    // if fileName doesn't end with `.bp`, throw a BeepFileException
    if (fileName.substr(fileName.length() - 3, 3) != ".bp")
    {
      string extension = fileName.substr(fileName.find_last_of(".") + 1);
      cout << "BeepFileException: File format not supported: ." << extension << endl;
      return 1;
    }
    ifstream file(fileName);
    // if fileName is not a file, throw a BeepFileException
    if (!file.is_open())
    {
      cout << "BeepFileException: File not found: " << fileName << endl;
      return 1;
    }
    // init line
    string line;
    int lineCount = 0;
    while (getline(file, line))
    {
      // if the line count is not 0, throw BeepSyntaxException
      if (lineCount >= 1)
      {
        cout << "BeepSyntaxException: Syntax error at line " << lineCount + 1
             << ": " << fileName << endl;
        cout << "Expected '' but found characters.\n"
             << "This may occur if you have more than one trailing newline in a file" << endl;
        return 1;
      }
      // if the line does not read "beep", throw BeepSyntaxException
      if (line != "beep") {
        cout << "BeepSyntaxException: Syntax error at line " << lineCount + 1
             << ": " << fileName << endl;
        cout << "Expected 'beep' but found '" << line << "'" << endl;
        return 1;
      }
      // increment lineCount and append beep
      lineCount++;
      beepOutPut += "beep\n";
    }
    // if lineCount was not incremented, append blank
    if (lineCount == 0)
    {
      beepOutPut += "\n";
    }
  }
  // print beepOutPut
  cout << beepOutPut;
  return 0;
}