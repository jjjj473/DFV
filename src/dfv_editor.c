#include <gtk/gtk.h>
#include <ges/ges.h>

/* Simple callback to quit the app */
static void on_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

/* Build a minimal timeline with a single clip */
static GESTimeline *
build_timeline(const gchar *uri, gint64 start, gint64 duration) {
    GESTimeline *timeline = ges_timeline_new_audio_video();
    GESLayer *layer = ges_layer_new();
    ges_timeline_add_layer(timeline, layer);

    GESClip *clip = ges_clip_asset_request_sync(uri, NULL);
    if (!clip) {
        g_printerr("Failed to load clip: %s\n", uri);
        return timeline;
    }

    ges_layer_add_clip(layer, clip);
    ges_clip_set_inpoint(clip, start);
    if (duration > 0)
        ges_clip_set_duration(clip, duration);

    return timeline;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    ges_init();

    const gchar *uri = NULL;
    if (argc > 1)
        uri = argv[1];
    else
        uri = "test-src.ogg";

    GESTimeline *timeline = build_timeline(uri, 0, 0);
    GESPipeline *pipeline = ges_pipeline_new();
    ges_pipeline_set_timeline(pipeline, timeline);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

    GtkWidget *video_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), video_area);

    GstElement *video_sink = gst_element_factory_make("gtksink", NULL);
    g_object_set(pipeline, "video-sink", video_sink, NULL);
    gtk_widget_show(window);

    ges_pipeline_set_state(pipeline, GST_STATE_PLAYING);

    gtk_main();
    ges_pipeline_set_state(pipeline, GST_STATE_NULL);
    g_object_unref(pipeline);
    return 0;
}
