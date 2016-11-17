#include <QCoreApplication>

#include "commandhandler.h"

int main(int argc, char **argv )
{

    CommandHandler mainHandler ;
    mainHandler.setCommand ( argc , argv ) ;
    mainHandler.parseCommand ( ) ;

    return 0 ;
}
