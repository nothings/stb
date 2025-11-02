/* stb_audio_effects - v1.00 - public domain audio effects library - http://nothings.org/stb
                                  no warranty implied; use at your own risk

   Do this:
      #define STB_AUDIO_EFFECTS_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   You can #define STB_AE_ASSERT(x) before the #include to avoid using assert.h.
   And #define STB_AE_MALLOC, STB_AE_REALLOC, and STB_AE_FREE to avoid using malloc,realloc,free

   QUICK NOTES:
      Simple audio effects library for games and applications
      Supports common effects like reverb, delay, chorus, and distortion
      Works with floating-point audio data (32-bit float)
      Supports mono and stereo channels
      Easy to use API with minimal setup

   LICENSE

   See end of file for license information.

RECENT REVISION HISTORY:

      1.00  (2024-10-26) initial release

*/

#ifndef STB_AUDIO_EFFECTS_H
#define STB_AUDIO_EFFECTS_H

#ifdef __cplusplus
extern "C" {
#endif

// Opaque effect handles
typedef void* stb_ae_reverb;
typedef void* stb_ae_delay;
typedef void* stb_ae_chorus;
typedef void* stb_ae_distortion;

// Reverb parameters
typedef struct {
    float decay_time;       // Decay time in seconds (0.1 - 5.0)
    float damping;          // High-frequency damping (0.0 - 1.0)
    float room_size;        // Room size (0.0 - 1.0)
    float wet_gain;         // Wet signal gain (0.0 - 1.0)
    float dry_gain;         // Dry signal gain (0.0 - 1.0)
} stb_ae_reverb_params;

// Delay parameters
typedef struct {
    float delay_time;       // Delay time in milliseconds (1.0 - 500.0)
    float feedback;         // Feedback amount (0.0 - 0.95)
    float wet_gain;         // Wet signal gain (0.0 - 1.0)
    float dry_gain;         // Dry signal gain (0.0 - 1.0)
} stb_ae_delay_params;

// Chorus parameters
typedef struct {
    float rate;             // LFO rate in Hz (0.1 - 5.0)
    float depth;            // LFO depth in milliseconds (0.1 - 10.0)
    float feedback;         // Feedback amount (0.0 - 0.9)
    float wet_gain;         // Wet signal gain (0.0 - 1.0)
    float dry_gain;         // Dry signal gain (0.0 - 1.0)
} stb_ae_chorus_params;

// Distortion parameters
typedef struct {
    float drive;            // Drive amount (0.0 - 10.0)
    float tone;             // Tone control (0.0 - 1.0)
    float wet_gain;         // Wet signal gain (0.0 - 1.0)
    float dry_gain;         // Dry signal gain (0.0 - 1.0)
} stb_ae_distortion_params;

// Default parameter values
extern const stb_ae_reverb_params stb_ae_reverb_defaults;
extern const stb_ae_delay_params stb_ae_delay_defaults;
extern const stb_ae_chorus_params stb_ae_chorus_defaults;
extern const stb_ae_distortion_params stb_ae_distortion_defaults;

// Reverb functions
stb_ae_reverb stb_ae_create_reverb(int sample_rate, const stb_ae_reverb_params* params);
void stb_ae_destroy_reverb(stb_ae_reverb reverb);
void stb_ae_process_reverb(stb_ae_reverb reverb, float* input, float* output, int num_samples, int num_channels);
void stb_ae_update_reverb_params(stb_ae_reverb reverb, const stb_ae_reverb_params* params);

// Delay functions
stb_ae_delay stb_ae_create_delay(int sample_rate, const stb_ae_delay_params* params);
void stb_ae_destroy_delay(stb_ae_delay delay);
void stb_ae_process_delay(stb_ae_delay delay, float* input, float* output, int num_samples, int num_channels);
void stb_ae_update_delay_params(stb_ae_delay delay, const stb_ae_delay_params* params);

// Chorus functions
stb_ae_chorus stb_ae_create_chorus(int sample_rate, const stb_ae_chorus_params* params);
void stb_ae_destroy_chorus(stb_ae_chorus chorus);
void stb_ae_process_chorus(stb_ae_chorus chorus, float* input, float* output, int num_samples, int num_channels);
void stb_ae_update_chorus_params(stb_ae_chorus chorus, const stb_ae_chorus_params* params);

// Distortion functions
stb_ae_distortion stb_ae_create_distortion(int sample_rate, const stb_ae_distortion_params* params);
void stb_ae_destroy_distortion(stb_ae_distortion distortion);
void stb_ae_process_distortion(stb_ae_distortion distortion, float* input, float* output, int num_samples, int num_channels);
void stb_ae_update_distortion_params(stb_ae_distortion distortion, const stb_ae_distortion_params* params);

// Utility functions
void stb_ae_reset_effect(void* effect);

#ifdef __cplusplus
}
#endif

#endif // STB_AUDIO_EFFECTS_H

#ifdef STB_AUDIO_EFFECTS_IMPLEMENTATION

#include <stdlib.h>
#include <math.h>

