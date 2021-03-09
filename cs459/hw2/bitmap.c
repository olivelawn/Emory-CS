/* Window Puzzle: Talk to Window Manager
     
*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>
#include <stdio.h>

#define offset 130

/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

struct {
  Bool On;
	} grid[16][16];

int geom[6];

Display *display;
int screen;
static char *progname;
int awidth, aheight, xbox, ybox, ubox, vbox;
unsigned int width, height;
XTextProperty windowName, iconName;
Pixmap pmap;
XWMHints wmhints;

void main(argc, argv)
int argc;
char **argv;
{
	Window win;
	unsigned x = 0, y = 0; 	/* window size and position */
	unsigned int border_width = 4;	/* four pixels */
	unsigned int display_width, display_height;
	unsigned int icon_width, icon_height;
	char *window_name = "Xbitmap";
	char *icon_name = "Xbitmap";
	int count;
	char *display_name = NULL;
	int window_size = 0;	/* OK, or too SMALL to display contents */
	GC gc, gc1, gc2;
	XEvent report;
	int ycoord, xcoord, ucoord, vcoord, wait, ind;



       	progname = argv[0];

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
	width = (3.5*display_width)/7, height = (4.4*display_height)/6;

	while ((width%2)!=0) { width++; }
	while ((height%2)!=0) { height++; }
	  
	printf("width=%d height=%d\n",width,height);



	/* create opaque window */
	win = XCreateSimpleWindow(display, RootWindow(display,screen), x, y, width, height, border_width, BlackPixel(display,screen), WhitePixel(display,screen));

	/* These calls store window_name and icon_name into XTextProperty */

	if (XStringListToTextProperty(&window_name, 1, &windowName) == 0) {
	  (void) fprintf( stderr, "%s: structure allocation for windowname failed.\n", progname);
	  exit(-1);
	}  

	if (XStringListToTextProperty(&icon_name, 1, &iconName) == 0) {
	  (void) fprintf( stderr, "%s: structure allocation for windowname failed.\n", progname);
	  exit(-1);
	}  


	/* Display window */
	XMapWindow(display, win);
	gc=XCreateGC(display,win,0,NULL);
	XSetForeground(display, gc, BlackPixel(display,screen));  /* gc draws black */
	XSetBackground(display, gc, WhitePixel(display,screen));  /* gc2 graws white */

	gc2=XCreateGC(display,win,0,NULL);
	XSetForeground(display, gc2, WhitePixel(display,screen));
	XSetBackground(display, gc2, BlackPixel(display,screen));

	XSelectInput(display, win, ExposureMask |  ButtonPressMask |StructureNotifyMask);
	

		/* Construct Pixmap for Icon and Tell WM */
	pmap=XCreatePixmap(display,RootWindow(display,screen),40,40,1);
	gc1=XCreateGC(display,pmap,0,NULL);
	
	init_grid();
        draw_icon_pixmap(gc1, win);   /* draw icon subroutine */


	/* Event Loop */
	while (1)  {
                XNextEvent(display, &report);
                switch  (report.type) {

		case ButtonPress:
		        
			xcoord = report.xbutton.x;
		        ycoord = report.xbutton.y;
		       	printf("xcoord=%d ycoord=%d\n",xcoord, ycoord);

			if (hit_clear(xcoord, ycoord)==1)  /* hit clear button? */
			  clear_routine();
			
			if ((ind=hit_geom(xcoord, ycoord))!=-99)  /* hit geom button? */
			  set_geom(ind);
		     
			
			if (hit_grid(xcoord, ycoord)) {
			  xbox=((xcoord-offset)/(awidth/16));
			  ybox=((ycoord-offset)/(awidth/16));
			  ubox=((ucoord-offset)/(awidth/16));
			  vbox=((vcoord-offset)/(awidth/16));
			  printf("xbox=%d, ybox=%d\n", xbox, ybox);
			}

			
			if ((hit_grid(xcoord, ycoord))&&(wait==1)) {
			  draw_2pt(win, gc, ucoord, vcoord, xcoord, ycoord);
			  wait=0;
			}

			else if ((hit_grid(xcoord, ycoord))&&(wait==0)) {
			  ucoord=xcoord;
			  vcoord=ycoord;
			  wait=1;
			}

		
			
			  
			
                case Expose:
		  
		        XClearWindow(display, win);
			draw_left_plane(win, gc);
		        draw_right_plane(win, gc);
			break;

		
		case ConfigureNotify:
			width=report.xconfigure.width;
			height=report.xconfigure.height;

			while ((width%2)!=0) { width++; }
			while ((height%2)!=0) { height++; }
		default:
		 	break;
		}
	}
}

Bool hit_clear(xcoord, ycoord)
int xcoord, ycoord;
{
  if ((xcoord>5)&&(xcoord<115)&&(ycoord>30)&&(ycoord<45))
    return True;
  else
    return False;
}

clear_routine()
{
init_grid();
}


int hit_geom(xcoord, ycoord)
int xcoord, ycoord;
{
int ii; 
int hit=-99;

 for(ii=1; ii<7; ii++){
   if ((xcoord>5)&&(xcoord<115)&&(ycoord>(20*ii)+30)&&(ycoord<(20*ii)+30+15)) {
     hit=1; break; }
 }
   if (hit==-99)
     return hit;
   else 
     return --ii;
}

set_geom(ind)
int ind;
{
int ii;
  for(ii=0; ii<6; ii++)
    geom[ii]=0;

  geom[ind]=1;
}

