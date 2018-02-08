


#ifndef GUPNP_ENUMS_H
#define GUPNP_ENUMS_H

#include <glib-object.h>

G_BEGIN_DECLS

/* enumerations from ./gupnp-error.h */
GType gupnp_server_error_get_type (void);
#define GUPNP_TYPE_SERVER_ERROR (gupnp_server_error_get_type())
GType gupnp_eventing_error_get_type (void);
#define GUPNP_TYPE_EVENTING_ERROR (gupnp_eventing_error_get_type())
GType gupnp_control_error_get_type (void);
#define GUPNP_TYPE_CONTROL_ERROR (gupnp_control_error_get_type())
GType gupnp_xml_error_get_type (void);
#define GUPNP_TYPE_XML_ERROR (gupnp_xml_error_get_type())
GType gupnp_rootdevice_error_get_type (void);
#define GUPNP_TYPE_ROOTDEVICE_ERROR (gupnp_rootdevice_error_get_type())
/* enumerations from ./gupnp-service-introspection.h */
GType gupnp_service_action_arg_direction_get_type (void);
#define GUPNP_TYPE_SERVICE_ACTION_ARG_DIRECTION (gupnp_service_action_arg_direction_get_type())
G_END_DECLS

#endif /* GUPNP_ENUMS_H */



