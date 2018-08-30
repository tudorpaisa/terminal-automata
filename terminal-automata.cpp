#include <iostream>
#include <vector>
#include <string>
#include <math.h>

//! One Dimensional Array Class
class oneDimArray
{
  public:
    //! Basic Constructor 
    /*  Should be _generally_ avoided
     */
    oneDimArray ();

    //! One Dimensional Array Constructor
    /*	Generates a vector given a size (type int) and sets the
     *	middle cell to 1
     */
    oneDimArray (const int& size);

    //! Calculates the cells at time t+1
    void calculateNext ();

    //! Prints the array
    void printArray () const;

    //! Pretty print of the array
    void printPretty () const;

    char getStartLoc () const { return startLoc; };
  
  protected:
    //! Starting position
    char startLoc;

  private:
    //! One Dimensional (1D) Array
    std::vector <int> array;

    //! Size of the array
    int size;


    //! Vector containing all possible patterns
    std::vector <std::string> pattern;

    //! Vector containing the state of the center cell at t+1
    std::vector <int> state;

};

oneDimArray::oneDimArray ()
{
  std::vector <int> array;
  std::vector <std::string> pattern;
  std::vector <int> state;
}

oneDimArray::oneDimArray (const int& s)
{
  //! "Real" size of the array
  /*! The 1D array has to meet two conditions in this program:
      1. The array size is an odd number (so the middle is an integer)
      2. The edges will always have to be zero, given that this program works with a fixed-size 1D array
  */
  int nsize;

  if (s % 2 == 0) {
    nsize = s + 3; 
  } else {
    nsize = s + 2;
  }

  size = nsize;

  int start;
  std::cout << "Select the starting postion: beginning, middle, end (b/m/e): ";
  std::cin >> startLoc;

  if (startLoc == 'b') {
    // Beginning of the array
    start = 1;
  } else if (startLoc == 'm'){
    // The middle of the array
    start = (nsize / 2);
  } else if (startLoc == 'e') {
    // End of the array
    start = nsize - 1;
  } else {
    std::cout << "Invalid entry! Exiting..." << std::endl;
    exit(0);
  }

  for (int i=0; i<nsize; i++) {
    array.push_back(0);
  }
  array[start] = 1;

  // TODO This can be done so much better...
  pattern.push_back("111");
  pattern.push_back("110");
  pattern.push_back("101");
  pattern.push_back("100");
  pattern.push_back("011");
  pattern.push_back("010");
  pattern.push_back("001");
  pattern.push_back("000");

  for (int i=0; i < pattern.size(); i++) {
    int input;

    std::cout << "What is the rule for " << pattern[i] << "(0/1): ";
    std::cin >> input;
    if (input > 1) {
      std::cout << "Invalid entry! Exiting..." << std::endl;
      exit(0);
    }
    state.push_back(input);
  }

}

void oneDimArray::calculateNext ()
{
  std::vector <int> narray (size, 0);

  for (int i=1; i < array.size()-1; i++) {
    std::string cellL = std::to_string(array[i-1]);
    std::string cellM = std::to_string(array[i]);
    std::string cellH = std::to_string(array[i+1]);

    std::string cell = cellL + cellM + cellH;

    for (int j=0; j < pattern.size(); j++) {
      int pattL = pattern[j][0];
      int pattM = pattern[j][1];
      int pattH = pattern[j][2];

      if (cell == pattern[j]) {
        narray[i] = state[j];
        
        break;
      }

    }
  }

  array = narray;
}

void oneDimArray::printArray () const
{
  for (int i=1; i < array.size()-1; i++) {
    std::cout << array[i];
  }
  std::cout << std::endl;
}

void oneDimArray::printPretty () const
{
  for (int i=1; i< array.size()-1; i++) {
    if (array[i] == 0) {
      std::cout << ' ';
    } else {
      std::cout << '*';
    }
  }
  
  std::cout << std::endl;
}

int main ()
{ 
  std::string istr;
  int size;
  int printSize;

  std::cout << "Input one dimensional array size (type 80 if in doubt): " 
            << std::endl;
  std::getline (std::cin, istr);

  size = std::stoi (istr); 
  
  oneDimArray cells (size);

  if (cells.getStartLoc() == 'm') {
    printSize = size / 2;
  } else {
    printSize = size;
  }

  cells.printPretty();
  
  for (int i=0; i < printSize; i++) {
    cells.calculateNext();
    cells.printPretty();
  }

  return 0;
}

