#ifndef XMEGA_H
#define XMEGA_h

#include "Spi.h"
#include <queue>

enum Xmega_Command {
  // TODO list all possible commands
  X_NONE,
  X_PLACEHOLDER,
};

class Xmega {
  public:
    /**
    * Sets up connection to XMEGA
    **/
    Xmega(Spi * s);

    /**
    * Writes a command to the Xmegas
    * Note: The command is not sent immediately
    * @param command the command to be run
    **/
    void write(Xmega_Command command);


    /**
    * Updates SPI and sends a command from the command queue
    * @return the command to be run
    **/ 
    Xmega_Command transfer();


  private:
    #ifdef SIM

    #else

      Spi * spi;
      std::queue<Xmega_Command> q;

    #endif
    
};

#endif

