#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "xor.h"
#include "ImageTraining.h"
#include "SaveAndLoad.h"

/************************  Environment Variables  *************************/
GtkWidget *MainWindow;
const gchar *path;
GtkWidget *Image;
GtkWidget * Table;
gchar *correction;
int First_Time = 0;
GtkWidget * ExtractBtn;
GtkWidget * GetTextBtn;



// Function which create an icon
GdkPixbuf *create_pixbuf(const gchar * filename)
{

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf)
   {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}


/********************************** XOR ************************************/
void OK_Xor (GtkWidget * button, gpointer data)
{
    button = button;
    const gchar * i1;
    const gchar * i2;
    int input1;
    int input2;
    GSList *l1;
    GSList *l2;
    GtkWidget * Result;
    GtkWidget * Window;

    l1 =  gtk_radio_button_get_group(GTK_RADIO_BUTTON(g_slist_nth_data(data, 0)));
    l2 =  gtk_radio_button_get_group(GTK_RADIO_BUTTON(g_slist_nth_data(data, 1)));
    Window = g_slist_nth_data(data, 2);

    while(l1)
    {
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(l1->data)))
        {
            i1 = gtk_button_get_label(GTK_BUTTON(l1->data));
            l1 = NULL;
        }
        else
        {
            l1 = g_slist_next(l1);
        }
    }

    while(l2)
    {
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(l2->data)))
        {
            i2 = gtk_button_get_label(GTK_BUTTON(l2->data));
            l2 = NULL;
        }
        else
        {
            l2 = g_slist_next(l2);
        }
    }
    input1 = atoi(i1);
    input2 = atoi(i2);
    double res =  xor_f(input1, input2);

    // Display the result of XOR according to inputs
    Result  = gtk_message_dialog_new (GTK_WINDOW(Window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_CANCEL,
        "%lf", res);
    gtk_window_set_title(GTK_WINDOW(Result), "Result");

    gtk_dialog_run(GTK_DIALOG(Result));
    gtk_widget_destroy(Result);
}


/********************************* SETTINGS ********************************/
void Exit_Settings (GtkWidget * button, gpointer data)
{
    button = button;
    gtk_widget_destroy(data);
}



