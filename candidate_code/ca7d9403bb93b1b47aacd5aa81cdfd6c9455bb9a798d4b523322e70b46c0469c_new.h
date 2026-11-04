// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34329676;
  double density_weight = 0.41725571;
  double prefix_weight = 0.13795735;
  double neighborhood_weight = 0.26385494;
  double late_weight = 0.00491372;
  double critical_weight = 0.34012961;
  unsigned budget = 24;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
