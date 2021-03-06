#include <Xm/PushB.h>

main(argc, argv)
int argc;
char *argv[];
{
  Widget toplevel, button;
  XtAppContext app;
  XmString label;
  void button_pushed();

  XtSetLanguageProc (NULL, NULL, NULL);

  toplevel = XtVaAppInitialize (&app, "Hello", NULL, 0,
				&argc, argv, NULL, NULL);
  
  label = XmStringCreateLocalized("Push here to say hello");
  button = XtVaCreateManagedWidget("pushme", xmPushButtonWidgetClass, toplevel, 
				   XmNlabelString, label, NULL);
  XmStringFree(label);
  XtAddCallback(button, XmNactivateCallback, button_pushed, NULL);
  
  XtRealizeWidget (toplevel);
  XtAppMainLoop(app);
}

void button_pushed(widget, client_data, call_data)
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  printf("Hello YTourself\n");
}