void Open_Settings (GtkWidget * button, gpointer data)
{
    button = button;

    // Main Window
    data = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(data), "Settings");
    gtk_widget_set_size_request(GTK_WIDGET(data), 1000, 1000);
    gtk_widget_show(data);
    gtk_window_set_modal(GTK_WINDOW(data), TRUE);

    // Variables
    GtkWidget * TableSettings = gtk_table_new(40, 40, TRUE);
    GtkWidget * Input1 = gtk_label_new("Input 1:");
    GtkWidget * Input2 = gtk_label_new("Input 2:");
    GtkWidget * OK =  gtk_button_new_from_stock(GTK_STOCK_OK);
    GtkWidget * Exit = gtk_button_new_from_stock(GTK_STOCK_GO_BACK);
    GtkWidget * Frame = gtk_frame_new ("XOR");
    GSList *Inputs_List = NULL;

    GtkWidget * Iterations = gtk_label_new("Number of iterations : 50.000");
    GtkWidget * Learning_rate = gtk_label_new("Learning rate : 0.1");
    GtkWidget * Number = gtk_label_new("Number of perceptrons : 30");
    GtkWidget * Frame2 = gtk_frame_new("Learning");
    GtkWidget * Train = gtk_button_new_with_label("Train");


    // Link widgets to Table
    gtk_table_attach(GTK_TABLE(TableSettings), Input1, 11, 14, 6, 8, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Input2, 19, 22, 6, 8, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), OK, 15, 18, 12, 14, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Exit, 0, 3, 0, 1, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Learning_rate, 11, 17, 23, 24, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Number, 11, 19, 25, 26, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Iterations, 11, 19, 27, 28, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_table_attach(GTK_TABLE(TableSettings), Train, 13, 16, 29, 30, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    // Creation input1
    GtkWidget * Btn1 = gtk_radio_button_new_with_label(NULL, "0");
    gtk_table_attach(GTK_TABLE(TableSettings), Btn1, 12, 14, 8, 9, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    GtkWidget * Btn2 =
        gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (Btn1), "1");
    gtk_table_attach(GTK_TABLE(TableSettings), Btn2, 12, 14, 10, 11, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    // Creation input2
    GtkWidget * Btn3 = gtk_radio_button_new_with_label(NULL, "0");
    gtk_table_attach(GTK_TABLE(TableSettings), Btn3, 20, 22, 8, 9, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    GtkWidget * Btn4 =
        gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (Btn3), "1");
    gtk_table_attach(GTK_TABLE(TableSettings), Btn4, 20, 22, 10, 11, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    // Frames
    gtk_frame_set_shadow_type (GTK_FRAME(Frame), GTK_SHADOW_ETCHED_IN);
    gtk_table_attach (GTK_TABLE(TableSettings), Frame, 10, 24, 4, 16, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_frame_set_shadow_type (GTK_FRAME(Frame2), GTK_SHADOW_ETCHED_IN);
    gtk_table_attach (GTK_TABLE(TableSettings), Frame2, 10, 24, 22, 31, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);


    // Add Table in window (data)
    gtk_container_add(GTK_CONTAINER(data), TableSettings);
    gtk_widget_show_all(data);

    // When the user press OK for XOR
    Inputs_List = g_slist_append(Inputs_List, Btn1);
    Inputs_List = g_slist_append(Inputs_List, Btn3);
    Inputs_List = g_slist_append(Inputs_List, data);
    g_signal_connect(G_OBJECT(OK), "clicked", G_CALLBACK(OK_Xor), Inputs_List);

    // When the user press exit
    g_signal_connect(G_OBJECT(Exit), "clicked",
            G_CALLBACK(Exit_Settings), data);

}


/****************************** LOAD IMAGE *******************************/
void display_image (GtkWidget *button, gpointer data)
{
    button = button;
    const gchar *_path;
    GdkPixbuf * test;
    GtkWidget * file_selection = data;
    _path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));


    //Check if the file chosen is an image -> ERROR otherwise
    test = gdk_pixbuf_new_from_file(_path, NULL);
    if (!test)
    {
            GtkWidget * Failure  = gtk_message_dialog_new
                (GTK_WINDOW(file_selection),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_CANCEL,
            "This is not an image");
            gtk_dialog_run(GTK_DIALOG(Failure));
            gtk_widget_destroy(Failure);
            return;
    }

    gtk_widget_destroy(file_selection);

    // Resize the image if this one is too big
    int w = gdk_pixbuf_get_width(test);
    int h = gdk_pixbuf_get_height(test);
    if (w > 1200|| h  > 700)
    {
        test = gdk_pixbuf_scale_simple(test, 800, 800, GDK_INTERP_BILINEAR);
    }


    // Display a preview of image
    GtkWidget * Preview = gtk_image_new_from_pixbuf(test);//gtk_image_new_from_file(_path);
    GtkWidget * display = gtk_dialog_new_with_buttons("Preview",
            GTK_WINDOW(MainWindow), GTK_DIALOG_MODAL, GTK_STOCK_OK,
            GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(display)->vbox), Preview, FALSE, FALSE, 0);
    gtk_widget_show_all(display);


    switch (gtk_dialog_run(GTK_DIALOG(display)))
    {
        // The user validate the image
        case GTK_RESPONSE_OK:

            // Verify if the image is not too large, ERROR
            if (w > 1200|| h  > 700)
            {
                 GtkWidget * Failure  = gtk_message_dialog_new (GTK_WINDOW(display),
                 GTK_DIALOG_MODAL,
                 GTK_MESSAGE_ERROR,
                 GTK_BUTTONS_CANCEL,
                 "The maximal format accepted is : 1200 x 700. Please choose another image");
                 gtk_dialog_run(GTK_DIALOG(Failure));
                 gtk_widget_destroy(Failure);
                 break;
            }

            // Display the image in the main window
            path = _path;
            printf("%s\n", path);
            if (First_Time == 1)
                gtk_container_remove(GTK_CONTAINER(Table), Image);
            First_Time = 1;
            Image = gtk_image_new_from_pixbuf(test);
            //Image = gtk_image_new_from_file(_path);
            gtk_table_attach(GTK_TABLE(Table), Image, 15, 35, 10, 25, GTK_EXPAND
                    ,
            GTK_EXPAND, 0, 0);
            gtk_widget_set_sensitive(ExtractBtn, TRUE);
            gtk_widget_set_sensitive(GetTextBtn, TRUE);
            gtk_widget_show_all(MainWindow);
            break;

        // The user cancel
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
        default:
            break;
    }
    gtk_widget_destroy(display);

}



