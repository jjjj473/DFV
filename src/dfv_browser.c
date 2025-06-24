#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

void fast_memcpy(void *dest, const void *src, size_t n);
size_t fast_strlen(const char *s);
long fast_add(long a, long b);
void fast_uppercase(char *s);
void *fast_memset(void *dest, int c, size_t n);
int fast_strcmp(const char *a, const char *b);
void *fast_memmove(void *dest, const void *src, size_t n);
unsigned long fast_sum_array(const unsigned int *arr, size_t n);

static const char *load_homepage(void)
{
    static char home[256] = "https://duckduckgo.com";
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

static void on_kernel_info(GtkMenuItem *m, gpointer win)
{
    struct utsname u;
    if (uname(&u) == 0) {
        char info[256];
        snprintf(info, sizeof(info), "%s %s\n%s\n%s", u.sysname, u.release,
                 u.version, u.machine);
        GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
            "%s", info);
        gtk_dialog_run(GTK_DIALOG(d));
        gtk_widget_destroy(d);
    }
}

static void on_memory_stats(GtkMenuItem *m, gpointer win)
{
    struct sysinfo s;
    if (sysinfo(&s) == 0) {
        double l1 = s.loads[0] / (double)(1 << SI_LOAD_SHIFT);
        double l5 = s.loads[1] / (double)(1 << SI_LOAD_SHIFT);
        double l15 = s.loads[2] / (double)(1 << SI_LOAD_SHIFT);
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "Uptime: %ld s\nLoad: %.2f %.2f %.2f\nRAM: %lu/%lu MB",
                 s.uptime, l1, l5, l15,
                 (unsigned long)((s.totalram - s.freeram) / 1024 / 1024),
                 (unsigned long)(s.totalram / 1024 / 1024));
        GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE,
            "%s", buf);
        gtk_dialog_run(GTK_DIALOG(d));
        gtk_widget_destroy(d);
    }
}

static void on_stack_change(GObject *stack, GParamSpec *pspec, gpointer data)
{
    const char *name = gtk_stack_get_visible_child_name(GTK_STACK(stack));
    WebKitWebView *wv = WEBKIT_WEB_VIEW(data);
    WebKitWebInspector *insp = webkit_web_view_get_inspector(wv);
    if (g_strcmp0(name, "devtools") == 0)
        webkit_web_inspector_show(insp);
    else
        webkit_web_inspector_close(insp);
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
    GtkWidget *kern_item = gtk_menu_item_new_with_label("Kernel Info");
    GtkWidget *mem_item = gtk_menu_item_new_with_label("Memory Stats");
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), info_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), net_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), disk_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), term_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), kern_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(tools_menu), mem_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), tools_item);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(box), hbox, TRUE, TRUE, 0);

    GtkWidget *sidebar = gtk_stack_sidebar_new();
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));
    gtk_box_pack_start(GTK_BOX(hbox), sidebar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), stack, TRUE, TRUE, 0);

    GtkWidget *webpage = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(webpage, TRUE);
    gtk_widget_set_vexpand(webpage, TRUE);
    gtk_stack_add_titled(GTK_STACK(stack), webpage, "web", "Web");

    GtkWidget *webview = webkit_web_view_new();
    gtk_box_pack_start(GTK_BOX(webpage), webview, TRUE, TRUE, 0);

    GtkWidget *dl_label = gtk_label_new("No downloads yet");
    gtk_stack_add_titled(GTK_STACK(stack), dl_label, "downloads", "Downloads");

    GtkWidget *hist_label = gtk_label_new("History not implemented");
    gtk_stack_add_titled(GTK_STACK(stack), hist_label, "history", "History");

    GtkWidget *settings_label = gtk_label_new("Settings go here");
    gtk_stack_add_titled(GTK_STACK(stack), settings_label, "settings", "Settings");

    GtkWidget *dev_label = gtk_label_new("Developer tools");
    gtk_stack_add_titled(GTK_STACK(stack), dev_label, "devtools", "Dev Tools");

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "web");

    const char *home = load_homepage();
    const char *uri = user_data ? (const char *)user_data : home;
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), uri);

    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
    webkit_settings_set_enable_developer_extras(settings, TRUE);

    g_signal_connect(info_item, "activate", G_CALLBACK(on_system_info), window);
    g_signal_connect(net_item, "activate", G_CALLBACK(on_network_info), window);
    g_signal_connect(disk_item, "activate", G_CALLBACK(on_disk_usage), window);
    g_signal_connect(term_item, "activate", G_CALLBACK(on_open_terminal), window);
    g_signal_connect(kern_item, "activate", G_CALLBACK(on_kernel_info), window);
    g_signal_connect(mem_item, "activate", G_CALLBACK(on_memory_stats), window);

    g_signal_connect(stack, "notify::visible-child-name", G_CALLBACK(on_stack_change), webview);

    char buf[64];
    char buf2[64];
    const char *demo = "fast routines";
    fast_memcpy(buf, demo, strlen(demo) + 1);
    fast_memset(buf2, 0, sizeof(buf2));
    size_t len = fast_strlen(buf);
    long sum = fast_add(2, 3);
    int cmp = fast_strcmp(buf, demo);
    fast_uppercase(buf);
    char movestr[32] = "overlap demo";
    fast_memmove(movestr+3, movestr, fast_strlen(movestr)+1);
    unsigned int arr[4] = {1,2,3,4};
    unsigned long total = fast_sum_array(arr, 4);
    g_print("Assembly demo: %s (len=%zu, add=%ld, cmp=%d, sum=%lu)\n",
           buf, len, sum, cmp, total);
    g_print("Memmove result: %s\n", movestr);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.dfvos.browser", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), argc > 1 ? argv[1] : NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
