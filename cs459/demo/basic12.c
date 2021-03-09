/* Basic11: Illustrate XOR */
     
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
Pixmap pmap;

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
	XWMHints wmhints;
	GC gc,gc1;
	XEvent report;
	int i;
	XPoint points[6];
	i=0;

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
	gc=XCreateGC(display,win,0,NULL);
	XSetForeground(display, gc, BlackPixel(display,screen));
	XSetBackground(display, gc, WhitePixel(display,screen));

	XSelectInput(display, win, ExposureMask |  ButtonPressMask |StructureNotifyMask|KeyPressMask);
	
		/* Construct Pixmap for Icon and Tell WM */
	pmap=XCreatePixmap(display,RootWindow(display,screen),40,40,1);
	gc1=XCreateGC(display,pmap,0,NULL);
	XSetForeground(display, gc1, WhitePixel(display,screen));
	XFillRectangle(display,pmap,gc1,0,0,40,40);
	XSetForeground(display, gc1, BlackPixel(display,screen));
        XDrawLine(display,pmap,gc1,0,0, 40,40);
        XDrawLine(display,pmap,gc1,40,0, 0,40);
	wmhints.flags= IconPixmapHint;
	wmhints.icon_pixmap = pmap;
	XSetWMProperties(display,win, NULL, NULL, NULL, NULL,NULL,&wmhints,NULL);

	XSetStipple(display, gc, pmap);

	/* Event Loop */
	while (1)  {
                XNextEvent(display, &report);
                switch  (report.type) {
		case KeyPress:
	 		XSetFunction(display, gc, GXxor);
			if (i) XCopyPlane(display, pmap, win, gc, 0,0,40,40,10*i,10*i,1);
			i++;
			XCopyPlane(display, pmap, win, gc, 0,0,40,40,10*i,10*i,1);
			break;
        case Expose:
			XClearWindow(display, win);
	 		XSetFunction(display, gc, GXcopy);
	       	XFillPolygon(display,win,gc,points,5,Complex,CoordModeOrigin);
	 		XSetFunction(display, gc, GXxor);
			if (i)XCopyPlane(display, pmap, win, gc, 0,0,40,40,10*i,10*i,1);
			break;

		case ButtonPress:
			exit(1);
		case ConfigureNotify:
			width=report.xconfigure.width-20;
			height=report.xconfigure.height-20;
			points[0].x=width/2; points[0].y=20;
			points[1].x=width; points[1].y=height;
			points[2].x=20; points[2].y=height/2;
			points[3].x=width; points[3].y=height/2;
			points[4].x=20; points[4].y=height;
			points[5].x=width/2; points[5].y=20;
		default:
		 	break;
		}
	}
}

changegc(gc,j)
	GC gc;
	int j;

{

	 XSetFunction(display, gc, j%16);
}
