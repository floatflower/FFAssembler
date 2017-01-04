#include "Source/Table/tablehandler.h"
#include "Source/Table/symboltable.h"
#include "Source/Table/registertable.h"

TableHandler::TableHandler(QObject *parent) : QObject(parent)
{
    m_symbolTable = new SymbolTable ;
    m_registerTable = new RegisterTable ;
}

SymbolTable* TableHandler::symbolTable( void )
{
    return m_symbolTable ;
}

RegisterTable* TableHandler::registerTable( void )
{
    return m_registerTable ;
}
