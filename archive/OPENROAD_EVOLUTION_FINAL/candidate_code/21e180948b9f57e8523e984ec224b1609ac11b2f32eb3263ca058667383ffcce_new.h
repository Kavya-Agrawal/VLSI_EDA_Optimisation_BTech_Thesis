// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12866676;
  double density_weight = 0.29464221;
  double prefix_weight = 0.19615645;
  double neighborhood_weight = 0.24370859;
  double late_weight = 0.26829645;
  double critical_weight = 0.39346479;
  unsigned budget = 27;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
