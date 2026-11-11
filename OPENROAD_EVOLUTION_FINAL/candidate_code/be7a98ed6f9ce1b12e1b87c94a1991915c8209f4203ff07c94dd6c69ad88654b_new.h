// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37901523;
  double density_weight = 0.28996439;
  double prefix_weight = 0.00495193;
  double neighborhood_weight = 0.24831105;
  double late_weight = 0.27191897;
  double critical_weight = 0.27582259;
  unsigned budget = 16;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
