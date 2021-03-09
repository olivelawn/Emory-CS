#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <math.h>


#define offset 130
#define gsize 40
#define MAXCOLORS 256 
/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

struct {
  unsigned long pixel;
  Bool On;
	} grid[40][40];

int geom[6];
FILE *file;
unsigned long col[128]; 
unsigned long cur_pixel=1;
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
Colormap colormap, cmap;

void main(argc, argv)
int argc;
char **argv;
{
	Window win, root;
	Screen *scr_ptr;
	Visual *default_visual;
	int default_depth, class;
	XVisualInfo vinfo_return;
	XColor colors[MAXCOLORS];
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
	int ycoord, xcoord, ucoord, vcoord, wait, ind, ii;
	Status status;
	unsigned long pixels[MAXCOLORS];
	Bool fall = False; Bool redraw_grid=True;


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
	scr_ptr = DefaultScreenOfDisplay(display);
	root = DefaultRootWindow(display);
	default_visual = DefaultVisual(display, screen);
	default_depth = DefaultDepth(display, screen);
	colormap=DefaultColormap(display, screen);

       	if(default_visual->class==4){
	  printf("default is TrueColor, class 4\n");
	  colormap=DefaultColormap(display, screen);
	  class=4;
	}
	else if(default_visual->class==3){
	  printf("default visual is PseudoColor, class 3\n");
	  class=3;
	}
	else 
	  printf("Didn't find a default depth, trying anyway\n");

	
	if (class==3){    
	for(ii=0; ii<MAXCOLORS; ii++){
	  colors[ii].pixel = ii;
	  colors[ii].flags = DoRed | DoGreen | DoBlue;
	}
	
	  XQueryColors(display, DefaultColormapOfScreen(scr_ptr), colors,MAXCOLORS);
	
	  
	  colormap = XCreateColormap(display,root,default_visual,AllocNone);
	  status=XAllocColorCells(display,colormap,False,NULL,0,pixels,128);
	  if (status==0) {
	    fprintf(stderr, "Can't allocate cells for existing colors\n");
	    exit(1);
	  }
	  for(ii=0; ii<128; ii++)
	    XStoreColor(display,colormap, colors[ii]);
	}


	/* size window */
	width = (3.5*display_width)/7, height = (4.4*display_height)/6;

	while ((width%2)!=0) { width++; }
	while ((height%2)!=0) { height++; }
	  
	printf("width=%d height=%d\n",width,height);



	/* create opaque window */
	win = XCreateSimpleWindow(display, RootWindow(display,screen), x, y, width, height, border_width, BlackPixel(display,screen), WhitePixel(display,screen));
	XSetWindowColormap(display, win, colormap);

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

			if (hit_clear(xcoord, ycoord)==1){  /* hit clear button? */
			  clear_routine();
			  redraw_grid=True;
			}
			if ((ind=hit_geom(xcoord, ycoord))!=-99)  /* hit geom button? */
			  set_geom(ind);

			if (hit_color(xcoord, ycoord))  /* hit color grid? */
			  set_color(xcoord, ycoord, win, gc);

			if (hit_save(xcoord, ycoord))
			  save();

			if (hit_restore(xcoord, ycoord)){
			  restore();
			  redraw_grid=True;
			}
			if (hit_quit(xcoord, ycoord))
			  quit();
			
			
			if (hit_grid(xcoord, ycoord)) {   /* hit bitmap grid? */
			  x1box=((xcoord-offset)/(awidth/40));
			  y1box=((ycoord-offset)/(awidth/40));
			  xbox=((ucoord-offset)/(awidth/40));
			  ybox=((vcoord-offset)/(awidth/40));
			  printf("xbox=%d, ybox=%d\n", xbox, ybox);
			}


			if ((pointOn())&&(hit_grid(xcoord, ycoord))){  
			  draw_point(win, gc, gc2,x1box, y1box);
			  redraw_grid=True;
			}
			
			else if ((hit_grid(xcoord, ycoord))&&(wait==1)) {
			  draw_2pt(win, gc, gc2, ucoord, vcoord, xcoord, ycoord);
			  wait=0;
			  redraw_grid=True;
			}

			else if ((hit_grid(xcoord, ycoord))&&(wait==0)) {
			  ucoord=xcoord;
			  vcoord=ycoord;
			  wait=1;
			}

			fall=True;
			
                case Expose:
		  
			if(fall==False)
			  draw_left_plane(win, gc);
			if((fall==False)||(redraw_grid==True)){
			XClearArea(display, win, 129, 30, (width-129), (height-129), False);
			draw_right_plane(win, gc, gc2);
		      	draw_pixmap(win, gc);
			}
			draw_sel_color(win, gc);
			fall=False;
			redraw_grid=False;
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

  if ((xcoord>offset)&&(xcoord<(offset+awidth))&&(ycoord>offset)&&(ycoord<(offset+awidth)))
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

 /* XSetForeground(display, gc3, cur_pixel);
 XDrawRectangle(display,win,gc, 5, 190, 50, 40);
 XFillRectangle(display,win,gc3, 5, 190, 50, 40);
 XFlush(display); */

  for(ii=0; ii<16; ii++) {
   for(jj=0; jj<8; jj++) {
     XSetForeground(display, gc3, col[count++]);  
     XDrawRectangle(display, win, gc, 5+(jj*8), 250+(ii*8), 8, 8);
     XFillRectangle(display, win, gc3, 5+(jj*8), 250+(ii*8), 8, 8);
      /* XFlush(display); */
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
box_size=awidth/40;
xstart=offset;
ystart=offset;

 for(ii=0; ii<40; ii++){
   for(jj=0; jj<40; jj++) {
     XDrawRectangle(display,win,gc,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     if (grid[ii][jj].On==True) {  /* draw the current color */
       XSetForeground(display, gc4, grid[ii][jj].pixel); 
       XFillRectangle(display,win,gc4,(jj*box_size)+xstart,(ii*box_size)+ystart,box_size,box_size); 
     }
     /* XFlush(display); */
   }
 }
}


draw_2pt(win, gc, gc2)
Window win;
GC gc, gc2;
{
if (geom[1]==1)  /* draw line */
  draw_line(win, gc, gc2, xbox, ybox, x1box, y1box);

else if (geom[2]==1)  /* draw rectangle */
  draw_rect(win, gc, gc2, xbox, ybox, x1box, y1box);

else if (geom[3]==1)  /* draw filled rectangle */
  draw_frect(win, gc, gc2, xbox, ybox, x1box, y1box);

else if (geom[4]==1)  /* draw circle */
  draw_circle(win, gc, gc2, xbox, ybox, x1box, y1box);

else if (geom[5]==1)  /* draw filled circle */
  draw_fcircle(win, gc, gc2, xbox, ybox, x1box, y1box);
}


draw_line(win, gc, gc2, x, y, x1, y1)
Window win;
GC gc, gc2;
int x, y, x1, y1;
{
int xmin, xmax, ymin, ymax;
int ytmp, tmp, tmp1, tmp2;
float xf, x1f, yf, y1f, slope;
int counter=0;
float tmp_slope=(1/2); 
printf("entering draw_line\n");

xf=x;
yf=y;
x1f=x1;
y1f=y1;
slope=(yf-y1f)/(xf-x1f);

xmin=min(x, x1);
ymin=min(y, y1);
xmax=max(x, x1);
ymax=max(y, y1);

draw_point(win, gc, gc2,x, y);
draw_point(win, gc, gc2,x1, y1);

tmp=xmax;
ytmp=ymin;

 if((x-x1)==0) {
   while(xmin<=xmax && ymin<=ymax)
     draw_point(win, gc, gc2,xmin, ymin++);
 }
 else if(ymin==ymax) {
   while(xmin<=xmax && ymin<=ymax)
     draw_point(win, gc, gc2, xmin++, ymin);
 }
 else if(slope>1) {
   tmp=ymax;
   tmp1=xmax;
   while(tmp1>=xmin && tmp>=ymin) {
     tmp2=tmp_slope;
     if(tmp2>counter) {
       tmp1--;
       counter++;
     }
     tmp_slope=tmp_slope+(1/slope);
     draw_point(win, gc, gc2,tmp1, tmp);
     tmp--;
    }
 }
 else if(slope>=-1 && slope<0) {
   tmp=xmin;
   tmp1=ymax;
   while(tmp1>=ymin && tmp<=xmax) {
     tmp2=tmp_slope;
     if(tmp2>counter) {
       tmp1--;
       counter++;
     }
     tmp_slope=tmp_slope-slope;
     draw_point(win, gc, gc2,tmp, tmp1);
     tmp++;
    }
 }
 else if(slope<=1 && slope>0) {
   tmp=xmax;
   tmp1=ymax;
   while(tmp1>=ymin && tmp>=xmin) {
     tmp2=tmp_slope;
     if(tmp2>counter) {
       tmp1--;
       counter++;
     }
     tmp_slope=tmp_slope+slope;
     draw_point(win, gc, gc2,tmp, tmp1);
     tmp--;
    }
 }
 else if(slope<-1) {
   tmp=ymin;
   tmp1=xmax;
   while(tmp1>=xmin && tmp<=ymax) {
     tmp2=tmp_slope;
     if(tmp2>counter) {
       tmp1--;
       counter++;
     }
     tmp_slope=tmp_slope-(1/slope);
     draw_point(win, gc, gc2,tmp1, tmp);
     tmp++;
    }
 }
}
     

draw_rect(win, gc, gc2, x, y, x1, y1)
Window win;
GC gc, gc2;
int x, y, x1, y1;
{
draw_line(win, gc, gc2, x, y, x1, y);
draw_line(win, gc, gc2, x, y, x, y1);
draw_line(win, gc, gc2, x, y1, x1, y1);
draw_line(win, gc, gc2, x1, y1, x1, y);
}
 

draw_frect(win, gc, gc2, x, y, x1, y1)
Window win;
GC gc, gc2;
int x, y, x1, y1;
{
int xmin, xmax, ymin, ymax;
printf("entering draw_frect\n");
/* draw outline */
draw_rect(win, gc, gc2, x, y, x1, y1);
/* fill her in */

xmin=min(x, x1);
ymin=min(y, y1);
xmax=max(x, x1);
ymax=max(y, y1);

 while(ymax>=ymin) {
   draw_rect(win, gc, gc2, xmin, ymin, xmax, ymax);
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

draw_circle(win, gc, gc2, x, y, x1, y1)
Window win;
GC gc, gc2;
int x, y, x1, y1;
{
double rad, sine, cosine, theta;
int tmpx, tmpy, ii;
printf("entering draw_circle\n");

 if((x==x1)||(y==y1)){
   if(x==x1)
     ii=abs(y1-y);
   if(y==y1)
     ii=abs(x1-x);

   for(theta=0; theta<=90; theta++){
     rad=(3.14*theta)/180;
     sine=sin(rad);
     cosine=cos(rad);
     tmpx=ii*cosine;
     tmpy=ii*sine;
     draw_point(win, gc, gc2, tmpx+x, y-tmpy);
     draw_point(win, gc, gc2, x-tmpx, y-tmpy);
     draw_point(win, gc, gc2, tmpx+x, tmpy+y);
     draw_point(win, gc, gc2, x-tmpx, tmpy+y);
   }
   draw_point(win, gc, gc2, x, y+ii);
   draw_point(win, gc, gc2, x, y-ii);
   draw_point(win, gc, gc2, x+ii, y);
   draw_point(win, gc, gc2, x-ii, y);
 }
}

draw_fcircle(win, gc, gc2, x, y, x1, y1)
Window win;
GC gc, gc2;
int x, y, x1, y1;
{
double rad, sine, cosine, theta;
int tmpx, tmpy, ii;
printf("entering draw_circle\n");

 if((x==x1)||(y==y1)){
   if(x==x1)
     ii=abs(y1-y);
   if(y==y1)
     ii=abs(x1-x);

   for(theta=0; theta<=90; theta++){
     rad=(3.14*theta)/180;
     sine=sin(rad);
     cosine=cos(rad);
     tmpx=ii*cosine;
     tmpy=ii*sine;
     draw_line(win, gc, gc2, tmpx+x, y-tmpy, x-tmpx, y-tmpy);
     draw_line(win, gc, gc2, tmpx+x, y+tmpy, x-tmpx, y+tmpy);
   }
   draw_point(win, gc, gc2, x, y+ii);
   draw_point(win, gc, gc2, x, y-ii);
   draw_point(win, gc, gc2, x+ii, y);
   draw_point(win, gc, gc2, x-ii, y);
 }
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
	/* XFlush(display); */

} 


init_grid()
{
int ii, jj;

 for(ii=0; ii<40; ii++) {
   for(jj=0; jj<40; jj++) {
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
      

draw_point(win, gc, gc2, xbox, ybox)
Window win;
GC gc, gc2;
int xbox, ybox;
{
  if((xbox>=0)&&(xbox<=(gsize-1))&&(ybox>=0)&&(xbox<=(gsize-1))) {
    /* printf("x=%d, y=%d\n", xbox,ybox); */
    grid[ybox][xbox].On=True;
    grid[ybox][xbox].pixel=cur_pixel;
    /* draw_right_plane(win, gc, gc2); */
  }
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

 for(ii=0; ii<40; ii++){
   for(jj=0; jj<40; jj++){
     if (grid[ii][jj].On==True){
       XSetForeground(display, gc, grid[ii][jj].pixel);       
       XFillRectangle(display, win, gc, offset+jj, 40+ii, 1, 1);
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
XAllocNamedColor(display, colormap, "gray", &color, &rgb_db_def);
col[1]=color.pixel;

 for(jj=0; jj<6; jj++){
  XAllocNamedColor(display, colormap, name[jj], &color, &rgb_db_def);
  XAllocNamedColor(display, colormap, name[jj+1], &color2, &rgb_db_def);
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
  printf("rinc=%d, ginc=%d, binc=%d\n", rinc, ginc, binc);

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

   XAllocColor(display, colormap, &color);   
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
 for(ii=0; ii<40; ii++) {
   for(jj=0; jj<40; jj++) {
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
 for(ii=0; ii<40; ii++) {
   for(jj=0; jj<40; jj++) {
     fscanf(file, "%d", &grid[ii][jj].On);
     fscanf(file, "%u", &grid[ii][jj].pixel);
   }
 }
 fclose(file);
}


draw_sel_color(win,gc)
Window win;
GC gc;
{
XSetForeground(display, gc3, cur_pixel);
XDrawRectangle(display,win,gc, 5, 190, 50, 40);
XFillRectangle(display,win,gc3, 5, 190, 50, 40);
/* XFlush(display); */
}
