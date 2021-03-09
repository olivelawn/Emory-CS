#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>



unsigned long AllocNamedColor( display, colormap, colorname, default_color )

Display		*display;
Colormap	colormap;
char		colorname[];
unsigned long	default_color;

/*
 *	Allocates a read-only (sharable) color cell in 
 *	the given colormap, using the RGB data base to 
 *	convert the color name to an RGB value.
 */

{	/* AllocNamedColor */
        XColor  	hardwarecolor, exactcolor;
	unsigned long	color;
	int		status;

	status = XAllocNamedColor( display, colormap,
			colorname,
			&hardwarecolor,
			&exactcolor );

	if ( status != 0 )
		{
		color = hardwarecolor.pixel;
		}
	else
		{
		color = default_color;
		}

	return( color );

}	/* AllocNamedColor */


