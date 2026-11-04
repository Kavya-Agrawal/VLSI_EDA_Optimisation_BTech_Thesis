// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79624757;
  double density_weight = 0.46546464;
  double prefix_weight = 0.28233981;
  double neighborhood_weight = 0.01880911;
  double late_weight = 0.08897866;
  double critical_weight = 0.28389138;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
