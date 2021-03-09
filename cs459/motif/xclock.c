/*****************************************************
 * xclock: Demonstrate the use of timeout callbacks
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <time.h>

static void UpdateTime ( XtPointer    clientData,
                         XtIntervalId id );
  
void main ( int argc, char **argv ) 
{
    Widget       shell, face;
    XtAppContext app ;

    shell = XtAppInitialize ( &app, "XClock",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
    
    face = XtCreateManagedWidget ( "face", xmLabelWidgetClass,
                                   shell, NULL, 0 );
   /*
    * Get the initial time.
    */
    
    UpdateTime ( ( XtPointer ) face, NULL );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
            
static void UpdateTime ( XtPointer clientData, XtIntervalId id ) 
{
    Widget w = ( Widget ) clientData;
    long   tloc, rounded_tloc, next_minute;
	char str[100];
	XmString  xmstr;
    
   /*
    * Get the system time.
    */
    
    time ( &tloc );
    
   /*
    * Convert the time to a string and display it,
    * after rounding it down to the last minute.
    */
    
    rounded_tloc = tloc / 60 * 60;
    
    sprintf ( str, "%s", ctime ( &rounded_tloc ) );
	xmstr =  XmStringCreateLtoR ( str, XmFONTLIST_DEFAULT_TAG );
	XtVaSetValues ( w, XmNlabelString, xmstr, NULL );
	XmStringFree ( xmstr );

    
   /*
    * Adjust the time to reflect the time until
    * the next round minute.
    */
    
    next_minute = ( 60 - tloc % 60 ) * 1000;
    
   /*
    * Xt removes timeouts when they occur,
    * so re-register the function.
    */
    
    XtAppAddTimeOut ( XtWidgetToApplicationContext ( w ),   
                      next_minute, UpdateTime, ( XtPointer ) w );
}
                                
