/* stb_gui_widgets - v1.00 - public domain GUI widgets library - http://nothings.org/stb
                                 no warranty implied; use at your own risk

   Do this:
      #define STB_GUI_WIDGETS_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   You can #define STB_GUI_ASSERT(x) before the #include to avoid using assert.h.
   And #define STB_GUI_MALLOC, STB_GUI_REALLOC, and STB_GUI_FREE to avoid using malloc,realloc,free

   QUICK NOTES:
      Simple GUI widgets library for games and applications
      Supports basic components: buttons, sliders, text boxes, labels
      Callback-based input handling
      Customizable appearance
      No external dependencies
      Works with any rendering backend

   LICENSE

   See end of file for license information.

RECENT REVISION HISTORY:

      1.00  (2024-10-26) initial release

*/

#ifndef STB_GUI_WIDGETS_H
#define STB_GUI_WIDGETS_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque widget handle
typedef void* stb_gui_widget;

// Widget types
typedef enum {
    STB_GUI_BUTTON,
    STB_GUI_SLIDER,
    STB_GUI_TEXTBOX,
    STB_GUI_LABEL,
    STB_GUI_CHECKBOX,
    STB_GUI_RADIOBUTTON,
    STB_GUI_DROPDOWN
} stb_gui_widget_type;

// Widget state
typedef enum {
    STB_GUI_NORMAL,
    STB_GUI_HOVERED,
    STB_GUI_PRESSED,
    STB_GUI_DISABLED,
    STB_GUI_FOCUSED
} stb_gui_widget_state;

// Color structure
typedef struct {
    float r, g, b, a;
} stb_gui_color;

// Rect structure
typedef struct {
    float x, y, width, height;
} stb_gui_rect;

// Font interface (for text rendering)
typedef struct {
    float (*get_text_width)(const char* text, float size);
    void (*render_text)(const char* text, float x, float y, float size, stb_gui_color color);
} stb_gui_font;

// Render callback function types
typedef void (*stb_gui_render_rect_func)(stb_gui_rect rect, stb_gui_color color, void* userdata);
typedef void (*stb_gui_render_text_func)(const char* text, float x, float y, float size, stb_gui_color color, void* userdata);

// Input event types
typedef enum {
    STB_GUI_MOUSE_DOWN,
    STB_GUI_MOUSE_UP,
    STB_GUI_MOUSE_MOVE,
    STB_GUI_KEY_DOWN,
    STB_GUI_KEY_UP,
    STB_GUI_TEXT_INPUT
} stb_gui_event_type;

// Mouse button types
typedef enum {
    STB_GUI_MOUSE_LEFT,
    STB_GUI_MOUSE_RIGHT,
    STB_GUI_MOUSE_MIDDLE
} stb_gui_mouse_button;

// Key codes (subset of common keys)
typedef enum {
    STB_GUI_KEY_UNKNOWN = 0,
    STB_GUI_KEY_BACKSPACE = 8,
    STB_GUI_KEY_TAB = 9,
    STB_GUI_KEY_ENTER = 13,
    STB_GUI_KEY_ESCAPE = 27,
    STB_GUI_KEY_SPACE = 32,
    STB_GUI_KEY_LEFT = 37,
    STB_GUI_KEY_UP = 38,
    STB_GUI_KEY_RIGHT = 39,
    STB_GUI_KEY_DOWN = 40,
    STB_GUI_KEY_DELETE = 127,
    STB_GUI_KEY_0 = 48,
    STB_GUI_KEY_1 = 49,
    STB_GUI_KEY_2 = 50,
    STB_GUI_KEY_3 = 51,
    STB_GUI_KEY_4 = 52,
    STB_GUI_KEY_5 = 53,
    STB_GUI_KEY_6 = 54,
    STB_GUI_KEY_7 = 55,
    STB_GUI_KEY_8 = 56,
    STB_GUI_KEY_9 = 57,
    STB_GUI_KEY_A = 65,
    STB_GUI_KEY_B = 66,
    STB_GUI_KEY_C = 67,
    STB_GUI_KEY_D = 68,
    STB_GUI_KEY_E = 69,
    STB_GUI_KEY_F = 70,
    STB_GUI_KEY_G = 71,
    STB_GUI_KEY_H = 72,
    STB_GUI_KEY_I = 73,
    STB_GUI_KEY_J = 74,
    STB_GUI_KEY_K = 75,
    STB_GUI_KEY_L = 76,
    STB_GUI_KEY_M = 77,
    STB_GUI_KEY_N = 78,
    STB_GUI_KEY_O = 79,
    STB_GUI_KEY_P = 80,
    STB_GUI_KEY_Q = 81,
    STB_GUI_KEY_R = 82,
    STB_GUI_KEY_S = 83,
    STB_GUI_KEY_T = 84,
    STB_GUI_KEY_U = 85,
    STB_GUI_KEY_V = 86,
    STB_GUI_KEY_W = 87,
    STB_GUI_KEY_X = 88,
    STB_GUI_KEY_Y = 89,
    STB_GUI_KEY_Z = 90
} stb_gui_key;

// Event structures
typedef struct {
    stb_gui_mouse_button button;
    float x, y;
} stb_gui_mouse_event;

typedef struct {
    stb_gui_key key;
    int mods;
} stb_gui_key_event;

typedef struct {
    const char* text;
} stb_gui_text_event;

typedef struct {
    stb_gui_event_type type;
    union {
        stb_gui_mouse_event mouse;
        stb_gui_key_event key;
        stb_gui_text_event text;
    } data;
} stb_gui_event;

// Widget callback functions
typedef void (*stb_gui_button_callback)(stb_gui_widget widget, void* userdata);
typedef void (*stb_gui_slider_callback)(stb_gui_widget widget, float value, void* userdata);
typedef void (*stb_gui_textbox_callback)(stb_gui_widget widget, const char* text, void* userdata);
typedef void (*stb_gui_checkbox_callback)(stb_gui_widget widget, int checked, void* userdata);
typedef void (*stb_gui_radiobutton_callback)(stb_gui_widget widget, int selected, void* userdata);
typedef void (*stb_gui_dropdown_callback)(stb_gui_widget widget, int selected_index, void* userdata);

