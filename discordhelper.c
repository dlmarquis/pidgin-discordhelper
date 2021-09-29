#define PURPLE_PLUGINS

#include <glib.h>

#include "notify.h"
#include "plugin.h"
#include "version.h"
#include "debug.h"

#include "gtkplugin.h"
#include "gtkprefs.h"
#include "gtkutils.h"
#include "gtkimhtml.h"

#include <string.h>

#define PLUGIN_ID "gtk-dlmarquis-discordhelper"

#define DSCMSGSIZE  (sizeof("dscmsg:") - 1)

PurplePlugin *quickadd_plugin = NULL;

static void add_buddy(GtkWidget *w, gchar *username)
{
	purple_blist_request_add_buddy(NULL, username, NULL, NULL);
}

static void url_copy(GtkWidget *w, gchar *url)
{

	GtkClipboard *clipboard;

	clipboard = gtk_widget_get_clipboard(w, GDK_SELECTION_PRIMARY);
	gtk_clipboard_set_text(clipboard, url, -1);

	clipboard = gtk_widget_get_clipboard(w, GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_set_text(clipboard, url, -1);
}

static gboolean
add_menu(GtkIMHtml *imhtml, GtkIMHtmlLink *link, GtkWidget *menu)
{
	GtkWidget *img, *item;
	const char *text;
	char *msg_id;

	text = gtk_imhtml_link_get_url(link);
	g_return_val_if_fail(text && strlen(text) > DSCMSGSIZE, FALSE);
	msg_id = (char*)text + DSCMSGSIZE;

	/* Copy Message ID */
	//img = gtk_image_new_from_stock(GTK_STOCK_COPY, GTK_ICON_SIZE_MENU);
	item = gtk_image_menu_item_new_with_mnemonic(("_Copy Message ID"));
	//gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), img);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(url_copy), msg_id);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

	/* React */
	//img = gtk_image_new_from_stock(GTK_STOCK_COPY, GTK_ICON_SIZE_MENU);
	//item = gtk_image_menu_item_new_with_mnemonic(("_React"));
	//gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), img);
	//g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(add_buddy), msg_id);
	//gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

	return TRUE;

//GtkIMHtml->protocols
}

static gboolean
url_clicked_idle_cb(gpointer data)
{
	purple_notify_uri(NULL, data);
	g_free(data);
	return FALSE;
}

static gboolean
url_clicked_cb(GtkIMHtml *imhtml, GtkIMHtmlLink *link)
{
	char *msg_id;
	const char *uri = gtk_imhtml_link_get_url(link);
	g_return_val_if_fail(uri && strlen(uri) > DSCMSGSIZE, FALSE);
	msg_id = (char*)uri + DSCMSGSIZE;
	url_copy(GTK_WIDGET(imhtml), msg_id);
	//g_idle_add(url_clicked_idle_cb, g_strdup(uri));
	return TRUE;
}

static gboolean
plugin_load(PurplePlugin *plugin) {



	gtk_imhtml_class_register_protocol("dscmsg:", NULL, NULL);

	gtk_imhtml_class_register_protocol("dscmsg:", url_clicked_cb, add_menu);

	return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin)
{
	return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    PLUGIN_ID,
    "DiscordHelper",
    "0.1",

    "DiscordHelper",
    "DiscordHelper Plugin",
    "Danielle Marquis (dmarquis@g.hmc.edu)",
    "",

    plugin_load,
    plugin_unload,
    NULL,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static void
init_plugin(PurplePlugin *plugin)
{
}

PURPLE_INIT_PLUGIN(hello_world, init_plugin, info)
