// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26612958;
  double density_weight = 0.47469787;
  double prefix_weight = 0.06733006;
  double neighborhood_weight = 0.29584155;
  double late_weight = 0.08272676;
  double critical_weight = 0.20694199;
  unsigned budget = 30;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
