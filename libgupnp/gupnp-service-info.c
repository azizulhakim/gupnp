/* 
 * Copyright (C) 2006, 2007 OpenedHand Ltd.
 *
 * Author: Jorn Baayen <jorn@openedhand.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:gupnp-service-info
 * @short_description: Base abstract class for querying service information.
 *
 * The #GUPnPDeviceInfo base abstract class provides methods for querying
 * service information.
 */

#include <libsoup/soup.h>
#include <string.h>

#include "gupnp-service-info.h"
#include "gupnp-service-introspection-private.h"
#include "gupnp-context-private.h"
#include "gupnp-error.h"
#include "gupnp-error-private.h"
#include "xml-util.h"

G_DEFINE_ABSTRACT_TYPE (GUPnPServiceInfo,
                        gupnp_service_info,
                        G_TYPE_OBJECT);

struct _GUPnPServiceInfoPrivate {
        GUPnPContext *context;

        char *location;
        char *udn;

        SoupUri *url_base;

        xmlNode *element;

        /* For async downloads */
        GList *pending_gets;
};

enum {
        PROP_0,
        PROP_CONTEXT,
        PROP_LOCATION,
        PROP_UDN,
        PROP_URL_BASE,
        PROP_ELEMENT
};

typedef struct {
        GUPnPServiceInfo                 *info;
        
        GUPnPServiceIntrospectionCallback callback;
        gpointer                          user_data;

        SoupMessage                      *message;
} GetSCPDURLData;

static void
get_scpd_url_data_free (GetSCPDURLData *data)
{
        data->info->priv->pending_gets =
                g_list_remove (data->info->priv->pending_gets, data);

        g_slice_free (GetSCPDURLData, data);
}

static void
gupnp_service_info_init (GUPnPServiceInfo *info)
{
        info->priv = G_TYPE_INSTANCE_GET_PRIVATE (info,
                                                  GUPNP_TYPE_SERVICE_INFO,
                                                  GUPnPServiceInfoPrivate);
}

