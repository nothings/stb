/* stb_3d_anim - v1.00 - public domain 3D animation library - http://nothings.org/stb
                         no warranty implied; use at your own risk

   Do this:
      #define STB_3D_ANIM_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   You can #define STB_3D_ANIM_ASSERT(x) before the #include to avoid using assert.h.
   You can #define STB_3D_ANIM_MALLOC and STB_3D_ANIM_FREE to use your own memory allocator.

   QUICK NOTES:
      Simple 3D animation library for games and applications
      Supports skeletal animation and skinning
      Keyframe interpolation and animation blending
      Bone hierarchy and inverse kinematics (IK)
      Morph target animation support
      No external dependencies

   LICENSE

   See end of file for license information.

RECENT REVISION HISTORY:

      1.00  (2024-10-26) initial release

*/

#ifndef STB_3D_ANIM_H
#define STB_3D_ANIM_H

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct stb_3d_anim_bone;
typedef struct stb_3d_anim_bone stb_3d_anim_bone;

struct stb_3d_anim_keyframe;
typedef struct stb_3d_anim_keyframe stb_3d_anim_keyframe;

struct stb_3d_anim_channel;
typedef struct stb_3d_anim_channel stb_3d_anim_channel;

struct stb_3d_anim_clip;
typedef struct stb_3d_anim_clip stb_3d_anim_clip;

struct stb_3d_anim_skin;
typedef struct stb_3d_anim_skin stb_3d_anim_skin;

struct stb_3d_anim_morph_target;
typedef struct stb_3d_anim_morph_target stb_3d_anim_morph_target;

struct stb_3d_anim_controller;
typedef struct stb_3d_anim_controller stb_3d_anim_controller;

// 3D transform structure
typedef struct {
    float position[3];
    float rotation[4]; // Quaternion (x, y, z, w)
    float scale[3];
} stb_3d_anim_transform;

// Bone structure
typedef struct stb_3d_anim_bone {
    char* name;
    int parent_index;
    stb_3d_anim_transform local_transform;
    stb_3d_anim_transform global_transform;
    float* inverse_bind_matrix; // 4x4 matrix
    int num_children;
    int* children_indices;
} stb_3d_anim_bone;

// Keyframe types
typedef enum {
    STB_3D_ANIM_KEYFRAME_POSITION,
    STB_3D_ANIM_KEYFRAME_ROTATION,
    STB_3D_ANIM_KEYFRAME_SCALE
} stb_3d_anim_keyframe_type;

// Keyframe structure
typedef struct stb_3d_anim_keyframe {
    float time;
    stb_3d_anim_keyframe_type type;
    union {
        float position[3];
        float rotation[4]; // Quaternion
        float scale[3];
    } data;
} stb_3d_anim_keyframe;

// Animation channel structure
typedef struct stb_3d_anim_channel {
    int bone_index;
    int num_position_keyframes;
    stb_3d_anim_keyframe* position_keyframes;
    int num_rotation_keyframes;
    stb_3d_anim_keyframe* rotation_keyframes;
    int num_scale_keyframes;
    stb_3d_anim_keyframe* scale_keyframes;
} stb_3d_anim_channel;

// Animation clip structure
typedef struct stb_3d_anim_clip {
    char* name;
    float duration;
    int num_channels;
    stb_3d_anim_channel* channels;
    int loop;
} stb_3d_anim_clip;

// Skin influence structure
typedef struct {
    int bone_index;
    float weight;
} stb_3d_anim_influence;

// Vertex skin data
typedef struct {
    stb_3d_anim_influence influences[4]; // Up to 4 bone influences per vertex
    int num_influences;
} stb_3d_anim_vertex_skin;

// Skin structure
typedef struct stb_3d_anim_skin {
    int num_bones;
    stb_3d_anim_bone* bones;
    int num_vertices;
    stb_3d_anim_vertex_skin* vertex_skins;
    float* bind_shape_matrix; // 4x4 matrix
} stb_3d_anim_skin;

// Morph target structure
typedef struct stb_3d_anim_morph_target {
    char* name;
    int num_vertices;
    float* positions; // x, y, z for each vertex
    float* normals; // x, y, z for each vertex (optional)
} stb_3d_anim_morph_target;

// Morph animation clip structure
typedef struct {
    char* name;
    float duration;
    int num_targets;
    int* target_indices;
    float* target_weights; // Array of keyframes for each target
    int loop;
} stb_3d_anim_morph_clip;

// Animation controller structure
typedef struct stb_3d_anim_controller {
    stb_3d_anim_skin* skin;
    stb_3d_anim_clip* current_clip;
    float time;
    int num_morph_targets;
    stb_3d_anim_morph_target* morph_targets;
    stb_3d_anim_morph_clip* current_morph_clip;
    float morph_time;
} stb_3d_anim_controller;

// IK chain structure
typedef struct {
    int num_bones;
    int* bone_indices;
    float* bone_lengths;
} stb_3d_anim_ik_chain;

// Create a new animation controller
stb_3d_anim_controller* stb_3d_anim_create_controller(void);

// Destroy an animation controller
void stb_3d_anim_destroy_controller(stb_3d_anim_controller* controller);

// Set the skin for the controller
void stb_3d_anim_set_skin(stb_3d_anim_controller* controller, stb_3d_anim_skin* skin);

// Add morph targets to the controller
void stb_3d_anim_add_morph_targets(stb_3d_anim_controller* controller, int num_targets, stb_3d_anim_morph_target* targets);

// Set the current animation clip
void stb_3d_anim_set_clip(stb_3d_anim_controller* controller, stb_3d_anim_clip* clip);

// Set the current morph animation clip
void stb_3d_anim_set_morph_clip(stb_3d_anim_controller* controller, stb_3d_anim_morph_clip* clip);

// Update the animation controller
void stb_3d_anim_update_controller(stb_3d_anim_controller* controller, float delta_time);

// Set animation time directly
void stb_3d_anim_set_time(stb_3d_anim_controller* controller, float time);

// Get current animation time
float stb_3d_anim_get_time(stb_3d_anim_controller* controller);

// Calculate bone transforms for the current animation frame
void stb_3d_anim_calculate_bone_transforms(stb_3d_anim_controller* controller);

// Apply skinning to vertices
void stb_3d_anim_apply_skinning(stb_3d_anim_controller* controller, const float* input_vertices, float* output_vertices, int num_vertices);

// Apply skinning to vertices and normals
void stb_3d_anim_apply_skinning_with_normals(stb_3d_anim_controller* controller, 
                                             const float* input_vertices, float* output_vertices,
                                             const float* input_normals, float* output_normals,
                                             int num_vertices);

// Apply morph target animation
void stb_3d_anim_apply_morph(stb_3d_anim_controller* controller, const float* base_vertices, float* output_vertices, int num_vertices);

// Create an IK chain
stb_3d_anim_ik_chain* stb_3d_anim_create_ik_chain(stb_3d_anim_skin* skin, int end_bone_index, int num_bones);

// Destroy an IK chain
void stb_3d_anim_destroy_ik_chain(stb_3d_anim_ik_chain* chain);

// Solve IK for a chain
int stb_3d_anim_solve_ik(stb_3d_anim_skin* skin, stb_3d_anim_ik_chain* chain, const float* target_position, int iterations, float tolerance);

// Create a bone
stb_3d_anim_bone* stb_3d_anim_create_bone(const char* name, int parent_index);

// Destroy a bone
void stb_3d_anim_destroy_bone(stb_3d_anim_bone* bone);

// Create an animation clip
stb_3d_anim_clip* stb_3d_anim_create_clip(const char* name, float duration, int num_channels, stb_3d_anim_channel* channels);

// Destroy an animation clip
void stb_3d_anim_destroy_clip(stb_3d_anim_clip* clip);

// Create a skin
stb_3d_anim_skin* stb_3d_anim_create_skin(int num_bones, stb_3d_anim_bone* bones, int num_vertices, stb_3d_anim_vertex_skin* vertex_skins);

// Destroy a skin
void stb_3d_anim_destroy_skin(stb_3d_anim_skin* skin);

// Create a morph target
stb_3d_anim_morph_target* stb_3d_anim_create_morph_target(const char* name, int num_vertices, const float* positions, const float* normals);

// Destroy a morph target
void stb_3d_anim_destroy_morph_target(stb_3d_anim_morph_target* target);

// Create a morph animation clip
stb_3d_anim_morph_clip* stb_3d_anim_create_morph_clip(const char* name, float duration, int num_targets, int* target_indices, float* target_weights);

// Destroy a morph animation clip
void stb_3d_anim_destroy_morph_clip(stb_3d_anim_morph_clip* clip);

// Utility functions
void stb_3d_anim_transform_identity(stb_3d_anim_transform* transform);
void stb_3d_anim_transform_multiply(const stb_3d_anim_transform* a, const stb_3d_anim_transform* b, stb_3d_anim_transform* result);
void stb_3d_anim_transform_to_matrix(const stb_3d_anim_transform* transform, float* matrix); // 4x4 matrix
void stb_3d_anim_matrix_to_transform(const float* matrix, stb_3d_anim_transform* transform); // 4x4 matrix

