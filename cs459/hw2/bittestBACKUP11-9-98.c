/* Window Puzzle: Talk to Window Manager
     
*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>
#include <stdio.h>

#define offset 130
#define gsize 40
/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

struct {
  unsigned long pixel;
  Bool On;
	} grid[gsize][gsize];

int geom[6];
FILE *file;
unsigned long col[128], cur_pixel;
Display *display;
int screen;
static char *progname;
int awidth, aheight, x1box, y1box, xbox, ybox, lookup[16][8];
unsigned int width, height;
XTextProperty windowName, iconName;
Pixmap pmap;
XWMHints wmhints;
XColor color, color2, rgb_db_def;
GC gc3, gc4;

void main(argc, argv)
int argc;
char **argv;
{
	Window win, root;
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

	gc3=XCreateGC(display,win,0,NULL);
	gc4=XCreateGC(display,win,0,NULL);

	XSelectInput(display, win, ExposureMask |  ButtonPressMask |StructureNotifyMask);
	

		/* Construct Pixmap for Icon and Tell WM */
	pmap=XCreatePixmap(display,RootWindow(display,screen),40,40,1);
	gc1=XCreateGC(display,pmap,0,NULL);
	
	init_lookup();
	init_grid();
        draw_icon_pixmap(gc1, win);   /* draw icon subroutine */
	fill_col_array(win, gc);



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

			if (hit_color(xcoord, ycoord))  /* hit color grid? */
			  set_color(xcoord, ycoord, win, gc);

			if (hit_save(xcoord, ycoord))
			  save();

			if (hit_restore(xcoord, ycoord))
			  restore();

			if (hit_quit(xcoord, ycoord))
			  quit();
			
			
			if (hit_grid(xcoord, ycoord)) {   /* hit bitmap grid? */
			  x1box=((xcoord-offset)/(awidth/gsize));
			  y1box=((ycoord-offset)/(awidth/gsize));
			  xbox=((ucoord-offset)/(awidth/gsize));
			  ybox=((vcoord-offset)/(awidth/gsize));
			  printf("xbox=%d, ybox=%d\n", xbox, ybox);
			}


			if ((pointOn())&&(hit_grid(xcoord, ycoord)))  
			  draw_point(x1box, y1box);

			
			else if ((hit_grid(xcoord, ycoord))&&(wait==1)) {
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
		        draw_right_plane(win, gc, gc2);
			draw_pixmap(win, gc);
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


Bool hit_color(xcoord, ycoord)
int xcoord, ycoord;
{
   if ((xcoord>5)&&(xcoord<69)&&(ycoord>250)&&(ycoord<378))
    return True;
  else
    return False;
}

set_color(xcoord, ycoord, win, gc)
int xcoord, ycoord;
{
int xcbox, ycbox;

xcbox=(xcoord-5)/8;  
ycbox=(ycoord-250)/8;

cur_pixel=col[lookup[ycbox][xcbox]];
}  


Bool hit_save(xcoord, ycoord)
{
  if ((xcoord>5)&&(xcoord<115)&&(ycoord>400)&&(ycoord<415))
    return True;
  else
    return False;
}


Bool hit_restore(xcoord, ycoord)
{
  if ((xcoord>5)&&(xcoord<(115))&&(ycoord>420)&&(ycoord<435))
    return True;
  else
    return False;
}

Bool hit_quit(xcoord, ycoord)
{
  if ((xcoord>5)&&(xcoord<(115))&&(ycoord>440)&&(ycoord<455))
    return True;
  else
    return False;
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
int ii, jj, count;
char *clear = "Clear";
char *point = "Point";
char *line = "Line";
char *rect = "Rectangle";
char *f_rect = "Filled Rectangle";
char *circle = "Circle";
char *f_circle = "Filled Circle";
char *save = "Save";
char *restore = "Restore";
char *quit = "Quit";

 count=0; 

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

 XSetForeground(display, gc3, cur_pixel);
 XDrawRectangle(display,win,gc, 5, 190, 50, 40);
 XFillRectangle(display,win,gc3, 5, 190, 50, 40);
 XFlush(display);

  for(ii=0; ii<16; ii++) {
   for(jj=0; jj<8; jj++) {
     XSetForeground(display, gc3, col[count++]);  
     XDrawRectangle(display, win, gc, 5+(jj*8), 250+(ii*8), 8, 8);
     XFillRectangle(display, win, gc3, 5+(jj*8), 250+(ii*8), 8, 8);
      XFlush(display);
   }
  }
  

  for (ii=0; ii<3; ii++){
    XDrawRectangle(display,win,gc, 5, (20*ii)+400, 110, 15);
  }
  ii=0;
  XDrawString(display,win,gc, 42, (20*ii+13)+400, save, 4 ); ii++;
  XDrawString(display,win,gc, 36, (20*ii+13)+400, restore, 7 ); ii++;
  XDrawString(display,win,gc, 42, (20*ii+13)+400, quit, 4 ); ii++;
}


draw_right_plane(win, gc, gc2)
Window win;
GC gc, gc2;
{
int ii, jj, xstart, ystart, box_size;

awidth=width-120;
aheight=height-25;

awidth=awidth-20;
box_size=awidth/gsize;
xstart=130;
ystart=130;

 for(ii=0; ii<gsize; ii++){
   for(jj=0; jj<gsize; jj++) {
     XDrawRectangle(display,win,gc,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     if (grid[ii][jj].On==True) {  /* draw the current color */
       XSetForeground(display, gc4, grid[ii][jj].pixel); 
       XFillRectangle(display,win,gc4,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     }
     XFlush(display);
   }
 }
}


draw_2pt(win, gc)
Window win;
GC gc;
{
if (geom[1]==1)  /* draw line */
  draw_line(win, gc, xbox, ybox, x1box, y1box);

else if (geom[2]==1)  /* draw rectangle */
  draw_rect(win, gc, xbox, ybox, x1box, y1box);

else if (geom[3]==1)  /* draw filled rectangle */
  draw_frect(win, gc, xbox, ybox, x1box, y1box);

else if (geom[4]==1)  /* draw circle */
  draw_circle(win, gc);

else if (geom[5]==1)  /* draw filled circle */
  draw_fcircle(win, gc);
}

draw_line(win, gc, x, y, x1, y1)
Window win;
GC gc;
int x, y, x1, y1;
{
int dist, ii, tempx, tmp;
printf("entering draw_line\n");

if ((x==x1)&&(y==y1))  /* same point */
     draw_point(x1, y1);

else if ((x==x1)||(y==y1)){   /* in same axis v or h*/

  if (y==y1) {
    dist=x1-x;
    dist=abs(dist);
    if (x<x1)
      tmp=x;
    else
      tmp=x1;
       for(ii=0; ii<dist+1; ii++)
	 draw_point(ii+tmp, y);
   }

  else if (x==x1) {
    dist=y1-y;
    dist=abs(dist);
    if (y<y1)
      tmp=y;
    else
      tmp=y1;
       for(ii=0; ii<dist+1; ii++)
	 draw_point(x, ii+tmp);
  }
}
}


draw_rect(win, gc, x, y, x1, y1)
Window win;
GC gc;
int x, y, x1, y1;
{
draw_line(win, gc, x, y, x1, y);
draw_line(win, gc, x, y, x, y1);
draw_line(win, gc, x, y1, x1, y1);
draw_line(win, gc, x1, y1, x1, y);

}

 
 

draw_frect(win, gc, x, y, x1, y1)
Window win;
GC gc;
int x, y, x1, y1;
{
int xmin, xmax, ymin, ymax;
printf("entering draw_frect\n");
/* draw outline */
draw_rect(win, gc, x, y, x1, y1);
/* fill her in */

xmin=min(x, x1);
ymin=min(y, y1);
xmax=max(x, x1);
ymax=max(y, y1);

 while(ymax>=ymin) {
   draw_rect(win, gc, xmin, ymin, xmax, ymax);
   ymin++;
   ymax--;
 }
}

int min(x, y)
int x, y;
{
if (x<y)
  return x;
else
  return y;
}


int max(x, y)
int x, y;
{
if (x>y)
  return x;
else
  return y;
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

 for(ii=0; ii<gsize; ii++) {
   for(jj=0; jj<gsize; jj++) {
     grid[ii][jj].On=False;
     grid[ii][jj].pixel=0;
   }
 }
}

init_lookup()
{
int ii, jj, count;
count=0;

  for(ii=0; ii<16; ii++) {
    for(jj=0; jj<8; jj++) {
      lookup[ii][jj]=count++;
    }
  }
}
      

draw_point(xbox, ybox)
int xbox, ybox;
{
grid[ybox][xbox].On=True;
grid[ybox][xbox].pixel=cur_pixel;
}

Bool pointOn()
{
if (geom[0]==1)
  return True;
else
  return False;
}


draw_pixmap(win, gc)
Window win;
GC gc;
{
int ii, jj;

 for(ii=0; ii<gsize; ii++){
   for(jj=0; jj<gsize; jj++){
     if (grid[ii][jj].On==True){
       XSetForeground(display, gc, grid[ii][jj].pixel);       
       XFillRectangle(display, win, gc, 130+jj, 40+ii, 1, 1);
     }
   }
 }
 XSetForeground(display, gc, BlackPixel(display, screen));
}

fill_col_array(win, gc)
Window win;
GC gc;
{
short rop, gop, bop; /* 1 is add 2 is subtract */
int ii, jj, rinc, ginc, binc, count; 
unsigned short rmin, gmin, bmin;
int div=22; 
static char* name[]= {"red", "orange", "yellow", "green", "blue", "violet", "purple"};
rop=gop=bop=0;
count=2; 

col[0]=BlackPixel(display,screen);
XAllocNamedColor(display, DefaultColormap(display, screen), "gray", &color, &rgb_db_def);
col[1]=color.pixel;

 for(jj=0; jj<6; jj++){
  XAllocNamedColor(display, DefaultColormap(display, screen), name[jj], &color, &rgb_db_def);
  XAllocNamedColor(display, DefaultColormap(display, screen), name[jj+1], &color2, &rgb_db_def);
  /* printf("%s is: Red=%d, Green=%d, Blue=%d\n", name[jj], color.red, color.green, color.blue);
  printf("%s is: Red=%d, Green=%d, Blue=%d\n", name[jj+1],color2.red, color2.green, color2.blue); */

  if(color.red>color2.red)
    rop=2;
  else
    rop=1;

  if(color.green>color2.green)
    gop=2;
  else
    gop=1;

  if(color.blue>color2.blue)
    bop=2;
  else
    bop=1;
  
  if(jj==5)
    div=29;

  rinc=(color.red-color2.red)/div;
  ginc=(color.green-color2.green)/div;
  binc=(color.blue-color2.blue)/div;
  rinc=abs(rinc);
  ginc=abs(ginc);
  binc=abs(binc);
  /* printf("rinc=%d, ginc=%d, binc=%d\n", rinc, ginc, binc); */

  for(ii=0; ii<21; ii++){
    if(rop==1)
      color.red+=(rinc);
    else
      color.red-=(rinc);
    
    if(gop==1)
      color.green+=(ginc);
    else
      color.green-=(ginc);

    if(bop==1)
      color.blue+=(binc);
    else
      color.blue-=(binc);

   XAllocColor(display, DefaultColormap(display, screen), &color);   
   /* XSetForeground(display, gc3, color.pixel); 
   XFillRectangle(display, win, gc3, 5+(ii*5), 500+(jj*5), 5, 5);
   XFlush(display); */
   col[count++]=color.pixel;
  }
 }
}


quit()
{
exit(1);
}


save()
{
int ii, jj;
file=fopen("bitdata", "w");
 for(ii=0; ii<gsize; ii++) {
   for(jj=0; jj<gsize; jj++) {
     fprintf(file, "%d\n%u\n", grid[ii][jj].On, grid[ii][jj].pixel);
   }
 }
 fclose(file);
}


restore()
{
int ii, jj;
int tempOn;
unsigned int temppixel;
file=fopen("bitdata", "r");
 for(ii=0; ii<gsize; ii++) {
   for(jj=0; jj<gsize; jj++) {
     fscanf(file, "%d", &grid[ii][jj].On);
     fscanf(file, "%u", &grid[ii][jj].pixel);
   }
 }
 fclose(file);
}