// Button creation parameters
typedef struct {
    const char* text;
    stb_gui_rect rect;
    stb_gui_button_callback callback;
    void* userdata;
    int enabled;
} stb_gui_button_params;

// Slider creation parameters
typedef struct {
    stb_gui_rect rect;
    float min_value;
    float max_value;
    float initial_value;
    stb_gui_slider_callback callback;
    void* userdata;
    int enabled;
} stb_gui_slider_params;

// Text box creation parameters
typedef struct {
    stb_gui_rect rect;
    const char* initial_text;
    int max_length;
    stb_gui_textbox_callback callback;
    void* userdata;
    int enabled;
} stb_gui_textbox_params;

// Label creation parameters
typedef struct {
    const char* text;
    stb_gui_rect rect;
    stb_gui_color color;
    float font_size;
} stb_gui_label_params;

// Checkbox creation parameters
typedef struct {
    const char* text;
    stb_gui_rect rect;
    int initial_checked;
    stb_gui_checkbox_callback callback;
    void* userdata;
    int enabled;
} stb_gui_checkbox_params;

// Radiobutton creation parameters
typedef struct {
    const char* text;
    stb_gui_rect rect;
    int group_id;
    int initial_selected;
    stb_gui_radiobutton_callback callback;
    void* userdata;
    int enabled;
} stb_gui_radiobutton_params;

// Dropdown creation parameters
typedef struct {
    stb_gui_rect rect;
    const char** items;
    int num_items;
    int initial_selected;
    stb_gui_dropdown_callback callback;
    void* userdata;
    int enabled;
} stb_gui_dropdown_params;

// Default colors
extern const stb_gui_color stb_gui_color_white;
extern const stb_gui_color stb_gui_color_black;
extern const stb_gui_color stb_gui_color_gray;
extern const stb_gui_color stb_gui_color_light_gray;
extern const stb_gui_color stb_gui_color_dark_gray;
extern const stb_gui_color stb_gui_color_red;
extern const stb_gui_color stb_gui_color_green;
extern const stb_gui_color stb_gui_color_blue;
extern const stb_gui_color stb_gui_color_transparent;

// Default font (null implementation)
extern const stb_gui_font stb_gui_default_font;

// Initialize GUI system
void stb_gui_init(stb_gui_render_rect_func render_rect, stb_gui_render_text_func render_text, const stb_gui_font* font, void* userdata);

// Shutdown GUI system
void stb_gui_shutdown(void);

// Create widgets
stb_gui_widget stb_gui_create_button(const stb_gui_button_params* params);
stb_gui_widget stb_gui_create_slider(const stb_gui_slider_params* params);
stb_gui_widget stb_gui_create_textbox(const stb_gui_textbox_params* params);
stb_gui_widget stb_gui_create_label(const stb_gui_label_params* params);
stb_gui_widget stb_gui_create_checkbox(const stb_gui_checkbox_params* params);
stb_gui_widget stb_gui_create_radiobutton(const stb_gui_radiobutton_params* params);
stb_gui_widget stb_gui_create_dropdown(const stb_gui_dropdown_params* params);

// Destroy widget
void stb_gui_destroy_widget(stb_gui_widget widget);

// Process input events
int stb_gui_process_event(const stb_gui_event* event);

// Render all widgets
void stb_gui_render(void);

// Widget manipulation functions
void stb_gui_set_widget_rect(stb_gui_widget widget, stb_gui_rect rect);
stb_gui_rect stb_gui_get_widget_rect(stb_gui_widget widget);

void stb_gui_set_widget_enabled(stb_gui_widget widget, int enabled);
int stb_gui_get_widget_enabled(stb_gui_widget widget);

void stb_gui_set_widget_visible(stb_gui_widget widget, int visible);
int stb_gui_get_widget_visible(stb_gui_widget widget);

// Button specific functions
void stb_gui_set_button_text(stb_gui_widget widget, const char* text);
const char* stb_gui_get_button_text(stb_gui_widget widget);

// Slider specific functions
void stb_gui_set_slider_value(stb_gui_widget widget, float value);
float stb_gui_get_slider_value(stb_gui_widget widget);

void stb_gui_set_slider_range(stb_gui_widget widget, float min_value, float max_value);

// Text box specific functions
void stb_gui_set_textbox_text(stb_gui_widget widget, const char* text);
const char* stb_gui_get_textbox_text(stb_gui_widget widget);

// Label specific functions
void stb_gui_set_label_text(stb_gui_widget widget, const char* text);
const char* stb_gui_get_label_text(stb_gui_widget widget);

void stb_gui_set_label_color(stb_gui_widget widget, stb_gui_color color);
stb_gui_color stb_gui_get_label_color(stb_gui_widget widget);

// Checkbox specific functions
void stb_gui_set_checkbox_checked(stb_gui_widget widget, int checked);
int stb_gui_get_checkbox_checked(stb_gui_widget widget);

// Radiobutton specific functions
void stb_gui_set_radiobutton_selected(stb_gui_widget widget, int selected);
int stb_gui_get_radiobutton_selected(stb_gui_widget widget);

// Dropdown specific functions
void stb_gui_set_dropdown_selected(stb_gui_widget widget, int index);
int stb_gui_get_dropdown_selected(stb_gui_widget widget);

#ifdef __cplusplus
}
#endif

#endif // STB_GUI_WIDGETS_H

#ifdef STB_GUI_WIDGETS_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef STB_GUI_ASSERT
#define STB_GUI_ASSERT(x) assert(x)
#endif

#ifndef STB_GUI_MALLOC
#define STB_GUI_MALLOC malloc
#endif

#ifndef STB_GUI_REALLOC
#define STB_GUI_REALLOC realloc
#endif

#ifndef STB_GUI_FREE
#define STB_GUI_FREE free
#endif