// Interpolation functions
void stb_3d_anim_interpolate_position(const float* a, const float* b, float t, float* result);
void stb_3d_anim_interpolate_rotation(const float* a, const float* b, float t, float* result); // Quaternions
void stb_3d_anim_interpolate_scale(const float* a, const float* b, float t, float* result);
void stb_3d_anim_interpolate_transform(const stb_3d_anim_transform* a, const stb_3d_anim_transform* b, float t, stb_3d_anim_transform* result);

// Matrix utility functions (4x4 matrices, column-major)
void stb_3d_anim_matrix_identity(float* matrix);
void stb_3d_anim_matrix_multiply(const float* a, const float* b, float* result);
void stb_3d_anim_matrix_translate(float* matrix, float x, float y, float z);
void stb_3d_anim_matrix_rotate(float* matrix, float x, float y, float z, float angle_radians);
void stb_3d_anim_matrix_scale(float* matrix, float x, float y, float z);
void stb_3d_anim_matrix_inverse(const float* matrix, float* result);
void stb_3d_anim_matrix_transpose(const float* matrix, float* result);

#ifdef __cplusplus
}
#endif

#endif // STB_3D_ANIM_H

#ifdef STB_3D_ANIM_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#ifndef STB_3D_ANIM_ASSERT
#define STB_3D_ANIM_ASSERT(x) assert(x)
#endif

#ifndef STB_3D_ANIM_MALLOC
#define STB_3D_ANIM_MALLOC malloc
#endif

#ifndef STB_3D_ANIM_FREE
#define STB_3D_ANIM_FREE free
#endif

// Create a new animation controller
stb_3d_anim_controller* stb_3d_anim_create_controller(void) {
    stb_3d_anim_controller* controller = (stb_3d_anim_controller*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_controller));
    STB_3D_ANIM_ASSERT(controller != NULL);
    memset(controller, 0, sizeof(stb_3d_anim_controller));
    return controller;
}

// Destroy an animation controller
void stb_3d_anim_destroy_controller(stb_3d_anim_controller* controller) {
    if (controller == NULL) return;
    
    // Note: We don't destroy the skin or clips here - they should be managed separately
    
    if (controller->morph_targets != NULL) {
        for (int i = 0; i < controller->num_morph_targets; ++i) {
            stb_3d_anim_destroy_morph_target(&controller->morph_targets[i]);
        }
        STB_3D_ANIM_FREE(controller->morph_targets);
    }
    
    STB_3D_ANIM_FREE(controller);
}

// Set the skin for the controller
void stb_3d_anim_set_skin(stb_3d_anim_controller* controller, stb_3d_anim_skin* skin) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    controller->skin = skin;
}

// Add morph targets to the controller
void stb_3d_anim_add_morph_targets(stb_3d_anim_controller* controller, int num_targets, stb_3d_anim_morph_target* targets) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    STB_3D_ANIM_ASSERT(targets != NULL);
    
    if (controller->morph_targets != NULL) {
        // If we already have morph targets, free them first
        for (int i = 0; i < controller->num_morph_targets; ++i) {
            stb_3d_anim_destroy_morph_target(&controller->morph_targets[i]);
        }
        STB_3D_ANIM_FREE(controller->morph_targets);
    }
    
    controller->num_morph_targets = num_targets;
    controller->morph_targets = (stb_3d_anim_morph_target*)STB_3D_ANIM_MALLOC(num_targets * sizeof(stb_3d_anim_morph_target));
    STB_3D_ANIM_ASSERT(controller->morph_targets != NULL);
    memcpy(controller->morph_targets, targets, num_targets * sizeof(stb_3d_anim_morph_target));
}

// Set the current animation clip
void stb_3d_anim_set_clip(stb_3d_anim_controller* controller, stb_3d_anim_clip* clip) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    controller->current_clip = clip;
    controller->time = 0.0f;
}

// Set the current morph animation clip
void stb_3d_anim_set_morph_clip(stb_3d_anim_controller* controller, stb_3d_anim_morph_clip* clip) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    controller->current_morph_clip = clip;
    controller->morph_time = 0.0f;
}

// Update the animation controller
void stb_3d_anim_update_controller(stb_3d_anim_controller* controller, float delta_time) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    
    // Update skeletal animation
    if (controller->current_clip != NULL) {
        controller->time += delta_time;
        
        if (controller->current_clip->loop) {
            // Loop the animation
            while (controller->time >= controller->current_clip->duration) {
                controller->time -= controller->current_clip->duration;
            }
        } else {
            // Clamp to end of animation
            if (controller->time >= controller->current_clip->duration) {
                controller->time = controller->current_clip->duration;
            }
        }
        
        // Calculate bone transforms for current frame
        stb_3d_anim_calculate_bone_transforms(controller);
    }
    
    // Update morph animation
    if (controller->current_morph_clip != NULL) {
        controller->morph_time += delta_time;
        
        if (controller->current_morph_clip->loop) {
            while (controller->morph_time >= controller->current_morph_clip->duration) {
                controller->morph_time -= controller->current_morph_clip->duration;
            }
        } else {
            if (controller->morph_time >= controller->current_morph_clip->duration) {
                controller->morph_time = controller->current_morph_clip->duration;
            }
        }
    }
}

// Set animation time directly
void stb_3d_anim_set_time(stb_3d_anim_controller* controller, float time) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    
    if (controller->current_clip != NULL) {
        if (controller->current_clip->loop) {
            // Wrap time within clip duration
            while (time < 0.0f) time += controller->current_clip->duration;
            while (time >= controller->current_clip->duration) time -= controller->current_clip->duration;
        } else {
            // Clamp time to clip duration
            if (time < 0.0f) time = 0.0f;
            if (time >= controller->current_clip->duration) time = controller->current_clip->duration;
        }
        
        controller->time = time;
        stb_3d_anim_calculate_bone_transforms(controller);
    }
}

// Get current animation time
float stb_3d_anim_get_time(stb_3d_anim_controller* controller) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    return controller->time;
}

// Find the index of the next keyframe
static int stb_3d_anim_find_next_keyframe(const stb_3d_anim_keyframe* keyframes, int num_keyframes, float time) {
    for (int i = 0; i < num_keyframes; ++i) {
        if (keyframes[i].time > time) {
            return i;
        }
    }
    return num_keyframes - 1;
}

