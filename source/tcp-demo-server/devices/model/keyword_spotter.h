/*
* Imagimob Studio 5.2.2058.65534+b51f1604b8ea06cce183b1e168da728c7506b77d
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 11/10/2024 15:32:19 UTC. Any changes will be lost.
* 
* Model ID  0ca24c76-28a8-4e2e-9eb4-d8a4d0f38756
* 
* Memory    Size                      Efficiency
* Buffers   9200 bytes (RAM)          100 %
* State     11592 bytes (RAM)         100 %
* Readonly  40516 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-0
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | down
* 2           | up
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [512]           float      dequeue
*    window_shape = [512]
*    stride = 160
*    buffer_multiplier = 1
* Hamming smoothing              [512]           float      dequeue
*    sym = True
* Real Discrete Fourier Transform [257,2]         float      dequeue
*    axis = 0
* Frobenius norm                 [257]           float      dequeue
*    axis = 0
* Mel Filterbank                 [40]            float      dequeue
*    num_filters = 40
*    sample_rate = 16000
*    f_low = 300
*    f_high = 8000
* Add Constant                   [40]            float      dequeue
*    A = 1
* Logarithm                      [40]            float      dequeue
* Clip                           [40]            float      dequeue
*    min = 0
*    max = 4
* Imagimob Speech Features       [40]            float      dequeue
*    output_freq = 100
*    output_features = 40
*    low_cut_freq = 300
*    high_cut_freq = 8000
* Sliding Window (data points)   [50,40]         float      dequeue
*    window_shape = [50,40]
*    stride = 280
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [50,40]         float      dequeue
*    contextual_length_sec = 0.5
*    prediction_freq = 14
* Input Layer                    [50,40]         float      dequeue
*    shape = [50,40]
* Convolution 1D                 [25,12]         float      dequeue
*    filters = 12
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,40,12]
* Batch Normalization            [25,12]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[12]
*    beta = float[12]
*    mean = float[12]
*    variance = float[12]
* Activation                     [25,12]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [25,24]         float      dequeue
*    filters = 24
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,12,24]
* Convolution 1D                 [25,24]         float      dequeue
*    filters = 24
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,24,24]
* Batch Normalization            [25,24]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[24]
*    beta = float[24]
*    mean = float[24]
*    variance = float[24]
* Activation                     [25,24]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [12,24]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,24,32]
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [12,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [12,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [6,32]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Global average pooling 1D      [32]            float      dequeue
*    trainable = True
* Dense                          [3]             float      dequeue
*    units = 3
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[32,3]
*    bias = float[3]
* Activation                     [3]             float      dequeue
*    activation = softmax
*    trainable = True
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[3].
* 
* int IMAI_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[1].
* 
* void IMAI_init(void)
*    Description: Initializes buffers to initial state. This function also works as a reset function.
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#ifndef _IMAI_MODEL_H_
#define _IMAI_MODEL_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>

typedef struct {    
    char *name;
    double TP; // True Positive or Correct Positive Prediction
    double FN; // False Negative or Incorrect Negative Prediction
    double FP; // False Positive or Incorrect Positive Prediction
    double TN; // True Negative or Correct Negative Prediction
    double TPR; // True Positive Rate or Sensitivity, Recall
    double TNR; // True Negative Rate or Specificity, Selectivity
    double PPV; // Positive Predictive Value or Precision
    double NPV; // Negative Predictive Value
    double FNR; // False Negative Rate or Miss Rate
    double FPR; // False Positive Rate or Fall-Out
    double FDR; // False Discovery Rate
    double FOR; // False Omission Rate
    double F1S; // F1 Score
} IMAI_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 95.231 %
* (F1S) F1 Score 95.519 %
* 
* Name of class                                            (unlabelled)             down               up
* (TP) True Positive or Correct Positive Prediction                7037              189              142
* (FN) False Negative or Incorrect Negative Prediction              251               54               64
* (FP) False Positive or Incorrect Positive Prediction              118              162               89
* (TN) True Negative or Correct Negative Prediction                 331             7332             7442
* (TPR) True Positive Rate or Sensitivity, Recall               96.56 %          77.78 %          68.93 %
* (TNR) True Negative Rate or Specificity, Selectivity          73.72 %          97.84 %          98.82 %
* (PPV) Positive Predictive Value or Precision                  98.35 %          53.85 %          61.47 %
* (NPV) Negative Predictive Value                               56.87 %          99.27 %          99.15 %
* (FNR) False Negative Rate or Miss Rate                         3.44 %          22.22 %          31.07 %
* (FPR) False Positive Rate or Fall-Out                         26.28 %           2.16 %           1.18 %
* (FDR) False Discovery Rate                                     1.65 %          46.15 %          38.53 %
* (FOR) False Omission Rate                                     43.13 %           0.73 %           0.85 %
* (F1S) F1 Score                                                97.45 %          63.64 %          64.99 %
*/


