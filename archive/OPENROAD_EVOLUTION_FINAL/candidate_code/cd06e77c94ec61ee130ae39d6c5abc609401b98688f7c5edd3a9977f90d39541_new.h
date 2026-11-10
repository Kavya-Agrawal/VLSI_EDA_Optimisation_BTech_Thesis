// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97398565;
  double density_weight = 0.45208902;
  double prefix_weight = 0.10970318;
  double neighborhood_weight = 0.08220618;
  double late_weight = 0.18137540;
  double critical_weight = 0.41944200;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