// Default colors
const stb_gui_color stb_gui_color_white = { 1.0f, 1.0f, 1.0f, 1.0f };
const stb_gui_color stb_gui_color_black = { 0.0f, 0.0f, 0.0f, 1.0f };
const stb_gui_color stb_gui_color_gray = { 0.5f, 0.5f, 0.5f, 1.0f };
const stb_gui_color stb_gui_color_light_gray = { 0.75f, 0.75f, 0.75f, 1.0f };
const stb_gui_color stb_gui_color_dark_gray = { 0.25f, 0.25f, 0.25f, 1.0f };
const stb_gui_color stb_gui_color_red = { 1.0f, 0.0f, 0.0f, 1.0f };
const stb_gui_color stb_gui_color_green = { 0.0f, 1.0f, 0.0f, 1.0f };
const stb_gui_color stb_gui_color_blue = { 0.0f, 0.0f, 1.0f, 1.0f };
const stb_gui_color stb_gui_color_transparent = { 0.0f, 0.0f, 0.0f, 0.0f };

// Default font implementation (does nothing)
static float stb_gui_default_get_text_width(const char* text, float size) {
    (void)text; (void)size; // Unused parameters
    return 0.0f;
}

static void stb_gui_default_render_text(const char* text, float x, float y, float size, stb_gui_color color) {
    (void)text; (void)x; (void)y; (void)size; (void)color; // Unused parameters
}

const stb_gui_font stb_gui_default_font = {
    stb_gui_default_get_text_width,
    stb_gui_default_render_text
};

// GUI context
typedef struct {
    stb_gui_render_rect_func render_rect;
    stb_gui_render_text_func render_text;
    const stb_gui_font* font;
    void* userdata;
    stb_gui_widget* widgets;
    int num_widgets;
    int max_widgets;
    stb_gui_widget focused_widget;
    float mouse_x, mouse_y;
    int mouse_buttons[3];
} stb_gui_context;

static stb_gui_context g_gui_context;

// Internal widget structure
typedef struct {
    stb_gui_widget_type type;
    stb_gui_rect rect;
    int enabled;
    int visible;
    stb_gui_widget_state state;
    void* data;
} stb_gui_widget_impl;

// Internal widget data structures
typedef struct {
    char* text;
    stb_gui_button_callback callback;
    void* userdata;
} stb_gui_button_data;

typedef struct {
    float min_value;
    float max_value;
    float value;
    stb_gui_slider_callback callback;
    void* userdata;
} stb_gui_slider_data;

typedef struct {
    char* text;
    int max_length;
    stb_gui_textbox_callback callback;
    void* userdata;
    int cursor_pos;
    int selection_start;
    int selection_end;
    int editing;
} stb_gui_textbox_data;

typedef struct {
    char* text;
    stb_gui_color color;
    float font_size;
} stb_gui_label_data;

typedef struct {
    char* text;
    int checked;
    stb_gui_checkbox_callback callback;
    void* userdata;
} stb_gui_checkbox_data;

typedef struct {
    char* text;
    int group_id;
    int selected;
    stb_gui_radiobutton_callback callback;
    void* userdata;
} stb_gui_radiobutton_data;

typedef struct {
    const char** items;
    int num_items;
    int selected_index;
    stb_gui_dropdown_callback callback;
    void* userdata;
    int opened;
} stb_gui_dropdown_data;

// Initialize GUI system
void stb_gui_init(stb_gui_render_rect_func render_rect, stb_gui_render_text_func render_text, const stb_gui_font* font, void* userdata) {
    memset(&g_gui_context, 0, sizeof(g_gui_context));
    g_gui_context.render_rect = render_rect;
    g_gui_context.render_text = render_text;
    g_gui_context.font = font ? font : &stb_gui_default_font;
    g_gui_context.userdata = userdata;
    g_gui_context.num_widgets = 0;
    g_gui_context.max_widgets = 0;
    g_gui_context.widgets = NULL;
    g_gui_context.focused_widget = NULL;
    g_gui_context.mouse_x = 0.0f;
    g_gui_context.mouse_y = 0.0f;
    memset(g_gui_context.mouse_buttons, 0, sizeof(g_gui_context.mouse_buttons));
}

// Shutdown GUI system
void stb_gui_shutdown(void) {
    for (int i = 0; i < g_gui_context.num_widgets; ++i) {
        stb_gui_widget_impl* widget = &g_gui_context.widgets[i];
        if (widget->data) {
            switch (widget->type) {
                case STB_GUI_BUTTON:
                    STB_GUI_FREE(((stb_gui_button_data*)widget->data)->text);
                    break;
                case STB_GUI_SLIDER:
                    break;
                case STB_GUI_TEXTBOX:
                    STB_GUI_FREE(((stb_gui_textbox_data*)widget->data)->text);
                    break;
                case STB_GUI_LABEL:
                    STB_GUI_FREE(((stb_gui_label_data*)widget->data)->text);
                    break;
                case STB_GUI_CHECKBOX:
                    STB_GUI_FREE(((stb_gui_checkbox_data*)widget->data)->text);
                    break;
                case STB_GUI_RADIOBUTTON:
                    STB_GUI_FREE(((stb_gui_radiobutton_data*)widget->data)->text);
                    break;
                case STB_GUI_DROPDOWN:
                    break;
            }
            STB_GUI_FREE(widget->data);
        }
    }
    STB_GUI_FREE(g_gui_context.widgets);
    memset(&g_gui_context, 0, sizeof(g_gui_context));
}

