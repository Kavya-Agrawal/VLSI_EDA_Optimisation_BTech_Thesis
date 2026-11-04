// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26402724;
  double density_weight = 0.38977284;
  double prefix_weight = 0.40484385;
  double neighborhood_weight = 0.21431721;
  double late_weight = 0.01909857;
  double critical_weight = 0.40548453;
  unsigned budget = 5;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
