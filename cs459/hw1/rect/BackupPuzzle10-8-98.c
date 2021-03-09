/* Basic7: Talk to Window Manager
     
*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>

#include <stdio.h>


/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

	struct {
	  int index;
	  int x;
	  int y;
	  int w;
	  int h;
	} tile[4][4];

Display *display;
int screen;
static char *progname;
int xempty, yempty, dist, dirv;
char num[16][2] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "99"};

void main(argc, argv)
int argc;
char **argv;
{
	Window win;
	unsigned int width, height, x = 0, y = 0; 	/* window size and position */
	unsigned int border_width = 4;	/* four pixels */
	unsigned int display_width, display_height;
	unsigned int icon_width, icon_height;
	char *window_name = "Xpuzzle";
	char *icon_name = "Xpuzzle";
	XTextProperty windowName, iconName;
	int count;
	char *display_name = NULL;
	int window_size = 0;	/* OK, or too SMALL to display contents */
	GC gc,gc1;
	XEvent report;
	Pixmap	pmap;
	XWMHints wmhints;
	int incw, inch, endw, endh, xcoord, ycoord, xbox, ybox;


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
	width = display_width/5, height = display_height/3;

	while ((width%4)!=0) { width++; }
	while ((height%4)!=0) { height++; }
	  
	printf("width=%d height=%d\n",width,height);
	initialize_index();
	register_tile(width, height, 1);


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
	XSetForeground(display, gc, BlackPixel(display,screen));
	XSetBackground(display, gc, WhitePixel(display,screen));

	XSelectInput(display, win, ExposureMask |  ButtonPressMask |StructureNotifyMask);
	

		/* Construct Pixmap for Icon and Tell WM */
	pmap=XCreatePixmap(display,RootWindow(display,screen),40,40,1);
	gc1=XCreateGC(display,pmap,0,NULL);
	XSetForeground(display, gc1, WhitePixel(display,screen));
	XFillRectangle(display,pmap,gc1,0,0,40,40);
	XSetForeground(display, gc1, BlackPixel(display,screen));

        XDrawRectangle(display,pmap,gc1,0,0, 10,10);
        XDrawRectangle(display,pmap,gc1,0,10,10,10);
        XDrawRectangle(display,pmap,gc1,0,20,10,10);
        XDrawRectangle(display,pmap,gc1,0,30,10,10);

        XDrawRectangle(display,pmap,gc1,10,0, 10,10);
        XDrawRectangle(display,pmap,gc1,10,10,10,10);
        XDrawRectangle(display,pmap,gc1,10,20,10,10);
        XDrawRectangle(display,pmap,gc1,10,30,10,10);

        XDrawRectangle(display,pmap,gc1,20,0, 10,10);
        XDrawRectangle(display,pmap,gc1,20,10,10,10);
        XDrawRectangle(display,pmap,gc1,20,20,10,10);
        XDrawRectangle(display,pmap,gc1,20,30,10,10);

        XDrawRectangle(display,pmap,gc1,30,0, 10,10);
        XDrawRectangle(display,pmap,gc1,30,10,10,10);
        XDrawRectangle(display,pmap,gc1,30,20,10,10);
        XDrawRectangle(display,pmap,gc1,30,30,10,10);

	wmhints.flags= IconPixmapHint;
	wmhints.icon_pixmap = pmap;
	XSetWMProperties(display,win, &windowName, &iconName, NULL, NULL,NULL,&wmhints,NULL);

	/* Event Loop */
	while (1)  {
                XNextEvent(display, &report);
                switch  (report.type) {

		case ButtonPress:
		  
		        incw = width/4;
			inch = ((height-30)/4);
		        
			xcoord = report.xbutton.x;
		        ycoord = report.xbutton.y;
			
			printf("xcoord=%d ycoord=%d\n",xcoord, ycoord);
	
			xbox = (xcoord/incw); 
			ybox = ((ycoord-30)/inch);
			printf("xbox=%d ybox=%d\n",xbox, ybox);

			if ((xbox==xempty || ybox==yempty))
			  if (xempty==xbox)
			    { dist = yempty-ybox; dirv=1; }
			  else 
			    { dist = xempty-xbox; dirv=0; }
			
			/* else { printf("Click not in same v or h axis");
			   break; } */

			recompute_structure(xbox, ybox, dist, dirv);
			
			if (ycoord<=30) {
			  printf("click observed in upper rectangle\n");
			  printf("calling reset button\n");			  
			  initialize_index();
			  register_tile(width, height, 1);
			                }

			

                case Expose:

		        XClearWindow(display, win);
		        XDrawRectangle(display,win,gc,0,0, width, 30);
			XFillRectangle(display,win,gc,0,0, width, 30);
			
			/* XDrawRectangle(display,win,gc,(7*(width/8)),0, width, 25); */
			

			draw_rect(win, gc);
			draw_text(win, gc);

			break;

		
		case ConfigureNotify:
			width=report.xconfigure.width;
			height=report.xconfigure.height;

			while ((width%4)!=0) { width++; }
			while ((height%4)!=0) { height++; }
			register_tile(width, height, 0);

		default:
		 	break;
		}
	}
}