// Calculate bone transforms for the current animation frame
void stb_3d_anim_calculate_bone_transforms(stb_3d_anim_controller* controller) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    STB_3D_ANIM_ASSERT(controller->skin != NULL);
    STB_3D_ANIM_ASSERT(controller->current_clip != NULL);
    
    stb_3d_anim_skin* skin = controller->skin;
    stb_3d_anim_clip* clip = controller->current_clip;
    float time = controller->time;
    
    // First, interpolate transforms for each bone from animation channels
    for (int i = 0; i < clip->num_channels; ++i) {
        stb_3d_anim_channel* channel = &clip->channels[i];
        int bone_index = channel->bone_index;
        
        if (bone_index < 0 || bone_index >= skin->num_bones) {
            continue; // Invalid bone index
        }
        
        stb_3d_anim_bone* bone = &skin->bones[bone_index];
        stb_3d_anim_transform* transform = &bone->local_transform;
        
        // Interpolate position
        if (channel->num_position_keyframes > 0) {
            if (channel->num_position_keyframes == 1 || time <= channel->position_keyframes[0].time) {
                // Use first keyframe
                memcpy(transform->position, channel->position_keyframes[0].data.position, sizeof(float) * 3);
            } else if (time >= channel->position_keyframes[channel->num_position_keyframes - 1].time) {
                // Use last keyframe
                memcpy(transform->position, channel->position_keyframes[channel->num_position_keyframes - 1].data.position, sizeof(float) * 3);
            } else {
                // Interpolate between two keyframes
                int next_index = stb_3d_anim_find_next_keyframe(channel->position_keyframes, channel->num_position_keyframes, time);
                int prev_index = next_index - 1;
                
                const stb_3d_anim_keyframe* prev_key = &channel->position_keyframes[prev_index];
                const stb_3d_anim_keyframe* next_key = &channel->position_keyframes[next_index];
                
                float t = (time - prev_key->time) / (next_key->time - prev_key->time);
                stb_3d_anim_interpolate_position(prev_key->data.position, next_key->data.position, t, transform->position);
            }
        }
        
        // Interpolate rotation
        if (channel->num_rotation_keyframes > 0) {
            if (channel->num_rotation_keyframes == 1 || time <= channel->rotation_keyframes[0].time) {
                // Use first keyframe
                memcpy(transform->rotation, channel->rotation_keyframes[0].data.rotation, sizeof(float) * 4);
            } else if (time >= channel->rotation_keyframes[channel->num_rotation_keyframes - 1].time) {
                // Use last keyframe
                memcpy(transform->rotation, channel->rotation_keyframes[channel->num_rotation_keyframes - 1].data.rotation, sizeof(float) * 4);
            } else {
                // Interpolate between two keyframes
                int next_index = stb_3d_anim_find_next_keyframe(channel->rotation_keyframes, channel->num_rotation_keyframes, time);
                int prev_index = next_index - 1;
                
                const stb_3d_anim_keyframe* prev_key = &channel->rotation_keyframes[prev_index];
                const stb_3d_anim_keyframe* next_key = &channel->rotation_keyframes[next_index];
                
                float t = (time - prev_key->time) / (next_key->time - prev_key->time);
                stb_3d_anim_interpolate_rotation(prev_key->data.rotation, next_key->data.rotation, t, transform->rotation);
            }
        }
        
        // Interpolate scale
        if (channel->num_scale_keyframes > 0) {
            if (channel->num_scale_keyframes == 1 || time <= channel->scale_keyframes[0].time) {
                // Use first keyframe
                memcpy(transform->scale, channel->scale_keyframes[0].data.scale, sizeof(float) * 3);
            } else if (time >= channel->scale_keyframes[channel->num_scale_keyframes - 1].time) {
                // Use last keyframe
                memcpy(transform->scale, channel->scale_keyframes[channel->num_scale_keyframes - 1].data.scale, sizeof(float) * 3);
            } else {
                // Interpolate between two keyframes
                int next_index = stb_3d_anim_find_next_keyframe(channel->scale_keyframes, channel->num_scale_keyframes, time);
                int prev_index = next_index - 1;
                
                const stb_3d_anim_keyframe* prev_key = &channel->scale_keyframes[prev_index];
                const stb_3d_anim_keyframe* next_key = &channel->scale_keyframes[next_index];
                
                float t = (time - prev_key->time) / (next_key->time - prev_key->time);
                stb_3d_anim_interpolate_scale(prev_key->data.scale, next_key->data.scale, t, transform->scale);
            }
        }
    }
    
    // Then, calculate global transforms for all bones
    for (int i = 0; i < skin->num_bones; ++i) {
        stb_3d_anim_bone* bone = &skin->bones[i];
        
        if (bone->parent_index == -1) {
            // Root bone, global transform is same as local
            memcpy(&bone->global_transform, &bone->local_transform, sizeof(stb_3d_anim_transform));
        } else {
            // Calculate global transform by combining with parent's global transform
            const stb_3d_anim_bone* parent = &skin->bones[bone->parent_index];
            stb_3d_anim_transform_multiply(&parent->global_transform, &bone->local_transform, &bone->global_transform);
        }
    }
}

// Apply skinning to vertices
void stb_3d_anim_apply_skinning(stb_3d_anim_controller* controller, const float* input_vertices, float* output_vertices, int num_vertices) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    STB_3D_ANIM_ASSERT(controller->skin != NULL);
    STB_3D_ANIM_ASSERT(input_vertices != NULL);
    STB_3D_ANIM_ASSERT(output_vertices != NULL);
    
    stb_3d_anim_skin* skin = controller->skin;
    
    for (int i = 0; i < num_vertices; ++i) {
        const stb_3d_anim_vertex_skin* vertex_skin = &skin->vertex_skins[i];
        float weighted_position[3] = { 0.0f, 0.0f, 0.0f };
        float total_weight = 0.0f;
        
        // Apply each bone influence
        for (int j = 0; j < vertex_skin->num_influences; ++j) {
            const stb_3d_anim_influence* influence = &vertex_skin->influences[j];
            int bone_index = influence->bone_index;
            float weight = influence->weight;
            
            if (bone_index < 0 || bone_index >= skin->num_bones) {
                continue; // Invalid bone index
            }
            
            const stb_3d_anim_bone* bone = &skin->bones[bone_index];
            
            // Calculate bone matrix: global transform * inverse bind matrix
            float bone_matrix[16];
            float global_matrix[16];
            stb_3d_anim_transform_to_matrix(&bone->global_transform, global_matrix);
            
            float final_matrix[16];
            stb_3d_anim_matrix_multiply(global_matrix, bone->inverse_bind_matrix, final_matrix);
            
            // Transform vertex position
            const float* v = &input_vertices[i * 3];
            float transformed[4] = {
                final_matrix[0] * v[0] + final_matrix[4] * v[1] + final_matrix[8] * v[2] + final_matrix[12],
                final_matrix[1] * v[0] + final_matrix[5] * v[1] + final_matrix[9] * v[2] + final_matrix[13],
                final_matrix[2] * v[0] + final_matrix[6] * v[1] + final_matrix[10] * v[2] + final_matrix[14],
                final_matrix[3] * v[0] + final_matrix[7] * v[1] + final_matrix[11] * v[2] + final_matrix[15]
            };
            
            // Apply weight
            weighted_position[0] += transformed[0] * weight;
            weighted_position[1] += transformed[1] * weight;
            weighted_position[2] += transformed[2] * weight;
            total_weight += weight;
        }
        
        // Normalize by total weight (in case weights don't sum to 1.0)
        if (total_weight > 0.0f) {
            weighted_position[0] /= total_weight;
            weighted_position[1] /= total_weight;
            weighted_position[2] /= total_weight;
        }
        
        // Store result
        output_vertices[i * 3] = weighted_position[0];
        output_vertices[i * 3 + 1] = weighted_position[1];
        output_vertices[i * 3 + 2] = weighted_position[2];
    }
}

