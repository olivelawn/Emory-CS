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

#define b_width 58
#define b_height 67

#define sleep 10

/* Declarations of callback functions */

void QuitCallback ( Widget w, XtPointer clientData, XtPointer callData );
void ResetCallback ( Widget w, XtPointer clientData, XtPointer callData );
void ButtonPressCallback ( Widget w, XtPointer clientData, XtPointer callData );
void Move_Tiles(void);



/* These are used as arguments to nearly every Xlib routine, so it saves 
 * routine arguments to declare them global.  If there were 
 * additional source files, they would be declared extern there. */

	struct{
	  Widget Wid;
	  int index;
	  int x;
	  int y;
	  int counter;
	}tile[4][4];

Widget GlobWidget[3];
Widget tilecopy[16];
int xempty, yempty;
int xbox, ybox, dist, dirv, xdst, ydst;
Widget shell, msg, bb, quit, reset;
Widget Widg[15];
int counter;
XtAppContext app;
Bool AcceptButtonPress = True;

void main(argc, argv)
int argc;
char **argv;
{
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

	    tilecopy[count]=tile[ii][jj].Wid;
	    tile[ii][jj].x =  b_width*jj;
	    tile[ii][jj].y =  b_height*ii+40;
	    count++;
	    tile[ii][jj].index = count;

	  }
    }
  }
    tile[3][3].Wid=NULL;
    tile[3][3].index=-1;
    tile[3][3].x=174;
    tile[3][3].y=241;
    tile[3][3].counter=-1;
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
                    ButtonPressCallback, NULL);
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
int count = 0;
Bool logic=True;

printf("hit reset button\n");

 for(ii=0; ii<4; ii++) {
   for(jj=0; jj<4; jj++) {
     if((ii==3)&&(jj==3))
	logic=False;
     
     if(logic) { 
     tile[ii][jj].Wid=tilecopy[count++];
     tile[ii][jj].index = count;
     tile[ii][jj].counter=0;
     XtVaSetValues(tile[ii][jj].Wid, XmNx, tile[ii][jj].x, XmNy, tile[ii][jj].y, NULL);
     }
   }
 }
 tile[3][3].Wid=NULL;
 tile[3][3].index=-1;	   
 tile[3][3].counter=-1;
 xempty=3;
 yempty=3;
}

void ButtonPressCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
Dimension x, y;
Bool hit=False;
int distance;

 if(AcceptButtonPress){
     AcceptButtonPress=False;
     printf("hit tile button\n");
     XtVaGetValues(w, XmNx, &x, XmNy, &y, NULL);
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

         
     if(hit){
       printf("got to hit\n");
       xdst=xempty;
       ydst=yempty;
       xempty=xbox;
       yempty=ybox;

       distance=dist;

       fill_GlobWidget_array(distance);
       copy_struct(distance);
       
       XtAppAddTimeOut( app, sleep, Move_Tiles, NULL );
       
       
     }

      else{
       printf("click not in v or h axis\n");
       AcceptButtonPress = True;
      }
 }
 else
   printf("Please Wait\n");

}


copy_struct(distance)
int distance;
{
int ii;

 if((distance>0)&&(dirv==1)) {      /* tile above */
   distance=abs(distance);
   for(ii=0; ii<distance; ii++){
     tile[ydst-ii][xdst].Wid=tile[ydst-(ii+1)][xdst].Wid;
     tile[ydst-ii][xdst].index=tile[ydst-(ii+1)][xdst].index;
     tile[ydst-ii][xdst].counter=tile[ydst-(ii+1)][xdst].counter;
   }
 }

 if((distance<0)&&(dirv==1)) {	/* tile below */
  distance=abs(distance);
  for (ii=0; ii<distance; ii++){
     tile[ydst+ii][xdst].Wid=tile[ydst+(ii+1)][xdst].Wid;
     tile[ydst+ii][xdst].index=tile[ydst+(ii+1)][xdst].index;
     tile[ydst+ii][xdst].counter=tile[ydst+(ii+1)][xdst].counter;
  }
}

 if((distance>0)&&(dirv==0)) {       /* tile left */
   distance=abs(distance);
   for (ii=0; ii<distance; ii++){
     tile[ydst][xdst-ii].Wid=tile[ydst][xdst-(ii+1)].Wid;
     tile[ydst][xdst-ii].index=tile[ydst][xdst-(ii+1)].index;
     tile[ydst][xdst-ii].counter=tile[ydst][xdst-(ii+1)].counter;
   }
 }

 if((distance<0)&&(dirv==0)){	/* tile right */
   distance=abs(distance);
   for (ii=0; ii<distance; ii++){
     tile[ydst][xdst+ii].Wid=tile[ydst][xdst+(ii+1)].Wid;
     tile[ydst][xdst+ii].index=tile[ydst][xdst+(ii+1)].index;
     tile[ydst][xdst+ii].counter=tile[ydst][xdst+(ii+1)].counter;
   }
 }
  
tile[ybox][xbox].Wid=NULL;
tile[ybox][xbox].index=-1;
tile[ybox][xbox].counter=-1;
  
}


