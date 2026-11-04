// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24803057;
  double density_weight = 0.32600684;
  double prefix_weight = 0.20931347;
  double neighborhood_weight = 0.02936209;
  double late_weight = 0.07176819;
  double critical_weight = 0.29648643;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
