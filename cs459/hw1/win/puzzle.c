/* Window Puzzle: Talk to Window Manager
     
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
	  Window Wid;
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
XTextProperty windowName, iconName;
Pixmap pmap;
XWMHints wmhints;

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
	/* XTextProperty windowName, iconName; */
	int count;
	char *display_name = NULL;
	int window_size = 0;	/* OK, or too SMALL to display contents */
	GC gc,gc1, gc2;
	XEvent report;
	/* Pixmap	pmap;
	XWMHints wmhints; */
	int incw, inch, endw, endh, xcoord, ycoord, xbox, ybox, tmp_x, w, rflag;
	int init_flag=0;


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
	register_win(width, height, 1, 0);


	/* create opaque window */
	win = XCreateSimpleWindow(display, RootWindow(display,screen), x, y, width, height, border_width, WhitePixel(display,screen), BlackPixel(display,screen));

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

	xempty=3; yempty=3;
	draw_icon_pixmap(gc1, win); /* draw icon subroutine */

	init_set_up(win);
	draw_text(win, gc, width, height);


	/* Event Loop */
	while (1)  {
                XNextEvent(display, &report);
                switch  (report.type) {

		case ButtonPress:
		  
		        incw = width/4;
			inch = ((height-30)/4);
			rflag = 0;
		        
			xcoord = report.xbutton.x;
		        ycoord = report.xbutton.y;
			
			printf("xcoord=%d ycoord=%d\n",xcoord, ycoord);
	
			xbox = (xcoord/incw); 
			ybox = ((ycoord-30)/inch);
			printf("xbox=%d ybox=%d\n",xbox, ybox);

			if (ycoord<30) {
			  if ((ycoord<=20)&&(ycoord>=10)&&(xcoord>=tmp_x)&&(xcoord<=(tmp_x+(w/2))))
			    {
			  if ((ycoord<=20)&&(ycoord>=10)&&(xcoord>=tmp_x)&&(xcoord<=(tmp_x+(w/2)))) {
			  printf("click observed in upper rectangle\n");
			  printf("calling reset button\n");
			  rflag=1;
			  initialize_index();
			  register_win(width, height, 0, rflag);
			  } 
			    }
			  else
			    break; }
 			if (((xbox==xempty || ybox==yempty))&&(rflag==0))
			  if (xempty==xbox)
			    { dist = yempty-ybox; dirv=1; }
			  else 
			    { dist = xempty-xbox; dirv=0; }
			
			else { 
			  if (rflag==0){
			  printf("Click not in same v or h axis");
			  break; }
			     }

			if (rflag==0) recompute_structure(xbox, ybox, dist, dirv, incw, inch, win, gc, gc1, gc2);

			                
                case Expose:
		  
		        if (rflag==1) 
			  { XUnmapSubwindows(display, win);
			    XFlush(display);
			    XDestroySubwindows(display, win);
			    init_set_up(win); 
			    rflag=0;
			    
			  }
			    
			XFlush(display);
			
		        XDrawRectangle(display,win,gc,0,0, ((4*width)/5), 30);
			XFillRectangle(display,win,gc,0,0, ((4*width)/5), 30);
			XDrawRectangle(display,win,gc2, ((4*width)/5),0,width/5, 30);
			XFillRectangle(display,win,gc2, ((4*width)/5),0,width/5, 30);
			
			w=width;
			tmp_x=(((4*w)/5)+((w-((4*w)/5))/2)-((w/12)/2));
			XDrawRectangle(display, win,gc, tmp_x, 10, (width/12), 10);
			
			move_resize_win(win);
			draw_text(win, gc, width, height);

			break;

		
		case ConfigureNotify:
			width=report.xconfigure.width;
			height=report.xconfigure.height;

			while ((width%4)!=0) { width++; }
			while ((height%4)!=0) { height++; }
			register_win(width, height, 0, 0);

		default:
		 	break;
		}
	}
}

recompute_structure(xbox, ybox, dist, dirv, incw, inch, win, gc, gc1, gc2)
int xbox;
int ybox;
int dist;
int dirv;
int incw;
int inch;
Window win;
GC gc;
GC gc1;
GC gc2;
{
int xdst, ydst;
xdst=xempty;
ydst=yempty;
xempty=xbox;
yempty=ybox;

      animate_tile(xbox, ybox, xdst, ydst, dist, dirv, incw, inch, win, gc, gc2);
      copy_struct(xbox, ybox, xdst, ydst, dist, dirv);
      draw_icon_pixmap(gc1, win);
}


copy_struct(xbox, ybox, xdst, ydst, dist, dirv)
int xbox, ybox, xdst, ydst, dist, dirv;
{
int ii;
    
if ((dist>0)&&(dirv==1))	/* tile above */
 for (ii=0; ii<dist; ii++){

    tile[ydst-ii][xdst].index=tile[ydst-(ii+1)][xdst].index;
    tile[ydst-ii][xdst].Wid=tile[ydst-(ii+1)][xdst].Wid;

 }

if ((dist<0)&&(dirv==1)) {	/* tile below */
  dist=abs(dist);
  for (ii=0; ii<dist; ii++){

    tile[ydst+ii][xdst].index=tile[ydst+(ii+1)][xdst].index;
    tile[ydst+ii][xdst].Wid=tile[ydst+(ii+1)][xdst].Wid;

  }
}

 if ((dist>0)&&(dirv==0))	/* tile left */
 for (ii=0; ii<dist; ii++){

    tile[ydst][xdst-ii].index=tile[ydst][xdst-(ii+1)].index;
    tile[ydst][xdst-ii].Wid=tile[ydst][xdst-(ii+1)].Wid;

 }

 if ((dist<0)&&(dirv==0)){	/* tile right */
  dist=abs(dist);
  for (ii=0; ii<dist; ii++){

    tile[ydst][xdst+ii].index=tile[ydst][xdst+(ii+1)].index;
    tile[ydst][xdst+ii].Wid=tile[ydst][xdst+(ii+1)].Wid;

  }
 }

tile[ybox][xbox].Wid=-1;
 tile[ybox][xbox].index=99; 
}


