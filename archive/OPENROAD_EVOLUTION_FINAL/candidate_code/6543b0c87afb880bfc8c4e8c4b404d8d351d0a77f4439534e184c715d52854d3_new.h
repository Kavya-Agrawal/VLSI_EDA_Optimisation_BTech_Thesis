// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25706313;
  double density_weight = 0.42467371;
  double prefix_weight = 0.29358841;
  double neighborhood_weight = 0.37898780;
  double late_weight = 0.24282755;
  double critical_weight = 0.14944712;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
