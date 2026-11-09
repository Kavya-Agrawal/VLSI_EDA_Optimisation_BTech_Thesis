// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84124417;
  double density_weight = 0.37843039;
  double prefix_weight = 0.18154394;
  double neighborhood_weight = 0.33344944;
  double late_weight = 0.21365059;
  double critical_weight = 0.35669857;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
