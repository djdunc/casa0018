/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// added for bug report https://github.com/tensorflow/tensorflow/pull/45878/commits/a5ec390b56bc7afaab4429bf0bd69dece30f8980
// #include <algorithm>

#include "feature_provider.h"

#include "audio_provider.h"
#include "micro_features_micro_features_generator.h"
#include "micro_features_micro_model_settings.h"

FeatureProvider::FeatureProvider(int feature_size, int8_t* feature_data)
    : feature_size_(feature_size),
      feature_data_(feature_data),
      is_first_run_(true) {
  // Initialize the feature data to default values.
  for (int n = 0; n < feature_size_; ++n) {
    feature_data_[n] = 0;
  }
}

FeatureProvider::~FeatureProvider() {}


/*
  Feature provider converts raw audio from audio_provider in spectrograms
  For a description of this process see TinyML Ch7 p142-145

 - Runs continuously, only updates features between now and last time ran 
 - Takes 30ms samples @ 16KHz therefore 16000*0.03 = 480 samples
 - To create a row of data in Spectrogram, run 30ms of audio through FFT
 - FFT (micro_features/micro_features_generator.cpp) analyses frequency 
    into 256 buckets, then averages into groups of 6 = 43 buckets 
 - Our kMaxAudioSampleSize size is 512 (but our audio is in first 480 samples) 
    so take first 40 of 43 buckets.
 - That data fills the first row of the spectrogam 
 - To build the 2D array this is repeater 49 times to build ~1 second of data
    (20ms*49 + 10ms overlap in final window = 990ms)
*/

TfLiteStatus FeatureProvider::PopulateFeatureData(
    tflite::ErrorReporter* error_reporter, int32_t last_time_in_ms,
    int32_t time_in_ms, int* how_many_new_slices) {
  if (feature_size_ != kFeatureElementCount) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Requested feature_data_ size %d doesn't match %d",
                         feature_size_, kFeatureElementCount);
    return kTfLiteError;
  }

  // Quantize the time into steps as long as each window stride, so we can
  // figure out which audio data we need to fetch.
  //const int last_step = (last_time_in_ms / kFeatureSliceStrideMs);
  //const int current_step = (time_in_ms / kFeatureSliceStrideMs);
  
  // change based on bug report at https://github.com/tensorflow/tensorflow/pull/45878/commits/9fe6428a70ebb78fb471c5ddf8ff3d6fb7f8b14d
  const int last_step = (last_time_in_ms - kFeatureSliceDurationMs) / kFeatureSliceStrideMs;
  const int current_step = (time_in_ms - kFeatureSliceDurationMs) / kFeatureSliceStrideMs;
   



  int slices_needed = current_step - last_step;
  // If this is the first call, make sure we don't use any cached information.
  if (is_first_run_) {
    TfLiteStatus init_status = InitializeMicroFeatures(error_reporter);
    if (init_status != kTfLiteOk) {
      return init_status;
    }
    is_first_run_ = false;
    slices_needed = kFeatureSliceCount;
  }
  if (slices_needed > kFeatureSliceCount) {
    slices_needed = kFeatureSliceCount;
  }
  *how_many_new_slices = slices_needed;

  const int slices_to_keep = kFeatureSliceCount - slices_needed;
  const int slices_to_drop = kFeatureSliceCount - slices_to_keep;
  // If we can avoid recalculating some slices, just move the existing data
  // up in the spectrogram, to perform something like this:
  // last time = 80ms          current time = 120ms
  // +-----------+             +-----------+
  // | data@20ms |         --> | data@60ms |
  // +-----------+       --    +-----------+
  // | data@40ms |     --  --> | data@80ms |
  // +-----------+   --  --    +-----------+
  // | data@60ms | --  --      |  <empty>  |
  // +-----------+   --        +-----------+
  // | data@80ms | --          |  <empty>  |
  // +-----------+             +-----------+
  if (slices_to_keep > 0) {
    for (int dest_slice = 0; dest_slice < slices_to_keep; ++dest_slice) {
      int8_t* dest_slice_data =
          feature_data_ + (dest_slice * kFeatureSliceSize);
      const int src_slice = dest_slice + slices_to_drop;
      const int8_t* src_slice_data =
          feature_data_ + (src_slice * kFeatureSliceSize);
      for (int i = 0; i < kFeatureSliceSize; ++i) {
        dest_slice_data[i] = src_slice_data[i];
      }
    }
  }
  // Any slices that need to be filled in with feature data have their
  // appropriate audio data pulled, and features calculated for that slice.
  if (slices_needed > 0) {
    for (int new_slice = slices_to_keep; new_slice < kFeatureSliceCount;
         ++new_slice) {

      
      const int new_step = (current_step - kFeatureSliceCount + 1) + new_slice;
      // added for bug report https://github.com/tensorflow/tensorflow/pull/45878/commits/a5ec390b56bc7afaab4429bf0bd69dece30f8980
      //const int new_step = std::max(0, (current_step - kFeatureSliceCount + 1) + new_slice);

      
      const int32_t slice_start_ms = (new_step * kFeatureSliceStrideMs);
      int16_t* audio_samples = nullptr;
      int audio_samples_size = 0;
      
      
      // TODO(petewarden): Fix bug that leads to non-zero slice_start_ms
      GetAudioSamples(error_reporter, (slice_start_ms > 0 ? slice_start_ms : 0),
                      kFeatureSliceDurationMs, &audio_samples_size,
                      &audio_samples);
      // added for bug report https://github.com/tensorflow/tensorflow/pull/45878/commits/a5ec390b56bc7afaab4429bf0bd69dece30f8980
      //GetAudioSamples(error_reporter, slice_start_ms,
      //                 kFeatureSliceDurationMs, &audio_samples_size,
      //                 &audio_samples);                
      
      if (audio_samples_size < kMaxAudioSampleSize) {
        TF_LITE_REPORT_ERROR(error_reporter,
                             "Audio data size %d too small, want %d",
                             audio_samples_size, kMaxAudioSampleSize);
        return kTfLiteError;
      }
      int8_t* new_slice_data = feature_data_ + (new_slice * kFeatureSliceSize);
      size_t num_samples_read;
      TfLiteStatus generate_status = GenerateMicroFeatures(
          error_reporter, audio_samples, audio_samples_size, kFeatureSliceSize,
          new_slice_data, &num_samples_read);
      if (generate_status != kTfLiteOk) {
        return generate_status;
      }
    }
  }
  return kTfLiteOk;
}
