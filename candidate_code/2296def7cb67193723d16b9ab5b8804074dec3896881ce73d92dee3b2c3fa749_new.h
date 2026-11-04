// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41537171;
  double density_weight = 0.15469719;
  double prefix_weight = 0.20251855;
  double neighborhood_weight = 0.39463532;
  double late_weight = 0.22925609;
  double critical_weight = 0.00585017;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
