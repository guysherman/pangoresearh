#include <iostream>

#include <stdio.h>
#include <pango/pangocairo.h>
#include <pango/pangoft2.h>
#include <fontconfig/fontconfig.h>
#include <freetype2/ftbitmap.h>

void rendertext(cairo_t *cr);

int main(int argc, char** argv)
{
	cairo_t *cr;
	cairo_status_t status;
	cairo_surface_t *surface;
	//FT_Bitmap bmp = {0};

	int stride = 0;
	int width = 640;
	int height = 480;



	bool ok = FcConfigAppFontAddFile(NULL, (FcChar8*)"fonts/ComicSansAfrica.ttf");
	if (!ok)
	{
		printf("Failed to load ComicSansAfrica.ttf\n");
	}

	FcChar8 *configName = FcConfigFilename(NULL);
	printf("%s", (const char*)configName);
	printf("\n");

	FcConfig* config = FcConfigCreate();
	FcConfigParseAndLoad(config, configName, true);
	FcConfigSetCurrent(config);

	/* FT buffer */
	//FT_Bitmap_New(&bmp);
	//bmp.rows = height;
	//bmp.width = width;

	//bmp.buffer = (unsigned char*)malloc(bmp.rows * bmp.width * 4);
	// if (NULL == bmp.buffer)
	// {
	// 	printf("+ error: cannot allocate the buffer for the output bitmap.\n");
	// 	exit(EXIT_FAILURE);
	// }

	//bmp.pitch = ((width+3) & -4) * 4;
	//bmp.pixel_mode = FT_PIXEL_MODE_BGRA;

	//printf("%d\n", bmp.pitch);

	//stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);
	//printf("%d\n", stride);

	//surface = cairo_image_surface_create_for_data(bmp.buffer, CAIRO_FORMAT_ARGB32, width, height, stride);
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	if (CAIRO_STATUS_SUCCESS != cairo_surface_status(surface)) {
		printf("+ error: couldn't create the surface.\n");
		exit(EXIT_FAILURE);
	}
	cr = cairo_create(surface);
	if (CAIRO_STATUS_NO_MEMORY == cairo_status(cr)) {
		printf("+ error: out of memory, cannot create cairo_t*\n");
		exit(EXIT_FAILURE);
	}


	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	cairo_paint(cr);

	rendertext(cr);


	status = cairo_surface_write_to_png(surface, "out.png");
	cairo_surface_destroy(surface);
	cairo_destroy(cr);

	return 0;
}

void rendertext(cairo_t *cr) {
	PangoContext* context = NULL;
	PangoLayout *layout = NULL;
	PangoFontDescription *desc = NULL;
	PangoFontMap* font_map = NULL;
	PangoRectangle lastInkRect;
	PangoRectangle lastLogicalRect;

	memset(&lastInkRect, 0, sizeof(PangoRectangle));
	memset(&lastLogicalRect, 0, sizeof(PangoRectangle));

	// font_map = pango_ft2_font_map_new();
	// if (NULL == font_map) {
	// 	printf("+ error: cannot create the pango font map.\n");
	// 	exit(EXIT_FAILURE);
	// }

	// context = pango_font_map_create_context(font_map);
	// if (NULL == context) {
	// 	printf("+ error: cannot create pango font context.\n");
	// 	exit(EXIT_FAILURE);
	// }

	//cairo_translate(cr, 10, 20);
	layout = pango_cairo_create_layout(cr);
	if (NULL == layout) {
		printf("+ error: cannot create the pango layout.\n");
		exit(EXIT_FAILURE);
	}

	desc = pango_font_description_from_string("Comic Sans Africa 40");
	pango_layout_set_font_description(layout, desc);
	//pango_font_map_load_font(font_map, context, desc);
	pango_font_description_free(desc);

	pango_layout_set_markup(layout, "Hello World!", -1);


	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	//pango_ft2_render_layout(bmp, layout, 30, 100);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);

	pango_layout_get_pixel_extents(layout, &lastInkRect, &lastLogicalRect);
	cairo_translate(cr, 0, lastInkRect.height);

	pango_layout_set_markup(layout, "\t\u2022 <span foreground=\"green\"><b>Second</b></span> Hello!", -1);
	desc = pango_font_description_from_string("Comic Sans Africa 24");
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);

	cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);

	pango_layout_get_pixel_extents(layout, &lastInkRect, &lastLogicalRect);
	cairo_translate(cr, 0, lastInkRect.height);

	pango_layout_set_markup(layout, "\t\u2022 <span foreground=\"green\"><b>Third</b></span> Hello!", -1);
	desc = pango_font_description_from_string("Skia 24");
	pango_layout_set_font_description(layout, desc);
	pango_font_description_free(desc);

	cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
	pango_cairo_update_layout(cr, layout);
	pango_cairo_show_layout(cr, layout);






	g_object_unref(layout);
	//g_object_unref(font_map);
	//g_object_unref(context);
}