// Create widget helper function
static stb_gui_widget stb_gui_create_widget(stb_gui_widget_type type, void* data) {
    if (g_gui_context.num_widgets >= g_gui_context.max_widgets) {
        int new_max = g_gui_context.max_widgets == 0 ? 16 : g_gui_context.max_widgets * 2;
        stb_gui_widget_impl* new_widgets = (stb_gui_widget_impl*)STB_GUI_REALLOC(g_gui_context.widgets, new_max * sizeof(stb_gui_widget_impl));
        if (new_widgets == NULL) return NULL;
        g_gui_context.widgets = new_widgets;
        g_gui_context.max_widgets = new_max;
    }
    
    stb_gui_widget_impl* widget = &g_gui_context.widgets[g_gui_context.num_widgets];
    widget->type = type;
    widget->rect = (stb_gui_rect){0, 0, 0, 0};
    widget->enabled = 1;
    widget->visible = 1;
    widget->state = STB_GUI_NORMAL;
    widget->data = data;
    
    g_gui_context.num_widgets++;
    return (stb_gui_widget)widget;
}

// Create button
stb_gui_widget stb_gui_create_button(const stb_gui_button_params* params) {
    STB_GUI_ASSERT(params != NULL);
    
    stb_gui_button_data* data = (stb_gui_button_data*)STB_GUI_MALLOC(sizeof(stb_gui_button_data));
    if (data == NULL) return NULL;
    
    data->text = params->text ? strdup(params->text) : strdup("");
    data->callback = params->callback;
    data->userdata = params->userdata;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_BUTTON, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data->text);
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create slider
stb_gui_widget stb_gui_create_slider(const stb_gui_slider_params* params) {
    STB_GUI_ASSERT(params != NULL);
    STB_GUI_ASSERT(params->max_value > params->min_value);
    
    stb_gui_slider_data* data = (stb_gui_slider_data*)STB_GUI_MALLOC(sizeof(stb_gui_slider_data));
    if (data == NULL) return NULL;
    
    data->min_value = params->min_value;
    data->max_value = params->max_value;
    data->value = params->initial_value;
    if (data->value < data->min_value) data->value = data->min_value;
    if (data->value > data->max_value) data->value = data->max_value;
    data->callback = params->callback;
    data->userdata = params->userdata;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_SLIDER, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create text box
stb_gui_widget stb_gui_create_textbox(const stb_gui_textbox_params* params) {
    STB_GUI_ASSERT(params != NULL);
    STB_GUI_ASSERT(params->max_length > 0);
    
    stb_gui_textbox_data* data = (stb_gui_textbox_data*)STB_GUI_MALLOC(sizeof(stb_gui_textbox_data));
    if (data == NULL) return NULL;
    
    data->text = (char*)STB_GUI_MALLOC((params->max_length + 1) * sizeof(char));
    if (data->text == NULL) {
        STB_GUI_FREE(data);
        return NULL;
    }
    
    if (params->initial_text) {
        strncpy(data->text, params->initial_text, params->max_length);
    } else {
        data->text[0] = '\0';
    }
    data->text[params->max_length] = '\0';
    data->max_length = params->max_length;
    data->callback = params->callback;
    data->userdata = params->userdata;
    data->cursor_pos = strlen(data->text);
    data->selection_start = 0;
    data->selection_end = data->cursor_pos;
    data->editing = 0;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_TEXTBOX, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data->text);
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create label
stb_gui_widget stb_gui_create_label(const stb_gui_label_params* params) {
    STB_GUI_ASSERT(params != NULL);
    
    stb_gui_label_data* data = (stb_gui_label_data*)STB_GUI_MALLOC(sizeof(stb_gui_label_data));
    if (data == NULL) return NULL;
    
    data->text = params->text ? strdup(params->text) : strdup("");
    data->color = params->color;
    data->font_size = params->font_size;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_LABEL, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
    } else {
        STB_GUI_FREE(data->text);
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create checkbox
stb_gui_widget stb_gui_create_checkbox(const stb_gui_checkbox_params* params) {
    STB_GUI_ASSERT(params != NULL);
    
    stb_gui_checkbox_data* data = (stb_gui_checkbox_data*)STB_GUI_MALLOC(sizeof(stb_gui_checkbox_data));
    if (data == NULL) return NULL;
    
    data->text = params->text ? strdup(params->text) : strdup("");
    data->checked = params->initial_checked;
    data->callback = params->callback;
    data->userdata = params->userdata;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_CHECKBOX, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data->text);
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create radiobutton
stb_gui_widget stb_gui_create_radiobutton(const stb_gui_radiobutton_params* params) {
    STB_GUI_ASSERT(params != NULL);
    
    stb_gui_radiobutton_data* data = (stb_gui_radiobutton_data*)STB_GUI_MALLOC(sizeof(stb_gui_radiobutton_data));
    if (data == NULL) return NULL;
    
    data->text = params->text ? strdup(params->text) : strdup("");
    data->group_id = params->group_id;
    data->selected = params->initial_selected;
    data->callback = params->callback;
    data->userdata = params->userdata;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_RADIOBUTTON, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data->text);
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Create dropdown
stb_gui_widget stb_gui_create_dropdown(const stb_gui_dropdown_params* params) {
    STB_GUI_ASSERT(params != NULL);
    STB_GUI_ASSERT(params->items != NULL);
    STB_GUI_ASSERT(params->num_items > 0);
    
    stb_gui_dropdown_data* data = (stb_gui_dropdown_data*)STB_GUI_MALLOC(sizeof(stb_gui_dropdown_data));
    if (data == NULL) return NULL;
    
    data->items = params->items;
    data->num_items = params->num_items;
    data->selected_index = params->initial_selected;
    if (data->selected_index < 0) data->selected_index = 0;
    if (data->selected_index >= data->num_items) data->selected_index = data->num_items - 1;
    data->callback = params->callback;
    data->userdata = params->userdata;
    data->opened = 0;
    
    stb_gui_widget widget = stb_gui_create_widget(STB_GUI_DROPDOWN, data);
    if (widget) {
        stb_gui_set_widget_rect(widget, params->rect);
        stb_gui_set_widget_enabled(widget, params->enabled);
    } else {
        STB_GUI_FREE(data);
    }
    
    return widget;
}

// Destroy widget
void stb_gui_destroy_widget(stb_gui_widget widget) {
    if (widget == NULL) return;
    
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    
    // Find widget index
    int index = -1;
    for (int i = 0; i < g_gui_context.num_widgets; ++i) {
        if (&g_gui_context.widgets[i] == impl) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return;
    
    // Free widget data
    if (impl->data) {
        switch (impl->type) {
            case STB_GUI_BUTTON:
                STB_GUI_FREE(((stb_gui_button_data*)impl->data)->text);
                break;
            case STB_GUI_SLIDER:
                break;
            case STB_GUI_TEXTBOX:
                STB_GUI_FREE(((stb_gui_textbox_data*)impl->data)->text);
                break;
            case STB_GUI_LABEL:
                STB_GUI_FREE(((stb_gui_label_data*)impl->data)->text);
                break;
            case STB_GUI_CHECKBOX:
                STB_GUI_FREE(((stb_gui_checkbox_data*)impl->data)->text);
                break;
            case STB_GUI_RADIOBUTTON:
                STB_GUI_FREE(((stb_gui_radiobutton_data*)impl->data)->text);
                break;
            case STB_GUI_DROPDOWN:
                break;
        }
        STB_GUI_FREE(impl->data);
    }
    
    // Remove widget from array
    g_gui_context.num_widgets--;
    if (index < g_gui_context.num_widgets) {
        memmove(&g_gui_context.widgets[index], &g_gui_context.widgets[index + 1], 
               (g_gui_context.num_widgets - index) * sizeof(stb_gui_widget_impl));
    }
    
    // Update focused widget if necessary
    if (g_gui_context.focused_widget == widget) {
        g_gui_context.focused_widget = NULL;
    }
}

// Check if point is inside rect
static int stb_gui_point_in_rect(float x, float y, stb_gui_rect rect) {
    return x >= rect.x && x <= rect.x + rect.width && y >= rect.y && y <= rect.y + rect.height;
}

// Process input events
int stb_gui_process_event(const stb_gui_event* event) {
    STB_GUI_ASSERT(event != NULL);
    
    int handled = 0;
    
    switch (event->type) {
        case STB_GUI_MOUSE_DOWN:
            {
                float x = event->data.mouse.x;
                float y = event->data.mouse.y;
                int button = event->data.mouse.button;
                
                if (button >= 0 && button < 3) {
                    g_gui_context.mouse_buttons[button] = 1;
                }
                
                // Find topmost widget under mouse
                stb_gui_widget clicked_widget = NULL;
                for (int i = g_gui_context.num_widgets - 1; i >= 0; --i) {
                    stb_gui_widget_impl* widget = &g_gui_context.widgets[i];
                    if (widget->visible && widget->enabled && stb_gui_point_in_rect(x, y, widget->rect)) {
                        clicked_widget = (stb_gui_widget)widget;
                        break;
                    }
                }
                
                if (clicked_widget) {
                    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)clicked_widget;
                    
                    // Update widget state
                    impl->state = STB_GUI_PRESSED;
                    
                    // Handle specific widget types
                    switch (impl->type) {
                        case STB_GUI_BUTTON:
                            {
                                stb_gui_button_data* data = (stb_gui_button_data*)impl->data;
                                if (data->callback) {
                                    data->callback(clicked_widget, data->userdata);
                                }
                                handled = 1;
                            }
                            break;
                        case STB_GUI_SLIDER:
                            {
                                stb_gui_slider_data* data = (stb_gui_slider_data*)impl->data;
                                // Calculate slider value based on mouse position
                                float normalized = (x - impl->rect.x) / impl->rect.width;
                                if (normalized < 0.0f) normalized = 0.0f;
                                if (normalized > 1.0f) normalized = 1.0f;
                                data->value = data->min_value + normalized * (data->max_value - data->min_value);
                                if (data->callback) {
                                    data->callback(clicked_widget, data->value, data->userdata);
                                }
                                handled = 1;
                            }
                            break;
                        case STB_GUI_TEXTBOX:
                            {
                                stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
                                data->editing = 1;
                                g_gui_context.focused_widget = clicked_widget;
                                handled = 1;
                            }
                            break;
                        case STB_GUI_CHECKBOX:
                            {
                                stb_gui_checkbox_data* data = (stb_gui_checkbox_data*)impl->data;
                                data->checked = !data->checked;
                                if (data->callback) {
                                    data->callback(clicked_widget, data->checked, data->userdata);
                                }
                                handled = 1;
                            }
                            break;
                        case STB_GUI_RADIOBUTTON:
                            {
                                stb_gui_radiobutton_data* data = (stb_gui_radiobutton_data*)impl->data;
                                data->selected = 1;
                                
                                // Deselect other radiobuttons in the same group
                                for (int i = 0; i < g_gui_context.num_widgets; ++i) {
                                    if (&g_gui_context.widgets[i] != impl && 
                                        g_gui_context.widgets[i].type == STB_GUI_RADIOBUTTON) {
                                        stb_gui_radiobutton_data* other_data = (stb_gui_radiobutton_data*)g_gui_context.widgets[i].data;
                                        if (other_data->group_id == data->group_id) {
                                            other_data->selected = 0;
                                        }
                                    }
                                }
                                
                                if (data->callback) {
                                    data->callback(clicked_widget, data->selected, data->userdata);
                                }
                                handled = 1;
                            }
                            break;
                        case STB_GUI_DROPDOWN:
                            {
                                stb_gui_dropdown_data* data = (stb_gui_dropdown_data*)impl->data;
                                data->opened = !data->opened;
                                handled = 1;
                            }
                            break;
                        default:
                            break;
                    }
                } else {
                    // Clicked outside any widget, unfocus text boxes
                    if (g_gui_context.focused_widget) {
                        stb_gui_widget_impl* impl = (stb_gui_widget_impl*)g_gui_context.focused_widget;
                        if (impl->type == STB_GUI_TEXTBOX) {
                            stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
                            data->editing = 0;
                        }
                        g_gui_context.focused_widget = NULL;
                    }
                }
            }
            break;
        case STB_GUI_MOUSE_UP:
            {
                int button = event->data.mouse.button;
                if (button >= 0 && button < 3) {
                    g_gui_context.mouse_buttons[button] = 0;
                }
                
                // Reset pressed state for all widgets
                for (int i = 0; i < g_gui_context.num_widgets; ++i) {
                    stb_gui_widget_impl* widget = &g_gui_context.widgets[i];
                    if (widget->state == STB_GUI_PRESSED) {
                        widget->state = STB_GUI_NORMAL;
                    }
                }
            }
            break;
        case STB_GUI_MOUSE_MOVE:
            {
                float x = event->data.mouse.x;
                float y = event->data.mouse.y;
                g_gui_context.mouse_x = x;
                g_gui_context.mouse_y = y;
                
                // Update hover state for all widgets
                for (int i = 0; i < g_gui_context.num_widgets; ++i) {
                    stb_gui_widget_impl* widget = &g_gui_context.widgets[i];
                    if (widget->visible && widget->enabled) {
                        if (stb_gui_point_in_rect(x, y, widget->rect)) {
                            if (widget->state == STB_GUI_NORMAL) {
                                widget->state = STB_GUI_HOVERED;
                            }
                        } else {
                            if (widget->state == STB_GUI_HOVERED) {
                                widget->state = STB_GUI_NORMAL;
                            }
                        }
                    }
                }
            }
            break;
        case STB_GUI_KEY_DOWN:
            {
                stb_gui_key key = event->data.key.key;
                int mods = event->data.key.mods;
                
                if (g_gui_context.focused_widget) {
                    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)g_gui_context.focused_widget;
                    if (impl->type == STB_GUI_TEXTBOX) {
                        stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
                        
                        // Handle text editing keys
                        if (key == STB_GUI_KEY_BACKSPACE && data->cursor_pos > 0) {
                            memmove(&data->text[data->cursor_pos - 1], &data->text[data->cursor_pos], 
                                   strlen(&data->text[data->cursor_pos]) + 1);
                            data->cursor_pos--;
                            data->selection_start = data->selection_end = data->cursor_pos;
                            if (data->callback) {
                                data->callback(g_gui_context.focused_widget, data->text, data->userdata);
                            }
                            handled = 1;
                        } else if (key == STB_GUI_KEY_DELETE && data->cursor_pos < strlen(data->text)) {
                            memmove(&data->text[data->cursor_pos], &data->text[data->cursor_pos + 1], 
                                   strlen(&data->text[data->cursor_pos + 1]) + 1);
                            data->selection_start = data->selection_end = data->cursor_pos;
                            if (data->callback) {
                                data->callback(g_gui_context.focused_widget, data->text, data->userdata);
                            }
                            handled = 1;
                        } else if (key == STB_GUI_KEY_LEFT && data->cursor_pos > 0) {
                            data->cursor_pos--;
                            data->selection_start = data->selection_end = data->cursor_pos;
                            handled = 1;
                        } else if (key == STB_GUI_KEY_RIGHT && data->cursor_pos < strlen(data->text)) {
                            data->cursor_pos++;
                            data->selection_start = data->selection_end = data->cursor_pos;
                            handled = 1;
                        }
                    }
                }
            }
            break;
        case STB_GUI_KEY_UP:
            break;
        case STB_GUI_TEXT_INPUT:
            {
                const char* text = event->data.text.text;
                if (g_gui_context.focused_widget) {
                    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)g_gui_context.focused_widget;
                    if (impl->type == STB_GUI_TEXTBOX) {
                        stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
                        int len = strlen(data->text);
                        int text_len = strlen(text);
                        
                        if (len + text_len <= data->max_length) {
                            // Insert text at cursor position
                            memmove(&data->text[data->cursor_pos + text_len], &data->text[data->cursor_pos], 
                                   len - data->cursor_pos + 1);
                            memcpy(&data->text[data->cursor_pos], text, text_len);
                            data->cursor_pos += text_len;
                            data->selection_start = data->selection_end = data->cursor_pos;
                            
                            if (data->callback) {
                                data->callback(g_gui_context.focused_widget, data->text, data->userdata);
                            }
                            handled = 1;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    
    return handled;
}

// Render all widgets
void stb_gui_render(void) {
    for (int i = 0; i < g_gui_context.num_widgets; ++i) {
        stb_gui_widget_impl* widget = &g_gui_context.widgets[i];
        if (!widget->visible) continue;
        
        stb_gui_color bg_color = stb_gui_color_gray;
        stb_gui_color fg_color = stb_gui_color_white;
        
        // Determine colors based on widget state
        if (!widget->enabled) {
            bg_color = stb_gui_color_dark_gray;
            fg_color = stb_gui_color_light_gray;
        } else {
            switch (widget->state) {
                case STB_GUI_NORMAL:
                    bg_color = stb_gui_color_gray;
                    fg_color = stb_gui_color_white;
                    break;
                case STB_GUI_HOVERED:
                    bg_color = stb_gui_color_light_gray;
                    fg_color = stb_gui_color_black;
                    break;
                case STB_GUI_PRESSED:
                    bg_color = stb_gui_color_dark_gray;
                    fg_color = stb_gui_color_white;
                    break;
                case STB_GUI_FOCUSED:
                    bg_color = stb_gui_color_blue;
                    fg_color = stb_gui_color_white;
                    break;
                default:
                    break;
            }
        }
        
        // Render widget based on type
        switch (widget->type) {
            case STB_GUI_BUTTON:
                {
                    stb_gui_button_data* data = (stb_gui_button_data*)widget->data;
                    
                    // Render button background
                    g_gui_context.render_rect(widget->rect, bg_color, g_gui_context.userdata);
                    
                    // Render button text
                    if (data->text && strlen(data->text) > 0) {
                        float text_width = g_gui_context.font->get_text_width(data->text, 16.0f);
                        float text_x = widget->rect.x + (widget->rect.width - text_width) / 2;
                        float text_y = widget->rect.y + (widget->rect.height - 16.0f) / 2;
                        g_gui_context.render_text(data->text, text_x, text_y, 16.0f, fg_color, g_gui_context.userdata);
                    }
                }
                break;
            case STB_GUI_SLIDER:
                {
                    stb_gui_slider_data* data = (stb_gui_slider_data*)widget->data;
                    
                    // Render slider background
                    g_gui_context.render_rect(widget->rect, bg_color, g_gui_context.userdata);
                    
                    // Calculate slider position
                    float normalized = (data->value - data->min_value) / (data->max_value - data->min_value);
                    if (normalized < 0.0f) normalized = 0.0f;
                    if (normalized > 1.0f) normalized = 1.0f;
                    float slider_pos = widget->rect.x + normalized * widget->rect.width;
                    
                    // Render slider thumb
                    stb_gui_rect thumb_rect = { slider_pos - 5.0f, widget->rect.y, 10.0f, widget->rect.height };
                    g_gui_context.render_rect(thumb_rect, fg_color, g_gui_context.userdata);
                }
                break;
            case STB_GUI_TEXTBOX:
                {
                    stb_gui_textbox_data* data = (stb_gui_textbox_data*)widget->data;
                    
                    // Render text box background
                    g_gui_context.render_rect(widget->rect, bg_color, g_gui_context.userdata);
                    
                    // Render text
                    if (data->text && strlen(data->text) > 0) {
                        float text_x = widget->rect.x + 5.0f;
                        float text_y = widget->rect.y + (widget->rect.height - 16.0f) / 2;
                        g_gui_context.render_text(data->text, text_x, text_y, 16.0f, fg_color, g_gui_context.userdata);
                    }
                }
                break;
            case STB_GUI_LABEL:
                {
                    stb_gui_label_data* data = (stb_gui_label_data*)widget->data;
                    
                    // Render label text
                    if (data->text && strlen(data->text) > 0) {
                        float text_x = widget->rect.x;
                        float text_y = widget->rect.y + (widget->rect.height - data->font_size) / 2;
                        g_gui_context.render_text(data->text, text_x, text_y, data->font_size, data->color, g_gui_context.userdata);
                    }
                }
                break;
            case STB_GUI_CHECKBOX:
                {
                    stb_gui_checkbox_data* data = (stb_gui_checkbox_data*)widget->data;
                    
                    // Render checkbox background
                    stb_gui_rect checkbox_rect = { widget->rect.x, widget->rect.y, 16.0f, 16.0f };
                    g_gui_context.render_rect(checkbox_rect, bg_color, g_gui_context.userdata);
                    
                    // Render checkmark if checked
                    if (data->checked) {
                        stb_gui_color check_color = fg_color;
                        g_gui_context.render_text("x", widget->rect.x + 2.0f, widget->rect.y + 1.0f, 14.0f, check_color, g_gui_context.userdata);
                    }
                    
                    // Render checkbox text
                    if (data->text && strlen(data->text) > 0) {
                        float text_x = widget->rect.x + 25.0f;
                        float text_y = widget->rect.y + (widget->rect.height - 16.0f) / 2;
                        g_gui_context.render_text(data->text, text_x, text_y, 16.0f, fg_color, g_gui_context.userdata);
                    }
                }
                break;
            case STB_GUI_RADIOBUTTON:
                {
                    stb_gui_radiobutton_data* data = (stb_gui_radiobutton_data*)widget->data;
                    
                    // Render radio button background
                    stb_gui_rect radio_rect = { widget->rect.x, widget->rect.y, 16.0f, 16.0f };
                    g_gui_context.render_rect(radio_rect, bg_color, g_gui_context.userdata);
                    
                    // Render radio dot if selected
                    if (data->selected) {
                        stb_gui_rect dot_rect = { widget->rect.x + 4.0f, widget->rect.y + 4.0f, 8.0f, 8.0f };
                        g_gui_context.render_rect(dot_rect, fg_color, g_gui_context.userdata);
                    }
                    
                    // Render radio button text
                    if (data->text && strlen(data->text) > 0) {
                        float text_x = widget->rect.x + 25.0f;
                        float text_y = widget->rect.y + (widget->rect.height - 16.0f) / 2;
                        g_gui_context.render_text(data->text, text_x, text_y, 16.0f, fg_color, g_gui_context.userdata);
                    }
                }
                break;
            case STB_GUI_DROPDOWN:
                {
                    stb_gui_dropdown_data* data = (stb_gui_dropdown_data*)widget->data;
                    
                    // Render dropdown background
                    g_gui_context.render_rect(widget->rect, bg_color, g_gui_context.userdata);
                    
                    // Render selected item text
                    if (data->selected_index >= 0 && data->selected_index < data->num_items) {
                        const char* text = data->items[data->selected_index];
                        if (text && strlen(text) > 0) {
                            float text_width = g_gui_context.font->get_text_width(text, 16.0f);
                            float text_x = widget->rect.x + 5.0f;
                            float text_y = widget->rect.y + (widget->rect.height - 16.0f) / 2;
                            g_gui_context.render_text(text, text_x, text_y, 16.0f, fg_color, g_gui_context.userdata);
                        }
                    }
                    
                    // Render dropdown arrow
                    g_gui_context.render_text(">", widget->rect.x + widget->rect.width - 20.0f, widget->rect.y + (widget->rect.height - 16.0f) / 2, 16.0f, fg_color, g_gui_context.userdata);
                    
                    // Render dropdown items if opened
                    if (data->opened) {
                        for (int j = 0; j < data->num_items; ++j) {
                            stb_gui_rect item_rect = {
                                widget->rect.x,
                                widget->rect.y + widget->rect.height + j * 25.0f,
                                widget->rect.width,
                                25.0f
                            };
                            
                            stb_gui_color item_color = j == data->selected_index ? stb_gui_color_blue : stb_gui_color_gray;
                            g_gui_context.render_rect(item_rect, item_color, g_gui_context.userdata);
                            
                            const char* text = data->items[j];
                            if (text && strlen(text) > 0) {
                                float text_x = item_rect.x + 5.0f;
                                float text_y = item_rect.y + (item_rect.height - 16.0f) / 2;
                                g_gui_context.render_text(text, text_x, text_y, 16.0f, stb_gui_color_white, g_gui_context.userdata);
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}

// Widget manipulation functions
void stb_gui_set_widget_rect(stb_gui_widget widget, stb_gui_rect rect) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    impl->rect = rect;
}

stb_gui_rect stb_gui_get_widget_rect(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    return impl->rect;
}

void stb_gui_set_widget_enabled(stb_gui_widget widget, int enabled) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    impl->enabled = enabled;
}

int stb_gui_get_widget_enabled(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    return impl->enabled;
}

void stb_gui_set_widget_visible(stb_gui_widget widget, int visible) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    impl->visible = visible;
}

int stb_gui_get_widget_visible(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    return impl->visible;
}

// Button specific functions
void stb_gui_set_button_text(stb_gui_widget widget, const char* text) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_BUTTON);
    stb_gui_button_data* data = (stb_gui_button_data*)impl->data;
    
    if (data->text) {
        STB_GUI_FREE(data->text);
    }
    data->text = text ? strdup(text) : strdup("");
}

const char* stb_gui_get_button_text(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_BUTTON);
    stb_gui_button_data* data = (stb_gui_button_data*)impl->data;
    return data->text;
}

// Slider specific functions
void stb_gui_set_slider_value(stb_gui_widget widget, float value) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_SLIDER);
    stb_gui_slider_data* data = (stb_gui_slider_data*)impl->data;
    
    data->value = value;
    if (data->value < data->min_value) data->value = data->min_value;
    if (data->value > data->max_value) data->value = data->max_value;
}

float stb_gui_get_slider_value(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_SLIDER);
    stb_gui_slider_data* data = (stb_gui_slider_data*)impl->data;
    return data->value;
}

void stb_gui_set_slider_range(stb_gui_widget widget, float min_value, float max_value) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_SLIDER);
    stb_gui_slider_data* data = (stb_gui_slider_data*)impl->data;
    
    STB_GUI_ASSERT(max_value > min_value);
    data->min_value = min_value;
    data->max_value = max_value;
    
    if (data->value < data->min_value) data->value = data->min_value;
    if (data->value > data->max_value) data->value = data->max_value;
}

