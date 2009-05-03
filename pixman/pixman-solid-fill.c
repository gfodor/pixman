/*
 * Copyright © 2000 SuSE, Inc.
 * Copyright © 2007, 2009 Red Hat, Inc.
 * Copyright © 2009 Soren Sandmann
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of SuSE not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  SuSE makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * SuSE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL SuSE
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <config.h>
#include "pixman-private.h"

static source_pict_class_t
solid_fill_classify (pixman_image_t *image,
		     int	     x,
		     int	     y,
		     int	     width,
		     int	     height)
{
    return (image->source.class = SOURCE_IMAGE_CLASS_HORIZONTAL);
}

static uint32_t
color_to_uint32 (const pixman_color_t *color)
{
    return
	(color->alpha >> 8 << 24) |
	(color->red >> 8 << 16) |
        (color->green & 0xff00) |
	(color->blue >> 8);
}

PIXMAN_EXPORT pixman_image_t *
pixman_image_create_solid_fill (pixman_color_t *color)
{
    pixman_image_t *img = _pixman_image_allocate();
    
    if (!img)
	return NULL;

    img->source.class = SOURCE_IMAGE_CLASS_UNKNOWN;
    img->common.classify = solid_fill_classify;
    
    img->type = SOLID;
    img->solid.color = color_to_uint32 (color);

    return img;
}