// Apply skinning to vertices and normals
void stb_3d_anim_apply_skinning_with_normals(stb_3d_anim_controller* controller, 
                                             const float* input_vertices, float* output_vertices,
                                             const float* input_normals, float* output_normals,
                                             int num_vertices) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    STB_3D_ANIM_ASSERT(controller->skin != NULL);
    STB_3D_ANIM_ASSERT(input_vertices != NULL);
    STB_3D_ANIM_ASSERT(output_vertices != NULL);
    STB_3D_ANIM_ASSERT(input_normals != NULL);
    STB_3D_ANIM_ASSERT(output_normals != NULL);
    
    stb_3d_anim_skin* skin = controller->skin;
    
    for (int i = 0; i < num_vertices; ++i) {
        const stb_3d_anim_vertex_skin* vertex_skin = &skin->vertex_skins[i];
        float weighted_position[3] = { 0.0f, 0.0f, 0.0f };
        float weighted_normal[3] = { 0.0f, 0.0f, 0.0f };
        float total_weight = 0.0f;
        
        // Apply each bone influence
        for (int j = 0; j < vertex_skin->num_influences; ++j) {
            const stb_3d_anim_influence* influence = &vertex_skin->influences[j];
            int bone_index = influence->bone_index;
            float weight = influence->weight;
            
            if (bone_index < 0 || bone_index >= skin->num_bones) {
                continue; // Invalid bone index
            }
            
            const stb_3d_anim_bone* bone = &skin->bones[bone_index];
            
            // Calculate bone matrix: global transform * inverse bind matrix
            float bone_matrix[16];
            float global_matrix[16];
            stb_3d_anim_transform_to_matrix(&bone->global_transform, global_matrix);
            
            float final_matrix[16];
            stb_3d_anim_matrix_multiply(global_matrix, bone->inverse_bind_matrix, final_matrix);
            
            // Calculate normal matrix (inverse transpose of upper-left 3x3)
            float normal_matrix[9];
            
            // Calculate determinant of 3x3 matrix
            float det = final_matrix[0] * (final_matrix[5] * final_matrix[10] - final_matrix[6] * final_matrix[9]) - 
                       final_matrix[4] * (final_matrix[1] * final_matrix[10] - final_matrix[2] * final_matrix[9]) + 
                       final_matrix[8] * (final_matrix[1] * final_matrix[6] - final_matrix[2] * final_matrix[5]);
            
            if (det == 0.0f) {
                // Singular matrix, use identity
                stb_3d_anim_matrix_identity((float*)normal_matrix);
            } else {
                float inv_det = 1.0f / det;
                
                // Calculate inverse of 3x3 matrix
                normal_matrix[0] = (final_matrix[5] * final_matrix[10] - final_matrix[6] * final_matrix[9]) * inv_det;
                normal_matrix[1] = (final_matrix[2] * final_matrix[9] - final_matrix[1] * final_matrix[10]) * inv_det;
                normal_matrix[2] = (final_matrix[1] * final_matrix[6] - final_matrix[2] * final_matrix[5]) * inv_det;
                normal_matrix[3] = (final_matrix[6] * final_matrix[8] - final_matrix[4] * final_matrix[10]) * inv_det;
                normal_matrix[4] = (final_matrix[0] * final_matrix[10] - final_matrix[2] * final_matrix[8]) * inv_det;
                normal_matrix[5] = (final_matrix[2] * final_matrix[4] - final_matrix[0] * final_matrix[6]) * inv_det;
                normal_matrix[6] = (final_matrix[4] * final_matrix[9] - final_matrix[5] * final_matrix[8]) * inv_det;
                normal_matrix[7] = (final_matrix[1] * final_matrix[8] - final_matrix[0] * final_matrix[9]) * inv_det;
                normal_matrix[8] = (final_matrix[0] * final_matrix[5] - final_matrix[1] * final_matrix[4]) * inv_det;
                
                // Transpose the inverse matrix
                float temp = normal_matrix[1]; normal_matrix[1] = normal_matrix[3]; normal_matrix[3] = temp;
                temp = normal_matrix[2]; normal_matrix[2] = normal_matrix[6]; normal_matrix[6] = temp;
                temp = normal_matrix[5]; normal_matrix[5] = normal_matrix[7]; normal_matrix[7] = temp;
            }
            
            // Transform vertex position
            const float* v = &input_vertices[i * 3];
            float transformed[4] = {
                final_matrix[0] * v[0] + final_matrix[4] * v[1] + final_matrix[8] * v[2] + final_matrix[12],
                final_matrix[1] * v[0] + final_matrix[5] * v[1] + final_matrix[9] * v[2] + final_matrix[13],
                final_matrix[2] * v[0] + final_matrix[6] * v[1] + final_matrix[10] * v[2] + final_matrix[14],
                final_matrix[3] * v[0] + final_matrix[7] * v[1] + final_matrix[11] * v[2] + final_matrix[15]
            };
            
            // Apply weight to position
            weighted_position[0] += transformed[0] * weight;
            weighted_position[1] += transformed[1] * weight;
            weighted_position[2] += transformed[2] * weight;
            
            // Transform vertex normal
            const float* n = &input_normals[i * 3];
            float transformed_normal[3] = {
                normal_matrix[0] * n[0] + normal_matrix[3] * n[1] + normal_matrix[6] * n[2],
                normal_matrix[1] * n[0] + normal_matrix[4] * n[1] + normal_matrix[7] * n[2],
                normal_matrix[2] * n[0] + normal_matrix[5] * n[1] + normal_matrix[8] * n[2]
            };
            
            // Apply weight to normal
            weighted_normal[0] += transformed_normal[0] * weight;
            weighted_normal[1] += transformed_normal[1] * weight;
            weighted_normal[2] += transformed_normal[2] * weight;
            
            total_weight += weight;
        }
        
        // Normalize by total weight (in case weights don't sum to 1.0)
        if (total_weight > 0.0f) {
            weighted_position[0] /= total_weight;
            weighted_position[1] /= total_weight;
            weighted_position[2] /= total_weight;
            
            weighted_normal[0] /= total_weight;
            weighted_normal[1] /= total_weight;
            weighted_normal[2] /= total_weight;
        }
        
        // Normalize the normal
        float normal_length = sqrtf(weighted_normal[0] * weighted_normal[0] + 
                                    weighted_normal[1] * weighted_normal[1] + 
                                    weighted_normal[2] * weighted_normal[2]);
        if (normal_length > 0.0f) {
            weighted_normal[0] /= normal_length;
            weighted_normal[1] /= normal_length;
            weighted_normal[2] /= normal_length;
        }
        
        // Store results
        output_vertices[i * 3] = weighted_position[0];
        output_vertices[i * 3 + 1] = weighted_position[1];
        output_vertices[i * 3 + 2] = weighted_position[2];
        
        output_normals[i * 3] = weighted_normal[0];
        output_normals[i * 3 + 1] = weighted_normal[1];
        output_normals[i * 3 + 2] = weighted_normal[2];
    }
}

// Apply morph target animation
void stb_3d_anim_apply_morph(stb_3d_anim_controller* controller, const float* base_vertices, float* output_vertices, int num_vertices) {
    STB_3D_ANIM_ASSERT(controller != NULL);
    STB_3D_ANIM_ASSERT(controller->current_morph_clip != NULL);
    STB_3D_ANIM_ASSERT(base_vertices != NULL);
    STB_3D_ANIM_ASSERT(output_vertices != NULL);
    
    stb_3d_anim_morph_clip* clip = controller->current_morph_clip;
    float time = controller->morph_time;
    
    // Calculate number of keyframes per target
    int num_keyframes = (int)(clip->duration + 0.5f) + 1; // Assuming 1 keyframe per second
    
    // Start with base vertices
    memcpy(output_vertices, base_vertices, num_vertices * 3 * sizeof(float));
    
    // Apply each morph target
    for (int i = 0; i < clip->num_targets; ++i) {
        int target_index = clip->target_indices[i];
        
        if (target_index < 0 || target_index >= controller->num_morph_targets) {
            continue; // Invalid target index
        }
        
        const stb_3d_anim_morph_target* target = &controller->morph_targets[target_index];
        
        if (target->num_vertices != num_vertices) {
            continue; // Mismatched vertex count
        }
        
        // Find the weight for this target at current time
        float weight = 0.0f;
        
        if (num_keyframes == 1 || time <= 0.0f) {
            weight = clip->target_weights[i * num_keyframes];
        } else if (time >= clip->duration) {
            weight = clip->target_weights[i * num_keyframes + num_keyframes - 1];
        } else {
            int keyframe_index = (int)time;
            float t = time - keyframe_index;
            
            float w0 = clip->target_weights[i * num_keyframes + keyframe_index];
            float w1 = clip->target_weights[i * num_keyframes + keyframe_index + 1];
            
            weight = w0 + t * (w1 - w0);
        }
        
        // Apply morph target with calculated weight
        if (weight > 0.0f) {
            for (int j = 0; j < num_vertices; ++j) {
                output_vertices[j * 3] += (target->positions[j * 3] - base_vertices[j * 3]) * weight;
                output_vertices[j * 3 + 1] += (target->positions[j * 3 + 1] - base_vertices[j * 3 + 1]) * weight;
                output_vertices[j * 3 + 2] += (target->positions[j * 3 + 2] - base_vertices[j * 3 + 2]) * weight;
            }
        }
    }
}

// Create an IK chain
stb_3d_anim_ik_chain* stb_3d_anim_create_ik_chain(stb_3d_anim_skin* skin, int end_bone_index, int num_bones) {
    STB_3D_ANIM_ASSERT(skin != NULL);
    STB_3D_ANIM_ASSERT(end_bone_index >= 0 && end_bone_index < skin->num_bones);
    STB_3D_ANIM_ASSERT(num_bones >= 1);
    
    stb_3d_anim_ik_chain* chain = (stb_3d_anim_ik_chain*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_ik_chain));
    STB_3D_ANIM_ASSERT(chain != NULL);
    
    chain->num_bones = num_bones;
    chain->bone_indices = (int*)STB_3D_ANIM_MALLOC(num_bones * sizeof(int));
    chain->bone_lengths = (float*)STB_3D_ANIM_MALLOC(num_bones * sizeof(float));
    STB_3D_ANIM_ASSERT(chain->bone_indices != NULL && chain->bone_lengths != NULL);
    
    // Build the chain from end bone to root
    int current_bone = end_bone_index;
    for (int i = 0; i < num_bones; ++i) {
        if (current_bone == -1) {
            // Reached root before building full chain
            chain->num_bones = i;
            break;
        }
        
        chain->bone_indices[i] = current_bone;
        
        const stb_3d_anim_bone* bone = &skin->bones[current_bone];
        
        if (bone->parent_index != -1) {
            // Calculate bone length as distance between bone and parent
            const stb_3d_anim_bone* parent = &skin->bones[bone->parent_index];
            float dx = bone->global_transform.position[0] - parent->global_transform.position[0];
            float dy = bone->global_transform.position[1] - parent->global_transform.position[1];
            float dz = bone->global_transform.position[2] - parent->global_transform.position[2];
            chain->bone_lengths[i] = sqrtf(dx * dx + dy * dy + dz * dz);
        } else {
            // Root bone has no length
            chain->bone_lengths[i] = 0.0f;
        }
        
        current_bone = bone->parent_index;
    }
    
    return chain;
}

// Destroy an IK chain
void stb_3d_anim_destroy_ik_chain(stb_3d_anim_ik_chain* chain) {
    if (chain == NULL) return;
    
    STB_3D_ANIM_FREE(chain->bone_indices);
    STB_3D_ANIM_FREE(chain->bone_lengths);
    STB_3D_ANIM_FREE(chain);
}

