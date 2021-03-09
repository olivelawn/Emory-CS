/* Basic4: Actually Draw something
	-- must create a graphics context and do drawing request
     
*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>

#include <stdio.h>


/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */
Display *display;
int screen;

void main(argc, argv)
int argc;
char **argv;
{
	Window win;
	unsigned int width, height, x = 0, y = 0; 	/* window size and position */
	unsigned int border_width = 4;	/* four pixels */
	unsigned int display_width, display_height;
	unsigned int icon_width, icon_height;
	char *window_name = "basicwin";
	int count;
	char *display_name = NULL;
	int window_size = 0;	/* OK, or too SMALL to display contents */
	GC gc;

	/* connect to X server */

	if ( (display=XOpenDisplay(display_name)) == NULL )
	{
		(void) fprintf( stderr, "basicwin: cannot connect to X server %s\n", XDisplayName(display_name));
		exit( -1 );
	}

	/* get screen size from display structure macro */
	screen = DefaultScreen(display);
	display_width = DisplayWidth(display, screen);
	display_height = DisplayHeight(display, screen);


	/* size window */
	width = display_width/3, height = display_height/4;
	printf("width=%d height=%d\n",width,height);

	/* create opaque window */
	win = XCreateSimpleWindow(display, RootWindow(display,screen), x, y, width, height, border_width, BlackPixel(display,
	    screen), WhitePixel(display,screen));

	/* Display window */
	XMapWindow(display, win);
	XFlush(display);
	sleep(5);
	gc=XCreateGC(display,win,0,NULL);
	XSetForeground(display, gc, BlackPixel(display,screen));
	XSetBackground(display, gc, WhitePixel(display,screen));
	XDrawLine(display,win,gc,0,0, width,height);
	XDrawLine(display,win,gc,0,height, width,0);
	XFlush(display);
	sleep(20);

}

