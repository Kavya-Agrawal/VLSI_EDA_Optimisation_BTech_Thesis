// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11085205;
  double density_weight = 0.11976084;
  double prefix_weight = 0.09718658;
  double neighborhood_weight = 0.04584399;
  double late_weight = 0.16168610;
  double critical_weight = 0.49417791;
  unsigned budget = 23;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