// Solve IK for a chain
int stb_3d_anim_solve_ik(stb_3d_anim_skin* skin, stb_3d_anim_ik_chain* chain, const float* target_position, int iterations, float tolerance) {
    STB_3D_ANIM_ASSERT(skin != NULL);
    STB_3D_ANIM_ASSERT(chain != NULL);
    STB_3D_ANIM_ASSERT(target_position != NULL);
    STB_3D_ANIM_ASSERT(iterations > 0);
    
    // This is a simple CCD (Cyclic Coordinate Descent) IK solver implementation
    
    for (int iter = 0; iter < iterations; ++iter) {
        // Get end effector position
        const stb_3d_anim_bone* end_bone = &skin->bones[chain->bone_indices[0]];
        float end_position[3];
        memcpy(end_position, end_bone->global_transform.position, sizeof(float) * 3);
        
        // Calculate distance to target
        float dx = target_position[0] - end_position[0];
        float dy = target_position[1] - end_position[1];
        float dz = target_position[2] - end_position[2];
        float distance = sqrtf(dx * dx + dy * dy + dz * dz);
        
        if (distance < tolerance) {
            // Target reached
            return 1;
        }
        
        // Iterate through each bone in the chain
        for (int i = 0; i < chain->num_bones; ++i) {
            int bone_index = chain->bone_indices[i];
            stb_3d_anim_bone* bone = &skin->bones[bone_index];
            
            if (bone->parent_index == -1) {
                // Skip root bone for CCD
                continue;
            }
            
            // Get parent bone
            stb_3d_anim_bone* parent = &skin->bones[bone->parent_index];
            
            // Calculate vector from parent to end effector
            float parent_to_end[3] = {
                end_position[0] - parent->global_transform.position[0],
                end_position[1] - parent->global_transform.position[1],
                end_position[2] - parent->global_transform.position[2]
            };
            
            // Calculate vector from parent to target
            float parent_to_target[3] = {
                target_position[0] - parent->global_transform.position[0],
                target_position[1] - parent->global_transform.position[1],
                target_position[2] - parent->global_transform.position[2]
            };
            
            // Normalize vectors
            float len_parent_to_end = sqrtf(parent_to_end[0] * parent_to_end[0] + 
                                           parent_to_end[1] * parent_to_end[1] + 
                                           parent_to_end[2] * parent_to_end[2]);
            
            float len_parent_to_target = sqrtf(parent_to_target[0] * parent_to_target[0] + 
                                              parent_to_target[1] * parent_to_target[1] + 
                                              parent_to_target[2] * parent_to_target[2]);
            
            if (len_parent_to_end < 0.0001f || len_parent_to_target < 0.0001f) {
                continue;
            }
            
            parent_to_end[0] /= len_parent_to_end;
            parent_to_end[1] /= len_parent_to_end;
            parent_to_end[2] /= len_parent_to_end;
            
            parent_to_target[0] /= len_parent_to_target;
            parent_to_target[1] /= len_parent_to_target;
            parent_to_target[2] /= len_parent_to_target;
            
            // Calculate rotation axis (cross product)
            float rotation_axis[3] = {
                parent_to_end[1] * parent_to_target[2] - parent_to_end[2] * parent_to_target[1],
                parent_to_end[2] * parent_to_target[0] - parent_to_end[0] * parent_to_target[2],
                parent_to_end[0] * parent_to_target[1] - parent_to_end[1] * parent_to_target[0]
            };
            
            float axis_length = sqrtf(rotation_axis[0] * rotation_axis[0] + 
                                     rotation_axis[1] * rotation_axis[1] + 
                                     rotation_axis[2] * rotation_axis[2]);
            
            if (axis_length < 0.0001f) {
                continue;
            }
            
            rotation_axis[0] /= axis_length;
            rotation_axis[1] /= axis_length;
            rotation_axis[2] /= axis_length;
            
            // Calculate rotation angle (dot product)
            float dot = parent_to_end[0] * parent_to_target[0] + 
                       parent_to_end[1] * parent_to_target[1] + 
                       parent_to_end[2] * parent_to_target[2];
            
            dot = (dot > 1.0f) ? 1.0f : (dot < -1.0f) ? -1.0f : dot;
            float angle = acosf(dot);
            
            // Limit rotation angle to prevent over-rotation
            float max_angle = 0.5f; // 28.6 degrees
            if (angle > max_angle) angle = max_angle;
            if (angle < -max_angle) angle = -max_angle;
            
            // Create rotation quaternion
            float half_angle = angle / 2.0f;
            float sin_half = sinf(half_angle);
            float rotation_quat[4] = {
                rotation_axis[0] * sin_half,
                rotation_axis[1] * sin_half,
                rotation_axis[2] * sin_half,
                cosf(half_angle)
            };
            
            // Apply rotation to bone's local rotation
            stb_3d_anim_interpolate_rotation(bone->local_transform.rotation, rotation_quat, 1.0f, bone->local_transform.rotation);
            
            // Recalculate global transforms for all bones
            for (int j = 0; j < skin->num_bones; ++j) {
                stb_3d_anim_bone* b = &skin->bones[j];
                
                if (b->parent_index == -1) {
                    memcpy(&b->global_transform, &b->local_transform, sizeof(stb_3d_anim_transform));
                } else {
                    const stb_3d_anim_bone* p = &skin->bones[b->parent_index];
                    stb_3d_anim_transform_multiply(&p->global_transform, &b->local_transform, &b->global_transform);
                }
            }
            
            // Update end position
            memcpy(end_position, skin->bones[chain->bone_indices[0]].global_transform.position, sizeof(float) * 3);
            
            // Check if we've reached the target
            dx = target_position[0] - end_position[0];
            dy = target_position[1] - end_position[1];
            dz = target_position[2] - end_position[2];
            distance = sqrtf(dx * dx + dy * dy + dz * dz);
            
            if (distance < tolerance) {
                return 1;
            }
        }
    }
    
    // Could not reach target within tolerance
    return 0;
}

// Create a bone
stb_3d_anim_bone* stb_3d_anim_create_bone(const char* name, int parent_index) {
    STB_3D_ANIM_ASSERT(name != NULL);
    
    stb_3d_anim_bone* bone = (stb_3d_anim_bone*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_bone));
    STB_3D_ANIM_ASSERT(bone != NULL);
    memset(bone, 0, sizeof(stb_3d_anim_bone));
    
    bone->name = (char*)STB_3D_ANIM_MALLOC(strlen(name) + 1);
    STB_3D_ANIM_ASSERT(bone->name != NULL);
    strcpy(bone->name, name);
    
    bone->parent_index = parent_index;
    
    // Set identity transform
    stb_3d_anim_transform_identity(&bone->local_transform);
    stb_3d_anim_transform_identity(&bone->global_transform);
    
    // Allocate inverse bind matrix (identity)
    bone->inverse_bind_matrix = (float*)STB_3D_ANIM_MALLOC(16 * sizeof(float));
    STB_3D_ANIM_ASSERT(bone->inverse_bind_matrix != NULL);
    stb_3d_anim_matrix_identity(bone->inverse_bind_matrix);
    
    return bone;
}

// Destroy a bone
void stb_3d_anim_destroy_bone(stb_3d_anim_bone* bone) {
    if (bone == NULL) return;
    
    STB_3D_ANIM_FREE(bone->name);
    STB_3D_ANIM_FREE(bone->inverse_bind_matrix);
    STB_3D_ANIM_FREE(bone->children_indices);
    STB_3D_ANIM_FREE(bone);
}

// Create an animation clip
stb_3d_anim_clip* stb_3d_anim_create_clip(const char* name, float duration, int num_channels, stb_3d_anim_channel* channels) {
    STB_3D_ANIM_ASSERT(name != NULL);
    STB_3D_ANIM_ASSERT(channels != NULL);
    
    stb_3d_anim_clip* clip = (stb_3d_anim_clip*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_clip));
    STB_3D_ANIM_ASSERT(clip != NULL);
    memset(clip, 0, sizeof(stb_3d_anim_clip));
    
    clip->name = (char*)STB_3D_ANIM_MALLOC(strlen(name) + 1);
    STB_3D_ANIM_ASSERT(clip->name != NULL);
    strcpy(clip->name, name);
    
    clip->duration = duration;
    clip->num_channels = num_channels;
    clip->loop = 1; // Default to looping
    
    // Allocate and copy channels
    clip->channels = (stb_3d_anim_channel*)STB_3D_ANIM_MALLOC(num_channels * sizeof(stb_3d_anim_channel));
    STB_3D_ANIM_ASSERT(clip->channels != NULL);
    memcpy(clip->channels, channels, num_channels * sizeof(stb_3d_anim_channel));
    
    return clip;
}

// Destroy an animation clip
void stb_3d_anim_destroy_clip(stb_3d_anim_clip* clip) {
    if (clip == NULL) return;
    
    STB_3D_ANIM_FREE(clip->name);
    
    // Free keyframes for each channel
    for (int i = 0; i < clip->num_channels; ++i) {
        stb_3d_anim_channel* channel = &clip->channels[i];
        STB_3D_ANIM_FREE(channel->position_keyframes);
        STB_3D_ANIM_FREE(channel->rotation_keyframes);
        STB_3D_ANIM_FREE(channel->scale_keyframes);
    }
    
    STB_3D_ANIM_FREE(clip->channels);
    STB_3D_ANIM_FREE(clip);
}

