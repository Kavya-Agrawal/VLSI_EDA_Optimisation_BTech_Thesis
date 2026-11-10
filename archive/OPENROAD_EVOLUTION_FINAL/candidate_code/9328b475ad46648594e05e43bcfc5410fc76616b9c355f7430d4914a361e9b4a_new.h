// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48921863;
  double density_weight = 0.36776407;
  double prefix_weight = 0.05735643;
  double neighborhood_weight = 0.26807691;
  double late_weight = 0.05409873;
  double critical_weight = 0.24360875;
  unsigned budget = 31;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
