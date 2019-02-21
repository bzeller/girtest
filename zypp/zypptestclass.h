#ifndef ZYPPTESTCLASS_H
#define ZYPPTESTCLASS_H

#include <glib-object.h>

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define ZYPP_TYPE_TESTCLASS zypp_testclass_get_type()
G_DECLARE_FINAL_TYPE( ZyppTestClass, zypp_testclass, ZYPP, TESTCLASS, GObject )

/*
 * Method definitions.
 */


ZyppTestClass *zypp_testclass_new ( void );

char *zypp_testclass_get_first_name ( ZyppTestClass *self );

char *zypp_testclass_get_last_name ( ZyppTestClass *self );

int   zypp_testclass_get_age ( ZyppTestClass *self );


G_END_DECLS


#endif // ZYPPTESTCLASS_H
