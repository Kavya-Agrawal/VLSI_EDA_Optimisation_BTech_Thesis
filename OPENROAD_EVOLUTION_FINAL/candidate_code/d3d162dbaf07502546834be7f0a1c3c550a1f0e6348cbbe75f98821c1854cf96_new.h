// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00662915;
  double density_weight = 0.54447801;
  double prefix_weight = 0.49049054;
  double neighborhood_weight = 0.20405114;
  double late_weight = 0.26945451;
  double critical_weight = 0.23149416;
  unsigned budget = 20;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
