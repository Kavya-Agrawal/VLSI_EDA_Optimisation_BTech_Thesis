// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31316657;
  double density_weight = 0.49656921;
  double prefix_weight = 0.39351340;
  double neighborhood_weight = 0.03445388;
  double late_weight = 0.24855606;
  double critical_weight = 0.43224229;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
