#ifndef TECTCLASS_H
#define TECTCLASS_H

#include <glibmm/object.h>
#include <glibmm/stringutils.h>
#include <glibmm/propertyproxy.h>
#include <glibmm/property.h>


class Testclass : public Glib::Object
{
public:
    Testclass();
    ~Testclass();
    // provide proxies for the properties.  The proxy allows you to connect to
    // the 'changed' signal, etc.
    Glib::PropertyProxy<Glib::ustring> firstname() { return prop_firstname.get_proxy(); }
    Glib::PropertyProxy<Glib::ustring> lastname() { return prop_lastname.get_proxy(); }
    Glib::PropertyProxy<int> age() { return prop_age.get_proxy(); }

private:
    Glib::Property<Glib::ustring> prop_firstname { *this, "firstname" };
    Glib::Property<Glib::ustring> prop_lastname  { *this, "lastname"};
    Glib::Property<int> prop_age { *this, "age" };
};

#endif // TECTCLASS_H
