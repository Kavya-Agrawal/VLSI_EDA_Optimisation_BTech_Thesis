// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34276922;
  double density_weight = 0.56852002;
  double prefix_weight = 0.39953908;
  double neighborhood_weight = 0.11159108;
  double late_weight = 0.23628604;
  double critical_weight = 0.06793037;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
