/*   
 *   Hello CASA - DL4SN example
 *   Duncan Wilson
 *   November 2020
 *   
 *   Simplified version of the TinyML Hello World code in Ch5 of TinyML book and based on 
 *   example at https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world
 *   
 *   some code and abstraction removed to make it simpler
*/

// These applications rely on having the Arduino_TensorFlowLite library installed
// https://www.tensorflow.org/lite/microcontrollers
#include <TensorFlowLite.h>

#include "model.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"


// Define the variables used by TFLite (pointers)
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;


// Create an area of memory to use for input, output, and intermediate arrays. After allocating 
// tensors you can retrieve this value by invoking interpreter.arena_used_bytes().
const int kTensorArenaSize = (2 * 1024);
uint8_t tensor_arena[kTensorArenaSize];


// The pin of the Arduino's built-in LED
int led = LED_BUILTIN;


// This constant represents the range of x values our model was trained on,
// which is from 0 to (2 * Pi). We approximate Pi to avoid requiring additional libraries.
const float kXrange = 2.f * 3.14159265359f;


// This constant determines number of inferences to perform across range of x values defined above. 
const int kInferencesPerCycle = 2000;


// A counter to keep track of how many inferences we have performed.
int inference_count = 0;

// Initialise the sketch - all this code is run once at start-up
void setup() {

  // Set up logging. 
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;


  // Map the model into a usable data structure. 
  model = tflite::GetModel(g_model);


  // Check to see if valid model and if not break out of setup
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  
  // This pulls in all the operation implementations we need (see all_ops_resolver.cc in TensorFlow)
  static tflite::AllOpsResolver resolver;


  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;


  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }


  // Obtain pointers to the model's input and output tensors. 
  // We have one tensor so our input and output reference item 0.
  input = interpreter->input(0);
  output = interpreter->output(0);


  // initialise inference counter to 0.
  inference_count = 0;


  // Set the LED pin to output
  pinMode(led, OUTPUT);  

}



// The main loop - this will run forever.
void loop() {

  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;

  // Quantize the input from floating-point to integer 
  int8_t x_quantized = x_val / input->params.scale + input->params.zero_point;
  
  // Place the quantized input in the model's input tensor
  input->data.int8[0] = x_quantized;

  // Run inference, and if an error: report it and break out of loop
  TfLiteStatus invoke_status = interpreter->Invoke();


  // Check to see if invoke went ok                       
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",
                         static_cast<double>(x_val));   
    return;
  }


  // Obtain the quantized output from model's output tensor
  int8_t y_quantized = output->data.int8[0];

  // Dequantize the output from integer to floating-point
  float y_val = (y_quantized - output->params.zero_point) * output->params.scale;


  // Calculate the brightness of the LED such that y=-1 is fully off
  // and y=1 is fully on. The LED's brightness can range from 0-255.
  int brightness = (int)(127.5f * (y_val + 1));

  // Need to make sure that the brightness is within the limits of PWM 0-255
  // Depending on model results y_val can be less than -1.0 and greater than 1.0 
  brightness = constrain(brightness, 0, 255);
  

  // Set the brightness of the LED. If the specified pin does not support PWM,
  // this will result in the LED being on when y > 127, off otherwise.
  analogWrite(led, brightness);


  // Log the current brightness value for display in the Arduino plotter
  TF_LITE_REPORT_ERROR(error_reporter, "%d\n", brightness);


  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;
 
}
