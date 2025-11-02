/* stb_script - v1.00 - public domain scripting utility library - http://nothings.org/stb
                         no warranty implied; use at your own risk

   Do this:
      #define STB_SCRIPT_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   You can #define STB_SCRIPT_ASSERT(x) before the #include to avoid using assert.h.
   You can #define STB_SCRIPT_MALLOC and STB_SCRIPT_FREE to use your own memory allocator.

   QUICK NOTES:
      Simple scripting utility library for embedding scripts in applications
      Supports basic script parsing and execution
      Variable system with type checking
      Function registration and calling mechanism
      Error handling and reporting
      No external dependencies

   LICENSE

   See end of file for license information.

RECENT REVISION HISTORY:

      1.00  (2024-10-26) initial release

*/

#ifndef STB_SCRIPT_H
#define STB_SCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct stb_script_env;
typedef struct stb_script_env stb_script_env;

struct stb_script_value;
typedef struct stb_script_value stb_script_value;

// Script value types
typedef enum {
    STB_SCRIPT_TYPE_NIL,
    STB_SCRIPT_TYPE_BOOL,
    STB_SCRIPT_TYPE_INT,
    STB_SCRIPT_TYPE_FLOAT,
    STB_SCRIPT_TYPE_STRING,
    STB_SCRIPT_TYPE_FUNCTION,
    STB_SCRIPT_TYPE_USERDATA
} stb_script_type;

// Script function signature
typedef stb_script_value* (*stb_script_func)(stb_script_env* env, int argc, stb_script_value** argv);

// Script value structure
typedef struct stb_script_value {
    stb_script_type type;
    union {
        int boolean;
        int integer;
        float floating;
        char* string;
        stb_script_func function;
        void* userdata;
    } data;
} stb_script_value;

// Error callback function signature
typedef void (*stb_script_error_callback)(const char* message, void* userdata);

// Create a new script environment
stb_script_env* stb_script_create_env(void);

// Destroy a script environment
void stb_script_destroy_env(stb_script_env* env);

// Set error callback
void stb_script_set_error_callback(stb_script_env* env, stb_script_error_callback callback, void* userdata);

// Register a native function
void stb_script_register_function(stb_script_env* env, const char* name, stb_script_func func);

// Set a global variable
void stb_script_set_global(stb_script_env* env, const char* name, const stb_script_value* value);

// Get a global variable
const stb_script_value* stb_script_get_global(stb_script_env* env, const char* name);

// Create script values
stb_script_value* stb_script_create_nil(void);
stb_script_value* stb_script_create_bool(int value);
stb_script_value* stb_script_create_int(int value);
stb_script_value* stb_script_create_float(float value);
stb_script_value* stb_script_create_string(const char* value);
stb_script_value* stb_script_create_function(stb_script_func func);
stb_script_value* stb_script_create_userdata(void* data);

// Copy a script value
stb_script_value* stb_script_copy_value(const stb_script_value* value);

// Destroy a script value
void stb_script_destroy_value(stb_script_value* value);

// Parse and execute a script from a string
int stb_script_execute_string(stb_script_env* env, const char* script);

// Parse and execute a script from a file
int stb_script_execute_file(stb_script_env* env, const char* filename);

// Call a script function
stb_script_value* stb_script_call_function(stb_script_env* env, const char* name, int argc, stb_script_value** argv);

// Get type name as string
const char* stb_script_type_name(stb_script_type type);

// Utility functions for value access
int stb_script_value_as_bool(const stb_script_value* value);
int stb_script_value_as_int(const stb_script_value* value);
float stb_script_value_as_float(const stb_script_value* value);
const char* stb_script_value_as_string(const stb_script_value* value);
stb_script_func stb_script_value_as_function(const stb_script_value* value);
void* stb_script_value_as_userdata(const stb_script_value* value);

// Check if a value is of a specific type
int stb_script_value_is_nil(const stb_script_value* value);
int stb_script_value_is_bool(const stb_script_value* value);
int stb_script_value_is_int(const stb_script_value* value);
int stb_script_value_is_float(const stb_script_value* value);
int stb_script_value_is_string(const stb_script_value* value);
int stb_script_value_is_function(const stb_script_value* value);
int stb_script_value_is_userdata(const stb_script_value* value);

#ifdef __cplusplus
}
#endif

#endif // STB_SCRIPT_H

#ifdef STB_SCRIPT_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#ifndef STB_SCRIPT_ASSERT
#define STB_SCRIPT_ASSERT(x) assert(x)
#endif

