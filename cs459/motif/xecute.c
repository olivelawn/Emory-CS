
/******************************************************************
 * xecute.c: Execute a command after the user confirms the action
 ******************************************************************/
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
void OneCallback ( Widget w, XtPointer clientData, XtPointer callData );


void main ( int argc, char **argv )
{
    Widget       shell, msg, bb, quit, reset, one, two;
    XtAppContext app;
    XmString     xmstr;
    /* Dimension    height; */

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "puzzle", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   
   /* Create a simple manager widget to hold the other widgets */

    bb = XtVaCreateManagedWidget ( "bboard", xmBulletinBoardWidgetClass,
				   shell,
				   XmNmarginWidth, 0,
				   XmNmarginHeight, 0,
				   XmNwidth, width,
				   XmNheight, height,
				   NULL );


   /*
    * Create two button widgets for "quit" and "reset"
    */

    quit = XtVaCreateManagedWidget ( "quit", xmPushButtonWidgetClass, bb, 
                                   XmNx, 0,
	                           XmNy, 0,
                                   NULL );


    reset = XtVaCreateManagedWidget ( "reset", xmPushButtonWidgetClass, bb, 
                                   XmNx, 180,
	                           XmNy, 0,
                                   NULL );

    one = XtVaCreateManagedWidget ( "1", xmPushButtonWidgetClass, bb, 
                                   XmNx, 0,
	                           XmNy, 40,
				   XmNwidth, b_width,
				   XmNheight, b_height,
                                   NULL );

    two = XtVaCreateManagedWidget ( "2", xmPushButtonWidgetClass, bb, 
                                   XmNx, 59,
	                           XmNy, 40,
				   XmNwidth, b_width,
				   XmNheight, b_height,
                                   NULL );


    /* Try to get color working */
    XmChangeColor(bb, 0);
    XmChangeColor(quit, 0);
    XmChangeColor(reset, 0);

   /* 
    * Add a callback to each button, for "yes" and "no" 
    * Pass the command to be executed as client data
    */

    XtAddCallback ( quit, XmNactivateCallback, 
                    QuitCallback, ( XtPointer ) argv[2] );

    XtAddCallback ( reset, XmNactivateCallback, 
                    ResetCallback, NULL );


    XtAddCallback ( one, XmNactivateCallback, 
                    OneCallback, NULL );

   /*
    * Realize the shell and enter the event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

void QuitCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
    printf("hit the quit button\n");
    exit(1);
}

void ResetCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
     printf("hit the reset button\n");
}

void OneCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
     printf("hit the 1 button\n");
}

