// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49570683;
  double density_weight = 0.18303199;
  double prefix_weight = 0.04999590;
  double neighborhood_weight = 0.37336552;
  double late_weight = 0.04434858;
  double critical_weight = 0.33777054;
  unsigned budget = 5;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
