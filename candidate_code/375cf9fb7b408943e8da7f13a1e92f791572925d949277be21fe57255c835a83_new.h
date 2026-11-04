// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70641143;
  double density_weight = 0.23925940;
  double prefix_weight = 0.04322453;
  double neighborhood_weight = 0.32653889;
  double late_weight = 0.16328979;
  double critical_weight = 0.01467850;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
