// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67670350;
  double density_weight = 0.43013275;
  double prefix_weight = 0.45320112;
  double neighborhood_weight = 0.05498019;
  double late_weight = 0.29979940;
  double critical_weight = 0.11106795;
  unsigned budget = 11;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