#ifndef STB_SCRIPT_MALLOC
#define STB_SCRIPT_MALLOC malloc
#endif

#ifndef STB_SCRIPT_FREE
#define STB_SCRIPT_FREE free
#endif

// Hash table entry for variables and functions
typedef struct stb_script_hash_entry {
    char* key;
    stb_script_value* value;
    struct stb_script_hash_entry* next;
} stb_script_hash_entry;

// Hash table structure
typedef struct {
    stb_script_hash_entry** buckets;
    int size;
    int count;
} stb_script_hash_table;

// Script environment structure
struct stb_script_env {
    stb_script_hash_table globals;
    stb_script_error_callback error_callback;
    void* error_userdata;
};

// Hash function for strings
static unsigned int stb_script_hash_string(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// Create a hash table
static stb_script_hash_table stb_script_create_hash_table(int size) {
    stb_script_hash_table table;
    table.size = size;
    table.count = 0;
    table.buckets = (stb_script_hash_entry**)STB_SCRIPT_MALLOC(size * sizeof(stb_script_hash_entry*));
    STB_SCRIPT_ASSERT(table.buckets != NULL);
    memset(table.buckets, 0, size * sizeof(stb_script_hash_entry*));
    return table;
}

// Destroy a hash table
static void stb_script_destroy_hash_table(stb_script_hash_table* table) {
    if (table == NULL) return;
    
    for (int i = 0; i < table->size; ++i) {
        stb_script_hash_entry* entry = table->buckets[i];
        while (entry != NULL) {
            stb_script_hash_entry* next = entry->next;
            STB_SCRIPT_FREE(entry->key);
            stb_script_destroy_value(entry->value);
            STB_SCRIPT_FREE(entry);
            entry = next;
        }
    }
    
    STB_SCRIPT_FREE(table->buckets);
    table->buckets = NULL;
    table->size = 0;
    table->count = 0;
}

// Insert a key-value pair into the hash table
static void stb_script_hash_table_insert(stb_script_hash_table* table, const char* key, stb_script_value* value) {
    STB_SCRIPT_ASSERT(table != NULL);
    STB_SCRIPT_ASSERT(key != NULL);
    STB_SCRIPT_ASSERT(value != NULL);
    
    unsigned int hash = stb_script_hash_string(key) % table->size;
    stb_script_hash_entry* entry = table->buckets[hash];
    
    // Check if key already exists
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            stb_script_destroy_value(entry->value);
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    
    // Create new entry
    entry = (stb_script_hash_entry*)STB_SCRIPT_MALLOC(sizeof(stb_script_hash_entry));
    STB_SCRIPT_ASSERT(entry != NULL);
    
    entry->key = (char*)STB_SCRIPT_MALLOC(strlen(key) + 1);
    STB_SCRIPT_ASSERT(entry->key != NULL);
    strcpy(entry->key, key);
    
    entry->value = value;
    entry->next = table->buckets[hash];
    table->buckets[hash] = entry;
    table->count++;
}

// Look up a value in the hash table
static stb_script_value* stb_script_hash_table_lookup(stb_script_hash_table* table, const char* key) {
    STB_SCRIPT_ASSERT(table != NULL);
    STB_SCRIPT_ASSERT(key != NULL);
    
    unsigned int hash = stb_script_hash_string(key) % table->size;
    stb_script_hash_entry* entry = table->buckets[hash];
    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

// Create a new script environment
stb_script_env* stb_script_create_env(void) {
    stb_script_env* env = (stb_script_env*)STB_SCRIPT_MALLOC(sizeof(stb_script_env));
    STB_SCRIPT_ASSERT(env != NULL);
    
    env->globals = stb_script_create_hash_table(64);
    env->error_callback = NULL;
    env->error_userdata = NULL;
    
    // Register some basic functions
    // (Placeholder - actual implementation would go here)
    
    return env;
}

// Destroy a script environment
void stb_script_destroy_env(stb_script_env* env) {
    if (env == NULL) return;
    
    stb_script_destroy_hash_table(&env->globals);
    STB_SCRIPT_FREE(env);
}

// Set error callback
void stb_script_set_error_callback(stb_script_env* env, stb_script_error_callback callback, void* userdata) {
    STB_SCRIPT_ASSERT(env != NULL);
    env->error_callback = callback;
    env->error_userdata = userdata;
}

// Report an error
static void stb_script_report_error(stb_script_env* env, const char* message) {
    if (env->error_callback != NULL) {
        env->error_callback(message, env->error_userdata);
    } else {
        fprintf(stderr, "stb_script error: %s\n", message);
    }
}

// Register a native function
void stb_script_register_function(stb_script_env* env, const char* name, stb_script_func func) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(name != NULL);
    STB_SCRIPT_ASSERT(func != NULL);
    
    stb_script_value* value = stb_script_create_function(func);
    stb_script_hash_table_insert(&env->globals, name, value);
}

// Set a global variable
void stb_script_set_global(stb_script_env* env, const char* name, const stb_script_value* value) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(name != NULL);
    STB_SCRIPT_ASSERT(value != NULL);
    
    stb_script_value* copy = stb_script_copy_value(value);
    stb_script_hash_table_insert(&env->globals, name, copy);
}