void Open_File (GtkWidget * button, gpointer data)
{
    data = data;
    button = button;

    // The user choose an image in his files
    GtkWidget* selection;
    selection = gtk_file_selection_new("Choose your image !");
    gtk_widget_show(selection);
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

    // The user select an image
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
            "clicked", G_CALLBACK(display_image), selection);

    // The user quit the selection menu
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button),
            "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}



/*************************** GET TEXT OCR ************************/
void Print_Text (GtkWidget * button, gpointer data)
{
	/////////////////////////////////
	Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 625;
	*(sizes.pt + 1) = 30;
	*(sizes.pt + 2) = 10;

	Network net = LoadNetwork(sizes);
	/////////////////////////////////

    button = button;
    GtkTextBuffer * text_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(data));

    char s[100] = "";
    for (int i = 0; *path != '\0'; i++)
    {
        s[i] = *path;
        path = path + 1; 
    }
    char st[100] = "";


    ApplyOCR2(s, st, net);

	free_network(net);
	free(sizes.pt);

    gtk_text_buffer_set_text(text_buffer, st, -1);
}


/**************************** SAVE *******************************/
void Save (GtkWidget * button, gpointer data)
{
    button = button;
    // Get the correction text written by a user
    GtkTextBuffer * text_buffer = gtk_text_view_get_buffer(data);
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(text_buffer, &start);
    gtk_text_buffer_get_end_iter(text_buffer, &end);
    correction = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
    printf("%s\n", correction);
    FILE *file;
    file = fopen("t.txt", "w+");
    fputs(correction, file);
    fclose(file);
    g_free(correction);
}



/************************************************************************************************/
/*                                          USER INTERFACE
************************************************************************************************/

