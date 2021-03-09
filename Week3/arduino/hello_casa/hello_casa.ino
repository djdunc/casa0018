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



/*  These applications rely on having the Arduino_TensorFlowLite library installed 
 *  https://www.tensorflow.org/lite/microcontrollers
 *  
 *  Go to "Tools>Manage Libraries" and search for Arduino_TensorFlowLite and hit install if you dont have it installed
*/
#include <TensorFlowLite.h>

// we are including our model in a seperate file to keep the code simpler
#include "model.h"
// we are using a variety of functions from the TensorFlowLite library and need to reference them here
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"


/* 
 * In the code below we are defining a number of global variables that we will be using in the sketch 
 */

// Define the variables used by TFLite (pointers)
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;


// Create an area of memory to use for input, output, and intermediate arrays. 
const int kTensorArenaSize = (2 * 1024);
uint8_t tensor_arena[kTensorArenaSize];

// This constant represents the range of x values our model was trained on,
// which is from 0 to (2 * Pi). We approximate Pi to avoid requiring additional libraries.
const float kXrange = 2.f * 3.14159265359f;

// This constant determines number of inferences to perform across range of x values defined above. 
const int kInferencesPerCycle = 8000;

// A counter to keep track of how many inferences we have performed.
int inference_count = 0;


// The pin of the Arduino's built-in LED
int led = LED_BUILTIN;





/*
 * Initialise the sketch - all this code is run once at start-up
 */

void setup() {

  // Set up a tflite mirco error reporter to allow us to log / display data to the terminal. 
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;


  // Load in the model we have defined in the model.cpp file and map it into a usable data structure. 
  model = tflite::GetModel(g_model);


  // Check to see if the model is valid using the version function in the library and 
  // if not valid then break out of setup since the code probably will not work!
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  
  // This pulls in all the operation implementations we need (e.g. ReLU, SoftMax)
  // (for more detail on what is available see all_ops_resolver.cc in TensorFlow library)
  // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/micro/all_ops_resolver.cc
  static tflite::AllOpsResolver resolver;


  // Build an interpreter to run the model with and 
  // create a variable that points to the address of that interpreter.
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


/*
 * The main loop - this will run forever.
 */

void loop() {


  /*
   * The Loop has five main steps:
   *  - work out an input x value
   *  - convert that input value to be the same as the model type (quantized)
   *  - invoke the interpreter to work out an output given an input
   *  - convert the output back into a number between -1 and 1
   *  - map the output into a value between 0 and 255 to change LED brightness
   */

  
/*   
 *  Step 1: work out an input x value 
 */
  // Calculate an x value to feed into the model. 
  // Position is a number between 0 and 1 depending on how far through the
  // inference count cycle we are.
  // We then mulitply that by our range factor to map it between 0 and 2PI.
  // (ie the range of possible x values the model was trained on)
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;


/*
 *  Step 2: convert that input value to be the same as the model type (quantized)
 */  
  // Quantize the input from floating-point to integer 
  int8_t x_quantized = x_val / input->params.scale + input->params.zero_point;
  
  // Place the quantized input in the model's input tensor
  input->data.int8[0] = x_quantized;

 
/*  
 *  Step 3: invoke the interpreter to work out an output given an input 
 */
  // Run inference, and if an error: report it and break out of loop
  TfLiteStatus invoke_status = interpreter->Invoke();

  // Check to see if invoke went ok                       
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",
                         static_cast<double>(x_val));   
    return;
  }


/* 
 *  Step 4: convert the output back into a number between -1 and 1
 */
  
  // Obtain the quantized output from model's output tensor
  int8_t y_quantized = output->data.int8[0];

  // Dequantize the output from integer to floating-point
  float y_val = (y_quantized - output->params.zero_point) * output->params.scale;


/*
 *  Step 5: map the output into a value between 0 and 255 to change LED brightness
 */
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
