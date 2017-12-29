/**
*  Reversi - Advanced Programming 1
*  Ex: #5
*  Simple logging header used for log
*/

// remove comment to print log messages
//#define DEBUG

#ifdef DEBUG
#define LOG(str) do { std::cout << str << std::endl; } while( false )
#else
#define LOG(str) do { } while ( false )
#endif
