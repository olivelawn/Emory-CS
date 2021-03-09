
/******************************************************************/
/*                                                                */
/*      This example demonstrates the usage of Xlib routines:     */
/*  "XDrawText","XDrawImageString","XDrawString","XTextExtents",  */
/*  "XQueryTextExtents","XLoadFont","XQueryFont","XLoadQueryFont",*/
/*  "XGetFontProperty" and "XUnloadFont".                         */
/*                                                                */
/*       This program first loads the font named by command line  */
/*  argument.  If no argument is given, "fixed" font is used by   */
/*  default.  Then it uses XTextExtents to get the font's writing */
/*  direction and dimension of the text string.  Based on the     */
/*  information,  three strings are drawn in the window using     */
/*  different X routines. In the second string, the ascent part   */
/*  and descent part of the text boxes are filled with different  */
/*  colors. The third string is drawn by XDrawImagestring, and it */
/*  also comes with an underline that is drawn by XFillRectangle. */
/*                                                                */
/******************************************************************/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>

Display            *display;
int                screen_num;
Window             root,main_win;
XEvent             the_event;
GC                 the_GC,fill_ascent_GC,fill_decent_GC;
char               test_string[24]="Gc test string: fjpqy.";
Font               demo_font;
XFontStruct        *demo_font_struct;
XCharStruct        xchar_struct;
int                text_width,direction,ascent,decent;
XTextItem          text_items[2];
unsigned long      green_pix,yellow_pix;
XColor             screen_color,exact_color;
int                underline_position,underline_thick;

