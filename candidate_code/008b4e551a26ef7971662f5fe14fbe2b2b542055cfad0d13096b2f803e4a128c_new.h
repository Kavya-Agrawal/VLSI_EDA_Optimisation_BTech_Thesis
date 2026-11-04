// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98810384;
  double density_weight = 0.19598294;
  double prefix_weight = 0.39066662;
  double neighborhood_weight = 0.31749535;
  double late_weight = 0.08991956;
  double critical_weight = 0.31818816;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
