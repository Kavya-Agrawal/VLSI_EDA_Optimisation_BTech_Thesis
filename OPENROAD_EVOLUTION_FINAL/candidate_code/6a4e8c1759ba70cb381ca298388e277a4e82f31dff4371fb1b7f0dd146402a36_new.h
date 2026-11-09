// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41726324;
  double density_weight = 0.52867682;
  double prefix_weight = 0.09005550;
  double neighborhood_weight = 0.35851343;
  double late_weight = 0.01631059;
  double critical_weight = 0.07085641;
  unsigned budget = 36;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
