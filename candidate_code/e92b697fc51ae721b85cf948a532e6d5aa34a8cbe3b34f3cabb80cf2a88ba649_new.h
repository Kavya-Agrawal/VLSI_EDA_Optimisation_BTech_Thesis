// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45933896;
  double density_weight = 0.49980484;
  double prefix_weight = 0.27057297;
  double neighborhood_weight = 0.06398357;
  double late_weight = 0.02866721;
  double critical_weight = 0.40993370;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