main(argc,argv)
int argc;
char **argv;
{
    int i;

    /* Open a connection to the server */
    if ((display=XOpenDisplay(NULL)) == NULL) {
        (void) fprintf(stderr, "Can't connect to display\n");
        exit(-1);
    }

    /* Get some default values from the server */
    screen_num = DefaultScreen(display);
    root = DefaultRootWindow(display);
    
    /* Create a main window and allocate two colors */
    main_win = XCreateSimpleWindow(display,root,    
                100, 100, 420, 420, 2,    
                BlackPixel(display,screen_num),  /* foreground */
                WhitePixel(display,screen_num)); /* background */
    if(XAllocNamedColor(display,DefaultColormap(display,screen_num),
                    "green",&screen_color,&exact_color) == 0) 

        /* If can't alloc green, use white instead */
        green_pix = WhitePixel(display,screen_num);  
    else
        green_pix = screen_color.pixel;
    if(XAllocNamedColor(display,DefaultColormap(display,screen_num),
                    "yellow",&screen_color,&exact_color) == 0) 

        /* If can't alloc green, use white instead */
        yellow_pix = WhitePixel(display,screen_num);  
    else
        yellow_pix = screen_color.pixel;

    /* Get the font name from the argument,
       otherwise use "fixed" as default */
    if(argc > 1){
        if ((demo_font_struct =
              XLoadQueryFont(display,argv[1])) == NULL){
            fprintf(stderr,
              "\"%s\" font not found, use \"fixed\" instead\n",
                                                       argv[1]);
            demo_font_struct = XLoadQueryFont(display,"fixed");
        } 
        else
            demo_font = demo_font_struct->fid;
    }
    else {

        /* No command line argument, use 'fixed' font as default */
        demo_font = XLoadFont(display,"fixed");
        demo_font_struct = XQueryFont(display,demo_font);
    }

    /* Create three GC's and set corresponding colors in them */
    the_GC = XCreateGC(display,main_win,0,0);
    XSetFont(display,the_GC,demo_font);
    XSetBackground(display,the_GC,green_pix);
    XSetForeground(display,the_GC,BlackPixel(display,screen_num));
    fill_ascent_GC = XCreateGC(display,main_win,0,0);
    fill_decent_GC = XCreateGC(display,main_win,0,0);
    XSetForeground(display,fill_ascent_GC,yellow_pix);
    XSetForeground(display,fill_decent_GC,green_pix);
    /* Get the dimension information of the test_string in order
       to compute the right position of the text in the window */
    text_width = XTextWidth(demo_font_struct,
                      test_string,strlen(test_string));
    XTextExtents(demo_font_struct,
                    test_string,strlen(test_string),
                    &direction,&ascent,&decent,&xchar_struct);

    /*
     *  Here XQueryTextExtents can be used instead of XTextExtents.
     *  The difference between them is that XTextExtents computes
     *  locally whereas, XQueryTextExtents sends a request to the
     *  server and bears the round-trip overhead.
     * 
     *    XQueryTextExtents(display,
     *                    demo_font_struct->fid,  
     *                    test_string,
     *                    strlen(test_string),
     *                    &direction,
     *                    &ascent,
     *                    &decent,
     *                    &xchar_struct);
     */

    /* Define the text_items to be used with XDrawText later */
    text_items[0].chars = test_string;
    text_items[0].nchars = strlen(test_string);
    text_items[0].delta = 10;
    text_items[0].font = demo_font;
    text_items[1].chars = test_string;
    text_items[1].nchars = strlen(test_string);
    text_items[1].delta = 10;
    text_items[1].font = demo_font;

    /* Get the font properties of underline position and thickness
       thickness in order to draw an under line with the string  */
    if (!XGetFontProperty(demo_font_struct,XA_UNDERLINE_POSITION,
                      &underline_position)) underline_position = 3;
    if (!XGetFontProperty(demo_font_struct,XA_UNDERLINE_THICKNESS,
                            &underline_thick)) underline_thick = 1;

    /* Set the event mask and map the window */
    XSelectInput(display,main_win,ExposureMask|
                   StructureNotifyMask|ButtonPressMask);
    XMapWindow(display,main_win);

    /* Main event loop to draw three text strings with differnt
       routines. Strings are all centered in the window */
    while(1) {
        XNextEvent(display,&the_event);
        switch (the_event.type) {
            case Expose:{ 
                Window temp_root;    /* local varriables */
                unsigned int width,height,x,y,border,depth;
                
                /* Get the window geometry, especially
                   if it is resized. */
                XGetGeometry(display,main_win,&temp_root,
                            &x,&y,&width,&height,&border,&depth);

                /* Draw a string with XTextItem array */
                XDrawText(display,main_win,the_GC,
                        (width-text_width*2-20)/2,height/4,
                        text_items,2);
                    
                /* Draw a string with different background
                   colors in ascent and decent parts */
                x = (width-text_width)/2;
                y = height/2;
                XFillRectangle(display,main_win,fill_ascent_GC,
                        x-xchar_struct.lbearing,y-ascent, /* x,y */
                        xchar_struct.lbearing+xchar_struct.rbearing,
                        ascent);
                XFillRectangle(display,main_win,fill_decent_GC,
                        x-xchar_struct.lbearing,y, 
                        xchar_struct.lbearing+xchar_struct.rbearing,
                        decent);
                XDrawString(display,main_win,the_GC,
                            x,y,test_string,
                            strlen(test_string));

                /* Draw a string with its own foreground and
                   background color in the text box        */
                XDrawImageString(display,main_win,the_GC,
                        (width-text_width)/2,height*3/4, /* x,y */
                        test_string,
                        strlen(test_string));

                /* Draw the under line */                    
                XFillRectangle(display,main_win,the_GC,
                        (width-text_width)/2,           /* x */
                        height*3/4 + underline_position,/* y */
                        text_width,                     /* width */
                        underline_thick);           /* thickness */
                }
                break;
            case ConfigureNotify:

                /* When window is reconfigured, generate
                   an expose event to redraw the content */
                XClearArea(display,main_win,0,0,0,0,True);
                break;
            case ButtonPress:
                if (the_event.xbutton.button == Button3) {
                        XUnloadFont(display,demo_font);
                        XCloseDisplay(display);
                        exit(0);
                }
                break;
        }
    }
}
