#include "Source/Table/tablehandler.h"
#include "Source/Table/symboltable.h"

TableHandler::TableHandler(QObject *parent) : QObject(parent)
{
    m_symbolTable = new SymbolTable ;
}

SymbolTable* TableHandler::symbolTable( void )
{
    return m_symbolTable ;
}
