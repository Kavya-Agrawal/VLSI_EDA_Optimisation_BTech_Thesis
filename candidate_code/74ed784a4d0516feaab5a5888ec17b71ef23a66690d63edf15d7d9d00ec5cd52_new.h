// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99336250;
  double density_weight = 0.15838697;
  double prefix_weight = 0.20554716;
  double neighborhood_weight = 0.38704806;
  double late_weight = 0.01909204;
  double critical_weight = 0.30910400;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