// Text box specific functions
void stb_gui_set_textbox_text(stb_gui_widget widget, const char* text) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_TEXTBOX);
    stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
    
    if (text) {
        strncpy(data->text, text, data->max_length);
    } else {
        data->text[0] = '\0';
    }
    data->text[data->max_length] = '\0';
    data->cursor_pos = strlen(data->text);
    data->selection_start = 0;
    data->selection_end = data->cursor_pos;
}

const char* stb_gui_get_textbox_text(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_TEXTBOX);
    stb_gui_textbox_data* data = (stb_gui_textbox_data*)impl->data;
    return data->text;
}

// Label specific functions
void stb_gui_set_label_text(stb_gui_widget widget, const char* text) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_LABEL);
    stb_gui_label_data* data = (stb_gui_label_data*)impl->data;
    
    if (data->text) {
        STB_GUI_FREE(data->text);
    }
    data->text = text ? strdup(text) : strdup("");
}

const char* stb_gui_get_label_text(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_LABEL);
    stb_gui_label_data* data = (stb_gui_label_data*)impl->data;
    return data->text;
}

void stb_gui_set_label_color(stb_gui_widget widget, stb_gui_color color) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_LABEL);
    stb_gui_label_data* data = (stb_gui_label_data*)impl->data;
    data->color = color;
}