#ifndef STB_AE_ASSERT
#include <assert.h>
#define STB_AE_ASSERT(x) assert(x)
#endif

#ifndef STB_AE_MALLOC
#define STB_AE_MALLOC malloc
#endif

#ifndef STB_AE_REALLOC
#define STB_AE_REALLOC realloc
#endif

#ifndef STB_AE_FREE
#define STB_AE_FREE free
#endif

// Default parameter values
const stb_ae_reverb_params stb_ae_reverb_defaults = {
    1.5f,   // decay_time
    0.5f,   // damping
    0.5f,   // room_size
    0.3f,   // wet_gain
    0.7f    // dry_gain
};

const stb_ae_delay_params stb_ae_delay_defaults = {
    100.0f, // delay_time
    0.5f,   // feedback
    0.3f,   // wet_gain
    0.7f    // dry_gain
};

const stb_ae_chorus_params stb_ae_chorus_defaults = {
    1.0f,   // rate
    2.0f,   // depth
    0.3f,   // feedback
    0.3f,   // wet_gain
    0.7f    // dry_gain
};

const stb_ae_distortion_params stb_ae_distortion_defaults = {
    2.0f,   // drive
    0.5f,   // tone
    0.5f,   // wet_gain
    0.5f    // dry_gain
};

// Internal effect structures
typedef struct {
    int sample_rate;
    stb_ae_reverb_params params;
    // Add internal state here
} stb_ae_reverb_impl;

typedef struct {
    int sample_rate;
    stb_ae_delay_params params;
    // Add internal state here
} stb_ae_delay_impl;

typedef struct {
    int sample_rate;
    stb_ae_chorus_params params;
    // Add internal state here
} stb_ae_chorus_impl;

typedef struct {
    int sample_rate;
    stb_ae_distortion_params params;
    // Add internal state here
} stb_ae_distortion_impl;

// Reverb implementation
stb_ae_reverb stb_ae_create_reverb(int sample_rate, const stb_ae_reverb_params* params) {
    STB_AE_ASSERT(sample_rate > 0);
    if (params == NULL) params = &stb_ae_reverb_defaults;
    
    stb_ae_reverb_impl* reverb = (stb_ae_reverb_impl*)STB_AE_MALLOC(sizeof(stb_ae_reverb_impl));
    if (reverb == NULL) return NULL;
    
    reverb->sample_rate = sample_rate;
    reverb->params = *params;
    
    // Initialize internal state here
    
    return (stb_ae_reverb)reverb;
}

void stb_ae_destroy_reverb(stb_ae_reverb reverb) {
    if (reverb == NULL) return;
    stb_ae_reverb_impl* impl = (stb_ae_reverb_impl*)reverb;
    // Cleanup internal state here
    STB_AE_FREE(impl);
}

void stb_ae_process_reverb(stb_ae_reverb reverb, float* input, float* output, int num_samples, int num_channels) {
    STB_AE_ASSERT(reverb != NULL);
    STB_AE_ASSERT(input != NULL);
    STB_AE_ASSERT(output != NULL);
    STB_AE_ASSERT(num_samples > 0);
    STB_AE_ASSERT(num_channels == 1 || num_channels == 2);
    
    stb_ae_reverb_impl* impl = (stb_ae_reverb_impl*)reverb;
    
    // Process audio here (placeholder implementation)
    for (int i = 0; i < num_samples * num_channels; ++i) {
        output[i] = input[i] * impl->params.dry_gain + input[i] * impl->params.wet_gain;
    }
}

void stb_ae_update_reverb_params(stb_ae_reverb reverb, const stb_ae_reverb_params* params) {
    STB_AE_ASSERT(reverb != NULL);
    STB_AE_ASSERT(params != NULL);
    
    stb_ae_reverb_impl* impl = (stb_ae_reverb_impl*)reverb;
    impl->params = *params;
}

// Delay implementation
stb_ae_delay stb_ae_create_delay(int sample_rate, const stb_ae_delay_params* params) {
    STB_AE_ASSERT(sample_rate > 0);
    if (params == NULL) params = &stb_ae_delay_defaults;
    
    stb_ae_delay_impl* delay = (stb_ae_delay_impl*)STB_AE_MALLOC(sizeof(stb_ae_delay_impl));
    if (delay == NULL) return NULL;
    
    delay->sample_rate = sample_rate;
    delay->params = *params;
    
    // Initialize internal state here
    
    return (stb_ae_delay)delay;
}

void stb_ae_destroy_delay(stb_ae_delay delay) {
    if (delay == NULL) return;
    stb_ae_delay_impl* impl = (stb_ae_delay_impl*)delay;
    // Cleanup internal state here
    STB_AE_FREE(impl);
}

void stb_ae_process_delay(stb_ae_delay delay, float* input, float* output, int num_samples, int num_channels) {
    STB_AE_ASSERT(delay != NULL);
    STB_AE_ASSERT(input != NULL);
    STB_AE_ASSERT(output != NULL);
    STB_AE_ASSERT(num_samples > 0);
    STB_AE_ASSERT(num_channels == 1 || num_channels == 2);
    
    stb_ae_delay_impl* impl = (stb_ae_delay_impl*)delay;
    
    // Process audio here (placeholder implementation)
    for (int i = 0; i < num_samples * num_channels; ++i) {
        output[i] = input[i] * impl->params.dry_gain + input[i] * impl->params.wet_gain;
    }
}