fill_GlobWidget_array(distance)
int distance;
{
int ii;
int count = 0;

 if((distance>0)&&(dirv==1)) {      /* tile above */
   distance=abs(distance);
   for(ii=0; ii<distance; ii++){
     GlobWidget[count++]=tile[ydst-(ii+1)][xdst].Wid;
    
   }
 }

 if((distance<0)&&(dirv==1)) {	/* tile below */
  distance=abs(distance);
  for (ii=0; ii<distance; ii++){
     GlobWidget[count++]=tile[ydst+(ii+1)][xdst].Wid;
    
  }
}

 if((distance>0)&&(dirv==0)) {       /* tile left */
   distance=abs(distance);
   for (ii=0; ii<distance; ii++){
     GlobWidget[count++]=tile[ydst][xdst-(ii+1)].Wid;
   }
 }

 if((distance<0)&&(dirv==0)){	/* tile right */
   distance=abs(distance);
   for (ii=0; ii<distance; ii++){
     GlobWidget[count++]=tile[ydst][xdst+(ii+1)].Wid;
   }
 }

}


int get_looptimes()
{
if(dirv==1)
  return(b_height);
else
  return(b_width);
}


void Move_Tiles()
{
int looptimes, ii;
int distance;
Dimension x, y;

distance=dist;

looptimes=get_looptimes();

 if (counter<looptimes){
   
   if((distance>0)&&(dirv==1)) {      /* tile above, move down */
     distance=abs(distance);
     for(ii=0; ii<distance; ii++){
     XtVaGetValues(GlobWidget[ii], XmNx, &x, XmNy, &y, NULL);
     XtVaSetValues(GlobWidget[ii], XmNx, x, XmNy, (y+1), NULL);
    
     }
   }

   
   if((distance<0)&&(dirv==1)) {	/* tile below, move up */
     distance=abs(distance);
     for (ii=0; ii<distance; ii++){
     XtVaGetValues(GlobWidget[ii], XmNx, &x, XmNy, &y, NULL);
     XtVaSetValues(GlobWidget[ii], XmNx, x, XmNy, (y-1), NULL);

     }
   }

   if((distance>0)&&(dirv==0)) {       /* tile left, move right */
     distance=abs(distance);
     for (ii=0; ii<distance; ii++){
     XtVaGetValues(GlobWidget[ii], XmNx, &x, XmNy, &y, NULL);
     XtVaSetValues(GlobWidget[ii], XmNx, (x+1), XmNy, y, NULL);

     }
   }

   if((distance<0)&&(dirv==0)){	        /* tile right, move left */
     distance=abs(distance);
     for (ii=0; ii<distance; ii++){
      XtVaGetValues(GlobWidget[ii], XmNx, &x, XmNy, &y, NULL);
      XtVaSetValues(GlobWidget[ii], XmNx, (x-1), XmNy, y, NULL);

     }
   }
   
   counter++;
   XtAppAddTimeOut( app, sleep, Move_Tiles, NULL );
   
 }

 else{
   counter=0;
   AcceptButtonPress=True;
   return;
 }
   
}










