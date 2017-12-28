//
// Created by chorin on 12/28/17.
//

//#define DEBUG

#ifdef DEBUG
#define LOG(str) do { std::cout << str << std::endl; } while( false )
#else
#define LOG(str) do { } while ( false )
#endif
