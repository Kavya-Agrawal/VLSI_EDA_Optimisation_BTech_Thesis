// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33676091;
  double density_weight = 0.20605069;
  double prefix_weight = 0.33695442;
  double neighborhood_weight = 0.00140838;
  double late_weight = 0.10378097;
  double critical_weight = 0.46726502;
  unsigned budget = 23;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
