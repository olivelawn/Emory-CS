/* Colo1 illustrate allocating colors by name */
     
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
Visual *visual;
Colormap colormap;
XSetWindowAttributes attributes;

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
	int blue,red,depth;
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

	/* setup visual and colormap */

	if (SetUpVisual( display, screen, &visual, &depth ) != True) {
		printf("Could not get visual\n");
		exit(1);
		};

	SetUpColormap( display, screen, RootWindow(display,screen), visual, &colormap );
	blue=AllocNamedColor( display, colormap, "blue", 0 );
	red=AllocNamedColor( display, colormap, "red", 1 );
	/* create opaque window */

	attributes.background_pixel=red;
	attributes.border_pixel=blue;
	attributes.colormap = colormap;
	win = XCreateWindow(display, RootWindow(display,screen), x, y, width, height, border_width, depth, InputOutput,visual,CWBackPixel|CWBorderPixel|CWColormap,&attributes);



	/* Display window */
	XMapWindow(display, win);
	gc=XCreateGC(display,win,0,NULL);
	XSetForeground(display, gc, blue);
	XSetBackground(display, gc, red);

	XSelectInput(display, win, ExposureMask |  ButtonPressMask |StructureNotifyMask|KeyPressMask);
	
		/* Construct Pixmap for Icon and Tell WM */
	pmap=XCreatePixmap(display,RootWindow(display,screen),40,40,1);
	gc1=XCreateGC(display,pmap,0,NULL);
	XSetForeground(display, gc1, blue);
	XFillRectangle(display,pmap,gc1,0,0,40,40);
	XSetForeground(display, gc1, red);
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
			XClearWindow(display, win);
			changegc(gc,i++);
        case Expose:
	       	XFillPolygon(display,win,gc,points,5,Complex,CoordModeOrigin);
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

	 XSetFillRule(display, gc, j%2);
	 XSetFillStyle(display, gc, (j/2)%2 ? FillSolid : FillStippled);
}
