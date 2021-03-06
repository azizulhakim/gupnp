LTVERSION = 0:0:0

if OS_WIN32
CONTEXT_MANAGER_IMPL = gupnp-windows-context-manager.c \
		       gupnp-windows-context-manager.h
CONTEXT_MANAGER_CFLAGS =
CONTEXT_MANAGER_LIBS = -lws2_32 -liphlpapi
WIN32_LDFLAGS = -no-undefined
else
if HAVE_IFADDRS_H
CONTEXT_MANAGER_IMPL = gupnp-unix-context-manager.c \
					   gupnp-unix-context-manager.h
else
CONTEXT_MANAGER_IMPL =
endif
if USE_NETWORK_MANAGER
CONTEXT_MANAGER_IMPL += gupnp-network-manager.c  \
		        gupnp-network-manager.h
CONTEXT_MANAGER_CFLAGS = -DUSE_NETWORK_MANAGER
else
if USE_CONNMAN
CONTEXT_MANAGER_IMPL += gupnp-connman-manager.c  \
			gupnp-connman-manager.h
CONTEXT_MANAGER_CFLAGS = -DUSE_CONNMAN
endif
endif
endif

if HAVE_NETLINK
CONTEXT_MANAGER_IMPL += \
	gupnp-linux-context-manager.c \
	gupnp-linux-context-manager.h
endif

if USE_NETLINK
NETLINK_CFLAGS = -DUSE_NETLINK
else
NETLINK_CFLAGS =
endif

AM_CFLAGS = $(LIBGUPNP_CFLAGS) \
	    $(DBUS_GLIB_CFLAGS) \
	    $(NETLINK_CFLAGS) \
		$(GUUL_CFLAGS) \
	    -I$(top_srcdir) \
	    $(CONTEXT_MANAGER_CFLAGS) \
        $(WARN_CFLAGS)

libgupnpincdir = $(includedir)/gupnp-1.2/libgupnp

lib_LTLIBRARIES = libgupnp-1.2.la

libgupnpinc_HEADERS = gupnp-acl.h			\
		      gupnp-context.h			\
		      gupnp-context-manager.h		\
		      gupnp-control-point.h		\
		      gupnp-device.h			\
		      gupnp-device-info.h		\
		      gupnp-device-proxy.h		\
		      gupnp-error.h			\
		      gupnp-resource-factory.h		\
		      gupnp-root-device.h		\
		      gupnp-service.h			\
		      gupnp-service-info.h		\
		      gupnp-service-proxy.h		\
		      gupnp-service-introspection.h	\
		      gupnp-xml-doc.h	                \
		      gupnp-white-list.h                \
		      gupnp-types.h			\
		      gupnp-uuid.h			\
		      gupnp.h

introspection_sources = $(libgupnpinc_HEADERS) \
			gupnp-acl.c			\
			gupnp-context.c			\
			gupnp-context-manager.c		\
			gupnp-control-point.c		\
			gupnp-device.c			\
			gupnp-device-info.c		\
			gupnp-device-proxy.c		\
			gupnp-error.c			\
			gupnp-resource-factory.c	\
			gupnp-root-device.c		\
			gupnp-service.c			\
			gupnp-service-info.c		\
			gupnp-service-proxy.c		\
			gupnp-service-introspection.c	\
			gupnp-xml-doc.c			\
			gupnp-white-list.c		\
			gupnp-types.c

libgupnp_1_2_la_LDFLAGS = -version-info $(LTVERSION) $(WIN32_LDFLAGS) $(WARN_LDFLAGS)

libgupnp_1_2_la_SOURCES = $(introspection_sources)		\
			  http-headers.c			\
			  http-headers.h			\
			  gupnp-context-private.h		\
			  $(CONTEXT_MANAGER_IMPL) 		\
			  gupnp-simple-context-manager.h	\
			  gupnp-simple-context-manager.c	\
			  gupnp-device-info-private.h		\
			  gupnp-error-private.h			\
			  gupnp-resource-factory-private.h	\
			  gupnp-service-introspection-private.h	\
                          gupnp-acl-private.h                   \
			  gupnp-types-private.h			\
			  gvalue-util.c				\
			  gvalue-util.h				\
			  xml-util.c				\
			  xml-util.h				\
			  gena-protocol.h			\
			  guul.c \
			  guul.h \
			  $(BUILT_SOURCES)

