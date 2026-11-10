// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18300312;
  double density_weight = 0.36178801;
  double prefix_weight = 0.14501653;
  double neighborhood_weight = 0.31277773;
  double late_weight = 0.29210936;
  double critical_weight = 0.29398584;
  unsigned budget = 10;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
