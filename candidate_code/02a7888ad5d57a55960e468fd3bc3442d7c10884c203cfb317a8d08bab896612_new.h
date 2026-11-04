// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77684697;
  double density_weight = 0.10689820;
  double prefix_weight = 0.26311981;
  double neighborhood_weight = 0.37248119;
  double late_weight = 0.21781777;
  double critical_weight = 0.26615691;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
