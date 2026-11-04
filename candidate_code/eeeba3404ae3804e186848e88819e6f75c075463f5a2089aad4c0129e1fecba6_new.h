// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30445391;
  double density_weight = 0.05590653;
  double prefix_weight = 0.23933585;
  double neighborhood_weight = 0.04476235;
  double late_weight = 0.06794838;
  double critical_weight = 0.15671967;
  unsigned budget = 19;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