recompute_structure(xbox, ybox, dist, dirv)
int xbox;
int ybox;
int dist;
int dirv;
{

int xdst, ydst;
xdst=xempty;
ydst=yempty;
xempty=xbox;
yempty=ybox;

    if ((dist>0)&&(dirv==1))	/* tile above */

      while (dist>0){
	     swap_struct(xbox, ybox++, xdst, ydst);
	     --dist;
		    }

    if ((dist<0)&&(dirv==1))	/* tile below */

      while (dist<0){
	     swap_struct(xbox, ybox--, xdst, ydst);
	     ++dist;
                    }

    if ((dist>0)&&(dirv==0))	/* tile left */

      while (dist>0){
	     swap_struct(xbox++, ybox, xdst, ydst);
	     --dist;
                    }

    if ((dist<0)&&(dirv==0))	/* tile right */

      while (dist<0){
	     swap_struct(xbox--, ybox, xdst, ydst);
	     ++dist;
                    }
}


swap_struct(xbox, ybox, xdst, ydst)
int xbox;
int ybox;
int xdst;
int ydst;
{

int tmp_index;

tmp_index=tile[ydst][xdst].index;
tile[ydst][xdst].index=tile[ybox][xbox].index;
tile[ybox][xbox].index=tmp_index;
}



draw_rect(win, gc)
Window win;
GC gc;
{
int ii, jj;

 for (ii=0; ii<4; ii++){
   for (jj=0; jj<4; jj++){

     XDrawRectangle(display,win,gc,tile[ii][jj].x, tile[ii][jj].y, tile[ii][jj].w, tile[ii][jj].h);
     
     if (tile[ii][jj].index==99)
       XFillRectangle(display,win,gc,tile[ii][jj].x, tile[ii][jj].y, tile[ii][jj].w, tile[ii][jj].h);
     
     XFlush(display);  /* debugging */
   }
 }

}


draw_text(win, gc)
Window win;
GC gc;
{
int ii, jj;
int len1=1;
int len2=2;

 for (ii=0; ii<4; ii++) {
   for (jj=0; jj<4; jj++) {
     if (tile[ii][jj].index<10)
     XDrawString(display, win, gc, ((tile[ii][jj].x)+(tile[ii][jj].w/2)), ((tile[ii][jj].y)+(tile[ii][jj].h/2)), num[tile[ii][jj].index-1], len1);
     else
     XDrawString(display, win, gc, ((tile[ii][jj].x)+(tile[ii][jj].w/2)), ((tile[ii][jj].y)+(tile[ii][jj].h/2)), num[tile[ii][jj].index-1], len2);

     XFlush(display);  /* debug, debug, debug */
   }
 }
}



initialize_index()
{
int ii, jj;
int count = 1;
/* Initialize data structure */

  for (ii=0; ii<4; ii++){
    for (jj=0; jj<4; jj++){

      tile[ii][jj].index=count;
      count++;
    }
  }
tile[3][3].index=99;  
xempty=3;
yempty=3;
}



register_tile(width, height, flag)
unsigned int width, height;
int flag;
{
int inw = width/4;
int inh = ((height-30)/4);

 if (flag==1) { tile[3][3].index=99; xempty=3; yempty=3; } 

  /* First Row */
tile[0][0].x=(inw*0);
tile[0][0].y=30;
tile[0][0].w=inw;
tile[0][0].h=inh;

tile[0][1].x=(inw*1);
tile[0][1].y=30;
tile[0][1].w=inw;
tile[0][1].h=inh;

tile[0][2].x=(inw*2);
tile[0][2].y=30;
tile[0][2].w=inw;
tile[0][2].h=inh;

tile[0][3].x=(inw*3);
tile[0][3].y=30;
tile[0][3].w=inw;
tile[0][3].h=inh;

  /* Second Row */

tile[1][0].x=(inw*0);
tile[1][0].y=(inh+30);
tile[1][0].w=inw;
tile[1][0].h=inh;
 
tile[1][1].x=(inw*1);
tile[1][1].y=(inh+30);
tile[1][1].w=inw;
tile[1][1].h=inh;
 
tile[1][2].x=(inw*2);
tile[1][2].y=(inh+30);
tile[1][2].w=inw;
tile[1][2].h=inh;
 
tile[1][3].x=(inw*3);
tile[1][3].y=(inh+30);
tile[1][3].w=inw;
tile[1][3].h=inh;
 
  /* Third Row */

tile[2][0].x=(inw*0);
tile[2][0].y=((inh*2)+30);
tile[2][0].w=inw;
tile[2][0].h=inh;
 
tile[2][1].x=(inw*1);
tile[2][1].y=((inh*2)+30);
tile[2][1].w=inw;
tile[2][1].h=inh;
 
tile[2][2].x=(inw*2);
tile[2][2].y=((inh*2)+30);
tile[2][2].w=inw;
tile[2][2].h=inh;
 
tile[2][3].x=(inw*3);
tile[2][3].y=((inh*2)+30);
tile[2][3].w=inw;
tile[2][3].h=inh;

  /* Forth Row */

tile[3][0].x=(inw*0);
tile[3][0].y=((inh*3)+30);
tile[3][0].w=inw;
tile[3][0].h=inh;
 
tile[3][1].x=(inw*1);
tile[3][1].y=((inh*3)+30);
tile[3][1].w=inw;
tile[3][1].h=inh;
 
tile[3][2].x=(inw*2);
tile[3][2].y=((inh*3)+30);
tile[3][2].w=inw;
tile[3][2].h=inh;
 
tile[3][3].x=(inw*3);
tile[3][3].y=((inh*3)+30);
tile[3][3].w=inw;
tile[3][3].h=inh;
 
}




