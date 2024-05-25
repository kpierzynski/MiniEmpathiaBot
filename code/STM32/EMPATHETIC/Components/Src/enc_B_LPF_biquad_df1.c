/* MATLAB GENERATED SOURCE FILE: enc_B_LPF_biquad_df1.c */
#include "enc_B_LPF_biquad_df1.h"
// Filter state
uint32_t enc_B_LPF_STATE_UINT[4*ENC_B_LPF_NUM_STAGES] = {
  #include "enc_B_LPF_state_init.csv"
};
float32_t *enc_B_LPF_STATE = (float32_t*)enc_B_LPF_STATE_UINT;
// Filter coefficients
uint32_t enc_B_LPF_COEFFS_UINT[5*ENC_B_LPF_NUM_STAGES] = {
  #include "enc_B_LPF_coeffs.csv"
};
float32_t *enc_B_LPF_COEFFS = (float32_t*)enc_B_LPF_COEFFS_UINT;
// Filter instance
arm_biquad_casd_df1_inst_f32 enc_B_LPF;
