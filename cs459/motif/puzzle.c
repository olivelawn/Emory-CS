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
#include <math.h>

#define width 232
#define height 310
#define sleep 1

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
	  Bool empty;
	} tile[4][4];

        typedef struct ugly {
        Widget W;
        int count;
               }ug;
  


int xempty, yempty;
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

  shell = XtAppInitialize ( &app, "puzzle", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

     instantiate_bb_quit_reset();
     instantiate_tiles();
     register_callbacks();    
     XtRealizeWidget ( shell );
     XtAppMainLoop ( app );
         

     /* init_set_up(win);
     draw_text(win, gc, width, height); */

}



instantiate_bb_quit_reset()
{
  bb = XtVaCreateManagedWidget ( "bboard", xmBulletinBoardWidgetClass,
				 shell,
				 XmNnoResize, True,
				 XmNresizePolicy, XmRESIZE_NONE,
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
int ii,jj, count;
Bool logic=True;
 char *num[] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};
		
count=0;
  for(ii=0; ii<4; ii++){
    for(jj=0; jj<4; jj++){
      if((ii==3)&&(jj==3))
	logic=False;
	
	  if(logic){
	    tile[ii][jj].Wid = XtVaCreateManagedWidget(num[count], 
                                   xmPushButtonWidgetClass, bb, 
                                   XmNx, b_width*jj,
	                           XmNy, b_height*ii+40,
				   XmNwidth, b_width,
				   XmNheight, b_height,
                                   NULL );
    count++;
	  }
    }
  }
    tile[3][3].Wid=NULL;
    tile[3][3].empty=True;
    xempty=3;
    yempty=3;
}


register_callbacks()
{
int ii, jj;
Bool logic=True;

    XtAddCallback ( quit, XmNactivateCallback, 
                    QuitCallback, NULL );

    XtAddCallback ( reset, XmNactivateCallback, 
                    ResetCallback, NULL );

    for(ii=0; ii<4; ii++){
      for(jj=0; jj<4; jj++){
	if((ii==3)&&(jj==3))
	  logic=False;
	
	if(logic){
	  XtAddCallback (tile[ii][jj].Wid, XmNactivateCallback, 
                    TileCallback, NULL);
	}
      }
    }
}
		     
void QuitCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
    printf("hit the quit button\n");
    exit(1);
}

void ResetCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
int ii, jj;
     printf("hit reset button\n");

     for(ii=0; ii<4; ii++) {
       for(jj=0; jj<4; jj++) {
	 if(tile[ii][jj].empty!=True){
	 XtDestroyWidget(tile[ii][jj].Wid);
	 }
       }
     }
     
}

void TileCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
Dimension x, y;
int xbox, ybox, dist, dirv;
Bool hit=False;

     printf("hit tile button\n");
     XtVaGetValues(w,
		   XmNx, &x,
		   XmNy, &y,
		   NULL);
     printf("xcoord=%d, ycoord=%d\n", x, y);

     xbox=x/b_width;
     ybox=(y-40)/b_height;
     printf("xbox=%d, ybox=%d\n", xbox, ybox);

     if((xbox==xempty)||(ybox==yempty)){
       hit=True;
       if(xempty==xbox)
	 { dist=yempty-ybox; dirv=1; }
       else
	 { dist=xempty-xbox; dirv=0; }
     }

     if(!hit)
       printf("click not in v or h axis\n");
     
     if(hit)
       recompute_structure(w, xbox, ybox, dist, dirv);
     
}


recompute_structure(w, xbox, ybox, dist, dirv)
Widget w;
int xbox, ybox, dist, dirv;
{
int xdst, ydst;
xdst=xempty;
ydst=yempty;
xempty=xbox;
yempty=ybox;


animate_tile(w, xbox, ybox, xdst, ydst, dist, dirv);
/* copy_struct(w, xbox, ybox, xdst, ydst, dist, dirv); */

}


