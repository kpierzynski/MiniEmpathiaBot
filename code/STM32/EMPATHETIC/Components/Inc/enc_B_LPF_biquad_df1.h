/* MATLAB GENERATED  HEADER FILE: enc_B_LPF_biquad_df1.h */
#ifndef INC_ENC_B_LPF_H_
#define INC_ENC_B_LPF_H_

#include "arm_math.h"

#define ENC_B_LPF_NUM_STAGES  1
#define ENC_B_LPF_BLOCK_SIZE  1
// Filter state
extern float32_t *enc_B_LPF_STATE;
// Filter coefficients
extern float32_t *enc_B_LPF_COEFFS;
// Filter instance
extern arm_biquad_casd_df1_inst_f32 enc_B_LPF;
#endif // INC_ENC_B_LPF_H_