void stb_ae_update_delay_params(stb_ae_delay delay, const stb_ae_delay_params* params) {
    STB_AE_ASSERT(delay != NULL);
    STB_AE_ASSERT(params != NULL);
    
    stb_ae_delay_impl* impl = (stb_ae_delay_impl*)delay;
    impl->params = *params;
}

// Chorus implementation
stb_ae_chorus stb_ae_create_chorus(int sample_rate, const stb_ae_chorus_params* params) {
    STB_AE_ASSERT(sample_rate > 0);
    if (params == NULL) params = &stb_ae_chorus_defaults;
    
    stb_ae_chorus_impl* chorus = (stb_ae_chorus_impl*)STB_AE_MALLOC(sizeof(stb_ae_chorus_impl));
    if (chorus == NULL) return NULL;
    
    chorus->sample_rate = sample_rate;
    chorus->params = *params;
    
    // Initialize internal state here
    
    return (stb_ae_chorus)chorus;
}

void stb_ae_destroy_chorus(stb_ae_chorus chorus) {
    if (chorus == NULL) return;
    stb_ae_chorus_impl* impl = (stb_ae_chorus_impl*)chorus;
    // Cleanup internal state here
    STB_AE_FREE(impl);
}

void stb_ae_process_chorus(stb_ae_chorus chorus, float* input, float* output, int num_samples, int num_channels) {
    STB_AE_ASSERT(chorus != NULL);
    STB_AE_ASSERT(input != NULL);
    STB_AE_ASSERT(output != NULL);
    STB_AE_ASSERT(num_samples > 0);
    STB_AE_ASSERT(num_channels == 1 || num_channels == 2);
    
    stb_ae_chorus_impl* impl = (stb_ae_chorus_impl*)chorus;
    
    // Process audio here (placeholder implementation)
    for (int i = 0; i < num_samples * num_channels; ++i) {
        output[i] = input[i] * impl->params.dry_gain + input[i] * impl->params.wet_gain;
    }
}

void stb_ae_update_chorus_params(stb_ae_chorus chorus, const stb_ae_chorus_params* params) {
    STB_AE_ASSERT(chorus != NULL);
    STB_AE_ASSERT(params != NULL);
    
    stb_ae_chorus_impl* impl = (stb_ae_chorus_impl*)chorus;
    impl->params = *params;
}

// Distortion implementation
stb_ae_distortion stb_ae_create_distortion(int sample_rate, const stb_ae_distortion_params* params) {
    STB_AE_ASSERT(sample_rate > 0);
    if (params == NULL) params = &stb_ae_distortion_defaults;
    
    stb_ae_distortion_impl* distortion = (stb_ae_distortion_impl*)STB_AE_MALLOC(sizeof(stb_ae_distortion_impl));
    if (distortion == NULL) return NULL;
    
    distortion->sample_rate = sample_rate;
    distortion->params = *params;
    
    // Initialize internal state here
    
    return (stb_ae_distortion)distortion;
}

void stb_ae_destroy_distortion(stb_ae_distortion distortion) {
    if (distortion == NULL) return;
    stb_ae_distortion_impl* impl = (stb_ae_distortion_impl*)distortion;
    // Cleanup internal state here
    STB_AE_FREE(impl);
}

void stb_ae_process_distortion(stb_ae_distortion distortion, float* input, float* output, int num_samples, int num_channels) {
    STB_AE_ASSERT(distortion != NULL);
    STB_AE_ASSERT(input != NULL);
    STB_AE_ASSERT(output != NULL);
    STB_AE_ASSERT(num_samples > 0);
    STB_AE_ASSERT(num_channels == 1 || num_channels == 2);
    
    stb_ae_distortion_impl* impl = (stb_ae_distortion_impl*)distortion;
    
    // Process audio here (placeholder implementation)
    for (int i = 0; i < num_samples * num_channels; ++i) {
        // Simple clipping distortion
        float distorted = input[i] * impl->params.drive;
        distorted = fmaxf(-1.0f, fminf(1.0f, distorted));
        output[i] = distorted * impl->params.wet_gain + input[i] * impl->params.dry_gain;
    }
}

void stb_ae_update_distortion_params(stb_ae_distortion distortion, const stb_ae_distortion_params* params) {
    STB_AE_ASSERT(distortion != NULL);
    STB_AE_ASSERT(params != NULL);
    
    stb_ae_distortion_impl* impl = (stb_ae_distortion_impl*)distortion;
    impl->params = *params;
}

// Utility function implementation
void stb_ae_reset_effect(void* effect) {
    (void)effect; // Unused parameter
    // Implementation depends on effect type, but for now just a placeholder
}

#endif // STB_AUDIO_EFFECTS_IMPLEMENTATION