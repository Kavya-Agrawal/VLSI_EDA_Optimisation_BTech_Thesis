// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61912502;
  double density_weight = 0.08385202;
  double prefix_weight = 0.34414385;
  double neighborhood_weight = 0.30703050;
  double late_weight = 0.05896307;
  double critical_weight = 0.45614000;
  unsigned budget = 18;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