// Create a skin
stb_3d_anim_skin* stb_3d_anim_create_skin(int num_bones, stb_3d_anim_bone* bones, int num_vertices, stb_3d_anim_vertex_skin* vertex_skins) {
    STB_3D_ANIM_ASSERT(bones != NULL);
    STB_3D_ANIM_ASSERT(vertex_skins != NULL);
    
    stb_3d_anim_skin* skin = (stb_3d_anim_skin*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_skin));
    STB_3D_ANIM_ASSERT(skin != NULL);
    memset(skin, 0, sizeof(stb_3d_anim_skin));
    
    skin->num_bones = num_bones;
    skin->num_vertices = num_vertices;
    
    // Allocate and copy bones
    skin->bones = (stb_3d_anim_bone*)STB_3D_ANIM_MALLOC(num_bones * sizeof(stb_3d_anim_bone));
    STB_3D_ANIM_ASSERT(skin->bones != NULL);
    memcpy(skin->bones, bones, num_bones * sizeof(stb_3d_anim_bone));
    
    // Allocate and copy vertex skins
    skin->vertex_skins = (stb_3d_anim_vertex_skin*)STB_3D_ANIM_MALLOC(num_vertices * sizeof(stb_3d_anim_vertex_skin));
    STB_3D_ANIM_ASSERT(skin->vertex_skins != NULL);
    memcpy(skin->vertex_skins, vertex_skins, num_vertices * sizeof(stb_3d_anim_vertex_skin));
    
    // Allocate bind shape matrix (identity)
    skin->bind_shape_matrix = (float*)STB_3D_ANIM_MALLOC(16 * sizeof(float));
    STB_3D_ANIM_ASSERT(skin->bind_shape_matrix != NULL);
    stb_3d_anim_matrix_identity(skin->bind_shape_matrix);
    
    // Build bone hierarchy (children indices)
    for (int i = 0; i < num_bones; ++i) {
        stb_3d_anim_bone* bone = &skin->bones[i];
        
        if (bone->parent_index != -1) {
            stb_3d_anim_bone* parent = &skin->bones[bone->parent_index];
            parent->num_children++;
        }
    }
    
    for (int i = 0; i < num_bones; ++i) {
        stb_3d_anim_bone* bone = &skin->bones[i];
        
        if (bone->num_children > 0) {
            bone->children_indices = (int*)STB_3D_ANIM_MALLOC(bone->num_children * sizeof(int));
            STB_3D_ANIM_ASSERT(bone->children_indices != NULL);
            
            int child_index = 0;
            for (int j = 0; j < num_bones; ++j) {
                if (skin->bones[j].parent_index == i) {
                    bone->children_indices[child_index++] = j;
                    if (child_index == bone->num_children) break;
                }
            }
        }
    }
    
    return skin;
}

// Destroy a skin
void stb_3d_anim_destroy_skin(stb_3d_anim_skin* skin) {
    if (skin == NULL) return;
    
    // Destroy each bone
    for (int i = 0; i < skin->num_bones; ++i) {
        // Note: We don't free the bone's children_indices here because they're part of the skin's memory block
        STB_3D_ANIM_FREE(skin->bones[i].name);
        STB_3D_ANIM_FREE(skin->bones[i].inverse_bind_matrix);
    }
    
    STB_3D_ANIM_FREE(skin->bones);
    STB_3D_ANIM_FREE(skin->vertex_skins);
    STB_3D_ANIM_FREE(skin->bind_shape_matrix);
    STB_3D_ANIM_FREE(skin);
}

// Create a morph target
stb_3d_anim_morph_target* stb_3d_anim_create_morph_target(const char* name, int num_vertices, const float* positions, const float* normals) {
    STB_3D_ANIM_ASSERT(name != NULL);
    STB_3D_ANIM_ASSERT(positions != NULL);
    
    stb_3d_anim_morph_target* target = (stb_3d_anim_morph_target*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_morph_target));
    STB_3D_ANIM_ASSERT(target != NULL);
    memset(target, 0, sizeof(stb_3d_anim_morph_target));
    
    target->name = (char*)STB_3D_ANIM_MALLOC(strlen(name) + 1);
    STB_3D_ANIM_ASSERT(target->name != NULL);
    strcpy(target->name, name);
    
    target->num_vertices = num_vertices;
    
    // Allocate and copy positions
    target->positions = (float*)STB_3D_ANIM_MALLOC(num_vertices * 3 * sizeof(float));
    STB_3D_ANIM_ASSERT(target->positions != NULL);
    memcpy(target->positions, positions, num_vertices * 3 * sizeof(float));
    
    // Allocate and copy normals if provided
    if (normals != NULL) {
        target->normals = (float*)STB_3D_ANIM_MALLOC(num_vertices * 3 * sizeof(float));
        STB_3D_ANIM_ASSERT(target->normals != NULL);
        memcpy(target->normals, normals, num_vertices * 3 * sizeof(float));
    }
    
    return target;
}

// Destroy a morph target
void stb_3d_anim_destroy_morph_target(stb_3d_anim_morph_target* target) {
    if (target == NULL) return;
    
    STB_3D_ANIM_FREE(target->name);
    STB_3D_ANIM_FREE(target->positions);
    STB_3D_ANIM_FREE(target->normals);
    STB_3D_ANIM_FREE(target);
}

// Create a morph animation clip
stb_3d_anim_morph_clip* stb_3d_anim_create_morph_clip(const char* name, float duration, int num_targets, int* target_indices, float* target_weights) {
    STB_3D_ANIM_ASSERT(name != NULL);
    STB_3D_ANIM_ASSERT(target_indices != NULL);
    STB_3D_ANIM_ASSERT(target_weights != NULL);
    
    stb_3d_anim_morph_clip* clip = (stb_3d_anim_morph_clip*)STB_3D_ANIM_MALLOC(sizeof(stb_3d_anim_morph_clip));
    STB_3D_ANIM_ASSERT(clip != NULL);
    memset(clip, 0, sizeof(stb_3d_anim_morph_clip));
    
    clip->name = (char*)STB_3D_ANIM_MALLOC(strlen(name) + 1);
    STB_3D_ANIM_ASSERT(clip->name != NULL);
    strcpy(clip->name, name);
    
    clip->duration = duration;
    clip->num_targets = num_targets;
    clip->loop = 1; // Default to looping
    
    // Calculate number of keyframes per target
    int num_keyframes = (int)(duration + 0.5f) + 1; // Assuming 1 keyframe per second
    
    // Allocate and copy target indices
    clip->target_indices = (int*)STB_3D_ANIM_MALLOC(num_targets * sizeof(int));
    STB_3D_ANIM_ASSERT(clip->target_indices != NULL);
    memcpy(clip->target_indices, target_indices, num_targets * sizeof(int));
    
    // Allocate and copy target weights
    clip->target_weights = (float*)STB_3D_ANIM_MALLOC(num_targets * num_keyframes * sizeof(float));
    STB_3D_ANIM_ASSERT(clip->target_weights != NULL);
    memcpy(clip->target_weights, target_weights, num_targets * num_keyframes * sizeof(float));
    
    return clip;
}

// Destroy a morph animation clip
void stb_3d_anim_destroy_morph_clip(stb_3d_anim_morph_clip* clip) {
    if (clip == NULL) return;
    
    STB_3D_ANIM_FREE(clip->name);
    STB_3D_ANIM_FREE(clip->target_indices);
    STB_3D_ANIM_FREE(clip->target_weights);
    STB_3D_ANIM_FREE(clip);
}

// Utility functions
void stb_3d_anim_transform_identity(stb_3d_anim_transform* transform) {
    STB_3D_ANIM_ASSERT(transform != NULL);
    transform->position[0] = 0.0f;
    transform->position[1] = 0.0f;
    transform->position[2] = 0.0f;
    transform->rotation[0] = 0.0f;
    transform->rotation[1] = 0.0f;
    transform->rotation[2] = 0.0f;
    transform->rotation[3] = 1.0f;
    transform->scale[0] = 1.0f;
    transform->scale[1] = 1.0f;
    transform->scale[2] = 1.0f;
}

void stb_3d_anim_transform_multiply(const stb_3d_anim_transform* a, const stb_3d_anim_transform* b, stb_3d_anim_transform* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    // Convert transforms to matrices
    float mat_a[16];
    float mat_b[16];
    stb_3d_anim_transform_to_matrix(a, mat_a);
    stb_3d_anim_transform_to_matrix(b, mat_b);
    
    // Multiply matrices
    float mat_result[16];
    stb_3d_anim_matrix_multiply(mat_a, mat_b, mat_result);
    
    // Convert result back to transform
    stb_3d_anim_matrix_to_transform(mat_result, result);
}

