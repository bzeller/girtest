#include "zypptestclass.h"

#include <iostream>

#include <glibmm/init.h>

#include "../testclass.h"

struct _ZyppTestClass
{
    GObject parent_instance;
    Testclass *wrappedClass;
    bool ownsPointer;
};
G_DEFINE_TYPE( ZyppTestClass, zypp_testclass, G_TYPE_OBJECT )

enum {
    PROP_WRAPPED = 1,
    PROP_AGE,
    PROP_NAME,
    PROP_FIRSTNAME,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void
zypp_testclass_finalize ( GObject *gobject )
{
    _ZyppTestClass *c = ZYPP_TESTCLASS( gobject );
    if ( c->wrappedClass  && c->ownsPointer )
        delete c->wrappedClass;

    G_OBJECT_CLASS ( zypp_testclass_parent_class )->finalize (gobject);
}

static void
zypp_testclass_constructed ( GObject *gobject )
{
    _ZyppTestClass *c = ZYPP_TESTCLASS( gobject );
    if ( !c->wrappedClass ) {
        c->wrappedClass = new Testclass;
        c->ownsPointer = true;
    }

    G_OBJECT_CLASS ( zypp_testclass_parent_class )->constructed(gobject);
}

static void
zypp_testclass_init ( ZyppTestClass *self )
{
    /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
    self->wrappedClass = nullptr;
    self->ownsPointer = false;
}

static void
zypp_testclass_set_property (GObject      *object,
                             guint         property_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
    ZyppTestClass *self = ZYPP_TESTCLASS( object );

    std::cout << "Setting property " << property_id << " wrapped is: " << self->wrappedClass << std::endl;

    switch (property_id)
    {
        case PROP_WRAPPED:
            if ( self->wrappedClass && self->ownsPointer )
                delete self->wrappedClass;
            self->wrappedClass = reinterpret_cast<Testclass *>( g_value_get_pointer( value ) );
            break;
        case PROP_NAME:
            //if wrapped class is not set we are initializing the object, so we do not set default values here as that is done in the c++ class
            if ( self->wrappedClass ) {
                const gchar *val = g_value_get_string( value );
                self->wrappedClass->lastname().set_value( val == NULL ? Glib::ustring() : Glib::ustring( val ) );
            }
            break;
        case PROP_FIRSTNAME:
            //if wrapped class is not set we are initializing the object, so we do not set default values here as that is done in the c++ class
            if ( self->wrappedClass ) {
                const gchar *val = g_value_get_string( value );
                self->wrappedClass->firstname().set_value( val == NULL ? Glib::ustring() : Glib::ustring( val ) );
            }
            break;
        case PROP_AGE:
            //if wrapped class is not set we are initializing the object, so we do not set default values here as that is done in the c++ class
            if ( self->wrappedClass ) {
                int moop = g_value_get_int( value );
                std::cout << "Got a int with " <<  moop << std::endl;
                self->wrappedClass->age().set_value( moop );
                std::cout << "int is now " << self->wrappedClass->age().get_value() << std::endl;
            }
            break;
        default:
            /* We don't have any other property... */
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
zypp_testclass_get_property (GObject    *object,
                             guint       property_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
    ZyppTestClass *self = ZYPP_TESTCLASS( object );


    std::cout << "Reading property " << property_id << " wrapped is: " << self->wrappedClass << std::endl;

    switch (property_id)
    {
        case PROP_NAME:
            if ( self->wrappedClass ) {
                g_value_set_string( value, self->wrappedClass->lastname().get_value().c_str() );
            }
            break;
        case PROP_FIRSTNAME:
            if ( self->wrappedClass ) {
                g_value_set_string( value, self->wrappedClass->firstname().get_value().c_str() );
            }
            break;
        case PROP_AGE:
            if ( self->wrappedClass ) {
                std::cout << "Returning a int with " << self->wrappedClass->age().get_value() << std::endl;
                g_value_set_int( value, self->wrappedClass->age().get_value() );
            }
            break;
        default:
            /* We don't have any other property... */
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
zypp_testclass_class_init (ZyppTestClassClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = zypp_testclass_finalize;
    object_class->constructed  = zypp_testclass_constructed;

    object_class->set_property = zypp_testclass_set_property;
    object_class->get_property = zypp_testclass_get_property;

    obj_properties[PROP_WRAPPED] =
        g_param_spec_pointer ("wrapped",
                              "Wrapped",
                              "Wrapped C++ object",
                              static_cast<GParamFlags>( G_PARAM_CONSTRUCT_ONLY | G_PARAM_WRITABLE ) );

    obj_properties[PROP_NAME] =
        g_param_spec_string( "name",
                             "LastName",
                             "The last name",
                             NULL,
                             static_cast<GParamFlags>( G_PARAM_READWRITE ) );

    obj_properties[PROP_FIRSTNAME] =
        g_param_spec_string( "firstname",
                            "FirstName",
                            "The first name",
                            NULL,
                            static_cast<GParamFlags>( G_PARAM_READWRITE ) );

    obj_properties[PROP_AGE] =
        g_param_spec_int    ("age",
                             "Age",
                             "The age",
                             0,
                             G_MAXINT,
                             0,
                             static_cast<GParamFlags>( G_PARAM_READWRITE ) );

    g_object_class_install_properties (object_class,
                                      N_PROPERTIES,
                                      obj_properties);
}

/**
 * zypp_testclass_new:
 *
 * Instantiates a new #ZyppTestClass singleton.
 *
 * Return value: a new #ZyppTestClass
 **/
ZyppTestClass *zypp_testclass_new ( void )
{
    ZyppTestClass *retval = ZYPP_TESTCLASS( (g_object_new (ZYPP_TYPE_TESTCLASS, NULL)) );
    return retval;
}

ZyppTestClass *zypp_testclass_wrap ( Testclass *toWrap )
{
    ZyppTestClass *retval = ZYPP_TESTCLASS( (g_object_new (ZYPP_TYPE_TESTCLASS, "wrapped", toWrap, NULL)) );
    return retval;
}

char *zypp_testclass_get_first_name ( ZyppTestClass *self )
{
    return g_strdup( ZYPP_TESTCLASS( self )->wrappedClass->firstname().get_value().c_str() );
}

char *zypp_testclass_get_last_name ( ZyppTestClass *self )
{
    return g_strdup( ZYPP_TESTCLASS( self )->wrappedClass->lastname().get_value().c_str() );
}

int zypp_testclass_get_age ( ZyppTestClass *self )
{
    return ZYPP_TESTCLASS( self )->wrappedClass->age().get_value();
}
