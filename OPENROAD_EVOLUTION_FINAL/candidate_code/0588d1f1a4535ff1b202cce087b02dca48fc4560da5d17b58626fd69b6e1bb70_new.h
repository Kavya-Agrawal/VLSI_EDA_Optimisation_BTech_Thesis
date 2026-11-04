// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08521149;
  double density_weight = 0.25670006;
  double prefix_weight = 0.42547248;
  double neighborhood_weight = 0.23136312;
  double late_weight = 0.23892376;
  double critical_weight = 0.18930789;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
