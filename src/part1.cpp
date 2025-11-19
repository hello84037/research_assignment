#include <iostream>
#include <fstream>
#include "alg_graphs.h"
#include "alg_strings.h"

using namespace std;

int main()
{
  std::string pattern = "ABABAC";
  std::string text = "ABABABACABA";

  RabinKarp rk(pattern);
  int pos = rk.search(text);
  if (pos != text.length())
  {
    cout << "Rabin-Karp: Pattern found at index: " << pos << endl;
  }
  else
  {
    cout << "Rabin-Karp: Pattern not found." << endl;
  }

  KMP kmp(pattern);
  int index = kmp.search(text);
  if (index != text.length())
  {
    cout << "Pattern found at index: " << index << endl;
  }
  else
  {
    cout << "Pattern not found." << endl;
  }
  return 0;
}
