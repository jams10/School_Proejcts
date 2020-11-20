#include <iostream>
#include "graph.h"

enum Menu
{
  SHOW_VERTICES = 1,
  SHOW_BRIDGES,
  SET_CONNECTION,
  BRIDGE_TEST,
  END
};

#define OUT

int CheckInput( int& v1, int& v2, const int& size );

int main()
{
  int n = 0;
  std::cout << "How many vertices you want? : ";
  std::cin >> n;

  Graph g(n);
  //g.ShowVertices();

  int select = 0 ;
  while( true )
  {
    std::cout << std::endl;
    std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
    std::cout << "1. SHOW VERTICES" << std::endl;
    std::cout << "2. SHOW BRIDGES" << std::endl;
    std::cout << "3. SET CONNECTION" << std::endl;
    std::cout << "4. BRIDGE TEST" << std::endl;
    std::cout << "Please select the menu(number) : ";
    std::cin >> select;
    if( SHOW_VERTICES > select || BRIDGE_TEST < select )
    {
      std::cout<<"You typed wrong number" << std::endl;
      continue;
    }
    int v1 = 0, v2 = 0, check = 0;
    int size = g.GetSize() - 1;
    switch(select)
    {
      case SHOW_VERTICES:
        g.ShowVertices();
        std::cout << std::endl;
        break;
      case SHOW_BRIDGES:
        g.ShowConnections();
        break;
      case SET_CONNECTION:
        while(true)
        {
          check = CheckInput(v1, v2, size);
          if( check == -1 ) break;
          if( check == 0 ) continue;
          if( !g.SetConnection(v1, v2) )
          {
            std::cout << "The connection has been already set." << std::endl;
          }
        }
        break;
      case BRIDGE_TEST:
        while(true)
        {
          check = CheckInput(v1, v2, size);
          if(check > 0)
          {
            if( g.CheckConnection(v1, v2) )
            {
              std::cout << "Bridge Confirmed." << std::endl;
            }
            else
            {
              std::cout << "Connection is not set." << std::endl;
            }
            break;
          }
          else
          {
            std::cout << "You typed wrong number" << std::endl;
          }
        }
        break;
      default:
        break;
    }
  }
}

int CheckInput( OUT int& v1, OUT int& v2, const int& size )
{
  int a = 0, b = 0;
  std::cout << "Vertices : 0 ~ " << size << std::endl;
  std::cout << "Please type the index of vertices : ";
  std::cin >> a >> b;
  if(a == -1 && b == -1)
  {
    return -1;
  }
  if(v1 > size || v1 < 0 || v2 > size || v2 < 0)
  {
    std::cout << "You typed wrong index" << std::endl;
    return 0;
  }
  v1 = a;
  v2 = b;
  return 1;
}
