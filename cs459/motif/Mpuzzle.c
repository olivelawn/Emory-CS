/* Window Puzzle: Talk to Window Manager
     
*/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define width 232
#define height 310

#define b_width 58
#define b_height 67

/* Declarations of callback functions */

void QuitCallback ( Widget w, XtPointer clientData, XtPointer callData );
void ResetCallback ( Widget w, XtPointer clientData, XtPointer callData );
void TileCallback ( Widget w, XtPointer clientData, XtPointer callData );


/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

	struct {
	  Widget Wid;
	  int x;
	  int y;
	} tile[4][4];


int xempty, yempty, dist, dirv;
Widget shell, msg, bb, quit, reset;
Widget Widg[15];

XTextProperty windowName, iconName;
Pixmap pmap;
XWMHints wmhints;

void main(argc, argv)
int argc;
char **argv;
{
  XtAppContext app;
  XmString xmstr;
  GC gc,gc1,gc2;
  int count;

    /* register_win(width, height, 1, 0); */

    /* gc=XCreateGC(display,win,0,NULL);
       XSetForeground(display, gc, BlackPixel(display,screen)); 
       XSetBackground(display, gc, WhitePixel(display,screen));  */

  shell = XtAppInitialize ( &app, "puzzle", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

     instantiate_bb_quit_reset();
     instantiate_tiles();
     register_callbacks();
     /* initialize_index();
	

     init_set_up(win);
     draw_text(win, gc, width, height); */

}



instantiate_bb_quit_reset()
{
  bb = XtVaCreateManagedWidget ( "bboard", xmBulletinBoardWidgetClass,
				 shell,
				 XmNmarginWidth, 0,
				 XmNmarginHeight, 0,
				 XmNwidth, width,
				 XmNheight, height,
				 NULL );
 
  quit = XtVaCreateManagedWidget ( "quit", xmPushButtonWidgetClass, bb, 
                                   XmNx, 10,
	                           XmNy, 10,
                                   NULL );


    reset = XtVaCreateManagedWidget ( "reset", xmPushButtonWidgetClass, bb, 
                                   XmNx, 180,
	                           XmNy, 10,
                                   NULL );
}

instantiate_tiles()
{
int ii;

  for(ii=0; ii<15; ii++){
    Widg[ii] = XtVaCreateManagedWidget ( "1", xmPushButtonWidgetClass, bb, 
                                   XmNx, 0,
	                           XmNy, 40,
				   XmNwidth, b_width,
				   XmNheight, b_height,
                                   NULL );
  }
}

register_callbacks()
{
int ii;

    XtAddCallback ( quit, XmNactivateCallback, 
                    QuitCallback, NULL );

    XtAddCallback ( reset, XmNactivateCallback, 
                    ResetCallback, NULL );

    for(ii=0; ii<15; ii++){
      XtAddCallback (Widg[ii], XmNactivateCallback, 
                    TileCallback, NULL);
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

   /* tile[ydst-ii][xdst].index=tile[ydst-(ii+1)][xdst].index; */
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
int count=0;
/* Initialize data structure */

  for (ii=0; ii<4; ii++){
    for (jj=0; jj<4; jj++){

      tile[ii][jj].Wid=Widg[count++];
      count++;
    }
  }
tile[3][3].Wid=NULL;  
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