static void
gupnp_service_info_set_property (GObject      *object,
                                 guint         property_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
        GUPnPServiceInfo *info;

        info = GUPNP_SERVICE_INFO (object);

        switch (property_id) {
        case PROP_CONTEXT:
                info->priv->context =
                        g_object_ref (g_value_get_object (value));
                break;
        case PROP_LOCATION:
                info->priv->location =
                        g_value_dup_string (value);
                break;
        case PROP_UDN:
                info->priv->udn =
                        g_value_dup_string (value);
                break;
        case PROP_URL_BASE:
                info->priv->url_base =
                        g_value_get_pointer (value);

                if (info->priv->url_base)
                        info->priv->url_base =
                                soup_uri_copy (info->priv->url_base);

                break;
        case PROP_ELEMENT:
                info->priv->element =
                        g_value_get_pointer (value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

static void
gupnp_service_info_get_property (GObject    *object,
                                 guint       property_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
        GUPnPServiceInfo *info;

        info = GUPNP_SERVICE_INFO (object);

        switch (property_id) {
        case PROP_CONTEXT:
                g_value_set_object (value,
                                    info->priv->context);
                break;
        case PROP_LOCATION:
                g_value_set_string (value,
                                    info->priv->location);
                break;
        case PROP_UDN:
                g_value_set_string (value,
                                    info->priv->udn);
                break;
        case PROP_URL_BASE:
                g_value_set_pointer (value,
                                     info->priv->url_base);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

static void
gupnp_service_info_dispose (GObject *object)
{
        GUPnPServiceInfo *info;

        info = GUPNP_SERVICE_INFO (object);

        /* Cancel any pending SCPD GETs */
        if (info->priv->context) {
                SoupSession *session;

                session = _gupnp_context_get_session (info->priv->context);

                while (info->priv->pending_gets) {
                        GetSCPDURLData *data;

                        data = info->priv->pending_gets->data;

                        soup_message_set_status (data->message,
                                                 SOUP_STATUS_CANCELLED);
                        soup_session_cancel_message (session, data->message);

                        get_scpd_url_data_free (data);
                }
        
                /* Unref context */
                g_object_unref (info->priv->context);
                info->priv->context = NULL;
        }
}

static void
gupnp_service_info_finalize (GObject *object)
{
        GUPnPServiceInfo *info;

        info = GUPNP_SERVICE_INFO (object);

        g_free (info->priv->location);
        g_free (info->priv->udn);

        soup_uri_free (info->priv->url_base);
}

static void
gupnp_service_info_class_init (GUPnPServiceInfoClass *klass)
{
        GObjectClass *object_class;

        object_class = G_OBJECT_CLASS (klass);

        object_class->set_property = gupnp_service_info_set_property;
        object_class->get_property = gupnp_service_info_get_property;
        object_class->dispose      = gupnp_service_info_dispose;
        object_class->finalize     = gupnp_service_info_finalize;

        g_type_class_add_private (klass, sizeof (GUPnPServiceInfoPrivate));

        /**
         * GUPnPServiceInfo:context
         *
         * The #GUPnPContext to use.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_CONTEXT,
                 g_param_spec_object ("context",
                                      "Context",
                                      "The GUPnPContext.",
                                      GUPNP_TYPE_CONTEXT,
                                      G_PARAM_READWRITE |
                                      G_PARAM_CONSTRUCT_ONLY |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPServiceInfo:location
         *
         * The location of the device description file.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_LOCATION,
                 g_param_spec_string ("location",
                                      "Location",
                                      "The location of the device description "
                                      "file",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_CONSTRUCT_ONLY |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPServiceInfo:udn
         *
         * The UDN of the containing device.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_UDN,
                 g_param_spec_string ("udn",
                                      "UDN",
                                      "The UDN of the containing device",
                                      NULL,
                                      G_PARAM_READWRITE |
                                      G_PARAM_CONSTRUCT_ONLY |
                                      G_PARAM_STATIC_NAME |
                                      G_PARAM_STATIC_NICK |
                                      G_PARAM_STATIC_BLURB));

        /**
         * GUPnPServiceInfo:url-base
         *
         * The URL base (#SoupUri).
         **/
        g_object_class_install_property
                (object_class,
                 PROP_URL_BASE,
                 g_param_spec_pointer ("url-base",
                                       "URL base",
                                       "The URL base",
                                       G_PARAM_READWRITE |
                                       G_PARAM_CONSTRUCT_ONLY |
                                       G_PARAM_STATIC_NAME |
                                       G_PARAM_STATIC_NICK |
                                       G_PARAM_STATIC_BLURB));

        /**
         * GUPnPServiceInfo:element
         *
         * Private property.
         *
         * Stability: Private
         **/
        g_object_class_install_property
                (object_class,
                 PROP_ELEMENT,
                 g_param_spec_pointer ("element",
                                       "Element",
                                       "The XML element related to this "
                                       "device",
                                       G_PARAM_WRITABLE |
                                       G_PARAM_CONSTRUCT_ONLY |
                                       G_PARAM_STATIC_NAME |
                                       G_PARAM_STATIC_NICK |
                                       G_PARAM_STATIC_BLURB));
}

/**
 * gupnp_service_info_get_context
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The #GUPnPContext associated with @info.
 **/
GUPnPContext *
gupnp_service_info_get_context (GUPnPServiceInfo *info)
{
        g_return_val_if_fail (GUPNP_IS_SERVICE_INFO (info), NULL);

        return info->priv->context;
}

/**
 * gupnp_service_info_get_location
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The location of the device description file.
 **/
const char *
gupnp_service_info_get_location (GUPnPServiceInfo *info)
{
        g_return_val_if_fail (GUPNP_IS_SERVICE_INFO (info), NULL);

        return info->priv->location;
}

/**
 * gupnp_service_info_get_url_base
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The URL base.
 **/
SoupUri *
gupnp_service_info_get_url_base (GUPnPServiceInfo *info)
{
        g_return_val_if_fail (GUPNP_IS_SERVICE_INFO (info), NULL);

        return info->priv->url_base;
}

/**
 * gupnp_service_info_get_udn
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The UDN of the containing device.
 **/
const char *
gupnp_service_info_get_udn (GUPnPServiceInfo *info)
{
        g_return_val_if_fail (GUPNP_IS_SERVICE_INFO (info), NULL);

        return info->priv->udn;
}

/**
 * gupnp_service_info_get_service_type
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The UPnP service type, or NULL. g_free() after use.
 **/
char *
gupnp_service_info_get_service_type (GUPnPServiceInfo *info)
{
        return xml_util_get_child_element_content_glib (info->priv->element,
                                                        "serviceType");
}

/**
 * gupnp_service_info_get_id
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The ID, or NULL. g_free() after use.
 **/
char *
gupnp_service_info_get_id (GUPnPServiceInfo *info)
{
        return xml_util_get_child_element_content_glib (info->priv->element,
                                                        "serviceId");
}

/**
 * gupnp_service_info_get_scpd_url
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The SCPD URL, or NULL. g_free() after use.
 **/
char *
gupnp_service_info_get_scpd_url (GUPnPServiceInfo *info)
{
        return xml_util_get_child_element_content_url (info->priv->element,
                                                       "SCPDURL",
                                                       info->priv->url_base);
}

/**
 * gupnp_service_info_get_control_url
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The control URL, or NULL. g_free() after use.
 **/
char *
gupnp_service_info_get_control_url (GUPnPServiceInfo *info)
{
        return xml_util_get_child_element_content_url (info->priv->element,
                                                       "controlURL",
                                                       info->priv->url_base);
}

/**
 * gupnp_service_info_get_event_subscription_url
 * @info: A #GUPnPServiceInfo
 *
 * Return value: The event subscription URL, or NULL. g_free() after use.
 **/
char *
gupnp_service_info_get_event_subscription_url (GUPnPServiceInfo *info)
{
        return xml_util_get_child_element_content_url (info->priv->element,
                                                       "eventSubURL",
                                                       info->priv->url_base);
}

/**
 * gupnp_service_info_get_introspection
 * @info: A #GUPnPServiceInfo
 * @error: return location for a GError, or NULL
 *
 * Note that introspection object is created from the information in service
 * description document (SCPD) provided by the service so it can not be created
 * if the service does not provide an SCPD.
 *
 * Return value: A new #GUPnPServiceIntrospection for this service or NULL.
 * Unref after use.
 **/
GUPnPServiceIntrospection *
gupnp_service_info_get_introspection (GUPnPServiceInfo *info,
                                      GError          **error)
{
        SoupSession *session;
        SoupMessage *msg;
        int status;
        char *scpd_url;
        xmlDoc *scpd;

        g_return_val_if_fail (GUPNP_IS_SERVICE_INFO (info), NULL);

        session = _gupnp_context_get_session (info->priv->context);

        scpd_url = gupnp_service_info_get_scpd_url (info);
        if (scpd_url == NULL) {
                g_set_error (error,
                             GUPNP_SERVER_ERROR,
                             GUPNP_SERVER_ERROR_NOT_IMPLEMENTED,
                             "Service does not provide an SCPD");
                             
                return NULL;
        }

        msg = soup_message_new (SOUP_METHOD_GET, scpd_url);

        g_free (scpd_url);

        g_assert (msg != NULL);

        status = soup_session_send_message (session, msg);
        if (!SOUP_STATUS_IS_SUCCESSFUL (status)) {
                set_server_error (error, msg);

                g_object_unref (msg);

                return NULL;
        }

        scpd = xmlParseMemory (msg->response.body, msg->response.length);

        g_object_unref (msg);

        if (!scpd) {
                g_set_error (error,
                             GUPNP_SERVER_ERROR,
                             GUPNP_SERVER_ERROR_INVALID_RESPONSE,
                             "Could not parse SCPD");

                return NULL;
        }

        return gupnp_service_introspection_new (scpd);
}

/**
 * SCPD document loaded.
 **/
static void
scpd_loaded (GetSCPDURLData *data,
             xmlDoc         *scpd)
{
        GUPnPServiceIntrospection *introspection;

        introspection = gupnp_service_introspection_new (scpd);
        if (introspection) {
                data->callback (data->info,
                                introspection,
                                data->user_data,
                                NULL);
        }
}

/**
 * SCPD URL downloaded.
 **/
static void
got_scpd_url (SoupMessage    *msg,
              GetSCPDURLData *data)
{
        GError *error = NULL;

        if (SOUP_STATUS_IS_SUCCESSFUL (msg->status_code)) {
                xmlDoc *scpd;

                scpd = xmlParseMemory (msg->response.body,
                                       msg->response.length);
                if (scpd)
                        scpd_loaded (data, scpd);
                else {
                        error = g_error_new
                                        (GUPNP_SERVER_ERROR,
                                         GUPNP_SERVER_ERROR_INVALID_RESPONSE,
                                         "Could not parse SCPD");
                }
        } else
                error = new_server_error (msg);

        if (error) {
                data->callback (data->info,
                                NULL,
                                data->user_data,
                                error);

                g_error_free (error);
        }

        get_scpd_url_data_free (data);
}

/**
 * gupnp_service_info_get_introspection_async
 * @info: A #GUPnPServiceInfo
 * @callback: callback to be called when introspection object is ready.
 * @user_data: user_data to be passed to the callback.
 *
 * Note that introspection object is created from the information in service
 * description document (SCPD) provided by the service so it can not be created
 * if the service does not provide an SCPD.
 **/
void
gupnp_service_info_get_introspection_async
                                (GUPnPServiceInfo                 *info,
                                 GUPnPServiceIntrospectionCallback callback,
                                 gpointer                          user_data)
{
        GetSCPDURLData *data;
        char *scpd_url;
        SoupSession *session;

        g_return_if_fail (GUPNP_IS_SERVICE_INFO (info));
        g_return_if_fail (callback != NULL);

        scpd_url = gupnp_service_info_get_scpd_url (info);
        if (scpd_url == NULL) {
                GError *error;

                error = g_error_new (GUPNP_SERVER_ERROR,
                                     GUPNP_SERVER_ERROR_NOT_IMPLEMENTED,
                                     "Service does not provide an SCPD");

                callback (info, NULL, user_data, error);

                g_error_free (error);

                return;
        }

        session = _gupnp_context_get_session (info->priv->context);

        /* Greate GetSCPDURLData structure */
        data = g_slice_new (GetSCPDURLData);

        /* Create message */
        data->message = soup_message_new (SOUP_METHOD_GET, scpd_url);

        g_free (scpd_url);

        g_assert (data->message != NULL);

        data->info      = info;
        data->callback  = callback;
        data->user_data = user_data;

        /* Send off the message */
        soup_session_queue_message (session,
                                    data->message,
                                    (SoupMessageCallbackFn) got_scpd_url,
                                    data);

        info->priv->pending_gets =
                g_list_prepend (info->priv->pending_gets,
                                data);
}
