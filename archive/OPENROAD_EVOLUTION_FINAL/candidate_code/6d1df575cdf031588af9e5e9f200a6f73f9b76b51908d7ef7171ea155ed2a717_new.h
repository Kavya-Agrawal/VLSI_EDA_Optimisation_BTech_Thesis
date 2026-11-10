// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83251143;
  double density_weight = 0.12472891;
  double prefix_weight = 0.02563456;
  double neighborhood_weight = 0.02277199;
  double late_weight = 0.13773678;
  double critical_weight = 0.31499532;
  unsigned budget = 30;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