Bool hit_grid(xcoord, ycoord)
int xcoord, ycoord;
{

  if ((xcoord>130)&&(xcoord<(130+awidth))&&(ycoord>130)&&(ycoord<(130+awidth)))
    return True;
  else
    return False;
}

 
draw_left_plane(win, gc)
Window win;
GC gc;
{
int ii;
char *clear = "Clear";
char *point = "Point";
char *line = "Line";
char *rect = "Rectangle";
char *f_rect = "Filled Rectangle";
char *circle = "Circle";
char *f_circle = "Filled Circle";

 XDrawLine(display,win,gc,0,25,width,25);  
 XDrawLine(display,win,gc,120,25,120,height);  

 for (ii=0; ii<7; ii++){
 XDrawRectangle(display,win,gc, 5, (20*ii)+30, 110, 15);
 }
 ii=0;
 XDrawString(display,win,gc, 42, (20*ii+13)+30, clear, 5 ); ii++;
 XDrawString(display,win,gc, 42, (20*ii+13)+30, point, 5 ); ii++;
 XDrawString(display,win,gc, 44, (20*ii+13)+30, line, 4 ); ii++;
 XDrawString(display,win,gc, 28, (20*ii+13)+30, rect, 9 ); ii++;
 XDrawString(display,win,gc, 10, (20*ii+13)+30, f_rect, 16 ); ii++;		
 XDrawString(display,win,gc, 39, (20*ii+13)+30, circle, 6 ); ii++;
 XDrawString(display,win,gc, 20, (20*ii+13)+30, f_circle, 13 );
	
 XFlush(display);

}


draw_right_plane(win, gc)
Window win;
GC gc;
{
int ii, jj, xstart, ystart, box_size;

awidth=width-120;
aheight=height-25;

awidth=awidth-20;
box_size=awidth/16;
xstart=130;
ystart=130;

 for(ii=0; ii<16; ii++){
   for(jj=0; jj<16; jj++) {
     XDrawRectangle(display,win,gc,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     if (grid[ii][jj].On==True)
     XFillRectangle(display,win,gc,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     XFlush(display);
   }
 }

}


draw_2pt(win, gc)
Window win;
GC gc;
{
if (geom[1]==1)  /* draw line */
  draw_line(win, gc, ubox, vbox, xbox, ybox);

else if (geom[2]==1)  /* draw rectangle */
  draw_rect(win, gc, ubox, vbox, xbox, ybox);

else if (geom[3]==1)  /* draw filled rectangle */
  draw_frect(win, gc);

else if (geom[4]==1)  /* draw circle */
  draw_circle(win, gc);

else if (geom[5]==1)  /* draw filled circle */
  draw_fcircle(win, gc);
}

draw_line(win, gc, u, v, x, y)
Window win;
GC gc;
int u, v, x, y;
{
int dist, ii, tempx, tmp;
printf("entering draw_line\n");

if ((u==x)&&(v==y))  /* same point */
     draw_point(x, y);

else if ((u==x)||(v==y)){   /* in same axis v or h*/

  if (v==y) {
    dist=x-u;
    dist=abs(dist);
    if (u<x)
      tmp=u;
    else
      tmp=x;
       for(ii=0; ii<dist+1; ii++)
	 draw_point(ii+tmp, v);
   }

  else if (u==x) {
    dist=y-v;
    dist=abs(dist);
    if (v<y)
      tmp=v;
    else
      tmp=y;
       for(ii=0; ii<dist+1; ii++)
	 draw_point(u, ii+tmp);
  }
}
}


draw_rect(win, gc, u, v, x, y)
Window win;
GC gc;
int u, v, x, y;
{
draw_line(win, gc, u, v, x, v);
draw_line(win, gc, u, v, u, y);
draw_line(win, gc, u, y, x, y);
draw_line(win, gc, x, y, x, v);

}

 
 

draw_frect(win, gc, u, v, x, y)
Window win;
GC gc;
{
printf("entering draw_frect\n");
/* draw outline */
draw_line(win, gc, u, v, x, v);
draw_line(win, gc, u, v, u, y);
draw_line(win, gc, u, y, x, y);
draw_line(win, gc, x, y, x, v);
/* fill her in */


}

draw_circle(win, gc)
Window win;
GC gc;
{
printf("entering draw_circle\n");
}

draw_fcircle(win, gc)
Window win;
GC gc;
{
printf("entering draw_fcircle\n");
}



draw_icon_pixmap(gc1, win)
GC gc1;
Window win;
{
int ii, jj;

	XSetForeground(display, gc1, WhitePixel(display,screen));
	XFillRectangle(display,pmap,gc1,0,0,40,40);
	XSetForeground(display, gc1, BlackPixel(display,screen));

for (ii=0; ii<4; ii++){
  for(jj=0; jj<4; jj++){
    
      XDrawRectangle(display,pmap,gc1,(ii*10),(jj*10),10,10);
      XFillRectangle(display,pmap,gc1,(ii*10),(jj*10),10,10);

  }
}


	wmhints.flags= IconPixmapHint;
	wmhints.icon_pixmap = pmap;
	XSetWMProperties(display,win, &windowName, &iconName, NULL, NULL,NULL,&wmhints,NULL);
	XFlush(display);

} 


init_grid()
{
int ii, jj;

 for(ii=0; ii<16; ii++) {
   for(jj=0; jj<16; jj++) {
     grid[ii][jj].On=False;
   }
 }
}


draw_point(xbox, ybox)
int xbox, ybox;
{
grid[ybox][xbox].On=True;
}







