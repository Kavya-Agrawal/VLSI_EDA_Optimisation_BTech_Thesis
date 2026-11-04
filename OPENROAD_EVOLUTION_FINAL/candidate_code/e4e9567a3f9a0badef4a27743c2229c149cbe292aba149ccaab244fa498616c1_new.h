// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40158927;
  double density_weight = 0.43869443;
  double prefix_weight = 0.12334477;
  double neighborhood_weight = 0.33963900;
  double late_weight = 0.09957835;
  double critical_weight = 0.49939958;
  unsigned budget = 31;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