libgupnp_1_2_la_LIBADD = $(LIBGUPNP_LIBS) $(DBUS_GLIB_LIBS) $(CONTEXT_MANAGER_LIBS) $(GUUL_LIBS)

EXTRA_DIST = gupnp-marshal.list 	   \
	     gupnp-network-manager.c   	   \
	     gupnp-network-manager.h       \
	     gupnp-connman-manager.c   	   \
	     gupnp-connman-manager.h       \
	     gupnp-linux-context-manager.c \
	     gupnp-linux-context-manager.h \
	     gupnp-unix-context-manager.c  \
	     gupnp-unix-context-manager.h  \
	     gupnp-windows-context-manager.c \
	     gupnp-windows-context-manager.h

enumheaders = \
	$(srcdir)/gupnp-error.h \
	$(srcdir)/gupnp-service-introspection.h

BUILT_SOURCES = \
	gupnp-enums.c \
	gupnp-enums.h

gupnp-enums.c: $(enumheaders) Makefile
	$(AM_V_GEN)$(GLIB_MKENUMS) \
		--identifier-prefix GUPnP \
		--symbol-prefix gupnp \
		--fhead "#include \"gupnp-enums.h\"\n\n" \
		--fprod "/* enumerations from \"@filename@\" */\n" \
		--fprod "#include \"@filename@\"\n" \
		--vhead "GType\n@enum_name@_get_type (void)\n{\n" \
		--vhead "    static GType type = 0;\n\n" \
		--vhead "    if (!type)\n    {\n" \
		--vhead "        static const G@Type@Value _@enum_name@_values[] = {" \
		--vprod "            { @VALUENAME@, \"@VALUENAME@\", \"@valuenick@\" }," \
		--vtail "            { 0, NULL, NULL }\n        };\n\n" \
		--vtail "        type = g_@type@_register_static (\"@EnumName@\", _@enum_name@_values);\n    }\n\n" \
		--vtail "  return type;\n}\n\n" \
		$(enumheaders) > $@

gupnp-enums.h: $(enumheaders) Makefile
	$(AM_V_GEN)$(GLIB_MKENUMS) \
		--identifier-prefix GUPnP \
		--symbol-prefix gupnp \
		--fhead "#ifndef GUPNP_ENUMS_H\n" \
		--fhead "#define GUPNP_ENUMS_H\n\n" \
		--fhead "#include <glib-object.h>\n\n" \
		--fhead "G_BEGIN_DECLS\n\n" \
		--fprod "/* enumerations from @filename@ */\n" \
		--vhead "GType @enum_name@_get_type (void);\n" \
		--vhead "#define GUPNP_TYPE_@ENUMSHORT@ (@enum_name@_get_type())\n" \
		--ftail "G_END_DECLS\n\n" \
		--ftail "#endif /* GUPNP_ENUMS_H */" \
		$(enumheaders) > $@


-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = \
			     --symbol-prefix=gupnp	\
			     --identifier-prefix=GUPnP	\
			     --add-include-path=$(top_srcdir) \
			     --pkg-export=gupnp-1.2 \
                 $(WARN_SCANNERFLAGS)
INTROSPECTION_COMPILER_ARGS = --includedir=$(top_srcdir)

if HAVE_INTROSPECTION
GUPnP-1.2.gir: libgupnp-1.2.la
GUPnP_1_2_gir_INCLUDES = libxml2-2.0 GObject-2.0 Soup-2.4 GSSDP-1.0
GUPnP_1_2_gir_CFLAGS = -DGOBJECT_INTROSPECTION_SKIP $(INCLUDES) $(AM_CFLAGS)
GUPnP_1_2_gir_LIBS = libgupnp-1.2.la
GUPnP_1_2_gir_FILES = $(introspection_sources)
GUPnP_1_2_gir_NAMESPACE = GUPnP
GUPnP_1_2_gir_VERSION = 1.2

INTROSPECTION_GIRS += GUPnP-1.2.gir

girdir = $(datadir)/gir-1.0
gir_DATA = GUPnP-1.2.gir

typelibdir = $(libdir)/girepository-1.0/
typelib_DATA = $(gir_DATA:.gir=.typelib)
endif

CLEANFILES = $(BUILT_SOURCES) $(gir_DATA) $(typelib_DATA)
DISTCLEANFILES = $(BUILT_SOURCES)
MAINTAINERCLEANFILES = Makefile.in $(BUILT_SOURCES)