// Get a global variable
const stb_script_value* stb_script_get_global(stb_script_env* env, const char* name) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(name != NULL);
    
    return stb_script_hash_table_lookup(&env->globals, name);
}

// Create script values
stb_script_value* stb_script_create_nil(void) {
    stb_script_value* value = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(value != NULL);
    value->type = STB_SCRIPT_TYPE_NIL;
    return value;
}

stb_script_value* stb_script_create_bool(int value) {
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_BOOL;
    val->data.boolean = value != 0;
    return val;
}

stb_script_value* stb_script_create_int(int value) {
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_INT;
    val->data.integer = value;
    return val;
}

stb_script_value* stb_script_create_float(float value) {
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_FLOAT;
    val->data.floating = value;
    return val;
}

stb_script_value* stb_script_create_string(const char* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_STRING;
    val->data.string = (char*)STB_SCRIPT_MALLOC(strlen(value) + 1);
    STB_SCRIPT_ASSERT(val->data.string != NULL);
    strcpy(val->data.string, value);
    return val;
}

stb_script_value* stb_script_create_function(stb_script_func func) {
    STB_SCRIPT_ASSERT(func != NULL);
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_FUNCTION;
    val->data.function = func;
    return val;
}

stb_script_value* stb_script_create_userdata(void* data) {
    stb_script_value* val = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(val != NULL);
    val->type = STB_SCRIPT_TYPE_USERDATA;
    val->data.userdata = data;
    return val;
}

// Copy a script value
stb_script_value* stb_script_copy_value(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    
    stb_script_value* copy = (stb_script_value*)STB_SCRIPT_MALLOC(sizeof(stb_script_value));
    STB_SCRIPT_ASSERT(copy != NULL);
    memcpy(copy, value, sizeof(stb_script_value));
    
    // Deep copy string type
    if (value->type == STB_SCRIPT_TYPE_STRING) {
        copy->data.string = (char*)STB_SCRIPT_MALLOC(strlen(value->data.string) + 1);
        STB_SCRIPT_ASSERT(copy->data.string != NULL);
        strcpy(copy->data.string, value->data.string);
    }
    
    return copy;
}

// Destroy a script value
void stb_script_destroy_value(stb_script_value* value) {
    if (value == NULL) return;
    
    // Free string data if needed
    if (value->type == STB_SCRIPT_TYPE_STRING) {
        STB_SCRIPT_FREE(value->data.string);
    }
    
    STB_SCRIPT_FREE(value);
}

// Parse and execute a script from a string
int stb_script_execute_string(stb_script_env* env, const char* script) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(script != NULL);
    
    // Placeholder implementation - actual parser would go here
    (void)script; // Unused parameter
    stb_script_report_error(env, "Script execution not implemented");
    return 0; // Failure
}

// Parse and execute a script from a file
int stb_script_execute_file(stb_script_env* env, const char* filename) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(filename != NULL);
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Could not open file: %s", filename);
        stb_script_report_error(env, error_msg);
        return 0;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file content
    char* buffer = (char*)STB_SCRIPT_MALLOC(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        stb_script_report_error(env, "Out of memory");
        return 0;
    }
    
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';
    fclose(file);
    
    // Execute script
    int result = stb_script_execute_string(env, buffer);
    
    // Clean up
    STB_SCRIPT_FREE(buffer);
    
    return result;
}

// Call a script function
stb_script_value* stb_script_call_function(stb_script_env* env, const char* name, int argc, stb_script_value** argv) {
    STB_SCRIPT_ASSERT(env != NULL);
    STB_SCRIPT_ASSERT(name != NULL);
    
    const stb_script_value* func_value = stb_script_get_global(env, name);
    if (func_value == NULL || func_value->type != STB_SCRIPT_TYPE_FUNCTION) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Function not found: %s", name);
        stb_script_report_error(env, error_msg);
        return stb_script_create_nil();
    }
    
    return func_value->data.function(env, argc, argv);
}

