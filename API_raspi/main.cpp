
#include "listen.h"
#include <iostream>
using namespace std;

// to set a virtual socket on your pc : modprobe vcan, flexcan, mcp251x, can-raw, can-dev, can
// ip link set vcan0 up type vcan
// cansend vcan0 7DF#0201050000000000, 7df: id variable, le reste = valeur


// http://copperhilltech.com/what-is-socketcan/
int
main(void)
{
  cout << "hello world!" << endl;
  listen((void*)1);
  return 0;
}


