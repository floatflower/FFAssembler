#include <QCoreApplication>

#include "ffassembler.h"

int main ( int argc , char **argv )
{

    FFAssembler assembler;
    assembler.setCommand ( argc , argv ) ;
    assembler.run( ) ;
    return 0 ;
}
