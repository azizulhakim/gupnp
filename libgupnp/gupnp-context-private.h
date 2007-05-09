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

#ifndef __GUPNP_CONTEXT_PRIVATE_H__
#define __GUPNP_CONTEXT_PRIVATE_H__

#include <libsoup/soup.h>
#include <libsoup/soup-server.h>

G_BEGIN_DECLS

typedef enum {
        _GUPNP_METHOD_SUBSCRIBE,
        _GUPNP_METHOD_UNSUBSCRIBE,
        _GUPNP_METHOD_NOTIFY,
        _GUPNP_METHOD_GET,
        _GUPNP_METHOD_POST
} _GUPnPMethod;

SoupSession *
_gupnp_context_get_session    (GUPnPContext *context);

SoupServer *
_gupnp_context_get_server     (GUPnPContext *context);

const char *
_gupnp_context_get_server_url (GUPnPContext *context);

G_END_DECLS

#endif /* __GUPNP_CONTEXT_PRIVATE_H__ */
