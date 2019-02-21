#include "testclass.h"
#include <iostream>

Testclass::Testclass()
    : Glib::ObjectBase( typeid( Testclass) )
{
    std::cout << "Created stuff" << std::endl;
}

Testclass::~Testclass()
{
    std::cout << "Destroyed stuff" << std::endl;
}
