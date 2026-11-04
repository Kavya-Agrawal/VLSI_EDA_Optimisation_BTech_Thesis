// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22384508;
  double density_weight = 0.00321285;
  double prefix_weight = 0.17933123;
  double neighborhood_weight = 0.39407001;
  double late_weight = 0.03246050;
  double critical_weight = 0.46993997;
  unsigned budget = 36;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