animate_tile(xbox, ybox, xdst, ydst, dist, dirv, incw, inch, win, gc, gc2)
int xbox, ybox, dist, dirv, incw, inch;
Window win;
GC gc, gc2;
{
int ii, jj;
jj=1;
      
      if ((dist>0)&&(dirv==1)){     /* tile above */
       for(ii=1; ii<=inch; ii++){
       while (jj<=dist){
	XMoveWindow(display, tile[ydst-jj][xdst].Wid, tile[ydst-jj][xdst].x, tile[ydst-jj][xdst].y+ii);
	XFlush(display);
	jj++;
	}
        jj=1;
	XFlush(display);
	burn_cpu();
       }
      }

      if ((dist<0)&&(dirv==1)){     /* tile below */
	dist=abs(dist);
	for(ii=1; ii<=inch; ii++){
	while (jj<=dist){
	XMoveWindow(display, tile[ydst+jj][xdst].Wid, tile[ydst+jj][xdst].x, tile[ydst+jj][xdst].y-ii);
	XFlush(display);
	jj++;
	}
        jj=1;
	XFlush(display);
	burn_cpu();
       }
      }
      if ((dist>0)&&(dirv==0)){     /* tile left */
	for(ii=1; ii<=incw; ii++){
        while (jj<=dist){
	XMoveWindow(display, tile[ydst][xdst-jj].Wid, tile[ydst][xdst-jj].x+ii, tile[ydst][xdst-jj].y);
	XFlush(display);
	jj++;
	}
        jj=1;
	XFlush(display);
	burn_cpu();
       }
      }
      if ((dist<0)&&(dirv==0)){     /* tile right */	
	dist=abs(dist);
	for(ii=1; ii<=incw; ii++){
	while (jj<=dist){
	XMoveWindow(display, tile[ydst][xdst+jj].Wid, tile[ydst][xdst+jj].x-ii, tile[ydst][xdst+jj].y);
	XFlush(display);
	jj++;
	}
        jj=1;
	XFlush(display);
	burn_cpu();
       }
      }
}
      	
burn_cpu()
{
int cpu;
for(cpu=0; cpu<22222; cpu++);
}


move_resize_win(win)
Window win;
{
int ii, jj;
Window wid;

 for (ii=0; ii<4; ii++){
   for (jj=0; jj<4; jj++){
     if (tile[ii][jj].Wid!=-1){
     XMoveWindow(display, tile[ii][jj].Wid, tile[ii][jj].x, tile[ii][jj].y);
     XResizeWindow(display, tile[ii][jj].Wid, tile[ii][jj].w, tile[ii][jj].h);

          XFlush(display);  /* debugging */
     }
   }
 }

}


draw_text(win, gc, width, height)
Window win;
GC gc;
{
int ii, jj, incw, inch;
int len1=1;
int len2=2;

incw = width/4;
inch = (height-30)/4;

 for (ii=0; ii<4; ii++) {
   for (jj=0; jj<4; jj++) {
     if (tile[ii][jj].Wid!=-1){
       if (tile[ii][jj].index<10)
	 XDrawString(display, tile[ii][jj].Wid, gc, incw/2, inch/2, num[tile[ii][jj].index-1], len1);
       else
	 XDrawString(display, tile[ii][jj].Wid, gc, incw/2, inch/2, num[tile[ii][jj].index-1], len2);

     XFlush(display);  /* debug, debug, debug */
     }
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
tile[3][3].Wid=-1;  
xempty=3;
yempty=3;
}



register_win(width, height, flag, rflag)
unsigned int width, height;
int flag, rflag;
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


/* draw 15 windows initially */
/* do not create more windows */
/* resize and move pre-existing ones */

init_set_up(win)
Window win;
{
int ii, jj, count;
Window wid;

 for (ii=0; ii<4; ii++){
   for (jj=0; jj<4; jj++){

     wid=XCreateSimpleWindow(display,win,tile[ii][jj].x, tile[ii][jj].y, tile[ii][jj].w, tile[ii][jj].h,1, BlackPixel(display, screen), WhitePixel(display, screen));
     tile[ii][jj].Wid=wid;
     if (tile[ii][jj].index!=99) 
       XMapWindow(display, wid);
          
     XFlush(display);  /* debugging */
   }
 }
tile[3][3].Wid=-1;
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
    
    if ((ii==xempty)&&(jj==yempty)){
      XDrawRectangle(display,pmap,gc1,(ii*10),(jj*10),10,10);
      XFillRectangle(display,pmap,gc1,(ii*10),(jj*10),10,10);
 }
    else
        XDrawRectangle(display,pmap,gc1,(ii*10),(jj*10),10,10);
  }
}


	wmhints.flags= IconPixmapHint;
	wmhints.icon_pixmap = pmap;
	XSetWMProperties(display,win, &windowName, &iconName, NULL, NULL,NULL,&wmhints,NULL);
	XFlush(display);

}
