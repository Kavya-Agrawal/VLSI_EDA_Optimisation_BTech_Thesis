// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53398837;
  double density_weight = 0.39443779;
  double prefix_weight = 0.49059253;
  double neighborhood_weight = 0.28405770;
  double late_weight = 0.08531434;
  double critical_weight = 0.30069460;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