#define IMAI_TEST_AVG_ACC 0.9523070957735557 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9551911341233853 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "(unlabelled)", TP: 7037, FN: 251, FP: 118, TN: 331, TPR: 0.9655598243688, TNR: 0.7371937639198, PPV: 0.9835080363382, NPV: 0.5687285223367, FNR: 0.0344401756311, FPR: 0.2628062360801, FDR: 0.0164919636617, FOR: 0.4312714776632, F1S: 0.9744512912829, }, \
 {name: "down", TP: 189, FN: 54, FP: 162, TN: 7332, TPR: 0.7777777777777, TNR: 0.9783827061649, PPV: 0.5384615384615, NPV: 0.9926888708367, FNR: 0.2222222222222, FPR: 0.0216172938350, FDR: 0.4615384615384, FOR: 0.0073111291632, F1S: 0.6363636363636, }, \
 {name: "up", TP: 142, FN: 64, FP: 89, TN: 7442, TPR: 0.6893203883495, TNR: 0.9881821803213, PPV: 0.6147186147186, NPV: 0.9914734878763, FNR: 0.3106796116504, FPR: 0.0118178196786, FDR: 0.3852813852813, FOR: 0.0085265121236, F1S: 0.6498855835240, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.657 %
* (F1S) F1 Score 96.959 %
* 
* Name of class                                            (unlabelled)             down               up
* (TP) True Positive or Correct Positive Prediction               43424              875              857
* (FN) False Negative or Incorrect Negative Prediction             1254              131              177
* (FP) False Positive or Incorrect Positive Prediction              308              741              513
* (TN) True Negative or Correct Negative Prediction                1732            44971            45171
* (TPR) True Positive Rate or Sensitivity, Recall               97.19 %          86.98 %          82.88 %
* (TNR) True Negative Rate or Specificity, Selectivity          84.90 %          98.38 %          98.88 %
* (PPV) Positive Predictive Value or Precision                  99.30 %          54.15 %          62.55 %
* (NPV) Negative Predictive Value                               58.00 %          99.71 %          99.61 %
* (FNR) False Negative Rate or Miss Rate                         2.81 %          13.02 %          17.12 %
* (FPR) False Positive Rate or Fall-Out                         15.10 %           1.62 %           1.12 %
* (FDR) False Discovery Rate                                     0.70 %          45.85 %          37.45 %
* (FOR) False Omission Rate                                     42.00 %           0.29 %           0.39 %
* (F1S) F1 Score                                                98.23 %          66.74 %          71.30 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9665653495440729 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9695898120410905 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 43424, FN: 1254, FP: 308, TN: 1732, TPR: 0.9719324947401, TNR: 0.8490196078431, PPV: 0.9929571023506, NPV: 0.5800401875418, FNR: 0.0280675052598, FPR: 0.1509803921568, FDR: 0.0070428976493, FOR: 0.4199598124581, F1S: 0.9823323153489, }, \
 {name: "down", TP: 875, FN: 131, FP: 741, TN: 44971, TPR: 0.8697813121272, TNR: 0.9837898144907, PPV: 0.5414603960396, NPV: 0.9970954724845, FNR: 0.1302186878727, FPR: 0.0162101855092, FDR: 0.4585396039603, FOR: 0.0029045275154, F1S: 0.6674294431731, }, \
 {name: "up", TP: 857, FN: 177, FP: 513, TN: 45171, TPR: 0.8288201160541, TNR: 0.9887706855791, PPV: 0.6255474452554, NPV: 0.9960968510187, FNR: 0.1711798839458, FPR: 0.0112293144208, FDR: 0.3744525547445, FOR: 0.0039031489812, F1S: 0.7129783693843, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 96.595 %
* (F1S) F1 Score 96.901 %
* 
* Name of class                                            (unlabelled)             down               up
* (TP) True Positive or Correct Positive Prediction               13260              227              243
* (FN) False Negative or Incorrect Negative Prediction              370               50               64
* (FP) False Positive or Incorrect Positive Prediction              112              229              143
* (TN) True Negative or Correct Negative Prediction                 472            13708            13764
* (TPR) True Positive Rate or Sensitivity, Recall               97.29 %          81.95 %          79.15 %
* (TNR) True Negative Rate or Specificity, Selectivity          80.82 %          98.36 %          98.97 %
* (PPV) Positive Predictive Value or Precision                  99.16 %          49.78 %          62.95 %
* (NPV) Negative Predictive Value                               56.06 %          99.64 %          99.54 %
* (FNR) False Negative Rate or Miss Rate                         2.71 %          18.05 %          20.85 %
* (FPR) False Positive Rate or Fall-Out                         19.18 %           1.64 %           1.03 %
* (FDR) False Discovery Rate                                     0.84 %          50.22 %          37.05 %
* (FOR) False Omission Rate                                     43.94 %           0.36 %           0.46 %
* (F1S) F1 Score                                                98.21 %          61.94 %          70.13 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.9659490643028 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9690137997341234 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 13260, FN: 370, FP: 112, TN: 472, TPR: 0.9728539985326, TNR: 0.8082191780821, PPV: 0.9916242895602, NPV: 0.5605700712589, FNR: 0.0271460014673, FPR: 0.1917808219178, FDR: 0.0083757104397, FOR: 0.4394299287410, F1S: 0.9821494704095, }, \
 {name: "down", TP: 227, FN: 50, FP: 229, TN: 13708, TPR: 0.8194945848375, TNR: 0.9835689172705, PPV: 0.4978070175438, NPV: 0.9963657508358, FNR: 0.1805054151624, FPR: 0.0164310827294, FDR: 0.5021929824561, FOR: 0.0036342491641, F1S: 0.6193724420190, }, \
 {name: "up", TP: 243, FN: 64, FP: 143, TN: 13764, TPR: 0.7915309446254, TNR: 0.9897174084993, PPV: 0.6295336787564, NPV: 0.9953717095747, FNR: 0.2084690553745, FPR: 0.0102825915006, FDR: 0.3704663212435, FOR: 0.0046282904252, F1S: 0.7012987012987, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "down", "up"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x76, 0x4c, 0xa2, 0x0c, 0xa8, 0x28, 0x2e, 0x4e, 0x9e, 0xb4, 0xd8, 0xa4, 0xd0, 0xf3, 0x87, 0x56}

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_QDYN8	(0x31)
#define IMAGINET_TYPES_QDYN16	(0x32)
#define IMAGINET_TYPES_QDYN32	(0x34)

// data_in [1] (4 bytes)
#define IMAI_DATA_IN_COUNT (1)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// data_out [3] (12 bytes)
#define IMAI_DATA_OUT_COUNT (3)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (54)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
