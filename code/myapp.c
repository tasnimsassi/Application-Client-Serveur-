
// Libraries
#include <gtk/gtk.h> // GTK Library
#include <stdio.h> // C IO Library (Not needed)

// Variables
GtkWidget *window; // Window
GtkLabel *mylabel; // Label
GtkWidget *entry0;
int nbruser=1;
const gchar *nbrclient;
// Main function
int main(int argc, char *argv[])
{
	GtkBuilder *builder; // GTK Builder variable
	gtk_init(&argc, &argv); // Start GTK
	
	builder = gtk_builder_new(); // Create GTK UI Builder
	gtk_builder_add_from_file(builder, "myui.glade", NULL); // Load our UI file

	// Assign the Variables
	window = GTK_WIDGET(gtk_builder_get_object(builder, "MyWindow")); // Load our window named MyWindow
	mylabel = GTK_LABEL(gtk_builder_get_object(builder, "MyLabel")); // Load our label named MyLabel
	entry0 = GTK_WIDGET(gtk_builder_get_object(builder, "nbrclient")); // Load our label named MyLabel
	// Essential for a GTK based program
	gtk_builder_connect_signals(builder, NULL); 
	g_object_unref(builder);
	
	gtk_widget_show_all(window); // Show our window
	gtk_main(); // Run our program

	return 0; // Necessary for a c main function
}

// Function to exit our app
void exit_app()
{
	printf("Exit app \n"); // Not neccesary
	gtk_main_quit(); // Command to quit a GTK program
}

// Function when our button is pressed
void tcp_clicked_cb()
{
	nbrclient = gtk_entry_get_text (GTK_ENTRY (entry0));
	int x = atoi(nbrclient);
	if ((x<=10)&&(x>0))
	{	
		nbruser=x;
	}
	printf("TCP clicked nombre clients : %d \n",nbruser);
	system("gnome-terminal -- bash -c 'make myAppServerTcp ; exec bash'");
	sleep(3);
	for(int i =0;i<nbruser;i++)
	{
	system("gnome-terminal -- bash -c 'make myAppClientTcp ; exec bash'");
	}
}
void on_pipe_clicked()
{

	nbrclient = gtk_entry_get_text (GTK_ENTRY (entry0));
	int x = atoi(nbrclient);
	if ((x<=10)&&(x>0))
	{	
		nbruser=x;
	}
	printf("PIPE clicked nombre clients : %d \n",nbruser);
	system("gnome-terminal -- bash -c 'make myAppServerPipe ; exec bash'");
	sleep(3);
	for(int i =0;i<nbruser;i++)
	{
	system("gnome-terminal -- bash -c 'make myAppClientPipe ; exec bash'");
	}
}
void udp_clicked()
{
	printf("UDP clicked nombre clients : %d \n",1);
	system("gnome-terminal -- bash -c 'make myAppServerUdp ; exec bash'");
	sleep(2);
	system("gnome-terminal -- bash -c 'make myAppClientUdp ; exec bash'");
	
}