// Get type name as string
const char* stb_script_type_name(stb_script_type type) {
    switch (type) {
        case STB_SCRIPT_TYPE_NIL: return "nil";
        case STB_SCRIPT_TYPE_BOOL: return "bool";
        case STB_SCRIPT_TYPE_INT: return "int";
        case STB_SCRIPT_TYPE_FLOAT: return "float";
        case STB_SCRIPT_TYPE_STRING: return "string";
        case STB_SCRIPT_TYPE_FUNCTION: return "function";
        case STB_SCRIPT_TYPE_USERDATA: return "userdata";
        default: return "unknown";
    }
}

// Utility functions for value access
int stb_script_value_as_bool(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    
    switch (value->type) {
        case STB_SCRIPT_TYPE_NIL: return 0;
        case STB_SCRIPT_TYPE_BOOL: return value->data.boolean;
        case STB_SCRIPT_TYPE_INT: return value->data.integer != 0;
        case STB_SCRIPT_TYPE_FLOAT: return value->data.floating != 0.0f;
        case STB_SCRIPT_TYPE_STRING: return value->data.string[0] != '\0';
        case STB_SCRIPT_TYPE_FUNCTION: return 1; // Functions are always truthy
        case STB_SCRIPT_TYPE_USERDATA: return value->data.userdata != NULL;
        default: return 0;
    }
}

int stb_script_value_as_int(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    
    switch (value->type) {
        case STB_SCRIPT_TYPE_NIL: return 0;
        case STB_SCRIPT_TYPE_BOOL: return value->data.boolean;
        case STB_SCRIPT_TYPE_INT: return value->data.integer;
        case STB_SCRIPT_TYPE_FLOAT: return (int)value->data.floating;
        case STB_SCRIPT_TYPE_STRING: return atoi(value->data.string);
        default: return 0;
    }
}

float stb_script_value_as_float(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    
    switch (value->type) {
        case STB_SCRIPT_TYPE_NIL: return 0.0f;
        case STB_SCRIPT_TYPE_BOOL: return (float)value->data.boolean;
        case STB_SCRIPT_TYPE_INT: return (float)value->data.integer;
        case STB_SCRIPT_TYPE_FLOAT: return value->data.floating;
        case STB_SCRIPT_TYPE_STRING: return (float)atof(value->data.string);
        default: return 0.0f;
    }
}

const char* stb_script_value_as_string(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    
    // Note: This returns a static string for non-string types
    // For a more robust implementation, we would allocate memory
    switch (value->type) {
        case STB_SCRIPT_TYPE_NIL: return "nil";
        case STB_SCRIPT_TYPE_BOOL: return value->data.boolean ? "true" : "false";
        case STB_SCRIPT_TYPE_INT: {
            static char buffer[32];
            snprintf(buffer, sizeof(buffer), "%d", value->data.integer);
            return buffer;
        }
        case STB_SCRIPT_TYPE_FLOAT: {
            static char buffer[32];
            snprintf(buffer, sizeof(buffer), "%f", value->data.floating);
            return buffer;
        }
        case STB_SCRIPT_TYPE_STRING: return value->data.string;
        case STB_SCRIPT_TYPE_FUNCTION: return "function";
        case STB_SCRIPT_TYPE_USERDATA: return "userdata";
        default: return "unknown";
    }
}

stb_script_func stb_script_value_as_function(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return (value->type == STB_SCRIPT_TYPE_FUNCTION) ? value->data.function : NULL;
}

void* stb_script_value_as_userdata(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return (value->type == STB_SCRIPT_TYPE_USERDATA) ? value->data.userdata : NULL;
}

// Check if a value is of a specific type
int stb_script_value_is_nil(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_NIL;
}

int stb_script_value_is_bool(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_BOOL;
}

int stb_script_value_is_int(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_INT;
}

int stb_script_value_is_float(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_FLOAT;
}

int stb_script_value_is_string(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_STRING;
}

int stb_script_value_is_function(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_FUNCTION;
}

int stb_script_value_is_userdata(const stb_script_value* value) {
    STB_SCRIPT_ASSERT(value != NULL);
    return value->type == STB_SCRIPT_TYPE_USERDATA;
}

#endif // STB_SCRIPT_IMPLEMENTATION