void stb_3d_anim_transform_to_matrix(const stb_3d_anim_transform* transform, float* matrix) {
    STB_3D_ANIM_ASSERT(transform != NULL);
    STB_3D_ANIM_ASSERT(matrix != NULL);
    
    float x = transform->rotation[0];
    float y = transform->rotation[1];
    float z = transform->rotation[2];
    float w = transform->rotation[3];
    
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    
    // Column-major order
    matrix[0] = (1.0f - 2.0f * (yy + zz)) * transform->scale[0];
    matrix[1] = 2.0f * (xy + wz) * transform->scale[0];
    matrix[2] = 2.0f * (xz - wy) * transform->scale[0];
    matrix[3] = 0.0f;
    
    matrix[4] = 2.0f * (xy - wz) * transform->scale[1];
    matrix[5] = (1.0f - 2.0f * (xx + zz)) * transform->scale[1];
    matrix[6] = 2.0f * (yz + wx) * transform->scale[1];
    matrix[7] = 0.0f;
    
    matrix[8] = 2.0f * (xz + wy) * transform->scale[2];
    matrix[9] = 2.0f * (yz - wx) * transform->scale[2];
    matrix[10] = (1.0f - 2.0f * (xx + yy)) * transform->scale[2];
    matrix[11] = 0.0f;
    
    matrix[12] = transform->position[0];
    matrix[13] = transform->position[1];
    matrix[14] = transform->position[2];
    matrix[15] = 1.0f;
}

void stb_3d_anim_matrix_to_transform(const float* matrix, stb_3d_anim_transform* transform) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    STB_3D_ANIM_ASSERT(transform != NULL);
    
    // Extract position
    transform->position[0] = matrix[12];
    transform->position[1] = matrix[13];
    transform->position[2] = matrix[14];
    
    // Extract scale
    float sx = sqrtf(matrix[0] * matrix[0] + matrix[1] * matrix[1] + matrix[2] * matrix[2]);
    float sy = sqrtf(matrix[4] * matrix[4] + matrix[5] * matrix[5] + matrix[6] * matrix[6]);
    float sz = sqrtf(matrix[8] * matrix[8] + matrix[9] * matrix[9] + matrix[10] * matrix[10]);
    
    transform->scale[0] = (sx > 0.0001f) ? sx : 1.0f;
    transform->scale[1] = (sy > 0.0001f) ? sy : 1.0f;
    transform->scale[2] = (sz > 0.0001f) ? sz : 1.0f;
    
    // Extract rotation (quaternion)
    float trace = matrix[0] + matrix[5] + matrix[10];
    
    if (trace > 0.0f) {
        float s = 0.5f / sqrtf(trace + 1.0f);
        transform->rotation[3] = 0.25f / s;
        transform->rotation[0] = (matrix[6] - matrix[9]) * s;
        transform->rotation[1] = (matrix[8] - matrix[2]) * s;
        transform->rotation[2] = (matrix[1] - matrix[4]) * s;
    } else {
        if (matrix[0] > matrix[5] && matrix[0] > matrix[10]) {
            float s = 2.0f * sqrtf(1.0f + matrix[0] - matrix[5] - matrix[10]);
            transform->rotation[3] = (matrix[6] - matrix[9]) / s;
            transform->rotation[0] = 0.25f * s;
            transform->rotation[1] = (matrix[1] + matrix[4]) / s;
            transform->rotation[2] = (matrix[8] + matrix[2]) / s;
        } else if (matrix[5] > matrix[10]) {
            float s = 2.0f * sqrtf(1.0f + matrix[5] - matrix[0] - matrix[10]);
            transform->rotation[3] = (matrix[8] - matrix[2]) / s;
            transform->rotation[0] = (matrix[1] + matrix[4]) / s;
            transform->rotation[1] = 0.25f * s;
            transform->rotation[2] = (matrix[6] + matrix[9]) / s;
        } else {
            float s = 2.0f * sqrtf(1.0f + matrix[10] - matrix[0] - matrix[5]);
            transform->rotation[3] = (matrix[1] - matrix[4]) / s;
            transform->rotation[0] = (matrix[8] + matrix[2]) / s;
            transform->rotation[1] = (matrix[6] + matrix[9]) / s;
            transform->rotation[2] = 0.25f * s;
        }
    }
}

// Interpolation functions
void stb_3d_anim_interpolate_position(const float* a, const float* b, float t, float* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    result[0] = a[0] + t * (b[0] - a[0]);
    result[1] = a[1] + t * (b[1] - a[1]);
    result[2] = a[2] + t * (b[2] - a[2]);
}

void stb_3d_anim_interpolate_rotation(const float* a, const float* b, float t, float* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    // Quaternion slerp (spherical linear interpolation)
    float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    
    // If dot is negative, use the other hemisphere to get shortest path
    if (dot < 0.0f) {
        dot = -dot;
        float neg_b[4] = { -b[0], -b[1], -b[2], -b[3] };
        b = neg_b;
    }
    
    // Clamp dot to avoid numerical issues
    if (dot > 0.9995f) {
        // Use linear interpolation for small angles
        result[0] = a[0] + t * (b[0] - a[0]);
        result[1] = a[1] + t * (b[1] - a[1]);
        result[2] = a[2] + t * (b[2] - a[2]);
        result[3] = a[3] + t * (b[3] - a[3]);
        
        // Normalize
        float length = sqrtf(result[0] * result[0] + 
                           result[1] * result[1] + 
                           result[2] * result[2] + 
                           result[3] * result[3]);
        
        if (length > 0.0f) {
            result[0] /= length;
            result[1] /= length;
            result[2] /= length;
            result[3] /= length;
        }
        
        return;
    }
    
    float angle = acosf(dot);
    float sin_angle = sinf(angle);
    float sin_t_angle = sinf(t * angle);
    float sin_one_minus_t_angle = sinf((1.0f - t) * angle);
    
    result[0] = (sin_one_minus_t_angle * a[0] + sin_t_angle * b[0]) / sin_angle;
    result[1] = (sin_one_minus_t_angle * a[1] + sin_t_angle * b[1]) / sin_angle;
    result[2] = (sin_one_minus_t_angle * a[2] + sin_t_angle * b[2]) / sin_angle;
    result[3] = (sin_one_minus_t_angle * a[3] + sin_t_angle * b[3]) / sin_angle;
}

void stb_3d_anim_interpolate_scale(const float* a, const float* b, float t, float* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    result[0] = a[0] + t * (b[0] - a[0]);
    result[1] = a[1] + t * (b[1] - a[1]);
    result[2] = a[2] + t * (b[2] - a[2]);
}

void stb_3d_anim_interpolate_transform(const stb_3d_anim_transform* a, const stb_3d_anim_transform* b, float t, stb_3d_anim_transform* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    stb_3d_anim_interpolate_position(a->position, b->position, t, result->position);
    stb_3d_anim_interpolate_rotation(a->rotation, b->rotation, t, result->rotation);
    stb_3d_anim_interpolate_scale(a->scale, b->scale, t, result->scale);
}

// Matrix utility functions (4x4 matrices, column-major)
void stb_3d_anim_matrix_identity(float* matrix) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    memset(matrix, 0, 16 * sizeof(float));
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void stb_3d_anim_matrix_multiply(const float* a, const float* b, float* result) {
    STB_3D_ANIM_ASSERT(a != NULL);
    STB_3D_ANIM_ASSERT(b != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    // Column-major matrix multiplication
    result[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3];
    result[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3];
    result[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3];
    result[3] = a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3];
    
    result[4] = a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7];
    result[5] = a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7];
    result[6] = a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7];
    result[7] = a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7];
    
    result[8] = a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11];
    result[9] = a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11];
    result[10] = a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11];
    result[11] = a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11];
    
    result[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15];
    result[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15];
    result[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
    result[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];
}

void stb_3d_anim_matrix_translate(float* matrix, float x, float y, float z) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    
    float translate[16];
    stb_3d_anim_matrix_identity(translate);
    translate[12] = x;
    translate[13] = y;
    translate[14] = z;
    
    float result[16];
    stb_3d_anim_matrix_multiply(matrix, translate, result);
    memcpy(matrix, result, 16 * sizeof(float));
}

void stb_3d_anim_matrix_rotate(float* matrix, float x, float y, float z, float angle_radians) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    
    // Normalize axis
    float length = sqrtf(x * x + y * y + z * z);
    if (length < 0.0001f) return;
    
    x /= length;
    y /= length;
    z /= length;
    
    float sin_angle = sinf(angle_radians);
    float cos_angle = cosf(angle_radians);
    float one_minus_cos = 1.0f - cos_angle;
    
    // Create rotation matrix (column-major)
    float rotate[16] = {
        x * x * one_minus_cos + cos_angle, y * x * one_minus_cos + z * sin_angle, z * x * one_minus_cos - y * sin_angle, 0.0f,
        x * y * one_minus_cos - z * sin_angle, y * y * one_minus_cos + cos_angle, z * y * one_minus_cos + x * sin_angle, 0.0f,
        x * z * one_minus_cos + y * sin_angle, y * z * one_minus_cos - x * sin_angle, z * z * one_minus_cos + cos_angle, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float result[16];
    stb_3d_anim_matrix_multiply(matrix, rotate, result);
    memcpy(matrix, result, 16 * sizeof(float));
}