copy_struct(w, xbox, ybox, xdst, ydst, dist, dirv)
Widget w;
int xbox, ybox, xdst, ydst, dist, dirv;
{
int ii;

 if((dist>0)&&(dirv==1)) {      /* tile above */
   dist=abs(dist);
   for(ii=0; ii<dist; ii++){
     tile[ydst-ii][xdst].Wid=tile[ydst-(ii+1)][xdst].Wid;
     tile[ydst-ii][xdst].empty=tile[ydst-(ii+1)][xdst].empty;
   }
 }

 if((dist<0)&&(dirv==1)) {	/* tile below */
  dist=abs(dist);
  for (ii=0; ii<dist; ii++){
     tile[ydst+ii][xdst].Wid=tile[ydst+(ii+1)][xdst].Wid;
     tile[ydst+ii][xdst].empty=tile[ydst+(ii+1)][xdst].empty;
  }
}

 if((dist>0)&&(dirv==0)) {       /* tile left */
   dist=abs(dist);
   for (ii=0; ii<dist; ii++){
     tile[ydst][xdst-ii].Wid=tile[ydst][xdst-(ii+1)].Wid;
     tile[ydst][xdst-ii].empty=tile[ydst][xdst-(ii+1)].empty;
   }
 }

 if((dist<0)&&(dirv==0)){	/* tile right */
   dist=abs(dist);
   for (ii=0; ii<dist; ii++){
     tile[ydst][xdst+ii].Wid=tile[ydst][xdst+(ii+1)].Wid;
     tile[ydst][xdst+ii].empty=tile[ydst][xdst+(ii+1)].empty;
   }
 }
  
tile[ybox][xbox].Wid=NULL;
tile[ybox][xbox].empty=True;
  
}


animate_tile(w, xbox, ybox, xdst, ydst, dist, dirv)
Widget w;
int xbox, ybox, xdst, ydst, dist, dirv;
{
Dimension x, y;
Widget widget;

ug *ugptr;
int ii;
int jj=1;
 
 if ((dist>0)&&(dirv==1)){       /* tile above */
   while (jj<=dist) {
     ugptr->W = tile[ydst-jj][xdst].Wid;
     ugptr->count = 0;
     move_down( (XtPointer) ugptr);
     jj++;
       }
 }


 if ((dist<0)&&(dirv==1)){     /* tile below */
   dist=abs(dist);
   while (jj<=dist){
     move_up( (XtPointer) tile[ydst+jj][xdst].Wid);
     jj++;
   }
 }
  

 if ((dist>0)&&(dirv==0)){     /* tile left */
   while (jj<=dist){
     XtVaGetValues(tile[ydst][xdst-jj].Wid, XmNx, &x, XmNy, &y, NULL);
     XtVaSetValues(tile[ydst][xdst-jj].Wid, XmNx, x+b_width, XmNy, y, NULL);
     jj++;
   }
 }

  
 if ((dist<0)&&(dirv==0)){     /* tile right */	
   dist=abs(dist);
   while (jj<=dist){
     XtVaGetValues(tile[ydst][xdst+jj].Wid, XmNx, &x, XmNy, &y, NULL);
     XtVaSetValues(tile[ydst][xdst+jj].Wid, XmNx, x-b_width, XmNy, y, NULL);
     jj++;
   }
 }
 copy_struct(w, xbox, ybox, xdst, ydst, dist, dirv);
}


move_down(XtPointer clientData)
{
ug *Data = (ug *) clientData;
Widget w = Data->W;
int count = Data->count;
Dimension x, y;

if(count<b_height) {
   XtVaGetValues(w, XmNx, &x, XmNy, &y, NULL);
   XtVaSetValues(w, XmNx, x, XmNy, y+1, NULL);
   count++;
   printf("x=%d, y=%d, counter=%d\n", x, y, count );
   Data->W=w;
   Data->count=count;
   
   XtAppAddTimeOut ( XtWidgetToApplicationContext ( w ),   
                 sleep, move_down, (XtPointer) Data );
  }
 else
   return;
}

move_up(XtPointer clientData, XtPointer counter)
{
Widget w = ( Widget ) clientData;
int count = ( int ) counter;
Dimension x, y;

if(count<b_height) {
   XtVaGetValues(w, XmNx, &x, XmNy, &y, NULL);   
   XtVaSetValues(w, XmNx, x, XmNy, y-1, NULL);
   count++;
   XtAppAddTimeOut ( XtWidgetToApplicationContext ( w ),   
                  sleep, move_up, ( XtPointer ) w, ( XtPointer ) count );
  }

}
   
 
