/**
 * This is a simple Motif application that creates a window with a button.
 * When the button is pressed, it prints a message to the console.
 * It also handles key presses, logging the key code to the console and
 * allowing the user to exit the application by pressing the Escape key.
 */
#include <Xm/PushB.h>       // for PushButton widget
#include <Xm/BulletinB.h>   // for BulletinBoard widget
#include <X11/keysym.h>     // for KeySym and XLookupKeysym
#include <stdlib.h>         // for exit()
#include <stdio.h>          // for printf()

// function declarations
void button_pushed(Widget, XtPointer, XtPointer);             // function for button press
void handle_keypress(Widget, XtPointer, XEvent *, Boolean *); // function for key press handling

// main function
int main(int argc, char **argv)
{
    Widget toplevel, button, board;
    XtAppContext app;
    XmString label;

    // Initialize the Xt toolkit and create the top-level widget
    XtSetLanguageProc(NULL, NULL, NULL);
    toplevel = XtVaAppInitialize(&app, "Hello", NULL, 0,
                                 &argc, argv, NULL, NULL);

    // Setup initial window and size it to 400x400
    XtVaSetValues(toplevel, XmNwidth, 400, XmNheight, 400, NULL);

    Display *display = XtDisplay(toplevel);
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));
    XColor color, exact;
    XAllocNamedColor(display, colormap, "black", &color, &exact);

    // Create a BulletinBoard widget to hold the button
    board = XtVaCreateManagedWidget("board",
                                    xmBulletinBoardWidgetClass, toplevel,
                                    XmNbackground, color.pixel, // Set background color
                                    NULL);

    // Create a PushButton widget with a label
    // The label is created using XmString to support internationalization
    label = XmStringCreateLocalized("Push here to say hello");
    button = XtVaCreateManagedWidget("pushme",
                                     xmPushButtonWidgetClass, board,
                                     XmNlabelString, label,
                                     XmNx, 100,     // X position
                                     XmNy, 180,     // Y position
                                     XmNwidth, 200, // Width
                                     XmNheight, 40, // Height
                                     NULL);

    // Free the label string from memoty after creating the button
    XmStringFree(label);

    // Add a callback function to the button for when it is pressed
    XtAddCallback(button, XmNactivateCallback, button_pushed, NULL);

    // Create parent widget (toplevel) and its children (board and button)
    XtRealizeWidget(toplevel);

    // Q: Why does this work on 'button' but not work on 'toplevel' or 'board'?
    // A: The button is a focusable widget, while toplevel and board are not.
    //    The button can receive keyboard events, so we add the keypress handler to it
    //    to handle key presses like Escape to exit the application.
    XtAddEventHandler(button, KeyPressMask, False, handle_keypress, NULL);

    // Attaches the application to the X11 event loop.
    XtAppMainLoop(app);
}

// Callback function for button press.
void button_pushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
    printf("Hello, Motif tutorial user!\n");
}

// Function to handle key (keyboard) presses.
void handle_keypress(Widget widget, XtPointer client_data, XEvent *event, Boolean *continue_to_dispatch)
{
    if (event->type == KeyPress)
    {
        XKeyEvent *key_event = (XKeyEvent *)event;
        KeySym keysym = XLookupKeysym(key_event, 0);
        
        // If user presses Escape key, exit the application
        if (keysym == XK_Escape)
        {
            printf("Escape pressed. Exiting.\n");
            exit(0);
        }
        // Otherwise, print the code of the key pressed
        else
        {
            printf("Key pressed: %lu\n", keysym);
        }
    }
}
