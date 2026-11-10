// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47242664;
  double density_weight = 0.24688839;
  double prefix_weight = 0.19967399;
  double neighborhood_weight = 0.33436425;
  double late_weight = 0.02398594;
  double critical_weight = 0.33329108;
  unsigned budget = 27;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
