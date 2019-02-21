#!/usr/bin/env python3

import gi
gi.require_version("Zypp", "0.1")
from gi.repository import GLib
from gi.repository import Zypp

def callback ( self , propertyName ):
    print ("Callback called, age changed to:")
    print ( self.get_age() )

Zypp.init()

zypp = Zypp.TestClass.new()
zypp.connect( "notify::age", callback )
zypp.set_property( "age", 22 )
print(zypp.get_property( "age" ))

help (Zypp.init)

