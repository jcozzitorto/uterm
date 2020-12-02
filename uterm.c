#include <stdio.h>
#include <vte/vte.h>

int main (int argc, char *argv[]) 
{
	GtkWidget *window, *terminal;

	gtk_init(&argc, &argv);
	terminal = vte_terminal_new();
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "uterm");

	gchar **envp = g_get_environ();
	gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL };
	g_strfreev(envp);
	vte_terminal_spawn_async(VTE_TERMINAL(terminal),
			VTE_PTY_DEFAULT,
			NULL,
			command,
			NULL,
			0,
			NULL, NULL,
			NULL,
			-1,
			NULL, NULL, NULL);

	g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
	g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);


	gtk_container_add(GTK_CONTAINER(window), terminal);
	gtk_widget_show_all(window);
	gtk_main();
}
