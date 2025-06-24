#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void fast_memcpy(void *dest, const void *src, size_t n);
size_t fast_strlen(const char *s);
long fast_add(long a, long b);
void fast_uppercase(char *s);
void *fast_memset(void *dest, int c, size_t n);
int fast_strcmp(const char *a, const char *b);

static const char *load_homepage(void)
{
    static char home[256] = "https://example.com";
    char *path = g_build_filename(g_get_home_dir(), ".dfv_browser.conf", NULL);
    gchar *contents = NULL;
    if (g_file_get_contents(path, &contents, NULL, NULL)) {
        gchar **lines = g_strsplit(contents, "\n", 0);
        for (gchar **p = lines; *p; p++) {
            if (g_str_has_prefix(*p, "homepage=")) {
                g_strlcpy(home, *p + 9, sizeof(home));
            }
        }
        g_strfreev(lines);
        g_free(contents);
    }
    g_free(path);
    return home;
}

static void on_system_info(GtkMenuItem *m, gpointer win)
{
    gchar *cpu = NULL, *mem = NULL;
    g_file_get_contents("/proc/cpuinfo", &cpu, NULL, NULL);
    g_file_get_contents("/proc/meminfo", &mem, NULL, NULL);
    GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
        "%s\n\n%s", cpu ? cpu : "", mem ? mem : "");
    gtk_dialog_run(GTK_DIALOG(d));
    gtk_widget_destroy(d);
    g_free(cpu); g_free(mem);
}

static void on_open_terminal(GtkMenuItem *m, gpointer data)
{
    g_spawn_command_line_async("x-terminal-emulator", NULL);
}

static void on_network_info(GtkMenuItem *m, gpointer win)
{
    gchar *out = NULL;
    GError *err = NULL;
    g_spawn_command_line_sync("ip addr", &out, NULL, NULL, &err);
    GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
        "%s", out ? out : (err ? err->message : ""));
    gtk_dialog_run(GTK_DIALOG(d));
    gtk_widget_destroy(d);
    g_free(out);
    if (err) g_error_free(err);
}

static void on_disk_usage(GtkMenuItem *m, gpointer win)
{
    gchar *out = NULL;
    GError *err = NULL;
    g_spawn_command_line_sync("df -h", &out, NULL, NULL, &err);
    GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
        "%s", out ? out : (err ? err->message : ""));
    gtk_dialog_run(GTK_DIALOG(d));
    gtk_widget_destroy(d);
    g_free(out);
    if (err) g_error_free(err);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 1024, 768);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *tools_menu = gtk_menu_new();
    GtkWidget *tools_item = gtk_menu_item_new_with_label("Tools");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(tools_item), tools_menu);
    GtkWidget *info_item = gtk_menu_item_new_with_label("System Info");
    GtkWidget *net_item = gtk_menu_item_new_with_label("Network Info");
    GtkWidget *disk_item = gtk_menu_item_new_with_label("Disk Usage");
    GtkWidget *term_item = gtk_menu_item_new_with_label("Open Terminal");
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), info_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), net_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), disk_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), term_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), tools_item);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    GtkWidget *webview = webkit_web_view_new();
    gtk_box_pack_end(GTK_BOX(box), webview, TRUE, TRUE, 0);

    const char *home = load_homepage();
    const char *uri = user_data ? (const char *)user_data : home;
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), uri);

    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
    webkit_settings_set_enable_developer_extras(settings, TRUE);

    g_signal_connect(info_item, "activate", G_CALLBACK(on_system_info), window);
    g_signal_connect(net_item, "activate", G_CALLBACK(on_network_info), window);
    g_signal_connect(disk_item, "activate", G_CALLBACK(on_disk_usage), window);
    g_signal_connect(term_item, "activate", G_CALLBACK(on_open_terminal), window);

    char buf[64];
    char buf2[64];
    const char *demo = "fast routines";
    fast_memcpy(buf, demo, strlen(demo) + 1);
    fast_memset(buf2, 0, sizeof(buf2));
    size_t len = fast_strlen(buf);
    long sum = fast_add(2, 3);
    int cmp = fast_strcmp(buf, demo);
    fast_uppercase(buf);
    g_print("Assembly demo: %s (len=%zu, add=%ld, cmp=%d)\n", buf, len, sum, cmp);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.dfvos.browser", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), argc > 1 ? argv[1] : NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
