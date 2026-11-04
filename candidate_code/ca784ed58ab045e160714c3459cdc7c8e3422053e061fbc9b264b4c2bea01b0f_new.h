// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55985123;
  double density_weight = 0.40500258;
  double prefix_weight = 0.14437644;
  double neighborhood_weight = 0.16630622;
  double late_weight = 0.04887439;
  double critical_weight = 0.25906770;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
