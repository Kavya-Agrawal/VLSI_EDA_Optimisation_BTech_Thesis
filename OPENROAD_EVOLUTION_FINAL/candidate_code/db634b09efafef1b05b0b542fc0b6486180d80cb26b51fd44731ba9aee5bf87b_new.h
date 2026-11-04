// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12966150;
  double density_weight = 0.17928088;
  double prefix_weight = 0.05433328;
  double neighborhood_weight = 0.34928722;
  double late_weight = 0.02348543;
  double critical_weight = 0.08699127;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
