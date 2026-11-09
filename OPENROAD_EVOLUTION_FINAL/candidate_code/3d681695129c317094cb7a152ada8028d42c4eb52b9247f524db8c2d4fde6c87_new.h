// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64398730;
  double density_weight = 0.32470237;
  double prefix_weight = 0.09228234;
  double neighborhood_weight = 0.22339366;
  double late_weight = 0.23302702;
  double critical_weight = 0.29311635;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
