// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55934507;
  double density_weight = 0.39502358;
  double prefix_weight = 0.12472562;
  double neighborhood_weight = 0.03777679;
  double late_weight = 0.27800164;
  double critical_weight = 0.39927671;
  unsigned budget = 28;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