void stb_3d_anim_matrix_scale(float* matrix, float x, float y, float z) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    
    float scale[16];
    stb_3d_anim_matrix_identity(scale);
    scale[0] = x;
    scale[5] = y;
    scale[10] = z;
    
    float result[16];
    stb_3d_anim_matrix_multiply(matrix, scale, result);
    memcpy(matrix, result, 16 * sizeof(float));
}

void stb_3d_anim_matrix_inverse(const float* matrix, float* result) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    // Calculate determinant
    float det = matrix[0] * (matrix[5] * matrix[10] * matrix[15] + matrix[6] * matrix[11] * matrix[13] + matrix[7] * matrix[9] * matrix[14] - 
                          matrix[5] * matrix[11] * matrix[14] - matrix[6] * matrix[9] * matrix[15] - matrix[7] * matrix[10] * matrix[13]) - 
               matrix[1] * (matrix[4] * matrix[10] * matrix[15] + matrix[6] * matrix[11] * matrix[12] + matrix[7] * matrix[8] * matrix[14] - 
                          matrix[4] * matrix[11] * matrix[14] - matrix[6] * matrix[8] * matrix[15] - matrix[7] * matrix[10] * matrix[12]) + 
               matrix[2] * (matrix[4] * matrix[9] * matrix[15] + matrix[5] * matrix[11] * matrix[12] + matrix[7] * matrix[8] * matrix[13] - 
                          matrix[4] * matrix[11] * matrix[13] - matrix[5] * matrix[8] * matrix[15] - matrix[7] * matrix[9] * matrix[12]) - 
               matrix[3] * (matrix[4] * matrix[9] * matrix[14] + matrix[5] * matrix[10] * matrix[12] + matrix[6] * matrix[8] * matrix[13] - 
                          matrix[4] * matrix[10] * matrix[13] - matrix[5] * matrix[8] * matrix[14] - matrix[6] * matrix[9] * matrix[12]);
    
    if (det == 0.0f) {
        // Singular matrix, return identity
        stb_3d_anim_matrix_identity(result);
        return;
    }
    
    float inv_det = 1.0f / det;
    
    // Calculate inverse matrix (column-major)
    result[0] = (matrix[5] * matrix[10] * matrix[15] + matrix[6] * matrix[11] * matrix[13] + matrix[7] * matrix[9] * matrix[14] - 
                matrix[5] * matrix[11] * matrix[14] - matrix[6] * matrix[9] * matrix[15] - matrix[7] * matrix[10] * matrix[13]) * inv_det;
    
    result[1] = -(matrix[1] * matrix[10] * matrix[15] + matrix[2] * matrix[11] * matrix[13] + matrix[3] * matrix[9] * matrix[14] - 
                 matrix[1] * matrix[11] * matrix[14] - matrix[2] * matrix[9] * matrix[15] - matrix[3] * matrix[10] * matrix[13]) * inv_det;
    
    result[2] = (matrix[1] * matrix[6] * matrix[15] + matrix[2] * matrix[7] * matrix[13] + matrix[3] * matrix[5] * matrix[14] - 
                matrix[1] * matrix[7] * matrix[14] - matrix[2] * matrix[5] * matrix[15] - matrix[3] * matrix[6] * matrix[13]) * inv_det;
    
    result[3] = -(matrix[1] * matrix[6] * matrix[9] + matrix[2] * matrix[7] * matrix[8] + matrix[3] * matrix[5] * matrix[10] - 
                 matrix[1] * matrix[7] * matrix[10] - matrix[2] * matrix[5] * matrix[9] - matrix[3] * matrix[6] * matrix[8]) * inv_det;
    
    result[4] = -(matrix[4] * matrix[10] * matrix[15] + matrix[6] * matrix[11] * matrix[12] + matrix[7] * matrix[8] * matrix[14] - 
                 matrix[4] * matrix[11] * matrix[14] - matrix[6] * matrix[8] * matrix[15] - matrix[7] * matrix[10] * matrix[12]) * inv_det;
    
    result[5] = (matrix[0] * matrix[10] * matrix[15] + matrix[2] * matrix[11] * matrix[12] + matrix[3] * matrix[8] * matrix[14] - 
                matrix[0] * matrix[11] * matrix[14] - matrix[2] * matrix[8] * matrix[15] - matrix[3] * matrix[10] * matrix[12]) * inv_det;
    
    result[6] = -(matrix[0] * matrix[6] * matrix[15] + matrix[2] * matrix[7] * matrix[12] + matrix[3] * matrix[4] * matrix[14] - 
                 matrix[0] * matrix[7] * matrix[14] - matrix[2] * matrix[4] * matrix[15] - matrix[3] * matrix[6] * matrix[12]) * inv_det;
    
    result[7] = (matrix[0] * matrix[6] * matrix[8] + matrix[2] * matrix[7] * matrix[4] + matrix[3] * matrix[4] * matrix[10] - 
                matrix[0] * matrix[7] * matrix[10] - matrix[2] * matrix[4] * matrix[8] - matrix[3] * matrix[6] * matrix[4]) * inv_det;
    
    result[8] = (matrix[4] * matrix[9] * matrix[15] + matrix[5] * matrix[11] * matrix[12] + matrix[7] * matrix[8] * matrix[13] - 
                matrix[4] * matrix[11] * matrix[13] - matrix[5] * matrix[8] * matrix[15] - matrix[7] * matrix[9] * matrix[12]) * inv_det;
    
    result[9] = -(matrix[0] * matrix[9] * matrix[15] + matrix[1] * matrix[11] * matrix[12] + matrix[3] * matrix[8] * matrix[13] - 
                 matrix[0] * matrix[11] * matrix[13] - matrix[1] * matrix[8] * matrix[15] - matrix[3] * matrix[9] * matrix[12]) * inv_det;
    
    result[10] = (matrix[0] * matrix[5] * matrix[15] + matrix[1] * matrix[7] * matrix[12] + matrix[3] * matrix[4] * matrix[13] - 
                 matrix[0] * matrix[7] * matrix[13] - matrix[1] * matrix[4] * matrix[15] - matrix[3] * matrix[5] * matrix[12]) * inv_det;
    
    result[11] = -(matrix[0] * matrix[5] * matrix[8] + matrix[1] * matrix[7] * matrix[4] + matrix[3] * matrix[4] * matrix[9] - 
                  matrix[0] * matrix[7] * matrix[9] - matrix[1] * matrix[4] * matrix[8] - matrix[3] * matrix[5] * matrix[4]) * inv_det;
    
    result[12] = -(matrix[4] * matrix[9] * matrix[14] + matrix[5] * matrix[10] * matrix[12] + matrix[6] * matrix[8] * matrix[13] - 
                 matrix[4] * matrix[10] * matrix[13] - matrix[5] * matrix[8] * matrix[14] - matrix[6] * matrix[9] * matrix[12]) * inv_det;
    
    result[13] = (matrix[0] * matrix[9] * matrix[14] + matrix[1] * matrix[10] * matrix[12] + matrix[2] * matrix[8] * matrix[13] - 
                matrix[0] * matrix[10] * matrix[13] - matrix[1] * matrix[8] * matrix[14] - matrix[2] * matrix[9] * matrix[12]) * inv_det;
    
    result[14] = -(matrix[0] * matrix[5] * matrix[14] + matrix[1] * matrix[6] * matrix[12] + matrix[2] * matrix[4] * matrix[13] - 
                 matrix[0] * matrix[6] * matrix[13] - matrix[1] * matrix[4] * matrix[14] - matrix[2] * matrix[5] * matrix[12]) * inv_det;
    
    result[15] = (matrix[0] * matrix[5] * matrix[8] + matrix[1] * matrix[6] * matrix[4] + matrix[2] * matrix[4] * matrix[9] - 
                matrix[0] * matrix[6] * matrix[9] - matrix[1] * matrix[4] * matrix[8] - matrix[2] * matrix[5] * matrix[4]) * inv_det;
}

void stb_3d_anim_matrix_transpose(const float* matrix, float* result) {
    STB_3D_ANIM_ASSERT(matrix != NULL);
    STB_3D_ANIM_ASSERT(result != NULL);
    
    result[0] = matrix[0];
    result[1] = matrix[4];
    result[2] = matrix[8];
    result[3] = matrix[12];
    
    result[4] = matrix[1];
    result[5] = matrix[5];
    result[6] = matrix[9];
    result[7] = matrix[13];
    
    result[8] = matrix[2];
    result[9] = matrix[6];
    result[10] = matrix[10];
    result[11] = matrix[14];
    
    result[12] = matrix[3];
    result[13] = matrix[7];
    result[14] = matrix[11];
    result[15] = matrix[15];
}

#endif // STB_3D_ANIM_IMPLEMENTATION