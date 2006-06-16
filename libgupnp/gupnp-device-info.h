/* 
 * Copyright (C) 2006 OpenedHand Ltd.
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

#ifndef __GUPNP_DEVICE_INFO_H__
#define __GUPNP_DEVICE_INFO_H__

#include <glib-object.h>
#include <libxml/tree.h>

G_BEGIN_DECLS

GType
gupnp_device_info_get_type (void) G_GNUC_CONST;

#define GUPNP_TYPE_DEVICE_INFO \
                (gupnp_device_info_get_type ())
#define GUPNP_DEVICE_INFO(obj) \
                (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                 GUPNP_TYPE_DEVICE_INFO, \
                 GUPnPDeviceInfo))
#define GUPNP_IS_DEVICE_INFO(obj) \
                (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                 GUPNP_TYPE_DEVICE_INFO))
#define GUPNP_DEVICE_INFO_GET_IFACE(obj) \
                (G_TYPE_INSTANCE_GET_INTERFACE ((obj), \
                 GUPNP_TYPE_DEVICE_INFO, \
                 GUPnPDeviceInfoIface))

typedef struct _GUPnPDeviceInfo GUPnPDeviceInfo; /* Dummy typedef */

typedef struct {
        GTypeInterface iface;

        /* vtable */
        const char * (* get_location) (GUPnPDeviceInfo *info);
        xmlNode    * (* get_element)  (GUPnPDeviceInfo *info);

        /* future padding */
        void (* _gupnp_reserved1) (void);
        void (* _gupnp_reserved2) (void);
        void (* _gupnp_reserved3) (void);
        void (* _gupnp_reserved4) (void);
} GUPnPDeviceInfoIface;

const char *
gupnp_device_info_get_location          (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_device_type       (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_friendly_name     (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_manufacturer      (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_manufacturer_url  (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_model_description (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_model_name        (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_model_number      (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_model_url         (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_serial_number     (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_udn               (GUPnPDeviceInfo *info);

const char *
gupnp_device_info_get_upc               (GUPnPDeviceInfo *info);

char *
gupnp_device_info_get_icon_url          (GUPnPDeviceInfo *info,
                                         const char      *requested_mime_type,
                                         int              requested_depth,
                                         int              requested_width,
                                         int              requested_height,
                                         gboolean         prefer_bigger,
                                         char           **mime_type,
                                         int             *depth,
                                         int             *width,
                                         int             *height);

G_END_DECLS

#endif /* __GUPNP_DEVICE_INFO_H__ */