stb_gui_color stb_gui_get_label_color(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_LABEL);
    stb_gui_label_data* data = (stb_gui_label_data*)impl->data;
    return data->color;
}

// Checkbox specific functions
void stb_gui_set_checkbox_checked(stb_gui_widget widget, int checked) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_CHECKBOX);
    stb_gui_checkbox_data* data = (stb_gui_checkbox_data*)impl->data;
    data->checked = checked;
}

int stb_gui_get_checkbox_checked(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_CHECKBOX);
    stb_gui_checkbox_data* data = (stb_gui_checkbox_data*)impl->data;
    return data->checked;
}

// Radiobutton specific functions
void stb_gui_set_radiobutton_selected(stb_gui_widget widget, int selected) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_RADIOBUTTON);
    stb_gui_radiobutton_data* data = (stb_gui_radiobutton_data*)impl->data;
    
    if (selected) {
        // Deselect other radiobuttons in the same group
        for (int i = 0; i < g_gui_context.num_widgets; ++i) {
            if (&g_gui_context.widgets[i] != impl && 
                g_gui_context.widgets[i].type == STB_GUI_RADIOBUTTON) {
                stb_gui_radiobutton_data* other_data = (stb_gui_radiobutton_data*)g_gui_context.widgets[i].data;
                if (other_data->group_id == data->group_id) {
                    other_data->selected = 0;
                }
            }
        }
        data->selected = 1;
    } else {
        data->selected = 0;
    }
}

int stb_gui_get_radiobutton_selected(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_RADIOBUTTON);
    stb_gui_radiobutton_data* data = (stb_gui_radiobutton_data*)impl->data;
    return data->selected;
}

// Dropdown specific functions
void stb_gui_set_dropdown_selected(stb_gui_widget widget, int index) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_DROPDOWN);
    stb_gui_dropdown_data* data = (stb_gui_dropdown_data*)impl->data;
    
    data->selected_index = index;
    if (data->selected_index < 0) data->selected_index = 0;
    if (data->selected_index >= data->num_items) data->selected_index = data->num_items - 1;
}

int stb_gui_get_dropdown_selected(stb_gui_widget widget) {
    STB_GUI_ASSERT(widget != NULL);
    stb_gui_widget_impl* impl = (stb_gui_widget_impl*)widget;
    STB_GUI_ASSERT(impl->type == STB_GUI_DROPDOWN);
    stb_gui_dropdown_data* data = (stb_gui_dropdown_data*)impl->data;
    return data->selected_index;
}

#endif // STB_GUI_WIDGETS_IMPLEMENTATION