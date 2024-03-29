#include <GL/ostinygl.h>
#include "zbuffer.h"
#include "zgl.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <assert.h>

static int num_contexts = 0;

/* create offscreen tinygl context with provided dimensions and depth */
ostgl_context *ostgl_create_context(int width, int height, int depth)
{
	/* variables */
	ostgl_context *context;

	/* check parameter validitiy */
	assert(width && height);
	assert(depth == 16);

	/* allocate context */
	context = gl_malloc(sizeof(ostgl_context));
	assert(context != NULL);

	/* allocate pixels */
	context->pixels = gl_malloc(width * height * (depth / 8));
	assert(context->pixels != NULL);

	/* open zbuffer */
	context->zb = ZB_open(width, height, ZB_MODE_5R6G5B, 0, NULL, NULL, context->pixels);
	assert(context->zb != NULL);

	/* init gl */
	if (++num_contexts == 1)
		glInit((ZBuffer *)context->zb);

	/* init values */
	context->width = width;
	context->height = height;
	context->depth = depth;

	/* return ptr */
	return context;
}

/* make current */
void ostgl_make_current(ostgl_context *context)
{
	GLContext *glcontext = gl_get_context();
	assert(glcontext != NULL);
	glcontext->zb = (ZBuffer *)context->zb;
}

/* delete zbuffers and free all memory */
void ostgl_delete_context(ostgl_context *context)
{
	ZB_close((ZBuffer *)context->zb);
	gl_free(context->pixels);
	gl_free(context);

	if (--num_contexts == 0)
		glClose();
}

/* resize all zbuffers in context */
void ostgl_resize(ostgl_context *context, int width, int height)
{
	context->width = width;
	context->height = height;
	ZB_resize(context->zb, context->pixels, width, height);
}