int main(int argc, char **argv)
{

	/*Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 625;
	*(sizes.pt + 1) = 30;
	*(sizes.pt + 2) = 10;

	Network net = LoadNetwork(sizes);
	print_network(net, net.length);
	
	free(sizes.pt);
	free_network(net);
*/

/*************** Variables ***************/
    GtkWidget * Settings = NULL;
    GdkPixbuf * icon = create_pixbuf("Logo.png");
    GtkWidget * Logo;
    GtkWidget * QuitBtn;
    GtkWidget * LoadBtn;
    GtkWidget * SettingsBtn;
    Table = gtk_table_new(42, 40, TRUE);
    GtkWidget * Frame;
    GtkWidget * Frame2;
    GtkWidget * Frame3;
    GtkWidget * Frame4;
    GtkWidget * Text_Zone;
    GtkWidget * SaveBtn;
    GtkWidget * Arrow;
    GtkWidget * Arrow2;
/******************************************/


    /****** Initialisation of GTK+ ******/

    gtk_init(&argc, &argv);



    /****** Window's creation *******/

    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); // constructor of window, type : normal window
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);



    /****** Customization of the window ******/

    gtk_window_set_title(GTK_WINDOW(MainWindow), "OCR DU TURFUX");

    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 500, 500);

    gtk_window_set_icon(GTK_WINDOW(MainWindow), icon);



    /****************** GtkButtons ********************/

    // -> Load
    LoadBtn = gtk_button_new_with_label("Load Image");
    gtk_table_attach(GTK_TABLE(Table), LoadBtn, 2, 6, 4, 6, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);

    // -> Extract
    ExtractBtn = gtk_button_new_with_label("Extraction");
    gtk_table_attach(GTK_TABLE(Table), ExtractBtn, 2, 6, 12, 14, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);
    gtk_widget_set_sensitive(ExtractBtn, FALSE);


    // -> Settings
    SettingsBtn = gtk_button_new_with_label("Settings");
    gtk_table_attach(GTK_TABLE(Table), SettingsBtn, 2, 6, 28, 30, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);
    g_signal_connect(G_OBJECT(SettingsBtn), "clicked", G_CALLBACK(Open_Settings),
            Settings);

    // -> Quit
    QuitBtn = gtk_button_new_from_stock (GTK_STOCK_QUIT);
    gtk_table_attach(GTK_TABLE(Table), QuitBtn, 2, 6, 36, 38, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);
    g_signal_connect(G_OBJECT(QuitBtn), "clicked",
           G_CALLBACK(gtk_main_quit), NULL);


    /************** Text Zone ********************/
    Text_Zone = gtk_text_view_new();
    gtk_table_attach(GTK_TABLE(Table), Text_Zone, 10, 31, 36, 39, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

    // -> Get Text
    GetTextBtn = gtk_button_new_with_label("Get Text");
    gtk_table_attach(GTK_TABLE(Table), GetTextBtn, 2, 6, 20, 22, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND | GTK_FILL, 0, 0);
    gtk_widget_set_sensitive(GetTextBtn, FALSE);

    g_signal_connect(G_OBJECT(GetTextBtn), "clicked", G_CALLBACK(Print_Text),
            Text_Zone);

    // -> Save Text
    SaveBtn = gtk_button_new_with_label("Save!");
    gtk_table_attach(GTK_TABLE(Table), SaveBtn, 34, 38, 36, 38, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
    g_signal_connect(G_OBJECT(SaveBtn), "clicked", G_CALLBACK(Save),
            Text_Zone);


    /************** File Selection ****************/

    g_signal_connect(G_OBJECT(LoadBtn), "clicked", G_CALLBACK(Open_File),
            ExtractBtn);

    /************** GtkFrames & Design ********************/

    Frame = gtk_frame_new ("Menu");
    gtk_frame_set_shadow_type (GTK_FRAME(Frame), GTK_SHADOW_ETCHED_IN);
    gtk_table_attach (GTK_TABLE(Table), Frame, 0, 8, 0, 42, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

    Frame2 = gtk_frame_new ("");
    gtk_frame_set_shadow_type (GTK_FRAME(Frame2), GTK_SHADOW_ETCHED_IN);
    gtk_table_attach(GTK_TABLE(Table), Frame2, 8, 42, 34, 42, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

    Frame3 = gtk_frame_new("");
    gtk_frame_set_shadow_type (GTK_FRAME(Frame3), GTK_SHADOW_ETCHED_OUT);
    gtk_table_attach (GTK_TABLE(Table), Frame3, 14, 23, 1, 2, GTK_EXPAND |
            GTK_FILL, GTK_EXPAND, 0, 0);

    Frame4 = gtk_frame_new("");
    gtk_frame_set_shadow_type (GTK_FRAME(Frame4), GTK_SHADOW_ETCHED_OUT);
    gtk_table_attach (GTK_TABLE(Table), Frame4, 27, 36, 1, 2, GTK_EXPAND |
            GTK_FILL,
            GTK_EXPAND , 0, 0);

    Logo = gtk_image_new_from_file("Logo.png");
    gtk_table_attach (GTK_TABLE(Table), Logo, 24, 26, 0, 3, GTK_EXPAND |
          GTK_FILL, GTK_EXPAND | GTK_FILL | GTK_FILL, 0, 0);

    GdkPixbuf * test = gdk_pixbuf_new_from_file("Red_Arrow.png", NULL);
    test = gdk_pixbuf_scale_simple(test, 100, 100, GDK_INTERP_BILINEAR);
    Arrow = gtk_image_new_from_pixbuf(test);
    gtk_table_attach (GTK_TABLE(Table), Arrow, 3, 5, 7, 11, GTK_EXPAND |
          GTK_FILL, GTK_EXPAND | GTK_FILL | GTK_FILL, 0, 0);
    Arrow2 = gtk_image_new_from_pixbuf(test);
    gtk_table_attach (GTK_TABLE(Table), Arrow2, 3, 5, 15, 19, GTK_EXPAND |
          GTK_FILL, GTK_EXPAND | GTK_FILL | GTK_FILL, 0, 0);

    /************* ADD WIDGET IN MAINWINDOW ******************/
    gtk_container_add(GTK_CONTAINER(MainWindow), Table);



    /************* DISPLAY & EVENT LOOP *************/
    gtk_widget_show_all(MainWindow);
    g_object_unref(icon);
    gtk_main();



    /************* Leaving.. *************/

	
    return EXIT_SUCCESS;

    return 0;




}



