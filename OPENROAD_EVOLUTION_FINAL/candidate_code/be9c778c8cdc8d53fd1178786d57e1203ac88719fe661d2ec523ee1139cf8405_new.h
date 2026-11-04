// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03112029;
  double density_weight = 0.34531870;
  double prefix_weight = 0.46031767;
  double neighborhood_weight = 0.39461550;
  double late_weight = 0.03499348;
  double critical_weight = 0.40113711;
  unsigned budget = 35;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
