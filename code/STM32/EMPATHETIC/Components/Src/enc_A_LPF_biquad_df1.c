/* MATLAB GENERATED SOURCE FILE: enc_A_LPF_biquad_df1.c */
#include "enc_A_LPF_biquad_df1.h"
// Filter state
uint32_t enc_A_LPF_STATE_UINT[4*ENC_A_LPF_NUM_STAGES] = {
  #include "enc_A_LPF_state_init.csv"
};
float32_t *enc_A_LPF_STATE = (float32_t*)enc_A_LPF_STATE_UINT;
// Filter coefficients
uint32_t enc_A_LPF_COEFFS_UINT[5*ENC_A_LPF_NUM_STAGES] = {
  #include "enc_A_LPF_coeffs.csv"
};
float32_t *enc_A_LPF_COEFFS = (float32_t*)enc_A_LPF_COEFFS_UINT;
// Filter instance
arm_biquad_casd_df1_inst_f32 enc_A_LPF;
