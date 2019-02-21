#include <iostream>
#include <glibmm/init.h>
#include <glib-object.h>
#include "testclass.h"
#include "zypp/zypptestclass.h"

using namespace std;

int main()
{
    Glib::init();

    Testclass cTest;
    cTest.age().signal_changed().connect( sigc::bind( []( Testclass *c ) {
        std::cout << "Age changed to " << c->age().get_value() << std::endl;
    }, &cTest ));

    cTest.age().set_value( 200 );


    ZyppTestClass *wrapped = zypp_testclass_new();

    g_object_set ( wrapped, "age", 20 , NULL);


    int val = -1;
    g_object_get( wrapped, "age", &val, NULL );

    std::cout << "Read stuff from wrapped " << val << std::endl;


    g_object_unref( wrapped );




    cout << "Hello World!" << endl;
    return 0;
}
