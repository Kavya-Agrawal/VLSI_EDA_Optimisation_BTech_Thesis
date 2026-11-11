// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85609705;
  double density_weight = 0.58235655;
  double prefix_weight = 0.39260035;
  double neighborhood_weight = 0.30627636;
  double late_weight = 0.15334141;
  double critical_weight = 0.07130756;
  unsigned budget = 26;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
