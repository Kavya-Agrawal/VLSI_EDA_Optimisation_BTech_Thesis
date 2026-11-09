// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65132635;
  double density_weight = 0.54023793;
  double prefix_weight = 0.38967857;
  double neighborhood_weight = 0.30043219;
  double late_weight = 0.16105404;
  double critical_weight = 0.35710793;
  unsigned budget = 32;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
