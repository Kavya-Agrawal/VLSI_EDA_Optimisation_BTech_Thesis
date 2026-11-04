// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37128897;
  double density_weight = 0.09543965;
  double prefix_weight = 0.38775645;
  double neighborhood_weight = 0.11325183;
  double late_weight = 0.18666225;
  double critical_weight = 0.49460043;
  unsigned budget = 18;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
