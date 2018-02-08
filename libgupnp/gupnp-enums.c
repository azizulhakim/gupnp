


#include "gupnp-enums.h"

/* enumerations from "./gupnp-error.h" */
#include "./gupnp-error.h"
GType
gupnp_server_error_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_server_error_values[] = {
            { GUPNP_SERVER_ERROR_INTERNAL_SERVER_ERROR, "GUPNP_SERVER_ERROR_INTERNAL_SERVER_ERROR", "internal-server-error" },
            { GUPNP_SERVER_ERROR_NOT_FOUND, "GUPNP_SERVER_ERROR_NOT_FOUND", "not-found" },
            { GUPNP_SERVER_ERROR_NOT_IMPLEMENTED, "GUPNP_SERVER_ERROR_NOT_IMPLEMENTED", "not-implemented" },
            { GUPNP_SERVER_ERROR_INVALID_RESPONSE, "GUPNP_SERVER_ERROR_INVALID_RESPONSE", "invalid-response" },
            { GUPNP_SERVER_ERROR_INVALID_URL, "GUPNP_SERVER_ERROR_INVALID_URL", "invalid-url" },
            { GUPNP_SERVER_ERROR_OTHER, "GUPNP_SERVER_ERROR_OTHER", "other" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPServerError", _gupnp_server_error_values);
    }

  return type;
}

GType
gupnp_eventing_error_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_eventing_error_values[] = {
            { GUPNP_EVENTING_ERROR_SUBSCRIPTION_FAILED, "GUPNP_EVENTING_ERROR_SUBSCRIPTION_FAILED", "subscription-failed" },
            { GUPNP_EVENTING_ERROR_SUBSCRIPTION_LOST, "GUPNP_EVENTING_ERROR_SUBSCRIPTION_LOST", "subscription-lost" },
            { GUPNP_EVENTING_ERROR_NOTIFY_FAILED, "GUPNP_EVENTING_ERROR_NOTIFY_FAILED", "notify-failed" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPEventingError", _gupnp_eventing_error_values);
    }

  return type;
}

GType
gupnp_control_error_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_control_error_values[] = {
            { GUPNP_CONTROL_ERROR_INVALID_ACTION, "GUPNP_CONTROL_ERROR_INVALID_ACTION", "invalid-action" },
            { GUPNP_CONTROL_ERROR_INVALID_ARGS, "GUPNP_CONTROL_ERROR_INVALID_ARGS", "invalid-args" },
            { GUPNP_CONTROL_ERROR_OUT_OF_SYNC, "GUPNP_CONTROL_ERROR_OUT_OF_SYNC", "out-of-sync" },
            { GUPNP_CONTROL_ERROR_ACTION_FAILED, "GUPNP_CONTROL_ERROR_ACTION_FAILED", "action-failed" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPControlError", _gupnp_control_error_values);
    }

  return type;
}

GType
gupnp_xml_error_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_xml_error_values[] = {
            { GUPNP_XML_ERROR_PARSE, "GUPNP_XML_ERROR_PARSE", "parse" },
            { GUPNP_XML_ERROR_NO_NODE, "GUPNP_XML_ERROR_NO_NODE", "no-node" },
            { GUPNP_XML_ERROR_EMPTY_NODE, "GUPNP_XML_ERROR_EMPTY_NODE", "empty-node" },
            { GUPNP_XML_ERROR_INVALID_ATTRIBUTE, "GUPNP_XML_ERROR_INVALID_ATTRIBUTE", "invalid-attribute" },
            { GUPNP_XML_ERROR_OTHER, "GUPNP_XML_ERROR_OTHER", "other" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPXMLError", _gupnp_xml_error_values);
    }

  return type;
}

GType
gupnp_rootdevice_error_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_rootdevice_error_values[] = {
            { GUPNP_ROOT_DEVICE_ERROR_NO_CONTEXT, "GUPNP_ROOT_DEVICE_ERROR_NO_CONTEXT", "no-context" },
            { GUPNP_ROOT_DEVICE_ERROR_NO_DESCRIPTION_PATH, "GUPNP_ROOT_DEVICE_ERROR_NO_DESCRIPTION_PATH", "no-description-path" },
            { GUPNP_ROOT_DEVICE_ERROR_NO_DESCRIPTION_FOLDER, "GUPNP_ROOT_DEVICE_ERROR_NO_DESCRIPTION_FOLDER", "no-description-folder" },
            { GUPNP_ROOT_DEVICE_ERROR_NO_NETWORK, "GUPNP_ROOT_DEVICE_ERROR_NO_NETWORK", "no-network" },
            { GUPNP_ROOT_DEVICE_ERROR_FAIL, "GUPNP_ROOT_DEVICE_ERROR_FAIL", "fail" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPRootdeviceError", _gupnp_rootdevice_error_values);
    }

  return type;
}

/* enumerations from "./gupnp-service-introspection.h" */
#include "./gupnp-service-introspection.h"
GType
gupnp_service_action_arg_direction_get_type (void)
{
    static GType type = 0;

    if (!type)
    {
        static const GEnumValue _gupnp_service_action_arg_direction_values[] = {
            { GUPNP_SERVICE_ACTION_ARG_DIRECTION_IN, "GUPNP_SERVICE_ACTION_ARG_DIRECTION_IN", "in" },
            { GUPNP_SERVICE_ACTION_ARG_DIRECTION_OUT, "GUPNP_SERVICE_ACTION_ARG_DIRECTION_OUT", "out" },
            { 0, NULL, NULL }
        };

        type = g_enum_register_static ("GUPnPServiceActionArgDirection", _gupnp_service_action_arg_direction_values);
    }

  return type;
}




