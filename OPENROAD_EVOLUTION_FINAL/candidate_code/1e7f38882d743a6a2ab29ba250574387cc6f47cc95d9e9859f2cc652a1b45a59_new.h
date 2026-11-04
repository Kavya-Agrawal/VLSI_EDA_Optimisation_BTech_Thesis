// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61031320;
  double density_weight = 0.42695444;
  double prefix_weight = 0.26213059;
  double neighborhood_weight = 0.21026204;
  double late_weight = 0.06215837;
  double critical_weight = 0.31759519;
  unsigned budget = 9;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
